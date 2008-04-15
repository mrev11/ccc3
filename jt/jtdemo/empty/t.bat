@echo off

java -jar  %jterminal% localhost  46000
java -jar  %jterminal% localhost  46001 ssl
java -jar  %jterminal% localhost  46002 ssl
java -jar  %jterminal% localhost  46002 aut=keys
java -jar  %jterminal% localhost  46003 key=keys psw=changeit
java -jar  %jterminal% localhost  46003 aut=keys key=keys psw=changeit
