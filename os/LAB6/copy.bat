@ECHO off
SET HOST=%COMPUTERNAME%
SET /A "_2MB=1<<21"

REM copy files bigger than 2MB into temp directory 
FOR %%f IN (\\%HOST%\ADMIN$\*) DO (
	IF %%~zf geq %_2MB% XCOPY /Z %%f \\%HOST%\temp
)