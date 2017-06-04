[TOC]

# 2. Markov Chains

A Markov Chain is a *network* with these two properties:

1. The weight of each edge represents a probability, and the value of the weights is in the range [0…1].
2. The sum of all the weights leaving a node is **1**.

## 2.1 States and chains

The nodes in a Markov Chain are called states.

**Transient state** - May not be revisited indefinetly once reached. In other words: The state has, through transitions, a connection to an absorbing state. After $$\lim_{n\to\infty}$$  iterations the state will "never" be a transient state.

**Recurrent state** - May be revisited indefinetly once reached. The state has no connection to an absorbing state unless it is also absorbing.

**Absorbing state** - The only transition(s) from the state leads back to itself. Normally such a state has only the one transition (as multiple transitions to itself can be simplified to just the one) with $100\%$ probability.

If a state is absorbing, it is never transient. It is however considered reccurent.

**Absorbing chain** - The chain has a transition from a state but no transition(s) back. The chain has a transition A $\rightarrow$ B, but no transition B $\rightarrow \dots \rightarrow$ A. 

An absorbing chain will have both reccurent states (or just the one) and transient states.

**Ergodic chain** - A chain is ergodic iff (if and only if) it's not absorbing. i.e. It will always be possible to move from one state to another through one or more transitions.

Ergodic chains has no absorbing states, thereby no transient states either. All states of an ergodic chain are recurrent.

## 2.2 The Stochastic Matrix

The stochastic matrix is another representation of the markov chain. The matrix describes the transitions in the markov chain where the matrix-values are the diferent probabilities of the transitions. This means that the matrix will have a specific set of properties normal matrices don't neccesarily have.

 @TODO properties - sum of rows/collumns = 1 etc.

**Matrix blocks [Q, 0, R, I]** - 

## 2.3 The Fundamental Matrix N

**N\[i][j]** - 

**RN\[i][j]** -

**cN\[i][j]** -

## 2.4 Matrix calculations with [Numpy & Python] and [Eigen & C++]