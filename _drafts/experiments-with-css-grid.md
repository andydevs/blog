---
title: "Experiments in CSS Grid"
layout: post
keywords: andydevs blog css-grid css grid gradient
---

A while back, I watched a [video lecture](https://youtu.be/7kVeCqQCxlk) from 
Coding Tech about CSS Grid. The lecturer was pretty enthusiastic about this
new feature, and he showed how he redesigned his entire blog using CSS Grid.
The code was short, concise, and elegant.

Needless to say, I was intrigued. I wanted to try it myself.

So, off the tail of another css project, I'm jumping right back in and making a 
website using CSS grid. This website in particular will be a homepage for a "blog".

It's not a real website, it's just a mockup.

I "drew" this layout (using google drawings)

_Desktop_

![Desktop](/assets/images/experiments-with-css-grid/desktop.jpg)

_Mobile_

![Mobile](/assets/images/experiments-with-css-grid/mobile.jpg)

A few notes on this design: the colors are actually linear gradients, and the 
"Icon Grid" and "Icon Row" sections will contain icons for things like mail
and social media.

## Setting up the Project

So I started up a new npm project. I used `grunt` as a task runner, as I was
going to be building `scss` code, and copying files over in my build process.

So I installed `grunt`, `grunt-cli`, `grunt-sass`, and `node-sass`.

I realized down the road that I didn't need any javascript for this project.
This was pure css. So no `grunt-babel` or any of that stuff.

I designated `_public` to be the directory where my files are stored. I 
underscored it so that it appears at the top. I realize after the fact
that it would've been beeter if I kept my source files on top. I'll try
that in my next web design project.

I decided to have a folder for my html files and have grunt copy them over
to the public directory using `grunt-contrib-copy`... I felt like the 
`_public` dir should be for build artifacts and I shouldn't have to go 
into it to change source files.

Plus, since I'm using `grunt-contrib-watch`, I can have it do something
when the html changes.

Speaking of which, `grunt-contrib-watch` will watch my source directories for
changes and run build tasks accordingly, so I don't have to keep doing that.
I can also add a special script into my html that will reload the page when 
grunt rebuilds the source files.

I did this in my last project and I liked that workflow. What I didn't know was
that there was also `grunt-contrib-connect`, which will set up a little server
that you can view the code from. This plugin will also automatically inject the
livereload script when serving html pages and automatically open the browser when
it starts. It made the development experience so much easier and enjoyable.

So yeah, I was pretty happy about that.

With my installs done, I setup my grunt file.

```js
const sass = require('node-sass')
const siteDirectory = '_public/'

/**
 * Configure grunt
 * 
 * @param grunt grunt instance
 */
module.exports = function configGrunt(grunt) {
    // Configure grunt
    grunt.initConfig({
        sass: {
            options: {
                implementation: sass,
                sourceMap: true
            },
            public: {
                files: [{
                    expand: true,
                    cwd: 'scss',
                    src: ['main.scss'],
                    dest: siteDirectory,
                    ext: '.css'
                }]
            }
        },
        copy: {
            html: {
                files: [{
                    expand: true,
                    cwd: 'html',
                    src: '**/*.html',
                    dest: siteDirectory
                }]
            }
        },
        watch: {
            options: {
                livereload: true
            },
            scss: {
                files: ['scss/**/*.scss'],
                tasks: ['sass']
            },
            html: {
                files: ['html/**/*.html'],
                tasks: ['copy:html']
            }
        },
        connect: {
            server: {
                options: {
                    hostname: 'localhost',
                    base: siteDirectory,
                    livereload: true,
                    open: true
                }
            }
        }
    })

    // Load tasks
    grunt.loadNpmTasks('grunt-sass')
    grunt.loadNpmTasks('grunt-contrib-watch')
    grunt.loadNpmTasks('grunt-contrib-connect')
    grunt.loadNpmTasks('grunt-contrib-copy')

    // Register tasks
    grunt.registerTask('build', ['sass', 'copy'])
    grunt.registerTask('devserver', ['build', 'connect', 'watch'])
    grunt.registerTask('default', ['build'])
}
```

I set up two tasks: `build` (the default task) will just build 
the project, compiling scss and copying html, and `devserver` 
will set up the `grunt-contrib-connect` server and 
`grunt-contrib-watch`.

To keep me on track (mostly to prevent me from spending long hours just
endlessly tweaking the project to satiate my perfectionism) I made a simple
To-Do list and put it in a `TODO.md`. A bit low-tech, but found I like it 
better this way.

## Adding Dummy Content

The first thing I did was add the HTML content in. I'm adding the content in first and then styling it, as you would.

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

    <footer class="footer">
        <div>
            <p>
                Lorem ipsum dolor sit amet consectetur adipisicing elit. 
                Atque ratione officia minima esse, enim ducimus adipisci 
                voluptates non iure iste commodi eius, porro recusandae. 
                Debitis libero sapiente odio placeat atque?
            </p>
            <center>
                Copyright &copy; Anshul Kharbanda (andydevs) 2020
            </center>
        </div>
    </footer>
</div>
```

The basic gist is that we have all of our content under one layout div. This single div will control the placement of all of our components. In it, we have our menu. I've kept the menu blank for now, as I'll be working on it a bit down the road (using nested grid). Following the menu are the post snippets. I grouped the snippets into `main`, `second` and `third` snippets. In the hypothetical blog I would be making, the `main` snippet would be a featured post of the day. The `second` snippets would be three other highlighted posts, and the `third` snippets would be eight less important posts (possibly the posts from last week or something)

I noticed I forgot to add the footer in my layout so I added it in after the fact.

Here's what that looks like

![Dummy Content](/assets/images/experiments-with-css-grid/dummy-content.jpg)

## First grid

So, first, I set up the `layout` div to take up the entire page, but be able to scroll downward to accomodate for content.

```scss
.layout {
    // Fill entire screen
    position: absolute;
    top: 0%;
    left: 0%;
    right: 0%;
    min-height: 100%;
    
    ...
}
```

To make a grid we use `display: grid`, then define the number of rows and columns in the grid, using
`grid-template-rows` and `grid-template-columns`.

```scss
.layout {
    ...

    // CSS Grid
    display: grid;
    grid-template-rows: repeat(5, 1fr);
    grid-template-columns: repeat(8, 1fr);
}
```

The `1fr` translates to "1 fraction". `repeat(5, 1fr)` will repeat that five times. This part of the code tells CSS to divide the vertical 
free space into five equally spaced rows. Likewise the part containing `repeat(8, 1fr)` will divide the horizontal free space into eight 
equally spaced columns. The result is a 5x8 grid of equally sized cells that we can play around in.

Now the real magic happens. Using `grid-template-areas`, we can assign cells on this grid into named areas. 

```scss
.layout {
    ...

    // Grid areas
    grid-template-areas:
        "main     main     main     second-1 second-1 second-1 second-1 menu     menu"
        "main     main     main     second-1 second-1 second-1 second-1 menu     menu"
        "main     main     main     second-2 second-2 third-1  third-2  third-3  third-4"
        "second-3 second-3 second-3 second-2 second-2 third-5  third-6  third-7  third-8"
        "second-3 second-3 second-3 second-2 second-2 footer   footer   footer   footer";
}
```

Then, in our contained elements, we set `grid-area` to the named area we want the element to be in, and the element will automatically fill that area!

```scss
.menu {
    grid-area: menu;
}

.main {
    grid-area: main;
}

.second-1 {
    grid-area: second-1;
}

.second-2 {
    grid-area: second-2;
}

.second-3 {
    grid-area: second-3;
}

.third-1 {
    grid-area: third-1;
}

.third-2 {
    grid-area: third-2;
}

...

.footer {
    grid-area: footer;
}
```

![First Grid](/assets/images/experiments-with-css-grid/first-grid.jpg)

SCSS makes this code more concise using variables and for loops

```scss
$second-count: 3;
$third-count: 12;

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

.footer {
    grid-area: footer;
}
```

Crazy, right? Well...

## Mobile grid

First, I created an scss mixin for detecting mobile screens.

```scss
$responsive-mobile-size: 830px !default;

@mixin on-mobile {
    @media only screen and (max-width: $responsive-mobile-size) {
        @content;
    }
}
```

Then, all we need to do is change `grid-template-areas` in the `.layout` class when we detect a mobile screen.

```scss
.layout {
    ...

    @include on-mobile {
        // CSS Grid
        display: grid;
        grid-template-rows: auto 1.5fr repeat(3, 1fr) repeat(5, auto);
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
            "footer   footer";
    }
}
```

![Mobile Grid 1](/assets/images/experiments-with-css-grid/mobile-grid-1.jpg)

![Mobile Grid 2](/assets/images/experiments-with-css-grid/mobile-grid-2.jpg)

Yeah, that's it! That's all ya gotta do. You can arrange these blocks
anywhere, and the divs will follow!

A few things to note here. The `auto` means scale the row to fit the content. 
We only want the menu to be as big as it needs to be, so `auto` takes care 
of that.

The other thing is that `1.5fr`. I wanted the main post snippet to be about 
50% taller than the second post snippets, so setting that row to `1.5fr` does
that for me

## Adding Fonts

Calibri Light, that's my go-to font. I'm putting the font settings in the
`.layout` div. In this styling, the `.layout` is meant to be the root of 
the "app", like the base component of a react page, so it controls the 
layout and the styling, including the fonts.

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

![Adding Fonts](/assets/images/experiments-with-css-grid/adding-fonts.jpg)

Looking back, in an actual app, I'd consider creating a separate class 
which controls theming and adding that in alongside layout in the root
div.

## Styling the post snippets

Now I want the post snippet to have the header right at top, the button 
group right at the bottom, and the remaining space to be filled with 
the content. 

I could use `display: flex` and set the `.content` div to have `flex: 1` 
so that it could fill the-

**NAHFAM&trade;**

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

![Post Snippet Styling 1](/assets/images/experiments-with-css-grid/post-snippets-1.jpg)

![Post Snippet Styling 1](/assets/images/experiments-with-css-grid/post-snippets-2.jpg)

And, just to make the "buttons" look nicer

```scss
// Generic button
.button {
    // Sizing
    text-decoration: none;
    padding: $spacing-unit/2 $spacing-unit;
    border-radius: $button-border-radius;
    
    // Coloring
    color: black;
    background-color: #ccc;

    // Hover effect
    transition: background-color 0.5s;
    &:hover {
        background-color: #aaa;
    }
}
```

![Button Styling](/assets/images/experiments-with-css-grid/button-styling.jpg)

Now for the fun part

## Colors!

So, according to the diagram, all the post-snippets are different colors,
and the buttons and titles follow that color scheme. I also want to have
the background of the post snippets have a linear gradient.

So, to make things easier to change and configure, I created a few variables
which will contain the color data for the parts of the web page.

```scss
// Control background colors for menu, footer, and 
// main, second and third post snippets
$menu-background: #444 !default;
$footer-background: #999 !default;
$main-background: gold !default;
$second-backgrounds: 
    tomato dodgerblue mediumseagreen !default;
$third-backgrounds: 
    lightcoral sienna indianred orange 
    pink lavender violet turquoise 
    teal slateblue darkolivegreen slategray !default;
```

`$second-backgrounds` and `$third-backgrounds` are lists of color data,
each element is separated by whitespace.

I also created a mixin, which would take the given base color and style
each of the components within a post snippet based on that color. It also
applies the linear gradient to the background.

```scss
@mixin colored-snippet($color) {
    // Background image
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
```

Now we just include this in our subcomponents. In SCSS, to select the
n'th element in a list, you use `nth($list-variable, $n)`.

```scss
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

The fruits of my labour:

![Colors 1](/assets/images/experiments-with-css-grid/colors-1.jpg)

![Colors 2](/assets/images/experiments-with-css-grid/colors-2.jpg)

## Menu

Now onto the menu. For this, I'll need some icons. I'll be using `fontawesome-free`.
So I type `npm install --save @fortawesome/fontawesome-free` to install the library.
Fontawesome stores SCSS files which can be imported in my main SCSS file.

```scss
@import "./node_modules/@fortawesome/fontawesome-free/scss/fontawesome.scss";
@import "./node_modules/@fortawesome/fontawesome-free/scss/solid.scss";
@import "./node_modules/@fortawesome/fontawesome-free/scss/brands.scss";

// ... Import remaining scss
```

But there's a little issue here. Fontawesome stores it's icons in font files that it
needs to import. In order to import these files, our "web app" needs to be able to 
serve them, which means they need to be copied over to our `_public` folder.

Luckily, I already had `grunt-contrib-copy`, so I can get grunt to do this for me.

In the `copy` property in my `grunt.initConfig` config, I added this extra bit of
configuration

```js
copy: {
    ...
    fonts: {
        files: [{
            expand: true,
            cwd: './node_modules/@fortawesome/fontawesome-free/webfonts',
            src: '*',
            dest: siteDirectory + '/fonts'
        }]
    }
},
```

Fontawesome stores it's fonts in a directory called "webfonts". It is configured by
default to look for fonts there. That needs to be changed, and it can be by setting
the `$fa-font-path` variable in the main scss file.

```scss
$fa-font-path: '/fonts';
@import "./node_modules/@fortawesome/fontawesome-free/scss/fontawesome.scss";
@import "./node_modules/@fortawesome/fontawesome-free/scss/solid.scss";
@import "./node_modules/@fortawesome/fontawesome-free/scss/brands.scss";

// ... Import remaining scss
```

### Add Content

With fontawesome installed, I added the icons I was going to use, along with a
title.

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

![Menu Content](/assets/images/experiments-with-css-grid/menu-content.jpg)

### Make another grid

Now we're making our first nested grid. The css is as simple as always:

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

![Menu Grid](/assets/images/experiments-with-css-grid/menu-grid.jpg)

### Centering the elements

So now we have a problem. The elements are arranged in a grid, but they're not really centered.

I could wrap each of the elements in a container grid and use `flexbox` to center the-

**NAHFAM 2: Revenge of the YEET**

In fact, it's even simpler than `flexbox`. All you need is one attribute.

```scss
.menu {
    ...
    place-items: center;
    ...
}
```

![Menu Centered](/assets/images/experiments-with-css-grid/menu-centered.jpg)

### Styling Menu

I just wanted to add the linear gradient without the remaining styling in the `colored-snippet` 
mixin. So, I didn't use it, and I added the gradient manually. I also added a bit of spacing 
around the menu content.

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

For the icons, I just made them a lot bigger and had them inherit their color. This way, I could
use icons elsewhere in the website.

```scss
.icon {
    color: inherit;
    font-size: 24pt;
}
```

![Menu Styled](/assets/images/experiments-with-css-grid/menu-styled.jpg)

### Mobile menu grid

For mobile, all you need to do is change the layout!

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

![Menu Mobile](/assets/images/experiments-with-css-grid/menu-mobile.jpg)

## Changing mobile layout of post snippets

To go off that, I also wanted to change the styling of the post snippets on mobile.
Mainly, I want to center the title and have the `Read` button fill the entire bottom.

For centering the title, I just needed `text-align: center` to be active only on mobile.

```scss
.post-snippet {

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

![Mobile Snippets Header](/assets/images/experiments-with-css-grid/mobile-snippets-header.jpg)

Now to make the read button fill the entire width of the button group.

I could use `flexbox` with `flex-direction: row-reverse` and set `flex: 1` 
on the button to -

Actually, `flexbox` would work better for this use case. I thought 
of this section as something that could have one or more buttons 
or even small input forms that are evenly spaced, and flex 
automatically scales and positions those buttons accordingly. With 
CSS Grid, I would have to change the layout to accomodate the new 
elements.

So, I ultimately decided to use flex here.

```scss
.post-snippet {
    ...

    .buttons {
        grid-area: buttons;

        // Set display to flex
        display: flex;
        flex-direction: row-reverse;
        align-items: flex-start;

        .button {
            // Dont stretch
            flex: 0;

            // Set only margin left
            margin: 0pt;
            margin-left: $spacing-unit/2;

            // Align internal text to center
            text-align: center;

            @include on-mobile {
                // Stretch and margin both sides
                flex: 1;
                margin: 0pt $spacing-unit/2;
            }
        }
    }

    ...
}
```

![Mobile Snippets Button Group](/assets/images/experiments-with-css-grid/mobile-snippets-button-group.jpg)

If there's anything I learned as a professional idiot who happens 
to know how to code, it's to not try to fit the job around the tool. 
Better to find the right tool for the job.

## Styling footer

So for the footer, I wanted to have the text at the center
of the division. So, what's the best tool for this one?

**NAHFAM 3: Thanos Snaps Himself**

Flexbox does use less attributes, but I think CSS grid just reads better.

You declare a 1x1 grid and set the items to be placed in the center.

```scss
// Footer
.footer {
    ...

    // Center using Grid
    display: grid;
    grid-template-rows: 1fr;
    grid-template-columns: 1fr;
    place-items: center;

    ...
}
```

Vs.

```scss
// Footer
.footer {
    ...

    // Center using flexbox
    display: flex;
    align-items: center;
    justify-content: center;

    ...
}
```

![Footer Centered](/assets/images/experiments-with-css-grid/footer-centered.jpg)

After that, I just set the font-style to italic, gave it a slightly
grey color, and padded the edges.

```scss
.footer {
    ...

    // Font and spacing
    padding: $spacing-unit;
    font-style: italic;

    // Coloring
    background-image: linear-gradient(45deg, lighten($footer-background, 8%), $footer-background);
    color: white;
}
```

![Footer Styled](/assets/images/experiments-with-css-grid/footer-styled.jpg)

## Setting Tablet Layout

The last thing I wanted to do was create an intermediate layout for tablets.

First off, I made another mixin.

```scss
$responsive-tablet-size: 1200px !default;

@mixin on-tablet {
    @media only screen and (max-width: $responsive-tablet-size) {
        @content;
    }
}
```

Now, there's a major caveat when using this mixin along with `on-mobile`.
These media queries will check if the screen width is _less than_ the
given width in the query. CSS also works from top to bottom, meaning
that media queries are processed in the order that they are in the file.

So, say you put the `on-tablet` media query underneath the `on-mobile`
media query. On a mobile device, it will check to see if the screen
width is less than the mobile width, which it is. So, it will style
accordingly. Then, it will check to see if the screen width is less
than the tablet width, which it is. So, it will overwrite the mobile
styling and give you the tablet layout on mobile!

Not what we want.

So, it's important to make sure that the `on-tablet` media query comes
_before_ the `on-mobile` one. That way, on a mobile device, it will
set the tablet style, but then it will overwrite that style with the
mobile media query, and give us what we want. On a tablet, the mobile
query will fail, and we won't have to worry about it.

Just like before, we just change the layout and the divs will follow suit!

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
            "main     main     main     main     second-1 second-1"
            "second-2 second-2 second-2 second-1 second-1 second-1"
            "second-2 second-2 second-2 second-2 third-1  third-2"
            "second-3 second-3 second-3 third-3  third-4  third-5"
            "second-3 second-3 second-3 third-6  third-7  third-8"
            "footer   footer   footer   footer   footer   footer";
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

![Tablet Layout 1](/assets/images/experiments-with-css-grid/tablet-layout-1.jpg)

![Tablet Layout 2](/assets/images/experiments-with-css-grid/tablet-layout-2.jpg)

![Tablet Layout 3](/assets/images/experiments-with-css-grid/tablet-layout-3.jpg)

## Conclusion

So, in summary, there are still cases where other tools like flex come in handy, 
but CSS Grid does have it's many uses. Namely, I found that CSS Grid is incredibly 
useful for laying out webpages both horizontally and vertically and having the layout 
respond to multiple device sizes. For cases where you have one or more items that are
evenly spaced/scaled in one direction, like a list or a row of items, Flexbox works 
better for that.

So yeah, I'm gonna use CSS Grid for everything now.

Check out the project on [GitHub](https://github.com/andydevs/css-grid-blog-homepage-example) 
and the actual [website](https://css-grid-blog-homepage-example.netlify.com/) if it fancies you.