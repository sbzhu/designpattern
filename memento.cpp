#include <iostream>
#include <list>
#include <typeinfo>
#include <string>
using namespace std;

class Memento {
	private:
		string state;
	public:
		Memento(const string & state){ this->state = state; }

		const string & loadState(){ return state; }
};

class Originator {
	private:
		string state;
	public:
		const string & loadState(){ return state; }
		void setState(const string & state){ this->state = state; } 
		Memento * writeMemento()
		{
			return new Memento(state);
		}
		void readMemento(Memento * memento)
		{
			if(!memento)
			{
				cout << "Wrong index or no memento" << endl;
				return;
			}
			setState(memento->loadState());
		}
};

class Caretaker {
	private:
		list<Memento *> mementoList;
		const int MAX_MEM;
	public:
		Caretaker() : MAX_MEM(10) { }
		void save(Memento * memento)
		{
			if(MAX_MEM == mementoList.size())
			{
				mementoList.erase(mementoList.begin());// remove the oldest memento
			}
			mementoList.push_back(memento);
		}
		Memento * load(int index)
		{ 
			if(index <= 0 || index > mementoList.size()) return 0;

			list<Memento *>::iterator iter = mementoList.end();
			while(0 < index--) iter--;

			return *iter;
		}
}; 

class MementoDemo {
	public:
		static void run()
		{
			Originator * originator = new Originator();
			Caretaker * caretaker = new Caretaker();

			originator->setState("#1");
			originator->setState("#2");
			caretaker->save(originator->writeMemento());
			originator->setState("#3");
			caretaker->save(originator->writeMemento());
			originator->setState("#4");
			caretaker->save(originator->writeMemento());
			originator->setState("#5");
			
			cout << "Current state : " << originator->loadState() << endl;
			originator->readMemento(caretaker->load(1));
			cout << "Current state : " << originator->loadState() << endl;
			originator->readMemento(caretaker->load(2)); 
			cout << "Current state : " << originator->loadState() << endl;
			originator->readMemento(caretaker->load(5)); 
			cout << "Current state : " << originator->loadState() << endl;
		}
};

int main(int argc, char * argv[])
{
	MementoDemo::run();
	return 0;
}
