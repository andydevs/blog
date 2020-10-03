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
let clickObservable$ = fromEvent(box, 'click')
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
let animationFrames$ = of(0, animationFrameScheduler)
```

Instead of setting our mouse pos directly, we save it to a buffer
variable and 

## Rective Forms