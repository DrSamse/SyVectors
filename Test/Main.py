import Visual
from SyVectors import Camera, Vector2, Vector3, VMath, Matrix3
from Shapes import Rectangle3
from Bodies import Cube

v1 = VMath.UnitVector3(Vector3( 1, 0.1, 0 ))
print(v1)
v2 = VMath.UnitVector3(Vector3( -0.2, 1, 0 ))
print(v2)

camera = Camera( Vector3( -10, 1, 10 ), v1, v2, Vector2( 1, 0.8 ), Vector2( 800, 600 ) )
visual = Visual.Visual()

m = Matrix3(camera.viewX, camera.viewY, camera.viewZ)
print(m)
print(VMath.VectorMultiMatrix3(Vector3(10, 10, 10), m))

LENGTH = 5
WIDTH = 5
HEIGHT = 5

cube = Cube(
    Rectangle3(
        Vector3( 0, 0, 0 ),
        Vector3( LENGTH, 0, 0 ),
        Vector3( LENGTH, WIDTH, 0 )
    ),  Vector3( 0, 0, HEIGHT )
)

obj = camera.RenderObj(cube.GetRenderObj3())
print("Render finished")
visual.DrawRenderObj(obj)

if __name__ == "__main__":
    visual.Start()