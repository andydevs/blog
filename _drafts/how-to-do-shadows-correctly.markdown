---
layout: post
title: How to Do Shadows Correctly
excerpt_separator: <!--bruh-->
---

This is a short one, a PSA if you will. Often the questions that perplex us 
have the simplest of answers. In these moments, I feel it is our mission, our 
_duty_, to inform the public so that others won't make the same mistake again. 

Or I just want to look less stupid. That's more likely

This is one of those moments, and it pertains to something so simple, something 
we take for granted: shadow effects. All the cool websites have them. But the 
way to do them was not as obvious to me to begin with.

<!--bruh-->

The Mistake
------------------------------------------------------------------------------

I was trying to make a button that floats with a little shadow to show that 
it's floating. So, I did the first thing that came to mind set the shadow color 
to a darker version of the background color.

![Virgin Color Shadow](/assets/images/how-to-do-shadows-correctly/virgin-color-shadow.png)

```css
.floating-button {
    /* Spacing */
    margin-right: 20pt;
    z-index: 1;
    
    /* Color */
    color: white;
    background-color: #333;
    
    /* Size and Shape */
    padding: 10pt 20pt;
    border: none;
    border-radius: 5pt;

    /* Shadow */
    box-shadow: 0px 0px 20px 0px rgba(90,90,90,1);
}
```

Makes sense for now, but what if the background changes?

![Virgin Color Shadow Ugly](/assets/images/how-to-do-shadows-correctly/virgin-color-shadow-ugly.png)

Now it looks ugly.

Now my immediate thought was either to find some CSS property to compute the
color based on the background. Other than that, all I could think of was that I 
was gonna have to do it somehow in javascript and I didn't want the headache. 
So I just gave up and avoided the problem...

I was afraid of shadows for a while, and a bit upset over it... I mean, Bootstrap
does it just fine. They have shadows over other shadows and everything...

Wait how does bootstrap do it?

I looked into it. That's when I realized that the answer was so simple, so
unbelievably simple, yet so elegant and pure.

Just lower the opacity you idiot
------------------------------------------------------------------------------

Set the background to black and lower the opacity. That adds a bit of "black" 
to the color directly below it, effectively darkening it.

```css
.floating-button {
    /* Spacing */
    margin-right: 20pt;
    z-index: 1;
    
    /* Color */
    color: white;
    background-color: #333;
    
    /* Size and Shape */
    padding: 10pt 20pt;
    border: none;
    border-radius: 5pt;

    /* Shadow */
    box-shadow: 0px 0px 20px 0px rgba(0,0,0,0.60);
}
```

![Alpha Chad Opacity Shadow](/assets/images/how-to-do-shadows-correctly/virgin-color-shadow-ugly.png)

So yeah... that's how you do shadows correctly.

I made a [Code Pen](https://codepen.io/andydevs/pen/gOMgYeX?editors=1100)... In 
case you needed to see it for yourself or something. I would say it's self 
explanitory but you know... I would need a code pen.