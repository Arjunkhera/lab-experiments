# import the required modules
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import csv
import hebb
import sys

def hebband():
    # path to the input file
    filename = "./inputs/bipolar-and.xlsx"
    # taking the threshold value
    threshold = 0
    # assuming True
    todraw = True

    hb = hebb.hebb(filename,threshold,todraw)
    finalop = hb.calculate()
    hb.displayresults()

def hebbnand():
    # path to the input file
    filename = "./inputs/bipolar-nand.xlsx"
    # taking the threshold value
    threshold = 0
    # assuming True
    todraw = True

    hb = hebb.hebb(filename,threshold,todraw)
    finalop = hb.calculate()
    hb.displayresults()

def hebbor():
    # path to the input file
    filename = "./inputs/bipolar-or.xlsx"
    # taking the threshold value
    threshold = 0
    # assuming True
    todraw = True

    hb = hebb.hebb(filename,threshold,todraw)
    finalop = hb.calculate()
    hb.displayresults()

def hebbnor():
    # path to the input file
    filename = "./inputs/bipolar-nor.xlsx"
    # taking the threshold value
    threshold = 0
    # assuming True
    todraw = True

    hb = hebb.hebb(filename,threshold,todraw)
    finalop = hb.calculate()
    hb.displayresults()

if __name__ == '__main__':

    print("Training AND on Hebb")
    hebband()
    print("-------End of example------\n")

    print("Training NAND on Hebb")
    hebbnand()
    print("-------End of example------\n")

    print("Training OR on Hebb")
    hebbor()
    print("-------End of example------\n")

    print("Training NOR on Hebb")
    hebbnor()
    print("-------End of example------\n")
