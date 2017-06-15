@echo off
REM SET A="..\..\..\gateware.git.0\DLL\Win32\i386\Debug\*.dll"
REM SET B="..\..\..\gateware.git.0\DLL\Win32\i386\Release\*.dll"
REM SET C="..\..\..\gateware.git.0\DLL\Win32\amd64\Debug\*.dll"
REM SET D="..\..\..\gateware.git.0\DLL\Win32\amd64\Release\*.dll"

SET E="..\GatewareTestSuite\Debug\*.dll"
SET F="..\GatewareTestSuite\Release\*.dll"
SET G="..\GatewareTestSuite\Debug\*.dll"
SET H="..\GatewareTestSuite\Release\*.dll"

REM del %A%
REM del %B%
REM del %C%
REM del %D%

del %E%
del %F%
del %G%
del %H%