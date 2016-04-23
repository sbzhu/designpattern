#include<iostream>
#include<string>
#include<list>

using namespace std;

// Build KFC meal

class Food {
	public:
		string name;
		double price;
};

class Burger : public Food {
	public:
		void pack(){ cout << "Wrapper " << name << " with paper" << endl; }
};

class Drink : public Food {
	public:
		void bottle(){ cout << "Poor " << name << " into bottle" << endl; }
};

class VegBurger : public Burger {
	public:
		VegBurger(){ name = "VegBurger", price = 7.5; } 
};
class ChickBurger : public Burger {
	public:
		ChickBurger(){ name = "ChickBurger", price = 11.3; } 
};
class Milk : public Drink {
	public:
		Milk(){ name = "Milk", price = 6.2; } 
};
class Coke: public Drink {
	public:
		Coke(){ name = "Coke", price = 5.8; } 
};

// this is the product
class Meal {
	public:
		list<Food *> foodList;
		double price;
};

// the builder
class MealBuilder {
	public: 
		Meal * meal;

	public: 
		MealBuilder() { meal = new Meal(); }
		virtual void countPrice() = 0;
		virtual void packBurger() = 0;
		virtual void packDrink() = 0;
		Meal * getMeal() { return meal; }
};
// the director to guide building
class Director {
	public:
		static void direct(MealBuilder * mealBuilder)
		{
			mealBuilder->packDrink();
			mealBuilder->packBurger();
			mealBuilder->countPrice();
		}
};

class BreakFastBuilder : public MealBuilder
{ 
	public:
		void packBurger(){
			Burger * burger = new VegBurger();
			burger->pack();
		   	meal->foodList.push_back(burger); 
		}
		void packDrink(){
			Drink * drink = new Milk();
			drink->bottle();
		   	meal->foodList.push_back(drink); 
		}
		void countPrice()
		{
			double price = 0.0;
			list<Food*> & foodList = meal->foodList;
			for(list<Food*>::iterator iter = foodList.begin(); foodList.end() != iter; iter++)
			  price += (*iter)->price;

			price *= 0.97;// discount
			
			meal->price = price;
		}
};
class LunchBuilder : public MealBuilder
{ 
	public:
		void packBurger(){
			Burger * burger = new ChickBurger();
			burger->pack();
		   	meal->foodList.push_back(burger); 
		}
		void packDrink(){
			Drink * drink = new Coke();
			drink->bottle();
		   	meal->foodList.push_back(drink); 
		}
		void countPrice()
		{
			double price = 0.0;
			list<Food*> & foodList = meal->foodList;
			for(list<Food*>::iterator iter = foodList.begin(); foodList.end() != iter; iter++)
			  price += (*iter)->price;

			price *= 0.85;// discount
			
			meal->price = price;
		}
};


class BuilderDemo {
	public:
		static void run()
		{
			MealBuilder * mealBuilder = 0;
			Meal * meal = 0;

			// Let's make breakfast !
			mealBuilder	= new BreakFastBuilder();
			Director::direct(mealBuilder); 
			meal = mealBuilder->getMeal();
			cout << "Price is " << meal->price << endl;
			delete mealBuilder, mealBuilder = 0;
			delete meal, meal = 0;

			// then lunch 
			mealBuilder	= new LunchBuilder();
			Director::direct(mealBuilder); 
			meal = mealBuilder->getMeal();
			cout << "Price is " << meal->price << endl;
			delete mealBuilder, mealBuilder = 0;
			delete meal, meal = 0;
		}
};
int main(int argc, char * argv[])
{
	BuilderDemo::run();
	return 0;
}
