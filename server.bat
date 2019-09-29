@ECHO OFF

set SCMA_BIN=src

IF /I "%PROCESSOR_ARCHITECTURE%" == "amd64" (
    set TESS_BIN=bin64
)
IF /I "%PROCESSOR_ARCHITEW6432%" == "amd64" (
    set TESS_BIN=bin64
)

start %SCMA_BIN%\tesseract.exe "-u$HOME\My Games\SchizoMania" -gserver-log.txt -d %*
