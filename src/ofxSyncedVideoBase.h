#include "ofMain.h"
#pragma once
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

#ifdef TARGET_RASPBERRY_PI
#ifdef RPI_4
#include "ofxRPI4VideoPlayer"
#endif

#include "ofxOMXPlayer.h"
#endif

class ofxSyncedVideoBase {

public:
  ofxSyncedVideoBase();
  virtual ~ofxSyncedVideoBase();

  // virtuals

  void setMaster(bool master);
  void loadDirectory(string folderPath);
  void update();
  void draw();
  void drawTimeCode();
  void play();
  void pause();

  void drawTime();

  void mute();
  void unmute();

  float getDuration();
  float getPosition();

  //   setting and getting frames

  void restart();
  void seekTo(int frame);
  void setPosition(float pct);

  int getCurrentFrame();

  // receiving messages
  ofxOscReceiver oscClient;

  void setMute(bool mute);
  void setPaused(bool paused);
  void getMessage(string address);
  void showFrameTime();

  float videoDuration;

#ifdef TARGET_RASPBERRY_PI

  ofxOMXPlayer player;

#else
  ofVideoPlayer player;

#endif

#ifdef CUSTOM_PIPELINE
  ofGstVideoUtils gst;
  std::shared_ptr<ofGstVideoPlayer> gstPlayer;
#endif
  // settings
  string videoPath;
  bool isMaster;
  int settingsPort;
  string settingsHost;
  float threshold;
  bool drawMovie;
  int currentMovie;
  int numMovies;
  bool isPlaying;

  bool shouldUpdate;
  int syncType;
  float gracePeriod;
  // settings file
  ofxXmlSettings settings;
};
