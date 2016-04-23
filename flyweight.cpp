#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>

using namespace std;

class Flyweight {
	protected:
		int state;
	public:
		virtual void operation() = 0;
		Flyweight(int state)
		{
			this->state = state;
		}
};

class ConcreteFlyweight : public Flyweight {
	public:
		ConcreteFlyweight(int state) : Flyweight(state){ }
		virtual void operation()
		{
			cout << "I'm shared component : " << state << " Address : " << (void *)this << endl; 
		}
};

class UnsharedConcreteFlyweight : public Flyweight {
	public:
		UnsharedConcreteFlyweight(int state) : Flyweight(state){ }
		virtual void operation()
		{
			cout << "I'm unshared component : " << state << endl; 
		}
};

class FlyweightFactory {
	protected:
		map<int, Flyweight *> pool;
	public:
		FlyweightFactory()
		{
			// init pool
			for(int i = 0; i < 10; i++)
			{
				pool[i] = new ConcreteFlyweight(i);
			}
		}
	
		Flyweight * getFlyweight(const int choice)
		{
			return pool[choice];
		}
};

class FlyweightDemo {
	public:
		static void run()
		{
			FlyweightFactory * flyweightFactory = new FlyweightFactory();

			Flyweight * flyweightA = flyweightFactory->getFlyweight(3); 
			flyweightA->operation();
			Flyweight * flyweightB = flyweightFactory->getFlyweight(3); 
			flyweightB->operation();

			if(flyweightA) delete flyweightA, flyweightA = 0; // noete flyweightA acturally is flyweightB
			if(flyweightB) delete flyweightA, flyweightA = 0; 
			if(flyweightFactory) delete flyweightFactory, flyweightFactory = 0;
		}
};

int main(int argc, char * argv[])
{
	FlyweightDemo::run();
	return 0;
}
