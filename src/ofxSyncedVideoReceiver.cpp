#include "ofxSyncedVideoReceiver.h"

void ofxSyncedVideoReceiver::setupOSC() {
  // setup the osc host and port
  int port = 8000;
  if (settingsPort > 0) {
    port = settingsPort;
  }
  oscClient.setup(port);

  ofLogNotice("ofxSyncedVideoReceiver::setupOSC")
      << "Setup OSC Client on port: " << port << "\n";
  ofLogNotice("ofxSyncedVideoReceiver::setupOSC")
      << "Client is listening: " << oscClient.isListening() << "\n";
}

void ofxSyncedVideoReceiver::receiveTransportControls(ofxOscMessage m) {
  if (m.getAddress() == "/isPlaying") {
    bool isPlaying = m.getArgAsBool(0);
    player.setPaused(!isPlaying);
    ofLogNotice("ofxSyncedVideoReceiver::receiveTransportControls")
        << "Received /isPlaying message";
  }
  if (m.getAddress() == "/restart") {
    ofLogNotice("ofxSyncedVideoReceiver::receiveTransportControls")
        << "Received /restart message";
    restart();
  }
  if (m.getAddress() == "/mute") {
    ofLogNotice("ofxSyncedVideoReceiver::receiveTransportControls")
        << "Received /mute message";
    mute();
  }
  if (m.getAddress() == "/unmute") {
    ofLogNotice("ofxSyncedVideoReceiver::receiveTransportControls")
        << "Received /unmute message";
    unmute();
  }
}

/*
CLIENT RECEIVE
 */

void ofxSyncedVideoReceiver::receiveFrame() {
  while (oscClient.hasWaitingMessages()) {
    ofxOscMessage m;
    oscClient.getNextMessage(m);
    receiveTransportControls(m);
    if (m.getAddress() == "/currentFrame") {
      int frame = m.getArgAsInt(0);
      if (player.getCurrentFrame() != frame && frame > 0) {
        seekTo(frame);
        ofLogNotice("ofxSyncedVideoReceiver::receiveFrame")
            << "Received setFrame message:  " << frame << endl;
        break;
      }
    }
  }
}

void ofxSyncedVideoReceiver::receiveDraw(ofxOscMessage m) {
  if (m.getAddress() == "/draw") {
    bool shouldDraw = m.getArgAsBool(0);
    ofLogNotice("ofxSyncedVideoReceiver::receiveDraw")
        << "received /draw message!!!" << shouldDraw;
#ifdef TARGET_RASPBERRY_PI
    player.setAlpha(shouldDraw);
#endif
    drawMovie = shouldDraw;
  }
}

bool ofxSyncedVideoReceiver::receiveState() {
  while (oscClient.hasWaitingMessages()) {
    ofxOscMessage m;
    oscClient.getNextMessage(m);
    if (m.getAddress() == "/state") {
      string state = m.getArgAsString(0);

      return true ? state == "online" : false;
    }
  }
  return false;
}

void ofxSyncedVideoReceiver::receivePosition() {
  // if its the first sync, wait for a restart message
  while (oscClient.hasWaitingMessages()) {
    ofxOscMessage m;
    oscClient.getNextMessage(m);
    if (m.getAddress() == "/draw") {
      receiveDraw(m);
    }
    if (m.getAddress() == "/restart" || m.getAddress() == "/isPlaying") {
      receiveTransportControls(m);
    }
    if (m.getAddress() == "/position") {
      //  main position receiver
      // simply checks whether the current position is within the threshold
      // if it isn't change to that position
      // TODO: make more sophisticated
      float pos = m.getArgAsFloat(0);
      // ofLogNotice("current position:  ") << getPosition() << "\n";
      if (pos > 0) {
        if (getPosition() <= pos - threshold ||
            getPosition() >= pos + threshold) {

          if (pos != lastPos) {
            ofLogNotice("ofxSyncedVideoReceiver::receivePosition")
                << "setting position to:  " << pos << "/" << videoDuration
                << "\n";

            setPosition(pos);
            lastPos = pos;
          }
        }
      }
      break;
    }
  }
}

void ofxSyncedVideoReceiver::sync() {
  // main sync function
  if (syncType == 1) {
    receivePosition();
  } else if (syncType == 2) {
    receiveFrame();
  }
}

void ofxSyncedVideoReceiver::close() {
  // when closed, clear the osc client and server
  oscClient.stop();
}
