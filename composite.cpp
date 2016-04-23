#include<iostream>
#include<string>
#include<list>

using namespace std;

class Component {
	protected:
		string name;
	public: 
		virtual void add(Component *) = 0;
		virtual void remove(Component *) = 0;
		virtual void display(int depth) = 0;
};

class Composite : public Component { 
	protected:
		list<Component *> componentList;
	public: 
		Composite(string name) { this->name = name; }
		void add(Component * component){ componentList.push_back(component); }
		void remove(Component * component){ componentList.remove(component); }
		void display(int depth){
			for(int i = 0; i < depth; i++) cout << "-";
			cout << name << endl;

			list<Component *>::iterator iter = componentList.begin();
			for(; componentList.end() != iter; iter++) {
			   	(*iter)->display(depth+1); 
			}
		}
};

class Leaf : public Component { 
	public:
		Leaf(string name) { this->name = name; }
		void add(Component * component){ cout << "Can't have component under Leaf " << endl; }
		void remove(Component * component){ cout << "No component under Leaf " << endl; }
		void display(int depth){
			for(int i = 0; i < depth; i++) cout << "-";
			cout << name << endl;
		}
};

class ComponentDemo {
	public:
		static void run()
		{
			Component *root = new Composite("root"); 
			Component *a = new Composite("a"); 
			Component *b = new Composite("b"); 
			Component *aa  = new Leaf("aa"); 
			Component *ab  = new Leaf("bb"); 
			Component *ba  = new Leaf("ba"); 
			Component *bb  = new Leaf("bb"); 
			Component *ee  = new Leaf("ee"); 

			root->add(a);
			root->add(b);

			a->add(aa);
			a->add(bb);

			b->add(ba);
			b->add(bb);

			bb->add(ee);

			root->display(0);

			delete root, root = 0; 
			delete a, a = 0; 
			delete b, b = 0; 
			delete aa, aa = 0; 
			delete ab, ab = 0; 
			delete ba, ba = 0; 
			delete bb, bb = 0; 
		}
};

int main(int argc, char * argv[])
{
	ComponentDemo::run();
	return 0;
}
