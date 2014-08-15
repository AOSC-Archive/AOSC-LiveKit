/* TODO: Be familiar with libparted by reading source code parted/parted/parted.c */

#include <stdio.h>
#include <parted/parted.h>
#include <parted/debug.h>

static char *disk_print_flags(PedDisk const *disk);
static void m_print_disk_info(const PedDevice *dev, const PedDisk *disk);
static void do_print(PedDevice** dev);

static char *disk_print_flags(PedDisk const *disk) 
{                                                                                   
    char *res = xstrdup("");
    if (!disk) { return res; }
    PedDiskFlag flag;
    size_t res_buf_len = 1;
    char const *sep = "";
    /* TODO: traverse flag */
    for (flag = ped_disk_flag_next(0); flag;
         flag = ped_disk_flag_next(flag)) {
        if (ped_disk_get_flag(disk, flag)) {
            const char *name = ped_disk_flag_get_name(flag);
            size_t new_len = res_buf_len + strlen(sep) + strlen(name);
            res = xrealloc(res, new_len);
            stpcpy(stpcpy(res + res_buf_len - 1, sep), name);
            res_buf_len = new_len;
            sep = ", ";
        }
    }
    return res;
}

static void m_print_disk_info(const PedDevice *dev, const PedDisk *disk) 
{
    char *start = ped_unit_format(dev, 0);
    PedUnit default_unit = ped_unit_get_default();
    char *end = ped_unit_format_byte(dev, dev->length * dev->sector_size
                                     - (default_unit == PED_UNIT_CHS ||
                                        default_unit == PED_UNIT_CYLINDER));
    char *disk_flags = disk_print_flags(disk);
    printf("DEBUG: %s %s %s %s\n", dev->model, dev->path, end, disk_flags);
    /* TODO: Mr. Cleanup :) */
    free(start); start = NULL;
    free(end); end = NULL;
    free(disk_flags); disk_flags = NULL;
}

static char *partition_print_flags (PedPartition const *part) 
{                                                                                   
    char *res = xstrdup("");
    if (!part) { return res; }
    PedPartitionFlag flag;
    size_t res_buf_len = 1;
    char const *sep = "";
    /* TODO: traverse flag */
    for (flag = ped_partition_flag_next(0); flag;
         flag = ped_partition_flag_next(flag)) {
        if (ped_partition_get_flag(part, flag)) {
            const char *name = ped_partition_flag_get_name(flag);
            size_t new_len = res_buf_len + strlen(sep) + strlen(name);
            res = xrealloc(res, new_len);
            stpcpy(stpcpy(res + res_buf_len - 1, sep), name);
            res_buf_len = new_len;
            sep = ", ";
        }
    }
    return res;
}

static void do_print(PedDevice** dev) 
{
    PedDisk *disk = NULL;
    PedPartition *part = NULL;
    char *start = NULL;
    char *end = NULL;
    char *size = NULL;
    char *name = NULL;
    /* TODO: if use GoLang, it is able to cleanup anywhere, CRAZY! */
    disk = ped_disk_new(*dev);
    if (!disk) {
        printf("ERROR: fail to ped_disk_new 0x%0x\n", dev); return;
    }
    m_print_disk_info(*dev, disk);
    /* TODO: traverse partition */
    for (part = ped_disk_next_partition(disk, NULL); part;
         part = ped_disk_next_partition(disk, part)) {
        if (!ped_partition_is_active(part)) {
            /* TODO: it does not need to print it out, too NOISZE...
             * printf("DEBUG: ped partition is NOT active 0x%x\n", part);
             */
            continue;
        }
        if (part->type & PED_PARTITION_METADATA) {
            printf("DEBUG: part type %d\n", part->type);
            continue;
        }
        start = ped_unit_format(*dev, part->geom.start);
        end = ped_unit_format_byte(*dev,
                                   (part->geom.end + 1) * (*dev)->sector_size - 1);
        size = ped_unit_format(*dev, part->geom.length);
        /* TODO: */
        name = ped_partition_type_get_name(part->type);
        
        char *flags = partition_print_flags(part);
        printf("DEBUG: %d\t%s\t%s\t%s\t%s\t%s\n", part->num, start, end, size,
               name, part->fs_type ? part->fs_type->name : "");
        /* TODO: Mr. Cleanup :) */
        free(flags); flags = NULL;
        free(start); start = NULL;
        free(end); end = NULL;
        free(size); size = NULL;
    }
    /* TODO: Mr. Cleanup :) */
    if (disk) free(disk); disk = NULL;
}

static void m_print_list() 
{
    PedDevice *current_dev = NULL;
    /* TODO: ped_device_probe_all acts like initial device list data structure?
     */
    ped_device_probe_all();
    /* TODO: traverse device list */
    while ((current_dev = ped_device_get_next(current_dev))) {
        do_print(&current_dev);
    }
}

int main(int argc, char *argv[]) 
{
    /* TODO: print list testcase */
    m_print_list();
    return 0;
}
