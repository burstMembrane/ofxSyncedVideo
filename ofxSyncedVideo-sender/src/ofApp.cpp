#include "ofApp.h"

//  TODO:  PROCESS OSC MESSAGES IN A ofEvent call?
//  TODO:  ADD SECOND VIDEO/ANIMATION/SOUNDS FOR OFF STATE
//--------------------------------------------------------------

void ofApp::setup() {

  ofSetWindowTitle("Sender:");
  ofSetWindowShape(1920, 1080);
  ofSetVerticalSync(false);
  syncSender.setupOSC();
  syncSender.setup();
  syncSender.play();
  syncSender.unmute();
  ofBackground(0);
  motionClient.setup(9999);
  ofLogNotice("ofApp::setup") << "Setup OSC Client on port 9999";
}

//--------------------------------------------------------------
void ofApp::update() {
  // allow ctrl-c to quit the app!
  signal(SIGINT, ofExit);

  while (motionClient.hasWaitingMessages()) {
    ofxOscMessage m;
    motionClient.getNextMessage(m);
    if (m.getAddress() == "/zigbee2osc/human_body_sensor/occupancy") {
      bool occupancy = m.getArgAsBool(0);
      syncSender.drawMovie = !occupancy;
      syncSender.setMute(occupancy);
      syncSender.player.setPaused(occupancy);
      syncSender.sendMessage("/draw", !occupancy);
      syncSender.sendMessage("/mute", occupancy);
      syncSender.sendMessage("/isPlaying", !occupancy);
      ofLogNotice("Sending /draw and /mute") << occupancy;
    }

    break;
  }

  // update and sync video
  syncSender.update();
  syncSender.sync();
}

//--------------------------------------------------------------
void ofApp::draw() {
  syncSender.draw();
  syncSender.drawTime();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  // ofLog(OF_LOG_NOTICE, "%c key pressed", key);
  switch (key) {

  case 'm':
    isMuted = !isMuted;
    if (isMuted)
      syncSender.mute();
    else
      syncSender.unmute();
    break;
  case 'r':
    syncSender.restart();
    break;
  case 32:
    togglePause = !togglePause;
    if (togglePause)
      syncSender.pause();
    else
      syncSender.play();
    break;
  case 102:
    // user pressed "f"
    isFullScreen = !isFullScreen;
    ofSetFullscreen(isFullScreen);
    break;
  }
}

void ofApp::exit() { syncSender.close(); }
