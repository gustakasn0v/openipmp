if [ ! -d "${JBOSS_HOME}" ]
then
	echo "JBOSS_HOME environment variable is not set!"
	exit 999
fi

if [ -f "${JBOSS_HOME}/conf/server.p12" ]
then
	rm -f "${JBOSS_HOME}/conf/server.p12"
fi
if [ -f "${JBOSS_HOME}/server/default/lib/jce-jdk13-112.jar" ]
then
	rm -f "${JBOSS_HOME}/server/default/lib/jce-jdk13-112.jar"
fi
if [ -f "${JBOSS_HOME}/server/default/lib/ldap.jar" ]
then
	rm -f "${JBOSS_HOME}/server/default/lib/ldap.jar"
fi
if [ -f "${JBOSS_HOME}/server/default/deploy/apply.war" ]
then
	rm -f "${JBOSS_HOME}/server/default/deploy/apply.war"
fi
if [ -f "${JBOSS_HOME}/server/default/deploy/ca.jar" ]
then
	rm -f "${JBOSS_HOME}/server/default/deploy/ca.jar"
fi
if [ -f "${JBOSS_HOME}/server/default/deploy/ra.jar" ]
then
	rm -f "${JBOSS_HOME}/server/default/deploy/ca.jar"
fi
if [ -f "${JBOSS_HOME}/server/default/deploy/sampleauth.war" ]
then
	rm -f "${JBOSS_HOME}/server/default/deploy/sampleauth.war"
fi
if [ -f "${JBOSS_HOME}/server/default/deploy/webdist.war" ]
then
	rm -f "${JBOSS_HOME}/server/default/deploy/webdist.war"
fi
