import numpy as np
def TRACE(matrix):
    return np.trace(matrix)
def INPUT_MATRIX(name):
    print(f"Введите размерность матрицы {name} (n x n): ")
    n = int(input())
    print(f"Введите элементы матрицы {name} построчно через пробел:")
    matrix = []
    for i in range(n):
        row = list(map(float, input().split()))
        matrix.append(row)
    return np.array(matrix)
X = INPUT_MATRIX("X")
Y = INPUT_MATRIX("Y")
Z = INPUT_MATRIX("Z")
trace_X = TRACE(X)
trace_Y = TRACE(Y)
trace_Z = TRACE(Z)
print(f"След матрицы X: {trace_X}")
print(f"След матрицы Y: {trace_Y}")
print(f"След матрицы Z: {trace_Z}")
max_trace = max(trace_X, trace_Y, trace_Z)
if max_trace == trace_X:
    print("Матрица X имеет максимальный след")
elif max_trace == trace_Y:
    print("Матрица Y имеет максимальный след")
else:
    print("Матрица Z имеет максимальный след")

