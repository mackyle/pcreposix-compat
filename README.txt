PCRE POSIX Compat Patches
=========================

For full documentation, see the `README.txt` file in the "pcreposix-compat"
branch of this repository.  If this file has been detached from its home
repository see the project link at the end of this file.

The patches in the `patches` subdirectory can be applied to the official
PCRE 8.43 release tarball to provide the "pcreposix-compat" version that
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

https://ftp.pcre.org/pub/pcre/pcre-8.43.tar.gz

      size:  2085854 byte(s)
       md5:  e775489c9f024a92ca0f431301ef4c5c
      sha1:  8f36ed69d3e938972fc511c19bfaa0ff27ff1d71
      blob:  73389614439b81cc42e42382d492c74795b00f66
    sha256:  0b8e7465dc5e98c757cc3650a20a7843ee4c3edf50aaf60bb33fd879690d2c73



License
-------

These updates and enhancements are licensed under the same terms as PCRE
itself.


Project Home Page
-----------------

https://github.com/mackyle/pcreposix-compat
