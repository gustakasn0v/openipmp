echo "Uninstalling osms"

if [ ! -d "${JBOSS_HOME}" ]
then
	echo "JBOSS_HOME environment variable is not set!"
	exit 999
fi

echo "Deleting mySQL tables"

mysql -f -u $1 --password=$2 -e "DROP DATABASE IF EXISTS OSMS;"

echo "Undeploying osms from JBoss"

if [ -f "${JBOSS_HOME}/server/default/deploy/openipmp.war" ]
then
	rm -f "${JBOSS_HOME}/server/default/deploy/openipmp.war"
fi
if [ -d "${JBOSS_HOME}/openIPMP" ]
then
	rm -rf "${JBOSS_HOME}/openIPMP"
fi
if [ -f "${JBOSS_HOME}/server/default/lib/mysql-connector-java-3.1.10-bin.jar" ]
then
	rm -f "${JBOSS_HOME}/server/default/lib/mysql-connector-java-3.1.10-bin.jar"
fi
if [ -f "${JBOSS_HOME}/server/default/lib/ca.jar" ]
then
	rm -f "${JBOSS_HOME}/server/default/lib/ca.jar"
fi
if [ -f "${JBOSS_HOME}/bin/lib/mastersecret.ser" ]
then
	rm -f "${JBOSS_HOME}/server/bin/lib/mastersecret.ser"
fi
if [ -f "${JBOSS_HOME}/server/default/lib/xerces.jar" ]
then
	rm -f "${JBOSS_HOME}/server/default/lib/xerces.jar"
fi

echo "Undeploying ejbca"

cd ../ejbca
if [ ! -x ./undeployJBoss4x.sh ]
then
  chmod +x ./undeployJBoss4x.sh
fi
./undeployJBoss4x.sh
cd ../osms

echo "Undeploying osmsWSProxy from JBoss"

if [ -f "${JBOSS_HOME}/server/default/deploy/osmsWSProxy.war" ]
then
	rm -f "${JBOSS_HOME}/server/default/deploy/osmsWSProxy.war"
fi

echo "osms uninstall completed"
