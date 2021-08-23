
#ifdef RPI_4
#include "ofxOMXPlayer.h"

class ofxRPI4VideoPlayer : public ofxOMXPlayer {

public:
  void createPlayer(string videoPath);
  bool hasLoaded;
  ofxOMXPlayer *omxPlayer;
};
#endif