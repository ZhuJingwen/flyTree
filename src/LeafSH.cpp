//
//  LeafSH.cpp
//  flyTree
//
//  Created by 朱静文 on 13-11-4.
//
//

#include "LeafSH.h"
// ----------------------------------
void LeafSH::initialize(float x, float y)
{
    radius = ofRandom(15,30);
    
    born = ofGetElapsedTimef();
    pos.set(x,y);
    color.setHsb(ofRandom(226,241),255,255);
    energy = 0;
}

// ----------------------------------
void LeafSH::updateMe()
{
    //To let the leaf die out with time
    float age = ofGetElapsedTimef() - born;
    color.a = ofMap(age,0,10,200,0);  //here change the speed of death
    //To let the leaf born with a speed
    energy = 0.9f * energy + 0.1f * 1.0f;
    
}

// ----------------------------------
void LeafSH::drawMe()
{
    //To draw the square leaves
    ofSetColor(color);
//    float angle = ofMap(radius, 20, 40, 0, 360);
//    //To let the leaves have rotation
//    ofSetRectMode(OF_RECTMODE_CENTER);
//    ofPushMatrix();
//    ofTranslate(pos.x,pos.y);
//    ofRotate(angle);
//    ofRect(0,0, radius*energy, radius*energy);
//    ofPopMatrix();
    ofCircle(pos.x,pos.y, radius*energy);
}
