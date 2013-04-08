#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    //  Gears
    //
    RMIN = 30;
    RMAX = 200;
    
    picked = new GuiGear();
    picked->set(ofGetScreenWidth()*0.07, ofGetScreenHeight()*0.89);
    picked->setRadius(50);
    picked->update();
    picked->type = "Job";
    gears.push_back(picked);
    picked = new GuiGear();
    
    you.set(ofGetScreenWidth()*0.95, ofGetScreenHeight()*0.07);
    you.setRadius(40);
    you.update();
    you.bSelected = false;
    you.type = "You";
    
    hoverGear = -1;

    bValid = false;
    bPrintToPdf = false;
    
    //  GUI
    //
    sTitle = "GEAR UP!";
    sSubTitle = "You are an immigrant trying to find a highly-skilled job in America.";
    sAnswer = "( Press a key to start )";
    
    fontBig.loadFont("tusj.ttf" , 30);
    fontSmall.loadFont("tusj.ttf", 14);
    
    nLevel  = 0;
    speed = 0.5;
    speedFactor = 1.0;
    ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (nLevel > 0){
        picked->set(mouseX,mouseY);
        bValid = setPosition( picked );
        
         // Hover hability
         //
        hoverGear = -1;
        ofPoint mouse = ofPoint(mouseX,mouseY);
        for (int i = 0; i < gears.size(); i++) {
            if ( gears[i]->inside(mouse) ){
                hoverGear = i;
                break;
            }
        }
        
        if (bValid){
            float radDiff = RMAX - RMIN;
            
            if ( nLevel == 1){
                sTitle = "VISA SITUATION";
                sSubTitle = "Who is your visa sponsor?";
                /*
                 I don't have a visa.                           0.0
                 I'm here for a job.                            2.0
                 I'm here with family / spouse.                 1.0
                 I have a green card.                           2.0
                 */
            
                float radStep = radDiff/4.0;
                
                if ( picked->getRadius() < RMIN+radStep ){
                    sAnswer = "- I don't have a visa -";
                    speedFactor = 0.0;
                } else if ( picked->getRadius() < RMIN+radStep*2.0 ){
                    sAnswer = "- I'm here with family / spouse -";
                    speedFactor = 1.0;
                } else if ( picked->getRadius() < RMIN+radStep*3.0 ){
                    sAnswer = "- I'm here for a job -";
                    speedFactor = 2.0;
                } else {
                    sAnswer = "- I have a green card -";
                    speedFactor = 2.0;
                }
                
            } else if ( nLevel == 2){
                sTitle = "ENGLISH FLUENCY";
                sSubTitle = "How well can you speak English?";
                
                /*
                I can't speak English.                         0.0
                I know some English.                           0.5
                I'm fluent in English.                         2.0
                 */
                
                float radStep = radDiff/3.0;
                
                if ( picked->getRadius() < RMIN+radStep ){
                    sAnswer = "- I can't speak English -";
                    speedFactor = 0.0;
                } else if ( picked->getRadius() < RMIN+radStep*2.0 ){
                    sAnswer = "- I know some English -";
                    speedFactor = 0.5;
                } else {
                    sAnswer = "- I'm fluent in English -";
                    speedFactor = 2.0;
                }
                
            } else if ( nLevel == 3){
                sTitle = "EDUCATION";
                sSubTitle = "What is your degree and where did you earn it?";
                
                /*
                I have a high school diploma / GED.            0.0
                I have an associate's degree.                  0.5
                I have a degree from a foreign university.     1.0
                I have a degree from an American university.	3.0
                 */
                
                float radStep = radDiff/4.0;
                
                if ( picked->getRadius() < RMIN+radStep ){
                    sAnswer = "- I have a high school diploma / GED -";
                    speedFactor = 0.0;
                } else if ( picked->getRadius() < RMIN+radStep*2.0 ){
                    sAnswer = "- I have an associate's degree -";
                    speedFactor = 0.5;
                } else if ( picked->getRadius() < RMIN+radStep*3.0 ){
                    sAnswer = "- I have a degree from a foreign university -";
                    speedFactor = 1.0;
                } else {
                    sAnswer = "- I have a degree from an American university -";
                    speedFactor = 3.0;
                }
                
            } else if ( nLevel == 4){
                sTitle = "ORIGIN";
                sSubTitle = "Where did you come from?";
                
                /*
                I'm from Europe or Asia.                       1.0
                I'm from Latin America.                        0.8
                I'm from Africa.                               0.5
                 */
                
                float radStep = radDiff/3.0;
                
                if ( picked->getRadius() < RMIN+radStep ){
                    sAnswer = "- I'm from Africa -";
                    speedFactor = 0.5;
                } else if ( picked->getRadius() < RMIN+radStep*2.0 ){
                    sAnswer = "- I'm from Latin America -";
                    speedFactor = 0.8;
                } else {
                    sAnswer = "- I'm from Europe or Asia -";
                    speedFactor = 1.0;
                }
                
            } else if ( nLevel == 5){
                sTitle = "RECENCY";
                sSubTitle = "Have you worked here before?";
                
                /*
                I've been working here already.                1.0
                I just got here!                               0.5
                 */
                
                float radStep = radDiff/2.0;
                
                if ( picked->getRadius() < RMIN+radStep ){
                    sAnswer = "- I just got here! -";
                    speedFactor = 0.5;
                } else {
                    sAnswer = "- I'm from Latin America -";
                    speedFactor = 1.0;
                }
            } else {
                sTitle = "You do NOT got the job";
                sSubTitle = "";
                sAnswer = "";
                speedFactor = 1.0;
            }
            
            picked->type = sAnswer;
            picked->getData()->speed = speed * speedFactor;
            
        } else {
            sAnswer = "";
            speedFactor = 1.0;
            picked->type = sAnswer;
            picked->getData()->speed = speed ;
        }
    }
    
    for(int i = gears.size()-1; i > 0; i--){
        if ( you.touching( gears[i] ) ){
            if ( speed > 0.0 ) {
                you.setData( gears[i]->getData() );
                setPosition( &you );
                you.update();
                sTitle = "YOU GOT THE JOB!";
            } else {
                sTitle = "You could got the job but is imposible";
            }
            
            sSubTitle = "";
            sAnswer = "";
            
            break;
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    //  Background
    //
    if (bPrintToPdf){
        ofBackground(255);
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
    } else {
        ofBackground(11,94,148);
        ofBackgroundGradient(ofColor(11,94,148), ofColor(0,45,128,100));
        float margin = 10;
        ofRectangle grid = ofRectangle(margin,margin,ofGetWidth()-margin*2.0,ofGetHeight()-margin*2.0);
        
        ofPushStyle();
        
        ofSetColor(200,20);
        ofSetLineWidth(2);
        ofNoFill();
        ofRect(grid);
        ofSetLineWidth(0.3);
        drawGrid(grid, 10);
        
        ofPopStyle();
    }
    
    //  Potentialy New Gear
    //
    if( bValid && !bPrintToPdf) {
        ofSetColor(255,0,0);
        picked->update();
        picked->draw();
    }
    
    //  Draw Gears
    //
    for (int i = 0; i < gears.size(); i++) {
        
        gears[i]->bPrint = bPrintToPdf;
        gears[i]->bSelected = (hoverGear == i);
        
        ofSetColor(255);
        gears[i]->update();
        gears[i]->draw();
        
    }
    
    //  Draw You
    //
    ofSetColor(255,50+abs(sin(ofGetElapsedTimef()))*200);
    you.draw();
    
    //  Text
    //
    ofSetColor(255);
    ofRectangle boundingBox = fontBig.getStringBoundingBox(sTitle, 0, 0);
    boundingBox.x = ofGetWidth()*0.5 - boundingBox.width*0.5;
    boundingBox.y = ofGetHeight()*0.15 - boundingBox.height*0.5;
    fontBig.drawString(sTitle, boundingBox.x, boundingBox.y);
    
    boundingBox = fontSmall.getStringBoundingBox(sSubTitle, 0, 0);
    boundingBox.x = ofGetWidth()*0.5 - boundingBox.width*0.5;
    boundingBox.y = ofGetHeight()*0.2 - boundingBox.height*0.5;
    fontSmall.drawString(sSubTitle, boundingBox.x, boundingBox.y );
    
    boundingBox = fontBig.getStringBoundingBox(sAnswer, 0, 0);
    boundingBox.x = ofGetWidth()*0.5 - boundingBox.width*0.5;
    boundingBox.y = ofGetHeight()*0.5 - boundingBox.height*0.5;
    fontBig.drawString(sAnswer, boundingBox.x, boundingBox.y );
    
    if (bPrintToPdf){
        ofEndSaveScreenAsPDF();
        bPrintToPdf = false;
    }
}

//--------------------------------------------------------------
bool testApp::setPosition(GuiGear *g1) {
    
    // We try to locate the gear as close as possible to (x, y)
    // while satisfying distance constraints towards the other gears.
    // Note: this process is implicitly iterative.
    //
//    GuiGear *g1 = p;
    
    // find the nearest gear
    //
    GuiGear *g2 = nearest(g1);
    
    // Primum Movens
    //
    if(g2 == NULL) {
        // and resize it softly
        //
        g1->setRadius( ofLerp(picked->getRadius(),RMIN, 0.1) );
        g1->linked = NULL;
        return false;
    }
    
    // calculate radius needed to touch g2 (using target coordinates)
    ofPoint diff = *g1 - *g2;
    float rtouch = diff.length() - g2->getRadius();
    
    // calculate maximum radius possible without touching any other gears.
    // We are using the actual gear coordinates so the center of the gear
    // can converge over the course of several iterations.
    //
    float rmax = maxRadiusBetween(g1, g2);
    
    // the new radius
    //
    float rnew = min(rtouch, min( rmax, RMAX));
    
    // is the new radius big enough for a new gear?
    //
    if (rnew >= RMIN) {
        g1->setRadius(rnew);
        
        // distance between the gear centers
        //
        float d = rnew + g2->getRadius();
        
        // angle between gear-axis and the x-axis
        //
        float ang = atan2(diff.y, diff.x);
        
        // align the angular rotation
        //
        g1->angle = PI + ((ang - g2->angle) * g2->getRadius() + ang * g1->getRadius()) / g1->getRadius();
        
        // align direction of rotation
        //
        g1->spin = -g2->spin;
        
        // move the gear center to its new location
        //
        g1->x = g2->x + cos(ang) * d;
        g1->y = g2->y + sin(ang) * d;
        
        g1->linked = g2;
        
        return true;
    } else {
        return false;
    }
}

float testApp::maxRadiusBetween(GuiGear *_g1, GuiGear *_g2){
    float rmax = 1000000.0;
    for (int i = 0; i < gears.size(); i++) {
        if (gears[i] == _g1 || gears[i] == _g2)
            continue;
        
        float d = _g1->distance( ofPoint(_g2->x,_g2->y) ) - _g2->getRadius() - _g1->getData()->hcog;
        rmax = min(rmax, d);
    }
    return rmax;
}

// find the gear that is closest to the point (x, y)
// or return null if there's no gear in the vicinity
GuiGear* testApp::nearest(ofPoint *p) {
    float dmax = RMAX;
    GuiGear *result = NULL;
    for (int i = 0; i < gears.size(); i++){
        if (gears[i] == picked)continue;
        
        float dist = gears[i]->distance( ofPoint(*p) ) - gears[i]->getRadius();
        if (dist < dmax) {
            result = gears[i];
            dmax = dist;
        }
    }
    return result;
}

void testApp::drawGrid(ofRectangle _rect, float _res){
    for (float x = 0 ; x < _rect.width; x += _res ){
        ofLine(_rect.x + x, _rect.y, _rect.x + x, _rect.y + _rect.height);
    }
    
    for (float y = 0 ; y < _rect.height; y += _res ){
        ofLine(_rect.x , _rect.y + y, _rect.x + _rect.width, _rect.y + y);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (nLevel < 1){
        nLevel++;
    } else {
    
        if (hoverGear >= 0){
            if (key == OF_KEY_RIGHT){
                gears[hoverGear]->getData()->speed += 0.1;
            } else if (key == OF_KEY_LEFT){
                gears[hoverGear]->getData()->speed -= 0.1;
            }
        }
        
        if (key == 'p'){
            bPrintToPdf = true;
        } else if ( key == 'f'){
            ofToggleFullscreen();
        } else if ( key == OF_KEY_RETURN ){
            while (gears.size() != 1) {
                gears.pop_back();
            }
            sTitle = "GEAR UP!";
            sSubTitle = "You are an immigrant trying to find a highly-skilled job in America.";
            sAnswer = "( Press a key to start )";
            nLevel = 0;
        }
    
    }
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
    if (nLevel < 1){
        nLevel++;
        return;
    }
    
    if (bValid && (nLevel<6)){
        gears.push_back(picked);
        picked = new GuiGear();
        speed = speed * speedFactor;
        nLevel++;
    }
    
    
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