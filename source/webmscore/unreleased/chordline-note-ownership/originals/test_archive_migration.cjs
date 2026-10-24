// Copyright 2026 Luckolite
// SPDX-License-Identifier: Apache-2.0
const fs=require('fs'),path=require('path'),cp=require('child_process');
const[oldBundle,newBundle,out,phase]=process.argv.slice(2);if(!oldBundle||!newBundle||!out)throw Error('Expected old bundle, candidate bundle, output directory');
if(!phase){if(fs.existsSync(out))throw Error('Use a new output directory');fs.mkdirSync(out,{recursive:true});for(const p of ['old','new'])cp.execFileSync(process.execPath,[__filename,oldBundle,newBundle,out,p],{stdio:'inherit'});process.exit(0);}
global.fetch=undefined;delete global.navigator;const M=require(path.resolve(phase==='old'?oldBundle:newBundle,'webmscore.nodejs.cjs')),source=fs.readFileSync(path.join(__dirname,'fixtures/two-head-two-scoop.musicxml'));
(async()=>{await M.ready;await M.setLogLevel(0);const live=[];
 if(phase==='old'){const s=await M.load('musicxml',source);live.push(s);fs.writeFileSync(path.join(out,'legacy.mscz'),await s.saveMsc('mscz'));fs.writeFileSync(path.join(out,'legacy.mscx'),await s.saveMsc('mscx'));}
 else{let s=await M.load('mscz',fs.readFileSync(path.join(out,'legacy.mscz')));live.push(s);const direct=Buffer.from(await s.saveMsc('mscx')).toString();fs.writeFileSync(path.join(out,'direct-legacy.mscx'),direct);s=await M.load('musicxml',source);live.push(s);s=await M.load('mscz',await s.saveMsc('mscz'));live.push(s);const fresh=Buffer.from(await s.saveMsc('mscx')).toString();fs.writeFileSync(path.join(out,'fresh-source-reimport.mscx'),fresh);const nested=x=>[...x.matchAll(/<Note>[\s\S]*?<\/Note>/g)].reduce((n,m)=>n+(m[0].match(/<ChordLine>/g)||[]).length,0);if(nested(direct)!==0||nested(fresh)!==2)throw Error('Legacy/retained-source migration boundary changed');fs.writeFileSync(path.join(out,'receipt.json'),JSON.stringify({result:'PASS',directOldArchiveNotMigrated:true,freshOriginalMusicXmlReimportRestoresOwners:true,customNativeOwnerTags:false},null,2));console.log('PASS: legacy remains legacy; original-source reimport repairs canonical owners.');}
 process.exit(0);
})().catch(e=>{console.error(e.stack);process.exit(1)});
