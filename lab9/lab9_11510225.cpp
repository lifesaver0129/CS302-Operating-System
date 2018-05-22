#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>


using namespace std;

int type = 0;
string path = "/Users/lifesaver/Documents/University/OS/CS302-Operating-System/lab9/3.in";
string connect = " -> ";
int start_point = 0, max_track = 0, track_length = 0;
fstream input_file;
fstream input_file2;

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
        input_file2.open(path, ios::in);
        input_file2 >> temp;
        input_file2 >> temp;
        input_file2 >> temp;
        for (int i = 0; i < track_length; i++) {
            input_file2 >> track_queue[i];
        }

    }
}

void FCFS(int *track_queue) {
    cout << "FCFS" << endl;
    int range = 0;
    range += abs(track_queue[0] - start_point);
    cout << start_point << connect << track_queue[0];
    for (int i = 0; i < track_length - 1; i++) {
        range += abs(track_queue[i] - track_queue[i + 1]);
        cout << connect << track_queue[i + 1];
    }
    cout << endl;
    cout << range << endl;
}

void SSTF(int *track_queue) {
    cout << "SSTF" << endl;
    int range = 0;
    int temp_range = abs(track_queue[0] - start_point);
    int temp_index = 0;
    for (int i = 1; i < track_length; i++) {
        if (abs(track_queue[i] - start_point) < temp_range) {
            temp_range = abs(track_queue[i] - start_point);
            temp_index = i;
        }
    }
    swap(track_queue[0], track_queue[temp_index]);
    range += abs(track_queue[0] - start_point);
    cout << start_point << connect << track_queue[0];
    for (int i = 0; i < track_length - 1; i++) {
        temp_range = abs(track_queue[i + 1] - track_queue[i]);
        temp_index = i + 1;
        for (int j = i + 2; j < track_length; j++) {
            if (abs(track_queue[j] - track_queue[i]) < temp_range) {
                temp_range = abs(track_queue[j] - track_queue[i]);
                temp_index = j;
            }
        }
        swap(track_queue[i + 1], track_queue[temp_index]);
        range += abs(track_queue[i] - track_queue[i + 1]);
        cout << connect << track_queue[i + 1];

    }
    cout << endl;
    cout << range << endl;
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int find_start_point(int *arr) {
    int index = 0;
    for (int i = 1; i < track_length; i++) {
        if (arr[i] <= start_point)
            index = i;
    }
    return index;
}

void SCAN(int *track_queue) {
    quickSort(track_queue, 0, track_length - 1);
    cout << "SCAN" << endl;
    int range = 0;
    if (track_length == 1) {
        cout << start_point;
        if (track_queue[0] > start_point) {
            range += abs(2 * start_point);
            cout << connect << 0;
        }
        cout << connect << track_queue[0];
        range += abs(track_queue[0] - start_point);
        cout << endl;
        cout << range << endl;
        return;
    }
    int list_start_point = find_start_point(track_queue);
    if (track_queue[list_start_point] <= start_point) {
        range += abs(track_queue[list_start_point] - start_point);
        cout << start_point << connect << track_queue[list_start_point];
        if (list_start_point > 0) {
            for (int i = list_start_point; i > 0; i--) {
                range += abs(track_queue[i] - track_queue[i - 1]);
                cout << connect << track_queue[i - 1];
            }
        }
    } else {
        cout << start_point;
        range += start_point;
    }
    if (list_start_point < track_length - 1) {
        cout << connect << 0;
        range += abs(track_queue[0]);
        for (int i = list_start_point; i < track_length - 1; i++) {
            range += abs(track_queue[i] - track_queue[i + 1]);
            cout << connect << track_queue[i + 1];
        }
    }
    cout << endl;
    cout << range << endl;
}

void CSCAN(int *track_queue) {
    cout << "C-SCAN" << endl;
    int range = 0;
    if (track_length == 1) {
        cout << start_point;
        if (track_queue[0] > start_point) {
            range += max_track - 1 - track_queue[0] + start_point;
            cout << connect << 0 << connect << max_track - 1 << connect << track_queue[0];

        } else {
            cout << connect << track_queue[0];
            range += abs(track_queue[0] - start_point);
        }
        cout << endl;
        cout << range << endl;
        return;
    }
    int list_start_point = find_start_point(track_queue);
    if (track_queue[list_start_point] <= start_point) {
        range += abs(track_queue[list_start_point] - start_point);
        cout << start_point << connect << track_queue[list_start_point];
        if (list_start_point > 0) {
            for (int i = list_start_point; i > 0; i--) {
                range += abs(track_queue[i] - track_queue[i - 1]);
                cout << connect << track_queue[i - 1];
            }
        }
    } else {
        cout << start_point;
        range += start_point;
    }
    if (list_start_point < track_length - 1) {
        cout << connect << 0 << connect << max_track - 1;
        range += abs(max_track - 1 - track_queue[track_length - 1]);
        cout << connect << track_queue[track_length - 1];
        for (int i = track_length - 1; i > list_start_point + 1; i--) {
            range += abs(track_queue[i] - track_queue[i - 1]);
            cout << connect << track_queue[i - 1];
        }
        if (track_queue[list_start_point] > start_point) {
            cout << connect << track_queue[list_start_point];
            range += abs(track_queue[list_start_point] - track_queue[list_start_point + 1]);
        }
    }
    cout << endl;
    cout << range << endl;
}

void LOOK(int *track_queue) {
    cout << "LOOK" << endl;
    int range = 0;
    int list_start_point = find_start_point(track_queue);
    if (track_length == 1) {
        cout << start_point << connect << track_queue[0];
        range += abs(track_queue[0] - start_point);
        cout << endl;
        cout << range << endl;
        return;
    }
    range += abs(track_queue[list_start_point] - start_point);
    cout << start_point << connect << track_queue[list_start_point];
    if (list_start_point > 0) {
        for (int i = list_start_point; i > 0; i--) {
            range += abs(track_queue[i] - track_queue[i - 1]);
            cout << connect << track_queue[i - 1];
        }
    }
    if (list_start_point < track_length - 1) {
        range += abs(track_queue[list_start_point + 1] - track_queue[0]);
        cout << connect << track_queue[list_start_point + 1];
        for (int i = list_start_point + 1; i < track_length - 1; i++) {
            range += abs(track_queue[i] - track_queue[i + 1]);
            cout << connect << track_queue[i + 1];
        }
    }
    cout << endl;
    cout << range << endl;
}

void CLOOK(int *track_queue) {
    cout << "C-LOOK" << endl;
    int range = 0;
    int list_start_point = find_start_point(track_queue);
    if (track_length == 1) {
        cout << start_point;
        if (track_queue[0] < start_point) {
            range += start_point - track_queue[0];
        }
        cout << connect << track_queue[0] << endl;
        cout << range << endl;
        return;
    }
    if (track_queue[list_start_point] <= start_point) {
        range += abs(track_queue[list_start_point] - start_point);
        cout << start_point << connect << track_queue[list_start_point];
        if (list_start_point > 0) {
            for (int i = list_start_point; i > 0; i--) {
                range += abs(track_queue[i] - track_queue[i - 1]);
                cout << connect << track_queue[i - 1];
            }
        }
    } else {
        cout << start_point;
    }
    if (list_start_point < track_length - 1) {
//        range += abs(max_track - 1 - track_queue[track_length - 1] + track_queue[0]);
        cout << connect << track_queue[track_length - 1];
        for (int i = track_length - 1; i > list_start_point + 1; i--) {
            range += abs(track_queue[i] - track_queue[i - 1]);
            cout << connect << track_queue[i - 1];
        }
        if (track_queue[list_start_point] > start_point) {
            cout << connect << track_queue[list_start_point];
            range += abs(track_queue[list_start_point] - track_queue[list_start_point + 1]);
        }
    }
    cout << endl;
    cout << range << endl;
}

int main() {
    if (type == 0) {
        read_default("");
    } else {
        read_default(path);
    }
    int track_queue[track_length];
    if (type == 0) {
        read_tracks("", track_queue);
    } else {
        read_tracks(path, track_queue);
    }
    FCFS(track_queue);
    SSTF(track_queue);
    SCAN(track_queue);
    CSCAN(track_queue);
    LOOK(track_queue);
    CLOOK(track_queue);
}
