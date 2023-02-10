#!/bin/bash

make partial ARGS="$@"

python ./moveObjs.py

./Build/Thesis.out