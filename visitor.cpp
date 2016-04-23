#include <iostream>
#include <list>
#include <typeinfo>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;

class Element;

class Visitor {
	public:
		virtual void visit(Element *) = 0;
};

class Element {
	public:
		virtual void accept(Visitor * visitor)
		{
			visitor->visit(this);
		}
};

class EmployInfo : public Element {
	public:
		const string name;
		string phone;
		double salary;
	public:
		EmployInfo(const string & name, const string & phone, double salary)
			: name(name), phone(phone), salary(salary)
		{

		}
};

class DataBase {
	public:
		list<EmployInfo *> employList;

	public:
		void attach(EmployInfo * employ)
		{
			employList.push_back(employ);
		}
		void accept(Visitor * visitor)
		{
			list<EmployInfo *>::iterator iter;
			for(iter = employList.begin(); employList.end() != iter; iter++)
			{
				visitor->visit(*iter);
			} 
		}
};

class FinancialStaff : public Visitor {
	public:
		virtual void visit(Element * element)
		{
			EmployInfo * employ = (EmployInfo *)element;
			cout << employ->name << " : salary " << employ->salary << endl;
		}
};

class HRStaff : public Visitor {
	public:
		virtual void visit(Element * element)
		{
			EmployInfo * employ = (EmployInfo *)element;
			cout << employ->name << " : phone " << employ->phone << endl;
		}
};

class VisitorDemo {
	public:
		static void run()
		{
			Visitor * HR = new HRStaff();
			Visitor * FS = new FinancialStaff();

			EmployInfo * john = new EmployInfo("John", "1827739301", 9000);
			john->accept(HR);

			DataBase * dataBase = new DataBase();
			dataBase->attach(john);
			dataBase->attach(new EmployInfo("AbelZhu", "15156684393", 18000));
			dataBase->attach(new EmployInfo("DingZhang", "18156684383", 28000));
			dataBase->attach(new EmployInfo("Mike", "19456684283", 11000));

			dataBase->accept(FS);
			dataBase->accept(HR);
		}
};

int main(int argc, char * argv[])
{
	VisitorDemo::run();
	return 0;
}
