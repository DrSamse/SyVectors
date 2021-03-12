import SyVectors as s
import math

# Camera
camera = s.Camera(s.Vector3(-10, 0, 0), s.Vector3(1, 0, 0), s.Vector3(0, 1, 0), s.Vector2(math.pi/4, math.pi/6), s.Vector2(800, 600) )

renderLine = s.Line3( s.Vector3( 0, 0, 1 ), s.Vector3( 0, 0, 0 ) )
renderObj = s.RenderObj3()
renderObj.lines = [
    renderLine,
    s.Line3( s.Vector3( 0, 0, 1 ), s.Vector3( 0, 0, 0 ) ),
    s.Line3( s.Vector3( 0, 0, 1 ), s.Vector3( 0, 0, 0 ) )
]

print(camera.RenderObj(renderObj).lines)