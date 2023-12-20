#include <iostream>
#include <string>
#include <regex>
#include <iomanip>

#include "todo_list.h"

#define COUT_WIDTH 20

using namespace std;

//display flag
enum {
	ALL=1,
	NOT_DONE
};

int todo_list::binary_search(int _value, int _begin, int _dest) {

	//cout << "Binary Searching" << endl;

	if (_begin == _dest) {
		return _begin;
	}

	else {
		int mid = (_begin + _dest + 1) / 2;
		if (this->get_format(mid).make_value() < _value) {
			return this->binary_search(_value, mid, _dest);
		}
		else {
			return this->binary_search(_value, _begin, mid-1);
		}
		
	}
}

todo_list::~todo_list() {
	while (!vector_todo_list.empty()) {
		vector_todo_list.erase(vector_todo_list.begin());
	}
}

bool todo_list::is_valid_date(string _date) {
	regex pattern("^([0-9]{4})-([0-9]{1,2})-([0-9]{1,2})$");
	return regex_match(_date, pattern);
}

void todo_list::new_todo() {
	format* new_f = new format();
	int _priority;
	string _deadline;
	string _topic;

	//set topic
	cout << "type topic: ";
	getline(cin, _topic);
	if (!_topic.empty()) new_f->set_topic(_topic);
	else {
		cout << "Topic should not be empty!" << endl;
		delete new_f;
		return;
	}
	
	//set deadline
	cout << "type deadline: ";
	getline(cin, _deadline);
	if (is_valid_date(_deadline)) new_f->set_deadline(_deadline);
	else {
		cout << "Wrong deadline date format. Date format must be like 2024-12-31!" << endl;
		delete new_f;
		return;
	}

	//set priority
	cout << "Enter priority from 1 to 5. Lower priority #, more urgent: ";
	cin >> _priority; cin.ignore();
	//int exception
	try {
		if (!std::is_integral<decltype(_priority)>::value) {
			throw invalid_argument("Priority's datatype mush be integer!");
		}

		else if (_priority <= 0 || _priority > 5) {
			throw invalid_argument("Wrong priority value!");
		}

		new_f->set_priority(_priority);
	}

	catch (invalid_argument& e) {
		cout << e.what() << endl;
		delete new_f;
		return;
	}

	this->sorting(*new_f);
	//vector_todo_list.push_back(*new_f);
	//cin.ignore();
	cout << endl;
}

void todo_list::new_todo(string _deadline, string _topic, int _priority, string _done) {
	format* new_f = new format();
	//int _priority;	string _deadline;	string _topic;

	//set topic
	if (!_topic.empty()) new_f->set_topic(_topic);
	else {
		cout << "Topic should not be empty!" << endl;
		delete new_f;
		return;
	}
	//cout << "Reading topic success!" << endl;

	//set deadline
	if (is_valid_date(_deadline)) new_f->set_deadline(_deadline);
	else {
		cout << "Wrong deadline date format. Date format must be like 2024-12-31!" << endl;
		delete new_f;
		return;
	}
	//cout << "Reading deadlne success!" << endl;

	//set priority
	try {//int exception
		if (!std::is_integral<decltype(_priority)>::value) {
			throw invalid_argument("Priority's datatype mush be integer!");
		}

		else if (_priority <= 0 || _priority > 5) {
			throw invalid_argument("Wrong priority value!");
		}

		new_f->set_priority(_priority);
	}

	catch (invalid_argument& e) {
		cout << e.what() << endl;
		delete new_f;
		return;
	}
	//cout << "Reading priority success!" << endl;

	//set done
	try {
		if (_done == "O" || _done == "X") new_f->set_done(_done);
		else throw invalid_argument("Wrong done flag!");
	}

	catch (invalid_argument& e) {
		cout << e.what() << endl;
		delete new_f;
		return;
	}
	//cout << "Reading done flag success!" << endl;

	this->sorting(*new_f);
	//vector_todo_list.push_back(*new_f);
	//cin.ignore();
	cout << endl;
}

void todo_list::delete_todo(int _idx) {

	if(_idx <= vector_todo_list.size() && _idx >= 0) {
		cout << "deleting index:" << _idx << " topic: " << vector_todo_list[_idx].get_topic() << "\n";
		vector_todo_list.erase(vector_todo_list.begin() + _idx);
		cout << "deleting success!\n";
	}

	else {
		cout << "Index range is wrong! \n";
	}
}

void todo_list::display(int _option) {

	cout.width(COUT_WIDTH);	cout << right << "Order";
	cout.width(COUT_WIDTH);	cout << right << "Deadline";
	cout.width(COUT_WIDTH);	cout << right << "Topic";
	cout.width(COUT_WIDTH);	cout << right << "Priority";
	cout.width(COUT_WIDTH);	cout << right << "Done";
	cout << endl;
	cout << endl;

	switch (_option) {
		
	//display all
	case ALL :		
		for (int i = 0; i < this->get_list_size(); i++) {
			cout.width(COUT_WIDTH);	cout << right << i+1;
			cout.width(COUT_WIDTH);	cout << right << this->get_format(i).get_deadline();
			cout.width(COUT_WIDTH);	cout << right << this->get_format(i).get_topic();
			cout.width(COUT_WIDTH);	cout << right << this->get_format(i).get_priority();
			cout.width(COUT_WIDTH);	cout << right << this->get_format(i).get_done();
			cout << endl;
		} break;
	
	case NOT_DONE:
		for (int i = 0; i < this->get_list_size(); i++) {
			if (this->get_format(i).get_done() == "O") continue;
			else {
				cout.width(COUT_WIDTH);	cout << right << i + 1;
				cout.width(COUT_WIDTH);	cout << right << this->get_format(i).get_deadline();
				cout.width(COUT_WIDTH);	cout << right << this->get_format(i).get_topic();
				cout.width(COUT_WIDTH);	cout << right << this->get_format(i).get_priority();
				cout.width(COUT_WIDTH);	cout << right << this->get_format(i).get_done();
				cout << endl;
			}
		} break;

	//Invalid option
	default:
		
		cout << "Something Wrong occured!" << endl;
	}

	cout << endl;
}

void todo_list::sorting(format& _f) {

	//cout << "Sorting" << endl;

	if (this->get_list_size() > 1) {
		int idx = this->binary_search(_f.make_value(), 0, this->get_list_size()-1);
		vector_todo_list.insert(vector_todo_list.begin() + idx, _f);
	}

	else if (this->get_list_size() == 1) {
		if(vector_todo_list[0].make_value() < _f.make_value()) vector_todo_list.push_back(_f);
		else vector_todo_list.insert(vector_todo_list.begin(), _f);
		
	}

	else vector_todo_list.push_back(_f);

	//this->display(1);
}

int todo_list::get_list_size() {
	return vector_todo_list.size();
}

format& todo_list::get_format(int _idx) {
	return vector_todo_list[_idx];
}