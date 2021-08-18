#include "ofMain.h"

#include "ofxOsc.h"
#include "ofxSyncedVideoBase.h"
#include "ofxXmlSettings.h"

class ofxSyncedVideoReceiver : public ofxSyncedVideoBase {
public:
  // receiving messages
  ofxOscReceiver oscClient;

  int recieveIntMessage(string address);
  bool receiveBoolMessage(string address);
  float receiveFloatMessage(string address);
  void receiveTransportControls(ofxOscMessage m);
  void correctPosition(float pos);
  bool receiveState();
  void receiveFrame();
  void receiveDraw(ofxOscMessage m);
  void setupOSC();

  void receivePosition();
  void getMessage(string address);

  void close();
  void sync();

  // settings
  float lastPos;
  int lastFrame;
  float syncTime;
  int timesAttemptedSync;

  // settings file
  ofxXmlSettings settings;
};
