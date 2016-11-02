---
layout:     post
title:      "The Road to Cider"
date:       2016-07-26 21:17
categories: updates
---

Note: The actual name is subject to change, but I'm still calling it Cider even though that name was taken on RubyGems. 

It will always be Cider in my heart for as long as I live.

I don't like IDE's. They're big programs with clunky UI's that take up way to much RAM, work very slowly, and don't have much in the way of customizabiltiy, since they tend to be designed for specific types of projects. After working with C++ projects (compilers, makefiles and project directories) outside of IDE's, I eventually came up with Cider. 

Cider is a lightweight, command line based IDE that uses Ruby scripts to automate project tasks like file manipulation, builds, and version control. The purpose was that you can use your own text editor and configure Cider to use whatever build system, version control system, and style of programming that you like, without going through tons of confusing menus and options. I came up with several ideas for Cider, like new templating engines, project management libraries, and newer concepts like interface definition languages. However, I realized these could be used for other Ruby projects, so I decided that I can implement these as separate gems and then pull them all together into Cider (or whatever I decide to call it).

I already developed release versions for [General](http://andydevs.github.io/general), a templating engine, and [Roject](http://andydevs.github.io/roject), a project manager, and I'm still updating those projects with new features. Aside from that, Cider will be using a command line interface gem that would traverse a Module structure and call methods from the command line, as well as a new simpler, human-readable build system written in Ruby.

Thats is what I've been working on recently (aside from Jump, which is another story alltogether). Currently, I don't really have a release date for Cider. I just update projects as I go while I'm not persuing my engineering degree. Be sure to check back on occasion for more updates.