/* Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <stdio.h>
#include <blkid/blkid.h>

int main(int argc, char *argv[]) 
{
    blkid_probe pr;
    const char *uuid = NULL;

    if (argc != 2) {
        printf("Usage: %s devname\n", argv[0]);
        return -1;
    }

    pr = blkid_new_probe_from_filename(argv[1]);
    if (!pr) {
        printf("ERROR: failed to open %s\n", argv[1]);
        return -1;
    }

    blkid_do_probe(pr);
    blkid_probe_lookup_value(pr, "UUID", &uuid, NULL);

    printf("UUID=%s\n", uuid);

    blkid_free_probe(pr);

    return 0;
}
