# Hello LibParted
**Leslie Zhai <xiang.zhai@i-soft.com.cn>**

There is NO dev doc available in the parted tarball or at [GNU Parted](http://www.gnu.org/software/parted/) official 
website.

So I simply read the parted source code `parted/parted/parted.c` to be familiar 
with how to use libparted API, then I wrote the `hello.c` testcase to print out 
disk and relative partition information at first.

## Build
```
make
```
## ped_device_probe_all

ped_device_probe_all acts like initial linked list data structure, doesn't it?
By reading about source code parted/libparted/device.c there is some comment 
shown as below:

```
/**
 * \addtogroup PedDevice
 *
 * \brief Device access.
 *
 * When ped_device_probe_all() is called, libparted attempts to detect all
 * devices.  It constructs a list which can be accessed with
 * ped_device_get_next().
 *
 * If you want to use a device that isn't on the list, use
 * ped_device_get().  Also, there may be OS-specific constructors, for creating
 * devices from file descriptors, stores, etc.  For example,
 * ped_device_new_from_store().
 *
 * @{
 */ 
```

Then it is able to traverse all the devices such as:

```C
PedDevice *current_dev = NULL;
while ((current_dev = ped_device_get_next(current_dev))) {
    handle with current_dev goes here...
}
```

## ped_disk_new

`ped_disk_new` acts like constructor if experienced in C++ :) There is some 
comment about ped_disk_new in `parted/libparted/disk.c`.

Then it is able to traverse partition for the disk by `ped_disk_next_partition`.

## structure

There are several structures or classes if using C++ concept to describe, if 
interested in PedDiskFlag, PedUnit, PedPartitionFlag, PedDisk, PedPartition, 
PedDevice, it is able to read relative header files to get closer to libparted.
