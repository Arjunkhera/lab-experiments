# import the required modules
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import csv
import sys

class mcpitts:

    def __init__(self,filename,w1,w2,threshold):

        # read the input from excel file
        excel_file = filename
        dataframe = pd.read_excel(excel_file)

        # Convert the dataframe into lists for analysis
        self.feature1 = dataframe['x1'].tolist()
        self.feature2 = dataframe['x2'].tolist()
        self.actualop = dataframe['y'].tolist()

        # Set the weights and activation value
        self.w1 = w1
        self.w2 = w2
        self.threshold = threshold

    def calculate(self):

        # Obtain output by multiplying inputs and weights
        self.op = [ (self.feature1[i]*self.w1+self.feature2[i]*self.w2) for i in range(4) ]

        # Apply the activation function
        self.finalop = [ 1 if x >= self.threshold else 0 for x in self.op ]

        return self.finalop

    def display(self):
        print("Model outputs : ")
        print(self.finalop)

if __name__ == '__main__':

    filename = sys.argv[1]
    w1 = int(sys.argv[2])
    w2 = int(sys.argv[3])
    threshold = int(sys.argv[4])

    mc = mcpitts(filename,w1,w2,threshold)
    mc.calculate()
    mc.display()
