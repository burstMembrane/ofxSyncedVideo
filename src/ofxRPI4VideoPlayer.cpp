#include "ofApp.h"

//--------------------------------------------------------------

void ofxRpi4VideoPlayer::createPlayer(string videoPath) {
  omxPlayer = NULL;

  if (!omxPlayer && ofGetFrameNum() == 100) {
    ofLog() << "createPlayer";

    string videoPath = ofToDataPath(videoPath, true);

    // Somewhat like ofFboSettings we may have a lot of options so this is the
    // current model
    ofxOMXPlayerSettings settings;
    settings.videoPath = videoPath;
    settings.useHDMIForAudio = true; // default true
    settings.enableTexture = false;  // default true
    settings.enableLooping = true;   // default true
    settings.enableAudio = true; // default true, save resources by disabling
    // settings.doFlipTexture = true;        //default false

    omxPlayer = new ofxOMXPlayer();
    // so either pass in the settings
    omxPlayer->setup(settings);
    hasLoaded = true;
  }
}
