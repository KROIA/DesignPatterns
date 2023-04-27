@echo off
set buildFolder=build

REM Speichere den aktuellen Pfad ab
set projectRootPath=%CD%

mkdir %buildFolder%
cd %buildFolder%

REM Funktionsaufruf build(Debug, projectRootPath)
CALL :build Debug, "%projectRootPath%"
CALL :build Release, "%projectRootPath%"

REM pause
EXIT

REM Funktionsdefinition
:build
REM Lese Parameter 1
set buildType=%~1
REM Lese Parameter 2
set installPrefix=%~2

REM Erstelle Buildpfad
mkdir %buildType%
REM Bewege in den Buildpfad
cd %buildType%
REM cmake Befehl fürs konfigurieren
cmake -DRELATIVE_BUILD_FOLDER="%buildFolder%" -DCMAKE_BUILD_TYPE=%buildType% -DCMAKE_INSTALL_PREFIX="%installPrefix%" "%projectRootPath%"
REM cmake Befehl fürs kompilieren
cmake --build . --config %buildType% --target install

if %errorlevel% neq 0 (
    CALL:ECHORED "Build failed!"
    pause
) else (
    CALL:ECHOGREEN "Build successful!"
)
EXIT /B 0

:ECHORED
%Windir%\System32\WindowsPowerShell\v1.0\Powershell.exe write-host -foregroundcolor Red %1
EXIT /B 0

:ECHOGREEN
%Windir%\System32\WindowsPowerShell\v1.0\Powershell.exe write-host -foregroundcolor Green %1
EXIT /B 0
