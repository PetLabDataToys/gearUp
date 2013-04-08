#pragma once

#include "ofMain.h"
#include "GuiGear.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
	
    bool        setPosition(GuiGear *p);
    GuiGear*    nearest(ofPoint *p);
    float       maxRadiusBetween(GuiGear *_g1, GuiGear *_g2);
    void        drawGrid(ofRectangle _rect, float _res);
    
    GuiGear             you;
	vector<GuiGear*>    gears;
    GuiGear*            picked;
    
    ofTrueTypeFont      fontBig;
    ofTrueTypeFont      fontSmall;
    string              sTitle;
    string              sSubTitle;
    string              sAnswer;
    
    float               RMIN, RMAX;
    float               tweening;
    
    int                 hoverGear;
    int                 nLevel;
    
    float               speed;
    float               speedFactor;
    
    bool                bValid;
    bool                bPrintToPdf;
};
