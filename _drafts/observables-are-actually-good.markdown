---
layout: post
title: Observables are Actually Good
---

Objective: animate box to follow mouse movement after being clicked.

The Naive Approach
----------------------------------------------------------------------------

Programatically creating boxes

```js
const app = document.getElementById('app')

export function createBox(color, initial={x: 0, y: 0}) {
    let box = document.createElement('div')
    box.classList.add('box')
    box.style.backgroundColor = color
    app.appendChild(box)
    moveBox(box, initial)
    return box
}
```

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

Now we can subscribe to that position and update our box

```js
let box = createBox('red', { x: 100, y: 100 })

function move(elem, pos) {
    elem.style.left = pos.x + 'px'
    elem.style.top = pos.y + 'px'
}

mouseMovePos$.subscribe(pos => move(box, pos))
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

We also want to toggle the motion from the mouse observable 
on a click. Subscribing to observables returns a subscription 
object which contains an unsubscribe method, so we use it to 
unsubscribe when we need to.

```js
let boxSub

box.addEventListener('click', event => {
    if (boxSub) {
        boxSub.unsubscribe()
        boxSub = null
    }
    else {
        boxSub = mouseMovePos$.subscribe(pos => move(box, pos))
    }
})
```

To implement drag

First off, the `mousemove` event only fires when the mouse moves,
we want it to move even when we're not moving our mouse.

Create a second observable that fires every animation frame. We
use a frame scheduler, which is provided using `observeOn`

```js
let animationFrame$ = of(null)
    .pipe(
        repeat(),
        observeOn(animationFrameScheduler)
    )
```

The actual value of this ovservable doesn't matter (it just emits
null over and over again), it only matters that this fires every
animation frame. The operators cause the animation frame to fire
only on the next animation frame and also repeat indefinitely.

Our mouse pos also only gets to fire on an animation event

```js
const mouseMovePos$ = fromEvent(document, 'mousemove')
    .pipe(
        map(event => ({
            x: event.clientX,
            y: event.clientY
        })),
        observeOn(animationFrameScheduler)
    )
```

Instead of setting our mouse pos directly, we save it to a buffer
variable and update our position on every animation frame

```js
let mousepos
mouseMovePos$.subscribe((pos) => mousepos = pos)

let boxSub
box.addEventListener('click', () => {
    if (boxSub) {
        boxSub.unsubscribe()
        boxSub = null
    }
    else {
        boxSub = animationFrame$.subscribe(() => move(box, mousepos))
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
mouseMovePos$.subscribe((pos) => mousepos = pos)

// Toggle mouse move subscribe
let mouseSub
box.addEventListener('click', () => {
    if (mouseSub) {
        mouseSub.unsubscribe()
        mouseSub = null
    }
    else {
        mouseSub = animationFrame$.subscribe(() => {
            // Update box position
            boxpos = {
                x: alpha*mousepos.x + (1 - alpha)*boxpos.x,
                y: alpha*mousepos.y + (1 - alpha)*boxpos.y
            }

            // Update box's actual position
            move(box, boxpos)
        })
    }
})
```

Use observables to make this better
----------------------------------------------------------------------------

We can actually make this a bit cleaner by using `closed` and 
`Subscription.EMPTY`, an empty subscription object provided by
`rxjs`

```js
let mouseSub = Subscription.EMPTY

box.addEventListener('click', () => {
    if (mouseSub.closed) {
        mouseSub = mouseMovePos$.subscribe(pos => move(box, pos))
    }
    else {
        mouseSub.unsubscribe()
    }
})
```

We can actually use an event observable for click events for good measure

```js
let mouseSub = Subscription.EMPTY

fromEvent(box, 'click')
    .subscribe(() => {
        if (mouseSub.closed) {
            mouseSub = moveMousePos$.subscribe(pos => move(box, pos))
        }
        else {
            mouseSub.unsubscribe()
        }
    })
```

Combine the animation frame observable and the mouse position 
into one observable that emits the latest mouse position recorded 
every frame

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

            // Move box to box position
            move(box, boxpos)
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
            // Box position update
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
        boxSub = boxPos$.subscribe(boxpos => move(box, pos))
    }
    else {
        boxSub.unsubscribe()
    }
})
```

We can move the scan operator to a separate function,
creating our own operator (so we can have different
alpha values)

```js
function interpolate(alpha) {
    return scan(
        (pos, next) => ({
            x: alpha * next.x + (1 - alpha) * pos.x,
            y: alpha * next.y + (1 - alpha) * pos.y
        }),
        { x: 0, y: 0 }
    )
}
```

Create a generic subscriber that toggles another subscription

```js
function toggle(observable$, subfunc) {
    return {
        subscription: Subscription.EMPTY,
        next() {
            if (this.subscription.closed)
                this.subscription = observable$.subscribe(subfunc)
            else
                this.subscription.unsubscribe()
        },
        error() {
            if (!this.subscription.closed)
                this.subscription.unsubscribe()
        },
        complete() {
            if (!this.subscription.closed)
                this.subscription.unsubscribe()
        }
    }
}
```

```js
// Toggle mouse move subscribe
fromEvent(box, 'click')
    .subscribe(toggle(
        mousePos$.pipe(interpolate(0.75)),
        pos => move(box, pos)
    ))
```

Now we have multiple elements

```js
function clickAndDrag(id, alpha) {
    let elem = document.getElementById(id)
    return fromEvent(elem, 'click')
        .subscribe(toggle(
            interpolate(alpha)(mousePos$),
            pos => move(elem, pos)
        ))
}

clickAndDrag('box', 1.0)
clickAndDrag('circle', 0.75)
clickAndDrag('airplane', 0.25)
```

Putting it all together
----------------------------------------------------------------------------

With observables

```js
function interpolate(alpha) {
    return scan(
        (pos, next) => ({
            x: alpha * next.x + (1 - alpha) * pos.x,
            y: alpha * next.y + (1 - alpha) * pos.y
        }),
        { x: 0, y: 0 }
    )
}

function toggle(observable$, subfunc) {
    return {
        subscription: Subscription.EMPTY,
        next() {
            if (this.subscription.closed)
                this.subscription = observable$.subscribe(subfunc)
            else
                this.subscription.unsubscribe()
        },
        error() {
            if (!this.subscription.closed)
                this.subscription.unsubscribe()
        },
        complete() {
            if (!this.subscription.closed)
                this.subscription.unsubscribe()
        }
    }
}

let animationFrame$ = of(null)
    .pipe(
        repeat(),
        observeOn(animationFrameScheduler)
    )

let mouseMovePos$ = fromEvent(document, 'mousemove')
    .pipe(
        map(event => ({
            x: event.clientX,
            y: event.clientY
        })),
        observeOn(animationFrameScheduler)
    )

let mousePos$ = combineLatest([animationFrame$, mouseMovePos$])
    .pipe(map(([_, pos]) => pos))

function clickAndDrag(id, alpha) {
    let elem = document.getElementById(id)
    return fromEvent(elem, 'click')
        .subscribe(toggle(
            interpolate(alpha)(mousePos$),
            pos => move(elem, pos)
        ))
}

clickAndDrag('box', 1.0)
clickAndDrag('circle', 0.75)
clickAndDrag('airplane', 0.25)
```