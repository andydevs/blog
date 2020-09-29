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

## Rective Forms