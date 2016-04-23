#include <iostream>
#include <string>

using namespace std;

// shape interface
class Shape {
	public:
		virtual void draw() = 0;
};

// Shape impletement
class Circle : public Shape {
	public:
		void draw() { cout << "I'm a Circle !" << endl; }
};

class Square : public Shape {
	public:
		void draw() { cout << "I'm a Square !" << endl; }
};


// Factory
class ShapeFactory {
	public:
		Shape * getShape(const string & shapeType)
		{
			if("Circle" == shapeType) return new Circle();
			else if("Square" == shapeType) return new Square();

			else return 0;
		}
};

// demo
class FactoryPatternDemo {
	public:
		static void run()	
		{
			ShapeFactory * shapeFactory = new ShapeFactory();

			Shape * shape = 0;

			shape = shapeFactory->getShape("Circle");
			shape->draw();
			delete shape, shape = 0;

			shape = shapeFactory->getShape("Square");
			shape->draw();
			delete shape, shape = 0;

			delete shapeFactory, shapeFactory = 0; 
		}
};

int main(int argc, char * argv[])
{
	FactoryPatternDemo::run();
	return 0;
}
