#!/bin/bash

cd ofxSyncedVideo-receiver
make run &
cd ..
cd ofxSyncedVideo-sender
make run
cd ..
