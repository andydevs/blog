---
layout: post
title: Multivariable Linear Regression
---

We talked about linear regression with one variable. Now we can graduate and look at more 
common models which involve multiple input variables andthe relationships between those 
models. Again, the simplest model that can be created is a linear one: a weighted sum of 
input variables.

Forming the Equation
--------------------------------------------------------------------------------------------

Once again, we start with our equation, with a few modifications. In the single variable 
case, our input data was a single column vector $x_i$

$$
\hat{y_i} = a_0 + a_1 x_i
$$

Now we have a model with multiple input variables, so we have multiple input data vectors. 
Our model now becomes a weigted sum of all these inputs

$$
\hat{y_i} = a_0 + a_1 x_i + a_2 w_i + a_3 v_i + ...
$$

So now we're gonna have to find the derivative of all of these input parameters separately. 
Fortunately, as we've seen in the last post, we can rewrite things using vectors and matrices 
and make the equation a lot simpler.

For example, the above equation is a simple weighted sum of a bunch of input variables and 
can be rewritten as a dot product of two vectors

$$
\hat{y_i} = a_0 + \begin{bmatrix}
    x_i & w_i & v_i & ...
\end{bmatrix} \begin{bmatrix}
    a_1 \\
    a_2 \\
    a_3 \\
    \vdots
\end{bmatrix}
$$

We can even include the $a_0$ term in the dot product by including an extra a pseudo input 
in our input vector that is always equal to $1$. This just turns into $a_0$ when multiplied 
by $a_0$ in the dot product.

$$
\hat{y_i} = \begin{bmatrix}
    1 & x_i & w_i & v_i & ...
\end{bmatrix} \begin{bmatrix}
    a_0 \\
    a_1 \\
    a_2 \\
    a_3 \\
    \vdots
\end{bmatrix}
$$

We can bundle all of these dot products together into one matrix-vector product.

$$
\begin{bmatrix}
    \hat{y_0} \\
    \hat{y_1} \\
    \hat{y_2} \\
    \hat{y_3} \\
    \vdots
\end{bmatrix} = \begin{bmatrix}
    1 & x_0 & w_0 & v_0 & ... \\
    1 & x_1 & w_1 & v_1 & ... \\
    1 & x_2 & w_2 & v_2 & ... \\
    1 & x_3 & w_3 & v_3 & ... \\
    \vdots & \vdots & \vdots & \vdots & \ddots
\end{bmatrix} \begin{bmatrix}
    a_0 \\
    a_1 \\
    a_2 \\
    a_3 \\
    \vdots
\end{bmatrix}
$$

We can now write this in vector matrix form as

$$
\hat{\textbf{y}} = \textbf{X}\textbf{a}
$$

Optimizing
--------------------------------------------------------------------------------------------

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
then set that single derivative to 0 and rearrange it to get our equation. I'll spare you 
the math (mainly because it won't fit on the page), but, if you use this 
[Wikipedia article](https://en.wikipedia.org/wiki/Matrix_calculus) for vector/matrix 
calculus (it's probably correct), you can verify this derivative for yourself.

$$
\frac{dJ}{d\textbf{a}} = 2(\textbf{X}^T\textbf{X}\textbf{a} - \textbf{X}^T\textbf{y}) = 0
$$

So from this, our final matrix vector equation for optimizing looks like this

$$
\textbf{X}^T\textbf{X}\textbf{a} = \textbf{X}^T\textbf{y}
$$

Revisiting the Single Variable Example
----------------------------------------------------------------------------------------

So let's say for example we have only 1 input. We build our $\textbf{X}$ matrix with our
extra 1's column

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

You'll notice that these matrices look familiar. These are, in fact the matrices used in 
single-variable linear regression. You can say that linear regression with one variable 
is just a special case of linear regression with multiple variables!