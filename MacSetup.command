#!/bin/bash

echo ${PWD}
BASEDIR="$( cd "$( dirname "$0" )" && pwd )"

echo "Script location: ${BASEDIR}"
cd "${BASEDIR}"

cd ../
mkdir GW_OUTPUT
cd GW_OUTPUT

mkdir ./Xcode
cd Xcode

export PATH=$PATH:/Applications/CMake.app/Contents/bin
cmake ./../../gateware.git.0 -DCMAKE_OSX_ARCHITECTURES="x86_64;i386" -G "Xcode"
