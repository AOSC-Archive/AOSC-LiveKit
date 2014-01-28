#! /bin/bash

bui-msgbox "Now installing GRUB (EFI installation not yet implemented)"
export GRUBPART=`bui-list "You may need to choose the one which has no number unless you have some special requirements." "Partition" /dev/sd*`
$INTARGET grub-install $GRUBPART
$INTARGET grub-mkconfig -o /boot/grub/grub.cfg
bui-msgbox "Installation complete, please restart your computer to proceed to the installed system. Thank you for taking your time testing our newest build!"
