import unittest

import PyTudat as ptd
import numpy as np
import math

floatingPointPlaceTolerance = 7  # Assert check to 7 decimal places


class TestMeanToEccentricAnomaly(unittest.TestCase):

    # See unitTestPhysicalConstants.cpp for the sources of the various test values

    def test_convertMeanAnomalyToEccentricAnomaly_circular(self):
        testEccentricity = 0.0
        testMeanAnomaly = 1.0472

        referenceEccentricAnomaly = 1.0472

        eccentricAnomaly = ptd.convertMeanAnomalyToEccentricAnomaly(testEccentricity, testMeanAnomaly)

        self.assertAlmostEqual(
            eccentricAnomaly / referenceEccentricAnomaly,
            1.0,
            places=floatingPointPlaceTolerance)

        # Checking the overloads :

        eccentricAnomaly = ptd.convertMeanAnomalyToEccentricAnomaly(aMeanAnomaly=testMeanAnomaly,eccentricity=testEccentricity)

        self.assertAlmostEqual(
            eccentricAnomaly / referenceEccentricAnomaly,
            1.0,
            places=floatingPointPlaceTolerance)

        eccentricAnomaly = ptd.convertMeanAnomalyToEccentricAnomaly(aMeanAnomaly=testMeanAnomaly,useDefaultInitialGuess=True,eccentricity=testEccentricity)

        self.assertAlmostEqual(
            eccentricAnomaly / referenceEccentricAnomaly,
            1.0,
            places=floatingPointPlaceTolerance)

    def test_convertMeanAnomalyToEccentricAnomaly_range(self):
        arrayOfTestEccentricities = [0.01671, 0.43582, 0.78514, 0.91525]

        arrayOfTestMeanAnomalies = [ptd.units.convertDegreesToRadians(60.0),
                                    ptd.units.convertDegreesToRadians(90.0),
                                    ptd.units.convertDegreesToRadians(120.0),
                                    ptd.units.convertDegreesToRadians(220.0)]

        arrayOfReferenceEccentricAnomalies = [1.06178920406832,
                                              1.97200731113253,
                                              2.5392410896466,
                                              3.51006218528448]

        for i in range(4):
            eccentricAnomaly = ptd.convertMeanAnomalyToEccentricAnomaly(
                arrayOfTestEccentricities[i], arrayOfTestMeanAnomalies[i])
            self.assertAlmostEqual(
                eccentricAnomaly / arrayOfReferenceEccentricAnomalies[i],
                1.0,
                places=floatingPointPlaceTolerance)

    def test_convertMeanAnomalyToEccentricAnomaly_TooHigh(self):
        testEccentricity = 2.0
        testMeanAnomaly = 1.0472

        with self.assertRaises(RuntimeError):
            ptd.convertMeanAnomalyToEccentricAnomaly(testEccentricity, testMeanAnomaly)

    def test_convertMeanAnomalyToEccentricAnomaly_nearParabolic(self):
        testEccentricity = 1.0 - 1.0e-15

        arrayOfTestMeanAnomalies = [0.0,
                                    1.0e-10,
                                    0.5,
                                    math.pi / 2 - 1.0e-10,
                                    math.pi / 2,
                                    math.pi / 2 + 1.0e-10,
                                    2.5,
                                    math.pi - 1.0e-10,
                                    math.pi,
                                    math.pi + 1.0e-10,
                                    4.0,
                                    3.0 / 2.0 * math.pi - 1.0e-10,
                                    3.0 / 2.0 * math.pi,
                                    3.0 / 2.0 * math.pi + 1.0e-10,
                                    5.5,
                                    2.0 * math.pi - 1.0e-10,
                                    2.0 * math.pi]

        arrayOfExpectedEccentricAnomalies = [0.0,
                                             0.000843432672832182,
                                             1.49730038909589,
                                             2.30988145995031,
                                             2.30988146001006,
                                             2.30988146006981,
                                             2.81798706288006,
                                             3.14159265353979,
                                             3.14159265358979,
                                             3.14159265363979,
                                             3.57764001198758,
                                             3.97330384710978,
                                             3.97330384722928,
                                             3.97330384722972,
                                             4.51869928040234,
                                             6.28234187379524,
                                             0.0]

        eccentricAnomaly = ptd.convertMeanAnomalyToEccentricAnomaly(testEccentricity, arrayOfTestMeanAnomalies[0])

        self.assertLess(eccentricAnomaly, 1.0E-9)

        eccentricAnomaly = ptd.convertMeanAnomalyToEccentricAnomaly(testEccentricity, arrayOfTestMeanAnomalies[16])

        self.assertLess(eccentricAnomaly, 1.0E-9)

        for i in range(1, 16):
            eccentricAnomalyLoop = ptd.convertMeanAnomalyToEccentricAnomaly(testEccentricity,
                                                                            arrayOfTestMeanAnomalies[i])
            self.assertAlmostEqual(
                eccentricAnomalyLoop / arrayOfExpectedEccentricAnomalies[i],
                1.0,
                places=floatingPointPlaceTolerance)

    def test_convertMeanAnomalyToHyperbolicEccentricAnomaly_range(self):
        arrayOfTestEccentricities = [ 1.03, 1.28, 1.97, 2.56, 10.87, 99.72]

        arrayOfTestMeanAnomalies = [1.5, 6.0, 0.5, -4.0, 5.5, 2.5]

        arrayOfReferenceEccentricAnomalies = [1.9132897042137,
                                              2.60400218106873,
                                              0.478057581067141,
                                              -1.50971422579796,
                                              0.529595060186511,
                                              0.0253214157050963]

        for i in range(6):
            eccentricAnomaly = ptd.convertMeanAnomalyToHyperbolicEccentricAnomaly(
                arrayOfTestEccentricities[i], arrayOfTestMeanAnomalies[i])
            self.assertAlmostEqual(
                eccentricAnomaly / arrayOfReferenceEccentricAnomalies[i],
                1.0,
                places=floatingPointPlaceTolerance)