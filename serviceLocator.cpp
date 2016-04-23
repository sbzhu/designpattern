#include <iostream>
#include <list>
#include <typeinfo>
#include <string>
#include <ctime>
#include <map>
using namespace std;

class Service {
	public:
		virtual string name() = 0;
	public:
		virtual void execute() = 0;
};

class ServiceA : public Service {
	public:
		string name(){ return "ServiceA"; }
		void execute()
		{
			cout << "Execute ServiceA" << endl;
		} 
};
class ServiceB : public Service {
	public:
		string name(){ return "ServiceB"; }
		void execute()
		{
			cout << "Execute ServiceB" << endl;
		} 
};
class InitialContext {
	public:
		Service * InitServer(string serviceName)
		{
			if("ServiceA" == serviceName)
			{
				cout << "Init servace A" << endl;
				return new ServiceA(); 
			}
			else if("ServiceB" == serviceName)
			{
				cout << "Init servace B" << endl;
				return new ServiceB(); 
			}
			else return 0;
		}
};

class Cache {
	private:
		map<string, Service *> services;
	public:
		Service * getService(string serviceName)
		{
			map<string, Service *>::iterator iter;
			if(services.end() != (iter = services.find(serviceName))) return iter->second;
			else return 0;
		}
		void addService(Service * service)
		{
			if(services.end() == services.find(service->name())) 
			{
				services[service->name()] = service; 
			}
		}
};

class ServiceLocator { // Actually it's factory pattern
	private:
		static Cache * cache;
	public:
		static Service * getService(string serviceName)
		{
			Service * service = cache->getService(serviceName);// first find it in cache

			if(!service) // if not in cache
			{
				service = (new InitialContext())->InitServer(serviceName); // create it
				cache->addService(service); // cache it
			} 

			return service;
		}

};
Cache * ServiceLocator::cache = new Cache();

class ServiceLocatorDemo {
	public:
		static void run()
		{ 
			ServiceLocator * serviceLocator = new ServiceLocator();
			serviceLocator->getService("ServiceA")->execute();
			serviceLocator->getService("ServiceA")->execute();
			serviceLocator->getService("ServiceA")->execute();
			serviceLocator->getService("ServiceB")->execute();
			serviceLocator->getService("ServiceB")->execute();
			serviceLocator->getService("ServiceC")->execute(); // it's not safe here, should add try / catch
		}
};

int main(int argc, char * argv[])
{
	ServiceLocatorDemo::run();
	return 0;
}
