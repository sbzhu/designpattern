#include <iostream>
#include <list>
#include <typeinfo>
#include <string>
#include <ctime>
using namespace std;

class Notifier;

class Observer {
	public:
		virtual void update(Notifier *)
		{
			// you can get information from notifier using getState()
			// then do something 
		}
}; 

class Notifier {
	private:
		list<Observer *> observerList;

	public:
		void attach(Observer * observer)
		{
			observerList.push_back(observer);
		}
		void detach(Observer * observer)
		{
			list<Observer *>::iterator iter = observerList.begin();
			while(observerList.end() != iter && *iter != observer) iter++;
			if(observerList.end() != iter) observerList.erase(iter);
		}
		void notify()
		{ 
			list<Observer *>::iterator iter = observerList.begin();
			for( ; observerList.end() != iter; iter++)
			{
				(*iter)->update(this);// give this to pass information
			}
		}

	   	// for Observer use. give the required information
		virtual const string & getState() = 0;
}; 

// below is usecase

class Camera : public Notifier {
	public:
		struct INFO{ 
			time_t time;
			string event;
		} information;

	public:
		void supervision(string event)
		{
			information.event = event;
			cout << "<Event> ";
			cout << event << endl;
			notify();
		}

		const string & getState()
		{
			return information.event;
		}
};

class Staff : public Observer {
	private:
		string name;
	public:
		Staff(const string & _name) : name(_name){ }
		void update(Notifier * notifier)
		{
			cout << "[Action] ";
			if(string::npos != notifier->getState().find("boss is coming"))
			{
				cout << name << " begin to work" << endl;
			}
			else cout << name << " go on sleeping" << endl;
		}
};

class ObserverDemo {
	public:
		static void run()
		{
			Camera * camera = new Camera();
			Staff * staffA = new Staff("AbelZhu");
			Staff * staffB = new Staff("DuQinqin");
			Staff * staffC = new Staff("DongYujun"); 

			camera->attach(staffA);
			camera->attach(staffB);
			camera->attach(staffC);

			camera->supervision("Oh my God, boss is coming !!!!");

			camera->detach(staffB);
			camera->supervision("A tiger outside the door !!!!");
		}
};

int main(int argc, char * argv[])
{
	ObserverDemo::run();
	return 0;
}
