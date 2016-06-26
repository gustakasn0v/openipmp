echo "Installing openIPMP server"

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

echo "Please enter mySQL user name: "
read MYSQL_USER
echo "Please enter mySQL user password: "
read MYSQL_PASS

export ANT_HOME=`pwd`/ant
if [ ! -x $ANT_HOME/bin/ant ]
then
	chmod +x $ANT_HOME/bin/ant
fi

cd ./OMADRMWS
if [ ! -x ./install_OMADRM.sh ]
then
	chmod +x ./install_OMADRM.sh
fi
./install_OMADRM.sh $MYSQL_USER $MYSQL_PASS
cd ..

cd ./osms
if [ ! -x ./install_OSMS.sh ]
then
	chmod +x ./install_OSMS.sh
fi
./install_OSMS.sh $MYSQL_USER $MYSQL_PASS
cd ..

export MYSQL_USER=
export MYSQL_PASS=
export ANT_HOME=
echo "openIPMP server installation COMPLETED"

exit 0
