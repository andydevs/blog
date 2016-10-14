---
layout:     post
title:      Optimization
date:       2016-9-18
categories: education
---

Imagine, if you will, that you happen to be stuck on a mountain and would like to get down to the lodge at the lowest spot on the mountain. However, you are also unfortunately blindfolded, and can only "see" what you can feel with your feet. How would you get down?

What you could do is feel with your feet where the ground slopes down and step in that direction, doing so repeatedly until the ground feels level in all directions. If you take off your blindfold, you should've reached ground level.

This is the basis of gradient descent, one of many optimization algorithms. Just think of the mountain as any function of one or more input values, with your height on the mountain corresponding to the output of the function. Your computer starts at random inputs, a random spot on the mountain. It can't see anything beyond it's local patch of ground. It only computes the gradient of the function at this patch, figures out where it slopes down, and travels a little in that direction, until the slope is mostly level (or almost zero). When the algorithm finishes, the computer would've found the lowest point, or the minimum, of the function.

Aside from altitude on a mountain, there are other things that you would want to find the minimum (or maximum!) of. If you want to build a fenced area, say a pig pen, you might want to find the minimum amount of fencing you'd want to buy to build a pen of a certain area. If you're selling a product, you might want to find the price you'd sell it at to generate the maximum revenue. If you're into machine learning, you will definitely want to find the minimum predictive error for a particular machine learning model. Optimization problems appear everywhere, and there are many algorithms that can tackle these problems.

## But First

You need a function with one output and one or more inputs. Let's call your input vector `x`, and your function `f(x)`. It can be your altitude on a mountain based on your location, the revenue from a product for selling at a particular price, or the cost of fencing based on how much fencing you buy. Your function needs to at least be differentiable (within the interval you're checking), so it cant have any breaks or gaps (like an inverse function).

## Gradient Descent

Gradient descent is the algorithm described above, and one of the simpler algorithms to implement:

	x := random
	until delta <= EPSILON
    	delta := f'(x)
    	x := x - ALPHA * delta

To prevent the code from running forever, the value of `EPSILON` determines what is considered a "zero" slope. Any `delta` value less than `EPSILON` is considered 0. The value `ALPHA` is the step size, or learning rate. It determines how long of a step the computer takes in any given iteration. If the computer takes a big step, it may miss the minimum, or could get stuck bouncing back and forth above the minimum without ever reaching it. If the step size is small, the algorithm may take very long to reach the minimum and could even stop moving altogether. There's no proper tweak to these numbers that works for all occasions, these need to be set for each function.

### Stochastic Gradient Descent

One of the limitations of gradient descent

	x := random
	delta := zero vector of length == x
	i := 0
	until delta <= EPSILON
		delta := f'(x)[i]
		x[i] := x[i] - ALPHA * delta
		i := (i + 1) % (length of x)

## Newton's Method for Optimization

Newton's method is a bit more clever than Gradient Descent. To explain it, we first have to talk about zeros.

### Finding Zeros

The way most people learn to find the zeros of a function (places where the function equals 0) is through functional analysis. Most people have learned how to find the zeros of a polynomial by factoring. For example, you can rewrite the function `x^2 + 5x + 6` as `(x + 3)*(x + 2)`. The zeros of this function are then -3 and -2 (taken from the factored coefficients). You also know that the one zero of `ln(x)` is 1, and the zeros of `sin(x)` are all integer multiples of pi. However, this process of finding zeros is tedious to do by hand, and doesn't generalize well, especially in computational programming, where you may need to find the zeros of a function or model that you can't really write down (like a neural network). There is a more general algorithm to discover a zero, or get close to one, using linear approximation and some computation.

The formula for a linear approximation is `L(x) = f(x0) + f'(x0)*(x - x0)`, where `x0` is the pivot point around which the function's being approximated by the line. Doing a little algebra, you find that the zero point of the approximation is given by `x = x0 - f(x0)/f'(x0)`. Now, this is not the actual zero point of the function, but it is close, and that's the important part. You can then set this zero point to the new `x0` and find the zero of the new linear approximation at that point, and it will be even closer to the actual zero of the function. Do this repeatedly, and you will eventually converge to the zero. This is Newton's method for finding zeros.

	x := random
	until f(x) <= EPSILON
		delta := f(x)/f'(x)
		x := x - ALPHA*delta

In this algorithm, `EPSILON` is what is considered close enough to zero, and `ALPHA` is the step size to travel in, all to prevent the program from potentially running forever.

### Finding Minima

Now that we know how to use Newton's method to find the zeros of a function, we can extend this algorithm to minima. Instead of taking a linear approximation, we use a _quadratic_ approximation, which involves the second derivative. The formula for a quadratic approximation is `Q(x) = f(x0) + f'(x0)*(x - x0) + 1/2*f''(x0)*(x - x0)^2`.