#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    // this is based in Golan Levin's example for Processing
    cam.initGrabber(640, 480);
    
    thisFrame.allocate(640, 480, OF_IMAGE_COLOR);  //color
    lastFrame.allocate(640, 480, OF_IMAGE_COLOR);
    diffImage.allocate(640,480, OF_IMAGE_COLOR);

    ofSetFrameRate(60);
    ofSetVerticalSync(TRUE);
    ofEnableAlphaBlending();
    ofBackground(255);
    
    branch.loadImage("Branch.png");
    branchback.loadImage("Branchback.png");
    sunNY.loadImage("sunNY.png");
    sunSH.loadImage("sunSH.png");
    font.loadFont("Bitter-Regular.ttf",20);
    
    //To help the sun rotate
    time = 0;
    
    //To set the first radius of the sun
    sunRadiusNY=200;
    sunRadiusSH=200;
    
    lightSH = 0;
    lightNY = 0;
    
}

//--------------------------------------------------------------
void testApp::update(){
    //camera
    cam.update();
    
    bIsFrameNew = cam.isFrameNew();
    
    if (bIsFrameNew) {
        thisFrame.setFromPixels(cam.getPixels(), 640, 480, OF_IMAGE_COLOR);
        
        movementSum = 0;
        
        for (int i = 0; i < 480; i++) {
            for (int j = 0; j < 640; j++) {
                
                ofColor currColor = thisFrame.getColor(j,i);
                ofColor prevColor = lastFrame.getColor(j,i);
                
                //extract rgb components from current pixel
                int currR = currColor.r;
                int currG = currColor.g;
                int currB = currColor.b;
                
                //extract rgb components from previous pixel
                
                int prevR = prevColor.r;
                int prevG = prevColor.g;
                int prevB = prevColor.b;
                
                //compute difference
                int diffR = abs(currR - prevR);   //abs means positive number
                int diffG = abs(currG - prevG);
                int diffB = abs(currB - prevB);
                
                //add these difference to the running tally
                movementSum += diffR + diffG +diffB;
                
                //render the difference image to the screen
                ofColor diff = ofColor(diffR, diffG,diffB);
                diffImage.setColor(j, i, diff);
                
                //save current frame to previous frame
                lastFrame.setColor(j,i,currColor);
                
            }
        }
    }

    //camera as light
    if(movementSum > 5000000){
        lightSH = movementSum;
        lightNY = movementSum;

        }else{
        lightSH = 0;
        lightNY = 0;
    }

    //To get the different time from Shanghai and New York
    timeSH = (ofGetUnixTime()+28800)%86400; //to change it to Shanghai Time
    timeNY = (ofGetUnixTime()-18000)%86400;
    
    //To let the leaf class update and if the leaf die out, it will be erased
    for (int i = 0; i<leafSH.size(); i++) {
        leafSH[i].updateMe();
        if (leafSH[i].color.a <1) {
            leafSH.erase(leafSH.begin()+i);
        }
    }
    
    for (int i = 0; i<leafNY.size(); i++) {
        leafNY[i].updateMe();
        if (leafNY[i].color.a <1) {
            leafNY.erase(leafNY.begin()+i);
        }
    }
    
    
    //To let the leaf grow
    if( lightSH%300 > 5){   //here change the speed of the leaves growth
        //r = ofRandom(0,300);
        float a = ofRandom(0,300);
        float b = ofRandom(0,340);
        LeafSH l;
        angleSH = ofRandom(360);
        float x = a*cos(angleSH)+0.5*ofGetWidth();
        float y = b*sin(angleSH)+0.5*ofGetHeight();
        l.initialize(x, y);
        leafSH.push_back(l);
        }
    

        if(lightNY%200 > 5){
        //r = ofRandom(0,300);
        float a = ofRandom(0,260);
        float b = ofRandom(0,300);
        LeafNY l;
        angleNY = ofRandom(360);
        float x = a*cos(angleNY)+0.5*ofGetWidth();
        float y = b*sin(angleNY)+0.5*ofGetHeight();
        l.initialize(x, y);
        leafNY.push_back(l);
        }
    
    //To help the sun rotate
    time = time +1;
    
    //To help the sun change its radius according to the current light smoothly
    sunSHPrev = sunRadiusSH;
    sunNYPrev = sunRadiusNY;
    
//    sunRadiusSH = ofMap(line1, 300, 1000, 100, 200);
//    sunRadiusNY = ofMap(line2, 300, 1000, 100, 200);
    sunRadiusSH = 200;
    sunRadiusNY = 200;
    
}
//--------------------------------------------------------------
void testApp::draw(){
    //To draw some of the branches behind the leaves
    branchback.draw(0,0, ofGetWidth(), ofGetHeight());
    
    //To draw the sun according to time
    timepercentSH = timeSH/86400;
    timepercentNY = timeNY/86400;
    sunSHx = 100;
    sunSHy = ofGetHeight()*timeSH/86400;
    sunNYx = ofGetWidth()-100;
    sunNYy = ofGetHeight()*timeNY/86400;
 
    //To draw the rotating sun
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(sunSHx,sunSHy);
    ofRotate(time);
    sunSH.draw(0, 0, sunSHPrev+0.5*(sunRadiusSH-sunSHPrev), sunSHPrev+0.5*(sunRadiusSH-sunSHPrev));
    ofPopMatrix();

    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(sunNYx,sunNYy);
    ofRotate(time);
    sunNY.draw(0, 0, sunNYPrev+0.5*(sunRadiusNY-sunNYPrev), sunNYPrev+0.5*(sunRadiusNY-sunNYPrev));
    ofPopMatrix();
    
    //To show the time of Shanghai and New York
    hourSH = timeSH/3600;
    minuteSH = (timeSH%3600)/60;
    secondSH = (timeSH%3600)%60;
    hourNY = timeNY/3600;
    minuteNY = (timeNY%3600)/60;
    secondNY = (timeNY%3600)%60;
    
    //To write the time
    color.setHsb(151.7,204,97);
    ofSetColor(color);
    font.drawString("SH time "+ofToString(hourSH)+":"+ofToString(minuteSH)+":"+ofToString(secondSH), 30,ofGetHeight()-20);
    font.drawString("NY time "+ofToString(hourNY)+":"+ofToString(minuteSH)+":"+ofToString(secondSH), ofGetWidth()-270,ofGetHeight()-20);
    font.drawString("SH light "+ofToString(lightSH), 30,40);
    font.drawString("NY light "+ofToString(lightNY), ofGetWidth()-215,40);
    
    //To draw the leaves
    for (int i = 0; i<leafSH.size(); i++) {
        leafSH[i].drawMe();
       }
    
    for (int i = 0; i<leafNY.size(); i++) {
        leafNY[i].drawMe();
    }
    
    //To draw the brunch infront of the leaves
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255);
    branch.draw(0,0,ofGetWidth(),ofGetHeight());
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
