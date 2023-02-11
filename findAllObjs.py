import os
import os.path
import sys

path = str(os.path.dirname(os.path.abspath(__file__))) + "/.objs/"

objs = []
objs += [each[:-2] for each in os.listdir("./.objs") if each.endswith('.o')]

objs = [path + val + ".o" for val in objs]

for val in objs:
    print(val)