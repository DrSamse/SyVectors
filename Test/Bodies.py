from SyVectors import Vector3, VMath, Line3, RenderObj3, LineSplitDown
from Shapes import Rectangle3

class Cube:
    def __init__(self, ABCD : Rectangle3, E : Vector3) -> None:
        self.ABCD = ABCD
        A = ABCD.A
        self.EFGH = Rectangle3(
            E,
            VMath.Add3(VMath.Subtract3(E, A), ABCD.B),
            VMath.Add3(VMath.Subtract3(E, A), ABCD.C)
        )
        self.lines = [
            *self.ABCD.lines,
            *self.EFGH.lines,
            Line3( ABCD.A, self.EFGH.A ),
            Line3( ABCD.B, self.EFGH.B ),
            Line3( ABCD.C, self.EFGH.C ),
            Line3( ABCD.D, self.EFGH.D )
        ]

    def GetRenderObj3(self) -> RenderObj3:
        obj = RenderObj3()
        for line in self.lines:
            obj.lines.extend( LineSplitDown(line, 100).lines )
        return obj