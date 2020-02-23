---
title: "Experiments in CSS Grid"
layout: post
keywords: andydevs blog css-grid css grid gradient
---

I watched a [video lecture](https://youtu.be/7kVeCqQCxlk) from Coding Tech about 
CSS Grid. I saw how CSS Grid was so much easier and more elegant than whatever I 
was using before (mainly flexbox).

Needless to say, I was intrigued and I wanted to try it myself.

So, off the tail of another css project, I'm jumping right back in and making a 
website using CSS grid. This website in particular will be a homepage for a "blog".

It's not a real website, it's just a mockup.

I "drew" this layout (using google drawings)

_Desktop_

![Desktop](/assets/images/experiments-with-css-grid/desktop.jpg)

_Mobile_

![Mobile](/assets/images/experiments-with-css-grid/mobile.jpg)

A few notes on this design: the colors are actually linear gradients, and the 
"Icon Grid" and "Icon Row" sections will contain icons for accessing other 
parts of the website.

## Setting up the Project

So I started up a new npm project. I used `grunt` as a task runner, as I was
going to be building `scss` code, and copying files over in my build process.

So I installed `grunt`, `grunt-cli`, `grunt-sass`, and `node-sass`.

I realized down the road that I didn't need any javascript for this project.
This was pure css. So no `grunt-babel` or any of that stuff.

I designated `_public` to be the directory where my files are stored (I 
underscored it so that it appears at the top... I think I might've gotten
it backwards as I should keep my source files on top but... oh well).

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

The basic gist is that we have all of our content under one layout div. This single div will control the placement of all of our components. In it, we have our menu. I've kept the menu blank for now, as I work on it a bit down the road (using nested grid). Following the menu are the post snippets. I grouped the snippets into `main`, `second` and `third` snippets. In the hypothetical blog I would be making, the `main` snippet would be, for example, the featured post of the day. The `second` snippets would be three other highlighted posts, and the `third` snippets would be eight less important posts (possibly like the posts from last week or something)

I noticed I forgot to add the footer in my layout so I added it in after the fact.

Here's what that looks like

- Add a screenshot of this

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

The `1fr` translates to "1 fraction". `repeat(5, 1fr)` will repeat that five times. This tells CSS to divide the vertical 
free space into five equally spaced rows. Likewise `repeat(8, 1fr)` will divide the horizontal free space into eight 
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

Then, in our contained elements, we set `grid-area` to a named area, and the element will automatically fill that area!

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

- Screenshot

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

Crazy, right. Well...

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

Then, all we need to do is change `grid-template-areas` in the `.layout` class.

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

Yeah, that's it! That's all ya gotta do. You can arrange these blocks
anywhere, and the divs will follow!

A few things to note here. `auto` means scale the row to fit the content. 
We only want the menu to be as big as it needs to be, so `auto` takes care 
of that.

The other thing is that `1.5fr`. I wanted the main post snippet to be about 
50% taller than the second post snippets, so I set that row to take up 
slightly more space.

Here's what that looks like

- Screenshot!

## Adding Fonts

Calibri Light, that's my go-to font. I'm putting the font settings in the
`layout` div. The `layout` is mean to be the root of the "app", so it controls
the layout and the styling, including the fonts.

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

- Screenshot!

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

## Styling footer

- Need to center text
- NAHFAM 3: Thanos Snaps Himself

```scss
// Footer
.footer {
    ...

    // Display Grid
    display: grid;
    grid-template-rows: 1fr;
    grid-template-columns: 1fr;
    place-items: center;

    ...
}
```

- Coloring and fonts

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

- Screenshot

## Conclusion

- CSS Grid was insanely easy
- I'm gonna use this for everything
- Check out project on github
- Check out website