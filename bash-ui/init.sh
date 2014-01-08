#export BUI_PREFIX="/usr/share/bash-ui"
. $BUI_PREFIX/const.sh
. $BUI_PREFIX/checkers.sh
if isunderx
then
	. $BUI_PREFIX/x.sh
else
	. $BUI_PREFIX/term.sh
fi
