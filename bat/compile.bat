@ECHO OFF
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
ml /c /coff /Zi exp.asm
link /OPT:NOREF /DEBUG BRA_Lib.lib exp.obj  /SUBSYSTEM:CONSOLE /NODEFAULTLIB:libcurt.lib
call exp.exe