GDPROV=matedialog
bui-msgbox(){
	$GDPROV --info --text="$1"
}
bui-choice(){
	$GDPROV --question --text="$1"
}
bui-working(){
	(echo 10 ; while true; do sleep 1000 ; true; done) | $GDPROV --progress --pulsate --text="$1" --no-cancel --auto-close
}
