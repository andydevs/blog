---
layout: post
title: "Python Descriptors: What Are They and Why They're Cool"
date: "2018-06-28 22:24:53 -0400"
---

A common practice in python classes is using the `property` object to define "members" whose values are the calculated results of other member variables. For example, you may want to define a "getter" for "private" member variables that you've prepended with `_` (a very common thing you do in python). Let's do that...

```python
class Person:
    def __init__(self, name, email, birthday):
        self._name = name
        self._email = email
        self._birthday = birthday

    @property
    def name(self):
        return self._name

    @property
    def email(self):
        return self._email

    @property
    def birthday(self):
        return self._birthday
```

It looks like some redundant code... Is there a better way to write this?

Python's got you covered!

```python
class Get:
    def __init__(self, member):
        self._member = member

    def __get__(self, instance, klass=None):
        return getattr(instance, self._member)

class Person:
    def __init__(self, name, email, birthday):
        self._name = name
        self._email = email
        self._birthday = birthday

    name = Get('_name')
    email = Get('_email')
    birthday = Get('_birthday')
```

What I just created up there is called a "descriptor". To describe it, it'll take a bit of explaining. Get ready for a lot of double-underscore, behind-the-scenes python clockwork.

The first thing to explain is the `__dict__` property. Every object (and also classes) in python has a `__dict__` property. This property contains every member variable within the object.

```python
class Get:
    def __init__(self, member):
        self._member = member

    def __get__(self, instance, klass=None):
        return getattr(instance, self._member)

class Person:
    def __init__(self, name, email, birthday):
        self._name = name
        self._email = email
        self._birthday = birthday

    name = Get('_name')
    email = Get('_email')
    birthday = Get('_birthday')

person = Person('Joe Schmoe', 'joe@schmoe.com', 22)
print(person.__dict__) # =>
# { 'name': 'Joe Schmoe',
#   'email': 'joe@schmoe.com',
#   'age': 22 }
```

Getting the `__dict__` property of the class yields the members of the class.

```python
print(Person.__dict__) # =>
# { '__module__': '__main__',
#   '__init__': <function Person.__init__ at 0x7f2b7716eea0>,
#   'name': <__main__.Get object at 0x7f2b770b8ba8>,
#   'email': <__main__.Get object at 0x7f2b770e0e48>,
#   'age': <__main__.Get object at 0x7f2b770e0ef0>,
#   '__dict__': <attribute '__dict__' of 'Person' objects>,
#   '__weakref__': <attribute '__weakref__' of 'Person' objects>,
#   '__doc__': None }
```

Notice the `'name'`, `'email'`, and `'age'` values in the class's `__dict__` are instances of the `Get` class that we created.
