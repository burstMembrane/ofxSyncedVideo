#include "ofApp.h"
#include "ofMain.h"
#ifdef RPI_4
#include "bcm_host.h"
#include "ofAppNoWindow.h"
#endif
//========================================================================
int main() {
  // <-------- setup the GL context
// Apply these GL settings for raspberry pi
#ifdef TARGET_RASPBERRY_PI

#ifdef RPI_4
  ofAppNoWindow window;
  ofSetupOpenGL(&window, 1920, 1080, OF_WINDOW);
#else

  ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);
  ofGLESWindowSettings settings;
  settings.setGLESVersion(2);
  ofCreateWindow(settings);
#endif

#else
  ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);
#endif
  // this kicks off the running of my app
  // can be OF_WINDOW or OF_FULLSCREEN
  // pass in width and height too:
  ofRunApp(new ofApp());
}
