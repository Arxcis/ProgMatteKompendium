[TOC]

# 1. Probability

##  1.1 Sample space and event space

In any given probability there's a _sample space_ and an _event space_ . When talking about sample space in probability, what we're really talking about is the set of possible outcomes. Likewise, when talking about event spaces, what we're really talking about is a specific set of outcomes. The event space is the set of outcomes matching a condition in our sample space.

**Example**

*You are picking a random letter in the alphabet. What is the probability of picking a vowel?*
$$
P(vowel)=\frac{\|S_{event}\|}{\|S_{sample}\|}\\
S_{sample} = \\\{ A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z\} \Rightarrow \|S_{sample}\|=26\\ $$$$
S_{event} = \{ A,E,I,O,U\} \Rightarrow \|S_{event}\|=5\\\\\text{(the letter y is not considered as a vowel in this case)}$$$$
P(vowel)=\frac{5}{26} \approx19\%
$$
While the cardinality of the sets/spaces is easy to obtain and use in probability in the example above, it's not always as useful to talk about the cardinality of the set. In more geometric cases where probability is applied (which arguably often is the case in game programming), it makes more sense to talk about the lengths, areas and/or volumes as the value of the sets/spaces, as were simply interested in the ratio between all possible outcomes and possible outcomes of a certain constraint.

**Example**

​	*Scenario*: You've made a spawning system for a game, where an entity is spawned within a circle with a radi of 15 units. There's a potential problem using this spawning system however, as there's a trap placed within the spawning circle. The trap itself causes damage to the entities if they're inside its area of effect (AoE [no, not Age of Empires ​:rage:​]). You want to figure out whether or not this will be an issue. The probability is considered neglectible if P(spawn in trap's AoE) <= 0.1% (i.e. every 1000th entity are allowed to spawn on the trap), thereby making the spawning system valid.

​	*Problem*: Will the spawning system be considered valid if the traps AoE-radi is 0.5 units?

​	*Solution*: As the spawning system uses a circle as it sample space, it's clear we're working with a 2D-problem. This means we can use the area to describe the ratio between sample space and event space:
$$
P(\text{spawn in AoE of trap}) =\frac{A(trap)}{A(spawn)}=\frac{\pi\frac{1}{2}^2}{\pi15^2}=\frac{1}{4\cdot15^2}=\frac{1}{900}\\
\frac{1}{900}\approx0.00111\dots > 0.1\%
$$
The probability of spawning inside the trap's AoE is just a tiny bit too high to be neglected. i.e. the spawning system is not valid (yet very close to being so).
$$
\text{Event space and sample space are simply the notion of "what we want" (event space)}\\
\text{from "what we're dealing with" (sample space). In  probability, we're really}\\
\text{just talking about the relation betwen them.}
$$

## 1.2 Independent events

## 1.3 Dice

## 1.4 Cards

## 1.5 Independence and Conditional Probabilities

## 1.6 Bayes Theorem

$$
P(A|B)=\frac{P(B|A)\cdot P(A)}{P(B)}
$$

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