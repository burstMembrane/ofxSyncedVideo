
#ifdef RPI_4
#include "ofxRPI4VideoPlayer.h"
//--------------------------------------------------------------

void ofxRPI4VideoPlayer::createPlayer(string videoPath) {
  omxPlayer = NULL;
  ofSystem("dd if=/dev/zero of=/dev/fb0 bs=1000 count=768");
  if (!omxPlayer && ofGetFrameNum() == 100) {
    ofLog() << "createPlayer";

    string videoPath = ofToDataPath(videoPath, true);

    ofxOMXPlayerSettings settings;
    settings.videoPath = videoPath;

    settings.useHDMIForAudio = true; // default true
    settings.enableTexture = false;  // default true
    settings.enableLooping = true;   // default true
    settings.enableAudio = true; // default true, save resources by disabling
    settings.layer = 1;
    omxPlayer = new ofxOMXPlayer();

    // so either pass in the settings
    omxPlayer->setup(settings);
    hasLoaded = true;
  }
}

#endif