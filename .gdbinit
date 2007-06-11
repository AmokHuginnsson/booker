directory .:~/usr/src/yaal:~/usr/src/yaal/hcore:~/usr/src/yaal/hconsole:~/usr/src/yaal/hdata:~/usr/src/yaal/tools
set solib-search-path ~/usr/lib
set auto-solib-add on
set extension-language .h c++
set extension-language .c c++
set history filename .gdbhistory
set history save on
set print asm-demangle on
set print demangle on
set print pretty on
set print object on
#define go
#	run
#	source .breaks
#end
file ./build/1exec -readnow
symbol-file ./build/1exec -readnow
share
break main
set language c++
core-file ./1exec.core
#run
