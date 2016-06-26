echo off 

echo Installing osms
pause

IF NOT EXIST %JBOSS_HOME% (
echo JBOSS_HOME environment variable is not set!
GOTO ERROR
)
IF NOT EXIST %JAVA_HOME% (
echo JAVA_HOME environment variable is not set!
GOTO ERROR
)

echo Creating mySQL tables

mysql -f -u %1 --password=%2 < .\db\Scripts\mySQL\mySQL_openIPMP_create_DB.sql
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)
mysql -f -u %1 --password=%2 < .\db\Scripts\mySQL\mySQL_openIPMP_create_tables.sql
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)
mysql -f -u %1 --password=%2 < .\db\Scripts\mySQL\mySQL_openIPMP_create_users.sql
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)
mysql -f -u %1 --password=%2 < .\db\Scripts\mySQL\mySQL_openIPMP_load_seed_data.sql
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

echo Building osms

call "..\ant\bin\ant" -f build-ws.xml
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

echo Deploy osms to JBoss

move /Y dist\lib\openipmp.war "%JBOSS_HOME%\server\default\deploy"
if not exist "%JBOSS_HOME%\openIPMP" md "%JBOSS_HOME%\openIPMP"
copy /Y serverConfigData.xml "%JBOSS_HOME%\openIPMP"
copy /Y lib\mysql\mysql-connector-java-3.1.10-bin.jar "%JBOSS_HOME%\server\default\lib"
copy /Y lib\ejbca\ca.jar "%JBOSS_HOME%\server\default\lib"
if not exist "%JBOSS_HOME%\bin\lib" md "%JBOSS_HOME%\bin\lib"
copy /Y lib\mastersecret.ser "%JBOSS_HOME%\bin\lib\mastersecret.ser"
copy /Y lib\squashxml\ext\xerces.jar "%JBOSS_HOME%\server\default\lib"
if not exist "%JBOSS_HOME%\openIPMP\Templates" md "%JBOSS_HOME%\openIPMP\Templates"
copy /Y Templates\Template*.xml "%JBOSS_HOME%\openIPMP\Templates"

echo Deploying osms to ejbca

copy /Y lib\ejbca\ejb-jar.xml "..\ejbca\src\ca\META-INF"
copy /Y lib\server.p12 "..\ejbca\src\ca\keyStore"
copy /Y lib\ejbca\ISignSession.java "..\ejbca\src\java\se\anatom\ejbca\ca\sign"
copy /Y lib\ejbca\RSASignSessionBean.java "..\ejbca\src\java\se\anatom\ejbca\ca\sign"

echo Building ejbca

cd "..\ejbca"
call "..\ant\bin\ant" -f build.xml
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

echo Deploying ejbca

call deployJBoss4x
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)
call deployJBoss4x keystore
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

echo Building osmsWSProxy

cd "..\osmsWSProxy"
call "..\ant\bin\ant"

echo Deploying osmsWSProxy to JBoss

move /Y dist\lib\osmsWSProxy.war "%JBOSS_HOME%\server\default\deploy"

cd "..\osms"

GOTO DONE

:ERROR
echo osms installation FAILED
GOTO END

:DONE
echo osms installation completed
GOTO END

:END
pause
