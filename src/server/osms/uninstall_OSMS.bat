echo off 

echo Uninstalling osms
pause

IF NOT EXIST %JBOSS_HOME% (
echo JBOSS_HOME environment variable is not set!
GOTO ERROR
)
IF NOT EXIST %JAVA_HOME% (
echo JAVA_HOME environment variable is not set!
GOTO ERROR
)

echo Deleting mySQL tables

mysql -f -u %1 --password=%2 -e "DROP DATABASE IF EXISTS OSMS;"
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

echo Undeploying osms from JBoss

if exist "%JBOSS_HOME%\server\default\deploy\openipmp.war" del "%JBOSS_HOME%\server\default\deploy\openipmp.war"
if exist "%JBOSS_HOME%\openIPMP\" rd /S /Q "%JBOSS_HOME%\openIPMP\"
if exist "%JBOSS_HOME%\server\default\lib\mysql-connector-java-3.1.10-bin.jar" del "%JBOSS_HOME%\server\default\lib\mysql-connector-java-3.1.10-bin.jar"
if exist "%JBOSS_HOME%\server\default\lib\ca.jar" del "%JBOSS_HOME%\server\default\lib\ca.jar"
if exist "%JBOSS_HOME%\bin\lib\mastersecret.ser" del "%JBOSS_HOME%\bin\lib\mastersecret.ser"
if exist "%JBOSS_HOME%\server\default\lib\xerces.jar" del "%JBOSS_HOME%\server\default\lib\xerces.jar"

echo Undeploying ejbca

cd ..\ejbca
call undeployJBoss4x
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
cd ..\osms
)
cd ..\osms

echo Undeploying osmsWSProxy from JBoss

if exist "%JBOSS_HOME%\server\default\deploy\osmsWSProxy.war" del "%JBOSS_HOME%\server\default\deploy\osmsWSProxy.war"

GOTO DONE

:ERROR
echo osms uninstall FAILED
GOTO END

:DONE
echo osms uninstall completed
GOTO END

:END
pause
