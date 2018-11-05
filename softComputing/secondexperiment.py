# import the required modules
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import csv
import perceptron as percep
import sys

if __name__ == '__main__':

    # path to the input file
    filename = "./inputs/bipolar-or.xlsx"
    epochs = 2
    alpha = 1
    threshold = 0
    inptype = True

    # Initialize the model
    p = percep.perceptron(filename,epochs,alpha,threshold,inptype)

    # train the model on the input
    p.calculate()
