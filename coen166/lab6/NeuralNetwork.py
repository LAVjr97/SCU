#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov 14 14:54:48 2023

@author: jonathansantosa
"""
from sklearn.metrics import confusion_matrix
import tensorflow as tf
import numpy as np
from tensorflow import keras
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Flatten
import matplotlib.pyplot as plt

fashion_mnist = keras.datasets.fashion_mnist
(x_train, y_train), (x_test, y_test) = fashion_mnist.load_data()
x_train, x_test = x_train / 255.0, x_test / 255.0 # normalize the pixel values to be in [0, 1] # note: you need to flatten the image to a vector, to serve as the input layer of the network. # code to be implemented ...

model = Sequential()
model.add(Flatten(input_shape=(28, 28)))
model.add(Dense(512, activation='relu'))
model.add(Dense(10, activation='softmax'))

# Compile the model
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

# Train the model
model.fit(x_train, y_train, epochs=5, batch_size=32, validation_data=(x_test, y_test))
predictions = model.predict(x_test)

# Round Predictions
y_test_hat = [np.argmax(x) for x in predictions]

num_correct = 0
for i in range(len(y_test)):
    if y_test_hat[i]==y_test[i]:
        num_correct +=1

Accuracy_rate = num_correct/len(y_test)
print("Accuracy Rate = ", Accuracy_rate)
print(confusion_matrix(y_test, y_test_hat))

fig, axes = plt.subplots(1, 10, figsize=(2*10,2*1)) #1 row, 10 columns

for i in range(10):
    ax = axes[i]
    ax.imshow(x_test[i], cmap='gray')

plt.tight_layout()
plt.show()
