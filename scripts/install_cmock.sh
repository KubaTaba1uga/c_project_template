#!/bin/bash

export CMOCK_DIR=../cmock

// Install cmock and unity
git clone --recursive https://github.com/throwtheswitch/cmock.git $CMOCK_DIR
cd $CMOCK_DIR
bundle install
