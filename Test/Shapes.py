from SyVectors import Vector2, Vector3, Line2, Line3, VMath, RenderObj3

TRIANGLE_STEP = 0.1
        
class Triangle2:
    def __init__(self, A : Vector2, B : Vector2, C : Vector2) -> None:
        self.A = A
        self.B = B
        self.C = C

class Triangle3:
    def __init__(self, A : Vector3, B : Vector3, C : Vector3, fill) -> None:
        self.A = A
        self.B = B
        self.C = C
        

class Rectangle3:
    def __init__(self, A : Vector3, B : Vector3, C : Vector3) -> None:
        self.A = A
        self.B = B
        self.C = C
        self.D = VMath.Subtract3( C, VMath.Subtract3( B, A ) )
        self.lines = [ 
            Line3(A, B),
            Line3(B, C),
            Line3(C, self.D),
            Line3(self.D, A) 
        ]
    
    def GetRenderObj3(self) -> RenderObj3:
        obj = RenderObj3()
        for line in self.lines:
            r = line.GetRenderObj3()
            obj.lines.extend(r.lines)
        return obj
