#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

struct task_struct *task;
struct task_struct *task_child;
struct list_head *list;

static int __init fetch_init(void)
{
    pr_info("Module loaded\n");

    for_each_process(task)
    {
        pr_info("PID: %d PROCESS: %s\n", task->pid, task->comm);

        list_for_each(list, &task->children)
        {
            task_child = list_entry(list, struct task_struct, sibling);
            pr_info("PID: %d PROCESS: %s\n", task_child->pid, task_child->comm);
        }
    }

    return 0;
}

static void __exit fetch_exit(void)
{
    pr_info("Module exit\n");
}

module_init(fetch_init);
module_exit(fetch_exit);

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Crinstaniev");
