# Kompendium | Matematikk for programmering REA1121


[TOC]

## 0. Enumeration

### Ordered Selection, allowing repeats

### Ordered selection, without repeats

### Unordered selection, allowing repeats

### Unordered selection, without repeats

## 1. Probability

### Sample space and event space

### Independent events

### Dice

### Cards

### Independence and Conditional Probabilities

### Bayes Theorem

### Random Variables

**Discrete random variables** -

**Continuous random variables** - 

### Probability distribution

**(0-1) distribution** - 

**Bernoulli distribution** - 

**Binominal distribution** - 

**Poisson distribution** - 

### Measures of random variables

**Mean** -

**Variance** - 

**Standard deviation** -

### Probability simulations using Python

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

## 2. Markov Chains

A Markov Chain is a *network* with these two properties:

1. The weight of each edge represents a probability, and the value of the weights is in the range [0…1].
2. The sum of all the weights leaving a node is **1**.

### States and chains

The nodes in a Markov Chain are called states. A state can be in two different modes.

**Transient state** -

**Absorbing state** -

**Absorbing chain** - 

**Ergodic chain** -

### The Stochastic Matrix

**Matrix blocks [Q, 0, R, I]** - 

### The Fundamental Matrix N

**N\[i][j]** - 

**RN\[i][j]** -

**cN\[i][j]** -

### Matrix calculations with [Numpy & Python] and [Eigen & C++]

## 3. Logic

### Bitwise operations

| Operation  | Symbol      | Signature     |
| ---------- | ----------- | ------------- |
| And        | &           | 0 - 0 - 0 - 1 |
| Or         | \|          | 0 - 1 - 1 - 1 |
| Xor        | ^           | 0 - 1 - 1 - 0 |
| Not        | ~  (not or) | 1 - 0 - 0 - 0 |
| ShiftLeft  | <<          | <<1 == 10     |
| ShiftRigth | \>>         | \>>1 ==  0    |
|            |             |               |

### Prolog

## 4. Matrices

### Vectors

**Linear combination**

**Dot product**

**Length**

**Unit vector**

**Angle**

### Vector spaces

**Sub space**

**Linear independence**

**Basis**

**Orthonormal basis**

**Dimension**

**Column space**

**Nullspace**

**Rank**

### Othogonality

**Projection**

**Least-squares approximation**

**Pseudoinverse**

### Eigen values and Eigen Vectors

**Eigenvalue - Eigenvector**

**Diagonalization**

**Symmetric matrix**

**Similar matrix**





## 5. Interpolation



#### HP-bar and other examples of Linear interpolation

#### Curves

**Polynomial functions** - 

**Rational functions** - 

**Trigonometric functions** - 

**Normal distribution aka *Bell Curve*** - 

**Clamp** - 

**Smoothstep** -

**Parametric curves** - 

**Circle curve** - 

#### **Physics in games**

Games tend to take certain freedoms in the way they implement physics. This is of course to make something that is better than the real world. See Lens

**Double jump** -

**Varying gravity** - 

#### LERP - Linear Interpolation

LERP is commonly used as the name of the funciton, which implements *Linear interpolation*

```javascript
function LERP (float t, Vector a, Vector b) 
{
   return (1-t)*a + t*b;
}
```



**Easing LERP** - 

#### What can be interpolated? 

- Position
- Color
- rotation
- size
- shape

#### Quadratic Bezier curves

Deifinition: Interpolation between two linear interpolations

**Control points** -

**Cubic Bezier curves** -

#### SLERP - Spherical interpolation

Interpolation with rotation.

## 6. Procedural

## 7. Path Finding

## 8. Mechanics

## 9. Functional Programming

## 10. Exam Review







