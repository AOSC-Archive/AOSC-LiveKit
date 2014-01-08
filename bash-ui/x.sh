if [ "$DESKTOP_SESSION" = "mate" ]
then
	. $BUI_PREFIX/mate-dialog.sh
elif [ "$DESKTOP_SESSION" = "kde" ]
then
	. $BUI_PREFIX/kdialog.sh
else
	. $BUI_PREFIX/zenity.sh
fi

