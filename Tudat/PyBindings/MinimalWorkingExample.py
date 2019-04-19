import PyTudat as ptd
import numpy as np

v = ptd.Vector3d()
v.x = 1
v.y = 2.0
v.z = 3.1
print("x = {0} y = {1} z = {2}".format(v.x,v.y,v.z))

for i,val in enumerate(v):
    print("v[{0}] = {1}".format(i,val))



