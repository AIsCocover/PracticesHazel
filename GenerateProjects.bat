@echo off

del /f /s /q "*.sln"
del /f /s /q "*.vcxproj.*"
rmdir /s /q "bin"
rmdir /s /q "bin-int"

call vendor\bin\premake\premake5.exe vs2017
PAUSE