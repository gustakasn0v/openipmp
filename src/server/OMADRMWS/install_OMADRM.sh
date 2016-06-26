echo "Installing OMADRMWS"

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

echo "Building OMADRMWS"

if [ ! -x $ANT_HOME/bin/ant ]
then
	chmod +x $ANT_HOME/bin/ant
fi

$ANT_HOME/bin/ant -f build.xml

echo "Deploying OMADRMWS"

mv -f OMADRMWS.war "$JBOSS_HOME/server/default/deploy"
cp -f ../osms/lib/ejbca/jce-jdk13-112.jar "$JBOSS_HOME/server/default/lib"
cp -f ../osms/lib/junit/junit.jar "$JBOSS_HOME/server/default/lib"
cp -f ../osms/lib/mysql/mysql-connector-java-3.1.10-bin.jar "$JBOSS_HOME/server/default/lib"
cp -f ../osms/lib/squashxml/ext/xerces.jar "$JBOSS_HOME/server/default/lib"

if [ ! -d "${JBOSS_HOME}"/openIPMP ]
then
	mkdir ${JBOSS_HOME}/openIPMP
fi
if [ ! -d "${JBOSS_HOME}"/openIPMP/OMADRM ]
then
	mkdir ${JBOSS_HOME}/openIPMP/OMADRM
fi
cp -f server_config.xml "$JBOSS_HOME/openIPMP/OMADRM"
if [ ! -x ./admin_OMADRM.sh ]
then
	chmod +x ./admin_OMADRM.sh
fi
cp -f ./admin_OMADRM.sh "$JBOSS_HOME/openIPMP/OMADRM"

echo "Creating mySQL tables"

mysql -f -u $1 --password=$2 < mySQL_OMADRM_create.sql

echo "Administering OMADRM"

./admin_OMADRM.sh $1 $2

echo "OMADRMWS installation completed"
