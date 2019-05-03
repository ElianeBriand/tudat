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

gravitationalAcceleration = ptd.CentralGravity.computeGravitationalAcceleration(
    positionAttractedBody, 4.9e12,
    positionAttractingBody)

print("")

print("Hello world!")
print("I am floating {0} km above the Moon's surface.".format(altitude_km))
print("The gravitational acceleration here is {0}".format(gravitationalAcceleration.norm()))

settingsmap = ptd.getDefaultBodySettings(["Earth"])

namedbd = ptd.createBodies(settingsmap)

namedbd["Asterix"] = ptd.Body()

ptd.setGlobalFrameBodyEphemerides( namedbd, "SSB", "ECLIPJ2000" )

