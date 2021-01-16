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

So why does this thing exist?

For all the times i've trained a machine learning model (which would be a couple), 
I've never really put those trained models into action. So, that's what I did. My 
goal was simple: find a dataset, train a machine learning model on it, and use 
that model in a web application. 

It was going to be as basic as possible (basic to the point of being impractical). 
I'd be using Tensorflow and other Python libraries for this project. I really wanted
to do this by the books.

## Training the Model

I got this [dataset](https://www.kaggle.com/uciml/mushroom-classification) 
from kaggle on different mushroom types. All the input data was categorical, 
which means it will all be encoded into a one-hot representation.

I'm not going to go to much into the data pipeline, since it is pretty 
complicated (mostly due to my overengineering). I'll briefly mention the `meta` 
object, which has information on the structure of the data.

Luckily, the rest of the model wasn't a problem to write out, thanks to Keras.
It was a fairly easy framework to declare the model with. However, it didn't 
have much in the way of support for feature columns, which helps preprocess 
incoming data. So, the data pipeline had to do a whole lot of the heavy lifting. 

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

After we define the model, we have the training task. Data is first split into 
training and testing. Then, it's passed into the data pipeline and onto the 
training code below.

```python
# Train model on training data
print('Training...')
model.fit(train_features, train_labels, epochs=10)

# Evaluate model on test data
print('Evaluating...')
_, accuracy = model.evaluate(test_features, test_labels)
print('Accuracy:', accuracy)

# Save model
print('Saving...')
model.save('saved-model.h5')
```

The last bit of code is for saving the model. Keras has a method for saving 
the model into a .h5 file. This file will be used to serve the trained model
over the web.

## Serving the Application

Used a flask application with a single index route that handles serving and
handling the form.

```py
# Model
model = load_model('saved-model.h5')

# Main page route
@app.route('/', methods=['GET', 'POST'])
def index():
    # Create a form
    form = DataForm()
    message = None
    message_type = None

    # Only if we're submitting a prediction
    if form.validate_on_submit():
        # Convert form data to array
        x = [ ]
        for name in meta.features.columns:
            input_name = sub('-', '_', name)
            x.append(form.data[input_name])

        # Encode and predict
        x = np.array([ x ])
        x = feature_encoder.transform(x)
        yHat = model.predict(x)
        yHat = label_encoder.inverse_transform(yHat)
        yHat = yHat[0, 0]

        # Set message based on encoding
        if yHat == 'p':
            message = 'Looks like it\'s poisonous. Don\'t eat it!'
            message_type = 'danger'
        else:
            message = 'Looks safe to eat! Hope it\'s tasty.'
            message_type = 'success'

    # Render template
    return render_template('index.html',
        form=form,
        message=message,
        message_type=message_type)
```

Used bootstrap to make it pretty... because I'm trying to be professional.

![The Site](/assets/images/machine-learning-mushrooms/the-site.png)

The gist is you put the characteristics of the mushroom into this form, you
click submit, and it comes back with an answer on wether it is poisionous or
not.

It's absolutely brilliant, isn't it?

Of course, it wasn't meant to be practicall. But, it served as a good exercise
in serving the machine learning models I train.