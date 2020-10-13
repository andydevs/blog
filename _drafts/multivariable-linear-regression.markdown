---
layout: post
title: Multivariable Linear Regression
---

We talked about linear regression. Now we graduate to multivariable
linear regression

Forming the Equation
-----------------------------------------------------------------------

$$
\hat{y_i} = a_0 + a_1 X_{i1} + a_2 X_{i2} + ... + a_N X_{iN}
$$

To make this equation simpler, we add $x_0 = 1$ to the first column $X$.

$$
X = \begin{bmatrix}
    1 & X_{01} & X_{02} & ... & X_{0N} \\
    1 & X_{11} & X_{12} & ... & X_{1N} \\
    \vdots & \ddots & & & \vdots \\
    \vdots & & \ddots & & \vdots \\
    \vdots & & & \ddots & \vdots \\
    1 & & & & X_{MN}
\end{bmatrix}
$$

Now our equation is

$$
\hat{y_i} = a_0 X_{i0} + a_1 X_{i1} + a_2 X_{i2} + ... + a_N X_{iN}
$$

We can now write this in vector matrix form as

$$
\hat{\textbf{y}} = \textbf{X}\textbf{a}
$$

Optimizing
----------------------------------------------------------------------------------------

Once again, we use our squared distance model

$$
J = ||\textbf{y} - \textbf{X}\textbf{a}||^2
$$

If we're using the vector forms of our equation, this formula translates to

$$
J = (\textbf{y} - \textbf{X}\textbf{a})^T(\textbf{y} - \textbf{X}\textbf{a})
$$

So now we differentiate this term with respect to our $a$ values. Writing it in this form
allows us to take the derivative with respect to the entire vector $\textbf{a}$. We can 
then and then set that single derivative to 0 and rearrange it to get our equation. 
I'll spare you the math (mainly because it won't fit on the page), but, if you use this 
[Wikipedia article](https://en.wikipedia.org/wiki/Matrix_calculus) for vector/matrix 
calculus (it's probably correct), you can verify this derivative for yourself.

$$
\frac{dJ}{d\textbf{a}} = 2(\textbf{X}^T\textbf{X}\textbf{a} - \textbf{X}^T\textbf{y}) = 0 \\
\textbf{X}^T\textbf{X}\textbf{a} = \textbf{X}^T\textbf{y}
$$

Revisiting the Single Variable Example
----------------------------------------------------------------------------------------

So let's say for example we have only 1 input. Our $\textbf{X}$ "matrix" would be

$$
\textbf{X} = \begin{bmatrix}
    x_0 \\
    x_1 \\
    \vdots \\
    x_N
\end{bmatrix}
$$

We add the column of 1's to our matrix

$$
\textbf{X} = \begin{bmatrix}
    1 & x_0 \\
    1 & x_1 \\
    \vdots & \vdots \\
    1 & x_N
\end{bmatrix}
$$

Next we compute $\textbf{X}^T\textbf{X}$ and $\textbf{X}^T\textbf{y}$

$$
\begin{aligned}
\textbf{X}^T\textbf{X} &= \begin{bmatrix}
    1 & 1 & ... & 1 \\
    x_0 & x_1 & ... & x_N
\end{bmatrix} \begin{bmatrix}
    1 & x_0 \\
    1 & x_1 \\
    \vdots & \vdots \\
    1 & x_N
\end{bmatrix} \\
\textbf{X}^T\textbf{y} &= \begin{bmatrix}
    1 & 1 & ... & 1 \\
    x_0 & x_1 & ... & x_N
\end{bmatrix} \begin{bmatrix}
    y_0 \\
    y_1 \\
    \vdots \\
    y_N
\end{bmatrix}
\end{aligned}
$$

$$
\begin{aligned}
\textbf{X}^T\textbf{X} &= \begin{bmatrix}
    N & \sum{x_i} \\
    \sum{x_i} & \sum{x_i^2}
\end{bmatrix} \\
\textbf{X}^T\textbf{y} &= \begin{bmatrix}
    \sum{y_i} \\
    \sum{y_ix_i}
\end{bmatrix}
\end{aligned}
$$

You'll notice that these matrices look familiar. These are, in fact
the matrices used in single-variable linear regression. You can say
that linear regression with one variable is just a special case of
linear regression with multiple variables!