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

So now we differentiate with respect to the entire vector $\textbf{a}$ and then solve 
for $\textbf{a}$. I'll spare you the math (mainly because it won't fit on the page), 
but, if you use this [cheat sheet]() for vector/matrix calculus, you can verify this 
derivative for yourself

$$
\frac{dJ}{d\textbf{a}} = 2(\textbf{X}^T\textbf{X}\textbf{a} - \textbf{y}^T\textbf{X})
$$

Now we set to 0 and rearrange to get our final equation

$$
2(\textbf{X}^T\textbf{X}\textbf{a} - \textbf{y}^T\textbf{X}) = 0
$$

$$
\textbf{X}^T\textbf{X}\textbf{a} = \textbf{y}^T\textbf{X}
$$

Revisiting the Single Variable Example
----------------------------------------------------------------------------------------

So let's say for example we have only 1 input. Our $\textbf{X}$ "matrix" would be

$$
\textbf{X} = \begin{bmatrix}
    x_0 \\
    x_1 \\
    x_2 \\
    \vdots \\
    x_N
\end{bmatrix}
$$

We add the column of 1's to make our matrix this

$$
\textbf{X} = \begin{bmatrix}
    1 & x_0 \\
    1 & x_1 \\
    1 & x_2 \\
    \vdots & \vdots \\
    1 & x_N
\end{bmatrix}
$$

Next we compute $\textbf{X}^T\textbf{X}$ and $\textbf{y}^T\textbf{X}$

$$
\textbf{X}^T\textbf{X} = \begin{bmatrix}
    1 & 1 & 1 & ... & 1 \\
    x_0 & x_1 & x_2 & ... & x_N
\end{bmatrix} \begin{bmatrix}
    1 & x_0 \\
    1 & x_1 \\
    1 & x_2 \\
    \vdots & \vdots \\
    1 & x_N
\end{bmatrix}
$$
