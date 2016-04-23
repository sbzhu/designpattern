#include <iostream>
#include <list>
#include <string>
#include <typeinfo>
using namespace std;

class Mediator;

class Person {
	protected:
		Mediator * mediator;
	public:
		string name;
	public:
		Person(string _name, Mediator * _mediator) : name(_name), mediator(_mediator){ }
		void setMediator(Mediator * mediator)
		{
			this->mediator = mediator;
		}

		virtual void sendMessage(const string & message) = 0;
		virtual void getMessage(const string & message, const string & sender) = 0;
};

class Mediator {
	protected:
		list<Person *> renterList;
		list<Person *> landlordList;
	public:
		void addRenter(Person * renter){ 
			renterList.push_back(renter); 
		}
		void addLandlord(Person * landlord){ 
			landlordList.push_back(landlord); 
		}
		virtual void sendToRenter(const string & message, const string & sender) = 0;
		virtual void sendToLandlord(const string & message, const string & sender) = 0;
		void broadcast(list<Person *> & personList, const string & message, const string & sender)
		{ // broadcast to landlord 
			list<Person *>::iterator iter;
			for(iter = personList.begin(); personList.end() != iter; iter++)
			{
				(*iter)->getMessage(message, sender);
			} 
		}
};

class Renter : public Person {
	public:
		Renter(string name, Mediator * mediator) : Person(name, mediator){ }
		void sendMessage(const string & message)
		{
			cout << name << " : >>[landlord] " << message << endl;
			mediator->sendToLandlord(message, name);
		}
		void getMessage(const string & message, const string & sender)
		{
			cout << name << " : <<[" << sender << "] " << message << endl;
		}
};
class Landlord : public Person {
	public:
		Landlord(string name, Mediator * mediator) : Person(name, mediator){ }
		void sendMessage(const string & message)
		{
			cout << name << " : >>[renter] " << message << endl;
			mediator->sendToRenter(message, name);
		}
		void getMessage(const string & message, const string & sender)
		{
			cout << name << " : <<[" << sender << "] " << message << endl;
		}
};

class HouseAgency : public Mediator {
	public:
		void sendToLandlord(const string & message, const string & sender)
		{
			broadcast(landlordList, message, sender);
		}
		void sendToRenter(const string & message, const string & sender)
		{
			broadcast(renterList, message, sender);
		} 
};

class MediatorDemo {
	public:
		static void run()
		{
			Mediator * mediator = new HouseAgency();
			Person * renterA = new Renter("Abel", mediator);
			Person * renterB = new Renter("Mike", mediator);
			Person * renterC = new Renter("Lee", mediator);
			Person * renterD = new Renter("Dong", mediator);
			Person * landlordA = new Landlord("Ding", mediator);
			Person * landlordB = new Landlord("Du", mediator);

			mediator->addRenter(renterA);
			mediator->addRenter(renterB);
			mediator->addRenter(renterC);
			mediator->addRenter(renterD);
			mediator->addLandlord(landlordA);
			mediator->addLandlord(landlordB);

			renterB->sendMessage("I want a big house facing the sea !");

			landlordA->sendMessage("I have a big house facing the sea and only costs $500 !");
		}
};
int main(int argc, char * argv[])
{
	MediatorDemo::run();
	return 0;
}
