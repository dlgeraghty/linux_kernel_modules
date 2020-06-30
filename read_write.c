
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <linux/tty.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");

static struct proc_dir_entry *proc_entry;

static ssize_t my_custom_read(struct file *filp, char __user *buf, size_t len, loff_t *off) {
	struct tty_struct *tty;

	if(*off > 0)
		return 0;

	//https://stackoverflow.com/questions/20719713/how-can-i-write-to-tty-from-a-kernel-module

	tty = get_current_tty();

	if(tty != NULL)

		(tty->driver->ops->write) (tty, "hello", strlen("hello"));
	else
		printk("bad tty");

	*off += len;
	return len;

}

static ssize_t my_custom_write(struct file *filp, const char __user *buf, size_t len, loff_t *off) {
	char * str;
	str = vmalloc((size_t) len);
	if(copy_from_user(str, buf, len)){
		vfree(str);
		return -EFAULT;
	}

	str[len] = '\0';

	printk(KERN_DEBUG "You entered: %s\n", str);

	vfree(str);
	*off += len;
	return len;

}

static const struct proc_ops proc_entry_fops = {
    .proc_read = my_custom_read,
    .proc_write = my_custom_write,
};

int my_custom_init(void){
	int ret = 0;
	proc_entry = proc_create( "rwtest", 0666, NULL, &proc_entry_fops);

	if(proc_entry == NULL){
		ret = -ENOMEM;
		printk(KERN_DEBUG "Cant create that proc entry\n");
	}else{
		printk(KERN_DEBUG "Module correctly loaded...");
	}
	return ret;
}

void my_custom_exit(void){


}

module_init( my_custom_init );
module_exit( my_custom_exit );
