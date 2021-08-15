#!/bin/bash

cd ofxSyncedVideo-receiver
make -j4 -s
cd ..
cd ofxSyncedVideo-sender
make -j4 -s
cd ..
