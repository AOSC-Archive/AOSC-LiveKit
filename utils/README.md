utils
====
Small utils made up from scripts.

live
----
Usage:`source live`.

Functions:
###mkinitramfs
`mkinitramfs source [dest] ["somezip -someflag"]`

dest defaults to `target/../initrd`, using xz for compression.

###exinitramfs
`exinitramfs source [dest]`
dest defaults to `${source}.unpacked.`