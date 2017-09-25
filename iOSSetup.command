#!/bin/bash

#Must be run at least once through terminal.

#echo ${PWD}
BASEDIR="$( cd "$( dirname "$0" )" && pwd )"

#echo "Script location: ${BASEDIR}"
cd "${BASEDIR}"

cd ../
mkdir GW_OUTPUT
cd GW_OUTPUT

mkdir ./Xcode
cd Xcode

#echo "${BASEDIR}/iOS-CMake/toolchain/iOS.cmake"
#cmake -DCMAKE_TOOLCHAIN_FILE="../../gateware.git.0/iOS-CMake/toolchain/iOS.cmake"
IOS="True"
export PATH=$PATH:/Applications/CMake.app/Contents/bin
cmake ./../../gateware.git.0 -DCMAKE_TOOLCHAIN_FILE=iOS-CMake/toolchain/iOS.cmake -DIOS=True -G "Xcode"
#-DIOS_PLATFORM=OS -G "Xcode"
