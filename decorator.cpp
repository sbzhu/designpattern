#include<iostream>
using namespace std;

// the basic component
class Component {
	public:
		virtual void operation() = 0;
};

class ConcreteComponent : public Component {
	public:
		void operation(){
			cout << "Doing basic function" << endl;
		} 
};

// 
class Decorator : public Component {
	protected:
		Component * component;
		virtual void addedBehavior() = 0;
	public: 
		Decorator(Component * component) { this->component = component; }
		~Decorator() { 
			if(component) delete component, component = 0;
		}
		// overwrite the operation to add behavior
		void operation()
		{
			component->operation();
			addedBehavior();// Note here, decorate the operation
		}
};

class DecoratorA : public Decorator {
	protected:
		void addedBehavior()
		{
			cout << "Doing added behavior A" << endl;
		} 
	public:
		DecoratorA(Component * component) : Decorator(component){ }
};

class DecoratorB : public Decorator {
	protected:
		void addedBehavior()
		{
			cout << "Doing added behavior B" << endl;
		} 
	public:
		DecoratorB(Component * component) : Decorator(component){ }
};

class DecoratorDemo {
	public:
		static void run()
		{
			Component * component= new ConcreteComponent();
			component = new DecoratorA(component);
			component = new DecoratorB(component);
			component = new DecoratorA(component);
			component->operation();

			delete component, component= 0;
		}
};

int main(int argc, char * argv[])
{
	DecoratorDemo::run();
	return 0;
}
