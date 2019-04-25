from Tudat import *


# Extending Vector3d in python

def Vector3d_str(self):
    return "[ {0} {1} {2} ]".format(*tuple(self))

Vector3d.__str__ = Vector3d_str

def Vector3d_eq(self, other):
    return tuple(self) == tuple(other)

Vector3d.__eq__ = Vector3d_eq

def Vector3d_ne(self, other):
    return tuple(self) != tuple(other)

Vector3d.__ne__ = Vector3d_ne

def Vector3d_len(self):
    return 3
Vector3d.__len__ = Vector3d_len

def Vector3d_getitem(self, key):
    if (key > 2) or (key < 0):
        raise IndexError('Vector3d index out of range (max 2)')
    return self._getElemAtIndex(key)
Vector3d.__getitem__ = Vector3d_getitem

def Vector3d_setitem(self, key,value):
    if (key > 2) or (key < 0):
        raise IndexError('Vector3d index out of range (max 2)')

    self._setElemAtIndex(key,float(value))
Vector3d.__setitem__ = Vector3d_setitem

def Vector3d_Zero():
    return Vector3d(0.0, 0.0, 0.0)

Vector3d.Zero = Vector3d_Zero


# Extending Vector6d in python

def Vector6d_str(self):
    return "[ {0} {1} {2} {3} {4} {5} ]".format(*tuple(self))

Vector6d.__str__ = Vector6d_str

def Vector6d_eq(self, other):
    return tuple(self) == tuple(other)

Vector6d.__eq__ = Vector6d_eq

def Vector6d_ne(self, other):
    return tuple(self) != tuple(other)

Vector6d.__ne__ = Vector6d_ne

def Vector6d_len(self):
    return 6
Vector6d.__len__ = Vector6d_len

def Vector6d_getitem(self, key):
    if (key > 5) or (key < 0):
        raise IndexError('Vector6d index out of range (max 5)')
    return self._getElemAtIndex(key)
Vector6d.__getitem__ = Vector6d_getitem

def Vector6d_setitem(self, key,value):
    if (key > 5) or (key < 0):
        raise IndexError('Vector6d index out of range (max 5)')

    self._setElemAtIndex(key,float(value))
Vector6d.__setitem__ = Vector6d_setitem



def Vector6d_Zero():
    v = Vector6d()
    for i in range(6):
        v[i] = 0.0
    return v

Vector6d.Zero = Vector6d_Zero


# Extending Vector4d in python

def Vector4d_str(self):
    return "[ {0} {1} {2} {3} ]".format(*tuple(self))

Vector4d.__str__ = Vector4d_str

def Vector4d_eq(self, other):
    return tuple(self) == tuple(other)

Vector4d.__eq__ = Vector4d_eq

def Vector4d_ne(self, other):
    return tuple(self) != tuple(other)

Vector4d.__ne__ = Vector4d_ne

def Vector4d_len(self):
    return 4
Vector4d.__len__ = Vector4d_len

def Vector4d_getitem(self, key):
    if (key > 3) or (key < 0):
        raise IndexError('Vector4d index out of range (max 3)')
    return self._getElemAtIndex(key)
Vector4d.__getitem__ = Vector4d_getitem

def Vector4d_setitem(self, key,value):
    if (key > 3) or (key < 0):
        raise IndexError('Vector4d index out of range (max 3)')

    self._setElemAtIndex(key,float(value))
Vector4d.__setitem__ = Vector4d_setitem



def Vector4d_Zero():
    v = Vector4d()
    for i in range(6):
        v[i] = 0.0
    return v

Vector4d.Zero = Vector4d_Zero