---
layout: post
title: "Exploring Metaprogramming"
date: "2017-12-04 14:23:08 -0500"
---

I love metaprogramming. It lets you write less code, and be way more expressive. In a sense, it allows you to hack the language and define your own syntax.
In this article, I'm going to go over metaprogramming in Python, Ruby, and Javascript.

## Python

I've already talked about first-class closure functions, function factories, and decorators in my ~~love letter~~ post about [decorators in python]({{ site.baseurl }}/2017/11/07/the-single-most-beautiful-piece-of-syntax-ever-invented.html). To recap, first-class functions are functions that are treated like other datatypes. So they can be passed around, defined within functions, passed into functions, and returned from functions, just like other datatypes.

```python
def get_a_cool_function():

    def cool_function():
        print('This function\'s cool')

    return cool_function

def say_this(word):
    print('[The spoken word]: '+word+'!')

def do_for_each(func, values):
    for val in values:
        func(val)

speak = say_this

do_for_each(speak, ['hello', 'goodbye', 'my name is Joe'])
# Prints '[The spoken word]: hello!'
# Prints '[The spoken word]: goodbye!'
# Prints '[The spoken word]: my name is Joe!'
```

Functions in python also have the closure property, which allows them to retain the environment they were defined in (including all the variables and functions set within that environment, even parameters), even if it is called outside that environment. We leverage this property to create function factories.

```python
def create_greeting(greeting):

    def greet(name):
        print(greeting + ', ' + name + '!')

    return greet

say_hello = create_greeting('Hello')

say_hello('Arin') # Prints 'Hello, Arin!'
say_hello('Danny') # Prints 'Hello, Danny!'
```

From these we can create function wrappers which we can use to modify functions

```python
def elementwise(func):

    def elementwise_wrapper(value):
        if type(value) is list:
            return [func(elem) for elem in value]
        else:
            return func(value)

    return elementwise_wrapper

def factorial(n):
    if n > 0: return n*factorial(n-1)
    else: return 1
factorial = elementwise(factorial)
```

Or even better...

```python
@elementwise
def factorial(n):
    if n > 0: return n*factorial(n-1)
    else: return 1
```

But that's not all python can do!

### Attribute Access and Descriptors

Now descriptors are a bit hard to describe, but if you know how they work, you can use them to make so many cool object-oriented features.

Let's say you create a class and instantiate an object of that class

```python
class Vector2:
    def __init__(self, x, y):
        self.x = x
        self.y = y

vector = Vector2(2, 3)
```

What happens when you type `vector.x`? Get ready for a lot of double-underscores and built-in behind-the-scenes python clockwork as I explain this.

What you're actually doing is calling a built-in method called `__getattribute__` available in all Python objects. This method starts a chain of checks which determines where the actual attribute value lies.

### Class Factories

### Metaclasses

## Ruby

Ruby is inherently, unapologetically object-oriented. Scope is determined by what object `self` is. In the main scope, `self` is an instance of Object.

Using `define_method`, `instance_variable_set`, `const_set`, `class_variable_set`, etc.

Using `instance_eval`, `module_eval`, `class_eval`, etc.

Using `responds_to?` and `method_missing`

## Javascript

Prototypical inheritence.

Updating object prototypes.

Hacking the prototype chain.

## Conclusion

conclude subject
