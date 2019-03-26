CLS
@ECHO OFF

setlocal ENABLEDELAYEDEXPANSION

PUSHD %~dp0

SET LANG=csharp
::SET LANG=python
::SET LANG=xml

SET OUT=out\%LANG%
::SET OUT=..\SolARUnitySamples\Assets\Standard Assets\SolARUnityPlugin\Wrapper

::RMDIR /S /Q "%OUT%"

::DEL /Q *.cxx

SET OPTIONS=^
 -c++ ^
 -%LANG% ^
 -small -O ^
 -outcurrentdir ^
 -I./Swig ^
 -I./Swig/include ^
 -I%BCOMDEVROOT%/thirdParties/xpcf/2.1.0/interfaces ^
 -I%BCOMDEVROOT%/bcomBuild/SolARFramework/0.5.1/interfaces ^
 -dllimport SolARWrapper ^
 

FOR %%F IN (Swig\*.i) DO (
ECHO ##########
ECHO # %%F
SET F=%%~nF
SET OUTPUT=%OUT%\!F:_=\!
DEL /Q "!OUTPUT!\*.*"
IF NOT EXIST "!OUTPUT!" MKDIR "!OUTPUT!"
CALL SWIG ^
 %OPTIONS% ^
 -namespace !F:_=.! ^
 -outdir "!OUTPUT!" ^
 %%F
)

POPD
