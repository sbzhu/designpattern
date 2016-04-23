#include <iostream>
using namespace std;

class Beverage {
	public:
		void boilWater()
		{
			cout << "Heat water to boil" << endl;
		}
		virtual void addMeterial() = 0;// this is the template method
		void makeBeverage()
		{
			boilWater();
			addMeterial();
		}
};

class Tea : public Beverage {
	public:
		void addMeterial()
		{
			cout << "Add tea to boiled water" << endl;
		}
};

class Coffee : public Beverage {
	public:
		void addMeterial()
		{
			cout << "Add coffee to boiled water" << endl;
		}
};

class TemplateMethodMode {
	public:
		static void run()
		{
			Beverage * beverage = new Tea();
			beverage->makeBeverage();

			if(beverage) delete beverage, beverage = 0;
		}
};

int main(int argc, char * argv[])
{
	TemplateMethodMode::run();

	return 0;
}
