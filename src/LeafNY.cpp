//
//  LeafNY.cpp
//  flyTree
//
//  Created by 朱静文 on 13-11-4.
//
//

#include "LeafNY.h"
// ----------------------------------
void LeafNY::initialize(float x, float y)
{
    radius = ofRandom(10,30);
    
    born = ofGetElapsedTimef();
    pos.set(x,y);
    color.setHsb(ofRandom(30,47),255,255);
    
    energy = 0;
}

// ----------------------------------
void LeafNY::updateMe()
{
    //To let the leaf die out with time
    float age = ofGetElapsedTimef() - born;
    color.a = ofMap(age,0,200,200,0);
    //To let the leaf born with a speed
    energy = 0.9f * energy + 0.1f * 1.0f;
    
}

// ----------------------------------
void LeafNY::drawMe()
{
    //To draw the square leaves
    ofSetColor(color);
    
    float angle = ofMap(radius, 10, 30, 0, 360);
    //To let the leaves have rotation
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(pos.x,pos.y);
    ofRotate(angle);
    //ofRect(0,0, radius*energy, radius*energy);
    ofTriangle(0, radius*energy, 0.866*radius*energy, -0.5*radius*energy, -0.866*radius*energy, -0.5*radius*energy);
    ofPopMatrix();
    
}
