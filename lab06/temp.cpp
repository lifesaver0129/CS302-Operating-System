//#include<bits/stdc++.h>
#include<unistd.h>
#include <string>

#define PROCESS_NAME_LEN 32
#define MIN_SLICE 10
#define DEFAULT_MEM_SIZE 1024
#define DEFAULT_MEM_START 0

using namespace std;

typedef pair<int, string> My_algo;

int mem_size = DEFAULT_MEM_SIZE;
bool flag = 0;
static int pid = 0;
My_algo algo[123];
int curr_algo = 1;

struct free_block {
    int size;
    int start_addr;
    struct free_block *next;
};

struct allocated_block {
    int pid;
    int size;
    int start_addr;
    char process_name[PROCESS_NAME_LEN];
    int *data;
    struct allocated_block *next;
};

struct free_block *free_block_head;

struct allocated_block *allocated_block_head = NULL;

struct allocated_block *find_process(int id);

struct free_block *init_free_block(int mem_size);

void display_menu();

int set_mem_size();

int allocate_mem(struct allocated_block *ab);

void rearrange_FF();

void rearrange_BF();

void rearrange_WF();

void rearrange(int new_algo);

void create_new_process();

int free_mem(struct allocated_block *ab);

void swap(int *p, int *q);

int dispose(struct allocated_block *ab);

void display_mem_usage();

int kill_process();

void use_my_algo(int id);

int set_algorithm(int i);

int main() {
    int op;
    int num_algo;
    pid = 0;
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
                set_algorithm(num_algo);
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
            default:
                break;
        }
    }
}

allocated_block *find_process(int id) {
    allocated_block *curr_ab = allocated_block_head;
    while (curr_ab != NULL) {
        if (curr_ab->pid != id) {
            curr_ab = curr_ab->next;
        } else {
            return curr_ab;
        }
    }
    printf("No such ID");
    return NULL;
}

free_block *init_free_block(int mem_size) {
    free_block *r, *p;
    allocated_block_head = (allocated_block *) malloc(sizeof(allocated_block));
    r = (free_block *) malloc(sizeof(free_block));
    p = (free_block *) malloc(sizeof(free_block));
    if (r == NULL) {
        puts("No memory left");
        return NULL;
    }
    allocated_block_head->next = NULL;
    r->next = p;
    p->size = mem_size;
    p->start_addr = DEFAULT_MEM_START;
    p->next = NULL;
    return r;
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

int set_mem_size() {
    int size_of_mem;
    if (flag) {
        printf("The size can only be set once\n");
        return 0;
    }
    printf("Please input the memory value\n");
    scanf("%d", &size_of_mem);
    if (size_of_mem > 0) {
        mem_size = size_of_mem;
        free_block_head->next->size = mem_size;
        flag = 1;
        return 1;
    } else {
        printf("Wrong range of input number\n");
        return 0;
    }
}

void swap(int *p, int *q) {
    int tmp = *p;
    *p = *q;
    *q = tmp;
    return;
}

int allocate_mem(struct allocated_block *ab) {
    free_block *fb;
    int request_size = ab->size;
    int real_size = request_size;
    fb = free_block_head->next;
    while (fb) {
        if (fb->size < request_size) {
            fb = fb->next;
        } else {
            fb->size -= request_size;
            if (fb->size < MIN_SLICE) {
                real_size += fb->size;
                fb->size = 0;
            }
            ab->start_addr = fb->start_addr + fb->size;
            return real_size;
        }
    }
    printf("There's no enough space\n");
    return 0;
}

void create_new_process() {
    int size_of_p, result;
    allocated_block *ab, *temp;
    ab = (allocated_block *) malloc(sizeof(allocated_block));
    temp = allocated_block_head->next;
    ab->next = NULL;
    pid++;
    sprintf(ab->process_name, "p%02d", pid);
    ab->pid = pid;
    printf("How large do you wanna give?\n");
    scanf("%d", &size_of_p);
    ab->size = size_of_p;
    result = allocate_mem(ab);
    if (result) {
        ab->size = result;
        if (allocated_block_head->next == NULL) {
            allocated_block_head->next = ab;
            printf("Finished\n");
        } else {
            printf("Finished\n");
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = ab;
        }
    } else {
        printf("Warning! Didn't input correctly\n");
        free(ab);
        pid--;
    }
}

int free_mem(struct allocated_block *ab) {
    free_block *curr, *pre;
    int clk = 0;
    curr = (free_block *) malloc(sizeof(free_block));
    if (curr == NULL)
        return -1;
    pre = free_block_head->next;
    curr->start_addr = ab->start_addr;
    curr->size = ab->size;
    while (pre->next) {
        pre = pre->next;
    }
    curr->next = NULL;
    pre->next = curr;
    rearrange(curr_algo);
    pre = free_block_head->next;
    while (pre->next != NULL) {
        if (pre->start_addr == pre->next->start_addr - pre->size) {
            pre->size = pre->size + pre->next->size;
            if (pre->next->next == NULL) {
                pre->next = NULL;
                break;
            } else {
                pre->next = pre->next->next;
            }
        }
        pre = pre->next;
    }
    pre = free_block_head->next;
    while (pre->next != NULL) {
        if (pre->start_addr == pre->next->start_addr - pre->size) {
            pre->size = pre->size + pre->next->size;
            if (pre->next->next == NULL) {
                pre->next = NULL;
                break;
            } else {
                pre->next = pre->next->next;
            }
        }
        pre = pre->next;
    }

    return 1;
}

int dispose(struct allocated_block *fab) {
    struct allocated_block *pre, *ab;
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
    free_block *fb = free_block_head->next;
    allocated_block *ab = allocated_block_head->next;
    puts("*********************Free Memory*********************");
    printf("%20s %20s\n", "start_addr", "size");
    int cnt = 0;
    int real_cnt = 0;
    while (fb != NULL) {
        cnt++;
        if (fb->start_addr < 100000 && fb->size > 0) {
            printf("%20d%20d\n", fb->start_addr, fb->size);
            real_cnt += 1;
        }
        fb = fb->next;
    }
    if (!real_cnt)
        puts("No Free Memory");
    puts("");
    puts("*******************Used Memory*********************");
    printf("%10s %20s %10s %20s\n", "PID", "ProcessName", "start_addr", "size");
    cnt = 0;
    while (ab != NULL) {
        cnt++;
        printf("%10d %20s %10d %20d \n", ab->pid, ab->process_name, ab->start_addr, ab->size);
        ab = ab->next;
    }
    if (!cnt)
        puts("No allocated block");
    else
        printf("Totaly %d allocated blocks\n", cnt);
    return;

}

int kill_process() {
    allocated_block *ab;
    int pid;
    printf("Please input the pid of Killed process\n");
    scanf("%d", &pid);
    ab = find_process(pid);
    if (ab != NULL) {
        free_mem(ab);
        dispose(ab);
    }
    return 0;
}

void rearrange_FF() {
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
    free_block *tmp, *tmpx;
    puts("Rearrange begins...");
    puts("Rearrange by address...");
    tmp = free_block_head;
    while (tmp != NULL) {
        tmpx = tmp->next;
        while (tmpx != NULL) {
            if (tmpx->size > tmp->size) {
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

void rearrange_WF() {
    free_block *tmp, *tmpx;
    puts("Rearrange begins...");
    puts("Rearrange by address...");
    tmp = free_block_head;
    while (tmp != NULL) {
        tmpx = tmp->next;
        while (tmpx != NULL) {
            if (tmpx->size < tmp->size) {
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

void rearrange(int new_algo) {
    if (new_algo == 1)
        rearrange_FF();
    else if (new_algo == 2)
        rearrange_BF();
    else
        rearrange_WF();
    curr_algo = new_algo;
}

int set_algorithm(int new_algo) {
    if (new_algo < 1 && new_algo <= 3) {
        curr_algo = new_algo;
        rearrange(curr_algo);
    }
}