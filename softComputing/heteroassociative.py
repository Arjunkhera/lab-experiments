# import the required modules
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import csv
import sys

class heteroassociative:

    def __init__(self,filename,features,threshold):

        # store number of features
        self.num_features = features
        # store the threshold value
        self.threshold = threshold

        # read the input from excel file
        excel_file = filename
        # convert it into a pandas dataframe
        dataframe = pd.read_excel(excel_file)

        # Convert dataframe to numpy array
        self.wholeset = dataframe.values
        # Separate the inputs and outputs
        self.train_data = self.wholeset[:,:self.num_features]
        self.train_op = self.wholeset[:,self.num_features:]

    def train(self):
        # calculate the associative weights
        self.weights = (self.train_data.T)@(self.train_op)

    def test(self):
        # calculate the results
        self.op = self.train_data@self.weights

        # apply the activation function to the op
        self.op = self.op > self.threshold
        self.op = self.op.astype(int)

    def display(self):

        print("Weights : ")
        print(self.weights)

        print("Outputs : ")
        print(self.op)


if __name__ == '__main__':

    # path to the input file
    filename = sys.argv[1]
    
    features = int(sys.argv[2])
    threshold = float(sys.argv[3])

    # Initialize the model
    h = heteroassociative(filename,features,threshold)

    h.train()
    h.test()
    h.display()
