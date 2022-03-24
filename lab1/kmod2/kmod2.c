#include<linux/kernel.h>
#include<linux/module.h>
//#include<linux/kallsyms.h>
#include<linux/unistd.h>
//#include<linux/time.h>
#include<asm/uaccess.h>
#include<linux/sched.h>
#include<linux/init.h>
//#include<asm/syscall.h>
#include<linux/kprobes.h>

#define NEW_SYSCALL_ID 335

int init_module(void);
void cleanup_module(void);

unsigned long * getSyscalltable(void);
unsigned int setWP(void);
void setbackWP(unsigned int);
int NewSyscall(void);
void LoadSyscall(void);
void RemoveSyscall(void);

static int (*syscall_ptr)(void);
unsigned long *table;

unsigned int setWP(){
	unsigned int ori_cr0 = 0;
	unsigned int tmp;
	asm volatile ("movq %%cr0, %%rax" : "=a"(ori_cr0));
	printk("reading cr0\ncr0:%x\n", ori_cr0);
	tmp = ori_cr0;
	tmp &= 0xfffeffff;
	asm volatile ("movq %%rax, %%cr0" :: "a"(tmp));
	printk("set WP\n"); 
	return ori_cr0;
}

void setbackWP(unsigned int cr0){
	printk("reading cr0\ncr0:%x\n", cr0);
	asm volatile ("movq %%rax, %%cr0"::"a"(cr0));
	printk("set back WP\n");
}

unsigned long * getSyscalltable(){
	//#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 7, 0)
	struct kprobe kp = {0};
	int flag;
	unsigned long * sct_entry = NULL;
	if(!sct_entry){

		// v1
		flag = 0;
		kp.symbol_name = "sys_call_table";
		flag = register_kprobe(&kp);
		printk("register_kprobe return %d\n", flag);
		if(kp.addr){
			sct_entry = (unsigned long *)kp.addr;
			printk("sct location: %p\n", sct_entry);
		}
		if(flag == 0){
			unregister_kprobe(&kp);
		}

		// v2
		// const char kp_name[16] = "sys_call_table";
		// unsigned int kp_offset = 0;
		// sct_entry = (unsigned long *)kprobe_lookup_name(
		// 	kp_name, kp_offset
		// );
	}
	return sct_entry;
	//#endif
}

void LoadSyscall(){
	int cr0;
	//table = (unsigned long *)kallsyms_lookup_name("sys_call_table");
	//table = (unsigned long *)sys_call_table;
	table = getSyscalltable();
	if(!table){
		printk("get table location\n");
	}
	syscall_ptr = (int(*)(void))(table[NEW_SYSCALL_ID]);
    cr0 = setWP();
	table[NEW_SYSCALL_ID] = (unsigned long)&NewSyscall;
	setbackWP(cr0);
	printk("load new syscall\n");
}

void RemoveSyscall(){
	int cr0 = setWP();
	table[NEW_SYSCALL_ID] = syscall_ptr;
	setbackWP(cr0);
	printk("remove syscall\n");
}

int init_module(){
	LoadSyscall();
	printk("insert kmod2.\n");
	return 0;
}

void cleanup_module(){
	RemoveSyscall();
	printk("remove kmod2.\n");
}

int NewSyscall(){
	int ret = 12345;
	printk("new syscall\n");
	return ret;
}

MODULE_LICENSE("GPL");
