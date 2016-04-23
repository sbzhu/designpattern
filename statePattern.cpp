#include <iostream>
#include <list>
#include <typeinfo>
#include <string>
#include <ctime>
using namespace std;

/*
 * 注意状态模式与策略模式的区别
 * 状态模式本质上是策略模式，但是多了个状态转移控制
 * 1. 策略模式的状态选择由client选择；状态模式的状态是状态内部自我切换
 * 2. 策略模式的各个策略没有关系，只有简单的替换；状态模式各个状态间转移有固定的模式，需要由状态自己定义
 */

class Context;

class State {
	public:
		virtual void handle(Context *) = 0;
};

class Context {
	protected:
		State * state;

	protected:
		void setState(State * state)// 这个函数是protected的，不允许client调用
		{
			if(this->state) delete this->state, this->state = 0;
			this->state = state;
		}
	public:
		virtual void request()
		{
			// let state to do the handle 
			if(state) state->handle(this);
		}
};

/*
 * 人有 lazy / work 两种状态，两种状态由人的精力值 power 决定
 * 不同状态下  power 值会有不同变化，进而造成人在两种状态间切换
 */
class Person : public Context {
	protected:
		const string name; 
	public:
		int power; 
	protected:
		void checkState();
	public:
		Person(string _name);
		void spendTime();
};
class WorkMode : public State {
	public:
		void handle(Context * context)
		{ 
			cout << "[work mode | power " << ((Person *)context)->power 
				<< "] Study ! Work ! go ! go ! go !" << endl;

			((Person *)context)->power -= 3;// hardworking use power
		}
};
class LazyMode : public State {
	public:
		void handle(Context * context)
		{
			cout << "[lazy mode | power " << ((Person *)context)->power 
				<< "] Sleep~sleep~sleep~ing~ing~~zZ" << endl;

			((Person *)context)->power += 2;// resting rise power
		}
};

void Person::checkState()
{
	if(power > 5) setState(new WorkMode());
	else setState(new LazyMode()); 
}
Person::Person(string _name) : name(_name){
	power = 5;
	checkState();
}
void Person::spendTime()
{
	request();
	checkState();
}

class StatePatternDemo {
	public:
		static void run()
		{
			Person * person = new Person("aQ");
			person->spendTime();
			person->spendTime();
			person->spendTime();
			person->spendTime();
			person->spendTime();
			person->spendTime();
			person->spendTime();
		}
};

int main(int argc, char * argv[])
{
	StatePatternDemo::run();
	return 0;
}
