---
title: Iteration Efficiency
layout: post
---

Iterating through a value and computing another value from that

Try to update that value directly

Example: Computing Sin
----------------------------------------------------------------

Let's take a simple example: Iterating an angle and computing 
$\sin$ from that angle. A simple example would be as follows:

```c++
// Declare iteration size, change 
// in theta and outputs
int n = 100000;
float outputs[n];
float dth = 0.01;

// Iterate theta and compute sin
float th = 0.0f;
for (int i = 0; i < n; ++i) {
    outputs[i] = sin(th);
    th += dth;
}
```

How is $\sin$ computed

$$
\sin{\theta} = \theta - \frac{\theta^3}{3!} + \frac{\theta^5}{5!} 
        - \frac{\theta^7}{7!} + \dots
$$

$\sin{\theta}$ is an infinite series. So, it's kind of an 
understatement that $\sin{\theta}$ is expensive. We can do 
better.

The change in $\sin$ is actually proportional to $\cos$, and 
the change in $\cos{\theta}$ is proportional to $-\sin{\theta}$. 
So, if we want to update $\sin{\theta}$, we just add 
$\cos{\theta} d\theta$, and if we want to update $\cos{\theta}$, 
we add $-\sin{\theta} d\theta$.

$$
\begin{aligned}
    \sin{(\theta + d\theta)} &\approx \sin{\theta} &+ \cos{\theta} d\theta \\
    \cos{(\theta + d\theta)} &\approx \cos{\theta} &- \sin{\theta} d\theta
\end{aligned}
$$

Track two values: $\sin$ and $\cos$. $\sin$ changes by $\cos$. 
$\cos$ changes by $-\sin$.