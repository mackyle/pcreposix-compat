PCRE POSIX Compat Patches
=========================

For full documentation, see the `README.txt` file in the "pcreposix-compat"
branch of this repository.  If this file has been detached from its home
repository see the project link at the end of this file.

The patches in the `patches` subdirectory can be applied to the official
PCRE 8.41 release tarball to provide the "pcreposix-compat" version that
can build the "pcreposix" headers and libraries that provide full POSIX
BRE and ERE support as well as PCRE and JRE support.

Note that Git relies on "undefined behavior" in its t7810-grep test.  Most
of that was corrected in version v2.11.1, but a few remain that can result
in spurious test failures.  There is a patch in the `gitpatches` subdirectory
that can be applied to v2.11.1 to eliminate the spurious failure when using
pcreposix-compat as a regex.h replacement.


PCRE Source Tarball
-------------------

These patches are intended to be applied to the following tarball:

https://ftp.pcre.org/pub/pcre/pcre-8.41.tar.gz

      size:  2068775 bytes
       md5:  2e7896647ee25799cb454fe287ffcd08
      sha1:  dddf0995aefe04cc6267c1448ffef0e7b0560ec0
      blob:  345b08315f15abed84561ad4cd654993cc795866
    sha256:  244838e1f1d14f7e2fa7681b857b3a8566b74215f28133f14a8f5e59241b682c


License
-------

These updates and enhancements are licensed under the same terms as PCRE
itself.


Project Home Page
-----------------

https://github.com/mackyle/pcreposix-compat
