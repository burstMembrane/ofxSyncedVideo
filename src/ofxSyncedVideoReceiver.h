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

  // settings file
  ofxXmlSettings settings;
};
