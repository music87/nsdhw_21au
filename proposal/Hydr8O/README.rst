Basic information
=================

Project link:
-------------
https://github.com/Hydr8O/nsd-project

Problem to solve
================

Problem Description
-------------------
Many companies in various industries store data about different procedures in a structured way for future use.

However, there are a big chunk of unstructured data in the form of paper documents that is needed to be converted into structured format manually.

The goal of this project is to automate manual data retrieval from the paper sources (OCR).

Methods Description
-------------------

To achieve the goal of the project, the whole procedure divided into two major sequential stages:

1. Image pre-processing.

   The main target of this stage is to get a top-down view of a document being processed which is achieved by following the pipeline:

 1. Edge detection - getting image edges.
 
 2. Contour detection - detecting contours based on the edges.
 3. Image warping - warping an image to get the top-down view for the text retrieval.


2. Textual data retrieval.
 
 The main instrument used for extracting text data from an image is OCR. 

Prospective Users
-----------------
Anyone who is in need for converting unstructured paper document data into a structured format (a company to track its own data, a data scientist wanting to get data from a document, etc.)

System Architecture
===================


Overall Workflow
----------------
Image preprocessing:

.. image:: ./images/image-preprocessing.png

Text data extraction:

.. image:: ./images/text-extraction.png

Modularization
--------------
Software consists of 5 modules each responsible for its own task:

1. ImagePreprocessor - initial preprocessing(gray-scale conversion, noise reduction).
 
2. EdgeDetector - edge detection in an image.
 
3. ContourDetector - contour detection in an image.
 
4. DocumentWarper - extract document from an image and warp it so that it is in a top-down view. Calls functions from 1-3. Stores results of 1-3 for debugging purposes.
 
5. TextRetriever - retrieve text information from an image.

API Description
===============
 
Pipeline: Image -> ImagePreprocessor -> EdgeDetector -> ContourDetector -> DocumentWarper -> TextRetriever
 
Usage example:

document_warper = DocumentWarper(image)

top_down_view_document = document_warper.warp()

 preprocessed_image = document_warper.get_preprocessed_image() #for debugging
 
 edge_image = document_warper.get_edge_image() #for debugging
 
 contour_image = document_warper.get_contour_image() #for debugging

text_retriever = TextRetriever(top_down_view_document)

text = text_retriever.retrieve()

Engineering Infrastructure
==========================

Build system will leverage make tool and pybind.

Testing will be conducted using pytest.

Documentation will be created and formated using Sphinx.

New version will be released after completion of major steps, namely:

1. Finish image pre-processing.
2. Finish text retrieval.
3. Finish python binding.
4. Finish final testing.

Schedule
========

* Week 1
 Set up the environment with all required dependencies.
 
 Make sure that everything has been installed properly.
 
* Week 2
 Get familiar with the tools.

* Week 3
 Implement image pre-processing stage.
 
 Write tests for the stage and conduct testing with different inputs.

* Week 4
 Implement text data retrieval stage.
 
 Write tests for the stage and conduct testing different inputs.

* Week 5
 Pipe the results from the image pre-processing into text data retrieval.
 
 Write tests for the whole pipeline and conduct testing different inputs.

* Week 6
 Implement build workflow.

* Week 7
 Conduct final testing with python.
 
* Week 8
 Make the project presentation.

References
==========
