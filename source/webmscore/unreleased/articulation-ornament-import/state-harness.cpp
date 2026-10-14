// Copyright 2026 Luckolite
// SPDX-License-Identifier: GPL-3.0-only
// Minimal framework substitutes; the importer functions are extracted unchanged.
#include <string>
#include <map>
#include <memory>
#include <iostream>
class QString {
    std::string v; bool null=true;
public:
    QString()=default;
    QString(const char* s):v(s?s:""),null(s==nullptr){}
    bool isNull()const{return null;}
    bool isEmpty()const{return v.empty();}
    bool operator==(const char* s)const{return v==s;}
    bool operator<(const QString& s)const{return v<s.v;}
};
template<class K,class V>class QMap {
    std::map<K,V> m;
public:V& operator[](const K& k){return m[k];}
    bool contains(const K& k)const{return m.find(k)!=m.end();}
    V value(const K& k)const{return m.at(k);}
};
// SYMBOL_ENUM
enum class Pid { DIRECTION,ARTICULATION_ANCHOR };
enum class PropertyFlags { STYLED,UNSTYLED };
enum class ArticulationAnchor { TOP_STAFF,BOTTOM_STAFF,CHORD };
struct EngravingObject {
    std::map<Pid,PropertyFlags> flags;
    void setPropertyFlags(Pid p,PropertyFlags f){flags[p]=f;}
    PropertyFlags propertyFlags(Pid p){return flags[p];}
};
struct Articulation:EngravingObject {
    SymId sym=SymId::noSym; bool up=true;
    ArticulationAnchor anchor=ArticulationAnchor::CHORD;
    void setSymId(SymId s){sym=s;}
    void setUp(bool v){up=v;}
    void setAnchor(ArticulationAnchor a){anchor=a;}
};
struct Notation {
    std::map<std::string,QString> attrs;
    SymId sym=SymId::articAccentAbove;
    SymId symId()const{return sym;}
    QString attribute(const char* name)const{auto i=attrs.find(name);return i==attrs.end()?QString():i->second;}
};
struct ChordRest {std::unique_ptr<Articulation> articulation;void add(Articulation* a){articulation.reset(a);}};
struct Factory {static Articulation* createArticulation(ChordRest*){return new Articulation;}};
// ACTUAL_PROPERTY_FUNCTION
// ACTUAL_ARTICULATION_FUNCTION
// ACTUAL_SYMBOL_FUNCTION
int failures=0,total=0;
void check(bool pass,const char* name){total++;if(!pass){failures++;std::cout<<"FAIL "<<name<<"\n";}}
void resetStyle(Articulation& a){if(a.propertyFlags(Pid::ARTICULATION_ANCHOR)==PropertyFlags::STYLED)a.anchor=ArticulationAnchor::CHORD;}
int main(){
    auto run=[](const char* placement,const char* type){Notation n;if(placement)n.attrs["placement"]=QString(placement);if(type)n.attrs["type"]=QString(type);ChordRest c;addArticulationToChord(n,&c);return std::move(c.articulation);};
    auto below=run("below",nullptr);check(below->anchor==ArticulationAnchor::BOTTOM_STAFF,"below without direction");
    check(below->propertyFlags(Pid::DIRECTION)==PropertyFlags::STYLED,"implicit direction remains styled");
    resetStyle(*below);check(below->anchor==ArticulationAnchor::BOTTOM_STAFF,"below survives style reload");
    auto belowUp=run("below","up");check(belowUp->anchor==ArticulationAnchor::BOTTOM_STAFF&&belowUp->up,"placement independent of up glyph");
    auto aboveDown=run("above","down");check(aboveDown->anchor==ArticulationAnchor::TOP_STAFF&&!aboveDown->up,"placement independent of down glyph");
    resetStyle(*aboveDown);check(aboveDown->anchor==ArticulationAnchor::TOP_STAFF,"above survives style reload");
    auto empty=run("below","");check(empty->anchor==ArticulationAnchor::BOTTOM_STAFF,"empty direction cannot shadow below");
    auto down=run(nullptr,"down");check(down->anchor==ArticulationAnchor::BOTTOM_STAFF,"legacy down fallback");
    resetStyle(*down);check(down->anchor==ArticulationAnchor::CHORD,"orientation-only import still follows style");
    auto belowDown=run("below","down");resetStyle(*belowDown);check(belowDown->anchor==ArticulationAnchor::BOTTOM_STAFF,"explicit below and down survives style reload");
    auto automatic=run(nullptr,nullptr);check(automatic->anchor==ArticulationAnchor::TOP_STAFF,"legacy implicit import default");
    resetStyle(*automatic);check(automatic->anchor==ArticulationAnchor::CHORD,"implicit placement still follows style");
    SymId id=SymId::noSym;check(convertArticulationToSymId(QString("delayed-inverted-turn"),id)&&id==SymId::ornamentTurnInverted,"delayed inverted turn shape");
    check(convertArticulationToSymId(QString("inverted-turn"),id)&&id==SymId::ornamentTurnInverted,"ordinary inverted turn preserved");
    check(convertArticulationToSymId(QString("turn"),id)&&id==SymId::ornamentTurn,"ordinary turn preserved");
    check(!convertArticulationToSymId(QString("unrecognized-ornament"),id),"unknown symbol not invented");
    std::cout<<total<<" controls, "<<failures<<" failures\n";return failures?1:0;
}
