import numpy as np
import numpy.linalg
from random import *


#
# Adds doors in the maze graph
#
def addDoor(s1,s2,M):
    M[s1][s2] = 1
    M[s2][s1] = 1


#
# M is the matrix of a graph
# after calling M is an associated Markov Chain and N contains numer of doors
# for each state
#
def createMarkov(M,N):
    x = M.shape[1]
    
    for i in range(x):
        c = 0.0
        l = []
        for j in range(x):            
            if M[j][i] > 0:
                l.append(j)
                c+=1
        for j in l:
            M[j][i] = 1.0 / c
        N[i] = c


#
# Maze creation
#
#
# I create a maze with no doors
#
P = np.zeros((16,16),dtype=float)
#
# I add some doors to make sure the graph is connected
#
for i in range(3):
    addDoor(i,i+1,P)  
    addDoor(i+4,i+5,P)
    addDoor(i+8,i+9,P)
    addDoor(i+12,i+13,P)
    addDoor(4*i,4*(i+1),P)
#
# and then add 3 more doors
#
addDoor(1,5,P)
addDoor(6,10,P)
addDoor(9,13,P)

#
# The graph is constructed and I now rescale entries so
# that we have a Markov Chain. At the same time I record
# the number of doors out of each room 
#
N = np.zeros((16))
createMarkov(P,N)
n = np.sum(N) # Twice the number of doors


#
# I create the matrix W
#
w = np.array([x/n for x in N])
W = np.transpose(np.array([w for x in range(16)]))

#
# And find the fundamental matrix
#
Z = np.linalg.inv(np.identity(16)-P+W)


#
# The answer to question 1 
#
print("The expected number of turns to get from 0 to 16 is:",(Z[15][15]-Z[15][0])/w[15])





#
#
# We now set up a simulation to do the same calculation.
# Here I use a different representation of the Maze, created from the matrix above.
#
L = []
for i in range(16):
    l = []
    for j in range(16):
        if P[j][i] != 0:
            l.append(j)
    L.append(l)


print(L)

seed()
count = 0.0
numsim = 100000
i = 0
while i < numsim:
    state = 0
    while state != 15:
        state = L[state][randint(0,len(L[state])-1)]
        count += 1
    i += 1

print("The expected number of turns to get from 0 to 16 is: ",count / numsim)

            
        


