@ECHO off
SET LAB=C:\LAB6
SET TEST=%LAB%\TEST

REM create directory LAB6 if it doesn't exist
IF NOT EXIST %LAB% MD %LAB%
CD %LAB%

REM print infromation about OS version, memory
SYSTEMINFO > "systeminfo.txt"
REM print info about disks
(ECHO LIST DISK) | DISKPART ^
	| MORE +6 > "diskpart.txt"

REM create directory TEST and copy everything
IF NOT EXIST %TEST% MD %TEST%
COPY * %TEST%
PUSHD %TEST%

REM concatenate all files into one
COPY * "copy.txt"

REM delete all files except the newest one
FOR /F "skip=1" %%f IN ('DIR /B /O-D') DO DEL %%f
POPD
