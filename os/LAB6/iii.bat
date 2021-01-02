@ECHO off
SET SERVICES=services.txt
SET UPD_SERVICES=upd_services.txt

REM list all services running on the system
SC QUERYEX type= service > %SERVICES%

REM stop DNS client and create a diff file
SC STOP dnscache ^
	&& TIMEOUT /T 2 /NOBREAK > NUL ^
	&& SC QUERYEX type= service > %UPD_SERVICES% ^
	&& FC %SERVICES% %UPD_SERVICES% > "diff.txt"

REM restart DNS client
SC START dnscache