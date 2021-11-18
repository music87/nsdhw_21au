Social distance detector
===========================
## Basic Information

**Github repository**: https://github.com/secondlevel/Social-distance-detector

The dataset is as follows https://data.mendeley.com/datasets/xh6m6gxhvj/1

## Problem to Solve

In recent years, due to the outbreak of COVID-19 epidemic, the mortality rate is very high all over the world. Because the virus spreads through the air, social distance, that is, the social distance between people, has become one of the ways to prevent the virus from spreading too fast. However, due to the lack of human resources, people can not always monitor whether there are people who violate this social distance. 

In order to solve this problem, the goal of this proposal is to automatically detect the social distance between people, and return the detected report to warn the person who violates this rule. The report contains some information about time, number of people, and personal identity, and the report can be used to track the infection history.

## Methods Description

The proposal aims to detect social distance by using side-view video, so the input will be the video, and the output will be the report.

In order to achieve this goal, the methods can be divided into five parts:

1. Video Split: Split video into multiple frames.

2. Camera calibration: Undistort the image which is shown below. The picture on the left is the case of "Normal", the picture in the middle is the case of "Positive Radial Distortation", and the picture on the right is the case of "Negative Radial Distortation".

<p float="center">
  
  <img src="https://github.com/secondlevel/nsdhw_21au/blob/secondlevel-proposal-submission/proposal/secondlevel/img/camera_calibration_normal.png" width="250" title="Normal image" hspace="35" />
  
  <img src="https://github.com/secondlevel/nsdhw_21au/blob/secondlevel-proposal-submission/proposal/secondlevel/img/camera_calibration_positive.png" width="280" title="Positive radial image" hspace="30" />
  
  <img src="https://github.com/secondlevel/nsdhw_21au/blob/secondlevel-proposal-submission/proposal/secondlevel/img/camera_calibration_negative.png" width="250" title="Negative radial image" hspace="40" /> 
  
</p>

3. Object tracking: Tracking the people that exists in the video through "YOLOv4" and "Deep-Sort".

4. Calculate social distance: Using the Euclidean distance, the paired distance of the centroid of the detected bounding box is determined.

5. Generate analysis report: Package all information into the report, including current time, people's identity, the distance between the people and who violates the social distance.

## Prospective Users

The government or those companies who want to limit the number of people in the venue.(The government and company can check whether anyone is too close to the infected person by reporting, etc.)

## System Architecture

<img src="https://github.com/secondlevel/nsdhw_21au/blob/secondlevel-proposal-submission/proposal/secondlevel/img/System_Architecture.jpg" width="850" title="System Architecture" hspace="80" />

## API Description

### Modules

There will have five modules on this software system, which is present as below.

1. VideoSplitter - Split video to multi-frames.
2. CameraCalibrator - Calibrate camera through the image.
3. SocialDistanceCalculator - Calculate the distance between the nearst bounding boxes and confirm whether the distance violates the social distance.

### Example

* video = VideoSplitter(video_path)

* cameracalibration = CameraCalibration(video)

  > intrinsic_matrix = cameracalibration.calculate_intrinsic_matrix()

  > extrinsic_matrix = cameracalibration.calculate_extrinsic_matrix()

  > undistortimage = cameracalibration.undistort(video[0],intrinsic_matrix,extrinsic_matrix)

* socialdistancecalculator = SocialDistanceCalculator()

  > array_of_the_bounding_box_coordinate = socialdistancecalculator.find_nearest_boundingbox_coordinate()

  > viloate, bounding_box_pair_label, bounding_box_pair_distance = socialdistancecalculator.judge_viloate(array_of_the_bounding_box_coordinate)

## Engineering Infrastructure

### Version Control

- Git

### Programing Language

- Video split function, Camera calibration function and Social distance calculation function will be completed by c++.

- Object tracking function and Generate analysis report function will be completed by python.

### Make-Pybind-Pytest

- The build system will convert the c++ function into python function through make and pybind.

- The python code will be tested by pytest.

### Project Step

Analysis report will be created using FPDF.

This project will be completed by executing the following steps:

- [ ] Complete the video splitter function.

- [ ] Complete the camera calibration function.

- [ ] Complete the social distance calculation function.

- [ ] Python binding.

- [ ] Final testing.

## Schedule

| Week | Schedule |                                                                                                     
| ------------- | ------------- |
| Week 1  | 1. Environment Construct<br />2. Familiar with the camera calibration method<br />3. Familiar with the Video split method<br /> |
| Week 2  | 1. Familiar with the tools<br />2. Familiar with the camera calibration method<br />3. Familiar with the Video split method<br /> |
| Week 3  | Implement VideoSplitter | 
| Week 3  | Implement VideoSplitter |
| Week 4  | Implement CameraCalibratior |
| Week 5  | Implement CameraCalibratior  |
| Week 6  | Testing function   |
| Week 7  | Build Workflow|
| Week 8  | Project Presentation  |

## References
1. [Camera calibration] https://github.com/opencv/opencv/blob/master/samples/cpp/calibration.cpp
2. [YOLOv4 Optimal Speed and Accuracy of Object Detection] https://arxiv.org/pdf/2004.10934.pdf
3. [Deep-sort] https://github.com/nwojke/deep_sort

