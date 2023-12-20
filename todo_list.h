#pragma once

#include <vector>

#include "format.h"

class todo_list {
	
	int binary_search(int value, int begin, int dest);

	public:
		//todo_list();
		~todo_list();

		//for valid date format
		bool is_valid_date(string _date);

		void new_todo();
		void new_todo(string _deadline, string _topic, int _priority, string _done);

		void sorting(format& _f);

		void delete_todo(int _idx);		

		void display(int _option);		

		int get_list_size();
		format& get_format(int _idx);

	private:
		vector <format> vector_todo_list;
};