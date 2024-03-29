#In order to run this shell script you must first set appropriate permissions (only once)
#sudo chmod 774 LinuxSetup.sh

#Also remember to install the necessary development libraries
#sudo apt-get install libx11-dev
#sudo apt-get install mesa-utils

#!/bin/bash

sudo apt install cmake
cd ../

mkdir GW_OUTPUT
cd GW_OUTPUT

mkdir CodeBlocks
cd CodeBlocks

mkdir Gateware_amd64
cd Gateware_amd64

mkdir amd64Debug
cd amd64Debug

touch amd64Debug
export PATH=$PATH:../../../../gateware.git.0/CMake/bin
cmake ../../../../gateware.git.0 -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug;
rm amd64Debug

cd ../
mkdir amd64Release

cd amd64Release

touch amd64Release
export PATH=$PATH:../../../../gateware.git.0/CMake/bin
cmake ../../../../gateware.git.0 -G "CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release;
rm amd64Release

cd ../../

sleep 30s
