#!/bin/bash
USERNAME=/tmp/username
PASSWD=/tmp/passwd

expect << EOF
spawn passwd `cat $USERNAME`
expect "Enter new UNIX password:"
send "`cat $PASSWD`\r"
expect "Retype new UNIX password:"
send "`cat $PASSWD`\r"
expect eof;
EOF
rm -rf /tmp/*
