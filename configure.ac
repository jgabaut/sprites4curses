# Define the package name and version
AC_INIT([sprites4curses], [0.3.6], [jgabaut@github.com])

# Verify automake version and enable foreign option
AM_INIT_AUTOMAKE([foreign -Wall])

# Detect the host system and set PACK_PREFIX accordingly
AC_CANONICAL_HOST
build_linux=no
build_windows=no
build_mac=no
echo "Host os:  $host_os"

# Define the include and library paths based on the host system
case "${host_os}" in
    mingw*)
        echo "Building for mingw: [$host_cpu-$host_vendor-$host_os]"
        build_windows=yes
        # mingw32 specific flags
        AC_SUBST([S4C_CFLAGS], ["-I/usr/x86_64-w64-mingw32/include -static -fstack-protector -DNCURSES_STATIC"])
        AC_SUBST([S4C_LDFLAGS], ["-L/usr/x86_64-w64-mingw32/lib -lncursesw"])
        AC_SUBST([CCOMP], ["/usr/bin/x86_64-w64-mingw32-gcc"])
        AC_SUBST([OS], ["w64-mingw32"])
        AC_SUBST([TARGET], ["demo.exe"])
    ;;
    darwin*)
        echo "Building for macos: [$host_cpu-$host_vendor-$host_os]"
        build_mac=yes
        # macOS specific flags
        AC_SUBST([S4C_CFLAGS], ["-I/opt/homebrew/opt/ncurses/include"])
        AC_SUBST([S4C_LDFLAGS], ["-L/opt/homebrew/opt/ncurses/lib -lncurses"])
        AC_SUBST([OS], ["darwin"])
        AC_SUBST([TARGET], ["demo"])
    ;;
    linux*)
        echo "Building for Linux: [$host_cpu-$host_vendor-$host_os]"
        build_linux=yes
        # Linux specific flags
        AC_SUBST([S4C_CFLAGS], [""])
        AC_SUBST([S4C_LDFLAGS], ["-lncurses"])
        AC_SUBST([OS], ["Linux"])
        AC_SUBST([TARGET], ["demo"])
    ;;
esac

AM_CONDITIONAL([DARWIN_BUILD], [test "$build_mac" = "yes"])
AM_CONDITIONAL([WINDOWS_BUILD], [test "$build_windows" = "yes"])
AM_CONDITIONAL([LINUX_BUILD], [test "$build_linux" = "yes"])

# Set a default version number if not specified externally
AC_ARG_VAR([VERSION], [Version number])
if test -z "$VERSION"; then
  VERSION="0.3.6"
fi

# Output variables to the config.h header
AC_DEFINE_UNQUOTED([VERSION], ["$VERSION"], [Version number])


AC_CHECK_PROGS([CCOMP], [gcc clang])
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_FUNCS([malloc calloc])

# Output the generated files (Makefile and config.h)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
