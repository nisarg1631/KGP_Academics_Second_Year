@echo off
set MATLAB=C:\Program Files\MATLAB\R2020a
"%MATLAB%\bin\win64\gmake" -f SigNetLabExp3code_19CS30031.mk  OPTS="-DTID01EQ=0"
