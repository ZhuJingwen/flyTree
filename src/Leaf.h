//
//  Leaf.h
//  Forest
//
//  Created by 朱静文 on 13-10-29.
//
//

#ifndef Forest_Leaf_h
#define Forest_Leaf_h

#include "ofMain.h"
class Leaf
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
#endif
