utils
====
Small utils made up from scripts.

autobuild/
----
Packs unilive-builder.

live
----
Usage:`source live`.

Functions:
###cinitramfs
`cinitramfs source [dest] ["somezip -someflag"]`

dest defaults to `target/../initrd`, using xz for compression.

###xinitramfs
`xinitramfs source [dest]`
dest defaults to `${source}.unpacked.`

###\_find\_decompressor
`\_find\_decompressor file`
finds something that prints the decompressed data of file to 
stdout, for uncompressed files it uses cat to forward to stdout.

###busyboxdup
`busyboxdup /path/to/unpacked/initramfs`
Interactively choose commands to keep. Saves list to `$1/bin/.keep`.

###busyboxln
`busyboxln /path/to/unpacked/initramfs`
Reads `$1/bin/.keep` and creates symlinks.

###\_readlink
`\_readlink file`
Gets the absolute path of file, rough equivalent of GNU's `readlink -e`
