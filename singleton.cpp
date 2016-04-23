#include <iostream>

using namespace std;

class Singleton {
	private:
		static Singleton * instance;

		Singleton(){
			cout << "Constructing.." << endl;
		}

	public:
		static Singleton * getInstance()
		{
			if(0 == instance) { 
				instance = new Singleton();    
			}
			else {
				cout << "Already have instance" << endl;
			}

			return instance; 
		} 
		static void destroyInstance()
		{
			if(instance){
				delete instance;
				instance = 0;
			}
			cout << "Destroying.." << endl;
		}
};

Singleton * Singleton::instance = 0;

class SingletonDemo{
	public:
		static void run(){
			Singleton *a = Singleton::getInstance();
			Singleton *b = Singleton::getInstance(); 
			Singleton::destroyInstance();
			Singleton *c = Singleton::getInstance(); 
		}
};

int main(int argc, char * argv[])
{
	SingletonDemo::run();
	return 0;
}
