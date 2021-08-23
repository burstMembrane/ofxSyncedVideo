

#include "ofMain.h"

#include "ofxOsc.h"
#include "ofxSyncedVideoBase.h"

class ofxSyncedVideoSender : public ofxSyncedVideoBase {
public:
  // receiving messages
  ofxOscSender oscServer;
  void sendPosition();

  void sendMessage(string address, int value);
  void sendMessage(string address, float value);
  void sendMessage(string address, bool value);
  void sendMessage(string address, char value);
  void sendMessage(string address, string value);

  void sendFrame();
  void setupOSC();
  void setup();
  void close();
  void sync();

  // transport controls
  void pause();
  void play();
  void mute();
  void unmute();
  void restart();

  float syncTime;
  float videoDuration;

  // settings
  float threshold;

  int lastFrame;
  float lastPos;
  bool shouldUpdate;
  // settings file
  ofxXmlSettings settings;
};
