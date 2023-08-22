#!/bin/bash

CMOCK_VER=2.5.3

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
export CMOCK_DIR=$SCRIPT_DIR/../cmock

if ! type "git" > /dev/null; then
    echo "Git is required to install cmock"
    exit 1
fi


if ! type "ruby" > /dev/null; then
    echo "Ruby is required to install cmock"
    exit 2
fi

if ! type "bundle" > /dev/null; then
    echo "Bundler is required to install cmock"
    exit 2
fi

# Install cmock and unity locally
git clone -b v$CMOCK_VER --recursive https://github.com/throwtheswitch/cmock.git $CMOCK_DIR
cd $CMOCK_DIR
bundle install
