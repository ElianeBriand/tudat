import unittest

import PyTudat as ptd
import numpy as np
import math

floatingPointPlaceTolerance = 7  # Assert check to 7 decimal places


class TestUnitConversions(unittest.TestCase):

    # See unitTestUnitConversions.cpp for the sources of the various test values

    def test_ConversionFromKilometersToMeters(self):
        t_input = 1.0e6
        output_ref = 1.0e6 * 1.0e3
        output_test = ptd.units.convertKilometersToMeters(t_input)
        self.assertAlmostEqual(output_test, output_ref, places=floatingPointPlaceTolerance)

    def test_ConversionFromDegreesToRadians(self):
        t_input = 45.0
        output_ref = math.pi / 4.0
        output_test = ptd.units.convertDegreesToRadians(t_input)
        self.assertAlmostEqual(output_test, output_ref, places=floatingPointPlaceTolerance)

    def test_ConversionFromDegreesToArcminutes(self):
        t_input = 43.2
        output_ref = 43.2 * 60.0
        output_test = ptd.units.convertDegreesToArcminutes(t_input)
        self.assertAlmostEqual(output_test, output_ref, places=floatingPointPlaceTolerance)

    def test_ConversionFromArcminutesToArcSeconds(self):
        t_input = 125.9
        output_ref = 125.9 * 60.0
        output_test = ptd.units.convertArcminutesToArcseconds(t_input)
        self.assertAlmostEqual(output_test / output_ref, 1.0, places=floatingPointPlaceTolerance)

    def test_ConversionFromAstronomicalUnitsToMeters(self):
        t_input = 30.10366151
        output_ref = 4.503443661e+12
        output_test = ptd.units.convertAstronomicalUnitsToMeters(t_input)
        self.assertAlmostEqual(output_test / output_ref, 1.0, places=floatingPointPlaceTolerance)

    def test_ConversionFromMinutesToSeconds(self):
        t_input = 12.0
        output_ref = 12.0 * 60.0
        output_test = ptd.units.convertMinutesToSeconds(t_input)
        self.assertAlmostEqual(output_test, output_ref, places=floatingPointPlaceTolerance)

    def test_ConversionFromSecondsToMinutes(self):
        t_input = 12.0
        output_ref = 0.2
        output_test = ptd.units.convertSecondsToMinutes(t_input)
        self.assertAlmostEqual(output_test, output_ref, places=floatingPointPlaceTolerance)

    def test_ConversionFromHoursToJulianYears(self):
        t_input = 24.0
        output_ref = 1.0 / 365.25
        output_test = ptd.units.convertJulianDaysToJulianYears(
            ptd.units.convertSecondsToJulianDays(
                ptd.units.convertHoursToSeconds(t_input)
            )
        )
        self.assertAlmostEqual(output_test, output_ref, places=floatingPointPlaceTolerance)

    def test_ConversionFromJulianYearsToHours(self):
        t_input = 1.0 / 365.25
        output_ref = 24.0
        output_test = ptd.units.convertSecondsToHours(
            ptd.units.convertJulianDaysToSeconds(
                ptd.units.convertJulianYearsToJulianDays(t_input)
            )
        )
        self.assertAlmostEqual(output_test, output_ref, places=floatingPointPlaceTolerance)

    def test_ConversionFromSiderealDaysToSeconds(self):
        t_input = 7.0
        output_ref = 7.0 * 86164.09054
        output_test = ptd.units.convertSiderealDaysToSeconds(t_input)
        self.assertAlmostEqual(output_test, output_ref, places=floatingPointPlaceTolerance)

    def test_ConversionFromSecondsToSiderealDays(self):
        t_input = 100.0
        output_ref = 100.0 / 86164.09054
        output_test = ptd.units.convertSecondsToSiderealDays(t_input)
        self.assertAlmostEqual(output_test, output_ref, places=floatingPointPlaceTolerance)

    def test_ConversionFromRankineToKelvin(self):
        t_input = 491.67
        output_ref = 273.15
        output_test = ptd.units.convertRankineToKelvin(t_input)
        self.assertAlmostEqual(output_test, output_ref, places=floatingPointPlaceTolerance)

    def test_ConversionFromFeetToMeters(self):
        t_input = 5280.0
        output_ref = 1609.344
        output_test = ptd.units.convertFeetToMeter(t_input)
        self.assertAlmostEqual(output_test, output_ref, places=floatingPointPlaceTolerance)

    def test_ConversionFromPoundsPerSquareFeetToPascal(self):
        t_input = 2116.21662367394
        output_ref = 101325.0
        output_test = ptd.units.convertPoundPerSquareFeetToPascal(t_input)
        self.assertAlmostEqual(output_test / output_ref, 1.0, places=floatingPointPlaceTolerance)
