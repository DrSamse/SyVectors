import tkinter
from SyVectors import Vector2, Vector3, Line2, Line3, RenderObj2
from Shapes import Triangle2

class Visual:
    def __init__(self, width : int = 800, height : int = 600):
        self.window = tkinter.Tk()
        self.window.geometry(str(width) + "x" + str(height))
        self.screenSize = Vector2( width, height )
        self.draw = tkinter.Canvas(self.window, width=width, height=height)
        self.draw.place(x=0, y=0)
    
    def DrawPoint( self, point : Vector2 ):
        if (point == None): return
        self.draw.create_oval(self.screenSize.x / 2 + point.x - 1, self.screenSize.y / 2 - point.y - 1, self.screenSize.x / 2 + point.x + 1, self.screenSize.y / 2 - point.y + 1)

    def DrawLine( self, line : Line2, *args, **kwargs):
        if (line == None): return
        # self.DrawPoint(line.a)
        # self.DrawPoint(line.b)
        self.draw.create_line(line.a.x + self.screenSize.x/2, -line.a.y + self.screenSize.y/2, line.b.x + self.screenSize.x/2, -line.b.y + self.screenSize.y/2, args, kwargs)

    def DrawTriangle(self, triangle : Triangle2):
        lines = [ 
            Line2(triangle.A, triangle.B),
            Line2(triangle.B, triangle.C),
            Line2(triangle.C, triangle.A)
        ]

    def DrawRenderObj( self, obj : RenderObj2, drawFunction = None):
        if drawFunction == None: drawFunction = self.DrawLine
        print("Drawing Obj ... [ L:", len(obj.lines), "]")
        for i in range(0, len(obj.lines)):
            drawFunction(obj.lines[i])

    def Start(self):
        self.window.mainloop()

    