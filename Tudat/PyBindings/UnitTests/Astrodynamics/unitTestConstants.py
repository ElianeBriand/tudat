import unittest

import PyTudat as ptd
import numpy as np
import math

floatingPointPlaceTolerance = 7  # Assert check to 7 decimal places


class TestPhysicalConstants(unittest.TestCase):

    # See unitTestPhysicalConstants.cpp for the sources of the various test values

    def test_RelationsBetweenPhysicalConstant(self):
        self.assertAlmostEqual(
            ptd.constants.JULIAN_YEAR_IN_SECONDS,
            ptd.constants.JULIAN_DAY_IN_SECONDS * ptd.constants.JULIAN_YEAR_IN_DAYS,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.SIDEREAL_YEAR_IN_SECONDS,
            ptd.constants.JULIAN_DAY_IN_SECONDS * ptd.constants.SIDEREAL_YEAR_IN_DAYS,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            math.pow(ptd.constants.SPEED_OF_LIGHT, -2.0),
            ptd.constants.INVERSE_SQUARE_SPEED_OF_LIGHT,
            places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(
            math.pow(ptd.constants.SPEED_OF_LIGHT, -3.0),
            ptd.constants.INVERSE_CUBIC_SPEED_OF_LIGHT,
            places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(
            math.pow(ptd.constants.SPEED_OF_LIGHT, -4.0),
            ptd.constants.INVERSE_QUARTIC_SPEED_OF_LIGHT,
            places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(
            math.pow(ptd.constants.SPEED_OF_LIGHT, -5.0),
            ptd.constants.INVERSE_QUINTIC_SPEED_OF_LIGHT,
            places=floatingPointPlaceTolerance)

    def test_otherConstants(self):
        self.assertAlmostEqual(
            ptd.constants.GRAVITATIONAL_CONSTANT,
            6.67259e-11,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.SPEED_OF_LIGHT,
            299792458.0,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.ASTRONOMICAL_UNIT,
            1.49597870691e11,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.MOLAR_GAS_CONSTANT,
            8.3144598,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.AVOGADRO_CONSTANT,
            6.022140857e23,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.PLANCK_CONSTANT,
            6.62606957E-34,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.BOLTZMANN_CONSTANT,
            1.3806488E-23,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.VACUUM_PERMEABILITY,
            4.0 * math.pi * 1.0E-7,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.VACUUM_PERMITTIVITY,
            1 / (4.0 * math.pi * 1.0E-7 * math.pow(ptd.constants.SPEED_OF_LIGHT, 2.0)),
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.STEFAN_BOLTZMANN_CONSTANT,
            2.0 * math.pow(math.pi, 5) * math.pow(ptd.constants.BOLTZMANN_CONSTANT, 4) /
            (15.0 * ptd.constants.SPEED_OF_LIGHT * ptd.constants.SPEED_OF_LIGHT *
             ptd.constants.PLANCK_CONSTANT * ptd.constants.PLANCK_CONSTANT * ptd.constants.PLANCK_CONSTANT),
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.STEFAN_BOLTZMANN_CONSTANT,
            5.670373E-8,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.LG_TIME_RATE_TERM,
            6.969290134E-10,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.LB_TIME_RATE_TERM,
            1.550519768E-8,
            places=floatingPointPlaceTolerance)

    def test_timeConstants(self):
        self.assertAlmostEqual(
            ptd.constants.JULIAN_YEAR_IN_DAYS,
            365.25,
            places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(
            ptd.constants.SIDEREAL_YEAR_IN_DAYS,
            365.25636,
            places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(
            ptd.constants.SIDEREAL_DAY_IN_SECONDS,
            86164.09054,
            places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(
            ptd.constants.JULIAN_DAY_IN_SECONDS,
            86400.0,
            places=floatingPointPlaceTolerance)

    def test_GravitationalParameters(self):
        self.assertAlmostEqual(
            ptd.constants.SUN_GRAVITATIONAL_PARAMETER,
            1.32712440018e20,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.MERCURY_GRAVITATIONAL_PARAMETER,
            ptd.constants.SUN_GRAVITATIONAL_PARAMETER / 6023600.0,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.VENUS_GRAVITATIONAL_PARAMETER,
            ptd.constants.SUN_GRAVITATIONAL_PARAMETER / 408523.71,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.EARTH_GRAVITATIONAL_PARAMETER,
            3.986004418e14,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.MOON_GRAVITATIONAL_PARAMETER,
            ptd.constants.SUN_GRAVITATIONAL_PARAMETER
            / (328900.56 * (1.0 + 81.30059)),
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.MARS_GRAVITATIONAL_PARAMETER,
            ptd.constants.SUN_GRAVITATIONAL_PARAMETER
            / 3098708.0,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.JUPITER_GRAVITATIONAL_PARAMETER,
            ptd.constants.SUN_GRAVITATIONAL_PARAMETER
            / 1047.3486,
            places=floatingPointPlaceTolerance)

        self.assertAlmostEqual(
            ptd.constants.SATURN_GRAVITATIONAL_PARAMETER,
            ptd.constants.SUN_GRAVITATIONAL_PARAMETER
            / 3497.898,
            places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(
            ptd.constants.URANUS_GRAVITATIONAL_PARAMETER,
            ptd.constants.SUN_GRAVITATIONAL_PARAMETER
            / 22902.98,
            places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(
            ptd.constants.NEPTUNE_GRAVITATIONAL_PARAMETER,
            ptd.constants.SUN_GRAVITATIONAL_PARAMETER
            / 19412.24,
            places=floatingPointPlaceTolerance)
        self.assertAlmostEqual(
            ptd.constants.PLUTO_GRAVITATIONAL_PARAMETER,
            ptd.constants.SUN_GRAVITATIONAL_PARAMETER
            / 1.35e8,
            places=floatingPointPlaceTolerance)
