TODOs
=====

installer-qt
----
Well, actually it will soon be replaced by another one...
### Installing additional packages from cd/network apt repo
Also with a groupinstall-like function, as in `aptitude` and `yum`.

We need a new tab and lots of other things for this.
### Move user settings to first setting part, just after partitioning
Should make installation easier.

installer-sh
----
This should at least has the same functions the qt build has.

Select-and-installer package groups seems easier
since we can just let the user use the `aptitude` interactive,
or use maybe `yum groupinstall` to wrap it.

Hmm, we should set these up on our software source repository.
### Merge parts
Modular design **using functions** is acceptable.

Also helps deal with lots of annoying things like passing variables.

### genfstab
Huh?

unilive-builder
----
### Missing packages
Just pack everything needed.

unilive.initrd
----
### Language selection into just one initrd
Maybe reading args from grub?

### Squashfs selector
Still grub args.

### tty-only installation
grub args and squashfs selection.

### ALL-IN-ONE live:
I need a bigger hole in my brain, telling me to use a basesystem squashfs and
an 'additions' image to create an all-in-one live. (JK)

Well, how about having a complete one, and removing unneeded things during installation?
Doesn't sound so UNIX but seems a bit more possible.
All
---
###cross-package-manager support
Abstract package manager into functions, either bash or cpp.

(I won't hit you if you use C# to write another installer,
but most likely I will reject the PR.)