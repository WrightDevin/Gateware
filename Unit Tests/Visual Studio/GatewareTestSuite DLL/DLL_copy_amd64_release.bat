@echo off
SET SRC="..\..\..\gateware.git.0\DLL\Win32\amd64\Release\*.dll"
SET DEST="..\GatewareTestSuite\x64\Release"
copy /V %SRC% %DEST%