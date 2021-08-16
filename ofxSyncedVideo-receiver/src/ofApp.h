#pragma once

#include "ofxSyncedVideoReceiver.h"

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();
  void exit();
  void keyPressed(int key);

  ofxSyncedVideoReceiver syncReceiver;

  bool togglePause = false;
  bool isMuted;
  bool isFullScreen;
};
