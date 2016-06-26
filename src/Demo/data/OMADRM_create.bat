rem Create certificate and private key for device (client) and rights issuer (server) root CA.
openssl req -x509 -days 365 -newkey rsa:2048 -keyout OMACAKey.pem -out OMACACert.pem

rem Create certificate and private key for the device (client).
openssl req -newkey rsa:2048 -keyout deviceKey.pem -out deviceCert.pem

rem Create certificate and private key for the rights issuer (server).
openssl req -newkey rsa:2048 -keyout riKey.pem -out riCert.pem

rem Initialize CA.
perl ..\..\usr\ssl\misc\CA.pl -newca

rem Sign device (client) certificate with root CA private key.
openssl ca -keyfile OMACAKey.pem -cert OMACACert.pem -in deviceCert.pem -out deviceCertSigned.pem

rem Sign rights issuer (server) certificate with root CA private key.
openssl ca -keyfile OMACAKey.pem -cert OMACACert.pem -in riCert.pem -out riCertSigned.pem

rem Convert certificates to DER format.
openssl x509 -in OMACACert.pem -inform PEM -out OMACACert.der -outform DER
openssl x509 -in deviceCertSigned.pem -inform PEM -out deviceCertSigned.der -outform DER
openssl x509 -in riCertSigned.pem -inform PEM -out riCertSigned.der -outform DER

rem Convert private keys to PKCS8 DER format.
openssl pkcs8 -topk8 -inform PEM -outform DER -in OMACAKey.pem -out OMACAKey.der -nocrypt
openssl pkcs8 -topk8 -inform PEM -outform DER -in deviceKey.pem -out deviceKey.der -nocrypt
openssl pkcs8 -topk8 -inform PEM -outform DER -in riKey.pem -out riKey.der -nocrypt

@pause
