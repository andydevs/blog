---
layout:     post
title:      Optimization Algorithms
date:       2016-9-18
categories: education
---

Imagine, if you will, that you happen to be stuck on a mountainside and would like to get down to the lodge at the lowest spot in the valley. However, you are also unfortunately blindfolded, and can only "see" what you can feel with your feet. Nevermind how you got into this predicament. The first thing you would want to do is get down. How would you do that?

What you could do is feel with your feet where the ground slopes down and step in that direction, doing so repeatedly until the ground feels level in all directions. Theoretically, the ground will be level at the base of the valley. If you take off your blindfold, you should've reached ground level where the lodge is.

This is the basis of gradient descent, one of many optimization algorithms. Just think of the mountain as any function of one or more input values, with your height on the mountain corresponding to the output of the function. Your computer starts at random inputs, a random spot on the mountain. It can't see anything beyond it's local patch of ground. It only figures out where it slopes down (by finding the gradient) and travels a little in that direction, until the slope is mostly level (or almost zero). When the algorithm finishes, the computer would've found the lowest point, or the minimum, of the function.

Aside from altitude on a mountain, there are other things that you would want to find the minimum (or maximum!) of. If you want to build a fenced area, say a pig pen, you might want to find the minimum amount of fencing you'd want to buy to build a pen of a certain area. If you're selling a product, you might want to find the price you'd sell it at to generate the maximum revenue. If you're into machine learning, you will definitely want to find the minimum predictive error for a particular machine learning model. Optimization problems appear everywhere, so much so that it has become an entire field of study. Thus, there are many computer algorithm approaches to these problems. Two of the more popular ones will be discussed here.

## But First

We need a function. It can be your altitude on a mountain based on your location, the revenue from a product for selling at a particular price, or the cost of fencing based on how much fencing you buy. Your function needs to at least be continuous (within the interval you're checking), so it cant have any breaks or gaps (like an inverse or step function).

We will be using this function

	f(x) = 0.50 + 0.30*x + 0.24*x^2 - 1.52*x^3 - 0.11*x^4 + 0.69*x^5 - 0.17*x^6

It creates this nice graph:

![Function to Optimize]({{ site.url }}/resources/images/optimization/function_to_optimize.png){:.graphic-center}

Looking at the graph, we know that the minimum is somewhere near 1.6 and 1.8. Let's see if the computer can figure it out.

## Calculating Slope on a Computer

Most people know how to find the derivative of a function, if they know what the function is. However, in many cases (like machine learning), your function may be too complex to find the derivative for. Since we have computers, the simpler way to determine the slope at a point for any function is to just do it manually. The general slope formula (for one dimension) is `f'(x) = (f(x + h) - f(x)) / h`. You can just pick the smallest value of h that your computer can represent, and find the slope using this formula.

## Gradient Descent

Gradient descent is the algorithm described at the beginning of the post, and one of the simpler algorithms to implement:

	x := random
	until f'(x) <= EPSILON
    	x := x - ALPHA*f'(x)

This graphic visually represents what gradient descent does. The black dot is the current location in each iteration, and the green dot is the calculated next location (using the slope at that point)

![Gradient Descent]({{ site.url }}/resources/images/optimization/gradient_descent.gif){:.graphic-center}

To prevent the code from running forever, the value of `EPSILON` determines what is considered a "zero" slope. Any `delta` value less than or equal to `EPSILON` is considered 0. The value `ALPHA` is the step size, or learning rate. It determines how long of a step the computer takes in any given iteration. If the computer takes a big step, it may miss the minimum, or could get stuck bouncing back and forth above the minimum without ever reaching it. If the step size is small, the algorithm may take way too long to reach the minimum and could even stop moving altogether. There's no proper tweak to these numbers that works for all occasions, and they could be provided as function parameters.

There is however, more information that we can obtain from a function at a point aside from a gradient (various forms of the second derivative, the gradient convergence etc.). Could we use this information to take bigger, more precise steps, compared to gradient descent? What other kinds of algorithms can we implement with this new information?

## Newton's Method for Minima

Newton's Method for Minima, invented by Isaac Newton, is a bit more clever than Gradient Descent. It uses a form of the second derivative of the function to compute the minimum. To explain it, we first have to talk about zeros.

### Finding Zeros

The way most people learn to find the zeros of a function is through functional analysis. We've learned how to find the zeros of a polynomial by factoring. We also know that the one zero of `ln(x)` is 1, the zeros of `sin(x)` are all integer multiples of pi, and `1/x` has no zeros. We can use simple rules like these to find the zeros of a function through analysis.

However, this process of finding zeros is tedious to do by hand, and doesn't generalize well, especially in computational programming, where you may need to find the zeros of a function or model that you can't really write down (like a neural network). There is a more general algorithm to discover a zero, or get close to one, using linear approximation and some computation.

The formula for a linear approximation is `L(x) = f(x0) + f'(x0)*(x - x0)`, where `x0` is the pivot point around which the function's being approximated by the line. Doing a little algebra, you find that the zero point of the approximation is given by `x = x0 - f(x0)/f'(x0)`. Now, this is not the actual zero point of the function, but it is close, and that's the important part. You can then set this zero point to the new `x0` and find the zero of the new linear approximation at that point, and it will be even closer to the actual zero of the function. Do this repeatedly, and you will eventually converge to the zero. This is Newton's Method for Zeros.

	x := random
	until f(x) <= EPSILON
		x := x - ALPHA*f(x)/f'(x)

Again, this can be graphically represented. In this animation, the yellow line represents the linear approximation at each iteration, and the yellow dot represents the approximated zero point.

![Newton's Method for Zeros]({{ site.url }}/resources/images/optimization/newtons_method_for_zeros.gif){:.graphic-center}

In this algorithm, `EPSILON` is what is considered close enough to zero, and `ALPHA` is the step size to travel in, all to prevent the program from potentially running forever.

### Finding Minima

Now that we know how to use Newton's method to find the zeros of a function, we can extend this algorithm to minima. Instead of taking a linear approximation, we use a _quadratic_ approximation, which involves the second derivative. The formula for a quadratic approximation is `Q(x) = f(x0) + f'(x0)*(x - x0) + 1/2*f''(x0)*(x - x0)^2`. If you take the derivative of this function, you get `Q'(x) = f'(x0) - f''(x0)*(x - x0)`. The minimum is then simply the zero of this derivative. Again, doing some algebra, we get `x = x0 - f'(x0)/f''(x0)`. We use this formula to travel to the minimum of the approximation, then we take the quadratic approximation the function, take the derivative of the approximation, and find the next minimum using the formula.

	x := random
	until f'(x) <= EPSILON
		x := x - ALPHA*f'(x)/f''(x)

In this graphic, the blue curve is representing the quadratic approximation, and it ends at the approximated minima in each iteration.

![Newton's Method for Minima]({{ site.url }}/resources/images/optimization/newtons_method_for_minimization.gif){:.graphic-center}

Side Note on This Algorithm: it not only finds the minumum, it also finds maximum and saddle points, since all of these have a derivative of 0. Basically, it will converge to the nearest critical point depending on where you start. This is an example of the algorithm finding a maximum.

![Newton's Method for Maxima]({{ site.url }}/resources/images/optimization/newtons_method_for_maximization.gif){:.graphic-center}

What most people will do is tweak their initial problem to only include minima. This could be done, for example, by squaring the original function to make it more quadratic-ish.

## There's Still a Problem

Let's go back to the mountain example, say you find where the slope is level and you take off your blindfolded. Are you sure you're at the lowest spot on the mountain? You could happen to be on a spot on the mountain where the ground happens to be level before rising to another peak. You could come across a relatively low ground between two peaks, or at a saddle point where the ground levels off before sloping down again. You could be far from the lowest spot.

It's the same case with optimization algorithms. They can only find what are called "local minima", points near where they started that appear to be a low region, where the ground is level. Again, computers do not have the foresight to see if there is any other spots that are lower (for now, at least). This is where human analysis could come back into the picture. If a function that can be plotted on a graph, rather than finding a random point, the computer could ask for a human guess that is relatively near to the minimum, before it performs optimization. This may not be suitable for more complex functions, like Neural Networks. Maybe a local minimum would suffice, or the cost function could be developed in such a way so as to allow only one minimum. Often times, an optimized model shouldn't be too precice. Either way, optimization algorithms serve merely as a tool, an assistor, rather than an exact method, to find minima.

## Addendum

The 'education' tag is something new that I'm trying. I learn a lot of things that I think are interesting to share. So this is a way for me to do that in a formatted manner. Let me know on [Twitter](http://www.twitter.com/{{ site.twitter_username }}) what you think and if you'd like to see more.

Note: I will be editing this as I go on, namely taking parts out as I elaborate on them in other posts (or fixing typos).

---

Image Credits:

- Anshul Kharbana 2016 (using [Desmos Graphing Calculator](http://www.desmos.com) and [Gif Maker](http://www.gifmaker.cc))