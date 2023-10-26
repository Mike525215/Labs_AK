#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
struct head_list
{
	struct head_list *next;
	ktime_t time;
};

MODULE_AUTHOR("Popov Mikhailo IO-16");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training Lab3");
MODULE_LICENSE("Dual BSD/GPL");

static struct head_list *head;

static int amount = 1;
module_param(amount, uint, S_IRUGO);
MODULE_PARM_DESC(times, "Output amount");

static int __init hello_init(void)
{
	uint i = 0;

	struct head_list *var_1, *var_2;

	head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);

	var_1 = head;
	if(amount == 0)
	{
		printk(KERN_WARNING "Parameter == 0");
	}
	else if(amount >= 5 && amount <= 10)
	{
		printk(KERN_WARNING "5 <= Parameter <= 10.");
	}
	else if(amount > 10)
	{
		printk(KERN_ERR "Parameter > 10.");
		return -EINVAL;
	}


	for(i=0; i < amount; i++)
	{
		var_1->next = kmalloc(sizeof(struct head_list), GFP_KERNEL);
		var_1->time = ktime_get();
		printk(KERN_EMERG "Hello, world!\n");
		var_2 = var_1;
		var_1 = var_1->next;
	}

	if (amount != 0) {
		kfree(var_2->next);
		var_2->next = NULL;
	}

	printk(KERN_INFO "Amount: %d\n", amount);

	return 0;
}

static void __exit hello_exit(void)
{
	struct head_list *var;

while (head != NULL && amount != 0) {
	var = head;
	printk(KERN_INFO "Time: %lld\n", var->time);
	head = var->next;
	kfree(var);
	}
}
module_init(hello_init);
module_exit(hello_exit);
