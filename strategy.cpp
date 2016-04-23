#include <iostream>
#include <list>
#include <typeinfo>
#include <string>
#include <ctime>
using namespace std;

class Strategy {
	public:
		virtual void goBackHome() = 0;
		virtual void goToSchool() = 0;
};

class Walk : public Strategy {
	public:
		virtual void goBackHome()
		{
			cout << "Walk to home" << endl;
		}
		virtual void goToSchool()
		{
			cout << "Walk to school" << endl;
		}
};

class Ride : public Strategy {
	public:
		virtual void goBackHome()
		{
			cout << "Ride to home" << endl;
		}
		virtual void goToSchool()
		{
			cout << "Ride to school" << endl;
		}
};

class Person {
	private:
		Strategy * moveStrategy;
	public:
		void spendTime()
		{
			if(!moveStrategy)
			{
				cout << "Please set move strategy !" << endl;
				return;
			}
			moveStrategy->goToSchool();	
			moveStrategy->goBackHome();	
		}
		void setMoveStrategy(Strategy * stratege)
		{
			if(moveStrategy) delete moveStrategy, moveStrategy= 0;

			moveStrategy = stratege;
		}
};

class StrategyDemo {
	public:
		static void run()
		{
			Person * person = new Person();

			person->setMoveStrategy(new Walk());// client to chose strategy
			person->spendTime();

			person->setMoveStrategy(new Ride());
			person->spendTime(); 
		}
};

int main(int argc, char * argv[])
{
	StrategyDemo::run();
	return 0;
}
