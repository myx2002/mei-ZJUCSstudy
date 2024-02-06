// arch/riscv/include/proc.h

#include "types.h"

#define NR_TASKS  (1 + 4) // 用于控制 最大线程数量 （idle 线程 + 31 内核线程）

#define TASK_RUNNING    0 // 为了简化实验, 所有的线程都只有一种状态

#define PRIORITY_MIN 1
#define PRIORITY_MAX 10

/* 用于记录 `线程` 的 `内核栈与用户栈指针` */
/* (lab2 中无需考虑, 在这里引入是为了之后实验的使用) */
typedef unsigned long* pagetable_t;
struct thread_info {
    uint64 kernel_sp;
    uint64 user_sp;
};

/* 线程状态段数据结构 */
struct thread_struct {
    uint64 ra; //返回地址寄存器保存
    uint64 sp; //栈指针寄存器保存
    uint64 s[12]; //必要保存寄存器
    //这里数据没有考虑堆栈保存，是否需要保存
    //对映sepc寄存器，用于确定用户的返回值
    uint64 sepc;
    //确定用户返回状态与控制信息
    uint64 sstatus;
    //用于记录用户栈，用于与内核栈进行替换
    uint64 sscratch; 
};

/* 线程数据结构 */
struct task_struct {
    //注意由结构变化为指针
    struct thread_info* thread_info;
    uint64 state;    // 线程状态
    uint64 counter;  // 运行剩余时间
    uint64 priority; // 运行优先级 1最低 10最高（而不一定是10）
    uint64 pid;      // 线程id
    //前面40个字节
    struct thread_struct thread;
    pagetable_t pgd;
};

/* 线程初始化 创建 NR_TASKS 个线程 */
void task_init();

/* 在时钟中断处理中被调用 用于判断是否需要进行调度 */
void do_timer();

/* 调度程序 选择出下一个运行的线程 */
void schedule();

/* 线程切换入口函数*/
void switch_to(struct task_struct* next);

/* dummy funciton: 一个循环程序, 循环输出自己的 pid 以及一个自增的局部变量 */
void dummy();

/*获得current的pid*/
uint64 getcur_id();
