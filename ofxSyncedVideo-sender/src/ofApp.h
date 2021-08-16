#pragma once

#include "ofMain.h"
#include "ofxSyncedVideoSender.h"

class ofApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();
  void exit();
  void keyPressed(int key);

  ofxSyncedVideoSender syncSender;

  bool togglePause = false;
  bool isMuted;
  ofxOscReceiver motionClient;
  bool isFullScreen;
};
