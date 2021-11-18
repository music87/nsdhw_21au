================================
Project Proposal: Diffusion Maps
================================

Basic Information
=================

Repository: https://github.com/abt8601/diffusion-maps

Problem to Solve
================

This project aims to implement diffusion maps [1],
a method of non-linear dimensionality reduction.
This method works, in short,
by defining a diffusion process on data based on a local similarity metric,
then performs dimensionality reduction
in a way that preserves the "diffusion distance",
a metric that captures the underlying "geometry" of the data.

Curse of dimensionality,
a term that often emerges in the machine learning circle,
refers to a phenomenon where higher-dimensional data breaks methods
which otherwise would work well on lower-dimensional data.
Therefore, a technique, dimensionality reduction,
could serve as a preprocessing step.
However, many popular dimensionality reduction techniques, like PCA or MDS,
are linear and fail to recognise
the non-linear underlying structure of some dataset.
(Imagine a point cloud shaped like a Swiss roll.)
Non-linear dimensionality reduction techniques
do not suffer from these problems,
and diffusion maps is one of them.
Diffusion maps also enables extracting the features at different "scales".

Refer to [2] for an introduction to diffusion maps.
(Note, however, that
we believe that some mathematical expositions in the literature are imprecise.)

The Mathematics Behind the Problem
----------------------------------

The following formulation is abridged and revised from that of [2],
which is more elementary and directly relates to the implementation.

Let ``Xᵢ`` be the given set of data where ``i = 1, 2, ..., n``
and ``k(x, y)`` be the kernel function (known as the diffusion kernel)
satisfying the following properties

- ``k`` is symmetric: ``k(x, y) = k(y, x)``
- ``k`` is positivity preserving: ``k(x, y) ≥ 0``

The kernel defines a local similarity measure.
Its value should be high for points close by
and quickly go to zero outside a certain neighbourhood.
An example is the popular radial basis function kernel
(referred to as the Gaussian kernel in some literatures)
``k(x, y) = e^(-γ∥x − y∥²)``.

We then define a random walk on the data points,
where the probability of jumping from point ``x`` to point ``y`` is
``p(x, y) = k(x, y) / d(x)``
where ``d(x) = Σ_y k(x, y)`` is the normalisation constant.
Intuitively, it is easier to jump to a nearby point than to one far away.

Running the random walk for several time steps
reveals the "geometry" of the data.
Define ``pₜ(x, y)`` to be
the probability of jumping from point ``x`` to point ``y`` in ``t`` steps.
(The explicit formula is given by the Chapman-Kolmogorov equation).
It is easy to jump along paths where data points are dense,
so ``pₜ(x, y)`` is high if ``x`` and ``y`` are "well-connected".

Now, we define the diffusion distance ``Dₜ(Xᵢ, Xⱼ)`` by
``Dₜ(Xᵢ, Xⱼ)² = ∥pₜ(Xᵢ, *) − pₜ(Xⱼ, *)∥²_l²(ℝⁿ, D⁻¹)``.
Intuitively, ``Dₜ(x, y)`` is small whenever
``x`` and ``y`` are similarly well-connected or disconnected
to every other points.
For example, if the points form two non-intersecting lines,
then two points on the same line have a low diffusion distance
because a third point is
either well-connected to both of the two points if it lies on the same line,
or disconnected from both of the two points if it lies on a different line.
The opposite is true for two points on different lines.
So the diffusion distance is a metric
that captures the underlying "geometry" of the data.

What is left to do is to map the data to a lower-dimensional space
such that the Euclidean distance in the new space
approximates the diffusion distance in the data space.
Let ``P`` be the probability matrix where ``Pᵢⱼ = p(Xᵢ, Xⱼ)``.
This matrix can be regarded as a transition matrix of a Markov chain.
We also have that ``pₜ(Xᵢ, Xⱼ) = Pᵗᵢⱼ``.
Let ``λᵢ`` be the i-th eigenvalue of ``P``
and ``ψᵢ`` be the corresponding eigenvector.
(It can be shown that ``P`` is diagonalisable; see later.)
If we map ``Xᵢ`` to ``Yᵢ`` where ``Yᵢⱼ = λᵗⱼ ψⱼᵢ``,
then it can be shown that ``∥Yᵢ − Yⱼ∥ = Dₜ(Xᵢ, Xⱼ)``.
Dimensionality reduction is achieved by removing dimensions
corresponding to small eigenvalues.
(In fact we can even remove the one corresponding to the largest eigenvalue,
because it is constant across data points.)
This way the Euclidean distance of the mapped data points
best approximates the diffusion distance in the data space.

We don't need to diagonalise ``P`` itself
to calculate ``P``'s eigenvalues and eigenvectors.
Let ``K`` be the kernel matrix where ``Kᵢⱼ = k(Xᵢ, Xⱼ)``.
Let ``D`` be the diagonal matrix that normalises the rows of ``K``
(i.e., ``P = D⁻¹ K``).
Then it can be shown that ``P' = D^(1/2) P D^(-1/2)``
is symmetric, has the same eigenvalues as ``P``,
and has eigenvectors easily convertible to that of ``P``.
Thus, the most difficult part of diffusion maps is to solve the
sparse symmetric eigendecomposition problem.

Prospective Users
=================

Anyone wishing to do fast non-linear dimensionality reduction using diffusion maps.

System Architecture
===================

The project mainly consists of 2 parts:
the computing layer and the Python interface layer.

Computing Layer
---------------

The computing layer is written in C++.
It can be further divided into 2 parts:
the data structures and the numerical computation routines.
Data structures used are dense matrix and sparse matrix.
Numerical computation routines consist of
one for solving sparse symmetric eigendecomposition problems
and some others for the main algorithm.

Dense Matrix
~~~~~~~~~~~~

The class ``Matrix`` is for the good ol' dense matrix,
where every element is placed inside a contiguous memory buffer.
This is used to pass data for the numerical computation routines
and internal to the main algorithm routine to perform some easy computations.

Sparse Matrix
~~~~~~~~~~~~~

The class ``SMatrix`` is for the sparse matrix in the CSR format.
This is used to store the affinity matrix and to perform eigendecomposition on.

(The exact format of the sparse matrix may change
if other parts of the project calls for it.
But CSR looks good because matrix-vector multiplication is pretty fast.)

Numerical Computation Routines
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A routine (naming TBD) solves the sparse symmetric eigendecomposition problems.
It accepts a ``SMatrix`` which is assumed to be symmetric
and returns some of the largest eigenvalues and the corresponding eigenvectors.

Some other numerical routines are used to implement the main algorithm,
which calls the aforementioned routine.
(Details TBD.)

The ``DiffusionMaps`` class is used to save some intermediate results
(eigenvalues and eigenvectors),
which are used when the user performs dimensionality reduction
with different scale parameter (diffusion time).
This is similar to the ``DiffusionMaps`` class
described in the API Description section,
but with a more primitive interface.

Interfaces
~~~~~~~~~~

A basic interface is created by pybind11.
The ``Matrix`` class and the ``DiffusionMaps`` class
are exposed through this interface.

Python Interface Layer
----------------------

The Python interface layer provides a high-level Python API for the library,
complete with docstrings and type annotations.
It is a thin wrapper
around the interface of the computing layer created by pybind11
and mainly handles argument checking.
Refer to the next section for the API description.

(Presently pybind11 does not seem to be able to
provide type annotation directly.)

API Description
===============

We specify the Python API below.

Class ``Matrix``
----------------

Dense matrix.

- Constructor ``Matrix(nrow: int, ncol: int)``:
  Construct an empty matrix with ``nrow`` rows and ``ncol`` columns,
  with all elements uninitialised.
- Property ``nrow: int``:
  Number of rows.
- Property ``ncol: int``:
  Number of columns.
- Method ``m[i, j]`` (where ``i: int``, ``j: int`` and ``m[i, j]: float``):
  Access the (``i``, ``j``)-th element of the matrix ``m``.

Class ``DiffusionMaps``
-----------------------

The diffusion maps interface.

- Constructor
  ``DiffusionMaps(data: Matrix, n_components: int, affinity: str, **kwargs)``:
  Compute the diffusion maps, where

  - ``data`` is the input data matrix. Each row is a data point.
  - ``n_components`` is the number of dimensions after dimensionality reduction.
  - ``affinity`` is the type of kernel used to calculate the affinity matrix.
    See below for explanation.
  - ``kwargs`` are the optional kernel parameters. See below for explanation.

  The available kernels are

  - ``"rbf"``: Radial basis function kernel.
    The kernel parameter ``gamma`` can be passed in
    as a keyword argument to the constructor.
    If the keyword argument ``sigma`` is given,
    then ``gamma = 1 / (2 * sigma**2)``.
    If neither ``gamma`` nor ``sigma`` is given,
    then ``gamma`` defaults to ``1 / n_features``
    where ``n_features = data.ncol``.
    If both ``gamma`` and ``sigma`` are given,
    the constructor raises ``ValueError``.

  Currently only ``"rbf"`` is guaranteed to be implemented.
  Other types of kernels will be added if time allows.

- Method ``at_scale(t: int) -> Matrix``:
  Get the lower-dimensional data at diffusion time ``t``.
  The output matrix is an ``n_samples`` × ``n_components`` matrix,
  where ``n_samples = data.nrow``.

Example
-------

.. code-block:: python

  import math

  from diffusion_maps import Matrix, DiffusionMaps

  # Generate data. (Helix.)
  data = Matrix(500, 3)
  for i in range(500):
      theta = (2*math.pi) * (i/100)
      data[i, 0] = math.cos(theta)
      data[i, 1] = math.sin(theta)
      data[i, 2] = 0.5 * i

  # Calculate diffusion maps
  dm = DiffusionMaps(data, n_components=2, affinity='rbf', sigma=1e-2)
  ld_data = dm.at_scale(t=1)  # 500 * 2 matrix

Engineering Infrastructure
==========================

- Build system

  - GNU Make

- Testing

  - C++: Use Criterion to test whether or not intermediate results make sense
  - Python: Use py.test to test the matrix class
    and the algorithm on simple datasets

- Documentation

  - Docstrings on Python code

- Version control

  - Git

- Source code quality

  - clang-format for consistent code style
  - Compiler warnings to avoid bad coding practice that may lead to bugs
  - (Whether or not to use a separate linter is still under consideration.)

- Continuous integration

  - GitHub Actions

Schedule
========

- Week 1 (2021-11-01 ~ 2021-11-07):

  - Survey numerical methods
    for the sparse symmetric eigendecomposition problem
  - Set up the CI infrastructure

- Week 2 (2021-11-08 ~ 2021-11-14):

  - Implement the classes for dense and sparse matrices

- Week 3 (2021-11-15 ~ 2021-11-21):

  - Implement the numerical method
    for sparse symmetric eigendecomposition problem

- Week 4 (2021-11-22 ~ 2021-11-28):

  - Implement the numerical method
    for sparse symmetric eigendecomposition problem

- Week 5 (2021-11-29 ~ 2021-12-5):

  - Implement the numerical method
    for sparse symmetric eigendecomposition problem

- Week 6 (2021-12-6 ~ 2021-12-12):

  - Implement the main algorithm
  - Complete Python interface

- Week 7 (2021-12-13 ~ 2021-12-19):

  - Prepare demo and presentation

- Week 8 (2021-12-20 ~ 2021-12-26):

  - Prepare presentation

References
==========

1. Ronald R. Coifman, Stéphane Lafon.
   Diffusion maps.
   Applied and Computational Harmonic Analysis,
   Volume 21, Issue 1, July 2006, Pages 5–30.
   DOI: https://doi.org/10.1016/j.acha.2006.04.006
   Available: https://github.com/tesheng-lab/diffusion-maps-abt8601/blob/master/literatures/%5BCoifman%5DDiffusion_maps_2016.pdf
2. J\. de la Porte, B. M. Herbst, W. Hereman, S. J. van der Walt.
   An introduction to diffusion maps.
   In Proceedings of the 19th Symposium
   of the Pattern Recognition Association of South Africa (PRASA 2008),
   Cape Town, South Africa, November 2008, Pages 15–25.
   Available: https://github.com/tesheng-lab/diffusion-maps-abt8601/blob/master/literatures/%5BPorte_Herbst_Hereman_Walt%5DIntroduction_Diffusion_Maps.pdf
