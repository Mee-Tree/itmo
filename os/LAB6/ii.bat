@ECHO off
SET LAB=C:\LAB6
SET TEMP=%LAB%\temp
SET HOST=%COMPUTERNAME%

REM create a network share
IF NOT EXIST %TEMP% MD %TEMP% ^
	&& NET SHARE temp=%TEMP% ^
	/GRANT:everyone,FULL /REMARK:"OS course temp share"

REM create a scheduled task for copying
SCHTASKS /CREATE /F /SC MINUTE ^
	/TN temp\copy /TR %LAB%\copy.bat /RL HIGHEST

REM delete the task and compare each file
REM in the meantime kill the copying process
TIMEOUT /T 60 /NOBREAK > NUL ^
	&& SCHTASKS /DELETE /F /TN temp\copy ^
	&& PUSHD %TEMP% ^
	&& FOR %%f IN (*) DO FC %%f \\%HOST%\ADMIN$\%%f > %LAB%\%%f.diff ^
	&& POPD

REM resume copying
CALL %LAB%\copy.bat