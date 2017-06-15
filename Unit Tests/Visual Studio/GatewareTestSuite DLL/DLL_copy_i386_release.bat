@echo off
SET SRC="..\..\..\DLL\Win32\i386\Release\*.dll"
SET DEST="..\GatewareTestSuite\Release"
copy /V %SRC% %DEST%