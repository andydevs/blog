---
layout: post
title: How to Do Shadows Correctly
excerpt_separator: "<!--bruh-->"
date: 2021-01-10 19:15 -0500
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

![Virgin Color Shadow](/assets/images/how-to-do-shadows-correctly/virgin-color-shadow.png)

Makes sense for now, but what if the background changes?

![Virgin Color Shadow Ugly](/assets/images/how-to-do-shadows-correctly/virgin-color-shadow-ugly.png)

Now it looks ugly.

My immediate thought was either to find some CSS property to compute the color
based on the background. There was the `drop-shadow` filter, but that only works on
images. Other than that, all I could think of was that I was gonna have to do it
somehow in javascript. I would use javascript to find the position of the element,
get all of the elements that cover that position, get the exact color of the element 
in that spot that the shadow covers and apply that to the shadow. But it would still
look ugly in gradients. For that, I would have to calculate the gradient of the region
overed by the box shadow and then set the box shadow to have that gradient somehow.

Eventually, I just gave up.

Then I realized something: Bootstrap does it just fine. They have shadows over 
other shadows and everything. How does bootstrap do it? I decided to look into it. 
I opened up a bootstrap example site and checked out the CSS in the developer view 
to find out what kind of black magic their engineers have cooked up to make this
effect.

And, for better or for worse, I got the answer.

Just lower the opacity you idiot
-------------------------------------------------------------------------------

Set the shadow color to black and lower the opacity. That adds a bit of "black" 
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

![Alpha Chad Opacity Shadow](/assets/images/how-to-do-shadows-correctly/alpha-chad-opacity-shadow.png)

It even works on gradients!

![Alpha Chad Opacity Shadow Gradient](/assets/images/how-to-do-shadows-correctly/alpha-chad-opacity-shadow-gradient.png)

Surprisingly, I didn't think to do that. Maybe because it was too simple. In my 
mind, there needed to be a smart, but still simple, solution, because shadows 
are so new and fancy. 

And then the answer is to just lower the opacity.

This has happened to me so many times in my various projects. I do have a tendency
to overthink and overengineer things, so it's hard to wrap my head around the answer
being so stupidly, boringly simple. I might write about some of the more egregious 
times as they come by.

But yeah... that's how you do shadows correctly.

I made a [Code Pen](https://codepen.io/andydevs/pen/gOMgYeX?editors=1100)... In 
case you needed to see it for yourself or something.

I certainly needed one.