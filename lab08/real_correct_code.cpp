//
// Created by lifesaver on 2018/5/6.
//
#include<unistd.h>
#include<iostream>
#include <vector>
#include <cmath>
#include <list>
#include <fstream>

#define DEFAULT_CACHE_SIZE 1024

using namespace std;

list<int> cache_list;
list<int> cache_list_2;
list<int>::iterator iter;

vector<int> cache_vec;
int cache_size = 0, working_algorithm = 0, page_size = 0, hit = 0, total = 0;
bool is_test = false;

fstream input_file;

void generate_input() {
    cin >> cache_size;
    cin >> working_algorithm;
    cin >> page_size;
}

void testing_input(int i, string path, int size) {
    cache_size = size;
    working_algorithm = i;
    input_file.open(path, ios::in);
    input_file >> page_size;
    is_test = true;
}

void FIFO() {
    int temp_input = 0;
    for (int i = 0; i < page_size; i++) {
        total += 1;
        if (is_test) {
            input_file >> temp_input;
        } else {
            cin >> temp_input;
        }
        iter = find(cache_list.begin(), cache_list.end(), temp_input);
        if (iter != cache_list.end()) {
            hit += 1;
        } else {
            if (cache_list.size() != cache_size)
                cache_list.push_back(temp_input);
            else {
                cache_list.push_back(temp_input);
                cache_list.pop_front();
            }
        }
    }
}


void LRU() {
    int temp_input = 0;
    for (int i = 0; i < page_size; i++) {
        total += 1;
        if (is_test) {
            input_file >> temp_input;
        } else {
            cin >> temp_input;
        }
        iter = find(cache_list.begin(), cache_list.end(), temp_input);
        if (iter != cache_list.end()) {
            cache_list.erase(iter);
            cache_list.push_back(temp_input);
            hit += 1;
        } else {
            if (cache_list.size() != cache_size)
                cache_list.push_back(temp_input);
            else {
                cache_list.push_back(temp_input);
                cache_list.pop_front();
            }
        }
    }
}


int search(int key) {
    for (int i = 0; i < cache_vec.size(); i++)
        if (cache_vec[i] == key)
            return i;
    return -1;
}

int find_min_index(int page_list[], int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < cache_vec.size(); i++) {
        int j;
        for (j = index; j < page_size; j++) {
            if (cache_vec[i] == page_list[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == page_size)
            return i;
    }
    return (res == -1) ? 0 : res;
}


void min_algo() {
    int page_list[page_size];
    for (int i = 0; i < page_size; i++) {
        total += 1;
        if (is_test) {
            input_file >> page_list[i];
        } else {
            cin >> page_list[i];
        }
    }
    for (int i = 0; i < page_size; i++) {
        if (search(page_list[i]) != -1) {
            hit += 1;
        } else {
            if (cache_vec.size() < cache_size)
                cache_vec.push_back(page_list[i]);
            else {
                int j = find_min_index(page_list, i + 1);
                cache_vec[j] = page_list[i];
            }
        }
    }
}

int find_clock_index(int *valid_bit, int hand) {
    while (1) {
        if (!valid_bit[hand]) {
            return hand;
        } else {
            valid_bit[hand] = 0;
            hand += 1;
            if (hand == cache_size)
                hand = 0;
        }
    }
}

void clock_algo() {
    int hand = 0;
    int temp_input = 0;
    int valid_bit[cache_size];
    fill_n(valid_bit, cache_size, 1);
    for (int i = 0; i < page_size; i++) {
        total += 1;
        if (is_test) {
            input_file >> temp_input;
        } else {
            cin >> temp_input;
        }
        iter = find(cache_list.begin(), cache_list.end(), temp_input);
        if (search(temp_input) != -1) {
            hand = search(temp_input);
            valid_bit[hand] = 1;
            hit += 1;
        } else {
            if (cache_vec.size() != cache_size) {
                cache_vec.push_back(temp_input);
                hand = cache_vec.size() - 1;
            } else {
                hand = hand % cache_size;
                int j = find_clock_index(valid_bit, hand);
                cache_vec[j] = temp_input;
                hand = j;
            }
        }
    }
}

void second_chance() {
    int temp_input = 0;
    int temp_output = 0;
    for (int i = 0; i < page_size; i++) {
        total += 1;
        if (is_test) {
            input_file >> temp_input;
        } else {
            cin >> temp_input;
        }
        iter = find(cache_list.begin(), cache_list.end(), temp_input);
        if (iter != cache_list.end()) {
            hit += 1;
        } else {
            if (cache_list.size() != cache_size / 2)
                cache_list.push_back(temp_input);
            else {
                iter = find(cache_list_2.begin(), cache_list_2.end(), temp_input);
                if (iter != cache_list_2.end()) {
                    cache_list_2.erase(iter);
                    cache_list.push_back(temp_input);
                    temp_output = cache_list.front();
                    cache_list.pop_front();
                    cache_list_2.push_back(temp_output);
                    hit += 1;
                } else {
                    cache_list.push_back(temp_input);
                    temp_output = cache_list.front();
                    cache_list.pop_front();
                    cache_list_2.push_back(temp_output);
                    if (cache_list_2.size() > cache_size / 2)
                        cache_list_2.pop_front();
                }
            }
        }
    }
}

void print_status() {
    float ans = double(hit) / double(total);
    ans *= 100;
    printf("Hit ratio = %.2f%%\n", ans);
}

int main() {
//    clock_t t1 = clock();
//    generate_input();
    testing_input(3, "1.in", 512);
    switch (working_algorithm) {
        case 0:
            FIFO();
            break;
        case 1:
            LRU();
            break;
        case 2:
            min_algo();
            break;
        case 3:
            clock_algo();
            break;
        case 4:
            second_chance();
            break;
    }
    print_status();
//    cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC << endl;
}