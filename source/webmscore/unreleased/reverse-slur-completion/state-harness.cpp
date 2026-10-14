// Copyright 2026 Luckolite
// SPDX-License-Identifier: GPL-3.0-only
// Original minimal host for testing the actual extracted GPL importer function.
// These substitutes exercise completion state, not MuseScore layout or lifetime internals.
extern "C" int puts(const char*);
bool same(const char* a,const char* b){while(*a&&*a==*b){a++;b++;}return *a==*b;}
struct QString {
    const char* text;QString(const char* s=""):text(s){}
    bool operator==(const char* s)const{return same(text,s);}
    int toInt()const{int n=0;for(const char* p=text;*p>='0'&&*p<='9';p++)n=n*10+*p-'0';return n;}
    QString arg(const QString&)const{return *this;}
};
struct QXmlStreamReader{};
struct MxmlLogger{int errors=0;void logError(const QString&,const QXmlStreamReader*){errors++;}};
struct Notation{
    const char* type;const char* line="";const char* placement="";
    QString attribute(const char* key)const{
        return same(key,"type")?type:same(key,"number")?"1":same(key,"line-type")?line:placement;
    }
};
struct Fraction{long value;static Fraction fromTicks(int n){return {n};}};
struct Spanner{enum class Anchor{DEFAULT,CHORD};};
enum class SlurStyleType{Solid,Dotted,Dashed};
enum class DirectionV{AUTO,UP,DOWN};
struct Score;
struct ChordRest{
    Score* owner;int voiceTrack;bool grace=false;
    Score* score(){return owner;}int track()const{return voiceTrack;}bool isGrace()const{return grace;}
};
ChordRest* toChordRest(ChordRest* p){return p;}
struct Slur{
    long startTick=0,duration=0;int startTrack=0,endTrack=0;
    ChordRest* start=nullptr;ChordRest* end=nullptr;
    Spanner::Anchor anchor=Spanner::Anchor::DEFAULT;
    SlurStyleType style=SlurStyleType::Solid;DirectionV direction=DirectionV::AUTO;
    void setTick(Fraction t){startTick=t.value;}void setTick2(Fraction t){duration=t.value-startTick;}
    Fraction tick2()const{return {startTick+duration};}
    void setStartElement(ChordRest* p){start=p;}void setEndElement(ChordRest* p){end=p;}
    ChordRest* endElement()const{return end;}
    void setTrack(int n){startTrack=n;}void setTrack2(int n){endTrack=n;}
    void setAnchor(Spanner::Anchor a){anchor=a;}void setStyleType(SlurStyleType s){style=s;}
    void setSlurDirection(DirectionV d){direction=d;}
};
struct Score{
    Slur pool[16];Slur* registered[16];int allocated=0,count=0;
    Score* dummy(){return this;}void addElement(Slur* p){registered[count++]=p;}
};
namespace Factory{Slur* createSlur(Score* s){return &s->pool[s->allocated++];}}
struct SlurDesc{
    Slur* pointer=nullptr;int state=0;
    bool isStart()const{return state==1;}bool isStop()const{return state==2;}
    Slur* slur()const{return pointer;}
    void start(Slur* p){pointer=p;state=1;}void stop(Slur* p){pointer=p;state=2;}
};
struct SlurStack{SlurDesc items[16];SlurDesc& operator[](int n){return items[n];}};

// ACTUAL_IMPORTER_FUNCTION

struct Case{
    Score score;ChordRest begin{&score,4,false},end{&score,0,false};
    SlurStack slurs;MxmlLogger logger;QXmlStreamReader reader;
    void reverse(const char* line="",const char* placement=""){
        addSlur({"stop"},slurs,&end,1440,&logger,&reader);
        addSlur({"start",line,placement},slurs,&begin,480,&logger,&reader);
    }
    void forward(){
        addSlur({"start"},slurs,&begin,480,&logger,&reader);
        addSlur({"stop"},slurs,&end,1440,&logger,&reader);
    }
};
int failures=0;
void check(bool ok,const char* name){if(!ok){puts(name);failures++;}}
int main(){
    {Case c;c.forward();check(c.score.count==1&&c.score.pool[0].startTick==480&&c.score.pool[0].tick2().value==1440,"ordinary forward");}
    {Case c;c.reverse();check(c.score.count==1&&c.score.registered[0]==&c.score.pool[0],"reverse registration");}
    {Case c;c.reverse();check(c.score.pool[0].startTick==480&&c.score.pool[0].tick2().value==1440,"reverse absolute stop");}
    {Case c;c.reverse();check(c.score.pool[0].startTrack==4&&c.score.pool[0].endTrack==0,"reverse tracks");}
    {Case c;c.reverse("dashed","above");check(c.score.pool[0].style==SlurStyleType::Dashed&&c.score.pool[0].direction==DirectionV::UP,"reverse dashed above");}
    {Case c;c.reverse("dotted","below");check(c.score.pool[0].style==SlurStyleType::Dotted&&c.score.pool[0].direction==DirectionV::DOWN,"reverse dotted below");}
    {Case c;c.begin.grace=true;c.reverse();check(c.score.pool[0].anchor==Spanner::Anchor::CHORD,"reverse start grace anchor");}
    {Case c;c.end.grace=true;c.reverse();check(c.score.pool[0].anchor==Spanner::Anchor::CHORD,"reverse end grace anchor");}
    {Case c;c.reverse();c.forward();check(c.score.count==2&&c.score.allocated==2&&!c.slurs[0].isStart()&&!c.slurs[0].isStop(),"reuse completed reverse number");}
    {Case c;addSlur({"start"},c.slurs,&c.begin,480,&c.logger,&c.reader);addSlur({"start"},c.slurs,&c.begin,480,&c.logger,&c.reader);check(c.score.count==1&&c.score.allocated==1&&c.logger.errors==1,"duplicate start stays rejected");}
    puts(failures?"REVERSE_SLUR_CONTROLS_FAILED":"PASS_TEN_REVERSE_SLUR_STATE_CONTROLS");return failures?1:0;
}
