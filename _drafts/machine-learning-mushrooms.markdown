---
layout: post
title: Machine Learning Mushrooms
excerpt_separator: <!--why-->
---

So picture this: You're in the forest and you're hungry. You didn't pack any food along the way and you're too far from anywhere where you can get food. You come across a mushroom, and you consider eating it for sustainance. But, your breadth of knowledge about forest ecology tells you that that mushroom might be poisionous. You just can't know for sure.

Well, you're in luck, 'cause ya boy Andy made an app that can tell you just that!

<!--why-->

All you need is a smartphone, a good internet connection, a magnifying glass maybe, and a whole lot of patience.

Okay. I wanted to try out machine learning. So, I got this [dataset](https://www.kaggle.com/uciml/mushroom-classification) from kaggle on different mushroom types and I trained a Keras model on it.

## The Data

So I started with the dataset, and I created a `meta.yaml` file to encode the structure of the data.

All my input data was categorical, which means it will all be encoded into a one-hot representation.

So, the pipeline involved pulling the csv data, splitting into features and labels, and encoding the
labels and features into one-hot representation.

## Training the Model

Model

```python

```

## Serving the Application

## Conclusion

It ain't practical... not in the least. But it is insanely cool.