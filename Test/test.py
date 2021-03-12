from SyVectors import Vector3, Matrix3, VMath, Vector2
import SyVectors
from testVectors import vector3, matrix3, VectorMultiMatrix3
from datetime import datetime
import math

COUNT = 0

# Camera
camera = SyVectors.Camera(Vector3(-10, 0, 0), Vector3(1, 0, 0), Vector3(0, 1, 0), Vector2(math.pi/4, math.pi/6), Vector2(800, 600) )
print(camera)

print(SyVectors.RenderObj3().lines)

# Vectors
testVector2 = Vector2( 10, 10 )
print(testVector2)
testVector = Vector3( 10, 10, 10 )
testMatrix = Matrix3(Vector3( 10, 10, 10 ), Vector3( 10, 10, 10 ), Vector3( 10, 10, 10 ))
print(testVector.x)
print(testMatrix)
print(VMath.Add3(testVector, Vector3(5, 8, 3)))
print(VMath.Amount3(testVector))
print(VMath.Scale3(testVector, 2.5))
print(VMath.Subtract3(testVector, Vector3(5, 8, 3)))
print(VMath.VectorMultiMatrix3(testVector, testMatrix))

pyVector = vector3( 10, 10, 10 )
pyMatrix = matrix3( vector3( 10, 10, 10 ), vector3( 10, 10, 10 ), vector3( 10, 10, 10 ) )
print("Py: ")
print(pyVector)
print(pyMatrix)
print(VectorMultiMatrix3(pyVector, pyMatrix))

cStart = datetime.now()

for i in range(0, COUNT):
    v = VMath.VectorMultiMatrix3(testVector, testMatrix)

cEnd = datetime.now()
pyStart = datetime.now()

for i in range(0, COUNT):
    v = VectorMultiMatrix3(pyVector, pyMatrix)

pyEnd = datetime.now()

print("TIMES:  [ c =", COUNT, "]")
print(" | C: ", cEnd - cStart)
print(" | Py:", pyEnd - pyStart)