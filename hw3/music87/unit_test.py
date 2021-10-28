import _matrix
import unittest
import timeit
import time
import sys
import os
from random import randrange

def initialize(mat):
    for i in range(mat.nrow):
        for j in range(mat.ncol):
            mat[i,j] = float(randrange(100))
    return mat

class TestClass:

    def test_accurate(self):
        n = 1000
        block_size = 128
        mat1 = _matrix.Matrix(n,n)
        mat2 = _matrix.Matrix(n,n)
        
        mat1 = initialize(mat1)
        mat2 = initialize(mat2)
        #mat1.printself()
        #mat2.printself()

        res_naive = _matrix.multiply_naive(mat1, mat2)
        res_tile = _matrix.multiply_tile(mat1, mat2, block_size)
        res_ans = _matrix.multiply_mkl(mat1, mat2)

        assert(res_naive == res_ans)
        assert(res_tile == res_ans)
        
    def test_performance(self):
        setup = '''
import _matrix
n = 1000
block_size = 128
mat1 = _matrix.Matrix(n,n)
mat2 = _matrix.Matrix(n,n)
for i in range(n):
    for j in range(n):
        mat1[i, j] = i*n+j+1
        mat2[i, j] = i*n+j+1
'''
        repeat=5
        with open('performance.txt', 'w') as fin:
            tile = timeit.Timer('_matrix.multiply_tile(mat1, mat2, block_size)', setup=setup)
            tile_sec = min(tile.repeat(repeat=repeat, number=1))
            naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
            naive_sec = min(naive.repeat(repeat=repeat, number=1))
            mkl = timeit.Timer('_matrix.multiply_mkl(mat1, mat2)', setup=setup)
            mkl_sec = min(mkl.repeat(repeat=repeat, number=1))
            print(f"multiply_tile takes {tile_sec} seconds", file=fin)
            print(f"multiply_naive takes {naive_sec} seconds", file=fin)
            print(f"multiply_mkl takes {mkl_sec} seconds", file=fin)
            print("MKL speed-up over naive: %g x" % (naive_sec/mkl_sec), file=fin)
            print("128 tile speed-up over naive: %g x" % (naive_sec/tile_sec), file=fin)


