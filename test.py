#!/usr/bin/env python 

class People:
	name = 'Jean' # it's public
	__age = 18 # it's private
	__sex = 'female' 

	def __init__(self, name, age, sex): # constructor
		self.name = name
		self.__age = age
		self.__sex = sex
	
	def __del__(self):
		pass

	def getAge(self):
		return self.__age

	@classmethod
	def getSex(cls): 
		return cls.__sex
	@staticmethod
	def setSex(sex):
		People.__sex = sex

p = People('Mike', 45, 'male')
print p.name 

print People.name  # like static value

People.name = "Jack" # change static value
print People.name

print p.getAge()

print People.getSex()

People.setSex('Male')
print People.getSex()
