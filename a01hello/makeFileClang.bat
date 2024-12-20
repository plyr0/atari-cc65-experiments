@echo off
IF [%1]==[] goto :ARGZ
mos-atari8-dos-clang %~n1.c -o %~n1_cl.xex
rem %~n1.xex
goto :END

:ARGZ
echo Usage: makeFileClang file.c
pause

:END