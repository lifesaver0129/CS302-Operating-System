//
// Created by lifesaver on 2018/5/2.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_INDEX 128

int all_tries = 0;
int hits = 0;

typedef struct {
    unsigned int valid;
    unsigned int tag[18];
} _cacheBlock;

void cal_hit() {
    float ans = hits / all_tries;
    printf("Hit ration = %.2f%%\n", ans);
}

int *type_in(char target, int be_added[], int index) {
    switch (target) {
        case '0': {
            be_added[index * 4] = 0;
            be_added[index * 4 + 1] = 0;
            be_added[index * 4 + 2] = 0;
            be_added[index * 4 + 3] = 0;
        }
        case '1': {
            be_added[index * 4] = 0;
            be_added[index * 4 + 1] = 0;
            be_added[index * 4 + 2] = 0;
            be_added[index * 4 + 3] = 1;
        }
        case '2': {
            be_added[index * 4] = 0;
            be_added[index * 4 + 1] = 0;
            be_added[index * 4 + 2] = 1;
            be_added[index * 4 + 3] = 0;
        }
        case '3': {
            be_added[index * 4] = 0;
            be_added[index * 4 + 1] = 0;
            be_added[index * 4 + 2] = 1;
            be_added[index * 4 + 3] = 1;
        }
        case '4': {
            be_added[index * 4] = 0;
            be_added[index * 4 + 1] = 1;
            be_added[index * 4 + 2] = 0;
            be_added[index * 4 + 3] = 0;
        }
        case '5': {
            be_added[index * 4] = 0;
            be_added[index * 4 + 1] = 1;
            be_added[index * 4 + 2] = 0;
            be_added[index * 4 + 3] = 1;
        }
        case '6': {
            be_added[index * 4] = 0;
            be_added[index * 4 + 1] = 1;
            be_added[index * 4 + 2] = 1;
            be_added[index * 4 + 3] = 0;
        }
        case '7': {
            be_added[index * 4] = 0;
            be_added[index * 4 + 1] = 1;
            be_added[index * 4 + 2] = 1;
            be_added[index * 4 + 3] = 1;
        }
        case '8': {
            be_added[index * 4] = 1;
            be_added[index * 4 + 1] = 0;
            be_added[index * 4 + 2] = 0;
            be_added[index * 4 + 3] = 0;
        }
        case '9': {
            be_added[index * 4] = 1;
            be_added[index * 4 + 1] = 0;
            be_added[index * 4 + 2] = 0;
            be_added[index * 4 + 3] = 1;
        }
        case 'A': {
            be_added[index * 4] = 1;
            be_added[index * 4 + 1] = 0;
            be_added[index * 4 + 2] = 1;
            be_added[index * 4 + 3] = 0;
        }
        case 'B': {
            be_added[index * 4] = 1;
            be_added[index * 4 + 1] = 0;
            be_added[index * 4 + 2] = 1;
            be_added[index * 4 + 3] = 1;
        }
        case 'C': {
            be_added[index * 4] = 1;
            be_added[index * 4 + 1] = 1;
            be_added[index * 4 + 2] = 0;
            be_added[index * 4 + 3] = 0;
        }
        case 'D': {
            be_added[index * 4] = 1;
            be_added[index * 4 + 1] = 1;
            be_added[index * 4 + 2] = 0;
            be_added[index * 4 + 3] = 1;
        }
        case 'E': {
            be_added[index * 4] = 1;
            be_added[index * 4 + 1] = 1;
            be_added[index * 4 + 2] = 1;
            be_added[index * 4 + 3] = 0;
        }
        case 'F': {
            be_added[index * 4] = 1;
            be_added[index * 4 + 1] = 1;
            be_added[index * 4 + 2] = 1;
            be_added[index * 4 + 3] = 1;
        }
    }
    return be_added;
}

void two_list_clear(int twoup[]) {
    for (int i = 0; i < 28; i++) {
        twoup[i] = 0;
    }
}

void check_hit(_cacheBlock *array, char input[]) {
    int *twoup[28];
    for (int i = 0; i < 8; i++) {
        *twoup = type_in(input[i], *twoup, i);
    }
    printf(*twoup);
}

int main() {
    _cacheBlock *array;
    for (int i = 0; i < 64; i++) {
        array[i].valid = 0;
        for (int z = 0; z < 18; z++) {
            array[i].tag[z] = 0;
        }
    }
    char input[8];
    char end_val[] = "END";
    scanf("%s", &input);
    while (strcmp(input, end_val) != 0) {
        check_hit(array, input);
        scanf("%s", &input);
    };
    cal_hit();
    return 0;
}