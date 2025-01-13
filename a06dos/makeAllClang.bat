@echo off
for /f %%f in ('dir /b *.c') do makeFileClang.bat %%f
