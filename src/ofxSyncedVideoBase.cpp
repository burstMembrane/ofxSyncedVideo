#include "ofxSyncedVideoBase.h"

/*
SETUP
 */

ofxSyncedVideoBase::ofxSyncedVideoBase(void) {

  // load xml settings if they exist
  // get video data
  try {
    settings.loadFile("settings.xml");
    string path = settings.getValue("settings:videoPath", "");
    videoPath = ofToDataPath("movies/" + path);
    ofLogNotice("ofxSyncedVideoBase::init")
        << "Loading video from " << videoPath;
    isMaster = settings.getValue("settings:isMaster", false);
    threshold = settings.getValue("settings:threshold", 0.05);
    settingsPort = settings.getValue("settings:port", 8000);
    settingsHost = settings.getValue("settings:host", "0.0.0.0");
    syncType = settings.getValue("settings:syncType", 1);
    drawMovie = true;

  } catch (const std::exception &e) {
    ofLogError("ofxSyncedVideoBase::init") << e.what() << '\n';
  }

  // hide the cursor!
  ofHideCursor();
}

void ofxSyncedVideoBase::setPaused(bool shouldPause) {
  player.setPaused(shouldPause);
}

void ofxSyncedVideoBase::drawTime() {
  char timestr[40];
  float pos = getPosition();
  sprintf(timestr, "%.2f", pos);
  sscanf(timestr, "%f", &pos);
  string positionString(timestr);
  string duration = ofToString(getDuration());
  ofDrawBitmapString(positionString + ":" + duration, 10, 50);
}

float ofxSyncedVideoBase::getPosition() {
#ifdef USE_OMXPLAYER
  return player.getMediaTime();
#else
  return player.getPosition() * player.getDuration();
#endif
}
void ofxSyncedVideoBase::setPosition(float pct) {
#ifdef USE_OMXPLAYER
  player.seekToTimeInSeconds(pct);
#else
  player.setPosition(pct / videoDuration);
#endif
}

int ofxSyncedVideoBase::getCurrentFrame() { return player.getCurrentFrame(); }

ofxSyncedVideoBase::~ofxSyncedVideoBase() {}

void ofxSyncedVideoBase::loadDirectory(string folderPath) {
  // convert the string path to a ofDirectory
  ofDirectory moviesFolder(ofToDataPath(folderPath));
  //   populate directory
  moviesFolder.listDir();
  moviesFolder.allowExt("mp4");
  // load last movie in the folder
  ofFile videoPathFile(videoPath);

  // check if there is a video file in settings
  // if there isn't load the last movie file found in the movies/ dir
  if (!videoPathFile.isFile()) {
    ofLogError("ofxSyncedVideoBase::loadDirectory")
        << "couldn't find file at path..  loading default"
        << "\n";
    for (size_t i = 0; i < moviesFolder.size(); i++) {
      ofLogNotice("ofxSyncedVideoBase::loadDirectory")
          << "found movie at :" << moviesFolder.getPath(i) << endl;
      numMovies = moviesFolder.size();
      ofLogNotice("ofxSyncedVideoBase::loadDirectory")
          << "Loaded " << numMovies << " Movies" << endl;
      if (moviesFolder.getFile(i).path() == videoPath)
        ofLogNotice("ofxSyncedVideoBase::loadDirectory")
            << "found file at videoPath " << videoPath;
      videoPath = moviesFolder.getPath(i);
    }
  }

#ifdef USE_OMXPLAYER
  // setup OMXPlayer
  ofxOMXPlayerSettings settings;
  settings.videoPath = videoPath;
  settings.enableTexture = false;

  player.setup(settings);

// #else
//   // setup ofVideoPlayer
//   player.load(videoPath);
//   // set the loop state to on
//   player.setLoopState(OF_LOOP_NORMAL);
#endif

#ifdef CUSTOM_PIPELINE

#ifdef TARGET_RASPBERRY_PI
 string pipeline =
      "filesrc location=" + videoPath + " ! qtdemux ! h264parse ! v4l2h264dec capture-io-mode=4   ";
#else
 string pipeline =
      "filesrc location=" + videoPath + " ! " + " decodebin ! videoconvert ";
#endif
 

  ofLogNotice("ofxSyncedVideoBase::loadDirectory")
      << "using custom gst pipeline. " << pipeline;

  gstPlayer = std::make_shared<ofGstVideoPlayer>();

  player.setPlayer(gstPlayer);

  auto gstUtils = gstPlayer->getGstVideoUtils();
  ofLogNotice("ofxSyncedVideoBase::loadDirectory")
      << "GstVideoUtils: " << gstUtils;

  gstUtils->setPipeline(pipeline);
  gstUtils->startPipeline();

#endif


// give her some time to warm up
  ofSleepMillis(2000);



  videoDuration = getDuration();

  play();

  ofLogNotice("ofxSyncedVideoBase::loadDirectory")
      << "Video Duration: " << videoDuration;
}

void ofxSyncedVideoBase::play() {
#ifdef USE_OMXPLAYER
if(player.isOpen())
  player.setPaused(false);
#else
  player.play();
#endif
}

void ofxSyncedVideoBase::pause() {
  // pause the videoplayerts
  if (player.isPlaying()) {
    player.setPaused(true);
  }
}

void ofxSyncedVideoBase::restart() {
#ifdef USE_OMXPLAYER
  player.restartMovie();
#else
  player.firstFrame();

#endif
}
float ofxSyncedVideoBase::getDuration() {
  // get the duration of the video clip
#ifdef USE_OMXPLAYER
  return player.getDurationInSeconds();
#else
  return player.getDuration();
#endif
}
void ofxSyncedVideoBase::mute() {
  // mute the player
  player.setVolume(0);
}
void ofxSyncedVideoBase::unmute() {
  // unmute the player
  player.setVolume(0.5);
}

void ofxSyncedVideoBase::setMute(bool mute) {
  if (mute)
    player.setVolume(0);
  else
    player.setVolume(0.5);
}

void ofxSyncedVideoBase::update() {
// update the movie
#ifndef USE_OMXPLAYER

  player.update();
#endif
}

void ofxSyncedVideoBase::draw() {
  // draw the movie

  if (drawMovie)
    player.draw(0, 0, ofGetWidth(), ofGetHeight());
  else
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}

/*
SETTERS
 */

void ofxSyncedVideoBase::seekTo(int frame) {

#ifdef USE_OMXPLAYER
  player.seekToFrame(frame);
#else
  player.setFrame(frame);
#endif
}
