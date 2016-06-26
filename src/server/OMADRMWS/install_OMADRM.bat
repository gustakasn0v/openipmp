@echo off

echo Installing OMADRMWS
pause

IF NOT EXIST %JBOSS_HOME% (
echo JBOSS_HOME environment variable is not set!
GOTO ERROR
)
IF NOT EXIST %JAVA_HOME% (
echo JAVA_HOME environment variable is not set!
GOTO ERROR
)

echo Building OMADRMWS

call "..\ant\bin\ant" -f build.xml
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

echo Deploying OMADRMWS

move /Y OMADRMWS.war "%JBOSS_HOME%\server\default\deploy"
copy /Y ..\osms\lib\ejbca\jce-jdk13-112.jar "%JBOSS_HOME%\server\default\lib"
copy /Y ..\osms\lib\junit\junit.jar "%JBOSS_HOME%\server\default\lib"
copy /Y ..\osms\lib\mysql\mysql-connector-java-3.1.10-bin.jar "%JBOSS_HOME%\server\default\lib"
copy /Y ..\osms\lib\squashxml\ext\xerces.jar "%JBOSS_HOME%\server\default\lib"

if not exist "%JBOSS_HOME%\openIPMP" md "%JBOSS_HOME%\openIPMP"
if not exist "%JBOSS_HOME%\openIPMP\OMADRM" md "%JBOSS_HOME%\openIPMP\OMADRM"
copy /Y server_config.xml "%JBOSS_HOME%\openIPMP\OMADRM"
copy /Y admin_OMADRM.bat "%JBOSS_HOME%\openIPMP\OMADRM"

echo Creating mySQL tables

mysql -f -u %1 --password=%2 < mySQL_OMADRM_create.sql
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

echo Administering OMADRM

call admin_OMADRM.bat %1 %2
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

GOTO DONE

:ERROR
echo OMADRMWS installation FAILED
GOTO END

:DONE
echo OMADRMWS installation completed
GOTO END

:END
pause
