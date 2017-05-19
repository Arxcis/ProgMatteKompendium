[TOC]

# 0. Enumeration


## 0.1 Counting in different ways



Enumeration is a fancy word for counting
$$
1 + 1 + 1 + 1 + 1 = 5 \\
5  \cdot 1 = 5
$$

When using addition and multiplication while counting, keep in mind that they have to follow some simple rules.


**Rule of Sum**

If you have *n* choices for one action, and *m* choices for another action, and the two actions cannot be #done at the same time, in total you can choose between *n* + *m* actions.<sup>[[1]](#brilliant.org)</sup>  Example: You wake up and don't know what to wear. You have 10 pants and 5 shorts to pick from. It does not make sense to wear more than 1 piece,  so you have 10 + 5 = 15 clothes to pick from.
In mathematical terms @correctness:

$$
enumerate(n \oplus m) = n + m
$$


**Rule of Product**

If there are *n* choices for one action, and *m* choices of doing something else after that, then there are *n* x *m* ways of doing both actions.<sup>[[1]](#brilliant.org)</sup> Example: After picking one of the 15 leg-pieces mentioned above, you also want to pick one of your 8 sweaters. The number of ways you can pick one leg-piece and one sweater, is 15 x 8 = 120.
In mathematical terms @correctness:

$$
enumerate(n \land m) = n  \cdot m
$$


**Rule of Bijection**

There is also a third rule. Sometimes you cannot solve a problem directly, but what you can do is translate the the problem to something we know how to solve. @example needed



## 0.2 The 4 common counting situations

You have a bag of balls numbered *1 to n* and you pick out *m* of these balls at random.
There are two important questions to ask.

1. Does the order of the balls you picked matter? (ordered/unordered)

2. Are balls returned to the bag after being picked? (allow/disallow repeats)

   ​


**Ordered Selection, allowing repeats**

$$
n^m
$$


**Ordered selection, disallow repeats**

$$
P(m,m)
$$


**Unordered selection, allowing repeats**

$$
C(n+m-1, n-1)
$$


**Unordered selection, without repeats**

$$
C(n,m)
$$

​In Lotto, m = 7 balls are chosen from n = 34. The order doesn’t matter, and once a ball has been picked, it is not put back in the bag. There is only |  *E* |= 1 winning combination.
The probability for winning in Lotto is then:

$$
P =  \frac {|E|}{|S|} = \frac{1}{C(34,7)}

\\
|S| = C(34,7) = \binom {34}{7} =
	\frac {34 \cdot 33 \cdot 32 \cdot 31 \cdot 30 \cdot 29 \cdot 28 }
		  { 7 \cdot  6 \cdot  5 \cdot  4 \cdot  3 \cdot  2 \cdot  1 }
									= 5 \ 379 \ 616
\\
P(winning \ lotto) = \frac{1}{5 \ 379 \ 616}
$$


<a name="#brilliant.org">1</a>: https://brilliant.org/wiki/rule-of-sum-and-rule-of-product-problem-solving/
