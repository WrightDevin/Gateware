@echo off
SET SRC="..\..\..\gateware.git.0\DLL\Win32\i386\Release\*.dll"
SET DEST="..\GatewareTestSuite\Release"
copy /V %SRC% %DEST%