from sklearn.metrics import confusion_matrix
import tensorflow as tf
import numpy as np
from tensorflow import keras
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Flatten
from keras.layers import Reshape
import matplotlib.pyplot as plt
import math

# Load and preprocess Fashion MNIST data
fashion_mnist = keras.datasets.fashion_mnist
(x_train, y_train), (x_test, y_test) = fashion_mnist.load_data()
x_train, x_test = x_train / 255.0, x_test / 255.0  # Normalize pixel values

M = 28
N = 28
P = 10  # Number of nodes in the compressed layer
T = 2   # Expansion factor

# Build the autoencoder model 
model = Sequential() 
model.add(Flatten(input_shape=(M, N)))  # Input layer
model.add(Dense(P, activation='relu'))   # Compressed layer
model.add(Dense(M * N * T, activation='relu'))  # Expansion layer
model.add(Dense(M * N, activation='sigmoid'))  # Output layer
model.add(Reshape(target_shape=(M, N)))  # Reshape layer 

# Compile the model
model.compile(optimizer='adam', loss='mean_squared_error', metrics=['accuracy'])

# Train the model
model.fit(x_train, x_train, epochs=10, batch_size=64)

# Evaluate the model on the test set
test_loss, test_accuracy = model.evaluate(x_test, x_test)
predictions = model.predict(x_test)

psnr1 = 10*math.log10(1/test_loss)

print("Loss = ", test_loss)
print("Accuracy = ", test_accuracy)
print("Average PSNR = ", psnr1)

# Load and preprocess Fashion MNIST data
fashion_mnist = keras.datasets.fashion_mnist
(x_train2, y_train2), (x_test2, y_test2) = fashion_mnist.load_data()
x_train2, x_test2 = x_train2 / 255.0, x_test2 / 255.0  # Normalize pixel values

''''''''''''
P = 50

# Build the autoencoder model 
model2 = Sequential() 
model2.add(Flatten(input_shape=(M, N)))  # Input layer
model2.add(Dense(P, activation='relu'))   # Compressed layer
model2.add(Dense(M * N * T, activation='relu'))  # Expansion layer
model2.add(Dense(M * N, activation='sigmoid'))  # Output layer
model2.add(Reshape(target_shape=(M, N)))  # Reshape layer 

# Compile the model
model2.compile(optimizer='adam', loss='mean_squared_error', metrics=['accuracy'])

# Train the model
model2.fit(x_train2, x_train2, epochs=10, batch_size=64)

# Evaluate the model on the test set
test_loss2, test_accuracy2 = model2.evaluate(x_test2, x_test2)
predictions2 = model2.predict(x_test2)

psnr2 = 10*math.log10(1/test_loss2)


print("Loss = ", test_loss2)
print("Accuracy = ", test_accuracy2)
print("Average PSNR = ", psnr2)


# Load and preprocess Fashion MNIST data
fashion_mnist = keras.datasets.fashion_mnist
(x_train3, y_train3), (x_test3, y_test3) = fashion_mnist.load_data()
x_train3, x_test3 = x_train3 / 255.0, x_test3 / 255.0  # Normalize pixel values

''''''''''''
P = 200

# Build the autoencoder model 
model3 = Sequential() 
model3.add(Flatten(input_shape=(M, N)))  # Input layer
model3.add(Dense(P, activation='relu'))   # Compressed layer
model3.add(Dense(M * N * T, activation='relu'))  # Expansion layer
model3.add(Dense(M * N, activation='sigmoid'))  # Output layer
model3.add(Reshape(target_shape=(M, N)))  # Reshape layer 

# Compile the model
model3.compile(optimizer='adam', loss='mean_squared_error', metrics=['accuracy'])

# Train the model
model3.fit(x_train3, x_train3, epochs=10, batch_size=64)

# returns the loss and accuracy given a test
test_loss3, test_accuracy3 = model3.evaluate(x_test3, x_test3)
# returns the predicted image set based on a given test
predictions3 = model3.predict(x_test3)

psnr3 = 10*math.log10(1/test_loss3)


print("Loss = ", test_loss3)
print("Accuracy = ", test_accuracy3)
print("Average PSNR = ", psnr3)

''''''''''''
# Create figure with one image from each class
fig, axes = plt.subplots(4, 10, figsize=(2*10,2*4)) #4 rows, 10 columns

for i in range(10):
    ax = axes[0, i]
    ax.imshow(x_test[i], cmap='gray')
    
for i in range(10):
    ax = axes[1, i]
    ax.imshow(predictions[i], cmap='gray')

for i in range(10):
    ax = axes[2, i]
    ax.imshow(predictions2[i], cmap='gray')

for i in range(10):
    ax = axes[3, i]
    ax.imshow(predictions3[i], cmap='gray')

plt.tight_layout()
plt.show()
