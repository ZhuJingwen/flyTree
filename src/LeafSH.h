//
//  LeafSH.h
//  flyTree
//
//  Created by 朱静文 on 13-11-4.
//
//

#ifndef __flyTree__LeafSH__
#define __flyTree__LeafSH__

#include <iostream>
#include "ofMain.h"

class LeafSH
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

#endif /* defined(__flyTree__LeafSH__) */
