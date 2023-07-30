#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.add(uiLearn.setup("learn"));
    gui.add(uiClearCircles.setup("clear circles"));
    gui.add(uiClearContourEdge.setup("clear contour"));
    gui.add(uiThreshold.setup("threshold", 50, 0, 100));

    grabber.setup(640, 480);
    
    color.allocate(grabber.getWidth(), grabber.getHeight());
    grayscale.allocate(grabber.getWidth(), grabber.getHeight());
    background.allocate(grabber.getWidth(), grabber.getHeight());
    difference.allocate(grabber.getWidth(), grabber.getHeight());

    box2d.init();
    box2d.setGravity(0, 30);
    box2d.createGround();
    box2d.registerGrabbing();
    box2d.createBounds(ofRectangle(0, 0, grabber.getWidth(), grabber.getHeight()));
    
    ofSetBackgroundColor(0);
    
    // set up right triangle shape
    rightTriangle.begin();
    rightTriangle.addVertex(0, 0);
    rightTriangle.addVertex(64, 0);
    rightTriangle.addVertex(64, 64);
    rightTriangle.end();
    
    // set up heart shape
    heart.begin();
    heart.addVertex(0, 0);
    heart.addVertex(0, 48);
    heart.addVertex(24, 64);
    heart.addVertex(32, 32);
    heart.addVertex(64, 24);
    heart.addVertex(48, 0);
    heart.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    box2d.update();
    grabber.update();

    if(grabber.isFrameNew()){
        color.setFromPixels(grabber.getPixels());
        grayscale = color;
        difference.absDiff(background, grayscale);
        difference.threshold(uiThreshold);

        int minimum = difference.getWidth() * difference.getHeight() * 0.05;
        int maximum = difference.getWidth() * difference.getHeight() * 0.8;
        contour.findContours(difference, minimum, maximum, 1, false);
    }

    if(uiLearn){
        background = color;
    }

    if(uiClearCircles){
        circles.clear();
    }

    if(uiClearContourEdge){
        contourEdge->clear();
        background = color;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    color.draw(0, 0);
    if(!contour.blobs.empty()){
        createContourEdge(ofPolyline(contour.blobs.at(0).pts));
        contourEdge->draw();
    }

    ofSetColor(255, 219, 100);
    for(auto rect:rectangles){
        rect->draw();
    }
    
    ofSetColor(5, 173, 0);
    for(auto circle:circles){
        circle->draw();
    }
    
    ofSetColor(70, 72, 255);
    for(auto triangle:triangles){
        triangle->draw();
    }
    
    ofSetColor(255, 50, 85);
    for(auto heart:hearts){
        heart->draw();
    }
}

void ofApp::createContourEdge(ofPolyline polyline){
    delete contourEdge;
    contourEdge = new ofxBox2dEdge();
    contourEdge->addVertexes(polyline);
    contourEdge->create(box2d.getWorld());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'w'){
        auto circle = make_shared<ofxBox2dCircle>();
        circle->setPhysics(3.0, 0.5, 1.0);
        circle->setup(box2d.getWorld(), mouseX, mouseY, 32);
        circles.push_back(circle);
    }
    if (key == 'a'){
        auto rect = make_shared<ofxBox2dRect>();
        rect->setPhysics(3.0, 0.5, 1.0);
        rect->setup(box2d.getWorld(), mouseX, mouseY, 64, 64);
        rectangles.push_back(rect);
    }
    if (key == 's'){
        auto heart_shape = make_shared<ofxBox2dPolygon>();
        heart_shape->addVertices(heart.getVertices());
        heart_shape->setPhysics(3.0, 0.5, 1.0);
        heart_shape->create(box2d.getWorld());
        hearts.push_back(heart_shape);
    }
    if (key == 'd'){
        auto triangle = make_shared<ofxBox2dPolygon>();
        triangle->addVertices(rightTriangle.getVertices());
        triangle->setPhysics(3.0, 0.5, 1.0);
        triangle->create(box2d.getWorld());
        triangles.push_back(triangle);
        
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

