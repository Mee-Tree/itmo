@ECHO off
SET DRIVERS=drivers.txt

REM list all drivers installed on the system 
REM in reverse alphabetical order
DRIVERQUERY /NH | SORT /R /O %DRIVERS%
