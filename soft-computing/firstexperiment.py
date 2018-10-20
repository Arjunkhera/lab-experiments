# import the required modules
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import csv
import twoinphebb as hebb
import sys

if __name__ == '__main__':

    # path to the input file
    filename = sys.argv[1]
    feature1, feature2, actualop = hebb.readinput(filename)

    # start the model
    actualop, finalop, weights, finalweights = hebb.calculate(feature1,feature2,actualop)

    if finalop != actualop:
        print("Single Layer Hebb wont work for this model")
    else :
        print("The output of the model matches the expected output")

    # draw the graph
    hebb.drawgraph(weights,finalweights,actualop,feature1,feature2)
