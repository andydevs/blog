---
layout:     post
title:      Approximation and Taylor Expansions
date:       2016-10-14
categories: education
---

I'm going to show you a trick that you can use for guessing hard calculations without a calculator.

Because, as we all know, forgetting a calculator on a test (especially ones meant for calculators), is a death sentence.

Say one of your questions is "compute the square root of 4.0437". Unless you're [Scott Flansburg](https://youtu.be/NgIICQvhqMc), you probably wouldn't know the square root of 4.0437 off the top of your head. So now you would either skip that question, or keep making guesses of what the result is going to be.

But you do know the square root of 4...

You're trying to find the value of `f(x) = sqrt(x)` where `x == 4.0437`. At `x == 4`, the value of `f` is easy to figure out (it's just 2). Yes that's not the answer, but here's the thing. `4` not that far off from `4.0437`. It's too far for us to just substitute 4 (depending on the precision your test demands), but it is far enough for us to do something else...

Imagine the graph of `f(x)` over a wide range (like from 0 to 8). Now find the point `4`, and imagine zooming into the function near that point. As you look at a smaller and smaller range of `f(x)`, you notice the graph becomes more and more linear, until it basically becomes a straight line, a linear function! This isn't a trick. (almost) Every function has this property. That's basically the foundation of calculus.

So what's the slope of this line you found? It's just derivative of `sqrt(x)`, which is `1/(2*sqrt(x))`. At `x == 4` (where you're looking), this just becomes `1/4`.

So you know the value of `f(4)`, and you know the value of `f'(4)`. Now it's just a matter of some simple addition and multiplication.

	L(4.0437) = 2 + (1/4) * (0.0437) << the distance from your point to the target point
			  = 2 + 0.25 * 0.0437
			  = 2 + 0.010925

	L(4.0437) = 2.010925

Checking our handy-dandy calculator when we get home from our exam (that was sitting on ), we see that the actual value of `sqrt(4.0437)` is `2.010895`, which is surprisingly close to what we had.

This is called Linear Approximation. The general form being:

	L(x) = f(x0) + f'(x0)*(x - x0)
