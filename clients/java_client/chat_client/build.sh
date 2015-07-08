#!/bin/sh

clear
echo
mvn clean install
echo
(cd target && java -jar chat_client-1.0-SNAPSHOT-jar-with-dependencies.jar )
echo
