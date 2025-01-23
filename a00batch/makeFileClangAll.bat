@echo off
for /f %%f in ('dir /b *.c') do ..\a00batch\makeFileClang.bat %%f
