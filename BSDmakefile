# This is wrapper around GNU make.

all: Makefile
	@make banner
	@echo "Invoking GNU make (gmake)."
	@gmake all

Makefile: Makefile.in configure
	@make banner
	@echo "Generating \`Makefile' and rest of necessary files."
	@./configure
	@echo "Ready for \`make'."

configure: configure.ac
	@make banner
	@echo -n "Generating \`configure' script ... "
	-@autoconf 2> /dev/null
	@echo "done."

b: bin

bin:
	@gmake bin

e: executable

executable:
	@gmake executable

dep: banner
	@gmake dep

tags: banner
	@gmake tags

i: install

install:
	@gmake install

c: clean

clean: banner
	@gmake clean

m: mrproper

mrproper: banner
	@gmake mrproper

p: purge

purge: banner
	@gmake purge

banner:
	@echo "[1m!!![m It is only a wrapper, use GNU make (gmake). [1m!!![m"

# vim: ft=make
