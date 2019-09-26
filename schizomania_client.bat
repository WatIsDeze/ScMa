@ECHO OFF

set SCMA_BIN=src

IF EXIST bin64\schizomania.exe (
    IF /I "%PROCESSOR_ARCHITECTURE%" == "amd64" (
        set SCMA_BIN=bin64
    )
    IF /I "%PROCESSOR_ARCHITEW6432%" == "amd64" (
        set SCMA_BIN=bin64
    )
)

start %SCMA_BIN%\schizomania.exe "-u$HOME\My Games\SchizoMania" -glog.txt %*
