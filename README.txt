PCRE POSIX Compat Patches
=========================

For full documentation, see the `README.txt` file in the "pcreposix-compat"
branch of this repository.  If this file has been detached from its home
repository see the project link at the end of this file.

The patches in the `patches` subdirectory can be applied to the official
PCRE 8.44 release tarball to provide the "pcreposix-compat" version that
can build the "pcreposix" headers and libraries that provide full POSIX
BRE and ERE support as well as PCRE and JRE support.

Note that Git relies on "undefined behavior" in its t7810-grep test.  Most
of that was corrected in version v2.11.1, but a few remain that can result
in spurious test failures.  There is a patch in the `gitpatches` subdirectory
that can be applied to v2.11.1 and later to eliminate the spurious failure when
using pcreposix-compat as a regex.h replacement.


PCRE Source Tarball
-------------------

These patches are intended to be applied to the following tarball:

https://ftp.pcre.org/pub/pcre/pcre-8.44.tar.gz

      size:  2090750 byte(s)
       md5:  3bcd2441024d00009a5fee43f058987c
      sha1:  934324e2d0e7c16d144c52817ab88f6f70c24692
      blob:  a8529764ef8062d6fed11ec589cafc2185cf8986
    sha256:  aecafd4af3bd0f3935721af77b889d9024b2e01d96b58471bd91a3063fb47728




License
-------

These updates and enhancements are licensed under the same terms as PCRE
itself.


Project Home Page
-----------------

https://github.com/mackyle/pcreposix-compat
