PCRE POSIX Compat Patches
=========================

For full documentation, see the `README.txt` file in the "pcreposix-compat"
branch of this repository.  If this file has been detached from its home
repository see the project link at the end of this file.

The patches in the `patches` subdirectory can be applied to the official
PCRE 8.40 release tarball to provide the "pcreposix-compat" version that
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

https://ftp.pcre.org/pub/pcre/pcre-8.40.tar.gz

      size:  2065161 bytes
       md5:  890c808122bd90f398e6bc40ec862102
      sha1:  10384eb3d411794cc15f55b9d837d3f69e35391e
    sha256:  1d75ce90ea3f81ee080cdc04e68c9c25a9fb984861a0618be7bbf676b18eda3e


License
-------

These updates and enhancements are licensed under the same terms as PCRE
itself.


Project Home Page
-----------------

https://github.com/mackyle/pcreposix-compat
