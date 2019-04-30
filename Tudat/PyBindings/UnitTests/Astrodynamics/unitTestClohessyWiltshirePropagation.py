import unittest

import PyTudat as ptd
import numpy as np
import math

floatingPointPlaceTolerance = 7  # Assert check to 7 decimal places


class TestClohessyWiltshirePropagation(unittest.TestCase):

    def test_ClohessyWiltshirePropagation_fullState (self):
        # See the C++ unit test for details (unitTestClohessyWiltshirePropagator.cpp)

        centralBodyGravitationalParameter = 3.986004418e14

        propagationDuration = 1800.0

        referenceOrbitRadius = 6.778137e6

        initialState = ptd.Vector6d(45.0, 37.0, 12.0, 0.08, 0.03, 0.01)

        computedFinalState = ptd.propagateClohessyWiltshire(
            initialState,
            propagationDuration,
            centralBodyGravitationalParameter,
            referenceOrbitRadius )

        expectedFinalState = ptd.Vector6d(3.806450080201250e2,
                                            -5.437424675454679e2, 2.509547637285142,
                                            1.541620605755606e-1, -7.294751390499470e-1,
                                            -1.662099488431618e-2)

        self.assertAlmostEqual(computedFinalState[0], expectedFinalState[0], places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(computedFinalState[1], expectedFinalState[1], places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(computedFinalState[2], expectedFinalState[2], places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(computedFinalState[3], expectedFinalState[3], places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(computedFinalState[4], expectedFinalState[4], places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(computedFinalState[5], expectedFinalState[5], places=floatingPointPlaceTolerance)

    def test_ClohessyWiltshirePropagation_harmonicMotion (self):
        # See the C++ unit test for details (unitTestClohessyWiltshirePropagator.cpp)

        centralBodyGravitationalParameter = 3.986004418e14

        referenceOrbitRadius = 6.778137e6

        meanAngularMotion = math.sqrt( centralBodyGravitationalParameter
                                       / ( referenceOrbitRadius * referenceOrbitRadius
                                           * referenceOrbitRadius ) )

        propagationDuration = 2.0 * math.pi / meanAngularMotion

        initialState = ptd.Vector6d( 34.0, 49.0 , 17.0,
                              0.5 * meanAngularMotion * 49.0,
                              -2.0 * meanAngularMotion * 34.0, 0.04 )

        computedFinalState = ptd.propagateClohessyWiltshire(
            initialState,
            propagationDuration,
            centralBodyGravitationalParameter,
            referenceOrbitRadius )


        self.assertAlmostEqual(computedFinalState[0], initialState[0], places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(computedFinalState[1], initialState[1], places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(computedFinalState[2], initialState[2], places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(computedFinalState[3], initialState[3], places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(computedFinalState[4], initialState[4], places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(computedFinalState[5], initialState[5], places=floatingPointPlaceTolerance)