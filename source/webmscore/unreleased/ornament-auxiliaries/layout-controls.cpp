// Copyright 2026 Luckolite
// SPDX-License-Identifier: GPL-3.0-only
#include "ornamentauxlayout.h"
#include <cmath>
#include <iostream>
using namespace mu::engraving::ornament_aux;
int count=0,fail=0;
void check(bool pass,const char* name){count++;if(!pass){fail++;std::cout<<"FAIL "<<name<<"\n";}}
bool close(double a,double b){return std::abs(a-b)<1e-9;}
int main(){
    Box base{-2,-3,4,1},accidental{-.7,-2,.6,3.5};
    auto upper=place(base,accidental,true,.25),lower=place(base,accidental,false,.25);
    check(close(upper.bounds.y+upper.bounds.height,-3.25),"upper glyph clears base by exact gap");
    check(close(lower.bounds.y,-1.75),"lower glyph clears base by exact gap");
    check(close(upper.bounds.x+upper.bounds.width*.5,0),"upper centered by ink bounds");
    check(close(lower.bounds.x+lower.bounds.width*.5,0),"lower centered by ink bounds");
    check(close(upper.x,.4)&&close(lower.x,.4),"negative font bearings retained");
    check(close(upper.y,-4.75)&&close(lower.y,.25),"font ascender offset retained");
    for(double s:{.5,1.0,2.0}){
        Box b{base.x*s,base.y*s,base.width*s,base.height*s};
        Box a{accidental.x*s,accidental.y*s,accidental.width*s,accidental.height*s};
        auto p=place(b,a,true,.25*s);
        check(close(p.x,upper.x*s)&&close(p.y,upper.y*s),"uniform staff scaling");
        check(close(p.bounds.width,accidental.width*s)&&close(p.bounds.height,accidental.height*s),"glyph dimensions unchanged");
    }
    auto translated=place({base.x+50,base.y+40,base.width,base.height},accidental,true,.25);
    check(close(translated.bounds.x,upper.bounds.x+50)&&close(translated.bounds.y,upper.bounds.y+40),"base translation follows ornament");
    auto wide=place(base,{-2,-1,6,2},true,.25);
    check(close(wide.bounds.x,-3)&&close(wide.bounds.x+wide.bounds.width,3),"wide auxiliary has symmetric collision bounds");
    check(wide.bounds.y+wide.bounds.height<base.y,"wide auxiliary cannot overlap base vertically");
    check(close(scale,.65),"auxiliary uses explicit proportional font scale");
    std::cout<<count<<" controls, "<<fail<<" failures\n";return fail?1:0;
}
