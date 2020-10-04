---
layout: post
title: How to Do Shadows Correctly
---

This is a short one. Often the questions that perplex us have the simplest of
answers.

## Mistake

I was trying to make a button that floats at the bottom right for easy access

I set the shadow color to a darker version of the background color

![Virgin Color Shadow]()

```css
.floating-button {
    /* Positioning */
    position: fixed;
    bottom: 50px;
    right: 50px;
    z-index: 1;

    /* Shape */
    width: 50px;
    height: 50px;

    /* Shadow */
    box-shadow: 0px 2px 20px 0px rgba(153,153,153,1);
}
```

Makes sense for now, but what if the background changes?

![Virgin Color Shadow Ugly]()

Now it looks ugly.

For a while I looked for a way to compute the color based on the background

I looked at drop shadows and doing it in JavaScript and eventually I gave up.

I was afraid of shadows for a while, and a bit upset over it... I mean, Bootstrap
does it just fine. They have shadows over other shadows and everything...

Wait how does bootstrap do it?

I looked into it. That's when I realized that the answer was so simple

## Just lower the opacity you idiot

Set the background to black and lower the opacity. That adds a bit of "black" 
to the color directly below it, effectively darkening it.

```css
.floating-button {
    /* Positioning */
    position: fixed;
    bottom: 50px;
    right: 50px;
    z-index: 1;

    /* Shape */
    width: 50px;
    height: 50px;

    /* Shadow */
    box-shadow: 0px 2px 20px 0px rgba(0,0,0,0.3);
}
```

![Alpha Chad Opacity Shadow]()

So yeah... that's how you do shadows correctly.