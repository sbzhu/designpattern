#include <iostream>
#include <string>

using namespace std;

// shape interface
class Shape {
	public:
		virtual void draw() = 0;
};

// Shape implement
class Circle : public Shape {
	public:
		void draw() { cout << "I'm a Circle !" << endl; }
};

class Square : public Shape {
	public:
		void draw() { cout << "I'm a Square !" << endl; }
}; 

// Color interface
class Color {
	public:
		virtual void fill() = 0;
};

// color implement
class Red : public Color {
	public:
		void fill(){ cout << "My color is red !" << endl; }
}; 
class Blue: public Color {
	public:
		void fill(){ cout << "My color is blue !" << endl; }
};

// Factory
class AbstractFactory {
	public:
		virtual Shape * getShape() = 0;
		virtual Color * getColor() = 0; 
};
class AppleFactory : public AbstractFactory {
	public:
		Shape * getShape(){ return new Circle(); }	
		Color * getColor(){ return new Red(); }	
};
class TableFactory : public AbstractFactory {
	public:
		Shape * getShape(){ return new Square(); }	
		Color * getColor(){ return new Blue(); }	
};


// demo
class AbstractFactoryDemo { 
	public:
		static void run()	
		{
			AbstractFactory * abstractFactory = 0;
			Shape * shape = 0;
			Color * color = 0; 
			
			// product apple 
			abstractFactory = new AppleFactory();
			shape = abstractFactory->getShape(), shape->draw();
			color = abstractFactory->getColor(), color->fill();
			delete shape, shape = 0;
			delete color, color = 0;
			delete abstractFactory, abstractFactory = 0;

			// product table
			abstractFactory = new TableFactory();
			shape = abstractFactory->getShape(), shape->draw();
			color = abstractFactory->getColor(), color->fill();
			delete shape, shape = 0;
			delete color, color = 0;
			delete abstractFactory, abstractFactory = 0;
		}
};

int main(int argc, char * argv[])
{
	AbstractFactoryDemo::run();
	return 0;
}
