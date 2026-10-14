// Copyright 2026 Luckolite
// SPDX-License-Identifier: GPL-3.0-only
// Explicit framework substitutes; parser/native helper bodies come from actual source.
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
struct QString {
    std::string value;
    QString()=default;QString(const char* s):value(s?s:""){}
    QString toString()const{return *this;}
    bool isEmpty()const{return value.empty();}
    int toInt()const{return std::atoi(value.c_str());}
    bool operator==(const char* s)const{return value==s;}
    bool operator!=(const char* s)const{return value!=s;}
    bool operator==(const QString& s)const{return value==s.value;}
    bool operator<(const QString& s)const{return value<s.value;}
};
using AsciiStringView=QString;
template<class K,class V>struct QMap {
    std::map<K,V> values;V& operator[](const K& k){return values[k];}
    bool contains(const K& k)const{return values.count(k);}
    V value(const K& k)const{return values.at(k);}
};
// SYMBOL_ENUM
// SYMBOL_NAMES
struct Attributes {
    std::map<QString,QString> data;
    QString value(const char* k)const{auto i=data.find(QString(k));return i==data.end()?QString():i->second;}
};
struct Notation {
    QString _name,_parent,_text;SymId _symId;std::map<QString,QString> _attributes;
    Notation(QString n,QString p="",SymId s=SymId::noSym):_name(n),_parent(p),_symId(s){}
    static Notation notationWithAttributes(QString n,Attributes a,QString p="",SymId s=SymId::noSym){Notation v(n,p,s);v._attributes=a.data;return v;}
    QString attribute(const QString& n)const{auto i=_attributes.find(n);return i==_attributes.end()?QString():i->second;}
    // ACTUAL_NOTATION_SETTER
    void setText(QString s){_text=s;}
};
struct Token {QString name;Attributes attrs;QString text;};
struct Reader {
    std::vector<Token> tokens;int index=-1;
    bool readNextStartElement(){return ++index<int(tokens.size());}
    QString name()const{return tokens.at(index).name;}
    Attributes attributes()const{return tokens.at(index).attrs;}
    QString readElementText(){return tokens.at(index).text;}
    void skipCurrentElement(){}
};
struct Logger {int errors=0;void logError(const char*,Reader*){errors++;}};
struct XmlReader {QString tag,value;QString name()const{return tag;}QString readAsciiText(){tag="advanced";return value;}};
struct XmlWriter {std::vector<std::pair<QString,QString>> tags;void tag(const char* n,QString v){tags.push_back({n,v});}};
struct SymNames {
    static QString nameForSymId(SymId s){return QString(symbolNames[int(s)]);}
    static SymId symIdByName(QString n){for(int i=0;i<int(sizeof(symbolNames)/sizeof(*symbolNames));i++)if(n==symbolNames[i])return SymId(i);return SymId::noSym;}
};
struct Articulation {
    SymId sym=SymId::ornamentTurn,_ornamentAuxAbove=SymId::noSym,_ornamentAuxBelow=SymId::noSym;
    bool isOrnament()const{return std::string(symbolNames[int(sym)]).rfind("ornament",0)==0;}
    void setOrnamentAuxiliary(SymId,bool);
    bool readOrnamentAuxiliary(XmlReader&);
    void writeOrnamentAuxiliaries(XmlWriter&)const;
};
// ACTUAL_NATIVE_MEMBERS
// ACTUAL_CONVERTER
// ACTUAL_AUX_SYMBOL
// ACTUAL_APPLY_AUX
struct MusicXMLParserNotations {
    Reader& _e;Logger* _logger;std::vector<Notation> _notations;
    QString _wavyLineType,_tremoloType;int _wavyLineNo=0,_tremoloNr=0;bool _wavyLineStop=false;
    MusicXMLParserNotations(Reader& e,Logger* l):_e(e),_logger(l){}
    void ornaments();void mordentNormalOrInverted();
    void skipLogCurrElem(){_logger->errors++;_e.skipCurrentElement();}
};
// ACTUAL_PARSER_MEMBERS
int total=0,fail=0;
void check(bool pass,const char* name){total++;if(!pass){fail++;std::cout<<"FAIL "<<name<<"\n";}}
Token token(const char* name,const char* text="",const char* placement=nullptr){Token t{name,{},text};if(placement)t.attrs.data["placement"]=placement;return t;}
std::vector<Notation> parse(std::vector<Token> tokens){Reader r{tokens};Logger l;MusicXMLParserNotations parser(r,&l);parser.ornaments();return parser._notations;}
Articulation bound(const Notation& n){Articulation a;if(n._symId!=SymId::noSym)a.sym=n._symId;applyOrnamentAuxiliaries(n,&a);return a;}
int main(){
    auto turn=parse({token("turn"),token("accidental-mark","flat","above"),token("accidental-mark","sharp","below")});auto t=bound(turn.at(0));
    check(t._ornamentAuxAbove==SymId::accidentalFlat&&t._ornamentAuxBelow==SymId::accidentalSharp,"turn retains both sides");
    auto trill=parse({token("trill-mark"),token("accidental-mark","natural")});
    check(bound(trill.at(0))._ornamentAuxAbove==SymId::accidentalNatural,"deferred trill retains natural");
    auto mordent=parse({token("mordent"),token("accidental-mark","flat","below")});
    check(bound(mordent.at(0))._ornamentAuxBelow==SymId::accidentalFlat,"separate mordent path retains accidental");
    auto pair=parse({token("turn"),token("accidental-mark","flat"),token("inverted-turn"),token("accidental-mark","sharp","below")});
    check(bound(pair.at(0))._ornamentAuxAbove==SymId::accidentalFlat&&bound(pair.at(0))._ornamentAuxBelow==SymId::noSym,"first ornament does not borrow lower mark");
    check(bound(pair.at(1))._ornamentAuxBelow==SymId::accidentalSharp&&bound(pair.at(1))._ornamentAuxAbove==SymId::noSym,"second ornament does not borrow upper mark");
    auto orphan=parse({token("accidental-mark","sharp"),token("turn")});check(bound(orphan.at(0))._ornamentAuxAbove==SymId::noSym,"orphan does not carry forward");
    auto tremolo=parse({token("turn"),token("tremolo","2"),token("accidental-mark","sharp")});check(bound(tremolo.at(0))._ornamentAuxAbove==SymId::noSym,"tremolo boundary clears owner");
    auto badSide=parse({token("turn"),token("accidental-mark","sharp","left")});check(bound(badSide.at(0))._ornamentAuxAbove==SymId::noSym,"unsupported side does not invent upper mark");
    auto badValue=parse({token("turn"),token("accidental-mark","quarter-sharp")});check(bound(badValue.at(0))._ornamentAuxAbove==SymId::noSym,"unsupported glyph not approximated");
    auto doubles=parse({token("turn"),token("accidental-mark","flat-flat"),token("accidental-mark","double-sharp","below")});check(bound(doubles.at(0))._ornamentAuxAbove==SymId::accidentalDoubleFlat&&bound(doubles.at(0))._ornamentAuxBelow==SymId::accidentalDoubleSharp,"double accidentals retain both sides");
    auto alias=parse({token("turn"),token("accidental-mark","sharp-sharp")});check(bound(alias.at(0))._ornamentAuxAbove==SymId::accidentalDoubleSharp,"standard double sharp alias retained");
    auto conflict=parse({token("turn"),token("accidental-mark","natural"),token("accidental-mark","sharp")});check(bound(conflict.at(0))._ornamentAuxAbove==SymId::noSym,"conflicting marks refused");
    auto repeated=parse({token("turn"),token("accidental-mark","sharp"),token("accidental-mark","sharp")});XmlWriter once;bound(repeated.at(0)).writeOrnamentAuxiliaries(once);check(once.tags.size()==1,"identical duplicate is one native glyph");
    auto deferred=parse({token("trill-mark"),token("turn"),token("accidental-mark","flat")});check(bound(deferred.at(0))._ornamentAuxAbove==SymId::accidentalFlat&&bound(deferred.at(1))._ornamentAuxAbove==SymId::noSym,"later turn does not contaminate deferred trill");
    Articulation saved;saved.setOrnamentAuxiliary(SymId::accidentalFlat,true);saved.setOrnamentAuxiliary(SymId::accidentalSharp,false);
    XmlWriter out;saved.writeOrnamentAuxiliaries(out);Articulation restored;
    for(auto tag:out.tags){XmlReader reader{tag.first,tag.second};check(restored.readOrnamentAuxiliary(reader),"actual native reader recognizes retained field");}
    check(restored._ornamentAuxAbove==SymId::accidentalFlat&&restored._ornamentAuxBelow==SymId::accidentalSharp,"native helper roundtrip retains both sides");
    Articulation clone=restored;clone.setOrnamentAuxiliary(SymId::accidentalNatural,true);check(restored._ornamentAuxAbove==SymId::accidentalFlat,"clone does not mutate source fields");
    XmlReader unrelated{"direction","up"};check(!clone.readOrnamentAuxiliary(unrelated),"native helper leaves unrelated tags alone");
    clone.setOrnamentAuxiliary(SymId::unrelatedGlyph,false);check(clone._ornamentAuxBelow==SymId::noSym,"native glyph whitelist rejects unrelated symbol");
    Articulation accent=restored;accent.sym=SymId::articAccentAbove;XmlWriter empty;accent.writeOrnamentAuxiliaries(empty);check(empty.tags.empty(),"non-ornament never writes inherited auxiliaries");
    // The Python checker validates expected baseline failures from this report.
    std::cout<<total<<" controls, "<<fail<<" failures\n";return 0;
}
