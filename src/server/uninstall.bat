@echo off

echo Uninstalling openIPMP server
pause

IF NOT EXIST %JBOSS_HOME% (
echo JBOSS_HOME environment variable is not set!
GOTO ERROR
)
IF NOT EXIST %JAVA_HOME% (
echo JAVA_HOME environment variable is not set!
GOTO ERROR
)

set /P MYSQL_USER=Please enter mySQL user name: 
set /P MYSQL_PASS=Please enter mySQL user password: 

cd .\OMADRMWS
call uninstall_OMADRM.bat %MYSQL_USER% %MYSQL_PASS%
IF %ERRORLEVEL% GTR 0 (
cd ..
GOTO ERROR
)
cd ..

cd .\osms
call uninstall_OSMS.bat %MYSQL_USER% %MYSQL_PASS%
IF %ERRORLEVEL% GTR 0 (
cd ..
GOTO ERROR
)
cd ..

GOTO DONE

:ERROR
echo openIPMP server uninstall FAILED
GOTO END

:DONE
echo openIPMP uninstall COMPLETED
GOTO END

:END
set MYSQL_USER=
set MYSQL_PASS=
pause
