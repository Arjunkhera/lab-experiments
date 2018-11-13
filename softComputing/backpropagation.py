# import the required modules
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import math
import random
import string
import csv
import sys

class BackPropagation():

    def __init__(self,networkFile="./inputs/structure.xlsx",dataFile="./inputs/backprop.xlsx",outputClasses=1,epochs=1000,alpha=0.1):

        # no of output classes of the network
        self.outputClasses = outputClasses
        # number of epochs
        self.epochs = epochs
        # value of learning rate
        self.alpha = alpha
        # to obtain random seeds
        np.random.seed(1)

        # Call the input function to obtain the number of nodes of each layer
        self.networkExtract(networkFile)
        # Call the input function to obtain the input values from training set
        self.dataExtract(dataFile)

        # number of hidden layers in the network
        self.noHiddenLayers = len(self.nodesPerLayer)
        # add the first and last layer node counts
        self.nodesPerLayer = [self.no_features] + self.nodesPerLayer + [self.outputClasses]
        # total number of layers in the network
        self.totalLayers = len(self.nodesPerLayer)

        # initialize the structure for the neural net
        self.initialize()

        # to store the cost function for each epoch
        self.totalerror = []

    # Obtain the network structure
    def networkExtract(self,networkFile:str) -> None:

        # read the input from excel file
        excel_file = networkFile
        # convert it into a pandas dataframe
        dataframe = pd.read_excel(excel_file)
        # stores the number of nodes in every layer
        self.nodesPerLayer = dataframe.columns.tolist()

    # Obtain the training data
    def dataExtract(self,dataFile:str) -> None:

        # read the input from excel file
        excel_file = dataFile
        # convert it into a pandas dataframe
        dataframe = pd.read_excel(excel_file)
        # find out the number of features
        self.no_features = len(dataframe.columns) - 1
        # find out the number of inputs
        self.no_rows = len(dataframe.index)

        # Convert the dataframe into numpy array for analysis
        self.training_data = np.array([ dataframe.iloc[i,:self.no_features].tolist() for i in range(self.no_rows) ])
        # Obtain the output in a separate numpy column vector
        self.actual_op = np.array([dataframe['y'].tolist()]).T

    # define and set the weight matrices
    def initialize(self) -> None:

        self.weights = []
        # construct the weight matrices
        for i in range(self.totalLayers-1):
            # initialize weights randomly with mean 0 and range [-1, 1] and add the bias node here itself
            self.weights.append(2*np.random.random((self.nodesPerLayer[i]+1,self.nodesPerLayer[i+1])) - 1)

    # train the model using backpropagation
    def train(self) -> list:
        for i in range(self.epochs):
            self.singleCycle()

        return self.returnOutput()

    # test the model
    def test(self,testinput) -> list:

        # store the testing data
        self.testing_data = testinput

        # do forward propagation
        self.forwardPropagation(True)

        # return the answers
        return self.returnOutput()

    # do the following for every epoch
    def singleCycle(self) -> None:

        # list of activations for all layers
        self.activations = []
        # do forward propagation
        self.forwardPropagation()

        # list of errors for all layers
        self.errors = []
        # do backward propagation
        self.backwardPropagation()

        # list of partial derivative matrices
        self.delta = []
        # update the weights
        self.updateWeights()


    # Forward Propogation procedure
    def forwardPropagation(self,trainortest=False) -> None:

        # to decide whether to test or train
        if(trainortest == True):
            inpData = self.testing_data
        else:
            inpData = self.training_data

        # initialize with training input
        inp = np.hstack((np.ones((inpData.shape[0], 1)),inpData))
        self.activations.append(inp)

        # Propogation for rest of the layers
        for i in range(self.totalLayers-2):
            newinp = np.hstack((np.ones((inpData.shape[0], 1)),self.sigmoid(np.dot(inp,self.weights[i]))))
            self.activations.append(newinp)
            inp = newinp
        # Do last layer separately to avoid adding bias term
        self.activations.append(self.sigmoid(np.dot(inp,self.weights[self.totalLayers-2])))

    # Backward Propogation procedure
    def backwardPropagation(self) -> None:

        # error for the output layer
        err = self.activations[self.totalLayers-1] - self.actual_op

        # errors for rest of the layers
        self.errors.append(err)
        for i in range(self.totalLayers-2,0,-1):
            newerr = self.activations[i][:,1:] * (1 - self.activations[i][:,1:]) * np.dot(err,self.weights[i].T[:,1:])
            self.errors.append(newerr)
            err = newerr

    # Update the weights learned by gradient descent
    def updateWeights(self) -> None:
        # Calculate the partial derivatives
        for i in range(self.totalLayers-1):
            self.delta.append(self.activations[i][:,:,np.newaxis] * self.errors[self.totalLayers-2-i][:,np.newaxis,:])

        # Take the average of the partial derivatives
        for i in range(self.totalLayers-1):
            self.delta[i] = np.average(self.delta[i],axis=0)

        # Update the weights
        for i in range(self.totalLayers-1):
            self.weights[i] += -self.alpha * self.delta[i]

    # sigmoid function
    def sigmoid(self,x,derivative=False):

        if (derivative == True):
            return x * (1 - x)
        else:
            return 1 / (1 + np.exp(-x))

    def returnOutput(self) -> list:
        # for single class output
        if(self.outputClasses == 1):
            self.op = (self.activations[self.totalLayers-1] >= 0.5).astype(int).tolist()
            return self.op

        # for multiclass output
        # initialize the output array
        self.op =  []

        # convert the activation values into one hot vectors for multiclass outputs
        tempArr = []
        for i in self.activations[self.totalLayers-1]:
            tempArr.append((i >= 0.5).astype(int))

        # convert the one hot vectors to required outputs
        for j in tempArr:
            self.op.append(np.argmax(j))

        return self.op

    def accuracy(self) -> float:

        match = 0
        for i in range(len(self.actual_op)):
            if self.op[i] == self.actual_op[i]:
                match += 1

        return (match/len(self.actual_op))*100.0

if __name__ == '__main__':

    # path to the neural network structure file
    networkfile = sys.argv[1]
    datafilename = sys.argv[2]

    outputClasses = int(sys.argv[3])
    epochs = int(sys.argv[4])
    alpha = float(sys.argv[5])

    # provide the path to neural network structure and input file
    backprop = BackPropagation(networkfile,datafilename,outputClasses,epochs,alpha)

    # to train the model
    print("outputs :{}".format(backprop.train()))

    # output the accuracy on training data
    print("accuracy : {}%".format(backprop.accuracy()))

    # output the activation values
    print("the activation values are : ")
    print(backprop.activations[backprop.totalLayers-1])
