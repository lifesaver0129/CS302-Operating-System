#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;

int all_tries = 0;
int hits = 0;

typedef struct {
    bool valid;
    string tag;
} cache_block;

void cal_hit() {
    float ans = double(hits) / double(all_tries);
    ans *=100;
    printf("Hit ration = %.2f%%\n", ans);
}

const char *hex_char_to_bin(char c) {
    switch (toupper(c)) {
        case '0':
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'A':
            return "1010";
        case 'B':
            return "1011";
        case 'C':
            return "1100";
        case 'D':
            return "1101";
        case 'E':
            return "1110";
        case 'F':
            return "1111";
    }
}

string hex_str_to_bin_str(const string &hex) {
    string bin;
    for (unsigned i = 0; i != hex.length(); ++i)
        bin += hex_char_to_bin(hex[i]);
    return bin;
}

void check_hit(cache_block array[], string input) {
    all_tries += 1;
    string x = hex_str_to_bin_str(input);
    string ind = x.substr(18, 6);
    string tag = x.substr(0, 18);
    int index = stoull(ind, 0, 2);
    if (!array[index].valid) {
        array[index].valid = true;
        array[index].tag = tag;
        cout << "Miss" << endl;
    } else {
        if (array[index].tag.compare(tag) != 0){
            array[index].tag = tag;
            cout << "Miss" << endl;
        }else{
            cout << "Hit" << endl;
            hits += 1;
        }
    }
}

int main() {
    cache_block cache_array[64];
    for (int i = 0; i < 64; i++) {
        cache_array[i].valid = false;
        cache_array[i].tag = "";
    }
    string input;
    cin >> input;
    while (input.compare("END") != 0) {
        check_hit(cache_array, input);
        cin >> input;
    };
    cal_hit();
    return 0;
}
