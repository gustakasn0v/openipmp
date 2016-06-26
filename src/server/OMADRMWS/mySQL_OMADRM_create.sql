--
--
-- LICENSE AND COPYRIGHT INFORMATION:
--
-- The contents of this file are subject to the Mozilla Public
-- License Version 1.1 (the "License"); you may not use this file
-- except in compliance with the License. You may obtain a copy of
-- the License at http://www.mozilla.org/MPL/
-- 
-- Software distributed under the License is distributed on an "AS
-- IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
-- implied. See the License for the specific language governing
-- rights and limitations under the License.
-- 
-- The Initial Developer of the Original Code is Mutable, Inc.
-- Portions created by Mutable, Inc. are
-- Copyright (C) Mutable, Inc. 2002-2006. All Rights Reserved.
-- 
--

DROP DATABASE IF EXISTS OMADRM;
CREATE DATABASE OMADRM;
USE OMADRM;
-- Add here all device CA certificates.
CREATE TABLE DEVICE_CA (
       ID                   INTEGER NOT NULL AUTO_INCREMENT,
       CERT                 BLOB NOT NULL,
       PRIMARY KEY (ID)
)TYPE=INNODB;
-- Add here rights issuer chain certificates.
CREATE TABLE RI_CERT_CHAIN (
       ID                   INTEGER NOT NULL AUTO_INCREMENT,
       CERT                 BLOB NOT NULL,
       PRIMARY KEY (ID)
)TYPE=INNODB;
CREATE TABLE RI_PRIVATE (
       ID                   INTEGER NOT NULL,
       PRIVATE_KEY          BLOB NOT NULL,
       CONTEXT              BLOB NOT NULL,
       PRIMARY KEY (ID)
)TYPE=INNODB;
CREATE TABLE DEVICE_CONTEXT (
       DEVICE_ID            VARCHAR(255) NOT NULL,
       CONTEXT              BLOB NOT NULL,
       PRIMARY KEY (DEVICE_ID)
)TYPE=INNODB;
CREATE TABLE CONTENTID2KEY (
       CONTENT_ID           VARCHAR(255) NOT NULL,
       ENC_KEY              VARCHAR(255) NOT NULL,
       PRIMARY KEY (CONTENT_ID)
)TYPE=INNODB;
CREATE TABLE DEVICEID2CONTENTID2ROIDRIGHTS (
       DEVICE_ID            VARCHAR(255) NOT NULL,
       CONTENT_ID           VARCHAR(255) NOT NULL,
       FULL_CONTENT_ID      BLOB NOT NULL,
       ROID                 BLOB NOT NULL,
       RIGHTS               BLOB NOT NULL,
       PRIMARY KEY (DEVICE_ID, CONTENT_ID)
)TYPE=INNODB;

GRANT ALL PRIVILEGES ON OMADRM.* TO omadrm@localhost IDENTIFIED BY 'omadrm' WITH GRANT OPTION; 
GRANT ALL PRIVILEGES ON OMADRM.* TO omadrm@127.0.0.1 IDENTIFIED BY 'omadrm' WITH GRANT OPTION; 
GRANT ALL PRIVILEGES ON OMADRM.* TO omadrm@"%" IDENTIFIED BY 'omadrm' WITH GRANT OPTION; 
GRANT ALL PRIVILEGES ON OMADRM.* TO ''@"%" WITH GRANT OPTION;
GRANT SHOW DATABASES ON *.* TO omadrm@localhost; 
GRANT SHOW DATABASES ON *.* TO omadrm@127.0.0.1;
GRANT SHOW DATABASES ON *.* TO omadrm@"%";
