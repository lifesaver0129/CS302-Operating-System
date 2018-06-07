#include <vector>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <zconf.h>
#include <sstream>

using namespace std;

string curr_path = "/";
string curr_user = "root";
bool error = false;
vector<string> path;

typedef struct user {
    string username;
    string password;
} user;

typedef struct file {
    string filename;
    int omode;
} file;

typedef struct dir {
    vector<dir *> dirs;
    vector<file *> files;
    string dirname;
} dir;

dir *root_dir = new dir();
dir *curr_dir = root_dir;
dir *op_dir = root_dir;

void name(){
    cout << curr_dir->dirname << endl;
}

void prepare_stat() {
    cout << curr_user << "$" << curr_path << "%:";
    error = false;
    op_dir = curr_dir;
}

void div_path(string target_path) {
    stringstream input(target_path);
    string temp;
    while (getline(input, temp, '/')) {
        path.push_back(temp);
    }
    op_dir = root_dir;
    if (target_path == "/") {
        path.clear();
        return;
    }
    for (auto item : path) {
        if (item == ""){
            continue;
        }
        bool find = false;
        for (auto dir1 : op_dir->dirs) {
            if (dir1->dirname == item) {
                op_dir = dir1;
                find = true;
                break;
            }
        }
        if (!find) {
            cout << "directory does not exist" << endl;
            error = true;
            break;
        }
    }
    path.clear();
}

void check_tar_dup(string tar_name, bool isFile) {
    if (isFile) {
        for (auto file1 : op_dir->files) {
            if (file1->filename == tar_name) {
                cout << "file already exists" << endl;
                error = true;
                break;
            }
        }
    } else {
        for (auto dir1 : op_dir->dirs) {
            if (dir1->dirname == tar_name) {
                cout << "directory already exists" << endl;
                error = true;
                break;
            }
        }
    }
}

void check_tar_exist(string tar_name, bool isFile) {
    error = true;
    if (isFile) {
        for (auto file1 : op_dir->files) {
            if (file1->filename == tar_name) {
                error = false;
                break;
            }
        }
        if (error) {
            cout << "file does not exist" << endl;
        }
    } else {
        for (auto dir1 : op_dir->dirs) {
            if (dir1->dirname == tar_name) {
                error = false;
                break;
            }
        }
        if (error) {
            cout << "directory does not exist" << endl;
        }
    }
}

void man() {
    cout << "Manual:" << endl;
    cout << "0) pwd (current work directory)" << endl;
    cout << "1) mkdir(p) (path) directory_name" << endl;
    cout << "2) dedir(p) (path) directory_name" << endl;
    cout << "3) search file_name" << endl;
    cout << "4) create(p) (path) file_name omode" << endl;
    cout << "5) cat(p) (path) file_name" << endl;
    cout << "6) delete(p) (path) file_name" << endl;
    cout << "7) write(p) (path) file_name buff wmode" << endl;
    cout << "8) reposition(p) (path) file_name pos" << endl;
    cout << "9) truncate (p) (path) file_name cnt" << endl;
    cout << "10) ls(p) (path)" << endl;
    cout << "11) open(p) (path) file_name" << endl;
    cout << "12) close(p) (path) file_name" << endl;
    cout << "13) regusr user_name password" << endl;
    cout << "14) delusr user_name [root only]" << endl;
    cout << "15) disusr" << endl;
    cout << "16) login user_name" << endl;
    cout << "17) lsfile" << endl;
    cout << "18) chmod(p) (path) file_name mode" << endl;
    cout << "19) exit" << endl;
}

void pwd() {
    cout << curr_path << endl;
};

void ls() {
    for (auto dir1 : op_dir->dirs) {
        cout << dir1->dirname <<endl;
    }
    for (auto file1 : op_dir->files) {
        cout << file1->filename <<endl;
    }
};

void lsp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        ls();
    }
};

void mkdir() {
    string dir_name;
    cin >> dir_name;
    check_tar_dup(dir_name, false);
    if (!error) {
        dir *tmp = new dir;
        tmp->dirname = dir_name;
        op_dir->dirs.push_back(tmp);
    }

};

void mkdirp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        mkdir();
    }
};

void cd() {
    string dir_name;
    cin >> dir_name;
    check_tar_exist(dir_name, false);
    if (!error) {
        for (auto dir1 : op_dir->dirs) {
            if (dir1->dirname == dir_name) {
                curr_dir = dir1;
                curr_path = curr_path + dir_name + "/";
                break;
            }
        }
    }
};

void cdp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        curr_dir = op_dir;
        curr_path = target_path;
    }
};

void dedir() {
    string dir_name;
    cin >> dir_name;
    check_tar_exist(dir_name, false);
    if (!error) {
        for (int i = 0; i < op_dir->dirs.size(); ++i) {
            if (op_dir->dirs[i]->dirname == dir_name) {
                delete (op_dir->dirs[i]);
                op_dir->dirs.erase(op_dir->dirs.begin() + i);
                break;
            }
        }
    }
};

void dedirp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        dedir();
    }
};

void create() {
    string fname;
    cin >> fname;
    int fmode;
    cin >> fmode;
    check_tar_dup(fname, true);
    if (!error) {
        file *tmp = new file();
        tmp->filename = fname;
        tmp->omode = fmode;
        op_dir->files.push_back(tmp);
    }
};

void createp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error){
        create();
    }
};

void search() {

};

void open() {

};

void openp() {

};

void lsfile() {

};


void lsfilep() {

};

void write() {

};

void writep() {

};

void reposition() {

};


void repositionp() {

};

void cat() {

};

void catp() {

};

void truncate() {

};

void truncatep() {

};

void chmod() {

};

void chmodp() {

};

void close() {

};

void closep() {

};

void deletei() {

};

void deletep() {

};

void regusr() {

};

void delusr() {

};

void disusr() {

};

void login() {

};

int main() {
    while (true) {
        prepare_stat();
        string input1;
        cin >> input1;
        if (input1 == "man")
            man();
        else if (input1 == "pwd")
            pwd();
        else if (input1 == "ls")
            ls();
        else if (input1 == "lsp")
            lsp();
        else if (input1 == "mkdir")
            mkdir();
        else if (input1 == "mkdirp")
            mkdirp();
        else if (input1 == "cd")
            cd();
        else if (input1 == "cdp")
            cdp();
        else if (input1 == "dedir")
            dedir();
        else if (input1 == "dedirp")
            dedirp();
        else if (input1 == "create")
            create();
        else if (input1 == "createp")
            createp();
        else if (input1 == "search")
            search();
        else if (input1 == "open")
            open();
        else if (input1 == "openp")
            openp();
        else if (input1 == "lsfile")
            lsfile();
        else if (input1 == "write")
            write();
        else if (input1 == "writep")
            writep();
        else if (input1 == "reposition")
            reposition();
        else if (input1 == "repositionp")
            repositionp();
        else if (input1 == "cat")
            cat();
        else if (input1 == "catp")
            catp();
        else if (input1 == "truncate")
            truncate();
        else if (input1 == "truncatep")
            truncatep();
        else if (input1 == "chmod")
            truncate();
        else if (input1 == "chmodp")
            truncate();
        else if (input1 == "close")
            truncate();
        else if (input1 == "closep")
            truncate();
        else if (input1 == "delete")
            deletei();
        else if (input1 == "deletep")
            deletep();
        else if (input1 == "regusr")
            regusr();
        else if (input1 == "delusr")
            delusr();
        else if (input1 == "disusr")
            disusr();
        else if (input1 == "login")
            login();
        else if (input1 == "exit")
            break;
        else if (input1 == "name")
            name();
        else
            continue;
    }
}

//tempwrong: duplicate input parameter

