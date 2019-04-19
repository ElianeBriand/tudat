# For rapid prototyping purpose
import os
import sys

sys.path.insert(0, "../../../build/tudat/Tudat/PyBindings")
##

import Tudat as td

v = td.Vector3d()
v.x = 1
v.y = 2.0
v.z = 3.1
print("x = {0} y = {1} z = {2}".format(v.x,v.y,v.z))