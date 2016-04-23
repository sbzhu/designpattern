#include <iostream>
#include <list>
#include <typeinfo>
#include <string>
#include <ctime>
using namespace std;
class Demo {
	public:
		static void run()
		{

		}
};

int main(int argc, char * argv[])
{
	time_t now = time(0);
	cout << now << endl;
	return 0;
}
