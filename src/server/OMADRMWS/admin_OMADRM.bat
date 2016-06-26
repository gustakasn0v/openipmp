@echo off

rem This is an administration script to set up OMA DRM rights issuer
rem (server). It sets trusted CA certificates for devices (clients),
rem rights issuer's (server's) certificate chain, private key and context
rem details. The script assumes that OMADRM database, DEVICE_CA,
rem RI_CERT_CHAIN and RI_PRIVATE tables exist in OMADRM database. Script
rem takes two parameters, first mySQL user name and second mySQL user
rem password. Provided user name must have privileges to change the OMADRM
rem database.

rem Clean up previous data.
mysql -f -u %1 --password=%2 -e "TRUNCATE TABLE DEVICE_CA;" OMADRM
mysql -f -u %1 --password=%2 -e "TRUNCATE TABLE RI_CERT_CHAIN;" OMADRM
mysql -f -u %1 --password=%2 -e "TRUNCATE TABLE RI_PRIVATE;" OMADRM

rem Use the following to add trusted device (client) CA certificates.
rem Replace *.der file names with CA certificate file names. Paths must
rem be given with forward slashes (unix style).
rem CERTIFICATE FILES MUST CONTAIN DER ENCODED X509 CERTIFICATES.
rem X509 CERTIFICATES PUBLIC KEYS MUST BE RSA WITH MD5 GENERATED.
rem If no trusted device (client) CA certificates are added, then a
rem device (client) can send any certificate to identify itself. Otherwise
rem device (client) must find its own certificate chain which roots in
rem any of the trusted device (client) CA certificates.
mysql -f -u %1 --password=%2 -e "SET @device_ca:=LOAD_FILE('%CD:\=/%/../../Demo/data/OMACACert.der');INSERT INTO DEVICE_CA ( CERT ) VALUES ( @device_ca );" OMADRM
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

rem Use the following to add rights issuer's certificate chain.
rem Replace *.der file names with chain certificate file names. Paths must
rem be given with forward slashes (unix style).
rem CERTIFICATE FILES MUST CONTAIN DER ENCODED X509 CERTIFICATES.
rem X509 CERTIFICATES PUBLIC KEYS MUST BE RSA WITH MD5 GENERATED.
mysql -f -u %1 --password=%2 -e "SET @ri_ca:=LOAD_FILE('%CD:\=/%/../../Demo/data/OMACACert.der');INSERT INTO RI_CERT_CHAIN ( CERT ) VALUES ( @ri_ca );" OMADRM
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)
mysql -f -u %1 --password=%2 -e "SET @ri_chain:=LOAD_FILE('%CD:\=/%/../../Demo/data/riCertSigned.der');INSERT INTO RI_CERT_CHAIN ( CERT ) VALUES ( @ri_chain );" OMADRM
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

rem Use the following to add rights issuer's private key and context.
rem Replace *.der file name with private key file name. Paths must
rem be given with forward slashes (unix style).
rem PRIVATE KEY FILE MUST CONTAIN DER ENCODED UNENCRYPTED PKCS8 PRIVATE KEY.
rem PRIVATE KEY MUST BE RSA WITH MD5 GENERATED.
mysql -f -u %1 --password=%2 -e "SET @ri_key:=LOAD_FILE('%CD:\=/%/../../Demo/data/riKey.der');SET @ri_ctx:=LOAD_FILE('%CD:\=/%/../../Demo/data/ri_context.xml');INSERT INTO RI_PRIVATE ( ID, PRIVATE_KEY, CONTEXT ) VALUES ( 1, @ri_key, @ri_ctx );" OMADRM
IF %ERRORLEVEL% GTR 0 (
GOTO ERROR
)

GOTO END

:ERROR
echo OMADRM administration FAILED
GOTO END

:END
pause
