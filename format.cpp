#include <iostream>
#include <regex>
#include <algorithm>

#include "format.h"

using namespace std;

format::format() {
	this->priority = 0;
	this->deadline = "";
	this->topic = "";
	this->done = "X";
}

format::format(int _priority, string _deadline, string _topic, string _done) {
	//initializing
	this->priority = 0;
	this->deadline = "";
	this->topic = "";
	this->done = "X";
	format::set_priority(_priority);
	format::set_deadline(_deadline);
	format::set_topic(_topic);
	format::set_done(_done);
}

format::format(int _priority, string _deadline, string _topic) {
	//initializing
	this->priority = 0;
	this->deadline = "";
	this->topic = "";
	this->done = "X";
	format::set_priority(_priority);
	format::set_deadline(_deadline);
	format::set_topic(_topic);
	//format::set_done(_done);
}

format::~format() {
	this->priority = NULL;
	this->deadline = "";
	this->topic = "";
	this->done = "X";
}

void format::set_priority(int _p) {
	this->priority = _p;
}

int format::get_priority() {
	return this->priority;
}

void format::set_deadline(string _d) {
	this->deadline = _d;
}

string format::get_deadline() {
	return this->deadline;
}

void format::set_topic(string _t) {
	this->topic = _t;
}

string format::get_topic() {
	return this->topic;
}

void format::set_done(string _d) {	
	this->done = _d;
}

string format::get_done() {
	return this->done;
}

int format::make_value() {
	string _deadline = this->get_deadline();
	_deadline.erase(find(_deadline.begin(), _deadline.end(), '-'));
	string _priority = to_string(this->get_priority());

	try {
		int value = stoi(_deadline + _priority);
		return value;
	}

	catch (invalid_argument& e) {
		cout << e.what() << endl;
		return -1;
	}
}