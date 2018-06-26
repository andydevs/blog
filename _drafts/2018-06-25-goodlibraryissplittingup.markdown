---
layout:   post
title:    "Splitting Up the Good Library (Monolithic Troubles)"
date:     "2018-06-25 20:27:00 -0400"
category: Update
---

_Everyone hates software. It's messy and it get's everywhere._ - Sam Gallagher 2017

I put that in the original README of The Good Library as a joke, but it's become a motto for my experience with the Good Library.

The Good Library was meant to be a utility library for writing more expressive code, eliminating redundancy and adding in some meta information that the interpreter can read. For me, it's an exercise in using the many metaprogramming features in python (which I will definitely write more about).

However, I've written the library to large enough to make me realize that I ran into a bit of a problem.

## The Software was Messy and Got Everywhere

A lot of these features don't really relate to each other, let alone depend on each other. But I decided to bundle them together in one monolithic package. It made it hard to maintain, even in "beta" (what I decided to call it). It's led to me making an "executive decision" to split my code, but I've learned something about this experience.

It's _much_ easier to manage multiple small packages of code rather than one giant thing of code.

In application development, for example, the microservice architecture has gained a lot of popularity, especially with cloud computing providing access to all the storage and infrastructure we need to build whatever we want. Python, Node, Ruby, and even Java now, have advanced package/dependency management systems that allow you to automatically install all the modules required to run your project. There's really no reason to bundle everything into one giant repository (unless you're like me).

## In Conclusion

The good-library package is officially (or will soon be) deprecated, and will be replaced by several packages which will contain the code within the original library. Look for packages with "good-" ahead of them.
