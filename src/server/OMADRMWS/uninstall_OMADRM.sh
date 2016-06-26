echo "Uninstalling OMADRMWS"

if [ ! -d "${JBOSS_HOME}" ]
then
	echo "JBOSS_HOME environment variable is not set!"
	exit 999
fi

echo "Undeploying OMADRMWS"

if [ -f "${JBOSS_HOME}/server/default/deploy/OMADRMWS.war" ]
then
	rm -f "${JBOSS_HOME}/server/default/deploy/OMADRMWS.war"
fi
if [ -f "${JBOSS_HOME}/server/default/lib/jce-jdk13-112.jar" ]
then
	rm -f "${JBOSS_HOME}/server/default/lib/jce-jdk13-112.jar"
fi
if [ -f "${JBOSS_HOME}/server/default/lib/junit.jar" ]
then
	rm -f "${JBOSS_HOME}/server/default/lib/junit.jar"
fi
if [ -f "${JBOSS_HOME}/server/default/lib/mysql-connector-java-3.1.10-bin.jar" ]
then
	rm -f "${JBOSS_HOME}/server/default/lib/mysql-connector-java-3.1.10-bin.jar"
fi
if [ -f "${JBOSS_HOME}/server/default/lib/xerces.jar" ]
then
	rm -f "${JBOSS_HOME}/server/default/lib/xerces.jar"
fi
if [ -d "${JBOSS_HOME}/openIPMP" ]
then
	rm -rf "${JBOSS_HOME}/openIPMP"
fi

echo "Deleting mySQL tables"

mysql -f -u $1 --password=$2 -e "DROP DATABASE IF EXISTS OMADRM;"

echo "OMADRMWS uninstall completed"
