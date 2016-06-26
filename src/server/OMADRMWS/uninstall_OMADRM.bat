@echo off

echo Uninstalling OMADRMWS
pause

IF NOT EXIST %JBOSS_HOME% (
echo JBOSS_HOME environment variable is not set!
GOTO ERROR
)
IF NOT EXIST %JAVA_HOME% (
echo JAVA_HOME environment variable is not set!
GOTO ERROR
)

echo Undeploying OMADRMWS

if exist "%JBOSS_HOME%\server\default\deploy\OMADRMWS.war" del "%JBOSS_HOME%\server\default\deploy\OMADRMWS.war"
if exist "%JBOSS_HOME%\server\default\lib\jce-jdk13-112.jar" del "%JBOSS_HOME%\server\default\lib\jce-jdk13-112.jar"
if exist "%JBOSS_HOME%\server\default\lib\junit.jar" del "%JBOSS_HOME%\server\default\lib\junit.jar"
if exist "%JBOSS_HOME%\server\default\lib\mysql-connector-java-3.1.10-bin.jar" del "%JBOSS_HOME%\server\default\lib\mysql-connector-java-3.1.10-bin.jar"
if exist "%JBOSS_HOME%\server\default\lib\xerces.jar" del "%JBOSS_HOME%\server\default\lib\xerces.jar"

if exist "%JBOSS_HOME%\openIPMP\" rd /S /Q "%JBOSS_HOME%\openIPMP\"

echo Deleting mySQL tables

mysql -f -u %1 --password=%2 -e "DROP DATABASE IF EXISTS OMADRM;"
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

GOTO DONE

:ERROR
echo OMADRMWS uninstall FAILED
GOTO END

:DONE
echo OMADRMWS uninstall completed
GOTO END

:END
pause
