from Tudat import *
import numpy as np


# Extending Vector*d in python

def VectorXd_str(self):
    beginStr = "[ "
    for i in range(self._size()):
        beginStr = beginStr + "{0} ".format(self._getElemAtIndex(i))
    return beginStr + "]"


VectorXd.__str__ = VectorXd_str
Vector3d.__str__ = VectorXd_str
Vector4d.__str__ = VectorXd_str
Vector6d.__str__ = VectorXd_str
Vector7d.__str__ = VectorXd_str

def VectorXd_eq(self, other):
    return tuple(self) == tuple(other)


VectorXd.__eq__ = VectorXd_eq
Vector3d.__eq__ = VectorXd_eq
Vector4d.__eq__ = VectorXd_eq
Vector6d.__eq__ = VectorXd_eq
Vector7d.__eq__ = VectorXd_eq

def VectorXd_ne(self, other):
    return tuple(self) != tuple(other)


VectorXd.__ne__ = VectorXd_ne
Vector3d.__ne__ = VectorXd_ne
Vector4d.__ne__ = VectorXd_ne
Vector6d.__ne__ = VectorXd_ne
Vector7d.__ne__ = VectorXd_ne

def VectorXd_len(self):
    return self._size()


VectorXd.__len__ = VectorXd_len
Vector3d.__len__ = VectorXd_len
Vector4d.__len__ = VectorXd_len
Vector6d.__len__ = VectorXd_len
Vector7d.__len__ = VectorXd_len


def VectorXd_getitem(self, key):
    if (key > (len(self)-1)) or (key < 0):
        raise IndexError('Index out of range (max {0})'.format((len(self)-1)))
    return self._getElemAtIndex(key)


VectorXd.__getitem__ = VectorXd_getitem
Vector3d.__getitem__ = VectorXd_getitem
Vector4d.__getitem__ = VectorXd_getitem
Vector6d.__getitem__ = VectorXd_getitem
Vector7d.__getitem__ = VectorXd_getitem

def VectorXd_setitem(self, key, value):
    if (key > (len(self)-1)) or (key < 0):
        raise IndexError('Vector4d index out of range (max 3)')

    self._setElemAtIndex(key, float(value))


VectorXd.__setitem__ = VectorXd_setitem
Vector3d.__setitem__ = VectorXd_setitem
Vector4d.__setitem__ = VectorXd_setitem
Vector6d.__setitem__ = VectorXd_setitem
Vector7d.__setitem__ = VectorXd_setitem


# Extending Vector3d in python

def Vector3d_Zero():
    return Vector3d(0.0, 0.0, 0.0)


Vector3d.Zero = Vector3d_Zero


# Extending Vector6d in python

def Vector6d_Zero():
    v = Vector6d()
    for i in range(6):
        v[i] = 0.0
    return v


Vector6d.Zero = Vector6d_Zero


def fromKeplerianElements(semiMajorAxis,
                          eccentricity,
                          inclination,
                          argumentOfPeriapsis,
                          longitudeOfAscendingNode,
                          trueAnomaly
                          ):
    vec = Vector6d()
    vec[KeplerianElementIndices.semiMajorAxisIndex] = semiMajorAxis
    vec[KeplerianElementIndices.eccentricityIndex] = eccentricity
    vec[KeplerianElementIndices.inclinationIndex] = inclination
    vec[KeplerianElementIndices.argumentOfPeriapsisIndex] = argumentOfPeriapsis
    vec[KeplerianElementIndices.longitudeOfAscendingNodeIndex] = longitudeOfAscendingNode
    vec[KeplerianElementIndices.trueAnomalyIndex] = trueAnomaly
    return vec


# Extending Vector4d in python

def Vector4d_Zero():
    v = Vector4d()
    for i in range(6):
        v[i] = 0.0
    return v


Vector4d.Zero = Vector4d_Zero


# Extending Matrix3d in python

def Matrix3d_str(self):
    return "[ {0} {1} {2} ]\n[ {3} {4} {5} ]\n[ {6} {7} {8} ]".format(
        self._getElem(0, 0), self._getElem(0, 1), self._getElem(0, 2),
        self._getElem(1, 0), self._getElem(1, 1), self._getElem(1, 2),
        self._getElem(2, 0), self._getElem(2, 1), self._getElem(2, 2)
    )


Matrix3d.__str__ = Matrix3d_str


def Matrix3d_getItem(self, indices):
    if not isinstance(indices, tuple):
        # Only one index was passed (eg matrix[1])
        return [self._getElem(indices, 0), self._getElem(indices, 1), self._getElem(indices, 2)]
    # Multiple indices were passed (matrix[1,3])
    if len(indices) != 2:
        raise IndexError("Matrix3d is indexed in two dimensions [row,columns]")
    row, col = indices
    return self._getElem(row, col)

Matrix3d.__getitem__ = Matrix3d_getItem

def Matrix3d_setItem(self, indices, val):
    if (not isinstance(indices, tuple)) or (len(indices) != 2) :
        raise IndexError("Matrix3d is indexed in two dimensions [row,columns]")
    row, col = indices
    self._setElem(row, col, val)

Matrix3d.__setitem__ = Matrix3d_setItem

def Matrix3d_toList(self):
    mat = [[self._getElem(0, 0), self._getElem(0, 1), self._getElem(0, 2)],
           [self._getElem(1, 0), self._getElem(1, 1), self._getElem(1, 2)],
           [self._getElem(2, 0), self._getElem(2, 1), self._getElem(2, 2)]]

Matrix3d.toList = Matrix3d_toList

def Matrix3d_fromList(list):
    mat = Matrix3d()
    for i in range(3):
        for j in range(3):
            mat[i,j] = list[i][j]
    return mat

Matrix3d.fromList = Matrix3d_fromList

def Matrix3d_toNumpy(self):
    return np.array(self.toList())

Matrix3d.toNumpy = Matrix3d_toNumpy

def Matrix3d_eq(self, other):
    l1 = self.toList()
    l2 = other.toList()
    equal = True
    for row in range(3):
        for column in range(3):
            if l1[row][column] != l2[row][column]:
                equal = False
    return equal

Matrix3d.__eq__ = Matrix3d_eq

def Matrix3d_neq(self, other):
    return not self.__eq__(other)

Matrix3d.__neq__ = Matrix3d_neq



