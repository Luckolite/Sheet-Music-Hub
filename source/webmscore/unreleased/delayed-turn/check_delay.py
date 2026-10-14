# Copyright 2026 Luckolite
# SPDX-License-Identifier: GPL-3.0-only
"""Qualify delayed-turn source state, layout geometry and legacy MIDI event clocks."""
from pathlib import Path
import argparse, hashlib, json, subprocess, sys, re
ROOT=Path(__file__).resolve().parent

def extract(text,name):
 start=text.index(name);opening=text.index('{',start);depth=0
 for end in range(opening,len(text)):
  depth+=(text[end]=='{')-(text[end]=='}')
  if not depth:return text[start:end+1]
 raise ValueError(name)

def run_events(r, trees, emcc, node, flags):
 results=[]
 for mode in ('before','after'):
  text=(trees[mode]/'src/engraving/libmscore/rendermidi.cpp').read_text(encoding='utf-8')
  h=(ROOT/'delay-harness.cpp').read_text(encoding='utf-8')
  h=h.replace('// ACTUAL_PITCH_HELPERS','\n'.join(extract(text,n) for n in ('static bool ornamentAuxiliaryAlteration(','static int ornamentPitchSteps(')))
  h=h.replace('// ACTUAL_EVENT_FUNCTION',extract(text,'bool renderNoteArticulation(NoteEventList* events, Note* note, bool chromatic, int requestedTicksPerNote,'))
  h=h.replace('// ACTUAL_WRAPPER',extract(text,'bool renderNoteArticulation(NoteEventList* events, Note* note, bool chromatic, SymId articulationType, OrnamentStyle ornamentStyle'))
  for name,out,sym,delay,up,low in [('IMMEDIATE','immediate','ornamentTurn',False,'noSym','noSym'),('DELAYED','delayed','ornamentTurn',True,'noSym','noSym'),('INVERSE','inverse','ornamentTurnInverted',True,'noSym','noSym'),('SIGNS','explicitSigns','ornamentTurn',True,'accidentalFlat','accidentalSharp'),('SHORT','shortTurn','ornamentTurn',True,'noSym','noSym'),('TINY','tooShort','ornamentTurn',True,'noSym','noSym'),('GRACE','graceTurn','ornamentTurn',True,'noSym','noSym'),('NORMAL_TRILL','normalTrill','ornamentTrill',False,'noSym','noSym'),('FLAGGED_TRILL','flaggedTrill','ornamentTrill',True,'noSym','noSym')]:
   call=f'renderNoteArticulation(&{out},&note,false,SymId::{sym},OrnamentStyle::DEFAULT,SymId::{up},SymId::{low}'+(','+str(delay).lower() if mode=='after' else '')+');'
   h=h.replace('// '+name+'_CALL',call)
  src=r/(mode+'-events.cpp');out=r/(mode+'-events.js');src.write_bytes(h.encode('utf-8'))
  p=subprocess.run([*emcc,str(src),'-std=c++17','-O0','-s','SINGLE_FILE=1','-s','ENVIRONMENT=node','-o',str(out)],capture_output=True,text=True,**flags)
  if p.returncode:raise RuntimeError(p.stdout+p.stderr)
  p=subprocess.run([node,str(out)],capture_output=True,text=True,**flags);(r/(mode+'-events.log')).write_bytes((p.stdout+p.stderr).encode('utf-8'));print(mode,p.stdout)
  m=re.search(r'(\d+) controls, (\d+) failures',p.stdout)
  if p.returncode or not m:raise RuntimeError(p.stdout+p.stderr)
  count,failed=map(int,m.groups())
  if count!=20 or failed!=(11 if mode=='before' else 0):raise RuntimeError('Unexpected event report: '+p.stdout)
  results.append(dict(mode=mode,controls=count,failures=failed))
 (r/'event-receipt.json').write_bytes((json.dumps(dict(results=results,frameworkObjectsSubstituted=True,actualWholeEventFunctionExtracted=True,fullRendererRuntimeProven=False),indent=2)+'\n').encode('utf-8'))

def run_state(r, trees, emcc, node, flags):
 results=[]
 for mode in ('before','after'):
  base=trees[mode]
  a=(base/'src/engraving/libmscore/articulation.cpp').read_text(encoding='utf-8')
  header=(base/'src/engraving/libmscore/articulation.h').read_text(encoding='utf-8')
  i=(base/'src/importexport/musicxml/internal/musicxml/importmxmlpass2.cpp').read_text(encoding='utf-8')
  e=(base/'src/importexport/musicxml/internal/musicxml/exportxml.cpp').read_text(encoding='utf-8')
  c=(base/'src/engraving/libmscore/chord.cpp').read_text(encoding='utf-8')
  h=(ROOT/'state-harness.cpp').read_text(encoding='utf-8')
  bodies=dict(GETTER=extract(header,'bool delayedTurn() const') if mode=='after' else 'bool delayedTurn()const{return false;}',
  SETTER=extract(header,'void setDelayedTurn(') if mode=='after' else 'void setDelayedTurn(bool){}',
  NATIVE='\n'.join(extract(a,n) for n in ('bool Articulation::readDelayedTurn(','void Articulation::writeDelayedTurn(')) if mode=='after' else 'bool Articulation::readDelayedTurn(XmlReader&){return false;}void Articulation::writeDelayedTurn(XmlWriter&)const{}',
  PROPERTY=extract(i,'static void setElementPropertyFlags('),
  IMPORTER=extract(i,'static void addArticulationToChord('),
  EXPORT=extract(e,'static QString articulationOrnamentXml(') if mode=='after' else 'static QString articulationOrnamentXml(const Articulation* a){return symIdToOrnam(a->symId());}',
  LAYOUT=extract(c,'static double delayedTurnX(') if mode=='after' else 'static double delayedTurnX(const Chord*,double x){return x;}')
  for key,body in bodies.items():h=h.replace('// ACTUAL_'+key,body)
  src=r/(mode+'-state.cpp');out=r/(mode+'-state.js');src.write_bytes(h.encode('utf-8'))
  p=subprocess.run([*emcc,str(src),'-std=c++17','-O0','-s','SINGLE_FILE=1','-s','ENVIRONMENT=node','-o',str(out)],capture_output=True,text=True,**flags)
  if p.returncode:raise RuntimeError((p.stdout+p.stderr)[:6000])
  p=subprocess.run([node,str(out)],capture_output=True,text=True,**flags);(r/(mode+'-state.log')).write_bytes((p.stdout+p.stderr).encode('utf-8'));print(mode,p.stdout)
  m=re.search(r'(\d+) controls, (\d+) failures',p.stdout)
  if p.returncode or not m:raise RuntimeError(p.stdout+p.stderr)
  count,failed=map(int,m.groups())
  if count!=20 or failed!=(10 if mode=='before' else 0):raise RuntimeError('Unexpected state report: '+p.stdout)
  results.append(dict(mode=mode,controls=count,failures=failed))
 (r/'state-receipt.json').write_bytes((json.dumps(dict(results=results,frameworkObjectsSubstituted=True,baselineUsesNoStateAdapter=True,fullRendererRuntimeProven=False),indent=2)+'\n').encode('utf-8'))

def sha(path):
 return hashlib.sha256(path.read_bytes().replace(b'\r\n',b'\n')).hexdigest()

def main():
 parser=argparse.ArgumentParser(description=__doc__)
 parser.add_argument('--checkout',type=Path,required=True)
 parser.add_argument('--output',type=Path,required=True)
 parser.add_argument('--emcc',default='em++')
 parser.add_argument('--node',default='node')
 args=parser.parse_args()
 manifest=json.loads((ROOT/'manifest.json').read_text(encoding='utf-8'))
 for name,expected in manifest['files'].items():
  if sha(ROOT/name)!=expected:raise ValueError('Packet differs: '+name)
 flags={'creationflags':subprocess.CREATE_NO_WINDOW} if sys.platform=='win32' else {}
 trees={'before':args.output/'baseline-tree','after':args.checkout}
 for name,expected in manifest['afterFiles'].items():
  source=args.checkout/name
  if sha(source)!=expected:raise ValueError('Checkout differs: '+name)
  destination=trees['before']/name;destination.parent.mkdir(parents=True,exist_ok=True)
  destination.write_bytes(source.read_bytes())
 subprocess.run(['git','apply','--reverse','--directory=baseline-tree',str(ROOT/'delayed-turn.patch')],cwd=args.output,check=True,**flags)
 for name,expected in manifest['beforeFiles'].items():
  if sha(trees['before']/name)!=expected:raise ValueError('Baseline differs: '+name)
 compiler=[sys.executable,args.emcc] if args.emcc.endswith('.py') else [args.emcc]
 # The extracted harness compiler orchestration uses Python em++.py or a native em++.
 run_events(args.output,trees,compiler,args.node,flags)
 run_state(args.output,trees,compiler,args.node,flags)

if __name__=='__main__':main()
