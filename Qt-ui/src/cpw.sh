#!/bin/bash
expect << EOF
spawn passwd $1
expect "Enter new UNIX password:"
send "$2\n"
expect "Retype new UNIX password:"
send "$2\n"
expect eof;
EOF
