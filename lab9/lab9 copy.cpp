#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

int type = 1;
int start_point = 0, max_track = 0, track_length = 0;
float avg;
fstream input_file;

void read_default(string path) {
    if (type == 0) {
        cin >> start_point;
        cin >> max_track;
        cin >> track_length;
    } else {
        input_file.open(path, ios::in);
        input_file >> start_point;
        input_file >> max_track;
        input_file >> track_length;
    }
}

void read_tracks(string path, int *track_queue) {
    if (type == 0) {
        for (int i = 0; i < track_length; i++) {
            cin >> track_queue[i];
        }
    } else {
        int temp = 0;
        input_file.open(path, ios::in);
        input_file >> temp;
        input_file >> temp;
        input_file >> temp;
        for (int i = 0; i < track_length; i++) {
            input_file >> track_queue[i];
        }

    }
}

void FCFS(int *track_queue) {
    cout << "FCFS" << endl;
    int range = 0;
    range += abs(track_queue[0] - start_point);
    string connect = " -> ";
    cout << start_point << connect << track_queue[0];
    for (int i = 0; i < track_length - 1; i++) {
        range += abs(track_queue[i] - track_queue[i + 1]);
        cout << connect << track_queue[i + 1];
    }
    cout << endl;
    cout << range << endl;
}

int main() {
    if (type == 0) {
        read_default("");
    } else {
        read_default("1.in");
    }
    int track_queue[track_length];
    cout << start_point << endl;
    cout << max_track << endl;
    cout << track_length << endl;
    if (type == 0) {
        read_tracks("", track_queue);
    } else {
        read_tracks("1.in", track_queue);
    }

    FCFS(track_queue);

}
