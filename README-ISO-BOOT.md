boot folder
====
The boot folder to start current version of Live devices. 

vmlinuz
----
Just a kernel.

initrd
----
This IS an `initrd`, not an `initramfs`. To mount and modify, just use your `mount`.
It is an ext4 block device.

Testing: Compress the initrd with xz and make it work, maybe the last thing done to this version of initrd. All we know about
compressing it with xz is we should use flags like `--check=crc32 --x86`.

It **finally** works! Using `xz -zv --check=crc32 --x86 --lzma2=preset=9e,nice=273 initrd`.