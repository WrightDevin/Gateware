@echo off
SET SRC="..\..\..\gateware.git.0\DLL\Win32\i386\Debug\*.dll"
SET DEST="..\GatewareTestSuite\Debug"
copy /V %SRC% %DEST%