# OpenIPMP2
Open source DRM for MPEG-4 and MPEG-2 adhering to ISO/MPEG IPMP open standards (MPEG IPMP Hooks and IPMP-X), ISMAcryp and OMA DRM 2 specs. Includes CA, PKI, DOI mgmt, ISMA streaming, license server, encoding/encryption, player, plugin architecture, etc

# Disclaimer

This code is not mine! It has been developed by [Mutable, Inc.](http://mutableinc.com/) and released under the Mozilla Public License version 1.1

# Getting the server up and running

The first thing you want to do to get the server running is to follow these steps

## Install Java 1.7
On most Debian-based distros, this should work

```
sudo apt-get install openjdk-7-jdk
```

## Install MySQL 5.5

This can be complicated depending on your Linux version as this is a fairly old MySQL version, but this is the one that's supported :/

## Download JBoss 4.0.2

You can get it [here](http://heanet.dl.sourceforge.net/project/jboss/JBoss/JBoss-4.0.2/jboss-4.0.2.tar.gz)

## Define some enviromental variables
OpenIPMP uses the `JAVA_HOME` and `JBOSS_HOME` environment variables. You can add something like this to your `/etc/environment` file. Make sure to double-check the paths, and don't forget to log-out and back in to refresh your environment
```
JAVA_HOME="/usr/lib/jvm/java-1.7.0"
JBOSS_HOME="/opt/jboss-4.0.2"

```

## Make sure your MySQL installation can read files from the system
In order to load the certificate files into the database, the project used the `LOAD_FILE` MySQL function (more info [here](http://dev.mysql.com/doc/refman/5.7/en/string-functions.html#function_load-file)), specifically in the [admin_OMADRM.sh](src/server/OMADRMWS/admin_OMADRM.sh) script. This is crucial for the installation to work. If you're having issues with this, you can move the certificate files referred in the script to the location described by your `secure_file_priv` MySQL system variable.

## Run the instalation script
Most of the installation steps are automated through the [install.sh](src/server/install.sh) script. Execute it, and inspect the output carefully for errors.

## Test the server
Go to the [OpenIPMP default URL](http://localhost:8080/openipmp/jsp/login.jsp), and create an account.
