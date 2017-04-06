##
## This file is for use in building Git with the "pcreposix-compat"
## regex libraries instead of its bundled ones.
##
## If you are not building Git this file will not be of use to you.
##
## See the "README-GIT-REGEX" file for additional details.
##

## NOTE: The "pcreposix-compat" libraries must already be built, this
##       file does not build them.

# If you already have your own config.mak, add these contents to the END
# of yours, not the beginning.  The "config.mak" file needs to be placed
# in the top-level directory of the Git distribution (alongside "Makefile")
# that is being built.

# The Git Makefile hard-codes NO_REGEX when uname_S is Darwin.
# Compensate for that by altering the uname_S setting in that case
# and duplicating the needed non-regex logic.
# If you never build on a "Darwin" platform you can remove this section.
ifeq ($(uname_S),Darwin)
  uname_S = Darwin-pcreposix
  ifndef NO_FINK
    ifeq ($(shell test -d /sw/lib && echo y),y)
      BASIC_CFLAGS += -I/sw/include
      BASIC_LDFLAGS += -L/sw/lib
    endif
  endif
  ifndef NO_DARWIN_PORTS
    ifeq ($(shell test -d /opt/local/lib && echo y),y)
      BASIC_CFLAGS += -I/opt/local/include
      BASIC_LDFLAGS += -L/opt/local/lib
    endif
  endif
  ifndef NO_APPLE_COMMON_CRYPTO
    NO_OPENSSL = YesPlease
    APPLE_COMMON_CRYPTO = YesPlease
    COMPAT_CFLAGS += -DAPPLE_COMMON_CRYPTO
  endif
  PTHREAD_LIBS =
endif

# Unfortunately Git's bundled compatibility regex library suffers from some
# serious performance problems.  Despite that it's often used automatically.

# Have Git build with pcreposix-compat instead which does not suffer from
# the same problematic performance problems.

# Set PCREPOSIXDIR to the directory containing an "include" and "lib"
# subdirectory with -lpcreposix -lpcre in "lib" and "pcreposix/regex.h" in
# "include".

PCREPOSIXDIR = /usr/local/or/whatever/correct/location/is/needed

# Alternatively change both of these two instead
PCREPOSIXINC = $(PCREPOSIXDIR)/include/pcreposix # should be a regex.h in here
PCREPOSIXLIB = $(PCREPOSIXDIR)/lib # should be a libpcreposix.<ext> in here

# Turn off the bundled regex (ineffective if uname_S is still "Darwin")
NO_REGEX =

# Add pcreposix-compat compiler and linker options
BASIC_CFLAGS += -I$(PCREPOSIXINC)
BASIC_LDFLAGS += -L$(PCREPOSIXLIB) -lpcreposix -lpcre
