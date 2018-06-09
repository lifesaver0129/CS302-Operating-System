#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
//Some global variables needs to declare: current path, error flag and input path storage vector
string curr_path = "/";
bool error = false;
vector<string> path;
//User structure, including username and password
typedef struct user {
    string username;
    string password;
} user;
//File structure, including creator, filename, mode, open flag, content, and position
typedef struct file {
    string creator;
    string filename;
    int omode;
    bool is_open;
    string context;
    int pointer;
} file;
//Directory structure, including subdirectories, files and name of current directory.
typedef struct dir {
    vector<dir *> dirs;
    vector<file *> files;
    string dirname;
} dir;
//A opened file structure, except for a pointer that point to file, also added the opener and path of opened file.
typedef struct opfile {
    file *opf_file;
    string opf_opener;
    string opf_path;
} opfile;
//A list that store all the opening files.
typedef struct oplist {
    vector<opfile *> opfiles;
} oplist;
//A list that store all current users.
typedef struct user_list {
    vector<user *> users;
} userlist;
//Some declaration before inputs, including root directory and current user set, opening file list and user list.
dir *root_dir = new dir();
dir *curr_dir = root_dir;
dir *op_dir = root_dir;
oplist *open_list = new oplist();
userlist *user_list = new userlist();
user *curr_user;
//Initialize the root user and add it into current user.
void prepare_user() {
    user *root_user = new user();
    root_user->username = "root";
    root_user->password = "111";
    user_list->users.push_back(root_user);
    curr_user = root_user;
}
//This operation is set before every input.
void prepare_stat() {
    cout << curr_user->username << "$" << curr_path << "%:";
    error = false;
    op_dir = curr_dir;
}
//Using for set the operation path for each command that including a path
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
        if (item == "") {
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
//This method is used to check whether there's already a targit in it.
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
//This method is used to check whether there's a target in it.
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
//Mannal method, print the manual.
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
    cout << "19) cd(p) (path) dir_name" << endl;
    cout << "20) exit" << endl;
}
//Print working directory method, print current path.
void pwd() {
    cout << curr_path << endl;
};
//List method, print all the directories and files out.
void ls() {
    for (auto dir1 : op_dir->dirs) {
        cout << dir1->dirname << endl;
    }
    for (auto file1 : op_dir->files) {
        cout << file1->filename << endl;
    }
};
//List method with a path, first redirect the path then print the files out.
void lsp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        ls();
    }
};
//Make directory method, used for initializing a new directory.
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
//Make directory method with a path, first redirect the path and then initialize a directory.
void mkdirp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        mkdir();
    }
};
//Change directory method, used for changing current directory.
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
//Change directory method with a path, first redirect the path and then without change the directory.
void cdp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        curr_dir = op_dir;
        curr_path = target_path;
    }
};
//Delete directory method, used for deleting directories.
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
//Delete directory method with a path, first redirect the path and then delete the directory.
void dedirp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        dedir();
    }
};
//Create method, used for create file on current path.
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
        tmp->creator = curr_user->username;
        op_dir->files.push_back(tmp);
    }
};
//Create methode with a path, first redirect to the operation path then delete.
void createp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        create();
    }
};
//Search method, used for searching file using depth first search.
void search(string spath, string sname) {
    error = true;
    for (auto file1 : op_dir->files) {
        if (file1->filename == sname) {
            cout << spath << sname << endl;
            error = false;
        }

    }
    for (auto dir1 : op_dir->dirs) {
        spath = spath + dir1->dirname + "/";
        op_dir = dir1;
        search(spath, sname);
    }

};
//Open method, used for oping file which located on current path.
void open(string opath) {
    string ofname;
    cin >> ofname;
    check_tar_exist(ofname, true);
    if (!error) {
        for (auto file1 : op_dir->files) {
            if (file1->filename == ofname) {
                if (file1->is_open) {
                    cout << "file already open" << endl;
                    return;
                }
                opfile *tmp = new opfile();
                tmp->opf_opener = curr_user->username;
                tmp->opf_file = file1;
                file1->is_open = true;
                tmp->opf_path = opath;
                open_list->opfiles.push_back(tmp);
                break;
            }
        }
    }
};
//Open file method with a path, which allow us to open the file in that path.
void openp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        open(target_path);
    }
};
//Display all the file, go through the open file list and print out the info that required.
void lsfile() {
    for (auto file1 : open_list->opfiles) {
        cout << file1->opf_path << " " << file1->opf_file->filename
             << " " << file1->opf_file->creator << " " << file1->opf_opener
             << " " << file1->opf_file->omode << endl;
    }
};
//Write method, first check existance, then check permission, serveral types are there for user to choose.
void write() {
    string wfname, wcontent;
    int wmode;
    cin >> wfname >> wcontent >> wmode;
    check_tar_exist(wfname, true);
    if (!error) {
        for (auto file1 : op_dir->files) {
            if (file1->filename == wfname) {
                if (file1->is_open) {
                    if (file1->omode % 4 > 1) {
                        if (wmode == 0) {
                            file1->context += wcontent;
                        } else if (wmode == 1) {
                            string ncontent = file1->context.substr(0, file1->pointer);
                            ncontent += wcontent;
                            if (file1->context.length() > file1->pointer + wcontent.length()) {
                                ncontent += file1->context.substr(file1->pointer + wcontent.length());
                            }
                            file1->context = ncontent;
                        } else if (wmode == 2) {
                            string ncontent1 = file1->context.substr(0, file1->pointer);
                            string ncontent2 = file1->context.substr(file1->pointer);
                            file1->context = ncontent1 + wcontent + ncontent2;
                        }
                        file1->pointer = file1->context.length();
                        cout << "write ok" << endl;
                    } else {
                        cout << "permission denied" << endl;
                        return;
                    }
                } else {
                    cout << "file does not open" << endl;
                    return;
                }
            }
        }
    }
}
//Write the file that is in target path. Check the existance then go write() function.
void writep() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        write();
    }
};
//Reposition the pointer of the file, check existance and then change the pointer.
void reposition() {
    string rfile;
    int rpos = 0;
    cin >> rfile >> rpos;
    check_tar_exist(rfile, true);
    if (!error) {
        for (auto file1 : op_dir->files) {
            if (file1->filename == rfile) {
                if (rpos >= 0 && rpos <= file1->context.length()) {
                    file1->pointer = rpos;
                    cout << "reposition ok" << endl;
                } else {
                    cout << "reposition failed" << endl;
                }
                break;
            }
        }
    }
}
//Reposition the pointer that in specific path.
void repositionp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        reposition();
    }
};
//Display the content of the file, check existance, permission, and then print the content of the file.
void cat() {
    string cfile;
    cin >> cfile;
    check_tar_exist(cfile, true);
    if (!error) {
        for (auto file1 : op_dir->files) {
            if (file1->filename == cfile) {
                if (file1->is_open) {
                    if (file1->omode >= 4) {
                        cout << file1->context << endl;
                    } else {
                        cout << "permission denied" << endl;
                    }
                    break;
                } else {
                    cout << "file does not open" << endl;
                    return;
                }
            }
        }
    }
};
//Concatenate method, with a redirect path.
void catp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        cat();
    }
};
//Truncate method, used to truncate the content of the file.
void truncate() {
    string tfile;
    int tindex = 0;
    cin >> tfile >> tindex;
    check_tar_exist(tfile, true);
    if (!error) {
        for (auto file1 : op_dir->files) {
            if (file1->filename == tfile) {
                file1->context = file1->context.substr(0, tindex);
                file1->pointer = static_cast<int>(file1->context.length());
            }
            break;
        }
    }
};
//Truncataed method with a path to redirect.
void truncatep() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        truncate();
    }
};
//Change mode function, used to change the permission of a target.
void chmod() {
    string cmfile;
    int cmindex = 0;
    cin >> cmfile >> cmindex;
    check_tar_exist(cmfile, true);
    if (!error) {
        for (auto file1 : op_dir->files) {
            if (file1->filename == cmfile) {
                file1->omode = cmindex;
            }
            break;
        }
    }
};
//Change mode function with a target path.
void chmodp() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        chmod();
    }
};
//Close function, check the existance, whether that file is open, and finally the permission.
void close(string clpath) {
    string clfile;
    cin >> clfile;
    check_tar_exist(clfile, true);
    error = true;
    for (int i = 0; i < open_list->opfiles.size(); ++i) {
        if (open_list->opfiles[i]->opf_file->filename == clfile
            && open_list->opfiles[i]->opf_path == clpath) {
            error = false;
            open_list->opfiles[i]->opf_file->is_open = false;
            delete (open_list->opfiles[i]);
            open_list->opfiles.erase(open_list->opfiles.begin() + i);
            break;
        }
    }
    if (error) {
        cout << "file does not open" << endl;
    }
};
//Close function with a path inside of it.
void closep() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        close(target_path);
    }
};
//Delete the file, needs to check the existance, and if that file is open, close it to continue.
void deletei(string dpath) {
    string file_name;
    cin >> file_name;
    check_tar_exist(file_name, true);
    if (!error) {
        for (int i = 0; i < op_dir->files.size(); ++i) {
            if (op_dir->files[i]->filename == file_name) {
                if (open_list->opfiles[i]->opf_file->filename == file_name
                    && open_list->opfiles[i]->opf_path == dpath) {
                    delete (open_list->opfiles[i]);
                    open_list->opfiles.erase(open_list->opfiles.begin() + i);
                }
                delete (op_dir->files[i]);
                op_dir->files.erase(op_dir->files.begin() + i);
                break;
            }
        }
    }
};
//Close file with a path inside of it.
void deletep() {
    string target_path;
    cin >> target_path;
    div_path(target_path);
    if (!error) {
        deletei(target_path);
    }
};
//Register new user, needs to input password and username. Duplication is not allowed.
void regusr() {
    string rusername, rpassword;
    cin >> rusername >> rpassword;
    for (auto user1 : user_list->users) {
        if (user1->username == rusername) {
            cout << "user already exists" << endl;
            return;
        }
    }
    user *tmp = new user();
    tmp->username = rusername;
    tmp->password = rpassword;
    user_list->users.push_back(tmp);
    cout << "register ok" << endl;
};
//Delete user method, only the root user is able to do this.
void delusr() {
    string dusername;
    cin >> dusername;
    error = true;
    for (int i = 0; i < user_list->users.size(); ++i) {
        if (user_list->users[i]->username == dusername) {
            error = false;
            if (dusername == "root" || curr_user->username != "root") {
                cout << "permission denied" << endl;
                return;
            } else {
                delete (user_list->users[i]);
                user_list->users.erase(user_list->users.begin() + i);
            }
        }
    }
    if (error) {
        cout << "user does not exist" << endl;
    }
};
//Display the user, also only permitted under the root account.
void disusr() {
    if (curr_user->username != "root") {
        cout << "permission denied" << endl;
        return;
    }
    for (auto user1 : user_list->users) {
        cout << user1->username << endl;
    }
};
//Login method, used to change users from different people.
void login() {
    string lusername, lpassword;
    cin >> lusername;
    error = true;
    for (auto user1 : user_list->users) {
        if (user1->username == lusername) {
            error = false;
        }
    }
    if (error) {
        cout << "user does not exist" << endl;
    } else {
        cout << "password:";
        cin >> lpassword;
        for (auto user1 : user_list->users) {
            if (user1->username == lusername) {
                if (user1->password == lpassword) {
                    cout << "login ok" << endl;
                    curr_user = user1;
                    return;
                } else {
                    cout << "password wrong" << endl;
                    return;
                }
            }
        }
    }
};
//Main function, first prepare the root user, then between every inputs, inplement prepare_stat() method.
int main() {
    prepare_user();
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
        else if (input1 == "search") {
            op_dir = root_dir;
            string sname;
            cin >> sname;
            search("/", sname);
            if (error) {
                cout << "file does not found" << endl;
            }
        } else if (input1 == "open")
            open(curr_path);
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
            chmod();
        else if (input1 == "chmodp")
            chmodp();
        else if (input1 == "close")
            close(curr_path);
        else if (input1 == "closep")
            closep();
        else if (input1 == "delete")
            deletei(curr_path);
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
        else
            continue;
    }
}
