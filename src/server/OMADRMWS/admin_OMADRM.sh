# This is an administration script to set up OMA DRM rights issuer
# (server). It sets trusted CA certificates for devices (clients),
# rights issuer's (server's) certificate chain, private key and context
# details. The script assumes that OMADRM database, DEVICE_CA,
# RI_CERT_CHAIN and RI_PRIVATE tables exist in OMADRM database. Script
# takes two parameters, first mySQL user name and second mySQL user
# password. Provided user name must have privileges to change the OMADRM
# database.

# Clean up previous data.
mysql -f -u $1 --password=$2 -e "TRUNCATE TABLE DEVICE_CA;" OMADRM
mysql -f -u $1 --password=$2 -e "TRUNCATE TABLE RI_CERT_CHAIN;" OMADRM
mysql -f -u $1 --password=$2 -e "TRUNCATE TABLE RI_PRIVATE;" OMADRM

export CURR_DIR=`pwd`

# Use the following to add trusted device (client) CA certificates.
# Replace *.der file names with CA certificate file names. Paths must
# be given with forward slashes (unix style).
# CERTIFICATE FILES MUST CONTAIN DER ENCODED X509 CERTIFICATES.
# X509 CERTIFICATES PUBLIC KEYS MUST BE RSA WITH MD5 GENERATED.
# If no trusted device (client) CA certificates are added, then a
# device (client) can send any certificate to identify itself. Otherwise
# device (client) must find its own certificate chain which roots in
# any of the trusted device (client) CA certificates.
mysql -f -u $1 --password=$2 -e "SET @device_ca:=LOAD_FILE('$CURR_DIR/../../Demo/data/OMACACert.der');INSERT INTO DEVICE_CA ( CERT ) VALUES ( @device_ca );" OMADRM

# Use the following to add rights issuer's certificate chain.
# Replace *.der file names with chain certificate file names. Paths must
# be given with forward slashes (unix style).
# CERTIFICATE FILES MUST CONTAIN DER ENCODED X509 CERTIFICATES.
# X509 CERTIFICATES PUBLIC KEYS MUST BE RSA WITH MD5 GENERATED.
mysql -f -u $1 --password=$2 -e "SET @ri_ca:=LOAD_FILE('$CURR_DIR/../../Demo/data/OMACACert.der');INSERT INTO RI_CERT_CHAIN ( CERT ) VALUES ( @ri_ca );" OMADRM
mysql -f -u $1 --password=$2 -e "SET @ri_chain:=LOAD_FILE('$CURR_DIR/../../Demo/data/riCertSigned.der');INSERT INTO RI_CERT_CHAIN ( CERT ) VALUES ( @ri_chain );" OMADRM

# Use the following to add rights issuer's private key and context.
# Replace *.der file name with private key file name. Paths must
# be given with forward slashes (unix style).
# PRIVATE KEY FILE MUST CONTAIN DER ENCODED UNENCRYPTED PKCS8 PRIVATE KEY.
# PRIVATE KEY MUST BE RSA WITH MD5 GENERATED.
mysql -f -u $1 --password=$2 -e "SET @ri_key:=LOAD_FILE('$CURR_DIR/../../Demo/data/riKey.der');SET @ri_ctx:=LOAD_FILE('$CURR_DIR/../../Demo/data/ri_context.xml');INSERT INTO RI_PRIVATE ( ID, PRIVATE_KEY, CONTEXT ) VALUES ( 1, @ri_key, @ri_ctx );" OMADRM
