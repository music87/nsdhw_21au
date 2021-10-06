import pytest
from _vector import compute_angle
import math

eps = 1e-2

class TestClass:
    def test_other_angle1(self):
        assert abs(compute_angle([1, 2], [3, 4]) - 0.17985) < eps 

    def test_other_angle2(self):
        assert abs(compute_angle([1, 0], [1.0/2.0, math.sqrt(3.0)/2.0]) - 1.0472) < eps #60 degree
    def test_other_angle3(self):
        assert abs(compute_angle([1, 0], [math.sqrt(3.0)/2.0, 1.0/2.0]) - 0.5236) < eps #30 degree
    def test_zero_angle(self):
        assert abs(compute_angle([1, 0], [2, 0]) - 0) < eps # 0 degree
    def test_right_angle(self):
        assert abs(compute_angle([1, 0], [0, 1]) - 1.5708) < eps # 90 degree
    def test_zero_len(self):
        try:
            compute_angle([0,0], [1,1])
        except ValueError as e:
            # compute_angle([0,0], [1,1]) should raise ValueError
            # hence e should be ValueError('zero-length 2-vector (invalid input)'), and type(e) is ValueError
            assert "zero-length 2-vector (invalid input)" in str(e)
        else:
            # if compute_angle([0,0], [1,1]) don't raise ValueError, then there is a mistake in _vector.cpp
            raise NotImplementedError


