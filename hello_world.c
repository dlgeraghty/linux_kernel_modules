#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");

int init_module(void){

	printk(KERN_INFO "Hello world this is my first module.\n");

	return 0;

}

void cleanup_module(void){

	printk(KERN_INFO "our first module ran smoothly!\n");

}
