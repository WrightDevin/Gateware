cd ../
if not exist "GW_OUTPUT" mkdir GW_OUTPUT
cd GW_OUTPUT

if not exist "VisualStudio" mkdir VisualStudio
cd VisualStudio

if not exist "Gateware_amd64" mkdir Gateware_amd64
cd Gateware_amd64
set PATH=%PATH%;../../../gateware.git.0/CMake/bin/
cmake -G "Visual Studio 15 2017 Win64" "../../../gateware.git.0"
cmake -G "Visual Studio 15 2017 Win64" "../../../gateware.git.0"
cd ../

if not exist "Gateware_i386" mkdir Gateware_i386
cd Gateware_i386
set PATH=%PATH%;../../../gateware.git.0/CMake/bin/
cmake -G "Visual Studio 15 2017" "../../../gateware.git.0"
cmake -G "Visual Studio 15 2017" "../../../gateware.git.0"
pause