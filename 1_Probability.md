[TOC]

# 1. Probability

##  1.1 Sample space and event space

## 1.2 Independent events

## 1.3 Dice

## 1.4 Cards

## 1.5 Independence and Conditional Probabilities

## 1.6 Bayes Theorem

## 1.7 Random Variables

**Discrete random variables**

**Continuous random variables** 

## 1.8 Probability distribution

**(0-1) distribution** 

**Bernoulli distribution** 

**Binominal distribution** 

**Poisson distribution**

## 1.9 Measures of random variables

**Mean**

**Variance**

**Standard deviation**

## 1.10 Probability simulations using Python

**6 equal dice[^1]** - What is the probability of getting six equal dice in a throw?

```python
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

```

**Area of unit circle[^1]** - Simulating the value of *PI*

```python
count = 0.0
n = 100000
i = 0
while i < n:
    i += 1
    x = uniform(-1,1)
    y = uniform(-1,1)
    if x*x + y*y < 1:    # test for inside circle
        count += 1

print(4*count / n)  #Bounding box has area 4, and count/n is the percentage of the bounding box
```

**Bus with 20 people[^1]** - There are 10 bus stops and people get off at uniformly distributed random stops. How many times does the bus stop? [^1]

```python
count = 0.0
n = 10000
i = 0
while i < n:
    i += 1
    l = [randint(1,10) for j in range(20)]
    m = set(l)
    count += len(m)

print(count / n)
```

**2x2 maze with rooms[^1]** - What is the average number of moves needed to go from room 0 to room 3?

```python
maze = [[1,2],[0,3],[0],[1]]  # We create the maze
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

```



[^1]: Alle code examples on probability are gathered from "Example code from class" by Bernt, found at Fronter 2017