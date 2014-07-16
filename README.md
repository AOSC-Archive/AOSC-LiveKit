AOSC-LiveKit
==============
Installer and live media builder for AOSC OS2/3 Distributions.

packing
----
For AOSC OSes:
```Bash
for i in installer-qt installer-sh unilive-builder; do
cd $i; autobuild; mv $i{.deb,_*.tar.xz} ..; cd ..
done
```
- Please remember to get your rpm packages from rpmbuild.

For other Linux/\*NIX:
Refer to `qmake` or `autobuild/build`.

If you are using a non-GNU environment, try including `utils/live` so that you can have readlink (implemented in a really strange way).

HowTo
----


unilive-builder
----
UniLive Builder for AOSC Spins based on AOSC OS2/3.