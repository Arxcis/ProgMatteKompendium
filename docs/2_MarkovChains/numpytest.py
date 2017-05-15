#
# We import libraries
#

import numpy as np
import numpy.linalg
from random import *


#
# Writing   from numpy import *
# is similar to writing using namespace numpy in C++
# we would then not need the prefix np. for every use of numpy
#

#
# There are many ways to create matrices.
# We create a few matrices to work with
#

#
# a is a matrix of floats due to the use of decimal numbers
#
a = np.array([1.0,1.0,1.0,2.0,2.0,2.0,3.0,3.0,3.0]).reshape(3,3)


#
# b is a matrix of integers, defined in a different way
#
b = np.array([[1,2,3],[8,8,8],[3,1,2]])

#
# c is a matrix of floats
#
c = np.array([1,2,3,4,5,6,7,8,9],dtype = float)

#
# d is a matrix of float initialized to zero
#
f = np.zeros((10,10),dtype=float)


#
# We can print arrays
#
print(a)
print(b)
print(c)
print(f)

#
# We have elementwise operations on matrices
#
print(b+b)
print(4*b)
print(b*b)  # Note that this is NOT matrix multiplication

#
# Matrix multiplication is done by the operation dot
#
d=b.dot(b)
print(d)

#
# You can access indvidual elements by
# Note that starting index is 0
#
print(a[0][0])
a[0][0] = 10.0
print(a[0][0])
print(a[2])
print(a[-1]) # the last row

#
# You can also access parts of a matrix
#
#d[2:4][2:4] = np.array([1,2,3,4])

#
# You can also retrieve a part of a matrix
#
print(f[0:10,2])  # the third column (column with index 2)
print(f[2,0:10])  # the third row

#
# copying data 
#
g = f  # this is not copying, chaning g will also change f
h = f.copy() # this is a copy, changing h will not change f

#
# you can take out a part of a matrix and work on it separatedly
#
g = f[2:7,2:7]
g[0][0] = 10
print(f)  # pay attention to where the 10 goes


#
# Lets create a square matrix filled with some numbers
#
a = np.array([i*i + 1.0 for i in range(5*5)]).reshape(5,5)
#
# we check if it is invertible
#
if np.linalg.matrix_rank(a) == 5:
    print("yep! invertible")
    np.linalg.inv(a) # and print the inverse
else:
    print("no")
    
#
# OOps the matrix was not invertible and we got an error message
# Lets try again, this time with some random numbers
#
seed()
a = np.array([randint(1,100) + 1.0 for i in range(5*5)]).reshape(5,5)
#
# Lets check if it is invertible this time
#
if np.linalg.matrix_rank(a) == 5:
    print("yep! invertible")
    print(np.linalg.inv(a)) # and print the inverse
else:
    print("no")







