import unittest

import PyTudat as ptd
import numpy as np
import math

floatingPointPlaceTolerance = 7 # Assert check to 7 decimal places

class TestEigenStructures(unittest.TestCase):

    def test_Vector3d_ConstructionComparison(self):
        v1 = ptd.Vector3d()
        v1.x = 1
        v1.y = 2.0
        v1.z = 3.1

        v2 = ptd.Vector3d(1,2,3)
        v3 = ptd.Vector3d(1,2,3.1)

        self.assertEqual(v3, v1)
        self.assertFalse(v1 == v2)
        self.assertTrue(v1 != v2)
        self.assertFalse(v1 != v3)
        self.assertTrue(v1 == v3)

        self.assertEqual(v3.x, 1.0)
        self.assertEqual(v3.y, 2.0)
        self.assertEqual(v3.z, 3.1)

    def test_Vector3d_Indexing(self):
        v3 = ptd.Vector3d(1,-2,3.1)

        self.assertEqual(v3[0], 1.0)
        self.assertEqual(v3[1], -2.0)
        self.assertEqual(v3[2], 3.1)
        with self.assertRaises(IndexError):
            v3[3] = 3
        with self.assertRaises(IndexError):
            a = v3[3]

        def test_Vector3d_Indexing(self):
            v3 = ptd.Vector3d(1,-2,3.1)

        self.assertEqual(v3[0], 1.0)
        self.assertEqual(v3[1], -2.0)
        self.assertEqual(v3[2], 3.1)
        with self.assertRaises(IndexError):
            v3[3] = 3
        with self.assertRaises(IndexError):
            a = v3[3]


    def test_Vector3d_Numpy(self):
        v = ptd.Vector3d(1.4,-2.1,3.9)

        vnp = v.toNumpy()

        refnp = np.array([[1.4], [-2.1], [3.9]])

        self.assertTrue(np.allclose(vnp, refnp))

    def test_Vector3d_str(self):
        v = ptd.Vector3d(1.4,-2.1,3.9)

        refstr = "[ 1.4 -2.1 3.9 ]"

        self.assertEqual(str(v),refstr)

    def test_Vector3d_isIterable(self):
        # This is indirectly testing if vector3d is iterable (__iter__)
        v = ptd.Vector3d(1.4,-2.1,3.9)

        sum = 0.0
        for val in v:
            sum += val

        refsum = 1.4 + -2.1 + 3.9

        self.assertEqual(sum,refsum)

    def test_Vector3d_normalization(self):
        v = ptd.Vector3d(1.4,-2.1,3.9)

        refnorm = math.sqrt(1.4**2 + (-2.1)**2 + 3.9**2)

        self.assertAlmostEqual(v.norm(),refnorm, places=floatingPointPlaceTolerance)

        v.normalize()

        self.assertAlmostEqual(v.norm(),1.0, places=floatingPointPlaceTolerance)

if __name__ == '__main__':
    unittest.main()