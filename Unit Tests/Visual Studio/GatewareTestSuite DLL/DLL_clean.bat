@echo off
REM SET A="..\..\..\gateware.git.0\DLL\Win32\i386\Debug\*.dll"
REM SET B="..\..\..\gateware.git.0\DLL\Win32\i386\Release\*.dll"
REM SET C="..\..\..\gateware.git.0\DLL\Win32\amd64\Debug\*.dll"
REM SET D="..\..\..\gateware.git.0\DLL\Win32\amd64\Release\*.dll"

SET E="..\GatewareTestSuite\x86\Debug\*.dll"
SET F="..\GatewareTestSuite\x86\Release\*.dll"
SET G="..\GatewareTestSuite\x64\Debug\*.dll"
SET H="..\GatewareTestSuite\x64\Release\*.dll"

REM del %A%
REM del %B%
REM del %C%
REM del %D%

del %E%
del %F%
del %G%
del %H%