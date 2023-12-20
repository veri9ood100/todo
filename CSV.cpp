#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "todo_List.h"

#define ITEM 3

using namespace std;

enum {
    TOPIC,
    DEADLINE,
    PRIORITY,
    DONE
};

int CSV_reader(todo_list& _tl) {
    
    fstream fs;
    string str_buf;
    vector <string> v_tmp;

    string filename = "Todo.csv";
    cout << "Trying to read " << filename << ".....";
    fs.open(filename, ios::in);
    
    if (fs.fail()) {
        cout << "Fail!" << endl;
        return -1;
    }

    else cout << "Success!" << endl;

    while(!fs.eof()){
        int cnt = 0;
        getline(fs, str_buf);
        if (str_buf.empty()) {
            cout << filename<<" is empty!" << endl;
            return -1;
        }
        while (!str_buf.empty()) {
            int idx = str_buf.find(',');
            if (idx >= 0) {
                v_tmp.push_back(str_buf.substr(0, idx));
                str_buf.erase(0, idx + 1);
                cnt++;
            }
            else {
                break;
            }
        }

        v_tmp.push_back(str_buf);

        if (cnt != ITEM) {
            cout << "Wrong format!" << endl;
            cout << "Current Items: " << cnt<<endl;
            return -1;
        }

        else {
            try {
                int _p = stoi(v_tmp[2]);
                _tl.new_todo(v_tmp[0], v_tmp[1], _p, v_tmp[3]);//deadline, topic, priority, done
                while (!v_tmp.empty()) {
                    v_tmp.pop_back();
                    }
               }
            catch (invalid_argument& e) {
                cout << e.what() << endl;
                return -1;
            }                 
        }
    }

    fs.close();

    return 1;

}

int CSV_writer(todo_list& _tl) {
    ofstream fs;
    string str_buf;

    string filename("Todo.csv");

    cout << "Trying to open " << filename << ".....";
    fs.open(filename);
    if (fs.fail()) {
        cout << "Fail!" << endl;
        return -1;
    }
    else cout << "Success!" << endl;

    cout << "Saving Current Toto list.....";
    for (int i = 0; i < _tl.get_list_size(); i++) {
        fs << _tl.get_format(i).get_deadline()\
            << "," << _tl.get_format(i).get_topic()\
            << "," << _tl.get_format(i).get_priority()\
            << "," << _tl.get_format(i).get_done();
        if (i + 1 != _tl.get_list_size()) fs << "\n";
    }
    cout << "Success!" << endl;

    cout << "Closing " << filename << "....";
    fs.close();
    if (fs.fail()) { 
        cout << "Fail!" << endl; 
        return -1; 
    }
    else {
        cout << "Success!" << endl;
        return 1;
    }
}