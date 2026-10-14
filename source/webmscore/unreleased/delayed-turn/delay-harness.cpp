// Copyright 2026 Luckolite
// SPDX-License-Identifier: GPL-3.0-only
// Actual event function and wrapper; explicit framework substitutes below.
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
namespace Constants { constexpr int division=480; }
enum class SymId {noSym,accidentalDoubleFlat,accidentalFlat,accidentalNatural,accidentalSharp,accidentalDoubleSharp,ornamentTurn,ornamentTurnInverted,ornamentTrill};
enum class OrnamentStyle {DEFAULT};
enum class Key {C};
enum class ClefType {TREBLE};
struct Fraction {int val=480; int ticks()const{return val;}};
struct BeatsPerSecond {double val=2.;};
struct Staff {ClefType clef(Fraction)const{return ClefType::TREBLE;}bool isPitchedStaff(Fraction)const{return true;}};
struct Score {Staff st;Staff* staff(int){return &st;}BeatsPerSecond tempo(Fraction)const{return {};}};
struct Note;
struct Chord {Score owner;int duration=480;std::vector<Chord*> before,after;std::vector<Note*> heads;
 Fraction tick()const{return {};}Fraction actualTicks()const{return {duration};}int vStaffIdx()const{return 0;}
 Score* score(){return &owner;}const std::vector<Chord*>& graceNotesBefore()const{return before;}
 const std::vector<Chord*>& graceNotesAfter()const{return after;}const std::vector<Note*>& notes()const{return heads;}};
enum class ElementType {GLISSANDO,OTHER};
struct Spanner {ElementType type()const{return ElementType::OTHER;}};
struct Glissando {int easeIn()const{return 0;}int easeOut()const{return 0;}};
Glissando* toGlissando(Spanner*){return nullptr;}
struct EaseInOut {EaseInOut(double,double){}void timeList(int,int,std::vector<int>*){}};
struct Note {Chord* c;int tone=60;Chord* chord()const{return c;}Score* score()const{return &c->owner;}
 int epitch()const{return tone;}int pitch()const{return tone;}int line()const{return 10;}bool play()const{return true;}
 Staff* staff()const{return &c->owner.st;}Fraction tick()const{return c->tick();}
 std::vector<Spanner*> spannerFor()const{return {};}};
int totalTiedNoteTicks(Note* n){return n->c->duration;}
int chromaticPitchSteps(const Note*,const Note*,int step){return step==1?2:step==-1?-1:0;}
int line2pitch(int line,ClefType,Key){return line==9?62:59;}
struct NoteEvent {int pitch,ontime,length;NoteEvent(int p,int o,int l):pitch(p),ontime(o),length(l){}};
using NoteEventList=std::vector<NoteEvent>;
// ACTUAL_PITCH_HELPERS
// ACTUAL_EVENT_FUNCTION
struct OrnamentExcursion {SymId atype;std::set<OrnamentStyle> ostyles;int duration;std::vector<int> prefix,body;bool repeatp,sustainp;std::vector<int> suffix;};
std::vector<OrnamentExcursion> excursions={
 {SymId::ornamentTurn,{},60,{}, {1,0,-1,0},false,true,{}},
 {SymId::ornamentTurnInverted,{},60,{}, {-1,0,1,0},false,true,{}},
 {SymId::ornamentTrill,{},60,{}, {1,0},true,true,{}}};
// ACTUAL_WRAPPER
int count=0,failed=0;
void check(bool ok,const char* name){count++;if(!ok){failed++;std::cout<<"FAIL "<<name<<"\n";}}
bool same(const NoteEventList& a,const NoteEventList& b){if(a.size()!=b.size())return false;for(size_t i=0;i<a.size();i++)if(a[i].pitch!=b[i].pitch||a[i].ontime!=b[i].ontime||a[i].length!=b[i].length)return false;return true;}
int eventEnd(const NoteEventList& e){return e.back().ontime+e.back().length;}
int main(){
 Chord chord;Note note{&chord};NoteEventList immediate,delayed,inverse;
 // IMMEDIATE_CALL
 // DELAYED_CALL
 // INVERSE_CALL
 check(immediate.size()==4,"immediate attack count unchanged");
 check(immediate[0].pitch==2&&immediate[0].ontime==0,"immediate starts upper at source attack");
 check(eventEnd(immediate)==1000,"immediate clock preserved");
 check(delayed.size()==5,"delayed adds principal lead");
 check(delayed.front().pitch==0&&delayed.front().ontime==0,"delayed starts principal");
 check(delayed.front().length==500,"spare sustain held before turn");
 check(delayed.size()==5&&delayed[1].pitch==2&&delayed[1].ontime==500,"upper turn starts after lead");
 check(delayed.size()==5&&delayed.back().length==125,"final note does not swallow leading sustain");
 check(eventEnd(delayed)==1000,"delayed exact total duration");
 check(inverse.size()==5&&inverse.front().pitch==0&&inverse[1].pitch==-1,"inverted delayed begins principal then lower");
 NoteEventList explicitSigns;
 // SIGNS_CALL
 check(explicitSigns.size()==5&&explicitSigns[1].pitch==1&&explicitSigns[3].pitch==0,"delayed turn forwards both auxiliary signs");
 chord.duration=120;
 NoteEventList shortTurn;
 // SHORT_CALL
 check(shortTurn.size()==5&&shortTurn.front().pitch==0,"short delay reserves principal pulse");
 check(eventEnd(shortTurn)==1000,"short delay exact total clock");
 check(std::all_of(shortTurn.begin(),shortTurn.end(),[](const NoteEvent& e){return e.length>0;}),"positive event lengths");
 chord.duration=60;NoteEventList tooShort;
 // TINY_CALL
 check(tooShort.empty(),"impossible five-pulse ornament rejects cleanly");
 chord.duration=480;
 Chord before,after;Note beforeNote{&before,57},afterNote{&after,64};before.heads={&beforeNote};after.heads={&afterNote};chord.before={&before};chord.after={&after};
 NoteEventList graceTurn;
 // GRACE_CALL
 check(graceTurn.size()==7,"grace heads and principal lead retained");
 check(graceTurn.front().pitch==-3&&graceTurn.front().ontime==0,"prefix grace precedes principal");
 check(graceTurn.size()==7&&graceTurn[1].pitch==0&&graceTurn[2].pitch==2,"prefix grace then principal then turn");
 check(graceTurn.back().pitch==4&&eventEnd(graceTurn)==1000,"after grace follows turn with exact clock");
 chord.before.clear();chord.after.clear();
 NoteEventList normalTrill,flaggedTrill;
 // NORMAL_TRILL_CALL
 // FLAGGED_TRILL_CALL
 check(same(normalTrill,flaggedTrill),"delayed flag cannot alter non-turn ornament");
 std::cout<<count<<" controls, "<<failed<<" failures\n";return 0;
}
