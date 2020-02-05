---
layout:   post
title:    "The Site Looks Different..."
keywords: andydevs blog webdesign
---

So, you may have noticed that the website looks different. I've been working on changing the site design for a while now (about a couple years). It wasn't that the old UI was ugly. It was just boring (I mean, it was the default jekyll UI and it's meant to be changed to something better looking). I decided to try my hand at styling a website. I also decided to put my css and javascript in a separate npm package, creating a style library that other people can use in their websites. Then, I'd port it over to my jekyll website. 

This is just an overview of the some of the new styling, particularly the more specific parts of it (the menu, cutouts, the slide buttons, etc). Not going to go too much in depth on the process of designing it. I will only touch on some of the challenges I faced and decsions that I made during designing this style.

Mostly because I forgot to document my work...

The new style is something I call "backwhite". Admittedly, the name isn't the best, but I'm keeping it for now (because everything now has that name). Basic rundown of what you're seeing: We have a menu panel off to the side of the main content. On mobile, this is hidden and switched to with a button. In this layout, the menu appears recessed into the background, behind the content (using a shadow), and is actually hidden behind the content. During switching to this menu on mobile, the content slides aside, revealing the menu in the back. Coloring follows a two-tone design. A dark "back" color colors the menu and other features, and one white color which colors the whitespace of the content panel. 

Hence "backwhite" (it's still a stupid name, but that's where it came from).

## Desktop Styling

The two panels of the website are made out of two divs, `<div class='bw-front'>` and `<div class='bw-back'>`, both existing on the root body. 

```html
<body>
    <div class="bw-back">
        <!-- Back menu content -->
    </div>

    <div class="bw-front">
        <!-- Main content -->
    </div>
</body>
```

We'll start with `bw-back`. You notice the menu is completely separate from the flow of the page. It stays in place. This is achieved by `position: fixed`. This also means we set the top, bottom, and left edges to `0%`, meaning they are locked to the edges of the screen.

```scss
.bw-back {
    position: fixed;
    top: 0%;
    left: 0%;
    bottom: 0%;
}
```

Since the menu is off to the side, I thought I'd set a variable `$desktop-menu-size`, which is the width of the menu. This also controls the left end of the `.bw-front` div, so everything is consistent and can change with one variable.

```scss
$desktop-menu-size: 300px;

.bw-back {
    position: fixed;
    top: 0%;
    left: 0%;
    bottom: 0%;
    
    width: $desktop-menu-size;
}
```

Yes I am using SCSS.

The other thing you notice in the css is the `z-index`. Since the menu is behind everything, We manually set the depth ordering of the div so that it's actually behind the other content. We set this to -1.

```scss
$desktop-menu-size: 300px;

.bw-back {
    position: fixed;
    top: 0%;
    left: 0%;
    bottom: 0%;

    width: $desktop-menu-size;

    z-index: -1;
}
```

The front panel has absolute positioning with top and right set to 0%. Left is set to the width of the menu, so it appears right beside the menu. We also set the `min-height` to 100% This ensures the div fills its entire section of the page, but can overflow downwards if need be. (even when the content doesn't fill the entire page).

```scss
$desktop-menu-size: 300px;

.bw-front {
    position: absolute;
    top: 0%;
    right: 0%;
    min-height: 100%;

    // Offset by menu size
    left: $desktop-menu-size;
}
```

We'll set the z-index to 0 so that it's moved to the front.

```scss
$desktop-menu-size: 300px;

.bw-front {
    position: absolute;
    top: 0%;
    right: 0%;

    // Offset by menu size
    left: $desktop-menu-size;

    // Set z-index to 0
    z-index: 0;
}
```

Since I want the page to flow vertically only, I set `overflow-x` to be hidden. We'll control horizontal scrolling in specific sections of the page (tables, code, etc.).

```scss
$desktop-menu-size: 300px;

.bw-front {
    position: absolute;
    top: 0%;
    right: 0%;

    // Offset by menu size
    left: $desktop-menu-size;

    // Set z-index to 0
    z-index: 0;

    // No scrolling in x direction
    overflow-x: hidden;
}
```

The final thing to do for these is to make the shadow effect. This is done with `box-shadow`.

```scss
$desktop-menu-size: 300px;

.bw-front {
    position: absolute;
    top: 0%;
    right: 0%;

    // Offset by menu size
    left: $desktop-menu-size;

    // Set z-index to 0
    z-index: 0;

    // Shadow effect
    box-shadow: -2pt 0pt 8pt darken($back-color, 33%);
}
```

The last thing I want to cover here is the bootstrap-like grid system.

```html
...
<div class='bw-row'>
    <div class='bw-col-4'>
        <!-- Content -->
    </div>
    <div class='bw-col-4'>
        <!-- Content -->
    </div>
    <div class='bw-col-4'>
        <!-- Content -->
    </div>
</div>
...
```
A grid row is created by a `bw-row` div. Within the `bw-row` div are `bw-col-[x]` divs where `x` can be from 1 to 12. `bw-row`'s have 12 columns that the `bw-col` divs can span across.

This is some clever little scss code that takes advantage of css's grid system and scss for loops.

To create a grid, you set the `display` property to `grid`.

```scss
.bw-row {
    display: grid;
}
```

A `bw-row` is made up of 1 row that is 12 columns wide. `grid-template-rows` determines the number of rows in the div, and `grid-template-columns` determines the number of columns. Each column is `1fr`, which means 1 equally-spaced width.

```scss
.bw-row {
    display: grid;
    grid-template-rows: 1fr;
    grid-template-columns: repeat(12, 1fr);
}
```

Next is `column-gap`. This is the space between columns. At this point, we come across `$spacing-unit`. This is a global variable that controls the overall spacing accross the entire website. I set it to `8pt`, but it can change (another part of customization).

- Mobile Styling
    - Change width and height of back and front
    - Create vertical grids
    - `<meta name="viewport" content="width=device-width,initial-scale=1">`
    - Make floating button appear
    - Handle sliding using jQuery
        - Sliding UI causes window to expand. Can't seem to hide it effectively
        - The front will just collapse using margin-left. That's what we're gonna do

- Cutouts
    - Inspired by back panel.
    - The idea is parts of the front are cut out from the back pane
    - I had a shadow on the button, meant for the front. But the shadow clashes with the cutouts.
        - Now... I could get rid of the cutouts, but I feel like the cutouts really add to the design while still running the same theme of the two layers.
        - Compromise: two fixed caret buttons at top instead of floating button
            - Got rid of the floating button entirely...
                - It was kind of tacky...
            - In place, we have two buttons at the top that stay in a place where the shadows can't clash.
                - You do have to move up the page to access the menu.
                - I got an idea for replacing the button which I'll talk about it later.

- Styling Forms
    - Block forms
        - Form row
            - Using flexbox to automatically adjust width of input groups
        - Form input group
            - Couples label with input
    - Forms not aligning properly on mobile
        - The input fields were too big on mobile.
        - `flex: 1` sets the flex-basis, which is the required length of the element. What we need is `flex: 1 auto`. This tells the element to grow to be 1 fractional length, but shrink as needed.

- Porting design over to my website
    - Adding the sass/js
        - Just copied over the files
        - Javascript file needed to be in /assets folder
            - Just yanked that from the other library
    - Making new layouts
        - default.html
        - post.html
        - index.html
    - Includes
        - head.html
        - back.html
    - Updating syntax highlighting
        - Wanted every part to be in relation to the back color, so that the style is customizable, but still fits with the two tone design.
    - Creating the theme gem
    
- Future
    - Getting an actual slide animation working
    - React components.
    - Touch gestures!