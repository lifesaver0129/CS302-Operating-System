//#include<bits/stdc++.h>
#include<unistd.h>
#include<iostream>
#include <vector>
#include <cmath>


using namespace std;

const double eps = 1e-8;

int dcmp(const double &x) {
    if (fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

#define DEFAULT_CACHE_SIZE 1024
#define DEFAULT_ALGORITHM 0

typedef pair<int, string> _algorithm;

int cache_size, working_algorithm, hit, miss;
vector<_algorithm> algorithms;
vector<int> pages;

void init();

void print_menu();

void set_cache_size();

void print_algorithms();

void set_algorithm();

void add_an_algorithm();

void generate_input();

void generate_randomly(int n);

void generate_by_hand(int n);

void print_pages();

void FIFO_algorithm();

void run_algorithm();

void read_pages();

void LRU_algorithm();

int main() {
//    freopen("1.in", "r", stdin);
    init();
    generate_input();
    //return 0;
    int op;
    set_cache_size();
    while (cin >> op) {
//        print_menu();
        switch (op) {
            case 1:
                set_cache_size();
                break;
            case 2:
                set_algorithm();
                break;
            case 3:
                add_an_algorithm();
                break;
            case 4:
                run_algorithm();
                break;
            case 5:
                read_pages();
                break;
            case 233:
                cout << "Bye..." << endl;
                sleep(1000);
                return 0;
            default:
                break;
        }
        sleep(1000);
    }
}

void print_pages() {
    cout << "pages number is: ";
    cout << pages.size() << endl;
    cout << "pages are: ";
    for (auto &x : pages) {
        cout << x << " ";
    }
    cout << endl;
}

void generate_randomly(int n) {
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        cout << rand() * 233 % cache_size << " ";
    }
    cout << endl;
}

void generate_by_hand(int n) {
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cout << x << " ";
    }
    cout << endl;
}

void generate_input() {
    pages.clear();
//    cout << "Please input the number of pages: ";
    int n, op;
    cin >> n;
    cout << "1) Generate randomly" << endl;
    cout << "2) Generate by hand" << endl;
    cin >> op;
    freopen("1.in", "w", stdout);
    switch (op) {
        case 1:
            generate_randomly(n);
            break;
        case 2:
            generate_by_hand(n);
            break;
        default:
            break;
    }
}

void init() {
    srand((unsigned int) time(0));
    algorithms.clear();
    pages.clear();
//    cout << "Setting the default cache size..." << endl;
    cache_size = DEFAULT_CACHE_SIZE;
//    sleep(1000);
//    cout << "Setting the default algorithm..." << endl;
    string s = "FIFO";
    algorithms.push_back(make_pair(DEFAULT_ALGORITHM, s));
    s = "LRU";
    algorithms.push_back(make_pair(DEFAULT_ALGORITHM + 1, s));
    working_algorithm = 0;
//    sleep(1000);
//    cout << "Setting the environment..." << endl;
//    sleep(1000);
//    cout << "Setting successfully" << endl;
}

void read_pages() {
    pages.clear();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pages.push_back(x);
    }
    cout << "Read successfully" << endl;
}

void print_menu() {
    cout << "**********MENU**********" << endl;
    cout << "1) set cache size" << endl;
    cout << "2) set algorithm" << endl;
    cout << "3) add an algorithm" << endl;
    cout << "4) run algorithm" << endl;
    cout << "5) read pages" << endl;
    cout << "233) quit" << endl;
}

void set_cache_size() {
//    cout << "Please input the new cache size: ";
    int x;
    cin >> x;
//    if (x <= 0) {
//        cerr << "Invalid cache size" << endl;
//        return;
//    }
    cache_size = x;
//    cout << "set cache size successfully, new cache size is: " << cache_size << endl;
}

void print_algorithms() {
    cout << "All algorithms are: " << endl;
    for (auto &x : algorithms) {
        cout << x.first << " : " << x.second << endl;
    }
}

void set_algorithm() {
    print_algorithms();
    cout << "Please input the index of algorithm" << endl;
    unsigned int id;
    cin >> id;
    working_algorithm = id;
    if (id >= algorithms.size()) {
        cerr << "Algorithm does not exists" << endl;
        return;
    }
    cout << "Set algorithm successfully" << endl;
    cout << "Now working algorithm is: " << algorithms[id].first << ":" << algorithms[id].second << endl;
}

void add_an_algorithm() {
    cout << "Please input the name of new algorithm: ";
    string algo;
    cin >> algo;
    algorithms.push_back(make_pair(algorithms.size(), algo));
    cout << "Algorithm added!" << endl;
    print_algorithms();
}

void FIFO_algorithm() {
}


void LRU_algorithm() {
}

void print_status() {
    cout << "cache size is: " << cache_size << endl;
    //print_pages();
    cout << "working algorithm is " << working_algorithm << ":" << algorithms[working_algorithm].second << endl;
    cout << "hit times = " << hit << endl << "miss times = " << miss << endl;
    cout << "hit percentage is " << (double) hit * 100 / (miss + hit) << "%" << endl;
}

void run_algorithm() {
    switch (working_algorithm) {
        case 0:
            FIFO_algorithm();
            break;
        case 1:
            LRU_algorithm();
            break;
        default:
            break;
    }
    print_status();
}
