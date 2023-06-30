export SHELL=/bin/bash

FLAGS = -Werror -Wall -Wpedantic -Wfatal-errors
all: demo
	@echo -e "\033[1;32mEnd of build.\e[0m\n"
.PHONY: all

demo: .demo.o
	@echo -en "Building demo:  "
	gcc $(FLAGS) .demo.o .animate.o -o demo -lncurses -pthread
	@echo -e "Done.\n"

.animate.o: animate_src/animate.c animate_src/animate.h
	@echo -en "Building animate.o:  "
	gcc $(FLAGS) -c animate_src/animate.c -o .animate.o
	@echo -e "Done."

.demo.o: demo_src/demo.c .animate.o
	@echo -en "Building demo.o:  "
	gcc $(FLAGS) -c demo_src/demo.c -o .demo.o
	@echo -e "Done."

clean:
	@echo -en "Cleaning build artifacts:  "
	rm \.*.o demo
	@echo -e "Done."

clean_debug:
	@echo -en "Cleaning debug build artifacts:  "
	rm \.*.o demo_debug
	@echo -e "Done."

cleanob:
	@echo -en "Cleaning object files:  "
	rm \.*.o
	@echo -e "Done."

debug:
	@echo -en "Building demo_debug with debug flags:  "
	gcc -c animate_src/animate.c -ggdb -O0 -o .animate.o
	gcc -c demo_src/demo.c -ggdb -O0 -o .demo.o
	gcc .demo.o .animate.o -o demo_debug -lncursesw
	@echo -e "Done.\nUse gdb to debug the executable.\n"

$(V).SILENT:
