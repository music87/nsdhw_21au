#include<pybind11/pybind11.h>
#include<iostream>
#include<cmath>
float EPS = 1e-2;
namespace py = pybind11;

float compute_angle(std::pair<float, float> v1, std::pair<float, float> v2){
    // compute the angle between two vectors
    // cos(theta) = (vector1 dot vector2) / (|vector1||vector2|) 
    // => theta = arccos( (vector1 dot vector2) / (|vector1||vector2|) ) 
    
    // declare variable
    float dot_result, len1, len2, theta;

    // dot product
    dot_result = v1.first*v2.first + v1.second*v2.second;//vector1 dot vector2
    
    // vector lenth
    len1 = std::sqrt(v1.first*v1.first + v1.second*v1.second); //|vector1|
    len2 = std::sqrt(v2.first*v2.first + v2.second*v2.second); //|vector2|
    if ((fabs(len1-0.0)<EPS) || (fabs(len2-0.0)<EPS)){
    	throw std::invalid_argument("zero-length 2-vector (invalid input)");
    } 

    // compute the angle and return
    theta = std::acos((dot_result) / (len1*len2));
    return theta;
}

PYBIND11_MODULE(_vector, m){
    m.doc() = "compute the angle between two vectors";
    m.def("compute_angle", &compute_angle, "calculates the angle (in radians) between two vectors in the 2-dimensional Cartesian coordinate system");

}

