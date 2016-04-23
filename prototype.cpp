#include<iostream>
using namespace std;

class Prototype{
	public:
		virtual Prototype * clone() = 0;
};

class Cell : public Prototype {
	private:
		// copy constructor
		Cell(const Cell & cell){
			if(this == &cell) return; 
			// do copy
			cout << "Clone cell" << endl;
		}
	public:
		Cell(){ cout << "Construct cell" << endl; }

		Prototype * clone(){
			return new Cell(*this);// call copy constructor
		}
};


class PrototypeDemo {
	public:
		static void run()
		{
			Prototype * prototype = new Cell();

			Prototype * cell_1 = prototype->clone();
			Prototype * cell_2 = prototype->clone();

			delete prototype, prototype = 0;
			delete cell_1, cell_1= 0;
			delete cell_2, cell_2= 0;
		}
};

int main(int argc,char * argv[])
{
	PrototypeDemo::run();
	return 0;
}
