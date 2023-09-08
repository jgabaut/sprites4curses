# Makefile.am

# Set the automake options
AUTOMAKE_OPTIONS = foreign

PALETTE_PATH = ./palette.gpl
# Variables
CFLAGS = @CFLAGS@
# Specify the shell to use in the makefile
SHELL := /bin/bash
# Set the .ONESHELL special target to use a specific shell for all recipes
.ONESHELL:
# Check system info
MACHINE := $$(uname -m)
PACK_NAME = $(TARGET)-$(VERSION)-$(OS)-$(MACHINE)

# Source files
s4c_SOURCES = s4c-animate/animate.c s4c-animate/palette.c s4c-demo/demo.c

# Linking rule
LDADD = $(S4C_LDFLAGS)

# Linker flag to strip symbols
AM_LDFLAGS = -s

# Compiler flags
AM_CFLAGS = $(S4C_CFLAGS) -O2 -Werror -Wpedantic -Wall


# Build rule for object files
%.o: %.c
	$(CCOMP) -c $(CFLAGS) $(AM_CFLAGS) $< -o $@

# Build rule for the final binary
$(TARGET): $(s4c_SOURCES:.c=.o)
	@echo -e "    \033[1;35mAM_CFLAGS\e[0m: [ \"\033[1;34m$(AM_CFLAGS)\e[0m\" ]"
	@echo -e "    \033[1;35mLDADD\e[0m: [ \"\033[1;34m$(LDADD)\e[0m\" ]"
	$(CCOMP) $(CFLAGS) $(AM_CFLAGS) $(s4c_SOURCES:.c=.o) -o $@ $(LDADD) $(AM_LDFLAGS)

s4c-animate/palette.c:
	@echo -en "Generating \033[1;35mpalette.c\e[0m and \033[1;35mpalette.h\e[0m from [$(PALETTE_PATH)]:  "
	python scripts/palette.py C-header $(PALETTE_PATH) ../.. > s4c-animate/palette.h
	python scripts/palette.py C-impl $(PALETTE_PATH) ../.. > s4c-animate/palette.c
	@echo -e "Done."

doc:
	@echo -e "Using doxygen to create tex + html from $(VERSION) src/:    "
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
	@echo -e "\ncd back to ../..:\n"
	cd ../..
	@echo -e "\nmv ./doxygen/latex/refman.pdf to (../../documentation/docs.pdf) :\n"
	mv ./doxygen/latex/refman.pdf ./documentation/docs.pdf
	@echo -e "\n\033[1;32mDone.\e[0m"
	@echo -en "\nRemove ./doxygen/:    "
	yes | rm -rd ./doxygen/
	@echo -e "\n\033[1;32mDone.\e[0m"

run: $(TARGET)
	@echo -en "Running ./$(TARGET).  "
	./$(TARGET)
	@echo -e "\033[1;33mDone.\e[0m"

clean:
	@echo -en "Cleaning build artifacts:  "
	-rm $(TARGET)
	-rm s4c-animate/*.o
	-rm s4c-animate/palette.h
	-rm s4c-animate/palette.c
	-rm s4c-demo/*.o
	@echo -e "\033[1;33mDone.\e[0m"

cleanob:
	@echo -en "Cleaning object build artifacts:  "
	-rm s4c-animate/*.o
	-rm s4c-demo/*.o
	@echo -e "\033[1;33mDone.\e[0m"

pack: rebuild
	@echo -e "Packing s4c:  make pack for $(VERSION)"
	@echo -e "\033[1;32m[TREE] Prepping tree, pack for $(VERSION):\e[0m"
	[[ -d ~/s4c-local/ ]] || mkdir ~/s4c-local
	[[ -d ~/s4c-local/share ]] || mkdir ~/s4c-local/share
	[[ -d ~/s4c-local/share/$(PACK_NAME) ]] || mkdir ~/s4c-local/share/$(PACK_NAME)
	[[ -d ~/s4c-local/share/$(PACK_NAME)/src ]] || mkdir ~/s4c-local/share/$(PACK_NAME)/src
	[[ -d ~/s4c-local/share/$(PACK_NAME)/demo-src ]] || mkdir ~/s4c-local/share/$(PACK_NAME)/demo-src
	[[ -d ~/s4c-local/share/$(PACK_NAME)/scripts ]] || mkdir ~/s4c-local/share/$(PACK_NAME)/scripts

	@echo -e "\033[1;32m[TREE] Removing '~/s4c-local/share/$(PACK_NAME).zip':\e[0m"
	touch ~/s4c-local/share/$(PACK_NAME).zip
	rm ~/s4c-local/share/$(PACK_NAME).zip
	@echo -e "\033[1;32m[TREE] Done.\e[0m"
	@echo -e "\033[1;35m[PACK] Installing:\e[0m"
	install $(TARGET) ~/s4c-local/share/$(PACK_NAME)
	install ./demofile.txt ~/s4c-local/share/$(PACK_NAME)
	install ./palette.gpl ~/s4c-local/share/$(PACK_NAME)
	install ./s4c-animate/animate.c ~/s4c-local/share/$(PACK_NAME)/src
	install ./s4c-animate/animate.h ~/s4c-local/share/$(PACK_NAME)/src
	install ./s4c-demo/demo.c ~/s4c-local/share/$(PACK_NAME)/demo-src
	install ./scripts/*.py ~/s4c-local/share/$(PACK_NAME)/scripts
	install ./requirements.txt ~/s4c-local/share/$(PACK_NAME)

	@echo -e "\033[1;35m[PACK] Done.\e[0m"
	@echo -e "\033[1;32m[ZIP] Compressing $(PACK_NAME):\e[0m"
	cd ~/s4c-local/share && zip -r $(PACK_NAME).zip ./$(PACK_NAME)
	@echo -e "\033[1;33m[ZIP] Testing zip:\e[0m"
	echo -e "\033[1;36m[UNZIP] Result:\n"
	unzip -t ~/s4c-local/share/$(PACK_NAME).zip | tail -n1
	@echo -e "\033[1;32m[ZIP] Done.\e[0m"
	@echo -e "\033[1;33mDone.\e[0m"

# Default target (builds everything)
all: $(TARGET)

# Target to clean and rebuild
rebuild: clean all

# By default, build the binary
.DEFAULT_GOAL := all
