#include "ofApp.h"

//  TODO:  PROCESS OSC MESSAGES IN A ofEvent call?
//  TODO:  ADD SECOND VIDEO/ANIMATION/SOUNDS FOR OFF STATE
//--------------------------------------------------------------

void ofApp::setup() {
  ofSetWindowShape(1920, 1080);
  ofSetVerticalSync(false);
  ofSetWindowTitle("Receiver");

  syncReceiver.setupOSC();
  syncReceiver.setup();
  syncReceiver.play();
  syncReceiver.unmute();
  ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update() {
  // allow ctrl-c to quit the app!
  signal(SIGINT, ofExit);

  // update and sync video
  syncReceiver.update();
  syncReceiver.sync();
}

//--------------------------------------------------------------
void ofApp::draw() {
  syncReceiver.draw();
  syncReceiver.drawTime();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  // ofLog(OF_LOG_NOTICE, "%c key pressed", key);
  switch (key) {
  case OF_KEY_LEFT:
    // syncedvideo.player.previousFrame();
    break;
  case OF_KEY_RIGHT:
    // syncedvideo.player.nextFrame();
    break;
  case 'm':
    isMuted = !isMuted;
    if (isMuted)
      syncReceiver.mute();
    else
      syncReceiver.unmute();
    break;
  case 32:
    togglePause = !togglePause;
    if (togglePause)
      syncReceiver.pause();
    else
      syncReceiver.play();
    break;
  case 102:
    // user pressed "f"
    isFullScreen = !isFullScreen;
    ofSetFullscreen(isFullScreen);
    break;
  }
}

void ofApp::exit() { syncReceiver.close(); }
