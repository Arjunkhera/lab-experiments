## General Instructions

1. All the models have been implemented both in jupyter notebooks and python packages.

2. Programs of Jupyter-notebooks can be run as is.

3. Python scripts are written to be implemented as packages. You will need to provide arguments while running the program. Check Specific Instructions for further details.

## Inputs

1. Inputs to the models are taken in the from of xlsx files(spreadsheet). You can modify the functions if you want to take other forms of input.

2. These xlsx files are stored in the inputs folder.

## Outputs

1. Figures are currently stored in the png format in figures folder.
2. [TODO] Store model outputs as csv files in an outputs folder

## Specific Instructions

- Input filepath always need to be provided
- Check default values before calling the module

1. **MC Pitts Model**

```bash
python twoinmcpitts.py [path to input file] [weight1] [weight2] [threshold]
```

2. **Hebb Model**

```bash
python hebb.py [path to input file] [threshold=0] [todraw=True]
```

**Note :** firstexperiment of README.md has been implemented by importing the hebb module. Hence, the same arguments are valid for firstexperiment.py too. Just change the input files while calling the script.

3. **Perceptron Model**

inptype = True for Bipolar values and False for Binary

```bash
python [path to input file] [epochs=1] [alpha=1] [threshold=0] [inptype=True] [todraw=True]
```
An example of importing the perceptron model is provided in thirdexperiment.py.

4. **Adaline Model**

```bash
python [path to input file] [epochs=1] [alpha=1] [threshold=0] [todraw=True]
```

5. **Heteroassociative Model**

```bash
python [path to input file] [number of features] [threshold=0]
```

6 **Back Propagation**

Structure excel file : write the number of nodes in every hidden layer in the first row column wise

```bash
python [path to neural structure] [path to training data] [outputClasses=1] [epochs=1000] [alpha=0.1]

# example
python backpropagation.py "./inputs/structure.xlsx" "./inputs/binary-xor.xlsx" 1 1000 0.3
```

**Note :** auto associative model is a subset of hetero associative model and can be implemented using the same program.
