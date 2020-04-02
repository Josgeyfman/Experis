
#!/bin/bash
echo please enter name:
read NAME
echo please enter  tel
read TEL
echo please enter address
read ADR
echo $NAME $TEL $ADR >> phonelist.txt
cat phonelist.txt
