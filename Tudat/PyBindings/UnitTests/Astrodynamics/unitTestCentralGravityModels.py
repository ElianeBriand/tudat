import unittest

import PyTudat as ptd
import numpy as np
import math

floatingPointPlaceTolerance = 7  # Assert check to 7 decimal places


class TestCentralGravityModels(unittest.TestCase):
    # See unitTestCentralAndZonalGravity.cpp for the sources of the various test values

    def test_GravitationalAcceleration(self):
        gravitationalParameterOfEarth = 6.6726e-11 * 5.9742e24

        positionOfEarth = ptd.Vector3d.Zero()

        positionOnEarthSurface = ptd.Vector3d(6.3781e6, 0.0, 0.0)

        gravitationalAccelerationExertedAtEarthSurface = ptd.CentralGravity.computeGravitationalAcceleration(
            positionOnEarthSurface, gravitationalParameterOfEarth, positionOfEarth)

        self.assertAlmostEqual(
            gravitationalAccelerationExertedAtEarthSurface.norm() / 9.8,
            1.0,
            places=3)

        universalGravitationalConstant = 6.6726e-11

        massOfMoon = 7.36e22

        positionOfMoon = ptd.Vector3d(12.65, 0.23, -45.78)

        positionOfLunarSurface = ptd.Vector3d(0.0, 1735771.89, 0.0)

        gravitationalAccelerationExertedAtLunarSurface = ptd.CentralGravity.computeGravitationalAcceleration(
            universalGravitationalConstant, positionOfLunarSurface,
            massOfMoon, positionOfMoon)

        self.assertAlmostEqual(
            gravitationalAccelerationExertedAtLunarSurface.norm() / 1.63,
            1.0,
            places=6)
