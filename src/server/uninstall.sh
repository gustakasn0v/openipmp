echo "Uninstalling openIPMP server"

if [ ! -d "${JBOSS_HOME}" ]
then
	echo "JBOSS_HOME environment variable is not set!"
	exit 999
fi

echo "Please enter mySQL user name: "
read MYSQL_USER
echo "Please enter mySQL user password: "
read MYSQL_PASS

cd ./OMADRMWS
if [ ! -x ./uninstall_OMADRM.sh ]
then
	chmod +x ./uninstall_OMADRM.sh
fi
./uninstall_OMADRM.sh $MYSQL_USER $MYSQL_PASS
cd ..

cd ./osms
if [ ! -x ./uninstall_OSMS.sh ]
then
	chmod +x ./uninstall_OSMS.sh
fi
./uninstall_OSMS.sh $MYSQL_USER $MYSQL_PASS
cd ..

export MYSQL_USER=
export MYSQL_PASS=
echo "openIPMP server uninstall COMPLETED"

exit 0
