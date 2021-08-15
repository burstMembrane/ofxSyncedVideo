#!/bin/bash

cd SyncVideo-receiver
make run &
cd ..
cd SyncVideo-sender
make run
cd ..
