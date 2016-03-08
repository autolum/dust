#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    nP = 512;
    
    float ivr = 3.0;
    float * pos = new float[nP*nP*4];
    for (int i = 0; i < nP*nP; ++i){
        pos[4*i + 0] = ofRandom(-ivr,ivr);
        pos[4*i + 1] = ofRandom(-ivr,ivr);
        pos[4*i + 2] = 0.0;//ofRandom(-ivr,ivr);
        pos[4*i + 3] = 0.0;//ofRandom(-ivr,ivr);
    }
    
    posPPB.allocate(nP,nP,GL_RGBA32F);
    posPPB.src->getTextureReference().loadData(pos, nP, nP, GL_RGBA);
    posPPB.dst->getTextureReference().loadData(pos, nP, nP, GL_RGBA);
    
    noiseTex.loadData(pos, nP, nP, GL_RGBA);
    
    dejong.load("shader/dejong.vert", "shader/dejong.frag");
    drawPos.load("shader/drawPos.vert", "shader/drawPos.frag");
    
    dustMesh.setMode(OF_PRIMITIVE_POINTS);
    for (int x = 0; x < nP; ++x){
    for (int y = 0; y < nP; ++y){
        dustMesh.addVertex(ofVec3f(x,y));
        dustMesh.addColor(ofColor(255,255,255,180));
    }}
    
    //dustVBO.setVertexData(dustMesh.getVerticesPointer(), nP*nP, GL_STATIC_DRAW);
    //dustVBO.setColorData(dustMesh.getColorsPointer(), nP*nP, GL_STATIC_DRAW);
    
    renderFBO.allocate(1024*2, 768*2);
    renderFBO.begin();
    ofClear(0);
    renderFBO.end();
    renderFBO.getTextureReference().setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST);
    ofBackground(0);
    
    gui.setup();
    gui.add(djA.setup( "AP 1", 1.4, -10, 10 ));
    gui.add(djB.setup( "AP 2", -2.3, -10, 10 ));
    gui.add(djC.setup( "AP 3", 2.4, -10, 10 ));
    gui.add(djD.setup( "AP 4", -2.1, -10, 10 ));
    gui.add(rotX.setup( "Rot X", 0, 0, 360 ));
    gui.add(rotY.setup( "Rot Y", 0, 0, 360 ));
    gui.add(scale.setup( "Scale", 1, 0, 10 ));
    gui.add(noise.setup( "Noise", 0, 0, 1 ));
    gui.add(alpha.setup( "Alpha", 0.2, 0, 1 ));
    gui.add(lumi.setup( "Luminace", 1, 0, 1 ));
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    posPPB.dst->begin();
    ofDisableAlphaBlending();
    ofDisableAntiAliasing();
    ofClear(0);
    dejong.begin();
    dejong.setUniformTexture("prevPos", posPPB.src->getTextureReference(), 0);
    dejong.setUniformTexture("noiseTex", noiseTex, 1);
    dejong.setUniform1f("a", djA + ofRandom(-0.001, 0.001));
    dejong.setUniform1f("b", djB + ofRandom(-0.001, 0.001));
    dejong.setUniform1f("c", djC + ofRandom(-0.001, 0.001));
    dejong.setUniform1f("d", djD + ofRandom(-0.001, 0.001));
    dejong.setUniform1f("noisemix", noise);
    posPPB.src->draw(0,0);
    dejong.end();
    posPPB.dst->end();
    
    renderFBO.begin();
    //ofClear(0);
    ofEnableAlphaBlending();
    //ofDisableAntiAliasing();
    ofFill();
    ofSetColor(0,100);
    ofRect(0, 0, 1024*2, 768*2);

    glPointSize(2);
    glEnable(GL_POINT_SMOOTH);
    //ofEnableBlendMode( OF_BLENDMODE_ADD );
    drawPos.begin();
    drawPos.setUniformTexture("posTex1", posPPB.src->getTextureReference(), 0);
    drawPos.setUniformTexture("posTex2", posPPB.dst->getTextureReference(), 1);
    drawPos.setUniform1f("alpha", alpha);
    drawPos.setUniform1f("lumi", lumi);
    
    ofPushMatrix();
    ofTranslate(1024, 768, 1024);
    ofScale(scale, scale, scale);
    ofRotateX(rotX);
    ofRotateY(rotY);
    dustMesh.draw();
    ofPopMatrix();
    drawPos.end();
    //ofDisableBlendMode();
    renderFBO.end();
    
    posPPB.swap();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofBackground(0);
    //ofEnableAntiAliasing();
    //ofEnableSmoothing();
    //glPointSize(2);
    ofDisableAlphaBlending();
    ofSetColor(255);
    
    //posPPB.dst->draw(1024-200,768-410, 200, 200);

    
    renderFBO.draw(0,0,1024,768);

    posPPB.src->draw(1024-200,768-200, 200, 200);
    
    gui.draw();
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 750);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    posPPB.swap();

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}