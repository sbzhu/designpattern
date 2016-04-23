#include <iostream>
#include <string>

using namespace std;


class Drawer {
	public:
		virtual void draw() = 0;
};
class Sketcher : public Drawer {
	void draw() { cout << "Sketching.." << endl; }
};
class Painter: public Drawer {
	void draw() { cout << "Painting.." << endl; }
};

// shape interface
class Shape {
	public:
		Drawer * drawer;
	public:
		virtual void show() = 0;
};

// Shape implement
class Circle : public Shape {
	public:
		void show() { 
			cout << "I'm a Circle !" << endl; 
			drawer->draw();
		}

		Circle(Drawer * drawer){ this->drawer = drawer; }
};

class Square : public Shape {
	public:
		void show() { 
			cout << "I'm a Square!" << endl; 
			drawer->draw();
		}

		Square(Drawer * drawer){ this->drawer = drawer; }
}; 

class BridgeDemo {
	public:
		static void run()
		{
			Drawer * drawer = 0;
			Shape * shape = 0;

			// I want to sketch a square 
			drawer = new Sketcher();
			shape = new Square(drawer);
			shape->show();
			delete drawer, drawer = 0;
			delete shape, shape = 0; 
		}
};

int main(int argc, char * argv[])
{
	BridgeDemo::run();
	return 0;
}
