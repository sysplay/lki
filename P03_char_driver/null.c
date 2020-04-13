#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/uaccess.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1

/* Add your variables here */

static dev_t dev;
static struct cdev c_dev;

static int my_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver: In open\n");
	/* Add code here */
	return 0;
}
static int my_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver: In close\n");
	/* Add code here */
	return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver: In read - Buf: %p; Len: %zd; Off: %Ld\nData:\n", buf, len, *off);
	/* Add code here */
	// TODO 4: // Send the last character of the previous write operation to the user space
	return 0 /* read cnt */;
}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	int i;
	char t;

	printk(KERN_INFO "Driver: In write - Buf: %p; Len: %zd; Off: %Ld\nData:\n", buf, len, *off);
	printk(KERN_INFO);

	for (i = 0; i < len; i++)
	{
		if (copy_from_user(&t, buf + i, 1))
		{
			return -EFAULT;
		}
		printk("%02X(%c) ", t, t);
	}
	printk("\n");
	/* Add code here */

	return len /* wrote cnt */;
}

//TODO 3: Register the call backs from open, release, read, write
static struct file_operations driver_fops =
{
	.owner = THIS_MODULE,
};

int __init init_module()
{
	int ret = 0;

	printk(KERN_INFO "Hello Universe\n");
	if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "null")) < 0)
	{
		return ret;
	}

	printk(KERN_INFO "(Major, Minor): (%d, %d)\n", MAJOR(dev), MINOR(dev));

	//TODO 1: Initialize the c_dev with driver_fops
	//TODO 2: Register file operations with VFS

	if ((ret) < 0)
	{
		unregister_chrdev_region(dev, MINOR_CNT);
		return ret;
	}
	
	return ret;
}

void __exit cleanup_module()
{
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
	printk(KERN_INFO "Bye Universe\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SysPlay Workshops <workshop@sysplay.in>");
MODULE_DESCRIPTION("First Character Driver");
