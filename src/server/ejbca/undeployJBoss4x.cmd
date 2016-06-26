@echo off
rem ----
rem Undeploy script for EJBCA
rem ----

if "%JBOSS_HOME%" == ""  goto error

if exist "%JBOSS_HOME%\conf\server.p12" del "%JBOSS_HOME%\conf\server.p12"
if exist "%JBOSS_HOME%\server\default\lib\jce-jdk13-112.jar" del "%JBOSS_HOME%\server\default\lib\jce-jdk13-112.jar"
if exist "%JBOSS_HOME%\server\default\lib\ldap.jar" del "%JBOSS_HOME%\server\default\lib\ldap.jar"
if exist "%JBOSS_HOME%\server\default\deploy\apply.war" del "%JBOSS_HOME%\server\default\deploy\apply.war"
if exist "%JBOSS_HOME%\server\default\deploy\ca.jar" del "%JBOSS_HOME%\server\default\deploy\ca.jar"
if exist "%JBOSS_HOME%\server\default\deploy\ra.jar" del "%JBOSS_HOME%\server\default\deploy\ra.jar"
if exist "%JBOSS_HOME%\server\default\deploy\sampleauth.war" del "%JBOSS_HOME%\server\default\deploy\sampleauth.war"
if exist "%JBOSS_HOME%\server\default\deploy\webdist.war" del "%JBOSS_HOME%\server\default\deploy\webdist.war"

goto end

:error 
echo JBOSS_HOME must be set

:end
