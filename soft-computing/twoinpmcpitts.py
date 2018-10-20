# import the required modules
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import csv
import sys

def readinput():
    
    # read the input from excel file 
    excel_file = './inputs/binary-and.xlsx'
    dataframe = pd.read_excel(excel_file)
    
    # Convert the dataframe into lists for analysis
    feature1 = dataframe['x1'].tolist()
    feature2 = dataframe['x2'].tolist()
    actualop = dataframe['y'].tolist()
    
    return feature1, feature2, actualop

def getweights():
    
    # Ask the user for weights and activation values
    # w1 = int(input("Enter the first weight : "))
    # w2 = int(input("Enter the first weight : "))
    # act = int(input("Enter the threshold value : "))
    
    w1 = int(sys.argv[1])
    w2 = int(sys.argv[2])
    act = int(sys.argv[3])
 
    return w1 , w2, act

def calculate(feature1,feature2):
    
    # Obtain the weights
    w1, w2, act = getweights()
    
    # Obtain output by multiplying inputs and weights
    op = [ (feature1[i]*w1+feature2[i]*w2) for i in range(4) ]

    # Apply the activation function
    finalop = [ 1 if x >= act else 0 for x in op ]

    return finalop

if __name__ == '__main__':
    
    feature1, feature2, actualop = readinput()
    
    # start the model
    finalop = calculate(feature1,feature2)

    if finalop != actualop:
        print("Please make changes and try again")
    else :
        print("The output of the model matches the expected output")
