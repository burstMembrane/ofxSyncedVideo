

#ifdef RPI_4
#include "ofxOMXPlayer.h"

class ofxRPI4VideoPlayer : public ofxOMXPlayer {

public:
  void createPlayer();
  bool hasLoaded;
  ofxOMXPlayer *omxPlayer;
};
#endif