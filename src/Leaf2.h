//
//  Leaf2.h
//  flyTree
//
//  Created by 朱静文 on 13-11-4.
//
//

#ifndef __flyTree__Leaf2__
#define __flyTree__Leaf2__

#include "ofMain.h"


class Leaf2
{
public:
    
    void initialize(float x, float y);
    void updateMe();
    void drawMe();
    
    ofPoint pos;
    ofColor color;
    float radius;
    float born;
    float energy;
    
};

#endif /* defined(__flyTree__Leaf2__) */


