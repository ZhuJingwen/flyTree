#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
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
    sunRadiusNY=300;
    sunRadiusSH=300;
    
//To get in the light data from spacebrew
    lightSH = 0;
    lightNY = 0;
    string host = "sandbox.spacebrew.cc"; // change to localhost to test Spacebrew local server
    //string host = Spacebrew::SPACEBREW_CLOUD;
    string name = "Solar Input";
    string description = "It's an input!";
    spacebrew.addSubscribe("line1", "range" );
    spacebrew.addSubscribe("line2", "range" );
    spacebrew.connect( host, name, description );
    Spacebrew::addListener(this, spacebrew);

}

//--------------------------------------------------------------
void testApp::update(){
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
    
    //To get the collected light data
    lightSH = lightSH + line1;
    lightNY = lightNY + line2;
 
    //To let the leaf grow when light colleted
    if ( line1 > 650) {
        if( lightSH%300 > 295){
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
    }
    
    if (line2 > 650) {
        if(lightNY%300 > 295){
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
    }
    
    //To help the sun rotate
    time = time +1;
    
    //To help the sun change its radius according to the current light smoothly
    sunSHPrev = sunRadiusSH;
    sunNYPrev = sunRadiusNY;
    sunRadiusSH = ofMap(line1, 300, 1000, 100, 200);
    sunRadiusNY = ofMap(line2, 300, 1000, 100, 200);
    

}
//---------------------------
void testApp::onMessage( Spacebrew::Message & msg ){
    if ( msg.name == "line1"){
        line1 = msg.valueRange();
    }else if ( msg.name == "line2"){
        line2 = msg.valueRange();
    }
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
    font.drawString("SH light "+ofToString(line1), 30,40);
    font.drawString("NY light "+ofToString(line2), ofGetWidth()-215,40);
    
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
