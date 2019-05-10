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

# ### C++-style interface
bodySettingsMap = ptd.getDefaultBodySettingsMap(["Earth"])

bodyMap = ptd.createBodies(bodySettingsMap)
bodyMap["Asterix"] = ptd.Body()

ptd.setGlobalFrameBodyEphemerides(bodyMap, "SSB", "ECLIPJ2000")

accelSettingsForAsterix = ptd.PerBodyAccelerationSettings()

# accelSettingsForAsterix.addAcceleration(exertingBodyName="Earth", listOfAccelerationSettings=[ptd.AvailableAcceleration.point_mass_gravity])
accelSettingsForAsterix.addAcceleration(exertingBodyName="Earth",
                                        accelerationType=ptd.AvailableAcceleration.point_mass_gravity)

accelMap = ptd.FullAccelerationMap()
accelMap["Asterix"] = accelSettingsForAsterix

modelAccelerationMap = ptd.createAccelerationModelsMap(bodyMap=bodyMap,
                                                       fullAccelerationMap=accelMap,
                                                       propagatedBodiesList=["Asterix"],
                                                       centralBodiesList=["Earth"])

# Starting conditions for asterix

# Either compose the vector from indices
# asterixInitialState = ptd.Vector6d.Zero()
# asterixInitialState[ptd.KeplerianElementIndices.semiMajorAxisIndex] = 7500.0e3

# or use a helper function
asterixInitialStateKepl = ptd.fromKeplerianElements(semiMajorAxis=7500.0e3,
                                                    eccentricity=0.1,
                                                    inclination=ptd.units.convertDegreesToRadians(85.3),
                                                    argumentOfPeriapsis=ptd.units.convertDegreesToRadians(235.7),
                                                    longitudeOfAscendingNode=ptd.units.convertDegreesToRadians(23.4),
                                                    trueAnomaly=ptd.units.convertDegreesToRadians(139.87))

earthGravitationalParameter = bodyMap["Earth"].getGravityFieldModel().getGravitationalParameter()
systemInitialState = ptd.convertKeplerianToCartesianElements(asterixInitialStateKepl,
                                                             earthGravitationalParameter)



# ### Wrapper interface
p = ptd.PropagationHelper()
p.populateWithCommonlyUsedBodies(["Earth"])

asterix = p.createBody("Asterix")
asterix.addAcceleration(exertingBodyName="Earth", accelerationType=ptd.AvailableAcceleration.point_mass_gravity)

p.setupPropagation(propagatedBodiesList=["Asterix"],
                   centralBodiesList=["Earth"])
