if [ "$DESKTOP_SESSION" = "mate" ]
then
	. $BUI_PREFIX/mate-dialog.sh
#elif [ "$XDG_CURRENT_DESKTOP" = "KDE" ]
#then
#	. $BUI_PREFIX/kdialog.sh
else
	. $BUI_PREFIX/zenity.sh
fi

