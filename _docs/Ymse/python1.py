#
# Some basics
#


#
# While loop
#
i = 0
while i < 10:
        print(i)
        i += 1


#
# For loop
#
for i in range(10):
        print(i)

for i in range(10,20,2):
        print(i)


#
# If statement
#
if 2 > 3:
        print("yes")
else:
        print("no")


#
# Lists
#
l = [1,2,3,4,[1,2,3]]
print(len(l))
print(l[0])
print(l[1:3])
l[1:3] = []
l.append(10)

for i in  l:
        print(i)


#
# Function definition - we didnt look at this due to lack of time, but
# you should learn how to create functions
#
def f(n):
        print(n)
        return n*n  

print(f(20))


#
# Local and global variables
#
test = 100
test2 = 100
def g(n):
        test = 1000  # local variable, global test is still 100
        global test2 # global variable
        test2 = 1000 
        test3 = 1    # local variable, cannot be accessed outside function  
       
        
g(20)
print(test)
print(test2)
# print(test3) error message because test2 is local to g(n)






#
# Importing modules
#
from random import *  # like include + using namespace in c++
import math    # like include in c++ (have to write math.sqrt(10)

math.sqrt(10)

seed() 

#
# Prob all six, six dice
#
'''
count = 0.0
i = 0
n = 1000000
while i < n:
	i += 1
	allsix = True
	for j in range(6):
		if randint(1,6) != 6:
			allsix = False
	if allsix: count += 1

'''

#
# What to do with rare events: i.e. probability less than 1 / 1000 
#
# We can for instance split the problem. For example with the intersection of
# three events A, B and C:
#
# P(A and B and C) = P(A|B and C) * P(B|C) * P(C)
#
#


#
# Calculate area of unit circle
#
'''count = 0.0
n = 100000
i = 0
while i < n:
	i += 1
	x = uniform(-1,1)
	y = uniform(-1,1)
	if x*x + y*y < 1:    # test for inside circle
		count += 1

print(4*count / n)  #Bounding box has area 4, and count/n is the percentage of the bounding box
'''

#
# How many runs should we do
# 
# Roughly: to increase precision with one digit, run 100* as many runs.
#

#
# Problem: Bus with 20 people
#          10 bus stops
#          people get off at uniformly distributed random stops
#          Question: How many times does the bus stop?
#
'''
count = 0.0
n = 10000
i = 0
while i < n:
	i += 1
	l = [randint(1,10) for j in range(20)]
	m = set(l)
	count += len(m)

print(count / n)
'''


#       the line m = set(l) could be replaced with
#
#	m = []
#	for x in l:
#		if x not in m:
#			m.append(x)
#	
#
#       the line l = [randint(1,10) for j in range(20)] could be replaced with
#
#       l = []
#       for i in range(20):
#	        l.append(randint(1,10))


#
# 2x2 maze with rooms  0 1
#                      2 3 
#
# What is the average number of moves needed to go from room 0 to room 3
#


'''maze = [[1,2],[0,3],[0],[1]]  # We create the maze
n = 10000
i = 0
count = 0.0
while i < n:
	i += 1
	state = 0
	while state != 3:
		count += 1
		# A list is indexed by 0...len - 1
		state = maze[state][randint(0,len(maze[state])-1)]
		

print(count / n)
'''
