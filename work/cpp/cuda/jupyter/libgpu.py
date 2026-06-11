import ctypes
import argparse

lib = ctypes.CDLL("/work/work/cpp/cuda/jupyter/libgpu.so")
lib.gpuAdd.argtypes = (ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int))
lib.gpuAdd.restype = None

parser = argparse.ArgumentParser(description="Call gpuAdd from libgpu.so with two integers")
parser.add_argument("a", type=int, help="first integer")
parser.add_argument("b", type=int, help="second integer")
args = parser.parse_args()

res = ctypes.c_int()
lib.gpuAdd(args.a, args.b, ctypes.byref(res))
print("Result from python: {}".format(res.value))
