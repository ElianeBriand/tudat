import PyTudat as ptd
import numpy as np
import random


#
# This is the tudat example application, in Python
#

random.seed(154)

altitude_km = random.uniform(0.0, 10.0)

altitude_m = ptd.units.convertKilometersToMeters(altitude_km)

positionAttractedBody = ptd.Vector3d(1737.1e3 + altitude_m, 0.0, 0.0)

positionAttractingBody = ptd.Vector3d.Zero()


v = ptd.Vector3d()
v.x = 1
v.y = 2.0
v.z = 3.1
print("x = {0} y = {1} z = {2}".format(v.x,v.y,v.z))


for i,val in enumerate(v):
    print("v[{0}] = {1}".format(i,val))



