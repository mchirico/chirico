#!/bin/bash
javac MyRemoteImpl.java
rmic MyRemoteImpl
rmiregistry &
java MyRemoteImpl &
#
# Now the client
javac MyRemoteClient.java
java MyRemoteClient
echo 'Will wait 5 secounds. Issue  pkill rmiregistry'
sleep 5
echo 'Run: pkill rmiregistry'
