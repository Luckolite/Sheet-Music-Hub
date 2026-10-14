// Copyright 2026 Luckolite
// SPDX-License-Identifier: GPL-3.0-only
// Actual native/import/export/layout helper bodies; framework objects substituted.
#include <algorithm>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <iostream>
struct QString {std::string v;bool null=true;QString()=default;QString(const char* s):v(s?s:""),null(!s){}bool isNull()const{return null;}bool isEmpty()const{return v.empty();}bool operator==(const char* s)const{return v==s;}bool operator!=(const char* s)const{return v!=s;}};
using AsciiStringView=QString;
enum class SymId {noSym,ornamentTurn,ornamentTurnInverted,ornamentTrill,articAccentAbove};
enum class Pid {DIRECTION,ARTICULATION_ANCHOR};
enum class PropertyFlags {STYLED,UNSTYLED};
enum class ArticulationAnchor {TOP_STAFF,BOTTOM_STAFF,CHORD};
struct XmlReader {QString tag;bool value;int reads=0;QString name()const{return tag;}bool readBool(){reads++;return value;}};
struct XmlWriter {std::vector<std::pair<QString,bool>> tags;void tag(const char* name,bool value){tags.push_back({name,value});}};
struct EngravingObject {std::map<Pid,PropertyFlags> flags;void setPropertyFlags(Pid p,PropertyFlags f){flags[p]=f;}};
struct Articulation:EngravingObject {SymId _symId=SymId::noSym;bool _delayedTurn=false,up=true;ArticulationAnchor anchor=ArticulationAnchor::CHORD;int auxCalls=0;
 SymId symId()const{return _symId;}void setSymId(SymId s){_symId=s;}void setUp(bool b){up=b;}void setAnchor(ArticulationAnchor a){anchor=a;}
 // ACTUAL_GETTER
 // ACTUAL_SETTER
 bool readDelayedTurn(XmlReader&);void writeDelayedTurn(XmlWriter&)const;
};
// ACTUAL_NATIVE
struct Notation {QString nameValue;SymId symbol;std::map<std::string,QString> attrs;
 QString name()const{return nameValue;}SymId symId()const{return symbol;}QString attribute(const char* name)const{auto i=attrs.find(name);return i==attrs.end()?QString():i->second;}};
struct ChordRest {std::unique_ptr<Articulation> a;void add(Articulation* p){a.reset(p);}};
struct Factory {static Articulation* createArticulation(ChordRest*){return new Articulation;}};
void applyOrnamentAuxiliaries(const Notation&,Articulation* a){a->auxCalls++;}
// ACTUAL_PROPERTY
// ACTUAL_IMPORTER
QString symIdToOrnam(SymId s){return s==SymId::ornamentTurn?"turn":s==SymId::ornamentTurnInverted?"inverted-turn":s==SymId::ornamentTrill?"trill-mark":"";}
// ACTUAL_EXPORT
struct Measure {double w=100;double width()const{return w;}};
struct Segment {double xpos=10;Measure* owner;Segment* next=nullptr;int observedTrack=-1;
 Segment* nextCR(int track){observedTrack=track;return next;}Measure* measure()const{return owner;}double x()const{return xpos;}};
struct Chord {double center=2,xpos=1;bool grace=false;int part=3;Segment* seg;Measure* m;
 double centerX()const{return center;}bool isGrace()const{return grace;}Segment* segment()const{return seg;}Measure* measure()const{return m;}int track()const{return part;}double x()const{return xpos;}};
// ACTUAL_LAYOUT
int count=0,fail=0;void check(bool ok,const char* name){count++;if(!ok){fail++;std::cout<<"FAIL "<<name<<"\n";}}
int main(){
 auto import=[](const char* name,SymId symbol){Notation n{name,symbol,{}};n.attrs["placement"]="below";ChordRest cr;addArticulationToChord(n,&cr);return std::move(cr.a);};
 auto turn=import("delayed-turn",SymId::ornamentTurn);auto inverse=import("delayed-inverted-turn",SymId::ornamentTurnInverted);
 check(turn->delayedTurn(),"import retains delayed turn state");
 check(inverse->delayedTurn(),"import retains delayed inverted turn state");
 check(turn->anchor==ArticulationAnchor::BOTTOM_STAFF&&turn->auxCalls==1,"placement and auxiliary binding preserved");
 check(!import("turn",SymId::ornamentTurn)->delayedTurn(),"ordinary turn stays immediate");
 check(!import("trill-mark",SymId::ornamentTrill)->delayedTurn(),"trill stays immediate");
 check(articulationOrnamentXml(turn.get())=="delayed-turn","export keeps delayed turn element");
 check(articulationOrnamentXml(inverse.get())=="delayed-inverted-turn","export keeps delayed inverted element");
 Articulation clone=*turn;XmlWriter out;clone.writeDelayedTurn(out);
 check(out.tags.size()==1&&out.tags[0].first=="delayedTurn"&&out.tags[0].second,"native write keeps delayed field");
 Articulation restored;restored.setSymId(SymId::ornamentTurn);XmlReader read{"delayedTurn",true};bool consumed=restored.readDelayedTurn(read);
 check(consumed&&read.reads==1&&restored.delayedTurn(),"native read retains delayed state");
 XmlReader no{"unrelated",true};check(!restored.readDelayedTurn(no)&&no.reads==0,"unrelated field remains untouched");
 XmlReader clear{"delayedTurn",false};restored.readDelayedTurn(clear);check(!restored.delayedTurn(),"explicit false clears delay");
 check(clone.delayedTurn()==turn->delayedTurn(),"copy preserves delay");
 clone.setSymId(SymId::ornamentTrill);XmlWriter nonTurn;clone.writeDelayedTurn(nonTurn);
 check(!clone.delayedTurn()&&nonTurn.tags.empty()&&articulationOrnamentXml(&clone)=="trill-mark","non-turn cannot inherit delayed serialization");
 Measure measure,other;Segment current{10,&measure},next{50,&measure};current.next=&next;Chord chord{2,1,false,3,&current,&measure};
 check(delayedTurnX(&chord, chord.center)==20.5,"delayed center lies halfway to next track onset");
 check(current.observedTrack==3,"next event search uses owner track");
 next.owner=&other;check(delayedTurnX(&chord, chord.center)==45.5,"system break uses current bar end");
 current.next=nullptr;check(delayedTurnX(&chord, chord.center)==45.5,"last onset uses current bar end");
 chord.grace=true;check(delayedTurnX(&chord, chord.center)==2,"grace ornaments keep original center");
 chord.grace=false;current.next=&next;next.owner=&measure;next.xpos=5;check(delayedTurnX(&chord, chord.center)==2,"invalid reverse geometry cannot move left");
 chord.seg=nullptr;check(delayedTurnX(&chord, chord.center)==2,"unattached chord keeps original center");
 std::cout<<count<<" controls, "<<fail<<" failures\n";return 0;
}
