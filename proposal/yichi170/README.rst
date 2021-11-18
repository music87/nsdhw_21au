==================
Related Work Graph
==================

Basic Information
=================

GitHub Repository: TBD

Problem to Solve
================

When we are reading a paper, we would like to check the related work of it so that
we can know some of background knowledge of the paper.
This "Related Work Graph" is to visualize the related work of given paper, so that we can clearly 
see that the relevance of these papers. 

Perspective users
=================

- The researcher 
- People who are bothered and don't know which paper should read first.

System architecture
===================

From Python, User can input the title of paper and the depth of the graph of the related work.
Send the data to C++ to construct the graph of related work of this paper.

There is stll lots of things that I'm not sure how to do it. I will fill the incomplete part 
as soon as possible.

API description
===============

- Python: get_related_work
- C++: construct the graph of related work

I will find a faster way to construct the graph, and try to figure out how to get the related work.


Engineering infrastructure
==========================

- Test: 

I may use the following tools to test my project. I'm not sure how to use Google test, so I will try to figure out if I need to use it to test.

    - C++: Google test
    - Python: Pytest

- Version Control
  - Git & GitHub

- Build System
  - Make


Schedule
++++++++++
TBD

Reference
=========

Connected Papers: https://www.connectedpapers.com/
