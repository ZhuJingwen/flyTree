//
//  Leaf.cpp
//  Forest
//
//  Created by 朱静文 on 13-10-29.
//
//

#include "Leaf.h"
// ----------------------------------
void Leaf::initialize(float x, float y)
{
    radius = ofRandom(20,40);
    
    born = ofGetElapsedTimef();
    pos.set(x,y);
    color.setHsb(ofRandom(255),200,200);
}

// ----------------------------------
void Leaf::updateMe()
{
    //To let the leaf die out with time
    float age = ofGetElapsedTimef() - born;
    color.a = ofMap(age,0,300,255,0);
    //To let the leaf born with a speed
    energy = 0.9f * energy + 0.1f * 1.0f;
 
}

// ----------------------------------
void Leaf::drawMe()
{
    //To draw the square leaves
    ofSetColor(color);
    float angle = ofMap(radius, 20, 40, 0, 360);
    //To let the leaves have rotation
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(pos.x,pos.y);
    ofRotate(angle);
    ofRect(0,0, radius*energy, radius*energy);
    ofPopMatrix();
    
}