#!/bin/bash

make partial ARGS="$@"

python ./moveObjs.py

make run

./Build/Thesis.out