# The Grandfather of Machine Learning

Regression is at the core of Machine Learning’s DNA. We’re gonna talk about Linear Regression

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

Expand distance estimation

$$

$$

Differentiate $J$ with respect to $a_0$ and $a_1$. 

$$
\frac{\partial{J}}{\partial{a_0}}
$$