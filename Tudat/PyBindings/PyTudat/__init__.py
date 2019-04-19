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
    return tuple(self)[key]
Vector3d.__getitem__ = Vector3d_getitem

def Vector3d_setitem(self, key,value):
    if (key > 2) or (key < 0):
        raise IndexError('Vector3d index out of range (max 2)')
    if key == 0:
        self.x = float(value)
    elif key == 1:
        self.y = float(value)
    elif key == 2:
        self.z = float(value)
Vector3d.__setitem__ = Vector3d_setitem