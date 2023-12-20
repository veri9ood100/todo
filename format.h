#ifndef FORMAT_H
#define FORMAT_H

#include <string>

using namespace std;

class format {

	public:
		//default constructor
		format();

		//constructor with variable
		format(int _priority, string _deadline, string _topic, string _done);
		format(int _priority, string _deadline, string _topic);

		//destructor
		~format();

		//priority set and get func
		void  set_priority(int _p);
		int get_priority();
		
		//deadline set and get func
		void set_deadline(string _d);
		string get_deadline();

		//topic set and get func
		void set_topic(string _t);
		string get_topic();

		//done set and get func
		void set_done(string _d);
		string get_done();

		int make_value();

	private:
		int priority;
		string deadline;
		string topic;
		string done;
};

#endif