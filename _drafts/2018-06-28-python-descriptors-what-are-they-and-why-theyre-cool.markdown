---
layout: post
title: "Python Descriptors: What Are They and Why They're Cool"
date: "2018-06-28 22:24:53 -0400"
series: ExploringCode
---

Many times in object oriented programming, objects will have properties that are calculated values from other properties. In fact, you often just want properties which allow access to other private member variables. In Java, you write "get" methods like so:

```java
class Person {

    // Private member variables

    private String name;
    private String email;
    private Date birthday;

    // Constructor
    ...

    // Property getters

    public String getName() { return name; }

    public String getEmail() { return email; }

    public Date getDate() { return birthday; }
}
```

You retrieve the property by calling the appropriate method. For example, if you want to get the name, you call `person.getName()`.

In C#, you have the nicer `{ get; set; }` syntax, that can define how a property is retrieved.

```csharp
public class Person {

    private string name;
    private string email;
    private Date birthday;

    // Constructor
    ...

    public string Name {
        get {
            return name;
        }
    }

    public string Email {
        get {
            return email;
        }
    }

    public Date Birthday {
        get {
            return birthday;
        }
    }
}
```

This lets you access the property like it's another member variable. Just use `person.Name`

In Python, you have access to the `property` decorator method, which allows you to define properties from functions.

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

Here, you can call `person.name`, and it will call the associated method to get the result.

But this is only scratching the surface of what python can do! Python's property system goes much further than just emulating private member variables and `{ get; set; }` syntax.

There's, in fact, a much cleaner way to write this.

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

What I just created up there is called a "descriptor". How does it work?

Well, get ready for a lot of double-underscore, behind-the-scenes python clockwork.

Every object (and also classes) in python has a `__dict__` property. This property contains every member variable within the object.

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
