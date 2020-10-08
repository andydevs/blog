---
layout: post
title: Multivariable Linear Regression
---

$$
\hat{y_i} = a_0 + a_1 X_{i1} + a_2 X_{i2} + ... + a_N X_{iN}
$$

$$
X' = \begin{bmatrix}
    X_{01} & X_{02} & ... & X_{0N} \\
    X_{11} & X_{12} & ... & X_{1N} \\
    \vdots & \ddots & & \vdots \\
    \vdots & & \ddots & \vdots \\
    1 & & & X_{MN}
\end{bmatrix}
$$

Add $x_0 = 1$ to the first column $X$ to make $X'$.

$$
X' = \begin{bmatrix}
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
\hat{y_i} = a_0X'_{i0} + a_1X'_{i1} + a_2X'_{i2} + ... + a_N X'_{iN}
$$

We can write this in vector form as

$$
\hat{\textbf{y}} = \textbf{X}\textbf{a}
$$

Squared distance

$$
J = ||\textbf{y} - \hat{\textbf{y}}||^2 = ||\textbf{y} - \textbf{X}\textbf{a}||^2 = (\textbf{y} - \textbf{X}\textbf{a})^T(\textbf{y} - \textbf{X}\textbf{a})
$$

Differentiate