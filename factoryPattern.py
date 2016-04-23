#!/usr/bin/env python 

class Operator:
	def calculate(self, op1, op2):
		pass 

class Add(Operator):
	def calculate(self, op1, op2):
		return op1 + op2
class Sub(Operator):
	def calculate(self, op1, op2):
		return op1 - op2
class Mul(Operator):
	def calculate(self, op1, op2):
		return op1 * op2
class Div(Operator):
	def calculate(self, op1, op2):
		try:
			return op1 / op2
		except:
			print 'second number must not be 0' 
			return 0

# using serviceLocator pattern 
class Cache:
	hashTable = { }
	def attach(self, elem, type):
		if type not in self.hashTable:
			self.hashTable[type] = elem
	def getOperator(self, type):
		if type in self.hashTable:
			return self.hashTable[type]
		else:
			return None
class OperatorCreator:
	@staticmethod
	def InitOperator(type):
		print 'Create operator %s' % type
		if '+' == type:
			return Add()
		elif '-' == type:
			return Sub()
		elif '*' == type:
			return Mul()
		elif '/' == type:
			return Div()
		else:
			return None

class OperatorFactory:  # factory with cache
	cache = Cache();
	@classmethod
	def getOperator(cls, type):
		operator = cls.cache.getOperator(type) # first find it in cache
		if not operator: # not in cache 
			operator = OperatorCreator.InitOperator(type) # create it
			cls.cache.attach(operator, type) # cache it 
		
		return operator

if __name__ == '__main__':
	# op = raw_input('Operator : ')
	# op1 = input('a : ')
	# op2 = input('b : ')
	try: 
		print OperatorFactory.getOperator('+').calculate(1, 2) 
		print OperatorFactory.getOperator('+').calculate(1, 2) 
		print OperatorFactory.getOperator('*').calculate(1, 2) 
		print OperatorFactory.getOperator('+').calculate(1, 2) 
		print OperatorFactory.getOperator('*').calculate(1, 2) 
		print OperatorFactory.getOperator('/').calculate(1, 0) 
		print OperatorFactory.getOperator('a').calculate(1, 2) 
	except:
		print 'Wrong expression'

