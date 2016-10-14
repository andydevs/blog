---
layout:     post
title:      Optimization
date:       2016-9-18
categories: education
---

Imagine, if you will, that you happen to be stuck on a mountain and would like to get down to ground level, or the lowest spot on the mountain. However, you are also unfortunately blindfolded, and can only "see" what you can feel with your feet. How would you get down?

What you could do is feel with your feet where the ground slopes down and step in that direction, doing so repeatedly until the ground feels level in all directions. If you take off your blindfold, you should've reached ground level.

This is the basis of gradient descent, one of many optimization algorithms. Just think of the mountain as any function of one or more input values, with your height on the mountain corresponding to the output of the function.

Your computer starts at random inputs, or a random spot on the mountain. It doesn't have the ability (at least in this algorithm) to see anything beyond it's local patch of ground. It only computes the gradient of the function at this patch, figures out where it slopes down, and travels a little in that direction, until the slope is mostly level (or almost zero). When the algorithm finishes, the computer would've found the lowest point, or the minimum, of the function.

Aside from altitude on a mountain, there are other things that you would want to find the minimum (or maximum!) of. If you want to build a fenced area, say a pig pen, you might want to find the minimum amount of fencing you'd want to buy to build a pen of a certain area. If you're selling a product, you might want to find the price you'd sell it at to generate the maximum revenue. If you're into machine learning, you will definitely want to find the minimum predictive error for a particular machine learning model. Optimization problems appear everywhere, and there are many algorithms that can tackle these problems.

## But First

You need a function with one output and one or more inputs. Let's call your input vector `x`, and your function `f(x)`. It can be your altitude on a mountain based on your location, the revenue from a product for selling at a particular price, or the cost of fencing based on how much fencing you buy. Your function needs to at least be differentiable (within the interval you're checking), so it cant have any breaks or gaps (like an inverse function).

## Gradient Descent

Gradient Descent is the algorithm described above, and one of the simpler algorithms to implement. The algorithm can be defined as follows:

	x := random
	while delta <= EPSILON
    	delta := f'(x)
    	x := x - ALPHA * delta

To prevent the code from running forever, the value of `EPSILON` determines what is considered a "zero" slope. Any `delta` value less than `EPSILON` is considered 0. The value `ALPHA` is the step size, or learning rate. It determines how long of a step the computer takes in any given iteration. If the computer takes a big step, it may miss the minimum, or could get stuck bouncing back and forth above the minimum. If the step size is small, the algorithm may take very long to reach the minimum.

### Stochastic Gradient Descent

	x := random
	delta := zero vector of length == x
	i := 0
	while delta <= EPSILON
		delta := f'(x)[i]
		x[i] := x[i] - ALPHA * delta
		i := (i + 1) % (length of x)

## Newton's Method for Optimization

Newton's method is a bit more clever than Gradient Descent. To explain it, we first have to talk about zeros.

### Finding Zeros

The way most people learn to find zeros is through functional analysis. Most people have learned how to find the zeros of a polynomial by factoring. You know that `ln(x) = 0` where `x = 1`, and `sin(x) = 0` whenever x is a multiple of pi.

But there is a general algorithm to discover a zero, or get close to one. And it uses linear approximation.

You can estimate a function at a particular point.

	x := random
	while delta <= EPSILON
		delta := f(x)/f'(x)
		x := x - ALPHA * delta