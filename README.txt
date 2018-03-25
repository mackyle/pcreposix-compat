PCRE POSIX Compat Patches
=========================

For full documentation, see the `README.txt` file in the "pcreposix-compat"
branch of this repository.  If this file has been detached from its home
repository see the project link at the end of this file.

The patches in the `patches` subdirectory can be applied to the official
PCRE 8.42 release tarball to provide the "pcreposix-compat" version that
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

https://ftp.pcre.org/pub/pcre/pcre-8.42.tar.gz

      size:  2081413 bytes
       md5:  fc18afa0f14a25475cf097ee102a3e4f
      sha1:  ee505270446f4c4bf52ac1a371335fdbb14465cb
      blob:  97b35e206396f4b52cff4e610bd75f4dcc5d88fb
    sha256:  69acbc2fbdefb955d42a4c606dfde800c2885711d2979e356c0636efde9ec3b5



License
-------

These updates and enhancements are licensed under the same terms as PCRE
itself.


Project Home Page
-----------------

https://github.com/mackyle/pcreposix-compat
