#include <iostream>
using namespace std;

template<class item>
class Iterator;

template<class item>
class ConcreteAggregate;

template<class item>
class Aggregate {
	public:
		virtual Iterator<item> * createIterator() = 0;
		virtual ~Aggregate(){ }
};

template<class item>
class ConcreteAggregate : public Aggregate {
	private:
		vector<item> data;
	public:
		ConcreteAggregate()
		{
			data.push_back(1);
			data.push_back(2);
			data.push_back(3);
		}
		Iterator<item> * createIterator()
		{
			return new ConcreteIterator<item>(this);
		}
		item & operator[](int index)
		{
			return data[index];
		}
		int size()
		{
			return data.size();
		}
};

template<class item>
class Iterator {
	public:
		virtual void first() = 0;
		virtual void next() = 0;
		virtual item * current() = 0;
}; 

template<class item>
class ConcreteIterator : public Iterator<item> {
	private:
		ConcreteAggregate<item> * aggregate;	
		int cur;
	public: 
		ConcreteIterator(ConcreteAggregate<item> * aggr) : aggregate(aggr), cur(0){ }
		void first()
		{
			cur = 0;
		}
		void next()
		{
			if(cur < aggregate->size()) cur++;
		}
		item * current()
		{
			if(cur < aggregate->size()) return &(*aggregate)[cur];
			else return 0; 
		}
};

int main(int argc, char * argv[])
{
	return 0;
}
