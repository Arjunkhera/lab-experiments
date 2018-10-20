# import the required modules
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import csv

def readinput(filename=None):

    # read the input from excel file
    if(filename == None):
        excel_file = './inputs/bipolar-and.xlsx'
    else:
         excel_file = filename
    dataframe = pd.read_excel(excel_file)

    # Convert the dataframe into lists for analysis
    feature1 = dataframe['x1'].tolist()
    feature2 = dataframe['x2'].tolist()
    actualop = dataframe['y'].tolist()

    return feature1, feature2, actualop

def calculate(feature1, feature2, actualop):

    # Set the initial weights as zero
    w1, w2, b = 0, 0, 0

    # to store the weights for drawing the graph
    weights = []
    weights.append([w1,w2,b])

    # Learn weights using Hebb Model
    for x in range(4):
        w1, w2, b = w1 + feature1[x]*actualop[x], w2 + feature2[x]*actualop[x], b + 1*actualop[x]
        weights.append([w1,w2,b])

    # Obtain output by multiplying inputs and weights
    op = [ w1*feature1[x] + w2*feature2[x] + b  for x in range(4)]

    # Apply the activation function
    finalop = [ 1 if x >= 0 else -1 for x in op ]
    # store the final weights
    finalweights = [w1,w2,b]

    return actualop, finalop, weights,finalweights

# function to calculate slope and intercept for every iteration
def linefunc(weights):
    slope = []
    intercept = []

    for x in range(1,5):
        if(weights[x][1] == 0):
            continue

        slope.append(-weights[x][0]/weights[x][1])
        intercept.append(-weights[x][2]/weights[x][1])

    for x,y  in zip(slope,intercept):
        yield x,y

# function to draw the graph
def drawgraph(weights,finalweights,actualop,feature1,feature2):
    # Plot of input values
    # Positive values are red and cross
    # Negative values are blue and circled
    for x in range(4):
        if(actualop[x] > 0):
            plt.plot(feature1[x],feature2[x],'rx')
        else :
            plt.plot(feature1[x],feature2[x],'bo')

    # Properties of the graph
    plt.axis([-3,3,-3,3])
    plt.grid(True)
    plt.xlabel("X axis")
    plt.ylabel("Y axis")
    plt.title("Linear Separability for current weights")

    # Plot the x and y axis
    plt.axhline(linewidth = 1, color='black')
    plt.axvline(linewidth = 1, color='black')

    # Plot the lines for every iteration
    axes = plt.gca()
    x_vals = np.array(axes.get_xlim())

    # Obtain the handle for the generator function
    gen = linefunc(weights)
    gen.send(None)
    it = 1

    # Use slope and itercept for every iteration to plot the graph
    for i in gen:
        # iteration number
        s = "{}".format(it)

        # y coordinate
        y_vals = i[1] + i[0] * x_vals
        plt.plot(x_vals, y_vals, '--')
        # show the iteration number
        plt.text(x_vals[0],y_vals[0],s,fontsize=12)
        it += 1

    # redraw the final linear separable line in solid black
    sl = -finalweights[0]/finalweights[1]
    inte = -finalweights[2]/finalweights[1]
    y_vals = inte + sl * x_vals
    plt.plot(x_vals, y_vals,color='black', linewidth=2.0)
    plt.text(x_vals[0],y_vals[0],s,fontsize=12)


    # store the figure
    plt.savefig('modelplot.png')
    # show the plot
    plt.show()

# main function
if __name__ == '__main__':

    feature1, feature2, actualop = readinput()

    # start the model
    actualop, finalop, weights, finalweights = calculate(feature1,feature2,actualop)

    if finalop != actualop:
        print("Single Layer Hebb wont work for this model")
    else :
        print("The output of the model matches the expected output")

    # draw the graph
    drawgraph(weights,finalweights,actualop,feature1,feature2)
