---
layout: post
title: Multivariable Linear Regression
---

$$
\hat{y_i} = a_0 + a_1 X_{i1} + a_2 X_{i2} + ... + a_N X_{iN}
$$

Add $x_0 = 1$ to the first column $X$.

$$
X = \begin{bmatrix}
    1 & X'_{01} & X'_{02} & ... & X'_{0N} \\
    1 & X'_{11} & X'_{12} & ... & X'_{1N} \\
    \vdots & \ddots & & & \vdots \\
    \vdots & & \ddots & & \vdots \\
    \vdots & & & \ddots & \vdots \\
    1 & & & & X'_{MN}
\end{bmatrix}
$$

Now our equation is

$$
\hat{y_i} = a_0 X_{i0} + a_1 X_{i1} + a_2 X_{i2} + ... + a_N X_{iN}
$$

We can write this in vector form as

$$
\hat{\textbf{y}} = \textbf{X}\textbf{a}
$$

Squared distance

$$
J = ||\textbf{y} - \hat{\textbf{y}}||^2 = ||\textbf{y} - \textbf{X}\textbf{a}||^2
$$

The vector form is

$$
J = (\textbf{y} - \textbf{X}\textbf{a})^T(\textbf{y} - \textbf{X}\textbf{a})
$$