# Package imports
import matplotlib.pyplot as plt
import numpy as np
import sklearn
import sklearn.datasets
import sklearn.linear_model
import matplotlib

# Display plots inline and change default figure size
matplotlib.rcParams['figure.figsize'] = (10.0, 8.0)

# Initialize random seed - for reproducibility. DO NOT CHANGE
np.random.seed(0)

# Generate a dataset and plot it
X, y = sklearn.datasets.make_moons(500, noise=0.22, random_state=0)
plt.scatter(X[:,0], X[:,1], s=40, c=y, cmap=plt.cm.Spectral)

# This function will plot the decision boundary of your classifier. Don't touch it :)
def plot_decision_boundary(pred_func):
    # Set min and max values and give it some padding
    x_min, x_max = X[:, 0].min() - .5, X[:, 0].max() + .5
    y_min, y_max = X[:, 1].min() - .5, X[:, 1].max() + .5
    h = 0.01
    # Generate a grid of points with distance h between them
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
    # Predict the function value for the whole gid
    Z = pred_func(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)
    # Plot the contour and training examples
    plt.contourf(xx, yy, Z, cmap=plt.cm.Spectral)
    plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.Spectral)

def sigmoid(a):
    return 1 / (1 + np.exp(-a))

def sigmoid_derivative(a):
    return sigmoid(a)*(1 - sigmoid(a))

def predict(model, X):
    W1, b1, W2, b2, W3, b3 = model['W1'], model['b1'], model['W2'], model['b2'], model['W3'], model['b3']    
    Z1 = X.dot(W1) + b1
    A1 = sigmoid(Z1)
    Z2 = A1.dot(W2) + b2
    A2 = sigmoid(Z2)
    Z3 = A2.dot(W3) + b3
    A3 = sigmoid(Z3)
    classify = np.vectorize(lambda x: 1 if x > 0.5 else 0)
    return classify(A3)

def calculate_loss(model, data):
    X, y = data[0], data[1]
    W1, b1, W2, b2, W3, b3 = model['W1'], model['b1'], model['W2'], model['b2'], model['W3'], model['b3']
    y_hat = predict(model, X)
    return float(np.sum(np.absolute(y[:, np.newaxis] - y_hat))) / len(X)

def train_nn(data, h1_dim, h2_dim, learning_rate=0.01, num_epochs=5000, verbose=False):
    X, y = data[0], data[1]
    
    num_examples = len(X)        # training set size
    input_dim = 2                # number of neurons in the input layer
    output_dim = 1               # number of neurons in the output layer
      
    # Initialize the parameters to random values. We need to learn these.
    W1 = np.random.randn(input_dim, h1_dim) / np.sqrt(input_dim)
    b1 = np.zeros((1, h1_dim))
    W2 = np.random.randn(h1_dim, h2_dim) / np.sqrt(h2_dim)
    b2 = np.zeros((1, h2_dim))
    W3 = np.random.randn(h2_dim, output_dim) / np.sqrt(output_dim)
    b3 = np.zeros((1, output_dim))
    
    # This is what we return at the end. UPDATE THIS AFTER EACH ITERATION
    model = { 'W1': W1, 'b1': b1, 'W2': W2, 'b2': b2, 'W3' : W3, 'b3' : b3}    
    for i in range(0, num_epochs):
        Z1 = X.dot(W1) + b1
        A1 = sigmoid(Z1)
        Z2 = A1.dot(W2) + b2
        A2 = sigmoid(Z2)
        Z3 = A2.dot(W3) + b3
        A3 = sigmoid(Z3)
        classify = np.vectorize(lambda x: 1 if x > 0.5 else 0)
        y_hat = classify(A3)
        if i % 100 == 0 and verbose:
            print(float(np.sum(np.absolute(y_hat - y[:, np.newaxis]))) / len(X))
        # Update the 3rd layer
        d4 = (A3 - y[:, np.newaxis]) * sigmoid_derivative(Z3)
        dW3 = A2.T.dot(d4)
        W3 = W3 - learning_rate * dW3
        db3 = np.sum(d4, axis=0)
        b3 = b3 - learning_rate * db3
        # Update the 2nd layer
        d3 = d4.dot(W3.T) * sigmoid_derivative(Z2)
        dW2 = A1.T.dot(d3)
        W2 = W2 - learning_rate * dW2
        db2 = np.sum(d3, axis=0)
        b2 = b2 - learning_rate * db2
        # Update the 1st layer
        d2 = d3.dot(W2.T) * sigmoid_derivative(Z1)
        dW1 = X.T.dot(d2)
        W1 = W1 - learning_rate * dW1
        db1 = np.sum(d2, axis=0)
        b1 = b1 - learning_rate * db1
        model['W1'], model['b1'], model['W2'], model['b2'], model['W3'], model['b3'] = W1, b1, W2, b2, W3, b3 
    return model

# Build a model 
data = [X,y]
model = train_nn(data, 50, 50, verbose=True)

# Plot the decision boundary
plot_decision_boundary(lambda x: predict(model, x))
plt.title("Decision Boundary for hidden layers of sizes 2 and 2")
plt.show()
