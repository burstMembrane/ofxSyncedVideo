#include "ofxSyncedVideoSender.h"

void ::ofxSyncedVideoSender::setupOSC() {
  oscServer.setup(settingsHost, settingsPort);

  ofLogNotice("ofxSyncedVideoSender::setupOSC")
      << "OSC Server running on " << settingsHost << ":" << settingsPort
      << "\n";
  sendMessage("/online", true);
  // wait a minute, then send restart message
  ofSleepMillis(1000);
  sendMessage("/restart", true);
}

void ofxSyncedVideoSender::close() {
  sendMessage("/online", false);
  oscServer.clear();
}

void ofxSyncedVideoSender::setup() {
  ofxSyncedVideoBase::setup();
  sendMessage("/restart", true);
}
void ofxSyncedVideoSender::sync() {

  switch (syncType) {
  case 1:
    sendPosition();
    break;
  case 2:
    sendFrame();
    break;
  default:
    sendPosition();
    break;
  }
}
void ofxSyncedVideoSender::pause() {
  ofxSyncedVideoBase::pause();
  sendMessage("/isPlaying", false);
}

void ofxSyncedVideoSender::play() {
  ofxSyncedVideoBase::play();
  sendMessage("/isPlaying", true);
}

void ofxSyncedVideoSender::mute() {
  ofxSyncedVideoBase::mute();
  sendMessage("/mute", true);
}
void ofxSyncedVideoSender::unmute() {
  ofxSyncedVideoBase::unmute();
  sendMessage("/mute", false);
}

void ofxSyncedVideoSender::restart() {
  ofxSyncedVideoBase::restart();
  sendMessage("/restart", true);
}
void ofxSyncedVideoSender::sendPosition() {

  // send position data over OSC (only if it has changed)
  if (isPlaying) {

    if (ofGetElapsedTimeMillis() % 50 == 0) {
      if (getPosition() != lastPos) {
        float pos = getPosition();
        sendMessage("/position", pos);
        lastPos = pos;
      }
    }
  } else {
    // its not playing, tell the client to pause
    if (fmod(ofGetElapsedTimef(), threshold) == 0) {

      sendMessage("/isPlaying", false);
      float pos = getPosition();
      sendMessage("/position", pos);
      lastPos = pos;
    }
  }
}

void ofxSyncedVideoSender::sendFrame() {
  //  send current frame over OSC
  int currentFrame = getCurrentFrame();
  if (currentFrame != lastFrame) {
    sendMessage("/currentFrame", currentFrame);
    if (currentFrame == 0) {
      sendMessage("/restart", true);
    }
    lastFrame = currentFrame;
  }
}

// sending messages
void ofxSyncedVideoSender::sendMessage(string address, string value) {
  ofLogVerbose("ofxSyncedVideoSender::sendMessage")
      << "Sending message: " << ofToString(address) << " " << value;
  // send an int message over OSC
  ofxOscMessage msg;
  msg.setAddress(address);
  msg.addStringArg(value);
  oscServer.sendMessage(msg);
}

void ofxSyncedVideoSender::sendMessage(string address, char value) {
  ofLogVerbose("ofxSyncedVideoSender::sendMessage")
      << "Sending message: " << ofToString(address) << " " << value;
  // send an int message over OSC
  ofxOscMessage msg;
  msg.setAddress(address);
  msg.addCharArg(value);
  oscServer.sendMessage(msg);
}

void ofxSyncedVideoSender::sendMessage(string address, int value) {
  ofLogVerbose("ofxSyncedVideoSender::sendMessage")
      << "Sending message: " << ofToString(address) << " " << ofToString(value);
  // send an int message over OSC
  ofxOscMessage msg;
  msg.setAddress(address);
  msg.addIntArg(value);
  oscServer.sendMessage(msg);
}

void ofxSyncedVideoSender::sendMessage(string address, float value) {
  // send a float message over OSC
  ofLogVerbose("ofxSyncedVideoSender::sendMessage")
      << "Sending message: " << ofToString(address) << " " << ofToString(value);
  ofxOscMessage msg;
  msg.setAddress(address);
  msg.addFloatArg(value);
  oscServer.sendMessage(msg);
}

void ofxSyncedVideoSender::sendMessage(string address, bool value) {
  ofLogVerbose("ofxSyncedVideoSender::sendMessage")
      << "Sending message: " << ofToString(address) << " " << ofToString(value);
  // send a boolean message over OSC
  ofxOscMessage msg;
  msg.setAddress(address);
  msg.addBoolArg(value);
  oscServer.sendMessage(msg);
}
