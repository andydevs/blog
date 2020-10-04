---
layout: post
title: How to Do Shadows Correctly
---

This is a short one

## Mistake

I was trying to make a button that floats at the bottom right for easy access

I set the shadow color to a darker version of the background color

```
.floating-button {
    position: fixed;
    bottom: 50px;
    right: 50px;
    box-shadow: ...
}
```

Makes sense but what if the background changes

For a while I looked for a way to compute the color based on the background

I looked at drop shadows and doing it in JavaScript and eventually I gave up.

But then the answer was so simple

## Just lower the opacity you idiot

Set the background to black and lower the opacity. That adds a bit of "black" 
to the color directly below it, effectively darkening it.

```
.floating-button {
    position: fixed;
    bottom: 50px;
    right: 50px;
    box-shadow: ...
}
```