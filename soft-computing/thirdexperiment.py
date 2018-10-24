# import the required modules
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import csv
import perceptron as percep
import sys

if __name__ == '__main__':

    # path to the input file
    filename = sys.argv[1]
    epochs = int(sys.argv[2])
    alpha = int(sys.argv[3])
    threshold = int(sys.argv[4])
    inptype = bool(sys.argv[5])

    # Initialize the model
    p = percep.perceptron(filename,epochs,alpha,threshold,inptype)

    # train the model on the input
    p.calculate()
