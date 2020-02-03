---
layout:   post
title:    "The Site Looks Different..."
keywords: andydevs blog webdesign
---

So, you may have noticed that the website looks different. I've been working on changing the site design for a while now (about a couple years). It wasn't that the old UI was ugly. It was just boring (it was the default jekyll UI). So, I decided to create a new UI design. I decided to create it as a npm package (that way I and other people can use it on other websites), then port it over to my website (and creating a jekyll theme to boot). Note: this is mostly of an overview of the new styling which included some of the process of creating it (problems, decisions, etc.). Not going to go too much in depth on the process of designing it. I will only touch on some of the challenges I faced and decsions that I made during designing this style.

The new style is something I call "backwhite". Admittedly, the name isn't the best, but I'm keeping it for now (because everything now has that name). Basic rundown of what you're seeing: The layout is a two-panel design. We have a menu panel off to the side of the content panel, that, on mobile, is switched to with a button. In this layout, the menu appears recessed into the background, behind the content (using a shadow), and is actually hidden behind the content. During switching to this menu, the content slides aside, revealing the menu in the back. Coloring follows a two-tone design, with one dark "back" color coloring the menu, and one white color which colors the content panel. Hence "backwhite" (it's still a stupid name, but that's where it came from).

## Desktop Styling

So, the first thing I needed to do was create the two panels. I created two divs, `<div class='bw-front'>` and `<div class='bw-back'>`, both existing on the root body. We'll start with `bw-back`. I wanted to keep the menu completely separate from the flow of the page. So, obviously, we needed `position: fixed`. This also means we set the top, bottom, and left edges to `0%`, meaning they are locked to the edges of the screen.

```scss
.bw-back {
    position: fixed;
    top: 0%;
    left: 0%;
    bottom: 0%;
}
```

Since the menu is off to the side, I thought I'd set a variable `$desktop-menu-size`, which is the width of the menu. This also controls the position of the `.bw-front` div, so everything is consistent and can change with one variable.

```scss
.bw-back {
    position: fixed;
    top: 0%;
    left: 0%;
    bottom: 0%;
    
    width: $desktop-menu-size;
}
```

The other thing we need to set is the `z-index`. We need to tell the div that it's actually behind the `bw-front` div that we're making. We set this to `-1` to keep it behind everything else.

```scss
.bw-back {
    position: fixed;
    top: 0%;
    left: 0%;
    bottom: 0%;

    width: $desktop-menu-size;

    z-index: -1;
}
```

For the front, I first decided to use fixed positioning and give the div it's own scroll bar. This was achieved with `overflow-y: scroll`.

```scss
.bw-front {
    position: fixed;
    top: 0%;
    right: 0%;

    // Offset by menu size
    left: $desktop-menu-size;
}
```

However, this caused a few problems. For one, the scrolling on mobile doesn't have momentum. This can be fixed with `-webkit-overflow-scrolling: touch`. The other problem was that the UI doesn't change on mobile when you scroll. The mobile UIs only follow the main scroll wheel, that scrolls the entire page. So, we have to set the position to absolute.

```scss
.bw-front {
    position: absolute;
    top: 0%;
    right: 0%;

    // Offset by menu size
    left: $desktop-menu-size;
}
```

We'll set the z-index to 0 so that it's moved to the front.

```scss
.bw-front {
    position: absolute;
    top: 0%;
    right: 0%;

    // Offset by menu size
    left: $desktop-menu-size;

    z-index: 0;
}
```

The final thing to do for these is to make the shadow effect. This is done with box shadow.

```scss
.bw-front {
    position: absolute;
    top: 0%;
    right: 0%;

    // Offset by menu size
    left: $desktop-menu-size;

    z-index: 0;

    box-shadow: -2pt 0pt 8pt darken($back-color, 33%);
}
```

- Desktop Styling
    - Grids

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