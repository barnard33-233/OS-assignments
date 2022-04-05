#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/module.h>
#include <linux/sched/types.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/list.h>

int init_module(void);
void cleanup_module(void);

void traverse(struct task_struct * task);

int init_module(){
    printk("state\t\tname\t\tpid\t\ttgid\n");
    traverse(&init_task);
    return 0;
}

void traverse(struct task_struct * task){
    struct list_head node;
    struct task_struct child;
    list_for_each(node, task->children){
        child = list_entry(node, struct task_struct, sibling);
        traverse(child);
        long state = child.state;
        char* name = child.comm;
        pid_t pid = child.pid;
        pid_t tgid = child.tgid;
        printk(
            "%ld\t\t%s\t\t%d\t\t%d\n",
            state,
            name,
            pid,
            tgid
        );
    }
}



MODULE_LICENCE("GPL");