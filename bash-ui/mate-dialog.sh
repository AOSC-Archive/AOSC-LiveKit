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
bui-inputbox(){
	$GDPROV --entry --text="$1"
}
bui-progress(){
	$GDPROV --progress --text="$1" --no-cancel --auto-close
}
bui-list(){
	BUILISTTEXT="$1"
	BUILISTCOLUMN="$2"
	shift 2
	( for i in $* ; do echo $i ; done ) | $GDPROV --list --text="$BUILISTTEXT" --column="$BUILISTCOLUMN" --editable
}
