# Define the package name and version
AC_INIT([sprites4curses], [0.2.13], [jgabaut@github.com])

# Verify automake version and enable foreign option
AM_INIT_AUTOMAKE([foreign -Wall])

# Detect the host system and set PACK_PREFIX accordingly
AC_CANONICAL_HOST
echo "Host os:  $host_os"
AM_CONDITIONAL([OS_DARWIN], [test "$host_os" = "darwin"])
AM_CONDITIONAL([MINGW32_BUILD], [test "$host_os" = "mingw32"])

# Define the include and library paths based on the host system
if test "$host_os" = "mingw32"; then
  echo "Building for mingw32: [$host_cpu-$host_vendor-$host_os]"
  # mingw32 specific flags
  AC_SUBST([S4C_CFLAGS], ["-I/usr/x86_64-w64-mingw32/include -static -fstack-protector -DMINGW32_BUILD -DNCURSES_STATIC"])
  AC_SUBST([S4C_LDFLAGS], ["-L/usr/x86_64-w64-mingw32/lib -lncursesw"])
  AC_SUBST([CCOMP], ["/usr/bin/x86_64-w64-mingw32-gcc"])
  AC_SUBST([OS], ["w64-mingw32"])
  AC_SUBST([TARGET], ["demo.exe"])
fi
if test "$host_os" = "darwin"; then
  echo "Building for macos: [$host_cpu-$host_vendor-$host_os]"
  # macOS specific flags
  AC_SUBST([S4C_CFLAGS], ["-I/usr/local/opt/ncurses/include"])
  AC_SUBST([S4C_LDFLAGS], ["-L/usr/local/opt/ncurses/lib -lncurses"])
  AC_SUBST([OS], ["darwin"])
  AC_SUBST([TARGET], ["demo"])
fi
if test "$host_os" = "linux-gnu"; then
  echo "Building for Linux: [$host_cpu-$host_vendor-$host_os]"
  # Linux specific flags
  AC_SUBST([S4C_CFLAGS], [""])
  AC_SUBST([S4C_LDFLAGS], ["-lncurses"])
  AC_SUBST([OS], ["Linux"])
  AC_SUBST([TARGET], ["demo"])
fi

# Set a default version number if not specified externally
AC_ARG_VAR([VERSION], [Version number])
if test -z "$VERSION"; then
  VERSION="0.2.13"
fi

# Output variables to the config.h header
AC_DEFINE_UNQUOTED([VERSION], ["$VERSION"], [Version number])


AC_CHECK_PROGS([CCOMP], [gcc clang])
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_FUNCS([malloc calloc])

# Output the generated files (Makefile and config.h)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT