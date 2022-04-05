#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/module.h>
#include <linux/sched/types.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/init.h>

int init_module(void);
void cleanup_module(void);

// char* state_names[] = {

// }

// long state_code[] = {

// }

int init_module(){
    struct task_struct * task;
    printk("state\t\tname\t\tpid\t\ttgid\n");
    for_each_process(task){
        long state = task->state;
        char* name = task->comm;
        pid_t pid = task->pid;
        pid_t tgid = task->tgid;
        printk(
            "%ld\t\t%s\t\t%d\t\t%d\n",
            state,
            name,
            pid,
            tgid
        );
        
    }
    return 0;
}

void cleanup_module(){
    printk("exit\n");
}

MODULE_LICENSE("GPL");