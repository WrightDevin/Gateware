cd ../
if not exist "GW_OUTPUT" mkdir GW_OUTPUT
cd GW_OUTPUT

if not exist "VisualStudio" mkdir VisualStudio
cd VisualStudio

if not exist "Gateware_amd64" mkdir Gateware_amd64
cd Gateware_amd64
set PATH=%PATH%;../../../gateware.git.0/CMake/bin/
cmake -G "Visual Studio 16 2019" -A x64 "../../../gateware.git.0"
cmake -G "Visual Studio 16 2019" -A x64 "../../../gateware.git.0"
if errorlevel 1 (
   echo Attempting to fallback to VS 2017 Compiler.
   cmake -G "Visual Studio 15 2017 Win64" "../../../gateware.git.0"
   cmake -G "Visual Studio 15 2017 Win64" "../../../gateware.git.0"
)
if errorlevel 1 (
   echo No appropriate VS compiler found. Error Level: %errorlevel%
)
cd ../
pause