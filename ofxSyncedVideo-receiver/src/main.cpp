#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
  // <-------- setup the GL context
// Apply these GL settings for raspberry pi
#ifdef TARGET_RASPBERRY_PI
  ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);
  ofGLESWindowSettings settings;
  settings.setGLESVersion(2);
  ofCreateWindow(settings);

#else
  ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);
#endif
  // this kicks off the running of my app
  // can be OF_WINDOW or OF_FULLSCREEN
  // pass in width and height too:
  ofRunApp(new ofApp());
}
