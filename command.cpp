#include <list>
#include <iostream>

using namespace std;

class Cooker {
	public:
		void makeMilk() { cout << "Making milk" << endl; }
		void makeChiken() { cout << "Making Chiken" << endl; }
};

class Order {
	protected:
		Cooker * cooker;
	public:
		Order(Cooker * cooker) { this->cooker = cooker; }
		virtual void execute() = 0;
};

class ChickenOrder : public Order {
	public:
		ChickenOrder(Cooker * cooker) : Order(cooker){ }
		void execute() { cooker->makeChiken(); } 
};
class MilkOrder : public Order {
	public:
		MilkOrder(Cooker * cooker) : Order(cooker){ }
		void execute() { cooker->makeMilk(); }
};

class Waiter {
	public:
		list<Order*> oderList;
	public:
		void addOder(Order * order) { oderList.push_back(order); }
		void notify()
		{
			for(list<Order*>::iterator iter = oderList.begin(); oderList.end() != iter; iter++)
			{
				(*iter)->execute(); 
			}
		} 
};

class CommandDemo {
	public:
		static void run()
		{
			Cooker * cooker = new Cooker();
			Waiter * waiter = new Waiter();
			waiter->addOder(new ChickenOrder(cooker));
			waiter->addOder(new MilkOrder(cooker));
			waiter->notify();
		}
};

int main(int argc, char * argv[])
{
	CommandDemo::run();
	return 0;
} 
