#!/bin/bash

make all

python ./moveObjs.py

make run

./Build/Thesis.out