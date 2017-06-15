@echo off
SET SRC="..\..\..\DLL\Win32\amd64\Debug\*.dll"
SET DEST="..\GatewareTestSuite\x64\Debug"
copy /V %SRC% %DEST%