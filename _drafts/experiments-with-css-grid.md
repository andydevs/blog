---
title: "Experiments in CSS Grid"
layout: post
keywords: andydevs blog css-grid css grid gradient
---

I watched a video lecture from Coding Tech about CSS Grid, and I was intrigued.

So, I'm creating a website using CSS grid. This website in particular will be 
a homepage for a "blog". I might actually add pages later, but I'm just making 
the homepage for now.

I "drew" a layout (using google drawings)

_Desktop_

![Desktop](./journal-assets/css-grid/desktop.jpg)

_Mobile_

![Mobile](./journal-assets/css-grid/mobile.jpg)

A few notes on this design, the colors are actually linear gradients. Makes things 
look nice. The "Icon Grid" and "Icon Row" sections will contain icons for accessing 
other parts of the website.

I'll be using scss and fontawesome for icons!

## Setting up the Project

- Created new npm package
- Installed grunt and scss dependencies
    - Realized that I didn't use any javascript so didn't install babel
    - Talk about grunt-contrib-connect and grunt-contrib-watch
    - Also talk about grunt-contrib-copy and copying html file
- Created a TO-DO list

## Make content

- Explain the naming of the divs
- Doing main layout first, and then doing menu

```html
<div class="layout">
    <div class="menu">
        <p>Menu Content</p>
    </div>

    <div class="post-snippet main">
        <h1 class="title">Example Header</h1>
        <p class="snippet">Lorem ipsum dolor, sit amet consectetur adipisicing elit. 
            Voluptate adipisci laborum tempore quam recusandae harum 
            vero optio nemo, dolorem quaerat? Nemo necessitatibus 
            vero eligendi eius, minima unde eos voluptatibus tenetur... Lorem ipsum 
            dolor sit amet consectetur adipisicing elit. Rerum doloremque quibusdam 
            molestias? Alias, labore impedit libero ea dolore neque provident molestiae 
            deleniti autem nulla veniam architecto sit exercitationem perferendis praesentium? 
            Lorem ipsum dolor sit amet consectetur adipisicing elit. Repudiandae ab nihil eaque...</p>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet second-1">
        <h2 class="title">Example Header</h2>
        <p class="snippet">Lorem ipsum dolor, sit amet consectetur adipisicing elit. 
            Voluptate adipisci laborum tempore quam recusandae harum 
            vero optio nemo, dolorem quaerat? Nemo necessitatibus 
            vero eligendi eius, minima unde eos voluptatibus tenetur...</p>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet second-2">
        <h2 class="title">Example Header</h2>
        <p class="snippet">Lorem ipsum dolor, sit amet consectetur adipisicing elit. 
            Voluptate adipisci laborum tempore quam recusandae harum 
            vero optio nemo, dolorem quaerat? Nemo necessitatibus 
            vero eligendi eius, minima unde eos voluptatibus tenetur...</p>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet second-3">
        <h2 class="title">Example Header</h2>
        <p class="snippet">Lorem ipsum dolor, sit amet consectetur adipisicing elit. 
            Voluptate adipisci laborum tempore quam recusandae harum 
            vero optio nemo, dolorem quaerat? Nemo necessitatibus 
            vero eligendi eius, minima unde eos voluptatibus tenetur...</p>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-1">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-2">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-3">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-4">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-5">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-6">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-7">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-8">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-9">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-10">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-11">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>

    <div class="post-snippet third-12">
        <h3 class="title">Example Header</h3>
        <p class="buttons">
            <a href="#" class="button read-button">Read</a>
        </p>
    </div>
</div>
```

- Explain why you added extra third divs
- Add a screenshot of this

## First grid

- Summarize position attributes
- Explain grid sections
- Explain css stuff at the bottom
- Explain 1fr

```scss
$second-count: 3;
$third-count: 12;

.layout {
    // Fill entire screen
    position: absolute;
    top: 0%;
    left: 0%;
    right: 0%;
    min-height: 100%;

    // CSS Grid
    display: grid;
    grid-template-rows: repeat(5, 1fr);
    grid-template-columns: repeat(8, 1fr);

    // Grid areas
    grid-template-areas:
        "main     main     main     second-1 second-1 second-1 second-1 menu     menu"
        "main     main     main     second-1 second-1 second-1 second-1 menu     menu"
        "main     main     main     second-2 second-2 third-1  third-2  third-3  third-4"
        "second-3 second-3 second-3 second-2 second-2 third-5  third-6  third-7  third-8"
        "second-3 second-3 second-3 second-2 second-2 third-9  third-10 third-11 third-12";
}

.menu {
    grid-area: menu;
}

.main {
    grid-area: main;
}

@for $i from 1 through $second-count {
    .second-#{$i} {
        grid-area: second-#{$i};
    }
}

@for $i from 1 through $third-count {
    .third-#{$i} {
        grid-area: third-#{$i};
    }
}
```

- Add Screenshot

## Mobile grid

All we need to do is change the grid layout
in the `.layout` class.

```scss
$responsive-mobile-size: 830px !default;

@mixin on-mobile {
    @media only screen and (max-width: $responsive-mobile-size) {
        @content;
    }
}

.layout {
    ...

    @include on-mobile {
        // CSS Grid
        display: grid;
        grid-template-rows: auto 1.5fr repeat(3, 1fr) repeat(6, auto);
        grid-template-columns: repeat(2, 1fr);

        // Grid areas
        grid-template-areas: 
            "menu     menu"
            "main     main"
            "main     main"
            "second-1 second-1"
            "second-2 second-2"
            "second-3 second-3"
            "third-1  third-2"
            "third-3  third-4"
            "third-5  third-6"
            "third-7  third-8"
            "third-9  third-10"
            "third-11 third-12";
    }
}
```

- Explain auto
- Explain 1.5fr
- Screenshot!

## Adding Fonts

- Explain why you're putting it in the layout

```scss
$font-family: "Calibri Light", sans-serif !default;
$font-size: 14pt !default;

.layout {
    // CSS Grid magic...

    // Font styling
    font-family: $font-family;
    font-size: $font-size;
}
```

## Styling the post snippets

Now I want the post snippet to have the header right at top, the button 
group right at the bottom, and the remaining space to be filled with 
the content. I was originally thinking that I would use flexbox but...

CSS Grid can take care of this as well! Here's what that looks like

```scss
$spacing-unit: 12pt !default;

.post-snippet {
    // Spacing
    padding: $spacing-unit;

    // Layout
    display: grid;
    grid-template-rows: auto 1fr auto;
    grid-template-columns: 1fr;
    grid-template-areas: "title" "snippet" "buttons";

    // Post title
    .title {
        grid-area: title;
    }

    // Post snippet
    .snippet {
        grid-area: snippet;
    }

    // Button set
    .buttons {
        grid-area: buttons;
        text-align: right;
    }
}
```

- Screenshot!

## Colors!

- Explain color lists
- Explain gradients
- Explain mixins

```scss
// Control background colors for menu and 
// main, second and third post snippets
$menu-background: #444 !default;
$main-background: gold !default;
$second-backgrounds: 
    tomato dodgerblue mediumseagreen !default;
$third-backgrounds: 
    lightcoral sienna indianred orange 
    pink lavender violet turquoise 
    teal slateblue darkolivegreen slategray !default;

@mixin colored-snippet($color) {
    // Background color
    background-image: linear-gradient(45deg, lighten($color, 8%), $color);

    // Title color
    .title {
        color: darken($color: $color, $amount: 25%);
    }

    // Button color (and hover color)
    .button {
        background-color: darken($color: $color, $amount: 20%);
        color: white;
        &:hover {
            background-color: darken($color: $color, $amount: 30%);
        }
    }
}

...

// Main post snippet
.main {
    grid-area: main;
    @include colored-snippet($main-background);
}

// Loop makes second post snippets
@for $i from 1 through $second-count {
    .second-#{$i} {
        grid-area: second-#{$i};
        @include colored-snippet(nth($second-backgrounds, $i));
    }
}

// Loop makes third post snippets
@for $i from 1 through $third-count {
    .third-#{$i} {
        grid-area: third-#{$i};
        @include colored-snippet(nth($third-backgrounds, $i));
    }
}
```

- Screenshot!

## Menu

- Install fontawesome
- Extra grunt copy task
- Configuring fontawesome in css

### Color menu

```scss
.menu {
    grid-area: menu;

    // Spacing
    padding: $spacing-unit;

    // Coloring!
    background-image: linear-gradient(45deg, lighten($menu-background, 5%), $menu-background);
    color: white;
}
```

### Make another grid

```scss
.menu {
    ...

    // Create grid layout
    display: grid;
    grid-template-rows: repeat(3, 1fr);
    grid-template-columns: repeat(3, 1fr);
    grid-template-areas: 
        "title  title  icon-1"
        "title  title  icon-2"
        "icon-3 icon-4 icon-5";

    .title {
        grid-area: title;
    }

    @for $i from 1 through 5 {
        .icon-#{i} {
            grid-area: icon-#{i};
        }
    }
}
```

### Add Content

```html
<div class="menu">
    <h1 class='title'>
        CSS Grid Example Homepage
    </h1>
    <div class='icon-1'>
        <a href="#" class="icon">
            <span class="fas fa-envelope"></span>
        </a>
    </div>
    <div class='icon-2'>
        <a href="#" class="icon">
            <span class="fab fa-facebook"></span>
        </a>
    </div>
    <div class='icon-3'>
        <a href="#" class="icon">
            <span class="fab fa-twitter"></span>
        </a>
    </div>
    <div class='icon-4'>
        <a href="#" class="icon">
            <span class="fab fa-instagram"></span>
        </a>
    </div>
    <div class='icon-5'>
        <a href="#" class="icon">
            <span class="fab fa-pinterest"></span>
        </a>
    </div>
</div>
```

- Screenshot

### Centering the elements

- First off how do we center them...
- NAHFAM&trade;
- Use CSS Grid

```scss
.menu {
    ...
    place-items: center;
    ...
}
```

### Styling icons

```scss
.icon {
    color: inherit;
    font-size: 24pt;
}
```

### Mobile menu grid

```scss
.menu {
    ...

    // Mobile styling
    @include on-mobile {
        display: grid;
        grid-template-rows: repeat(2, auto);
        grid-template-columns: repeat(5, 1fr);
        place-items: center;
        grid-template-areas: 
            "title  title  title  title  title"
            "icon-1 icon-2 icon-3 icon-4 icon-5";
    }

    ...
}
```

## Changing mobile layout of post snippets

- Center title
- Explain `justify-items: stretch;`

```scss
.post-snippet {

    ...

    // Mobile
    @include on-mobile {
        justify-items: stretch;
    }

    ...

    .title {
        ...

        @include on-mobile {
            text-align: center;
        }
    }
    ...
}
```

- Screenshot

- Make button fill entire width
- NAHFAM 2: Revenge of the YEET

```scss
.post-snippet {
    ...

    .buttons {
        display: block;

        @include on-mobile {
            display: grid;
            grid-template-rows: 1fr;
            grid-template-columns: 1fr;
            justify-items: stretch;

            // Align text
            text-align: center;
        }
    }
}
```

- Screenshot

## Setting Tablet Layout

```scss
$responsive-tablet-size: 1200px !default;

@mixin on-tablet {
    @media only screen and (max-width: $responsive-tablet-size) {
        @content;
    }
}
```

- Explain why on-tablet needs to come before on-mobile

Main layout

```scss
.layout {
    ...

    // Grid areas on tablet
    @include on-tablet {
        // CSS Grid
        display: grid;
        grid-template-rows: repeat(8, 1fr);
        grid-template-columns: repeat(6, 1fr);

        // Grid areas
        grid-template-areas: 
            "menu     menu     menu     menu     menu     menu"
            "main     main     main     main     second-1 second-1"
            "main     main     main     main     second-1 second-1"
            "second-2 second-2 second-2 third-1  second-1 second-1"
            "second-2 second-2 second-2 third-1  third-2  third-3"
            "second-3 second-3 second-3 third-4  third-5  third-6"
            "second-3 second-3 second-3 third-7  third-8  third-9"
            "second-3 second-3 second-3 third-10 third-11 third-12";
    }

    // Mobile styling comes after!
    ...
}

...

.menu {
    ...

    // Tablet styling
    @include on-tablet {
        display: grid;
        grid-template-rows: repeat(2, 1fr);
        grid-template-columns: repeat(4, 1fr);
        place-items: center;
        grid-template-areas: 
            "title  title  title  icon-1"
            "icon-2 icon-3 icon-4 icon-5";
    }

    ...
}
```

- Screenshot

## Conclusion

- CSS Grid was insanely easy
- I'm gonna use this for everything
- Check out project on github
- Check out website