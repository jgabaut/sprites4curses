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
TARGET_INSTALL_DIR = /usr
SOURCE_INSTALL_DIR = "."
INSTALLER_LOG_FILE = "./installer.log"
PACK_NAME = $(TARGET)-$(VERSION)-$(OS)-$(MACHINE)

# Source files
demo_animate_SOURCES = src/s4c.c s4c-animate/palette.c s4c-demo/demo_animate.c

# Lib source files
lib_SOURCES = src/s4c.c

# Linking rule
LDADD = $(S4C_LDFLAGS)

# Linker flag to strip symbols
AM_LDFLAGS = -s

# Compiler flags
AM_CFLAGS = $(S4C_CFLAGS) -O2 -Werror -Wpedantic -Wall

if S4C_RAYLIB_BUILD
AM_CFLAGS += -DS4C_RAYLIB_EXTENSION
else
endif

if S4C_EXPERIMENTAL_BUILD
AM_CFLAGS += -DS4C_EXPERIMENTAL
endif

if S4C_RL_QUIETER_BUILD
AM_CFLAGS += -DS4C_RL_QUIETER
endif

libs4c.o: $(lib_SOURCES)
	@echo -e "\033[1;35m[Makefile]\e[0m    Building \"$@\":"
	$(CCOMP) -c $(CFLAGS) $(AM_CFLAGS) -fPIC $< -o $@
	@echo -e "\033[1;33mDone.\e[0m"

$(SHARED_LIB): libs4c.o
	@echo -e "\033[1;35m[Makefile]\e[0m    Building \"$@\":"
	@echo -e "    \033[1;35mAM_CFLAGS\e[0m: [ \"\033[1;34m$(AM_CFLAGS)\e[0m\" ]"
	@echo -e "    \033[1;35mCFLAGS\e[0m: [ \"\033[1;34m$(CFLAGS)\e[0m\" ]"
	$(CCOMP) $(CFLAGS) $(AM_CFLAGS) -shared $< -o $@ $(LDADD)
	@echo -e "\033[1;33mDone.\e[0m"

libs4c.a: libs4c.o
	@echo -e "\033[1;35m[Makefile]\e[0m    Building \"$@\":"
	ar rcs $@ $<
	@echo -e "\033[1;33mDone.\e[0m"

# Build rule for object files
%.o: %.c
	$(CCOMP) -c $(CFLAGS) $(AM_CFLAGS) $< -o $@

# Build rule for the final binary
$(TARGET): $(demo_animate_SOURCES:.c=.o)
	@echo -e "    \033[1;35mAM_CFLAGS\e[0m: [ \"\033[1;34m$(AM_CFLAGS)\e[0m\" ]"
	@echo -e "    \033[1;35mLDADD\e[0m: [ \"\033[1;34m$(LDADD)\e[0m\" ]"
	$(CCOMP) $(CFLAGS) $(AM_CFLAGS) $(demo_animate_SOURCES:.c=.o) -o $@ $(LDADD) $(AM_LDFLAGS)

s4c-animate/palette.c:
	@echo -en "Generating \033[1;35mpalette.c\e[0m and \033[1;35mpalette.h\e[0m from [$(PALETTE_PATH)]:  "
	python -m s4c-scripts.s4c.core.palette C-header $(PALETTE_PATH) ../.. > s4c-animate/palette.h
	python -m s4c-scripts.s4c.core.palette C-impl $(PALETTE_PATH) ../.. > s4c-animate/palette.c
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
	-rm src/*.o
	-rm s4c-animate/*.o
	-rm s4c-animate/palette.h
	-rm s4c-animate/palette.c
	-rm s4c-demo/*.o
	-rm ./*.o
	-rm ./*.so
	-rm ./*.a
	-rm ./*.dll
	@echo -e "\033[1;33mDone.\e[0m"

cleanob:
	@echo -en "Cleaning object build artifacts:  "
	-rm src/*.o
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

init:
	@echo -e "\033[1;35m[Makefile] Initialising submodules.\e[0m"
	git submodule update --init
	@echo -e "\033[1;33mDone.\e[0m"

install: $(SHARED_LIB) doc
	@echo -en "Installing s4c lib $(VERSION):  "
	./installer-sh "-i" $(VERSION) $(TARGET_INSTALL_DIR) $(SOURCE_INSTALL_DIR) $(INSTALLER_LOG_FILE)
	ldconfig
	@echo -e "\n\033[1;33mDone.\e[0m"

# Default target (builds everything)
all: init $(TARGET) $(SHARED_LIB) libs4c.a

# Target to clean and rebuild
rebuild: clean all

# By default, build the binary
.DEFAULT_GOAL := all
