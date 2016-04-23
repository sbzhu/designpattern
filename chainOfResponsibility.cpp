#include <iostream>
using namespace std;

class ExceptionHaddle {
	protected:
		ExceptionHaddle * successor;
	public:
		ExceptionHaddle(){ successor = 0; }
		virtual void handle(int errCode) = 0;
		void setSuccessor(ExceptionHaddle * successor) { this->successor = successor; }
};

class WarningHaddle : public ExceptionHaddle {
	public:
		void handle(int errCode)
		{
			if(errCode < 5) cout << "Warning" << endl;
			else successor->handle(errCode);// pass to successor
		}
};

class AlarmHaddle : public ExceptionHaddle {
	public:
		void handle(int errCode)
		{
			if(errCode < 10) cout << "Alarm" << endl;
			else successor->handle(errCode);// pass to successor
		}
};

class FailHaddle : public ExceptionHaddle {
	public:
		void handle(int errCode)
		{
			cout << "System failed" << endl;//this is the end of the chain, no successor
		}
};

class ChainOfResponsibilityDemo {
	public:
		static void run()
		{
			ExceptionHaddle * warningHaddle = new WarningHaddle();
			ExceptionHaddle * alarmHaddle = new AlarmHaddle();
			ExceptionHaddle * failHaddle = new FailHaddle();

			// set chain
			warningHaddle->setSuccessor(alarmHaddle);
			alarmHaddle->setSuccessor(failHaddle);

			warningHaddle->handle(3);
			warningHaddle->handle(7);
			warningHaddle->handle(10); 

			if(warningHaddle) delete warningHaddle, warningHaddle = 0;
			if(alarmHaddle) delete alarmHaddle, alarmHaddle = 0;
			if(failHaddle) delete failHaddle, failHaddle = 0;
		}
};

int main(int argc, char * argv[])
{
	ChainOfResponsibilityDemo::run();
	return 0;
}
