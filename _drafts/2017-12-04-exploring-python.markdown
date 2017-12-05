---
layout: post
title: "Exploring Python"
series: ExploringCode
date: "2017-12-04 14:23:08 -0500"
---

I've already talked about first-class closure functions, function factories, and decorators in my ~~love letter~~ post about [decorators in python]({{ site.baseurl }}/2017/11/07/the-single-most-beautiful-piece-of-syntax-ever-invented.html). But python has so much more to offer that it's not surprising that it's one of the most popular languages in the world. In this article, I'm going to go over more unique features in Python that I love.

## First-Class Closure Functions, Function Factories, and Decorators: a Recap

First-class functions are functions that are treated like other datatypes. So they can be passed around, defined within functions, passed into functions, and returned from functions, just like other datatypes.

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

    # Construct your function and return it!
    def greet(name):
        print(greeting + ', ' + name + '!')
    return greet

# Create a new greeting
say_hello = create_greeting('Hello')

say_hello('Arin') # Prints 'Hello, Arin!'
say_hello('Danny') # Prints 'Hello, Danny!'
```

Using these properties, we can create function wrappers which we can use to modify functions

```python
def elementwise(func):

    def elementwise_wrapper(value):
        if type(value) is list:
            return [func(elem) for elem in value]
        else:
            return func(value)

    return elementwise_wrapper

def factorial(n):
    prod = 1
    for r in range(1,n):
        prod *= r
    return prod
factorial = elementwise(factorial)

factorial(3) # Returns 6
factorial([2, 3, 4]) # Returns [2, 6, 24]
```

Or even better...

```python
@elementwise
def factorial(n):
    if n > 0: return n*factorial(n-1)
    else: return 1
```

## Attribute Access and Descriptors

Let's say you're designing a vector math library and you create a vector class

```python
class Vector:
    def __init__(self, *args):
        self._comps = args

    def __len__(self):
        """
        Returns the length of the vector
        """
        return len(self._comps)

    def __getitem__(self, index):
        """
        Returns a component in the vector
        """
        return self._comps[index]

    def __add__(self, other):
        """
        Adds two vectors together
        """
        return Vector(*(a+b for a,b in zip(self._comps, other._comps)))

    def __mul__(self, scalar):
        """
        Scales two vectors
        """
        return Vector(*(scalar*a for a in self._comps))

vector = Vector(2, 3, 4, 5, 1, 9)
vector[2] # returns 4
```

But you know that some people use 'x' and 'y', to represent the components of a 2-vector, and 'x', 'y', and 'z' to represent the components of a 3-vector. You can use the `property` decorator to create these named values. So you create special vector classes that can get those special names.

```python
class Vector2(Vector):
    @property
    def x(self):
        return self[0]

    @property
    def y(self):
        return self[1]

class Vector3(Vector):
    @property
    def x(self):
        return self[0]

    @property
    def y(self):
        return self[1]

    @property
    def z(self):
        return self[2]

v = Vector3(2, 3, 4)
v.x # Returns 2!
v.x = 3 # X is now 3!
```

Nice, right? Well, it seems like you're writing a lot of redundant code. All you're doing is matching each property name to an index in a list, right? Is there a more concise way to write this?

Python's got you covered! But it will take a bit of explaining. Get ready for a lot of double-underscore, behind-the-scenes python clockwork.

When you type `v.x`, what you're actually doing is calling a built-in method called `__getattribute__` that exists in all Python objects, passing in the name of the attribute, in this case `x`. So `v.x` under the hood is `v.__getattribute__('x')`. This method starts a chain of checks which determines where the actual attribute value lies.

Every object in python has what is called `__dict__`. This is a dictionary of all the attributes that are stored within that object. So, if you write `v.__dict__['x']`, you're effectively doing `v.x`.

`__getattribute__` first checks if `x` is in the object's `__dict__`. If so, it returns the value of `x` in the `__dict__`. Otherwise, it goes one level and checks the `__dict__` in the class, (which, in fact, also has a `__dict__`. I'll go deeper into why this is in the next section). If `x` is in the class `__dict__`, it will return the value of `x` in that `__dict__`... almost.

## Class Factories

Do you know why classes also have a `__dict__`? Are you ready to have your mind blown?

It's because classes are _also_ objects.

## Metaclasses

## Conclusion
