from distutils.core import setup, Extension
import os

NAME = "SyVectors"

def main():
    setup(
        name=NAME,
        version="0.0.1",
        description=open("./README.md").read(),
        author="Samuel Nösslböck", 
        author_email="samuel.noessi@gmail.com",
        ext_modules=[Extension(NAME, ["SyVectors.cpp"])]
    )


if __name__ == "__main__":

    print("Del old ... ")
    os.system("del /f .\\build\\lib.win32-3.8\\" + NAME + ".cp38-win32.pyd")
    print("Old deleted")

    main()

    print("Copying file ... ")
    os.system("copy .\\build\\lib.win32-3.8\\" + NAME + ".cp38-win32.pyd .\\Test")
    print("File copied! ")
    