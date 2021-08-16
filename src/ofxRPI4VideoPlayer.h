

#include "ofxOMXPlayer.h"

class ofxRpi4VideoPlayer : public ofxOMXPlayer {

public:
  void createPlayer();
  bool hasLoaded;
  ofxOMXPlayer *omxPlayer;
};
