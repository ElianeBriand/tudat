import unittest

import PyTudat as ptd
import numpy as np
import math

floatingPointPlaceTolerance = 5  # Assert check to 7 decimal places


class TestOrbitalElementsConversions(unittest.TestCase):

    def test_KeplerianToCartesianElementConversion_1(self):
        earthGravitationalParameter = 3.986004415e14

        keplerianElements = ptd.fromKeplerianElements(semiMajorAxis=8000.0 * 1000.0,
                                                      eccentricity=0.23,
                                                      inclination=20.6 / 180.0 * math.pi,
                                                      argumentOfPeriapsis=274.78 / 180.0 * math.pi,
                                                      longitudeOfAscendingNode=108.77 / 180.0 * math.pi,
                                                      trueAnomaly=46.11 / 180.0 * math.pi)

        expectedCartesianElements = ptd.Vector6d(2.021874804243437e6,
                                                 6.042523817035284e6,
                                                 -1.450371183512575e6,
                                                 -7.118283509842652e3,
                                                 4.169050171542199e3,
                                                 2.029066072016241e3)

        computedCartesianElements = ptd.convertKeplerianToCartesianElements(keplerianElements,
                                                                            earthGravitationalParameter)

        self.assertAlmostEqual(expectedCartesianElements[0] / computedCartesianElements[0], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[1] / computedCartesianElements[1], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[2] / computedCartesianElements[2], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[3] / computedCartesianElements[3], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[4] / computedCartesianElements[4], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[5] / computedCartesianElements[5], 1.0,
                               places=floatingPointPlaceTolerance)

    def test_KeplerianToCartesianElementConversion_2(self):
        earthGravitationalParameter = 4.2828018915e13

        keplerianElements = ptd.fromKeplerianElements(semiMajorAxis=9201.61 * 1000.0,
                                                      eccentricity=0.0,
                                                      inclination=0.0,
                                                      argumentOfPeriapsis=12.54 / 180.0 * math.pi,
                                                      longitudeOfAscendingNode=201.55 / 180.0 * math.pi,
                                                      trueAnomaly=-244.09 / 180.0 * math.pi)

        expectedCartesianElements = ptd.Vector6d(7.968828015716932e6,
                                                 -4.600804999999997e6,
                                                 0.0,
                                                 1.078703495685965e3,
                                                 1.868369260830248e3,
                                                 0.0)

        computedCartesianElements = ptd.convertKeplerianToCartesianElements(keplerianElements,
                                                                            earthGravitationalParameter)

        self.assertAlmostEqual(expectedCartesianElements[0] / computedCartesianElements[0], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[1] / computedCartesianElements[1], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual((expectedCartesianElements[2] + 0.1) / (computedCartesianElements[2] + 0.1), 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[3] / computedCartesianElements[3], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[4] / computedCartesianElements[4], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual((expectedCartesianElements[5] + 0.1) / (computedCartesianElements[5] + 0.1), 1.0,
                               places=floatingPointPlaceTolerance)

    def test_KeplerianToCartesianElementConversion_3(self):
        earthGravitationalParameter = 1.32712440018e20

        keplerianElements = ptd.fromKeplerianElements(semiMajorAxis=-4.5e11,
                                                      eccentricity=2.3,
                                                      inclination=25.5 / 180.0 * math.pi,
                                                      argumentOfPeriapsis=156.11 / 180.0 * math.pi,
                                                      longitudeOfAscendingNode=-215.03 / 180.0 * math.pi,
                                                      trueAnomaly=123.29 / 180.0 * math.pi)

        expectedCartesianElements = ptd.Vector6d(-2.776328224174438e12,
                                                 -6.053823869632723e12,
                                                 3.124576293512172e12,
                                                 7.957674684798018e3,
                                                 1.214817382001788e4,
                                                 -6.923442392618828e3)

        computedCartesianElements = ptd.convertKeplerianToCartesianElements(keplerianElements,
                                                                            earthGravitationalParameter)

        self.assertAlmostEqual(expectedCartesianElements[0] / computedCartesianElements[0], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[1] / computedCartesianElements[1], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[2] / computedCartesianElements[2], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[3] / computedCartesianElements[3], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[4] / computedCartesianElements[4], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedCartesianElements[5] / computedCartesianElements[5], 1.0,
                               places=floatingPointPlaceTolerance)

    def test_CartesianToKeplerianElementConversion_1(self):
        earthGravitationalParameter = 3.986004415e14

        cartesianElements = ptd.Vector6d(3.75e6,
                                         4.24e6,
                                         -1.39e6,
                                         -4.65e3,
                                         -2.21e3,
                                         1.66e3)

        expectedKeplerianElements = ptd.fromKeplerianElements(semiMajorAxis=3.707478199246163e6,
                                                              eccentricity=0.949175203660321,
                                                              inclination=0.334622356632438,
                                                              argumentOfPeriapsis=2.168430616511167,
                                                              longitudeOfAscendingNode=1.630852596545341,
                                                              trueAnomaly=3.302032232567084)

        computedKeplerianElements = ptd.convertCartesianToKeplerianElements(cartesianElements,
                                                                            earthGravitationalParameter)

        self.assertAlmostEqual(expectedKeplerianElements[0] / computedKeplerianElements[0], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedKeplerianElements[1] / computedKeplerianElements[1], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedKeplerianElements[2] / computedKeplerianElements[2], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedKeplerianElements[3] / computedKeplerianElements[3], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedKeplerianElements[4] / computedKeplerianElements[4], 1.0,
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedKeplerianElements[5] / computedKeplerianElements[5], 1.0,
                               places=floatingPointPlaceTolerance)

    def test_CartesianToKeplerianElementConversion_2(self):
        earthGravitationalParameter = 3.2485504415e14

        cartesianElements = ptd.Vector6d( 5.580537430785387e6,
                                          2.816487703435473e6,
                                          0.0,
                                         -3.248092722413634e3,
                                          6.435711753323540e3,
                                          0.0)

        expectedKeplerianElements = ptd.fromKeplerianElements(semiMajorAxis=6.251e6,
                                                              eccentricity=0.0,
                                                              inclination=0.0,
                                                              argumentOfPeriapsis=0.0,
                                                              longitudeOfAscendingNode= 0.0,
                                                              trueAnomaly=26.78 / 180.0 * math.pi)

        computedKeplerianElements = ptd.convertCartesianToKeplerianElements(cartesianElements,
                                                                            earthGravitationalParameter)

        self.assertAlmostEqual(expectedKeplerianElements[0] , computedKeplerianElements[0],
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedKeplerianElements[1] , computedKeplerianElements[1],
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedKeplerianElements[2] , computedKeplerianElements[2],
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedKeplerianElements[3] ,computedKeplerianElements[3],
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedKeplerianElements[4] , computedKeplerianElements[4],
                               places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(expectedKeplerianElements[5] , computedKeplerianElements[5],
                               places=floatingPointPlaceTolerance)