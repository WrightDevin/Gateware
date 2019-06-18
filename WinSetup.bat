cd ../
if not exist "GW_OUTPUT" mkdir GW_OUTPUT
cd GW_OUTPUT

if not exist "VisualStudio" mkdir VisualStudio
cd VisualStudio

if not exist "Gateware_amd64" mkdir Gateware_amd64
cd Gateware_amd64
set PATH=%PATH%;../../../gateware.git.0/CMake/bin/
cmake -A x64 "../../../gateware.git.0"
cmake -A x64 "../../../gateware.git.0"
if errorlevel 1 (
   echo No appropriate VS compiler found. Error Level: %errorlevel%
)
cd ../
pause