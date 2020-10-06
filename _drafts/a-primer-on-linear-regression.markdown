---
layout: post
title: A Primer on Linear Regression
---

When people think of machine learning, they usually imagine the complex neural network algorithms that can find faces in images (or even [create faces](http://thispersondoesnotexist.com)... view at your own risk). All machine learning is, though, is finding patterns in data, and building models based on those patterns so we can make predictions. Humans do this intuitively, obviously, but computers have been able to do this for as long as they've been used for science and especially business. One of the simplest models you can make is a linear one: your prediction is just proportional to your data, shifted by some amount. The process of building one is called linear regression.

## Framing the Question

Suppose we have a set of data points $(x_i, y_i)$. We want to find a line that passes as close to all of these points as possible. Doing so would allow us to predict $y$ by looking at where the line is at the point $x$. Mathematically, we want to find a linear equation $\hat{y} = a_0 + a_1 x$ that best approximates this set.

So how do we start? The ideal is $\hat{y} = y$. But, of course, we're not expecting that, or we wouldn't have to do this. We frame the problem as getting $\hat{y}$ as equal to $y$ as possible. Luckily for us, we have a tool that can measure that.

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

If we sub our original model formula in for $\hat{y}$

$$
J = ||\textbf{y} - a_0 - a_1 \textbf{x}||
$$

Our objective now is to find the right $a_0$ and $a_1$ values that minimize this quantity.

## Optimization

If we expand out the distance estimation, we get this

$$
J = \sqrt{ \sum_i{ (y_i - a_0 - a_1x_i)^2 } }
$$

That square root is gonna make the derivative pretty complicated. Fortunately, we can make things simpler by ignoring the square root term. Normally, the square root has two solutions, one positive, one negative. However, we know that distances are always positive (something being -20 feet away from you doesn't really make sense). We also know that the derivative of the square root function is never 0, so there isn't a minima. Therefore, if we find the minima of the inner values, we can find the minima of the entire thing. So we only really need to concern ourselves with the squared distance formula

$$
J = ||\textbf{y} - \hat{\textbf{y}}||^2 = \sum_i{ (y_i - a_0 - a_1x_i)^2 }
$$

Differentiate $J$ with respect to $a_0$ and $a_1$.

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

## Conclusion

I have a corresponding [Jupyter Notebook](/notebooks/linear-regression) that shows how to 
do this in python with the same sample data set