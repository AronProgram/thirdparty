# generated automatically by aclocal 1.16.3 -*- Autoconf -*-

# Copyright (C) 1996-2020 Free Software Foundation, Inc.

# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

m4_ifndef([AC_CONFIG_MACRO_DIRS], [m4_defun([_AM_CONFIG_MACRO_DIRS], [])m4_defun([AC_CONFIG_MACRO_DIRS], [_AM_CONFIG_MACRO_DIRS($@)])])
dnl
dnl  This file is part of Bakefile (http://www.bakefile.org)
dnl
dnl  Copyright (C) 2003-2007 Vaclav Slavik, David Elliott and others
dnl
dnl  Permission is hereby granted, free of charge, to any person obtaining a
dnl  copy of this software and associated documentation files (the "Software"),
dnl  to deal in the Software without restriction, including without limitation
dnl  the rights to use, copy, modify, merge, publish, distribute, sublicense,
dnl  and/or sell copies of the Software, and to permit persons to whom the
dnl  Software is furnished to do so, subject to the following conditions:
dnl
dnl  The above copyright notice and this permission notice shall be included in
dnl  all copies or substantial portions of the Software.
dnl
dnl  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
dnl  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
dnl  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
dnl  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
dnl  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
dnl  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
dnl  DEALINGS IN THE SOFTWARE.
dnl
dnl  Compiler detection macros by David Elliott and Vadim Zeitlin
dnl


dnl ===========================================================================
dnl Macros to detect different C/C++ compilers
dnl ===========================================================================

dnl Based on autoconf _AC_LANG_COMPILER_GNU
dnl _AC_BAKEFILE_LANG_COMPILER(NAME, LANG, SYMBOL, IF-YES, IF-NO)
AC_DEFUN([_AC_BAKEFILE_LANG_COMPILER],
[
    AC_LANG_PUSH($2)
    AC_CACHE_CHECK(
        [whether we are using the $1 $2 compiler],
        [bakefile_cv_[]_AC_LANG_ABBREV[]_compiler_[]$3],
        [AC_TRY_COMPILE(
            [],
            [
             #ifndef $3
                choke me
             #endif
            ],
            [bakefile_cv_[]_AC_LANG_ABBREV[]_compiler_[]$3=yes],
            [bakefile_cv_[]_AC_LANG_ABBREV[]_compiler_[]$3=no]
         )
        ]
    )
    if test "x$bakefile_cv_[]_AC_LANG_ABBREV[]_compiler_[]$3" = "xyes"; then
        :; $4
    else
        :; $5
    fi
    AC_LANG_POP($2)
])

dnl More specific version of the above macro checking whether the compiler
dnl version is at least the given one (assumes that we do use this compiler)
dnl
dnl _AC_BAKEFILE_LANG_COMPILER_LATER_THAN(NAME, LANG, SYMBOL, VER, VERMSG, IF-YES, IF-NO)
AC_DEFUN([_AC_BAKEFILE_LANG_COMPILER_LATER_THAN],
[
    AC_LANG_PUSH($2)
    AC_CACHE_CHECK(
        [whether we are using $1 $2 compiler v$5 or later],
        [bakefile_cv_[]_AC_LANG_ABBREV[]_compiler_[]$3[]_lt_[]$4],
        [AC_TRY_COMPILE(
            [],
            [
             #ifndef $3 || $3 < $4
                choke me
             #endif
            ],
            [bakefile_cv_[]_AC_LANG_ABBREV[]_compiler_[]$3[]_lt_[]$4=yes],
            [bakefile_cv_[]_AC_LANG_ABBREV[]_compiler_[]$3[]_lt_[]$4=no]
         )
        ]
    )
    if test "x$bakefile_cv_[]_AC_LANG_ABBREV[]_compiler_[]$3[]_lt_[]$4" = "xyes"; then
        :; $6
    else
        :; $7
    fi
    AC_LANG_POP($2)
])

dnl IBM xlC compiler defines __xlC__ for both C and C++
AC_DEFUN([AC_BAKEFILE_PROG_XLCC],
[
    _AC_BAKEFILE_LANG_COMPILER([IBM xlC], C, __xlC__, XLCC=yes)
])

AC_DEFUN([AC_BAKEFILE_PROG_XLCXX],
[
    _AC_BAKEFILE_LANG_COMPILER([IBM xlC], C++, __xlC__, XLCXX=yes)
])

dnl recent versions of SGI mipsPro compiler define _SGI_COMPILER_VERSION
dnl
dnl NB: old versions define _COMPILER_VERSION but this could probably be
dnl     defined by other compilers too so don't test for it to be safe
AC_DEFUN([AC_BAKEFILE_PROG_SGICC],
[
    _AC_BAKEFILE_LANG_COMPILER(SGI, C, _SGI_COMPILER_VERSION, SGICC=yes)
])

AC_DEFUN([AC_BAKEFILE_PROG_SGICXX],
[
    _AC_BAKEFILE_LANG_COMPILER(SGI, C++, _SGI_COMPILER_VERSION, SGICXX=yes)
])

dnl Sun compiler defines __SUNPRO_C/__SUNPRO_CC
AC_DEFUN([AC_BAKEFILE_PROG_SUNCC],
[
    _AC_BAKEFILE_LANG_COMPILER(Sun, C, __SUNPRO_C, SUNCC=yes)
])

AC_DEFUN([AC_BAKEFILE_PROG_SUNCXX],
[
    _AC_BAKEFILE_LANG_COMPILER(Sun, C++, __SUNPRO_CC, SUNCXX=yes)
])

dnl Intel icc compiler defines __INTEL_COMPILER for both C and C++
AC_DEFUN([AC_BAKEFILE_PROG_INTELCC],
[
    _AC_BAKEFILE_LANG_COMPILER(Intel, C, __INTEL_COMPILER, INTELCC=yes)
])

AC_DEFUN([AC_BAKEFILE_PROG_INTELCXX],
[
    _AC_BAKEFILE_LANG_COMPILER(Intel, C++, __INTEL_COMPILER, INTELCXX=yes)
])

dnl Intel compiler command line options changed in incompatible ways sometimes
dnl before v8 (-KPIC was replaced with gcc-compatible -fPIC) and again in v10
dnl (-create-pch deprecated in favour of -pch-create) so we need to test for
dnl its exact version too
AC_DEFUN([AC_BAKEFILE_PROG_INTELCC_8],
[
    _AC_BAKEFILE_LANG_COMPILER_LATER_THAN(Intel, C, __INTEL_COMPILER, 800, 8, INTELCC8=yes)
])
AC_DEFUN([AC_BAKEFILE_PROG_INTELCXX_8],
[
    _AC_BAKEFILE_LANG_COMPILER_LATER_THAN(Intel, C++, __INTEL_COMPILER, 800, 8, INTELCXX8=yes)
])

AC_DEFUN([AC_BAKEFILE_PROG_INTELCC_10],
[
    _AC_BAKEFILE_LANG_COMPILER_LATER_THAN(Intel, C, __INTEL_COMPILER, 1000, 10, INTELCC10=yes)
])

AC_DEFUN([AC_BAKEFILE_PROG_INTELCXX_10],
[
    _AC_BAKEFILE_LANG_COMPILER_LATER_THAN(Intel, C++, __INTEL_COMPILER, 1000, 10, INTELCXX10=yes)
])

dnl HP-UX aCC: see http://docs.hp.com/en/6162/preprocess.htm#macropredef
AC_DEFUN([AC_BAKEFILE_PROG_HPCC],
[
    _AC_BAKEFILE_LANG_COMPILER(HP, C, __HP_cc, HPCC=yes)
])

AC_DEFUN([AC_BAKEFILE_PROG_HPCXX],
[
    _AC_BAKEFILE_LANG_COMPILER(HP, C++, __HP_aCC, HPCXX=yes)
])

dnl Tru64 cc and cxx
AC_DEFUN([AC_BAKEFILE_PROG_COMPAQCC],
[
    _AC_BAKEFILE_LANG_COMPILER(Compaq, C, __DECC, COMPAQCC=yes)
])

AC_DEFUN([AC_BAKEFILE_PROG_COMPAQCXX],
[
    _AC_BAKEFILE_LANG_COMPILER(Compaq, C++, __DECCXX, COMPAQCXX=yes)
])

dnl ===========================================================================
dnl Macros to do all of the compiler detections as one macro
dnl ===========================================================================

dnl check for different proprietary compilers depending on target platform
dnl _AC_BAKEFILE_PROG_COMPILER(LANG)
AC_DEFUN([_AC_BAKEFILE_PROG_COMPILER],
[
    AC_REQUIRE([AC_PROG_$1])

    dnl Intel compiler can be used under several different OS and even
    dnl different architectures (x86, amd64 and Itanium) so it's easier to just
    dnl always test for it
    AC_BAKEFILE_PROG_INTEL$1

    dnl If we use Intel compiler we also need to know its version
    if test "$INTEL$1" = "yes"; then
        AC_BAKEFILE_PROG_INTEL$1_8
        AC_BAKEFILE_PROG_INTEL$1_10
    fi

    dnl if we're using gcc, we can't be using any of incompatible compilers
    if test "x$G$1" != "xyes"; then
        dnl most of these compilers are only used under well-defined OS so
        dnl don't waste time checking for them on other ones
        case `uname -s` in
            AIX*)
                AC_BAKEFILE_PROG_XL$1
                ;;

            Darwin)
                AC_BAKEFILE_PROG_XL$1
                ;;

            IRIX*)
                AC_BAKEFILE_PROG_SGI$1
                ;;

            Linux*)
                dnl Sun CC is now available under Linux too, test for it unless
                dnl we already found that we were using a different compiler
                if test "$INTEL$1" != "yes"; then
                    AC_BAKEFILE_PROG_SUN$1
                fi
                ;;

            HP-UX*)
                AC_BAKEFILE_PROG_HP$1
                ;;

            OSF1)
                AC_BAKEFILE_PROG_COMPAQ$1
                ;;

            SunOS)
                AC_BAKEFILE_PROG_SUN$1
                ;;
        esac
    fi
])

AC_DEFUN([AC_BAKEFILE_PROG_CC],
[
    _AC_BAKEFILE_PROG_COMPILER(CC)
])

AC_DEFUN([AC_BAKEFILE_PROG_CXX],
[
    _AC_BAKEFILE_PROG_COMPILER(CXX)
])


dnl
dnl  This file is part of Bakefile (http://www.bakefile.org)
dnl
dnl  Copyright (C) 2003-2007 Vaclav Slavik and others
dnl
dnl  Permission is hereby granted, free of charge, to any person obtaining a
dnl  copy of this software and associated documentation files (the "Software"),
dnl  to deal in the Software without restriction, including without limitation
dnl  the rights to use, copy, modify, merge, publish, distribute, sublicense,
dnl  and/or sell copies of the Software, and to permit persons to whom the
dnl  Software is furnished to do so, subject to the following conditions:
dnl
dnl  The above copyright notice and this permission notice shall be included in
dnl  all copies or substantial portions of the Software.
dnl
dnl  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
dnl  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
dnl  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
dnl  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
dnl  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
dnl  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
dnl  DEALINGS IN THE SOFTWARE.
dnl
dnl  Support macros for makefiles generated by BAKEFILE.
dnl


dnl ---------------------------------------------------------------------------
dnl Lots of compiler & linker detection code contained here was taken from
dnl wxWidgets configure.in script (see https://www.wxwidgets.org)
dnl ---------------------------------------------------------------------------



dnl ---------------------------------------------------------------------------
dnl AC_BAKEFILE_GNUMAKE
dnl
dnl Detects GNU make
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE_GNUMAKE],
[
    dnl does make support "-include" (only GNU make does AFAIK)?
    AC_CACHE_CHECK([if make is GNU make], bakefile_cv_prog_makeisgnu,
    [
        if ( ${SHELL-sh} -c "${MAKE-make} --version" 2> /dev/null |
                egrep -s GNU > /dev/null); then
            bakefile_cv_prog_makeisgnu="yes"
        else
            bakefile_cv_prog_makeisgnu="no"
        fi
    ])

    if test "x$bakefile_cv_prog_makeisgnu" = "xyes"; then
        IF_GNU_MAKE=""
    else
        IF_GNU_MAKE="#"
    fi
    AC_SUBST(IF_GNU_MAKE)
])

dnl ---------------------------------------------------------------------------
dnl AC_BAKEFILE_PLATFORM
dnl
dnl Detects platform and sets PLATFORM_XXX variables accordingly
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE_PLATFORM],
[
    PLATFORM_UNIX=0
    PLATFORM_WIN32=0
    PLATFORM_MAC=0
    PLATFORM_MACOS=0
    PLATFORM_MACOSX=0
    PLATFORM_BEOS=0

    if test "x$BAKEFILE_FORCE_PLATFORM" = "x"; then
        case "${BAKEFILE_HOST}" in
            *-*-mingw32* )
                PLATFORM_WIN32=1
            ;;
            *-*-darwin* )
                PLATFORM_MAC=1
                PLATFORM_MACOSX=1
            ;;
            *-*-beos* )
                PLATFORM_BEOS=1
            ;;
            powerpc-apple-macos* )
                PLATFORM_MAC=1
                PLATFORM_MACOS=1
            ;;
            * )
                PLATFORM_UNIX=1
            ;;
        esac
    else
        case "$BAKEFILE_FORCE_PLATFORM" in
            win32 )
                PLATFORM_WIN32=1
            ;;
            darwin )
                PLATFORM_MAC=1
                PLATFORM_MACOSX=1
            ;;
            unix )
                PLATFORM_UNIX=1
            ;;
            beos )
                PLATFORM_BEOS=1
            ;;
            * )
                AC_MSG_ERROR([Unknown platform: $BAKEFILE_FORCE_PLATFORM])
            ;;
        esac
    fi

    AC_SUBST(PLATFORM_UNIX)
    AC_SUBST(PLATFORM_WIN32)
    AC_SUBST(PLATFORM_MAC)
    AC_SUBST(PLATFORM_MACOS)
    AC_SUBST(PLATFORM_MACOSX)
    AC_SUBST(PLATFORM_BEOS)
])


dnl ---------------------------------------------------------------------------
dnl AC_BAKEFILE_PLATFORM_SPECIFICS
dnl
dnl Sets misc platform-specific settings
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE_PLATFORM_SPECIFICS],
[
    case "${BAKEFILE_HOST}" in
      *-*-darwin* )
        dnl For Unix to MacOS X porting instructions, see:
        dnl http://fink.sourceforge.net/doc/porting/porting.html
        if test "x$GCC" = "xyes"; then
            CFLAGS="$CFLAGS -fno-common"
            CXXFLAGS="$CXXFLAGS -fno-common"
        fi
        if test "x$XLCC" = "xyes"; then
            CFLAGS="$CFLAGS -qnocommon"
            CXXFLAGS="$CXXFLAGS -qnocommon"
        fi
        ;;

      i*86-*-beos* )
        LDFLAGS="-L/boot/develop/lib/x86 $LDFLAGS"
        ;;
    esac
])

dnl ---------------------------------------------------------------------------
dnl AC_BAKEFILE_SUFFIXES
dnl
dnl Detects shared various suffixes for shared libraries, libraries, programs,
dnl plugins etc.
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE_SUFFIXES],
[
    SO_SUFFIX="so"
    SO_SUFFIX_MODULE="so"
    EXEEXT=""
    LIBPREFIX="lib"
    LIBEXT=".a"
    DLLPREFIX="lib"
    DLLPREFIX_MODULE=""
    DLLIMP_SUFFIX=""
    dlldir="$libdir"

    case "${BAKEFILE_HOST}" in
        dnl PA-RISC HP systems used .sl but IA64 use ELF-64 and so use the
        dnl standard .so extension
        ia64-hp-hpux* )
        ;;
        *-hp-hpux* )
            SO_SUFFIX="sl"
            SO_SUFFIX_MODULE="sl"
        ;;
        *-*-aix* )
            dnl quoting from
            dnl http://www-1.ibm.com/servers/esdd/articles/gnu.html:
            dnl     Both archive libraries and shared libraries on AIX have an
            dnl     .a extension. This will explain why you can't link with an
            dnl     .so and why it works with the name changed to .a.
            SO_SUFFIX="a"
            SO_SUFFIX_MODULE="a"
        ;;
        *-*-cygwin* )
            SO_SUFFIX="dll"
            SO_SUFFIX_MODULE="dll"
            DLLIMP_SUFFIX="dll.a"
            EXEEXT=".exe"
            DLLPREFIX="cyg"
            dlldir="$bindir"
        ;;
        *-*-mingw32* )
            SO_SUFFIX="dll"
            SO_SUFFIX_MODULE="dll"
            DLLIMP_SUFFIX="dll.a"
            EXEEXT=".exe"
            DLLPREFIX=""
            dlldir="$bindir"
        ;;
        *-*-darwin* )
            SO_SUFFIX="dylib"
            SO_SUFFIX_MODULE="bundle"
        ;;
    esac

    if test "x$DLLIMP_SUFFIX" = "x" ; then
        DLLIMP_SUFFIX="$SO_SUFFIX"
    fi

    AC_SUBST(SO_SUFFIX)
    AC_SUBST(SO_SUFFIX_MODULE)
    AC_SUBST(DLLIMP_SUFFIX)
    AC_SUBST(EXEEXT)
    AC_SUBST(LIBPREFIX)
    AC_SUBST(LIBEXT)
    AC_SUBST(DLLPREFIX)
    AC_SUBST(DLLPREFIX_MODULE)
    AC_SUBST(dlldir)
])


dnl ---------------------------------------------------------------------------
dnl AC_BAKEFILE_SHARED_LD
dnl
dnl Detects command for making shared libraries, substitutes SHARED_LD_CC
dnl and SHARED_LD_CXX.
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE_SHARED_LD],
[
    dnl the extra compiler flags needed for compilation of shared library
    PIC_FLAG=""
    if test "x$GCC" = "xyes"; then
        dnl the switch for gcc is the same under all platforms
        PIC_FLAG="-fPIC"
    fi

    dnl Defaults for GCC and ELF .so shared libs:
    SHARED_LD_CC="\$(CC) -shared ${PIC_FLAG} -o"
    SHARED_LD_CXX="\$(CXX) -shared ${PIC_FLAG} -o"
    WINDOWS_IMPLIB=0

    case "${BAKEFILE_HOST}" in
      *-hp-hpux* )
        dnl default settings are good for gcc but not for the native HP-UX
        if test "x$GCC" != "xyes"; then
            dnl no idea why it wants it, but it does
            LDFLAGS="$LDFLAGS -L/usr/lib"

            SHARED_LD_CC="${CC} -b -o"
            SHARED_LD_CXX="${CXX} -b -o"
            PIC_FLAG="+Z"
        fi
      ;;

      *-*-linux* )
        dnl newer icc versions use -fPIC just as gcc does and, in fact, the
        dnl newest (v10+) ones don't even understand -KPIC any longer
        if test "$INTELCC" = "yes" -a "$INTELCC8" != "yes"; then
            PIC_FLAG="-KPIC"
        elif test "x$SUNCXX" = "xyes"; then
            SHARED_LD_CC="${CC} -G -o"
            SHARED_LD_CXX="${CXX} -G -o"
            PIC_FLAG="-KPIC"
        fi
      ;;

      *-*-solaris2* )
        if test "x$SUNCXX" = xyes ; then
            SHARED_LD_CC="${CC} -G -o"
            SHARED_LD_CXX="${CXX} -G -o"
            PIC_FLAG="-KPIC"
        fi
      ;;

      *-*-darwin* )
        AC_BAKEFILE_CREATE_FILE_SHARED_LD_SH
        chmod +x shared-ld-sh

        SHARED_LD_MODULE_CC="`pwd`/shared-ld-sh -bundle -headerpad_max_install_names -o"
        SHARED_LD_MODULE_CXX="CXX=\"\$(CXX)\" $SHARED_LD_MODULE_CC"

        dnl Most apps benefit from being fully binded (its faster and static
        dnl variables initialized at startup work).
        dnl This can be done either with the exe linker flag -Wl,-bind_at_load
        dnl or with a double stage link in order to create a single module
        dnl "-init _wxWindowsDylibInit" not useful with lazy linking solved

        dnl If using newer dev tools then there is a -single_module flag that
        dnl we can use to do this for dylibs, otherwise we'll need to use a helper
        dnl script.  Check the version of gcc to see which way we can go:
        AC_CACHE_CHECK([for gcc 3.1 or later], bakefile_cv_gcc31, [
           AC_TRY_COMPILE([],
               [
                   #if (__GNUC__ < 3) || \
                       ((__GNUC__ == 3) && (__GNUC_MINOR__ < 1))
                       This is old gcc
                   #endif
               ],
               [
                   bakefile_cv_gcc31=yes
               ],
               [
                   bakefile_cv_gcc31=no
               ]
           )
        ])
        if test "$bakefile_cv_gcc31" = "no"; then
            dnl Use the shared-ld-sh helper script
            SHARED_LD_CC="`pwd`/shared-ld-sh -dynamiclib -headerpad_max_install_names -o"
            SHARED_LD_CXX="$SHARED_LD_CC"
        else
            dnl Use the -single_module flag and let the linker do it for us
            SHARED_LD_CC="\${CC} -dynamiclib -single_module -headerpad_max_install_names -o"
            SHARED_LD_CXX="\${CXX} -dynamiclib -single_module -headerpad_max_install_names -o"
        fi

        if test "x$GCC" == "xyes"; then
            PIC_FLAG="-dynamic -fPIC"
        fi
        if test "x$XLCC" = "xyes"; then
            PIC_FLAG="-dynamic -DPIC"
        fi
      ;;

      *-*-aix* )
        if test "x$GCC" = "xyes"; then
            dnl at least gcc 2.95 warns that -fPIC is ignored when
            dnl compiling each and every file under AIX which is annoying,
            dnl so don't use it there (it's useless as AIX runs on
            dnl position-independent architectures only anyhow)
            PIC_FLAG=""

            dnl -bexpfull is needed by AIX linker to export all symbols (by
            dnl default it doesn't export any and even with -bexpall it
            dnl doesn't export all C++ support symbols, e.g. vtable
            dnl pointers) but it's only available starting from 5.1 (with
            dnl maintenance pack 2, whatever this is), see
            dnl http://www-128.ibm.com/developerworks/eserver/articles/gnu.html
            case "${BAKEFILE_HOST}" in
                *-*-aix5* )
                    LD_EXPFULL="-Wl,-bexpfull"
                    ;;
            esac

            SHARED_LD_CC="\$(CC) -shared $LD_EXPFULL -o"
            SHARED_LD_CXX="\$(CXX) -shared $LD_EXPFULL -o"
        else
            dnl FIXME: makeC++SharedLib is obsolete, what should we do for
            dnl        recent AIX versions?
            AC_CHECK_PROG(AIX_CXX_LD, makeC++SharedLib,
                          makeC++SharedLib, /usr/lpp/xlC/bin/makeC++SharedLib)
            SHARED_LD_CC="$AIX_CC_LD -p 0 -o"
            SHARED_LD_CXX="$AIX_CXX_LD -p 0 -o"
        fi
      ;;

      *-*-beos* )
        dnl can't use gcc under BeOS for shared library creation because it
        dnl complains about missing 'main'
        SHARED_LD_CC="${LD} -nostart -o"
        SHARED_LD_CXX="${LD} -nostart -o"
      ;;

      *-*-irix* )
        dnl default settings are ok for gcc
        if test "x$GCC" != "xyes"; then
            PIC_FLAG="-KPIC"
        fi
      ;;

      *-*-cygwin* | *-*-mingw32* )
        PIC_FLAG=""
        SHARED_LD_CC="\$(CC) -shared -o"
        SHARED_LD_CXX="\$(CXX) -shared -o"
        WINDOWS_IMPLIB=1
      ;;

      powerpc-apple-macos* | \
      *-*-freebsd* | *-*-openbsd* | *-*-netbsd* | *-*-gnu* | *-*-k*bsd*-gnu | \
      *-*-mirbsd* | \
      *-*-sunos4* | \
      *-*-osf* | \
      *-*-dgux5* | \
      *-*-sysv5* )
        dnl defaults are ok
      ;;

      *)
        AC_MSG_ERROR(unknown system type $BAKEFILE_HOST.)
    esac

    if test "x$PIC_FLAG" != "x" ; then
        PIC_FLAG="$PIC_FLAG -DPIC"
    fi

    if test "x$SHARED_LD_MODULE_CC" = "x" ; then
        SHARED_LD_MODULE_CC="$SHARED_LD_CC"
    fi
    if test "x$SHARED_LD_MODULE_CXX" = "x" ; then
        SHARED_LD_MODULE_CXX="$SHARED_LD_CXX"
    fi

    AC_SUBST(SHARED_LD_CC)
    AC_SUBST(SHARED_LD_CXX)
    AC_SUBST(SHARED_LD_MODULE_CC)
    AC_SUBST(SHARED_LD_MODULE_CXX)
    AC_SUBST(PIC_FLAG)
    AC_SUBST(WINDOWS_IMPLIB)
])


dnl ---------------------------------------------------------------------------
dnl AC_BAKEFILE_SHARED_VERSIONS
dnl
dnl Detects linker options for attaching versions (sonames) to shared  libs.
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE_SHARED_VERSIONS],
[
    USE_SOVERSION=0
    USE_SOVERLINUX=0
    USE_SOVERSOLARIS=0
    USE_SOVERCYGWIN=0
    USE_SOTWOSYMLINKS=0
    USE_MACVERSION=0
    SONAME_FLAG=

    case "${BAKEFILE_HOST}" in
      *-*-linux* | *-*-freebsd* | *-*-openbsd* | *-*-netbsd* | \
      *-*-k*bsd*-gnu | *-*-mirbsd* | *-*-gnu* )
        if test "x$SUNCXX" = "xyes"; then
            SONAME_FLAG="-h "
        else
            SONAME_FLAG="-Wl,-soname,"
        fi
        USE_SOVERSION=1
        USE_SOVERLINUX=1
        USE_SOTWOSYMLINKS=1
      ;;

      *-*-solaris2* )
        SONAME_FLAG="-h "
        USE_SOVERSION=1
        USE_SOVERSOLARIS=1
      ;;

      *-*-darwin* )
        USE_MACVERSION=1
        USE_SOVERSION=1
        USE_SOTWOSYMLINKS=1
      ;;

      *-*-cygwin* )
        USE_SOVERSION=1
        USE_SOVERCYGWIN=1
      ;;
    esac

    AC_SUBST(USE_SOVERSION)
    AC_SUBST(USE_SOVERLINUX)
    AC_SUBST(USE_SOVERSOLARIS)
    AC_SUBST(USE_SOVERCYGWIN)
    AC_SUBST(USE_MACVERSION)
    AC_SUBST(USE_SOTWOSYMLINKS)
    AC_SUBST(SONAME_FLAG)
])


dnl ---------------------------------------------------------------------------
dnl AC_BAKEFILE_DEPS
dnl
dnl Detects available C/C++ dependency tracking options
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE_DEPS],
[
    AC_ARG_ENABLE([dependency-tracking],
                  AS_HELP_STRING([--disable-dependency-tracking],
                                 [don't use dependency tracking even if the compiler can]),
                  [bk_use_trackdeps="$enableval"])

    AC_MSG_CHECKING([for dependency tracking method])

    BK_DEPS=""
    if test "x$bk_use_trackdeps" = "xno" ; then
        DEPS_TRACKING=0
        AC_MSG_RESULT([disabled])
    else
        DEPS_TRACKING=1

        if test "x$GCC" = "xyes"; then
            DEPSMODE=gcc
            DEPSFLAG="-MMD"
            AC_MSG_RESULT([gcc])
        elif test "x$SUNCC" = "xyes"; then
            DEPSMODE=unixcc
            DEPSFLAG="-xM1"
            AC_MSG_RESULT([Sun cc])
        elif test "x$SGICC" = "xyes"; then
            DEPSMODE=unixcc
            DEPSFLAG="-M"
            AC_MSG_RESULT([SGI cc])
        elif test "x$HPCC" = "xyes"; then
            DEPSMODE=unixcc
            DEPSFLAG="+make"
            AC_MSG_RESULT([HP cc])
        elif test "x$COMPAQCC" = "xyes"; then
            DEPSMODE=gcc
            DEPSFLAG="-MD"
            AC_MSG_RESULT([Compaq cc])
        else
            DEPS_TRACKING=0
            AC_MSG_RESULT([none])
        fi

        if test $DEPS_TRACKING = 1 ; then
            AC_BAKEFILE_CREATE_FILE_BK_DEPS
            chmod +x bk-deps
            dnl FIXME: make this $(top_builddir)/bk-deps once autoconf-2.60
            dnl        is required (and so top_builddir is never empty):
            BK_DEPS="`pwd`/bk-deps"
        fi
    fi

    AC_SUBST(DEPS_TRACKING)
    AC_SUBST(BK_DEPS)
])

dnl ---------------------------------------------------------------------------
dnl AC_BAKEFILE_CHECK_BASIC_STUFF
dnl
dnl Checks for presence of basic programs, such as C and C++ compiler, "ranlib"
dnl or "install"
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE_CHECK_BASIC_STUFF],
[
    AC_PROG_RANLIB
    AC_PROG_INSTALL
    AC_PROG_LN_S

    AC_PROG_MAKE_SET
    AC_SUBST(MAKE_SET)

    if test "x$SUNCXX" = "xyes"; then
        dnl Sun C++ compiler requires special way of creating static libs;
        dnl see here for more details:
        dnl https://sourceforge.net/tracker/?func=detail&atid=109863&aid=1229751&group_id=9863
        AR=$CXX
        AROPTIONS="-xar -o"
        AC_SUBST(AR)
    elif test "x$SGICC" = "xyes"; then
        dnl Almost the same as above for SGI mipsPro compiler
        AR=$CXX
        AROPTIONS="-ar -o"
        AC_SUBST(AR)
    else
        AC_CHECK_TOOL(AR, ar, ar)
        AROPTIONS=rc
    fi
    AC_SUBST(AROPTIONS)

    AC_CHECK_TOOL(STRIP, strip, :)
    AC_CHECK_TOOL(NM, nm, :)

    dnl Don't use `install -d`, see https://trac.wxwidgets.org/ticket/13452
    INSTALL_DIR="mkdir -p"
    AC_SUBST(INSTALL_DIR)

    LDFLAGS_GUI=
    case ${BAKEFILE_HOST} in
        *-*-cygwin* | *-*-mingw32* )
        LDFLAGS_GUI="-mwindows"
    esac
    AC_SUBST(LDFLAGS_GUI)
])


dnl ---------------------------------------------------------------------------
dnl AC_BAKEFILE_RES_COMPILERS
dnl
dnl Checks for presence of resource compilers for win32 or mac
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE_RES_COMPILERS],
[
    case ${BAKEFILE_HOST} in
        *-*-cygwin* | *-*-mingw32* )
            dnl Check for win32 resources compiler:
            AC_CHECK_TOOL(WINDRES, windres)
         ;;
    esac

    AC_SUBST(WINDRES)
])

dnl ---------------------------------------------------------------------------
dnl AC_BAKEFILE_PRECOMP_HEADERS
dnl
dnl Check for precompiled headers support (GCC >= 3.4)
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE_PRECOMP_HEADERS],
[

    AC_ARG_ENABLE([precomp-headers],
                  AS_HELP_STRING([--disable-precomp-headers],
                                 [don't use precompiled headers even if compiler can]),
                  [bk_use_pch="$enableval"])

    GCC_PCH=0
    ICC_PCH=0
    USE_PCH=0
    BK_MAKE_PCH=""

    case ${BAKEFILE_HOST} in
        *-*-cygwin* )
            dnl PCH support is broken in cygwin gcc because of unportable
            dnl assumptions about mmap() in gcc code which make PCH generation
            dnl fail erratically; disable PCH completely until this is fixed
            bk_use_pch="no"
            ;;
    esac

    if test "x$bk_use_pch" = "x" -o "x$bk_use_pch" = "xyes" ; then
        if test "x$GCC" = "xyes"; then
            dnl test if we have gcc-3.4:
            AC_MSG_CHECKING([if the compiler supports precompiled headers])
            AC_TRY_COMPILE([],
                [
                    #if !defined(__GNUC__) || !defined(__GNUC_MINOR__)
                        There is no PCH support
                    #endif
                    #if (__GNUC__ < 3)
                        There is no PCH support
                    #endif
                    #if (__GNUC__ == 3) && \
                       ((!defined(__APPLE_CC__) && (__GNUC_MINOR__ < 4)) || \
                       ( defined(__APPLE_CC__) && (__GNUC_MINOR__ < 3))) || \
                       ( defined(__INTEL_COMPILER) )
                        There is no PCH support
                    #endif
                ],
                [
                    AC_MSG_RESULT([yes])
                    GCC_PCH=1
                ],
                [
                    if test "$INTELCXX8" = "yes"; then
                        AC_MSG_RESULT([yes])
                        ICC_PCH=1
                        if test "$INTELCXX10" = "yes"; then
                            ICC_PCH_CREATE_SWITCH="-pch-create"
                            ICC_PCH_USE_SWITCH="-pch-use"
                        else
                            ICC_PCH_CREATE_SWITCH="-create-pch"
                            ICC_PCH_USE_SWITCH="-use-pch"
                        fi
                    else
                        AC_MSG_RESULT([no])
                    fi
                ])
            if test $GCC_PCH = 1 -o $ICC_PCH = 1 ; then
                USE_PCH=1
                AC_BAKEFILE_CREATE_FILE_BK_MAKE_PCH
                chmod +x bk-make-pch
                dnl FIXME: make this $(top_builddir)/bk-make-pch once
                dnl        autoconf-2.60 is required (and so top_builddir is
                dnl        never empty):
                BK_MAKE_PCH="`pwd`/bk-make-pch"
            fi
        fi
    fi

    AC_SUBST(GCC_PCH)
    AC_SUBST(ICC_PCH)
    AC_SUBST(ICC_PCH_CREATE_SWITCH)
    AC_SUBST(ICC_PCH_USE_SWITCH)
    AC_SUBST(BK_MAKE_PCH)
])



dnl ---------------------------------------------------------------------------
dnl AC_BAKEFILE([autoconf_inc.m4 inclusion])
dnl
dnl To be used in configure.in of any project using Bakefile-generated mks
dnl
dnl Behaviour can be modified by setting following variables:
dnl    BAKEFILE_CHECK_BASICS    set to "no" if you don't want bakefile to
dnl                             to perform check for basic tools like ranlib
dnl    BAKEFILE_HOST            set this to override host detection, defaults
dnl                             to ${host}
dnl    BAKEFILE_FORCE_PLATFORM  set to override platform detection
dnl
dnl Example usage:
dnl
dnl   AC_BAKEFILE([FOO(autoconf_inc.m4)])
dnl
dnl (replace FOO with m4_include above, aclocal would die otherwise)
dnl (yes, it's ugly, but thanks to a bug in aclocal, it's the only thing
dnl we can do...)
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE],
[
    AC_PREREQ([2.58])

    dnl We need to always run C/C++ compiler tests, but it's also possible
    dnl for the user to call these macros manually, hence this instead of
    dnl simply calling these macros. See http://www.bakefile.org/ticket/64
    AC_REQUIRE([AC_BAKEFILE_PROG_CC])
    AC_REQUIRE([AC_BAKEFILE_PROG_CXX])

    if test "x$BAKEFILE_HOST" = "x"; then
               if test "x${host}" = "x" ; then
                       AC_MSG_ERROR([You must call the autoconf "CANONICAL_HOST" macro in your configure.ac (or .in) file.])
               fi

        BAKEFILE_HOST="${host}"
    fi

    if test "x$BAKEFILE_CHECK_BASICS" != "xno"; then
        AC_BAKEFILE_CHECK_BASIC_STUFF
    fi
    AC_BAKEFILE_GNUMAKE
    AC_BAKEFILE_PLATFORM
    AC_BAKEFILE_PLATFORM_SPECIFICS
    AC_BAKEFILE_SUFFIXES
    AC_BAKEFILE_SHARED_LD
    AC_BAKEFILE_SHARED_VERSIONS
    AC_BAKEFILE_DEPS
    AC_BAKEFILE_RES_COMPILERS

    dnl OBJCFLAGS is set by Autoconf, but OBJCXXFLAGS is not:
    AC_SUBST(OBJCXXFLAGS)


    BAKEFILE_BAKEFILE_M4_VERSION="0.2.11"

    dnl includes autoconf_inc.m4:
    $1

    if test "$BAKEFILE_AUTOCONF_INC_M4_VERSION" = "" ; then
        AC_MSG_ERROR([No version found in autoconf_inc.m4 - bakefile macro was changed to take additional argument, perhaps configure.in wasn't updated (see the documentation)?])
    fi

    if test "$BAKEFILE_BAKEFILE_M4_VERSION" != "$BAKEFILE_AUTOCONF_INC_M4_VERSION" ; then
        AC_MSG_ERROR([Versions of Bakefile used to generate makefiles ($BAKEFILE_AUTOCONF_INC_M4_VERSION) and configure ($BAKEFILE_BAKEFILE_M4_VERSION) do not match.])
    fi
])


dnl ---------------------------------------------------------------------------
dnl              Embedded copies of helper scripts follow:
dnl ---------------------------------------------------------------------------

AC_DEFUN([AC_BAKEFILE_CREATE_FILE_BK_DEPS],
[
dnl ===================== bk-deps begins here =====================
dnl    (Created by merge-scripts.py from bk-deps
dnl     file do not edit here!)
D='$'
cat <<EOF >bk-deps
#!/bin/sh

# This script is part of Bakefile (http://www.bakefile.org) autoconf
# script. It is used to track C/C++ files dependencies in portable way.
#
# Permission is given to use this file in any way.

DEPSMODE=${DEPSMODE}
DEPSFLAG="${DEPSFLAG}"
DEPSDIRBASE=.deps

if test ${D}DEPSMODE = gcc ; then
    ${D}* ${D}{DEPSFLAG}
    status=${D}?

    # determine location of created files:
    while test ${D}# -gt 0; do
        case "${D}1" in
            -o )
                shift
                objfile=${D}1
            ;;
            -* )
            ;;
            * )
                srcfile=${D}1
            ;;
        esac
        shift
    done
    objfilebase=\`basename ${D}objfile\`
    builddir=\`dirname ${D}objfile\`
    depfile=\`basename ${D}srcfile | sed -e 's/\\..*${D}/.d/g'\`
    depobjname=\`echo ${D}depfile |sed -e 's/\\.d/.o/g'\`
    depsdir=${D}builddir/${D}DEPSDIRBASE
    mkdir -p ${D}depsdir

    # if the compiler failed, we're done:
    if test ${D}{status} != 0 ; then
        rm -f ${D}depfile
        exit ${D}{status}
    fi

    # move created file to the location we want it in:
    if test -f ${D}depfile ; then
        sed -e "s,${D}depobjname:,${D}objfile:,g" ${D}depfile >${D}{depsdir}/${D}{objfilebase}.d
        rm -f ${D}depfile
    else
        # "g++ -MMD -o fooobj.o foosrc.cpp" produces fooobj.d
        depfile=\`echo "${D}objfile" | sed -e 's/\\..*${D}/.d/g'\`
        if test ! -f ${D}depfile ; then
            # "cxx -MD -o fooobj.o foosrc.cpp" creates fooobj.o.d (Compaq C++)
            depfile="${D}objfile.d"
        fi
        if test -f ${D}depfile ; then
            sed -e "\\,^${D}objfile,!s,${D}depobjname:,${D}objfile:,g" ${D}depfile >${D}{depsdir}/${D}{objfilebase}.d
            rm -f ${D}depfile
        fi
    fi
    exit 0

elif test ${D}DEPSMODE = unixcc; then
    ${D}* || exit ${D}?
    # Run compiler again with deps flag and redirect into the dep file.
    # It doesn't work if the '-o FILE' option is used, but without it the
    # dependency file will contain the wrong name for the object. So it is
    # removed from the command line, and the dep file is fixed with sed.
    cmd=""
    while test ${D}# -gt 0; do
        case "${D}1" in
            -o )
                shift
                objfile=${D}1
            ;;
            * )
                eval arg${D}#=\\${D}1
                cmd="${D}cmd \\${D}arg${D}#"
            ;;
        esac
        shift
    done

    objfilebase=\`basename ${D}objfile\`
    builddir=\`dirname ${D}objfile\`
    depsdir=${D}builddir/${D}DEPSDIRBASE
    mkdir -p ${D}depsdir

    eval "${D}cmd ${D}DEPSFLAG" | sed "s|.*:|${D}objfile:|" >${D}{depsdir}/${D}{objfilebase}.d
    exit 0

else
    ${D}*
    exit ${D}?
fi
EOF
dnl ===================== bk-deps ends here =====================
])

AC_DEFUN([AC_BAKEFILE_CREATE_FILE_SHARED_LD_SH],
[
dnl ===================== shared-ld-sh begins here =====================
dnl    (Created by merge-scripts.py from shared-ld-sh
dnl     file do not edit here!)
D='$'
cat <<EOF >shared-ld-sh
#!/bin/sh
#-----------------------------------------------------------------------------
#-- Name:        distrib/mac/shared-ld-sh
#-- Purpose:     Link a mach-o dynamic shared library for Darwin / Mac OS X
#-- Author:      Gilles Depeyrot
#-- Copyright:   (c) 2002 Gilles Depeyrot
#-- Licence:     any use permitted
#-----------------------------------------------------------------------------

verbose=0
args=""
objects=""
linking_flag="-dynamiclib"
ldargs="-r -keep_private_externs -nostdlib"

if test "x${D}CXX" = "x"; then
    CXX="c++"
fi

while test ${D}# -gt 0; do
    case ${D}1 in

       -v)
        verbose=1
        ;;

       -o|-compatibility_version|-current_version|-framework|-undefined|-install_name)
        # collect these options and values
        args="${D}{args} ${D}1 ${D}2"
        shift
        ;;

       -arch|-isysroot)
        # collect these options and values
        ldargs="${D}{ldargs} ${D}1 ${D}2"
        shift
        ;;

       -s|-Wl,*)
        # collect these load args
        ldargs="${D}{ldargs} ${D}1"
        ;;

       -l*|-L*|-flat_namespace|-headerpad_max_install_names)
        # collect these options
        args="${D}{args} ${D}1"
        ;;

       -dynamiclib|-bundle)
        linking_flag="${D}1"
        ;;

       -*)
        echo "shared-ld: unhandled option '${D}1'"
        exit 1
        ;;

        *.o | *.a | *.dylib)
        # collect object files
        objects="${D}{objects} ${D}1"
        ;;

        *)
        echo "shared-ld: unhandled argument '${D}1'"
        exit 1
        ;;

    esac
    shift
done

status=0

#
# Link one module containing all the others
#
if test ${D}{verbose} = 1; then
    echo "${D}CXX ${D}{ldargs} ${D}{objects} -o master.${D}${D}.o"
fi
${D}CXX ${D}{ldargs} ${D}{objects} -o master.${D}${D}.o
status=${D}?

#
# Link the shared library from the single module created, but only if the
# previous command didn't fail:
#
if test ${D}{status} = 0; then
    if test ${D}{verbose} = 1; then
        echo "${D}CXX ${D}{linking_flag} master.${D}${D}.o ${D}{args}"
    fi
    ${D}CXX ${D}{linking_flag} master.${D}${D}.o ${D}{args}
    status=${D}?
fi

#
# Remove intermediate module
#
rm -f master.${D}${D}.o

exit ${D}status
EOF
dnl ===================== shared-ld-sh ends here =====================
])

AC_DEFUN([AC_BAKEFILE_CREATE_FILE_BK_MAKE_PCH],
[
dnl ===================== bk-make-pch begins here =====================
dnl    (Created by merge-scripts.py from bk-make-pch
dnl     file do not edit here!)
D='$'
cat <<EOF >bk-make-pch
#!/bin/sh

# This script is part of Bakefile (http://www.bakefile.org) autoconf
# script. It is used to generated precompiled headers.
#
# Permission is given to use this file in any way.

outfile="${D}{1}"
header="${D}{2}"
shift
shift

builddir=\`echo ${D}outfile | sed -e 's,/\\.pch/.*${D},,g'\`

compiler=""
headerfile=""

while test ${D}{#} -gt 0; do
    add_to_cmdline=1
    case "${D}{1}" in
        -I* )
            incdir=\`echo ${D}{1} | sed -e 's/-I\\(.*\\)/\\1/g'\`
            if test "x${D}{headerfile}" = "x" -a -f "${D}{incdir}/${D}{header}" ; then
                headerfile="${D}{incdir}/${D}{header}"
            fi
        ;;
        -use-pch|-use_pch|-pch-use )
            shift
            add_to_cmdline=0
        ;;
    esac
    if test ${D}add_to_cmdline = 1 ; then
        compiler="${D}{compiler} ${D}{1}"
    fi
    shift
done

if test "x${D}{headerfile}" = "x" ; then
    echo "error: can't find header ${D}{header} in include paths" >&2
else
    if test -f ${D}{outfile} ; then
        rm -f ${D}{outfile}
    else
        mkdir -p \`dirname ${D}{outfile}\`
    fi
    depsfile="${D}{builddir}/.deps/\`echo ${D}{outfile} | tr '/.' '__'\`.d"
    mkdir -p ${D}{builddir}/.deps
    if test "x${GCC_PCH}" = "x1" ; then
        # can do this because gcc is >= 3.4:
        ${D}{compiler} -o ${D}{outfile} -MMD -MF "${D}{depsfile}" "${D}{headerfile}"
    elif test "x${ICC_PCH}" = "x1" ; then
        filename=pch_gen-${D}${D}
        file=${D}{filename}.c
        dfile=${D}{filename}.d
        cat > ${D}file <<EOT
#include "${D}header"
EOT
        # using -MF icc complains about differing command lines in creation/use
        ${D}compiler -c ${ICC_PCH_CREATE_SWITCH} ${D}outfile -MMD ${D}file && \\
          sed -e "s,^.*:,${D}outfile:," -e "s, ${D}file,," < ${D}dfile > ${D}depsfile && \\
          rm -f ${D}file ${D}dfile ${D}{filename}.o
    fi
    exit ${D}{?}
fi
EOF
dnl ===================== bk-make-pch ends here =====================
])

m4_include([config/acx_pthread.m4])
m4_include([config/ax_cxx_compile_stdcxx.m4])
m4_include([config/libm.m4])
m4_include([config/libtool.m4])
m4_include([config/localtime_r.m4])
m4_include([config/ltoptions.m4])
m4_include([config/ltsugar.m4])
m4_include([config/ltversion.m4])
m4_include([config/lt~obsolete.m4])
m4_include([config/mysql_loc.m4])
m4_include([config/mysql_ssl.m4])
m4_include([config/socket_nsl.m4])
m4_include([config/stl_slist.m4])
