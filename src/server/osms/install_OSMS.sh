echo "Installing osms"

if [ ! -d "${JBOSS_HOME}" ]
then
	echo "JBOSS_HOME environment variable is not set!"
	exit 999
fi

if [ ! -d "${JAVA_HOME}" ]
then
	echo "JAVA_HOME environment variable is not set!"
	exit 999
fi

if [ ! -d "${ANT_HOME}" ]
then
	echo "ANT_HOME environment variable is not set!"
	exit 999
fi

echo "Creating mySQL tables"

mysql -f -u $1 --password=$2 < ./db/Scripts/mySQL/mySQL_openIPMP_create_DB.sql
mysql -f -u $1 --password=$2 < ./db/Scripts/mySQL/mySQL_openIPMP_create_tables.sql
mysql -f -u $1 --password=$2 < ./db/Scripts/mySQL/mySQL_openIPMP_create_users.sql
mysql -f -u $1 --password=$2 < ./db/Scripts/mySQL/mySQL_openIPMP_load_seed_data.sql

echo "Building osms"

if [ ! -x $ANT_HOME/bin/ant ]
then
	chmod +x $ANT_HOME/bin/ant
fi

$ANT_HOME/bin/ant -f build-ws.xml

echo "Deploy osms to JBoss"

mv -f dist/lib/openipmp.war "$JBOSS_HOME/server/default/deploy"
if [ ! -d "${JBOSS_HOME}"/openIPMP ]
then
	mkdir ${JBOSS_HOME}/openIPMP
fi
cp -f serverConfigData.xml "$JBOSS_HOME/openIPMP"
cp -f lib/mysql/mysql-connector-java-3.1.10-bin.jar "$JBOSS_HOME/server/default/lib"
cp -f lib/ejbca/ca.jar "$JBOSS_HOME/server/default/lib"
if [ ! -d "${JBOSS_HOME}"/bin/lib ]
then
	mkdir ${JBOSS_HOME}/bin/lib
fi
cp -f lib/mastersecret.ser "$JBOSS_HOME/bin/lib/mastersecret.ser"
cp -f lib/squashxml/ext/xerces.jar "$JBOSS_HOME/server/default/lib"
if [ ! -d "${JBOSS_HOME}"/openIPMP/Templates ]
then
	mkdir ${JBOSS_HOME}/openIPMP/Templates
fi
cp -f templates/Template*.xml "$JBOSS_HOME/openIPMP/Templates"

echo "Deploying osms to ejbca"

cp -f lib/ejbca/ejb-jar.xml "../ejbca/src/ca/META-INF"
cp -f lib/server.p12 "../ejbca/src/ca/keyStore"
cp -f lib/ejbca/ISignSession.java "../ejbca/src/java/se/anatom/ejbca/ca/sign"
cp -f lib/ejbca/RSASignSessionBean.java "../ejbca/src/java/se/anatom/ejbca/ca/sign"

echo "Building ejbca"

cd "../ejbca"
$ANT_HOME/bin/ant -f build.xml

echo "Deploying ejbca"

if [ ! -x ./deployJBoss4x.sh ]
then
	chmod +x ./deployJBoss4x.sh
fi
./deployJBoss4x.sh
./deployJBoss4x.sh keystore

echo "Building osmsWSProxy"

cd "../osmsWSProxy"
$ANT_HOME/bin/ant

echo "Deploying osmsWSProxy to JBoss"

mv -f dist/lib/osmsWSProxy.war "$JBOSS_HOME/server/default/deploy"

cd "../osms"

echo "osms installation completed"
