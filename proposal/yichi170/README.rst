==================
Related Work Graph
==================

Basic Information
=================

GitHub Repository: https://github.com/yichi170/RelatedWorkGraph

Problem to Solve
================

When we are reading a paper, we would like to check the related work of it so that
we can know some of background knowledge of the paper.
This "Related Work Graph" is to visualize the related work of given paper, so that we can clearly 
see that the relevance of these papers.

I will use the force-drected algorithm (Fruchterman Reingold with a little modification) to calculate the position of the node which represents a paper.
Also, I will seperate reference and citation into two part, so everytime user want to check the related work, they can only choose citation or reference.

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

- Python: get_related_work from https://www.semanticscholar.org/
- Pybind: Let Python use the function in C++
- C++: construct the graph of related work by force-directed algorithm.

Engineering infrastructure
==========================

- Test: 

I may use the following tools to test my project. I'm not sure how to use Google test, so I will try to figure out if I need to use it to test.

- ``C++: Google test``
- ``Python: Pytest``

- Version Control
  - Git & GitHub

- Build System
  - Make


Schedule
++++++++++

.. list-table::
  :header-rows: 1

  * - Date
    - Work
  * - 12/5 - 12/11
    - Finish Python / C++
  * - 12/12 - 12/19
    - Connect Python & C++ + Test
  * - 12/20 - 12/26
    - Test + Prepare presentation

Reference
=========

Connected Papers: https://www.connectedpapers.com/
