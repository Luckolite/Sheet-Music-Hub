// Copyright 2026 Luckolite
// SPDX-License-Identifier: GPL-3.0-only
// Explicit framework substitutes; resolver and event-lambda bodies are extracted unchanged.
#include <iostream>
#include <vector>
#include <map>
#include <set>
enum class SymId { noSym,accidentalDoubleFlat,accidentalFlat,accidentalNatural,accidentalSharp,accidentalDoubleSharp,ornamentTurn,unrelatedGlyph };
enum class OrnamentStyle { DEFAULT };
enum class ClefType { TREBLE,BASS };
enum class Key { C,G };
struct Fraction {int value=480;int ticks()const{return value;}};
struct Staff {ClefType type=ClefType::TREBLE;bool pitched=true;int observedTick=-1;ClefType clef(Fraction f)const{return type;}bool isPitchedStaff(Fraction)const{return pitched;}};
struct Score {Staff staves[2];Staff* staff(int i){return &staves[i];}};
struct Chord {int visualStaff=0;Fraction actualTicks()const{return {};}int vStaffIdx()const{return visualStaff;}Fraction tick()const{return {37};}};
struct Note {
    Score* owner;Chord* c;int effective=60,position=10,defaultUpper=2,defaultLower=-1;
    Chord* chord()const{return c;}Score* score()const{return owner;}int epitch()const{return effective;}int line()const{return position;}
    Staff* staff()const{return owner->staff(c->vStaffIdx());}Fraction tick()const{return c->tick();}
};
int defaultCalls=0,lastDefaultStep=0,lastLine=0;ClefType lastClef=ClefType::TREBLE;Key lastKey=Key::G;
int naturalUpper=62,naturalLower=59;
int chromaticPitchSteps(const Note* l,const Note* r,int step){defaultCalls++;lastDefaultStep=step;if(step){lastLine=l->line()-step;lastClef=l->staff()->type;lastKey=Key::C;}return step==0?0:step==1?l->defaultUpper:step==-1?l->defaultLower:step*2;}
int line2pitch(int line,ClefType clef,Key key){lastLine=line;lastClef=clef;lastKey=key;return line==9?naturalUpper:naturalLower;}
// ACTUAL_ALTERATION
// ACTUAL_RESOLVER
struct NoteEvent {int pitch,ontime,length;NoteEvent(int p,int t,int l):pitch(p),ontime(t),length(l){}};
using NoteEventList=std::vector<NoteEvent>;
std::vector<NoteEvent> sequence(Note* note,bool chromatic,SymId upperAuxiliary,SymId lowerAuxiliary){
    Chord* chord=note->chord();NoteEventList storage;NoteEventList* events=&storage;
    // ACTUAL_EVENT_LAMBDA
    int cursor=48000;
    for(int step:{1,0,-1,0})cursor=makeEvent(step,cursor,24000);
    return storage;
}
struct OrnamentExcursion {SymId atype;std::set<OrnamentStyle> ostyles;int duration;std::vector<int> prefix,body;bool repeatp,sustainp;std::vector<int> suffix;};
std::vector<OrnamentExcursion> excursions={{SymId::ornamentTurn,{},60,{}, {1,0,-1,0},false,true,{}}};
SymId capturedUpper=SymId::noSym,capturedLower=SymId::noSym;
bool renderNoteArticulation(NoteEventList*,Note*,bool,int,const std::vector<int>&,const std::vector<int>&,bool,bool,const std::vector<int>&,int=64,int=8,SymId up=SymId::noSym,SymId low=SymId::noSym){capturedUpper=up;capturedLower=low;return true;}
// ACTUAL_PATTERN_WRAPPER
int count=0,fail=0;
void check(bool ok,const char* name){count++;if(!ok){fail++;std::cout<<"FAIL "<<name<<"\n";}}
int main(){
    Score score;Chord chord;Note note{&score,&chord};
    SymId signs[]={SymId::accidentalDoubleFlat,SymId::accidentalFlat,SymId::accidentalNatural,SymId::accidentalSharp,SymId::accidentalDoubleSharp};
    for(int i=0;i<5;i++){
        check(ornamentPitchSteps(&note,1,signs[i],SymId::noSym)==i,"upper explicit alteration is relative to natural letter");
        check(ornamentPitchSteps(&note,-1,SymId::noSym,signs[i])==i-3,"lower explicit alteration is relative to natural letter");
    }
    note.defaultUpper=3;check(ornamentPitchSteps(&note,1,SymId::noSym,SymId::noSym)==3,"unmarked neighbor keeps prior accidental context");
    check(ornamentPitchSteps(&note,1,SymId::accidentalNatural,SymId::noSym)==2,"explicit natural cancels prior sharp");
    note.effective=64;naturalUpper=65;note.defaultUpper=2;
    check(ornamentPitchSteps(&note,1,SymId::accidentalNatural,SymId::noSym)==1,"natural cancels key signature");
    check(ornamentPitchSteps(&note,1,SymId::noSym,SymId::noSym)==2,"key signature remains when unmarked");
    note.effective=61;naturalUpper=62;naturalLower=59;
    check(ornamentPitchSteps(&note,1,SymId::accidentalFlat,SymId::noSym)==0,"enharmonic unison is not forced upward");
    note.effective=60;check(ornamentPitchSteps(&note,-1,SymId::noSym,SymId::accidentalDoubleSharp)==1,"literal lower spelling may cross principal pitch");
    check(ornamentPitchSteps(&note,0,SymId::accidentalSharp,SymId::accidentalFlat)==0&&note.effective==60,"principal pitch never changes");
    int calls=defaultCalls;check(ornamentPitchSteps(&note,2,SymId::accidentalFlat,SymId::accidentalSharp)==4&&defaultCalls==calls+1,"distant excursion delegates unchanged");
    calls=defaultCalls;check(ornamentPitchSteps(&note,1,SymId::unrelatedGlyph,SymId::noSym)==2&&defaultCalls==calls+1,"unknown mark delegates unchanged");
    chord.visualStaff=1;score.staves[1].type=ClefType::BASS;ornamentPitchSteps(&note,1,SymId::accidentalNatural,SymId::noSym);
    check(lastClef==ClefType::BASS&&lastKey==Key::C&&lastLine==9,"moved staff uses visible clef and natural letter");
    chord.visualStaff=0;auto changed=sequence(&note,false,SymId::accidentalFlat,SymId::accidentalFlat);auto old=sequence(&note,false,SymId::noSym,SymId::noSym);
    check(changed.size()==4&&changed[0].pitch==1&&changed[2].pitch==-2,"actual event generator receives both explicit neighbors");
    bool clocks=changed.size()==old.size();for(unsigned i=0;i<old.size();i++)clocks=clocks&&changed[i].ontime==old[i].ontime&&changed[i].length==old[i].length;
    check(clocks&&changed[0].ontime==100&&changed[0].length==50,"event attack and length are exact unchanged");
    auto chromatic=sequence(&note,true,SymId::accidentalFlat,SymId::accidentalFlat);check(chromatic[0].pitch==1&&chromatic[2].pitch==-1,"chromatic glissando path ignores ornament alterations");
    NoteEventList events;
    // WRAPPER_CALL
    check(capturedUpper==SymId::accidentalFlat&&capturedLower==SymId::accidentalSharp,"pattern wrapper forwards source auxiliary fields");
    score.staves[0].pitched=false;check(!renderNoteArticulation(&events,&note,false,SymId::ornamentTurn,OrnamentStyle::DEFAULT),"unpitched legacy guard remains");
    std::cout<<count<<" controls, "<<fail<<" failures\n";return 0;
}
