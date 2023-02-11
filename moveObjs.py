import os
import shutil

objs = []
objs += [each for each in os.listdir(".") if each.endswith('.o')]

pdb = []
pdb += [each for each in os.listdir(".") if each.endswith('.pdb')]

try:
    for val in pdb:
        os.remove("./" + str(val))

finally:
    for element in objs:
        if (str(element) in os.listdir("./.objs")):
            os.remove("./.objs/" + str(element))
        
        shutil.move("./" + str(element), "./.objs/" + str(element))