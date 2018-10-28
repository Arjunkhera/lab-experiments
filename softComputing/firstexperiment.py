# import the required modules
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import csv
import hebb
import sys

if __name__ == '__main__':

    # path to the input file
    filename = sys.argv[1]
    threshold = int(sys.argv[2])
    todraw = bool(sys.argv[3])

    hb = hebb.hebb(filename,threshold,todraw)
    finalop = hb.calculate()
    hb.displayresults()

    if finalop != actualop:
        print("Single Layer Hebb wont work for this model")
    else :
        print("The output of the model matches the expected output")
