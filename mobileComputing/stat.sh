#!/bin/bash

echo "Running the awk script"
awk -f "${1}experiment.awk" "out.tr"
