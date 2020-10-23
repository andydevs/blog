---
layout: post
title: Machine Learning Mushrooms
excerpt_separator: <!--why-->
---

So picture this: You're in the forest and you're hungry. You didn't pack any food 
along the way and you're too far from anywhere where you can get food. You come 
across a mushroom, and you consider eating it for sustainance. But, your breadth 
of knowledge about forest ecology tells you that that mushroom might be poisionous. 
You just can't know for sure.

Well, you're in luck, 'cause ya boy Andy made an app that can tell you just that!

<!--why-->

All you need is a smartphone, a good internet connection, a magnifying glass 
maybe, and a whole lot of patience.

Okay. I wanted to try out machine learning. So, I got this 
[dataset](https://www.kaggle.com/uciml/mushroom-classification) from kaggle on 
different mushroom types and I trained a Keras model on it.

## The Data

So I started with the dataset, and I created a `meta.yaml` file to encode the 
structure of the data. All my input data was categorical, which means it will 
all be encoded into a one-hot representation.

```yaml
--- !MetaData

# Output labels and name of column
output: !Output
    column: class
    labels: !CategorySet
        categories:
            e: edible
            p: poisonous

# Outline categories for each feature
features: !FeatureSet
    features:
        bruises: !CategorySet
            categories:
                f: 'no'
                t: bruises
        cap-color: !CategorySet
            categories:
                b: buff
                c: cinnamon
                e: red
                g: gray
                n: brown
.
.
.
```

By far the most extensive part of this project was the data pipeline. The data
had to be read from the dataset, split into training and testing, and encoded
using one hot representation.

Python YAML actually has a feature that allows you to define classes that the
YAML data is automatically converted into. So, I can define a lot of functionality
into the YAML file.

```python
class MetaData(yaml.YAMLObject):
    yaml_tag = u'!MetaData'

    def __init__(self, output, features):
        self.output = output
        self.features = features

    def __repr__(self):
        return f'MetaData(output={self.output}, features={self.features})'

    def split_dataset(self, dataset):
        labels = dataset[self.output.column].values.reshape(-1,1)
        features = dataset[self.features.columns].values
        return labels, features

class Output(yaml.YAMLObject):
    yaml_tag = u'!Output'
    
    def __init__(self, column, labels):
        self.column = column
        self.labels = labels

    def __repr__(self):
        return f'Output(column={self.column}, labels={self.labels})'

    @property
    def size(self):
        return len(self.labels)

.
.
.
```

The pipeline involved pulling the csv data, splitting into features and labels, 
and encoding the labels and features into one-hot representation. A lot of the 
parsing and organizing of the data is handled by `meta.yaml`.

## Training the Model

The model was declared using Keras's framework. It was a fairly easy framework
to use. However, it didn't have much in the way of support for feature columns,
which helps process incoming data. So, the data pipeline had to do a whole lot 
of the heavy lifting.

Luckily, the rest of the model wasn't a problem. The following code defines the
model:

```python
model = tf.keras.models.Sequential([
    tf.keras.Input(shape=(meta.features.size,)),
    tf.keras.layers.Dense(16, activation='relu'),
    tf.keras.layers.Dropout(0.2),
    tf.keras.layers.Dense(meta.output.size, activation='softmax')
])
model.compile(
    loss=tf.keras.losses.CategoricalCrossentropy(),
    optimizer='adam',
    metrics=['accuracy']
)
model.summary()
```

The training task

```python
from .model import model
from .data import prepare_train_test_data
import config

# Get training and testing data
train_labels, train_features, test_labels, test_features = prepare_train_test_data()

# Train model on training data
print('Training...')
model.fit(train_features, train_labels, epochs=10)

# Evaluate model on test data
print('Evaluating...')
_, accuracy = model.evaluate(test_features, test_labels)
print('Accuracy:', accuracy)

# Save model
print('Saving...')
model.save(f'{config.model_directory}/{config.model_filename}')
```

## Serving the Application

Used a flask application with a single link. Send a post request via the same link.

Used bootstrap to make it pretty... because I'm trying to be professional.

![The Site](/assets/machine-learning-mushrookms/the-site.png)

## Conclusion

It ain't practical... not in the least. But it is insanely cool.