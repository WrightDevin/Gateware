@echo off
SET SRC="..\..\..\gateware.git.0\DLL\Win32\amd64\Debug\*.dll"
SET DEST="..\GatewareTestSuite\x64\Debug"
copy /V %SRC% %DEST%