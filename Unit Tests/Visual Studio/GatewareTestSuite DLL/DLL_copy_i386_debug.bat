@echo off
SET SRC="..\..\..\DLL\Win32\i386\Debug\*.dll"
SET DEST="..\GatewareTestSuite\Debug"
copy /V %SRC% %DEST%