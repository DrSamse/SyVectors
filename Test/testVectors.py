class vector3:
    def __init__(self, x : float = 0, y : float = 0, z : float = 0):
        self.x = x
        self.y = y
        self.z = z

    def __repr__(self):
        return "( " + str(self.x) + " " + str(self.y) + " " + str(self.z) + " )"

class matrix3: 
    def __init__(self, x : vector3, y : vector3, z : vector3):
        self.x = x
        self.y = y
        self.z = z

    def __repr__(self):
        return "( " + repr(self.x) + " " + repr(self.y) + " " + repr(self.z) + " )"

def VectorMultiMatrix3(v : vector3, m : matrix3) -> vector3:
    return vector3(
        (m.x.x + m.x.y + m.x.z) * v.x,
        (m.y.x + m.y.y + m.y.z) * v.y,
        (m.z.x + m.z.y + m.z.z) * v.z
    )