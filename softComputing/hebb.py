# import the required modules
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import sys
import csv

class graph:

    def __init__(self):

        # Set properties of the graph
        plt.axis([-3,3,-3,3])
        plt.grid(True)
        plt.xlabel("X axis")
        plt.ylabel("Y axis")
        plt.title("Linear Separability for current weights")

        # Plot the x and y axis
        plt.axhline(linewidth = 1, color='black')
        plt.axvline(linewidth = 1, color='black')

    def plotpoints(self,training_data,actualop):

        # Plot of input values
        # Positive values are red and cross
        # Negative values are blue and circled
        for x in range(4):
            if(actualop[x] > 0):
                plt.plot(training_data[x][0],training_data[x][1],'rx')
            else :
                plt.plot(training_data[x][0],training_data[x][1],'bo')

    def draw(self,weights,it,isLast=False):

        # Plot the lines for every iteration
        axes = plt.gca()
        x_vals = np.array(axes.get_xlim())

        if(weights[1] == 0):
            return None

        slope = (-weights[0] / weights[1])
        intercept = (-weights[2] / weights[1])

        # iteration number
        s = "{}".format(it)

        # y coordinate
        y_vals = intercept + slope * x_vals

        if(isLast):
            plt.plot(x_vals, y_vals,color='black', linewidth=2.0)
        else:
            plt.plot(x_vals, y_vals, '--')

        # show the iteration number
        plt.text(x_vals[0],y_vals[0],s,fontsize=12)

    def showandsave(self,name=None):

        # store the figure
        plt.savefig('./figures/modelplot.png')
        # show the graph
        plt.show()

class hebb:

    def __init__(self,filename,threshold=0,todraw=True):

        # Set the threshold value
        self.threshold = threshold
        # Set the draw variable
        self.todraw = todraw

        # read the input from excel file
        excel_file = filename
        dataframe = pd.read_excel(excel_file)

        # find out the number of features
        self.no_features = len(dataframe.columns) - 1
        # find out the number of inputs
        self.no_rows = len(dataframe.index)

        # Convert the dataframe into lists for analysis
        self.training_data = [ dataframe.iloc[i,:self.no_features].tolist() for i in range(self.no_rows) ]
        # Obtain the output in a separate list
        self.actual_op = dataframe['y'].tolist()

        # Initialize the weights and bias as zero
        self.weights = [ 0 for x in range(self.no_features)]
        self.bias = 0


    def displayresults(self):
        # Display the results of the model
        print("The weights are : ")
        print(self.weights+[self.bias])
        print("---------------------")

    def calculate(self):

        if(self.todraw):
            g = graph()
            g.plotpoints(self.training_data,self.actual_op)

        # Learn weights using Hebb Model
        for x in range(self.no_rows):
            for y in range(self.no_features):
                self.weights[y] += self.training_data[x][y]*self.actual_op[x]
            self.bias += 1*self.actual_op[x]

            # redraw the graph
            if(self.todraw):
                g.draw(self.weights+[self.bias],x)

        # redraw the final line
        if(self.todraw):
            g.draw(self.weights+[self.bias],self.no_features,True)
            g.showandsave()

        # Obtain output by multiplying inputs and weights
        yin = (np.sum((np.array(self.training_data)*np.array(self.weights)),axis=1)+np.array(self.bias)).tolist()

        # Apply the activation function
        self.finalop = [ 1 if x >= self.threshold else -1 for x in yin ]

        return self.finalop

if __name__ == '__main__':

    filename = sys.argv[1]
    threshold = int(sys.argv[2])
    todraw = bool(sys.argv[3])

    hb = hebb(filename,threshold,todraw)
    hb.calculate()
    hb.displayresults()
