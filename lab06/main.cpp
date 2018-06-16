//#include<bits/stdc++.h>
#include<unistd.h>
#include <string>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

#define PROCESS_NAME_LEN 32 //进程名最大长度
#define MIN_SLICE 10 //内碎片最大大小
#define DEFAULT_MEM_SIZE 1024  //总内存大小
#define DEFAULT_MEM_START 0  //内存开始分配时的起始地址

int ma_algorithm = 1;

typedef pair<int, string> My_algo;

int mem_size = DEFAULT_MEM_SIZE;
bool flag = 0;
static int pid = 0;
My_algo algo[123];

struct free_block {    //空闲数据块
    int size;
    int start_addr;
    struct free_block *next;
};

struct allocated_block { //已分配的数据块
    int pid;
    int size;
    int start_addr;
    char process_name[PROCESS_NAME_LEN];
    int *data;
    struct allocated_block *next;
};

free_block *free_block_head; //空闲数据块首指针
allocated_block *allocated_block_head = NULL; //分配块首指针

allocated_block *find_process(int id); //寻找pid为id的分配块
free_block *init_free_block(int mem_size); //空闲块初始化
void display_menu(); //显示选项菜单
int set_mem_size(); //设置内存大小
int allocate_mem(allocated_block *ab); //为制定块分配内存
void rearrange(); // 对块进行重新分配
void rearrange_BF();

void rearrange_WF();

void create_new_process(); //创建新的进程
int free_mem(allocated_block *ab); //释放分配块
void swap(int *p, int *q); //交换地址
int dispose(allocated_block *ab); //释放分配块结构体
void display_mem_usage(); //显示内存情况
void kill_process(); //杀死对应进程并释放其空间与结构体
void use_my_algo(int id); //使用对应的分配算法

//主函数
int main() {
    int op;
    int num_algo;
    pid = 0;
    //初始化一个可以使用的内存块，类似与操作系统可用的总存储空间
    free_block_head = init_free_block(mem_size);
    for (;;) {
        sleep(1);
        display_menu();
        fflush(stdin);
        scanf("%d", &op);
        switch (op) {
            case 1: {
                set_mem_size();
                break;
            }
            case 2: {
                printf("Press 1 for First Fit \n");
                printf("Press 2 for Best Fit \n");
                printf("Press 3 for Worst Fit \n");
                scanf("%d", &num_algo);
                use_my_algo(num_algo);
                break;
            }
            case 3: {
                create_new_process();
                break;
            }
            case 4: {
                kill_process();
                break;
            }
            case 5: {
                display_mem_usage();
                break;
            }
            case 233: {
                puts("bye....");
                sleep(1);
                return 0;
            }
            defaut:
                break;
        }
    }
}

allocated_block *find_process(int id) {
    allocated_block *get_temp = allocated_block_head;
    while (get_temp != NULL) {
        if (get_temp->pid == id) {
            return get_temp;
        } else {
            get_temp = get_temp->next;
        }
    }
    printf("Didn't find target\n");
    return NULL;
}

free_block *init_free_block(int mem_size) {
    free_block *p;
    p = (free_block *) malloc(sizeof(free_block));
    if (p == NULL) {
        puts("No memory left");
        return NULL;
    }
    p->size = mem_size;
    p->start_addr = DEFAULT_MEM_START;
    p->next = NULL;
    return p;
}

void display_menu() {
    puts("\n\n******************menu*******************");
    printf("1) Set memory size (default = %d)\n", DEFAULT_MEM_SIZE);
    printf("2) Set memory allocation algorithm\n");
    printf("3) Create a new process\n");
    printf("4) Kill a process\n");
    printf("5) Display memory usage\n");
    printf("233) Exit\n");
}

//更改最大内存大小
int set_mem_size() {
    int size_of_mem;
    if (flag) {
        printf("The size can only be set once");
        return 0;
    }
    printf("Please input the memory value");
    scanf("%d", &size_of_mem);
    if (size_of_mem > 0) {
        mem_size = size_of_mem;
        free_block_head->size = mem_size;
        flag = 1;
        return 1;
    } else {
        printf("Wrong range of input number");
        return 0;
    }
}

//为块分配内存，真正的操作系统会在这里进行置换等操作
int allocate_mem(allocated_block *ab) {
    struct free_block *fbt;
    int request_size = ab->size;
    fbt = free_block_head->next;
    while (fbt != NULL) {
        if (fbt->size >= request_size) {
            ab->start_addr = fbt->start_addr + fbt->size - request_size;
            fbt->size = fbt->size - request_size;
            return 1;
        } else {
            fbt = fbt->next;
        }
    }
    printf("空闲区不够！\n");
    return 0;
}

//创建新进程
void create_new_process() {
    int size, ret;
    struct allocated_block *ab, *temp;
    printf("Mem");
    ab = (struct allocated_block *) malloc(sizeof(struct allocated_block));
    printf("Mem");
    temp = allocated_block_head->next;
    printf("Mem");
    if (!ab) {
        exit(-5);
    }
    ab->next = NULL;
    pid++;
    sprintf(ab->process_name, "PROCESS-%02d", pid);
    ab->pid = pid;
    printf("Memory for %s:\n", ab->process_name);
    scanf("%d", &size);
    ab->size = size;
    ret = allocate_mem(ab);
    if ((ret == 1) && (allocated_block_head->next == NULL)) {
        allocated_block_head->next = ab;
        printf("ret==1");
        return 1;
    } else if (ret == 1) {
        printf("分配成功\n");
        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = ab;
        return 2;
    } else if (ret == -1) {
        printf("Allocation fail\n");
        free(ab);
        return 1;
    }
    return 3;
}

void swap(int *p, int *q) {
    int tmp = *p;
    *p = *q;
    *q = tmp;
    return;
}

void rearrange() {
    free_block *tmp, *tmpx;
    puts("Rearrange begins...");
    puts("Rearrange by address...");
    tmp = free_block_head;
    while (tmp != NULL) {
        tmpx = tmp->next;
        while (tmpx != NULL) {
            if (tmpx->start_addr < tmp->start_addr) {
                swap(&tmp->start_addr, &tmpx->start_addr);
                swap(&tmp->size, &tmpx->size);
            }
            tmpx = tmpx->next;
        }
        tmp = tmp->next;
    }
    usleep(500);
    puts("Rearrange Done.");
}

void rearrange_BF() {
    return;
}

void rearrange_WF() {
    return;
}

int free_mem(allocated_block *ab) {
    return 0;
}

int dispose(allocated_block *fab) { //释放结构体所占的内存
    allocated_block *pre, *ab;
    if (fab == allocated_block_head) {
        allocated_block_head = allocated_block_head->next;
        free(fab);
        return 1;
    }
    pre = allocated_block_head;
    ab = allocated_block_head->next;
    while (ab != fab) {
        pre = ab;
        ab = ab->next;
    }
    pre->next = ab->next;
    free(ab);
    return 2;
}

void display_mem_usage() {
    free_block *fb = free_block_head;
    allocated_block *ab = allocated_block_head;
    puts("*********************Free Memory*********************");
    printf("%20s %20s\n", "start_addr", "size");
    int cnt = 0;
    while (fb != NULL) {
        cnt++;
        printf("%20d %20d\n", fb->start_addr, fb->size);
        fb = fb->next;
    }
    if (!cnt) puts("No Free Memory");
    else printf("Totaly %d free blocks\n", cnt);
    puts("");
    puts("*******************Used Memory*********************");
    printf("%10s %20s %10s %20s\n", "PID", "ProcessName", "start_addr", "size");
    cnt = 0;
    while (ab != NULL) {
        cnt++;
        printf("%10d %20s %10d %20d\n", ab->pid, ab->process_name, ab->start_addr, ab->size);
        ab = ab->next;
    }
    if (!cnt) puts("No allocated block");
    else printf("Totaly %d allocated blocks\n", cnt);
    return;
}

void kill_process() { //杀死某个进程
    allocated_block *ab;
    int pid;
    puts("Please input the pid of Killed process");
    scanf("%d", &pid);
    ab = find_process(pid);
    if (ab != NULL) {
        free_mem(ab);
        dispose(ab);
    }
}

void use_my_algo(int num_algo) {
    if (num_algo > 1 || num_algo < 3) {
        ma_algorithm = num_algo;
        switch (num_algo) {
            case 1:
                rearrange();
                break;
            case 2:
                rearrange_BF();
                break;
            case 3:
                rearrange_WF();
                break;
        }
    } else {
        printf("Wrong value");
        return;
    }
}


