---
layout: post
title: Observables are Actually Good
---

Here are a few ways that I've used observables.

## Reactive Animations

Objective: animate box to follow mouse movement after being clicked.

Create observable to track mouse position.

```js
const mouseMovePos$ = fromEvent(document, 'mousemove')
    .pipe(
        map(event => ({
            x: event.clientX,
            y: event.clientY
        }))
    )
```

Get box element from document

```js
let box = document.getElementById('redbox')
```

Now we subscribe to the mouse move pos on a click event

```js
box.addEventListener('click', event => {
    mouseMovePos$.subscribe(pos => {
        box.style.left = pos.x + 'px'
        box.style.top = pos.y + 'px'
    })
})
```

We also want to unsubscribe from the mouse observable on
a second click. Subscribing to observables returns a 
subscription object which contains an unsubscribe method,
so we use it to unsubscribe

```js
let mouseSub

box.addEventListener('click', event => {
    if (mouseSub) {
        mouseSub.unsubscribe()
        mouseSub = null
    }
    else {
        mouseSub = mouseMovePos$.subscribe(pos => {
            box.style.left = pos.x + 'px'
            box.style.top = pos.y + 'px'
        })
    }
})
```

We can actually make this a bit cleaner by using `closed` and 
`Subscription.EMPTY`, an empty subscription object provided by
`rxjs`

```js
let mouseSub = Subscription.EMPTY

box.addEventListener('click', () => {
    if (mouseSub.closed) {
        mouseSub = mouseMovePos$.subscribe(pos => {
            box.style.left = pos.x + 'px'
            box.style.top = pos.y + 'px'
        })
    }
    else {
        mouseSub.unsubscribe()
    }
})
```

We can actually use an event observable for click events

```js
let mouseSub = Subscription.EMPTY

fromEvent(box, 'click').subscribe(() => {
    if (mouseSub.closed) {
        mouseSub = moveMousePos$.subscribe(pos => {
            box.style.left = pos.x + 'px'
            box.style.top = pos.y + 'px'
        })
    }
    else {
        mouseSub.unsubscribe()
    }
})
```

### Implementing drag

First off, the `mousemove` event only fires when the mouse moves,
we want it to move event when we're not moving our mouse.

Create a second observable that fires every animation frame. We
use a frame scheduler

```js
let animationFrame$ = of(0, animationFrameScheduler)
```

Instead of setting our mouse pos directly, we save it to a buffer
variable and update our position on every animation frame

```js
let mousepos
mouseMovePos$.subscribe((pos) => {
    mousepos = pos
})

let mouseSub = Subscription.EMPTY
fromEvent(box, 'click').subscribe(() => {
    if (mouseSub.closed) {
        mouseSub = animationFrame$.subscribe(() => {
            box.style.left = mousepos.x + 'px'
            box.style.top = mousepos.y + 'px'
        })
    }
    else {
        mouseSub.unsubscribe()
    }
})
```

Now to implement drag, we can use the following equation to 
compute the updated position

$$
\textbf{x}_{n+1} = \alpha \textbf{y} - (1 - \alpha) \textbf{x}_n
$$

Essentially, the updated position $\textbf{x}$ is proportional 
to the current distance to the mouse position $\textbf{y}$

Implemented in code

```js
const alpha = 0.75

// Initial box position
let boxpos = { x: 50, y: 50 }

// Mouse position
let mousepos
mouseMovePos$.subscribe((pos) => {
    mousepos = pos
})

// Toggle mouse move subscribe
let mouseSub = Subscription.EMPTY
fromEvent(box, 'click').subscribe(() => {
    if (mouseSub.closed) {
        mouseSub = animationFrame$.subscribe(() => {
            // Update box position
            boxpos = {
                x: alpha*mousepos.x + (1 - alpha)*boxpos.x,
                y: alpha*mousepos.y + (1 - alpha)*boxpos.y
            }

            // Update box's actual position
            box.style.left = boxpos.x + 'px'
            box.style.top = boxpos.y + 'px'
        })
    }
    else {
        mouseSub.unsubscribe()
    }
})
```

### Use observables to make this better

We can actually combine the animation frame observable and 
the mouse position into one observable that emits the latest
mouse position recorded every frame

```js
// Alpha parameter
const alpha = 0.75

// Mouse position every animation frame
let mousePos$ = combineLatest([animationFrame$, mouseMovePos$])
    .pipe(map(([_, pos]) => pos))

// Initial box position
let boxpos = { x: 50, y: 50 }

// Toggle mouse move subscribe
let mouseSub = Subscription.EMPTY
fromEvent(box, 'click').subscribe(() => {
    if (mouseSub.closed) {
        mouseSub = mousePos$.subscribe(mousepos => {
            // Update box position
            boxpos = {
                x: alpha * mousepos.x + (1 - alpha) * boxpos.x,
                y: alpha * mousepos.y + (1 - alpha) * boxpos.y
            }

            // Update box's actual position
            box.style.left = boxpos.x + 'px'
            box.style.top = boxpos.y + 'px'
        })
    }
    else {
        mouseSub.unsubscribe()
    }
})
```

The `boxpos` is an accumulator variable that is updated with each
new object emitted from `mousePos$`. `rxjs` actually has an operator
for this, called `scan`, which can be used for an observable that
depends on an internal state

```js
// Alpha parameter
const alpha = 0.75

// Box position observable
let boxPos$ = mousePos$
    .pipe(
        scan(
            (boxpos, mousepos) => ({
                x: alpha * mousepos.x + (1 - alpha) * boxpos.x,
                y: alpha * mousepos.y + (1 - alpha) * boxpos.y
            }), 
            { x: 50, y: 50 }
        )
    )

// Toggle mouse move subscribe
let boxSub = Subscription.EMPTY
fromEvent(box, 'click').subscribe(() => {
    if (boxSub.closed) {
        // Update box's position
        boxSub = boxPos$.subscribe(boxpos => {
            box.style.left = boxpos.x + 'px'
            box.style.top = boxpos.y + 'px'
        })
    }
    else {
        boxSub.unsubscribe()
    }
})
```

## Rective Forms