export SHELL=/bin/bash

VERSION= v0.2.12
FLAGS = -Werror -Wall -Wpedantic -Wfatal-errors

PALETTE_PATH = ./palette.gpl

all: demo
	@echo -e "End of build.\n"

.PHONY: all

demo: .demo.o
	@echo -en "Building demo for $(VERSION):  "
	gcc $(FLAGS) .demo.o .animate.o .palette.o -o demo -lncurses -pthread
	@echo -e "Done.\n"

s4c-animate/palette.c:
	@echo -en "Generating palette.c from [$(PALETTE_PATH)]:  "
	python scripts/palette.py C-impl $(PALETTE_PATH) ../.. > s4c-animate/palette.c
	@echo -e "Done."

s4c-animate/palette.h:
	@echo -en "Generating palette.h from [$(PALETTE_PATH)]:  "
	python scripts/palette.py C-header $(PALETTE_PATH) ../.. > s4c-animate/palette.h
	@echo -e "Done."

.palette.o: s4c-animate/palette.c s4c-animate/palette.h
	@echo -en "Building palette.o:  "
	gcc $(FLAGS) -c s4c-animate/palette.c -o .palette.o
	@echo -e "Done."

.animate.o: s4c-animate/animate.c s4c-animate/animate.h
	@echo -en "Building animate.o:  "
	gcc $(FLAGS) -c s4c-animate/animate.c -o .animate.o
	@echo -e "Done."

.demo.o: s4c-demo/demo.c .animate.o .palette.o
	@echo -en "Building demo.o:  "
	gcc $(FLAGS) -c s4c-demo/demo.c -o .demo.o
	@echo -e "Done."

doc:
	@echo -e "Using doxygen to create tex + html for $(VERSION):    "
	doxygen ./documentation/s4c.doxyfile
	@echo -e "\n\033[1;33mDone.\e[0m\n"
	sleep 1
	clear
	@echo -e "Listing ./doxygen directory contents:\n"
	ls -R ./doxygen
	@echo -e "\n\033[1;32mDone.\e[0m"
	@echo -e "\ncd to ./doxygen/latex and make tex into pdf:\n"
	cd ./doxygen/latex ; make | grep "Output written"
	@echo -e "\n\033[1;32mDone.\e[0m"
	@echo -e "\nmv ./doxygen/latex/refman.pdf to (../../documentation/docs.pdf) :\n"
	mv ./doxygen/latex/refman.pdf ./documentation/docs.pdf
	@echo -e "\n\033[1;32mDone.\e[0m"
	@echo -en "\nRemove ./doxygen/:    "
	yes | rm -rd ./doxygen/
	@echo -e "\n\033[1;32mDone.\e[0m"
clean:
	@echo -en "Cleaning build artifacts:  "
	-rm \.*.o demo s4c-animate/palette.*
	@echo -e "Done."

clean_debug:
	@echo -en "Cleaning debug build artifacts:  "
	-rm \.*.o demo_debug
	@echo -e "Done."

cleanob:
	@echo -en "Cleaning object files:  "
	-rm \.*.o
	@echo -e "Done."

debug: s4c-animate/palette.c s4c-animate/palette.h
	@echo -en "Building demo_debug with debug flags:  "
	gcc -c s4c-animate/animate.c -ggdb -O0 -o .animate.o
	gcc -c s4c-animate/palette.c -ggdb -O0 -o .palette.o
	gcc -c s4c-demo/demo.c -ggdb -O0 -o .demo.o
	gcc .demo.o .animate.o .palette.o -o demo_debug -lncurses
	@echo -e "Done.\nUse gdb to debug the executable.\n"

rebuild: clean all

$(V).SILENT:
