PCRE POSIX Compat
=================

What Is It?
-----------

POSIX compatibility updates for the "pcreposix" functionality provided with
the PCRE library so that "pcreposix.h" and the corresponding library may be
used as a standard POSIX "regex.h" substitute.

See the "How to Use" section at the bottom if you're having a tl;dr moment.


Wherefore Art Thou?
-------------------

Some poorly implemented regex engines go bananas over this:

    w++++++++++++++++++++++

Technically that's not a POSIX ERE (using `+` requires an ERE not a BRE).

But this is:

    (((((((((((((((((((((w+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+

You need only compile it with one of those engines like so:

    grep -E '(((((((((((((((((((((w+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+)+'

to watch the bananas hit the fan.

PCRE does not suffer bananas easily and with a few, relatively simple,
enhancements can be used as a substitute for the POSIX "regex.h" `regcomp`
and `regexec` functions to avoid going bananas over nothing.


Good Timing Results for pcregrep
--------------------------------

The PCRE distribution contains a `pcregrep` utility that works very much
like `grep` except that all patterns are PCRE patterns (as long as `-F` is
not used).

Here are some timing results for the problem regex shown above when passed
to `pcregrep`.  The "count" value along the "x" axis represents how many
"+" quantifiers are being used in the pattern.

Some of these are running in VMs which is why these "good" timings are in
the tens of milliseconds rather than much closer to 0.

These timing results confirm that using PCRE does not go bananas on these
kinds of patterns.  These are all "good" results.

    Testing "pcregrep" on Linux 3.16.0-4-amd64 x86_64
    |0.030| *     *
    |     | =     =
    |0.027| =     =
    |     | =     =
    |0.024| =     =
    |     | =     =
    |0.021| =     =
    |     | =     =               *     *       *
    |0.018| =     =               =     =       =
    |     | =     =               =     =       =
    |0.015| =     =               =     =       =
    |     | =     =               =     =       =
    |0.012| =     =               =     =       =
    |     | =   * = * * * *   * * = * * = * * * = *   * * * *   * * * *
    |0.009| =   = = = = = =   = = = = = = = = = = =   = = = =   = = = =
    |     | =   = = = = = =   = = = = = = = = = = =   = = = =   = = = =
    |0.006| =   = = = = = =   = = = = = = = = = = =   = = = =   = = = =
    |     | =   = = = = = =   = = = = = = = = = = =   = = = =   = = = =
    |0.003| =   = = = = = =   = = = = = = = = = = =   = = = =   = = = =
    |     | =   = = = = = =   = = = = = = = = = = =   = = = =   = = = =
    |0.000| = * = = = = = = * = = = = = = = = = = = * = = = = * = = = =
    | sec +------------------------------------------------------------
    |:::::| 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3
    |:::::|                   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0

    Testing "pcregrep" on FreeBSD 10.3-RELEASE-p4 amd64
    |0.031|       *
    |     |       =
    |0.029|       =
    |     |       =
    |0.027|       =
    |     |       =
    |0.024|       =
    |     |       =   *   *         *             *     *           *
    |0.022|       =   =   =         =             =     =           =
    |     |       =   =   =         =             =     =           =
    |0.020|       =   =   =         =             =     =           =
    |     |       =   =   =         =             =     =           =
    |0.017|       =   =   =         =             =     =           =
    |     | * * * = * = * = * * *   =   * * * * * = *   = * * * * * = *
    |0.015| = = = = = = = = = = =   =   = = = = = = =   = = = = = = = =
    |     | = = = = = = = = = = =   =   = = = = = = =   = = = = = = = =
    |0.013| = = = = = = = = = = =   =   = = = = = = =   = = = = = = = =
    |     | = = = = = = = = = = =   =   = = = = = = =   = = = = = = = =
    |0.010| = = = = = = = = = = =   =   = = = = = = =   = = = = = = = =
    |     | = = = = = = = = = = =   =   = = = = = = =   = = = = = = = =
    |0.008| = = = = = = = = = = = * = * = = = = = = = * = = = = = = = =
    | sec +------------------------------------------------------------
    |:::::| 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3
    |:::::|                   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0

    Testing "pcregrep" on Darwin 9.8.0 i386
    |0.010|         *           *           *         *   *           *
    |     |         =           =           =         =   =           =
    |0.009|         =           =           =         =   =           =
    |     |         =           =           =         =   =           =
    |0.008|         =           =           =         =   =           =
    |     |         =           =           =         =   =           =
    |0.007|         =           =           =         =   =           =
    |     |         =           =           =         =   =           =
    |0.006|         =           =           =         =   =           =
    |     |         =           =           =         =   =           =
    |0.005|         =           =           =         =   =           =
    |     |         =           =           =         =   =           =
    |0.004|         =           =           =         =   =           =
    |     |         =           =           =         =   =           =
    |0.003|         =           =           =         =   =           =
    |     |         =           =           =         =   =           =
    |0.002|         =           =           =         =   =           =
    |     |         =           =           =         =   =           =
    |0.001|         =           =           =         =   =           =
    |     |         =           =           =         =   =           =
    |0.000| * * * * = * * * * * = * * * * * = * * * * = * = * * * * * =
    | sec +------------------------------------------------------------
    |:::::| 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3
    |:::::|                   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0


Good and Bad grep Timing Results
--------------------------------

There's only one "good" result here, but it should be obvious which one
it is.  That there's only one "good" result here instead of two will
probably come as somewhat of a surprise to some folks, especially once
the next section's results are viewed as well.

    Testing "grep -E" on Linux 3.16.0-4-amd64 x86_64
    |2.370|                               *
    |     |                               =
    |2.133|                               =
    |     |                               =
    |1.896|                               =
    |     |                               =
    |1.659|                               =
    |     |                               =
    |1.422|                               =
    |     |                               =
    |1.185|                             * =
    |     |                             = =
    |0.948|                             = =
    |     |                             = =
    |0.711|                             = =
    |     |                             = =
    |0.474|                           * = =
    |     |                           = = =
    |0.237|                         * = = =
    |     |                     * * = = = =
    |0.000| * * * * * * * * * * = = = = = =
    | sec +--------------------------------
    |:::::| 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1
    |:::::|                   0 1 2 3 4 5 6

    Testing "grep -E" on FreeBSD 10.3-RELEASE-p4 amd64
    |8.820|                               *
    |     |                               =
    |7.939|                               =
    |     |                               =
    |7.058|                               =
    |     |                               =
    |6.177|                               =
    |     |                               =
    |5.295|                               =
    |     |                               =
    |4.414|                               =
    |     |                               =
    |3.533|                               =
    |     |                               =
    |2.652|                               =
    |     |                               =
    |1.770|                               =
    |     |                             * =
    |0.889|                           * = =
    |     |                         * = = =
    |0.008| * * * * * * * * * * * * = = = =
    | sec +--------------------------------
    |:::::| 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1
    |:::::|                   0 1 2 3 4 5 6

    Testing "grep -E" on Darwin 9.8.0 i386
    |0.020|                                       *
    |     |                                       =
    |0.018|                                       =
    |     |                                       =
    |0.016|                                       =
    |     |                                       =
    |0.014|                                       =
    |     |                                       =
    |0.012|                                       =
    |     |                                       =
    |0.010|           *             *             =             *
    |     |           =             =             =             =
    |0.008|           =             =             =             =
    |     |           =             =             =             =
    |0.006|           =             =             =             =
    |     |           =             =             =             =
    |0.004|           =             =             =             =
    |     |           =             =             =             =
    |0.002|           =             =             =             =
    |     |           =             =             =             =
    |0.000| * * * * * = * * * * * * = * * * * * * = * * * * * * = * * *
    | sec +------------------------------------------------------------
    |:::::| 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3
    |:::::|                   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0


Good and Bad git Timing Results
-------------------------------

There's only one "good" result here, but it should be obvious which one
it is (and, no, it's not the same one as in the previous set).  Again,
it's a bit surprising there's only one "good" result here.

    Testing "git log --grep" on Linux 3.16.0-4-amd64 x86_64
    |2.330|                               *
    |     |                               =
    |2.097|                               =
    |     |                               =
    |1.864|                               =
    |     |                               =
    |1.631|                               =
    |     |                               =
    |1.398|                               =
    |     |                               =
    |1.165|                             * =
    |     |                             = =
    |0.932|                             = =
    |     |                             = =
    |0.699|                             = =
    |     |                           * = =
    |0.466|                           = = =
    |     |                           = = =
    |0.233|                         * = = =
    |     |                       * = = = =
    |0.000| * * * * * * * * * * * = = = = =
    | sec +--------------------------------
    |:::::| 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1
    |:::::|                   0 1 2 3 4 5 6

    Testing "git log --grep" on FreeBSD 10.3-RELEASE-p4 amd64
    |0.047|                                           *
    |     |                                           =
    |0.044|                                           =
    |     |                                           =
    |0.041|                                           =
    |     |                                           =               *
    |0.038|                                           =               =
    |     |                                           =               =
    |0.034|                                           =               =
    |     |                                           =               =
    |0.031|     *   * *   * * *   *   *     *         = * *     * *   =
    |     |     =   = =   = = =   =   =     =         = = =     = =   =
    |0.028|     =   = =   = = =   =   =     =         = = =     = =   =
    |     |     =   = =   = = =   =   =     =         = = =     = =   =
    |0.025|     =   = =   = = =   =   =     =         = = =     = =   =
    |     | * * = * = =   = = = * = * =   * = * * * * = = = * * = = * =
    |0.022| = = = = = =   = = = = = = =   = = = = = = = = = = = = = = =
    |     | = = = = = =   = = = = = = =   = = = = = = = = = = = = = = =
    |0.019| = = = = = =   = = = = = = =   = = = = = = = = = = = = = = =
    |     | = = = = = =   = = = = = = =   = = = = = = = = = = = = = = =
    |0.016| = = = = = = * = = = = = = = * = = = = = = = = = = = = = = =
    | sec +------------------------------------------------------------
    |:::::| 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3
    |:::::|                   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0

    Testing "git log --grep" on Darwin 9.8.0 i386
    |3.150|                                 *
    |     |                                 =
    |2.835|                                 =
    |     |                                 =
    |2.520|                                 =
    |     |                                 =
    |2.205|                                 =
    |     |                                 =
    |1.890|                                 =
    |     |                                 =
    |1.575|                                 =
    |     |                               * =
    |1.260|                               = =
    |     |                               = =
    |0.945|                               = =
    |     |                               = =
    |0.630|                             * = =
    |     |                             = = =
    |0.315|                           * = = =
    |     |                         * = = = =
    |0.000| * * * * * * * * * * * * = = = = =
    | sec +----------------------------------
    |:::::| 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1
    |:::::|                   0 1 2 3 4 5 6 7


PCRE POSIX Means What?
----------------------

With a name like "pcreposix" it could be taken to mean either of these:

 1. PCRE used as an implementation backend to provide POSIX semantics
 2. PCRE semantics provided via a POSIX-similar API

If you guessed (1), you're wrong.  At least historically speaking, "pcreposix"
has always meant (2) which can be a bit confusing since it provided neither
Basic Regular Expression (BRE) support nor Extended Regular Expression (ERE)
support via the `regcomp` and `regexec` functions in the "pcreposix.h" header,
but has "posix" in its name and POSIX `regcomp` and `regexec` provide those.

What it did provide was Perl Compatible Regular Expression (PCRE) support via
that header.


PCRE POSIX Compat
-----------------

These compatibility updates for "pcreposix" update it to provide _both_ (1)
and (2) by introducing full support for POSIX BREs and EREs and providing a
new `REG_PCRE` option for the `regcomp` function to activate PCRE support.

As a bonus a `REG_JAVASCPT` option is also provided to activate PCRE's
Javascript Regular Expression (JRE) support.

All in one place with one API you get your BREs, EREs, PCREs and JREs.


Backwards Compatibility
-----------------------

Not with older "pcreposix" libraries.  The original version of "pcreposix.h"
defines the `REG_EXTENDED` constant to be 0.  This makes backwards
compatibility for the "pcreposix" library impossible.

The version for the "pcreposix" library has been changed from a previous
`-version-info 0:4:0` to the current `-version-info 1:0:0`.  What this means
is that both the old and new "pcreposix" libraries can coexist on the same
system.  The old, original one will have a name like "libpcreposix.0.<ext>"
while the new one will be named like "libpcreposix.1.<ext>".

The "pcreposix.h" header has also seen substantial changes and while an attempt
has been made to make sure same-named constants keep the same value between the
original version of "pcreposix.h" and the new one, in some cases that's just
not possible.  For example, `REG_EXTENDED` must not be 0.

To address this issue and also facilitate use as a "regex.h" substitute, the
new "pcreposix.h" header and a new "regex.h" header (it's the same header) are
now installed to "$includedir/pcreposix/pcreposix.h" and
"$includedir/pcreposix/regex.h" whereas the original header was installed
simply to "$includedir/pcreposix.h".

So again, the old and new versions of the "pcreposix.h" header can coexist on
the same system.  But now, to use the new "pcreposix" as a drop-in "regex.h"
substitute all that's required is adding a "-I $includedir/pcreposix" option
to the compile line and "-lpcreposix -lpcre" options to the link line.

Although if "libpcreposix.<ext>" is pointing at the old "libpcreposix.0.<ext>"
library then that will have to be "-lpcreposix.1" instead.

The version of PCRE remains unchanged because:

 1. The only client of the new options is the new pcreposix
 2. Versions of PCRE not supporting the new options will complain about them
    causing the new pcreposix `regcomp` implementation to return an error
 3. Even if non-pcreposix clients make use of the newly provided PCRE options
    regex's compiled using them can be executed by any version of PCRE


Slight of Hand
--------------

So how does PCRE now, all of a sudden, support POSIX-semantics BREs and EREs?

Magic.  A slight of hand. "Syntactic Sugar".

When the pattern is compiled in "BRE" mode, automagical virtual backslash
escaping and unescaping takes place to transform the incoming BRE into an
equivalent PCRE.

To a lesser extent the same thing happens in "ERE" mode but really only in
the one case (`[^foo]` does not match `\n` when one of the new options is
enabled).  But again, more slight of hand (an extra `\n` is virtually inserted
into the negated character class to get the desired semantics).

There are five new PCRE options in all.  (The other three also perform more
slight-of-hand to provide POSIX `REG_EXTENDED`, BSD `REG_PEND` and BSD
`REG_NOSPEC` compatibility.)

The bottom line is that saving off a compiled PCRE regular expression that used
one (or more) of the new options, loading it on a system without support for
the new options and "exec"ing it works and matches what it's supposed to.

The rest of the POSIX semantics compatibility is provided by having the new
"pcreposix" library manipulate other PCRE options (`PCRE_DOTALL`,
`PCRE_DOLLARENDOLY` and `PCRE_MULTILINE`) based on the options supplied to
the `regcomp` function.

Full details are in the "pcreposix.h" header, but basically, sticking to only
POSIX-defined options results in POSIX semantics.  Using either the new
`REG_PCRE` or `REG_JAVASCPT` non-POSIX options gets you either PCREs or JREs
respectively.

The "*BSD" compatibility options (`REG_PEND`, `REG_NOSPEC` and `REG_STARTEND`)
are supported in all regex modes (but `REG_NOSPEC` acts like its own mode).


New pcreposix Old pcre
----------------------

So what happens if a new "pcreposix" library is linked against an old "pcre"
library?

It depends.

If the "pcreposix" client has set `REG_PCRE` and/or `REG_JAVASCPT` and avoids
using `REG_NOSPEC` and `REG_PEND` then everything else will work.

Alternatively, if the "pcreposix" client sets `REG_EXTENDED` and does NOT set
any of `REG_NEWLINE`, `REG_NOSPEC` or `REG_PEND` it will also still work.

If none of `REG_EXTENDED`, `REG_PCRE` or `REG_JAVASCPT` are set or either of
`REG_PEND` or `REG_NOSPEC` is set it will fail at `regcomp` time with a
`REG_INVARG` error.

The fact that "pcreposix" non-BRE and non-REG_NEWLINE functionality works fully
and correctly with an "old" "-lpcre" library and returns an error rather than
giving incorrect results for the rest is the reason that the PCRE library
version remains unchanged by these compatibility updates.

An application that links against a shared "pcre" library and needs to use one
or more of the options that require the enhanced "pcre" library should simply
attempt to compile a simple pattern using the needed options at startup and
bail out immediately if it gets a `REG_INVARG` result.


How to Use
----------

Build and install like normal for PCRE (e.g. run "./configure" then "make"
and then "make install").

This repository already contains the necessary pre-generated "configure" and
patches pre-applied to the PCRE 8.40 tarball release.  Clone it, download a
tarball of it or see the "pcreposix-compat-patches" branch for individual
patches to apply to a PCRE 8.40 tarball yourself.

Clients that explicitly need to use non-POSIX options should include the header
as `#include <pcreposix/pcreposix.h>` and make sure they set the `REG_PCRE`
and/or `REG_JAVASCPT` option bit(s) for `regcomp` to get PCRE or JRE support.

For use as a drop-in substitute for the POSIX "regex.h", clients should just
continue to `#include <regex.h>` and then compile with the proper include
"-I $includedir/pcreposix" option.

In any case, clients of "pcreposix" must link against BOTH "-lpcreposix" and
"-lpcre" (wherever they happen to be).

If you wish to use this as a substitute "regex.h" when building Git, see the
accompanying "README-GIT-REGEX" and "config.mak" files for assistance with
doing that.

See the previous section for a discussion of what happens when you link against
the new "pcreposix" library and an older "pcre" library.  In some cases that
may be a desirable scenario where a static version of the new "pcreposix"
library is linked into an application which is then linked against an older
shared "pcre" library.  Read the previous section for details.


License
-------

These updates and enhancements are licensed under the same terms as PCRE
itself.


Project Home Page
-----------------

https://github.com/mackyle/pcreposix-compat
