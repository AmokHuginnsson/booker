directory .:~/prog/stdhapi:~/prog/stdhapi/hcore:~/prog/stdhapi/hconsole:~/prog/stdhapi/hdata:~/prog/stdhapi/tools
set solib-search-path ~/lib
set auto-solib-add on
set history filename .gdbhistory
set history save on
set print pretty on
set print object on
tty /dev/tty11
define go
	run
	source .breaks
end
file ./1exec -readnow -mapped
symbol-file ./1exec -readnow -mapped
share
break main
set language c++
core-file ./1exec.core
#run
