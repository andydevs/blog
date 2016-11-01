---
layout:     post
title:      Approximation and Taylor Expansions
date:       2016-10-14
categories: education
---

I'm going to show you a trick that you can use for guessing hard calculations without a calculator, because, as we all know, forgetting a calculator on a test (especially ones meant for calculators), is a death sentence. Say one of your questions is "compute the square root of 4.0137". Unless you're [Scott Flansburg](https://youtu.be/NgIICQvhqMc), you probably wouldn't know the square root of 4.0137 off the top of your head. So now you would either skip that question, or keep making guesses of what the result is going to be.

But you do know the square root of 4...

You're trying to find the value of `f(x) = sqrt(x)` where `x == 4.0137`. Think of a function as a hill, with your position being `x` and your height being `f(x)`. If your standing at `x == 4`, the height is easy to calculate (it's just 2), and the distance between `x == 4` and `x == 4.0137` isn't all that much. So, what if you dropped a wooden plank on the ground where you're standing, and you use the plank to guess the height of the point directly in front of you? The height of the point on the plank is going to be a linear relationship with the distance you travel, but it's going to be pretty close to the height of the plank at that point. After all, it's not that far from where you're standing. 

So all you got to do is multiply the slope of the plank and the distance to the point in question and add it to your current height. But what's the slope? It's just derivative of `sqrt(x)`, which is `1/(2*sqrt(x))`. At `x == 4` (where you're standing), this just becomes `1/4`.

So you know the value of `f(4)`, and you know the value of `f'(4)`. Now it's just a matter of some simple addition and multiplication.

	2 + (1/4) * (0.0137) <-- the distance from your point to the target point
	2 + 0.25 * 0.0137
	2 + 0.003425

	2.003425

Checking our handy-dandy calculator when we get home from our exam, we see that the actual value of `sqrt(4.0137)` is `2.003422`, which is surprisingly close to what we had.

This is called Linear Approximation. The general form being:

	L(x) = f(x0) + f'(x0)*(x - x0)
