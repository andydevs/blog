---
layout: post
title: A Primer on Linear Regression
---

Regression is at the core of Machine Learning’s DNA. We’re gonna talk about Linear Regression.

## Framing the Question

Suppose we have a set of data points $(x_i, y_i)$. we want to find a linear equation $\hat{y} = a_0 + a_1 x$ that best approximates this set.

The ideal is $\hat{y} = y$. But, of course, that’s not what we’re expecting. We frame the problem as getting $\hat{y}$ as equal to $y$ as possible. Luckily for us, we have a tool that can measure that.

## Distance

If two points in space are the same, then the distance between those two points is 0.

$$
\textbf{p} = \textbf{q} \rightarrow ||\textbf{q} - \textbf{p}|| = 0
$$

Simple enough. But if they are not equal, we can still measure their similarity, i.e. closeness, using their distance.  For example, if $\textbf{r}$ is closer to $\textbf{p}$ than $\textbf{q}$ is, then

$$
||\textbf{r} - \textbf{p}|| < ||\textbf{q} - \textbf{p}||
$$

So we can think of our estimated dataset $\hat{y}$ and our actual dataset $y$ as two points in a multidimensional space. Then we can compute the distance between the two points

$$
J = ||\textbf{y} - \hat{\textbf{y}}||
$$

If we sub in $\hat{y}$ for our original model formula

$$
J = ||\textbf{y} - a_0 - a_1 \textbf{x}||
$$

Our objective now is to find the right $a_0$ and $a_1$ values that minimize this quantity.

## Optimization

We'll make things simpler by considering the squared distance for now

$$
J = ||\textbf{y} - a_0 - a_1 \textbf{x}||^2
$$

Expand distance equation

$$
J = \sum_i{ (y_i - a_0 - a_1x_i)^2 }
$$

Differentiate $J$ with respect to $a_0$ and $a_1$. Optimization for $a_0$ and $a_1$ means setting both derivatives to 0.

$$
\frac{\partial{J}}{\partial{a_0}} = \sum_i{ 2(y_i - a_0 - a_1x_i) } = 0
$$

$$
\frac{\partial{J}}{\partial{a_1}} = \sum_i{ 2x_i(y_i - a_0 - a_1x_i) } = 0
$$

Expanding out and rearranging equations we get

$$
Na_0 + (\sum{x_i})a_1 = \sum_i{y_i}
$$

$$
(\sum{x_i})a_0 + (\sum{x_i^2})a_1 = \sum_i{x_iy_i}
$$

And what we find, in fact, is a system of linear equations! So we can rewrite it in matrix form

$$
\begin{bmatrix}
N & \sum_i{x_i} \\
\sum_i{x_i} & \sum_i{x_i^2}
\end{bmatrix}
\begin{bmatrix}
a_0 \\
a_1
\end{bmatrix}
= 
\begin{bmatrix}
\sum_i{y_i} \\
\sum_i{x_iy_i}
\end{bmatrix}
$$

Solving this equation for our input vector will get us our optimized $a_0$ and $a_1$ terms!

## Doing it in code

Using `numpy` and `matplotlib`

```python
data = np.loadtxt('mydata.csv', delimeter=',')
x = data[:,0]
y = data[:,1]
```

Construct our constants

```python
A = np.array([
    [ x.shape[0], x.sum()      ],
    [ x.sum(),    (x**2).sum() ]
])

B = np.array([
    y.sum(),
    (y*x).sum()
])
```

Now we find the inverse of `A` and multiply it with `B`

```python
Ainv = np.linalg.inv(A)
a = np.matmul(Ainv, B)
```