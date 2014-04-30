#!/bin/bash
LANG=C expect << EOF
spawn passwd $1
expect "?assword:"
send \"$2\r\"
expect "?assword:"
send \"$2\r\"
expect eof;
EOF
