import unittest

import PyTudat as ptd
import numpy as np
import math

floatingPointPlaceTolerance = 7 # Assert check to 7 decimal places

class TestEigenStructures_Vector3d(unittest.TestCase):

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
        v = ptd.Vector3d(1.4, -2.1, 3.9)

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

    def test_Vector6d_ConstructionComparisonIndexing(self):
        v1 = ptd.Vector6d(2.3, 0.0, -1.4, 1, 2, 3.1)

        v2 = ptd.Vector6d()
        v2[0] = 2.3
        v2[1] = 0.1
        v2[2] = -1.4
        v2[3] = 1
        v2[4] = 2
        v2[5] = 3.1

        v3 = ptd.Vector6d(2.3, 0.0, -1.4, 1, 2, 3.1)

        self.assertFalse(v1 == v2)
        self.assertTrue(v1 != v2)

        v2[1] = 0.0

        self.assertFalse(v1 != v2)
        self.assertTrue(v1 == v2)

        self.assertEqual(v1[5], 3.1)
        self.assertEqual(v1[0], 2.3)

        self.assertFalse(v1 != v3)
        self.assertTrue(v1 == v3)

        with self.assertRaises(TypeError):
            a = ptd.Vector6d(2.3, 0.0, -1.4, 1, 2)

    def test_Vector6d_Indexing(self):
        v1 = ptd.Vector6d(2.3, 0.0, -1.4, 1, 2, 3.1)


        self.assertEqual(v1[2], -1.4)

        with self.assertRaises(IndexError):
            v1[6] = 3
        with self.assertRaises(IndexError):
            a = v1[6]

    def test_Vector6d_Numpy(self):
        v = ptd.Vector6d(1.4, -2.1, 3.9, 9.4, 2.78, 2.5)

        vnp = v.toNumpy()

        refnp = np.array([[1.4], [-2.1], [3.9],[9.4], [2.78], [2.5]])

        self.assertTrue(np.allclose(vnp, refnp))


if __name__ == '__main__':
    unittest.main()