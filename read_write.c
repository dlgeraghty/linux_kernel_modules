
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

static struct proc_dir_entry *proc_entry;

static ssize_t my_custom_read(struct file *filp, char __user *buf, size_t len, loff_t *off) {

}

static ssize_t my_custom_write(struct file *filp, const char __user *buf, size_t len, loff_t *off) {

}

static const struct file_operations proc_entry_fops = {
	.read = my_custom_read;
	.write = my_custom_write;
};

int my_custom_init(void){
	int ret = 0;
	proc_entry = proc_create("rw", 0666, NULL, &proc_entry_fops);
	if(proc_entry == NULL){
		ret = -ENOMEM;
		printk(KERN_DEBUG "Cant create that proc entry\n");
	}else{
		printk(KERN_DEBUG "Module correctly loaded...");
	}
	return ret;
}

module_init( my_custom_init );
module_exit( my_custom_exit );
