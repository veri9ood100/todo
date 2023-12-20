#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

#include "todo_list.h"
#include "CSV.h"

#define COUT_WIDTH 22

using namespace std;

enum {
	INVALID,
	NEW,
	MODIFY,
	DELETE,
	SAVE,
	QUIT
};

enum {
	TOPIC,
	DEADLINE,
	PRIORITY,
	DONE
};

int converting_inst(string _inst) {
	transform(_inst.begin(), _inst.end(), _inst.begin(), tolower);
	if (_inst == "1" ||  _inst == "new" || _inst == "n") return NEW;
	else if (_inst == "2"|| _inst == "modify"|| _inst == "m") return MODIFY;
	else if (_inst == "3"|| _inst == "delete"|| _inst == "d") return DELETE;
	else if (_inst == "4"|| _inst == "quit"|| _inst == "q"|| _inst == "exit") return QUIT;
	else return INVALID;
}

int modifying(string _num) {
	transform(_num.begin(), _num.end(), _num.begin(), tolower);
	if (_num == "1" || _num == "topic" || _num == "t") return TOPIC;
	else if (_num == "2" || _num == "deadline" || _num == "dl") return DEADLINE;
	else if (_num == "3" || _num == "priority" || _num == "p") return PRIORITY;
	else if (_num == "4" || _num == "done" || _num == "d") return DONE;
	else return INVALID;
}

int main() {

	todo_list tl;
	todo_list& ptr_tl = tl;	
	
	string inst; int converted_inst = INVALID;
	std::cout << "Welcome to veri9ood100's Todo List!" << endl;
	int CSV_flag = CSV_reader(ptr_tl);
	cout << endl;

	while (converted_inst != QUIT) {

		if (CSV_flag == 1) tl.display(1);
		else CSV_flag = 1;

		std::cout << "Choose the number or name of instruction that you want to excute and enter it" << endl;
		std::cout.width(COUT_WIDTH); std::cout << right << "1. New(n)";
		std::cout.width(COUT_WIDTH); std::cout << right << "2. Modify(m)";
		std::cout.width(COUT_WIDTH); std::cout << right << "3. Delete(d)";
		std::cout.width(COUT_WIDTH); std::cout << right << "4. Save(s)";
		std::cout.width(COUT_WIDTH); std::cout << right << "5. Quit(q)";
		std::cout << endl;
		std::cout << "Your input: ";
		
		std::getline(cin, inst);
		converted_inst=converting_inst(inst);

		string s_mod;  
		int i_mod = INVALID; 
		string modified_data="";
		int idx;

		switch (converted_inst) {
		case NEW:
			tl.new_todo();
			//tl.display(1);
			break; //break NEW
		
		case MODIFY:
			std::cout << "What do you want to modify? Enter the index" << endl;
			std::cout << "Your input: ";
			cin >> idx; cin.ignore();
			idx--;

			try {
				if (!std::is_integral<decltype(idx)>::value) {
					throw invalid_argument("Index mush be integer!");
				}

				if (idx < 0 || idx >= tl.get_list_size()) {
					throw invalid_argument("Wrong index range!");
				}
			}

			catch (invalid_argument &e) {
				std::cout << e.what() << endl;
				break; // break MODIFY with exception
			}

			std::cout << "Choose what you want to modify" << endl;
			std::cout.width(COUT_WIDTH); std::cout << right << "1. Topic(t)";
			std::cout.width(COUT_WIDTH); std::cout << right << "2. Deadline(dl)";
			std::cout.width(COUT_WIDTH); std::cout << right << "3. Priority(p)";
			std::cout.width(COUT_WIDTH); std::cout << right << "4. Done(d)" << endl;
			//std::cout << setfill('-') << setw(COUT_WIDTH * 5) << "\n";
			std::cout << "Your input: ";
			std::getline(cin, s_mod);
			i_mod = modifying(s_mod);			

			switch (i_mod) {
			case TOPIC:
				std::cout << "Current topic: " << tl.get_format(idx).get_topic() << endl;
				std::cout << "Enter the modified topic: ";

				std::getline(cin, modified_data);
				if (!modified_data.empty()) {
					tl.get_format(idx).set_topic(modified_data);
				}
				else std::cout << "Topic should not be empty!" << endl;
				
				//tl.display(1);
				break;// BREAK TOPIC

			case DEADLINE:
				std::cout << "Current deadline: " << tl.get_format(idx).get_deadline() << endl;
				std::cout << "Enter the modified deadline: ";

				std::getline(cin, modified_data);
				if (tl.is_valid_date(modified_data)) {
					tl.get_format(idx).set_deadline(modified_data);
				}
				else std::cout << "Wrong deadline date format. Date format must be like 2024-12-31!" << endl;
				//tl.display(1);
				break; //break DEADLINE


			case PRIORITY:
				std::cout << "Current priority: " << tl.get_format(idx).get_priority() << endl;
				std::cout << "Enter the modified priority: ";
				int modified_p;
				cin >> modified_p; cin.ignore();

				tl.get_format(idx).set_priority(modified_p);

				//tl.display(1);
				break; // break PRIORITY

			case DONE:
				std::cout << "Current done flag: " << tl.get_format(idx).get_done() << endl;
				std::cout << "Enter the modified done flag: ";
				std::getline(cin, modified_data);

				if (modified_data == "y" || modified_data == "yes"
					|| modified_data == "d" || modified_data == "done"
					|| modified_data == "O"	|| modified_data == "o") {
					tl.get_format(idx).set_done("O");
				}
				else if (modified_data == "n" || modified_data == "no" 
					|| modified_data == "yet" 
					|| modified_data == "X" || modified_data == "x") {
					tl.get_format(idx).set_done("X");
				}
				//tl.display(1);
				break; //break DONE


			default:
				std::cout << "Invalid input. Please try agin!" << endl;
				break; //break MODIFY default
			tl.display(1);
			}//end of MODIFY switch

		case DELETE:
			//int idx;
			std::cout << "What do you want to Delete? Enter the index" << endl;
			std::cout << "Your input: ";
			cin >> idx; cin.ignore();
			tl.delete_todo(idx);
			//tl.display(1);
			break;

		case SAVE:
			CSV_writer(ptr_tl);
			break;

		case QUIT:
			break;

		default:
			cout << "Invalid value entered! Pleas try again" << endl;

		}
		
	}//end of while

	std::cout << "Closing veri9ood100's todo List" <<endl;
	//
	CSV_writer(ptr_tl);
	//
	std::cout <<"Thank you for using it and have a good day!" << endl;

	return 0;
}