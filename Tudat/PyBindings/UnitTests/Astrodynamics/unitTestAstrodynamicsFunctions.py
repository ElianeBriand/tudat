import unittest

import PyTudat as ptd
import numpy as np
import math

floatingPointPlaceTolerance = 7  # Assert check to 7 decimal places


class TestAstrodynamicsFunctions(unittest.TestCase):
    # See unitAstrodynamicsFunctions.cpp for the sources of the various test values

    keplerianElements = ptd.Vector6d.Zero()
    earthGravitationalParameter = ptd.constants.GRAVITATIONAL_CONSTANT * 5.9736e24

    def setUp(self):
        self.keplerianElements[0] = 25999.683025291e3
        self.keplerianElements[1] = 0.864564003552322
        self.keplerianElements[5] = 0.757654217738482

    def test_KeplerOrbitalPeriod(self):
        satelliteMass = 1.0e3
        earthGravitationalParameter = ptd.constants.GRAVITATIONAL_CONSTANT * 5.9736e24
        distanceBetweenSatelliteAndEarth = 4.2164e7

        orbitalPeriod = ptd.computeKeplerOrbitalPeriod(distanceBetweenSatelliteAndEarth,
                                                                     earthGravitationalParameter,
                                                                     satelliteMass)

        expectedOrbitalPeriod = 86164.09054

        self.assertAlmostEqual(
            orbitalPeriod / expectedOrbitalPeriod,
            1.0,
            places=5)

    def test_KeplerRadialDistance(self):
        radialDistance1 = ptd.computeKeplerRadialDistance(self.keplerianElements[0],
                                                                        self.keplerianElements[1],
                                                                        self.keplerianElements[5])
        radialDistance2 = ptd.computeKeplerRadialDistance(self.keplerianElements)

        expectedRadialDistance = 4032815.56442827

        self.assertAlmostEqual(
            radialDistance1 / expectedRadialDistance,
            1.0,
            places=5)

        self.assertAlmostEqual(
            radialDistance2 / expectedRadialDistance,
            1.0,
            places=floatingPointPlaceTolerance)

    def test_KeplerAngularMomentum(self):
        satelliteMass = 1.0e3

        distanceBetweenSatelliteAndEarth = 4.2164e7
        eccentricityOfSatelliteOrbit = 0.0

        angularMomentum = ptd.computeKeplerAngularMomentum(
            distanceBetweenSatelliteAndEarth, eccentricityOfSatelliteOrbit,
            self.earthGravitationalParameter, satelliteMass)

        expectedAngularMomentum = satelliteMass * distanceBetweenSatelliteAndEarth * math.sqrt(
            self.earthGravitationalParameter / distanceBetweenSatelliteAndEarth)

        self.assertAlmostEqual(
            angularMomentum / expectedAngularMomentum,
            1.0,
            places=floatingPointPlaceTolerance)

    def test_KeplerOrbitalVelocity(self):
        orbitalVelocity1 = ptd.computeKeplerOrbitalVelocity(
            self.keplerianElements[0], self.keplerianElements[1], self.keplerianElements[5],
            self.earthGravitationalParameter)
        orbitalVelocity2 = ptd.computeKeplerOrbitalVelocity(
            self.keplerianElements, self.earthGravitationalParameter)

        expectedOrbitalVelocity = 13503.4992923871

        self.assertAlmostEqual(
            orbitalVelocity1 / expectedOrbitalVelocity,
            1.0,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            orbitalVelocity2 / expectedOrbitalVelocity,
            1.0,
            places=floatingPointPlaceTolerance)

    def test_MeanMotion(self):
        satelliteMass = 1.0e3

        distanceBetweenSatelliteAndEarth = 4.2164e7

        meanMotion = ptd.computeKeplerMeanMotion(
            distanceBetweenSatelliteAndEarth, self.earthGravitationalParameter, satelliteMass)

        expectedMeanMotion = 7.2921e-5

        self.assertAlmostEqual(
            meanMotion / expectedMeanMotion,
            1.0,
            places=5)
