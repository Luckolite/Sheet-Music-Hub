// Copyright 2026 Luckolite
// SPDX-License-Identifier: Apache-2.0
// Reproject source-validated isolated approach/departure shape attributes onto a newly exported XML clone.
(()=>{'use strict';
 const F=HairpinSource.Fraction,z=F.from(0),need=(v,m)=>{if(!v)throw Error('Source chord-line export: '+m);};
 const children=(p,n)=>[...p.children].filter(e=>e.localName===n),field=(p,n,d=null)=>{const a=children(p,n);need(a.length<=1,'duplicate '+n);return a.length?a[0].textContent.trim():d;};
 const integer=v=>{need(/^[+-]?\d+$/.test(String(v)),'expected integer');const n=Number(v);need(Number.isSafeInteger(n),'integer overflow');return n;},steps={C:0,D:2,E:4,F:5,G:7,A:9,B:11};
 const key=c=>JSON.stringify([c.part,c.staff,c.measure,c.start.toString(),c.duration.toString(),[...c.pitches].sort((a,b)=>a-b),c.grace,c.ordinal]);
 function columns(doc){
  need(doc.documentElement?.localName==='score-partwise'&&!doc.getElementsByTagName('parsererror').length,'valid partwise XML required');const out=[];
  children(doc.documentElement,'part').forEach((part,pi)=>{let divisions=null;const ordinals=new Map();
   children(part,'measure').forEach((measure,mi)=>{let cursor=z;const previous=new Map();
    for(const node of [...measure.children]){
     if(node.localName==='attributes'){const d=field(node,'divisions');if(d!==null){divisions=integer(d);need(divisions>0,'divisions');}continue;}
     if(!['note','backup','forward'].includes(node.localName))continue;need(divisions!==null,'missing divisions');
     const grace=children(node,'grace').length>0,duration=grace?z:new F(field(node,'duration',''),4*divisions);
     if(node.localName==='backup'){cursor=cursor.subtract(duration);need(cursor.compare(z)>=0,'negative cursor');continue;}if(node.localName==='forward'){cursor=cursor.add(duration);continue;}
     const voice=field(node,'voice','1'),staff=field(node,'staff','1'),chord=children(node,'chord').length>0;let c;
     if(chord){c=previous.get(voice);need(c&&c.staff===staff&&c.duration.compare(duration)===0&&c.grace===grace,'mixed/orphan chord');}
     else {let ordinal=0;if(grace){const k=JSON.stringify([pi,staff,mi,voice,cursor.toString()]);ordinal=ordinals.get(k)||0;ordinals.set(k,ordinal+1);}c={part:pi,staff,measure:mi,voice,start:cursor,duration,grace,ordinal,pitches:[],nodes:[],beams:[]};out.push(c);previous.set(voice,c);if(!grace)cursor=cursor.add(duration);}
     c.nodes.push(node);const p=children(node,'pitch');if(p.length){need(p.length===1&&Object.hasOwn(steps,field(p[0],'step')),'supported pitched identity required');c.pitches.push((integer(field(p[0],'octave'))+1)*12+steps[field(p[0],'step')]+integer(field(p[0],'alter','0')));}
     else need(children(node,'rest').length===1,'unpitched source needs explicit display identity');
     c.beams.push(...children(node,'beam'));
    }
   });
  });return out;
 }
 function restore(source,exported,native,options={}){
  const serialize=d=>new XMLSerializer().serializeToString(d);
  const candidate=exported.cloneNode(true),symbols={scoop:'4',plop:'3',falloff:'1'};
  const printAttrs=['line-shape','line-type'];
  const requested=[...source.querySelectorAll('notations > articulations > *')].filter(n=>Object.hasOwn(symbols,n.localName)&&printAttrs.some(a=>n.hasAttribute(a)));
  const own=[...source.querySelectorAll('encoding > software')].some(n=>n.textContent==='Music Sheets');
  if(!own||!requested.length)return {document:candidate,proof:{owned:false,requested:0,changed:0}};
  need(native?.documentElement?.localName==='museScore','native source-owner proof required');
  const sourceBefore=serialize(source),nativeBefore=serialize(native),exportBefore=serialize(exported);
  need(!source.querySelector('unpitched'),'display-carrier articulation export requires a separate owner projection');
  for(const mark of requested){
   need(!mark.hasAttribute('line-shape')||['straight','curved'].includes(mark.getAttribute('line-shape')),'unsupported line-shape');
   need(!mark.hasAttribute('line-type')||mark.getAttribute('line-type')==='solid','unsupported line-type');
   need(mark.localName!=='falloff'||!mark.hasAttribute('line-shape')||mark.getAttribute('line-shape')==='curved','straight falloff is outside this qualified source contract');
  }
  const identity=HairpinIdentity.identify(source,native,options);
  const sourceParts=children(source.documentElement,'part'),nativeStaffMap=new Map(identity.mapping.map(m=>[m.nativeStaff,{part:sourceParts.findIndex(p=>p.getAttribute('id')===m.partId),staff:m.sourceStaff}])),nativeStems=new Map(),nativeOrdinals=new Map();
  HairpinIdentity.walkNative(native,identity.plan.lengths,({sid,mi,vi,node,cursor,duration,grace})=>{
   if(node.localName!=='Chord')return;const where=nativeStaffMap.get(sid);need(where,'unmapped native source staff');let ordinal=0;if(grace){const k=JSON.stringify([sid,mi,vi,cursor.toString()]);ordinal=nativeOrdinals.get(k)||0;nativeOrdinals.set(k,ordinal+1);}
   const pitches=children(node,'Note').map(n=>integer(field(n,'pitch'))),k=key({...where,measure:mi,start:cursor,duration,pitches,grace,ordinal});if(!nativeStems.has(k))nativeStems.set(k,[]);nativeStems.get(k).push(node);
  });
  const expected=columns(source),actual=columns(candidate),lookup=new Map();for(const c of actual){const k=key(c);if(!lookup.has(k))lookup.set(k,[]);lookup.get(k).push(c);}
  const lane=c=>JSON.stringify([c.part,c.staff,c.voice]),lanes=new Map(),pending=[],mapped=new Map(),used=new Set();
  for(const c of expected){if(!c.pitches.length)continue;const found=lookup.get(key(c))||[];need(found.length,'source pitch/clock/chord absent from new export');if(found.length===1){const known=lanes.get(lane(c));need(known===undefined||known===found[0].voice,'inconsistent output voice mapping');lanes.set(lane(c),found[0].voice);mapped.set(c,found[0]);}else pending.push([c,found]);}
  for(const[c,found]of pending){const matches=found.filter(t=>t.voice===lanes.get(lane(c)));need(matches.length===1,'ambiguous output unison');mapped.set(c,matches[0]);}
  for(const t of mapped.values()){need(!used.has(t),'source stems alias one output stem');used.add(t);}
  const midi=note=>{const p=children(note,'pitch')[0];need(p&&Object.hasOwn(steps,field(p,'step')),'pitched endpoint required');return(integer(field(p,'octave'))+1)*12+steps[field(p,'step')]+integer(field(p,'alter','0'));};
  const jobs=[],claimed=new Set(),groups=new Map();let persistentNativeOwners=0,multiplicityGroups=0;
  const marksOf=(note,kind)=>children(note,'notations').flatMap(n=>children(n,'articulations')).flatMap(n=>children(n,kind));
  for(const c of expected)for(const note of c.nodes)for(const mark of children(note,'notations').flatMap(n=>children(n,'articulations')).flatMap(n=>[...n.children]).filter(n=>requested.includes(n)))groups.set(key(c)+'|'+mark.localName,{column:c,kind:mark.localName});
  for(const {column:c,kind} of groups.values()){
   const rows=c.nodes.flatMap(note=>marksOf(note,kind).map(mark=>({note,mark}))),nativeOwners=nativeStems.get(key(c))||[];
   need(nativeOwners.length===1,'missing or ambiguous native source stem');
   const nativeStem=nativeOwners[0],glyphs=[...children(nativeStem,'ChordLine'),...children(nativeStem,'Note').flatMap(n=>children(n,'ChordLine'))].filter(n=>field(n,'subtype','')===symbols[kind]),target=mapped.get(c);need(target,'missing source stem');
   const marks=target.nodes.flatMap(n=>marksOf(n,kind));need(glyphs.length===rows.length,'source/native chord-line multiplicity differs');need(marks.length===rows.length,'source/output chord-line multiplicity differs');
   const multiple=rows.length>1,usedPitches=new Set(),usedGlyphs=new Set();if(multiple)multiplicityGroups++;
   for(const {note,mark} of rows){
    const pitch=midi(note),heads=target.nodes.filter(n=>children(n,'pitch').length&&midi(n)===pitch);need(heads.length===1,'ambiguous output chord head');
    need(!usedPitches.has(pitch),'duplicate source chord-line head owner');usedPitches.add(pitch);
    let glyph,output;
    if(multiple){
     const owned=glyphs.filter(n=>{need(n.parentElement?.localName==='Note','multiple native chord lines require persistent note owners');const p=integer(field(n.parentElement,'pitch'));need(p>=0&&p<=127,'native chord-line owner outside pitch domain');return p===pitch;});
     need(owned.length===1,'missing or ambiguous native chord-line head owner');glyph=owned[0];
     const exact=marksOf(heads[0],kind);need(exact.length===1,'multiple output chord lines must retain exact source heads');output=exact[0];
    }else{
     glyph=glyphs[0];output=marks[0];
    }
    const owner=glyph.parentElement?.localName==='Note'?glyph.parentElement:null;
    if(owner){const p=integer(field(owner,'pitch'));need(p>=0&&p<=127&&p===pitch,'native chord-line owner differs from source head');need(children(nativeStem,'Note').filter(n=>integer(field(n,'pitch'))===p).length===1,'ambiguous native chord-line pitch owner');persistentNativeOwners++;}
    else need(children(nativeStem,'Note').length===1,'unbound legacy chord line has no exact head proof in a multi-note chord');
    need(!usedGlyphs.has(glyph),'native chord-line owner reused');usedGlyphs.add(glyph);
    const straight=field(glyph,'straight','0');need(['0','1'].includes(straight),'invalid native straightness');need((straight==='1')===(mark.getAttribute('line-shape')==='straight'),'native chord-line shape does not match source; patched importer required');
    if(requested.includes(mark)){need(!claimed.has(output),'conflicting source articulation owners in one chord');claimed.add(output);jobs.push({source:mark,target:output,note:heads[0]});}
   }
  }
  const pathOf=node=>{const p=[];for(let n=node;n.parentElement;n=n.parentElement)p.push([...n.parentElement.children].indexOf(n));return p.reverse();};
  const beforePaths=jobs.map(j=>pathOf(j.target));
  let changed=0,moved=0,attributes=0;
  for(const job of jobs){let edited=false;for(const attr of printAttrs)if(job.source.hasAttribute(attr)&&job.target.getAttribute(attr)!==job.source.getAttribute(attr)){job.target.setAttribute(attr,job.source.getAttribute(attr));attributes++;edited=true;}
   if(job.target.parentElement.parentElement.parentElement!==job.note){let notation=children(job.note,'notations')[0];if(!notation){notation=candidate.createElement('notations');const later=[...job.note.children].find(n=>['lyric','play','listen'].includes(n.localName));job.note.insertBefore(notation,later||null);}let art=children(notation,'articulations')[0];if(!art){art=candidate.createElement('articulations');notation.appendChild(art);}art.appendChild(job.target);moved++;edited=true;}
   if(edited)changed++;
  }
  need(jobs.length===requested.length,'incomplete chord-line projection');
  const scrub=(doc,paths)=>{const c=doc.cloneNode(true),nodes=paths.map(p=>p.reduce((node,index)=>node.children[index],c.documentElement));nodes.forEach(n=>n.remove());for(const n of [...c.querySelectorAll('articulations, notations')].reverse())if(!n.children.length&&!n.textContent.trim())n.remove();return serialize(c);};
  need(scrub(exported,beforePaths)===scrub(candidate,jobs.map(j=>pathOf(j.target))),'unrelated exported notation fields changed');
  need(sourceBefore===serialize(source)&&nativeBefore===serialize(native)&&exportBefore===serialize(exported),'input mutation');
  return {document:candidate,proof:{owned:true,requested:requested.length,changed,attributes,moved,mappedNotes:identity.noteCount,persistentNativeOwners,multiplicityGroups,otherExportedFieldsExact:true,sourceAndNativeInputsUntouched:true,scope:'scoop/plop straight or curved and curved falloff, solid line-type only, on exact pitched complete-stem owners; multiple same-kind glyphs require persistent native note owners and exact output heads; other notations untouched'}};
 }
 globalThis.SourceChordLineExport=Object.freeze({restore});
})();
