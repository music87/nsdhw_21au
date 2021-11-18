===================================================================
Simple Polyhedral Structure
===================================================================

The GitHub repository: https://github.com/ran-ablaze/Simple-Polyhedral-Structure

Basic Information
=================

The polyhedral model is a powerful mathematical framework that reasons about loops in programs. Each lattice point inside a polyhedral corresponds with one instance of statement within nested loops.

Problem to Solve
================

The interest of using polyhedral representations is that they can be manipulated or optimized with algorithms whose complexity depends on their structure. Furthermore, generic and compact solutions can be designed that depend on program parameters. 

The Simple Polyhedral Structure tries to use C++ to construct a simple API to express the model and allow the users to optimize the model by using simple instruction.

The structure has a scheduling language featuring novel commands for targeting multiple high performance architectures. It is designed to enable easy integration of code generators for new architectures.

The focus of the implementation is to treat the loop structure as a polygon structure and to do a mapping transformation of this structure.

.. image:: affine_transformation.JPG

Prospective Users
=================

Almost all loops in a majority of High Performance Computing programs and deep learning. Users don't need to know how to optimize their code, they just need to tell my API how they want to optimize!

System Architecture
===================

Simple Polyhedral Structure can use simple instructions to declare a function that does loops and generate specified optimized object file.

The ``param`` class represents the parameters passed to the function.

The ``iter`` class represents the iterator variables. The range defines the range of the loop around the computation.

The ``expr`` class represents the expressions.

The ``comput`` class represents the computations that share schedules up to a level. A computation has an expression and iteration domain defined using an iterator variable. It contains many optimization functions.

API Description
===============

The ``iter`` class and ``comput`` class should be constructed with variable name, range of loop and the statement in the loop.

Function in `comput` class

* ``parallelize()``: parallelize the for loop with specified layer.
* ``vectorize()``: vectorize the for loop with specified layer and vector size.
* ``tiling()``: tiling the loop.
* ``codegen()``: generate the loop code.
* more to be continued

Example
~~~~~~~~~~~

Code to be implemented in a simple polyhedral structure:

.. code-block::

  foo(int A[M][N], int B[M][N]) {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 5; j++)
        B[i][j] = A[i][j] + 100;
  }
      
Implementation in a simple polyhedral structure:

.. code-block:: c++

  #include "simple_polyhedral_structure.h"
  
  void generate_code() {
    // 1. Specify the function nam
    f_name("foo");
    
    // 2. Declare function parameter 
    param A("A", {"i", "j"}, {M, N}, int);
    param B("B", {"i", "j"}, {M, N}, int);
    
    // 3. Declare iterator variables 
    iter i("i", 0, 3);
    iter j("j", 0, 5);

    // 4. Declare expressions
    comput exp("B", {i,j}, (A(i, j) + 100));
    
    // 5. Specify optimizations
    exp.parallelize(i);

    // 6. Generate the object file with the specified function
    codegen({&A, &B}, "foo.o");
  }

Engineering Infrastructure
==========================

I plan to use google test as my testing framework.

Schedule
========

Week 1:
  Implement the iter class.

Week 2:
  Implement the expr class.

Week 3:
  Implement the comput class constructors.

Week 4:
  Implement the codegen() function and corresponding unit tests.

Week 5:
  Implement one optimization finctions in comput class and corresponding unit tests.

Week 6:
  Implement one optimization finctions in comput class and corresponding unit tests.

Week 7:
  Implement one optimization finctions in comput class and corresponding unit tests.

Week 8:
  Overflown work.

References
==========

* Polyhedral compilation community :
  https://polyhedral.info/
