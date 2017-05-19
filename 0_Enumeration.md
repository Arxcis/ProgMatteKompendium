[TOC]

# 0. Enumeration


## 0.1 Counting in different ways



Enumeration is a fancy word for counting
$$
1 + 1 + 1 + 1 + 1 = 5 \\
5  \times 1 = 5
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
enumerate(n \land m) = n  \times m
$$


**Rule of Bijection**

There is also a third rule. Sometimes you cannot solve a problem directly, but what you can do is translate the the problem to something we know how to solve. @example needed



## 0.2 Common counting situations

**Ordered Selection, allowing repeats**

$$
n^m
$$


**Ordered selection, without repeats**

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



<a name="#brilliant.org">1</a>: https://brilliant.org/wiki/rule-of-sum-and-rule-of-product-problem-solving/
