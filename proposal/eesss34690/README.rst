=============================================================================
Proposal for FFT Computing Optimization base on Columnar Array (CA-FFT)
=============================================================================

Basic information
=================

The GitHub repository is at: `Github Repo <https://github.com/eesss34690/Cache_Optimization.git>`__

Problem to solve
================

Computing `Fast Fourier Transform <https://en.wikipedia.org/wiki/Fast_Fourier_transform>`__ is very important for digital recording, sampling. It is an algorithm computing the discrete Fourier transform (DFT) of a sequence. Since the sequences usually include lots of data and the computation of FFT is heavy, fasten up the solving speed is crucial for saving caching memory and also optimizing the computing speed.

Currently the most common method to do FFT is ``Cooley-Tukey algorithm``. In this algorithm, it keeps breaking down a DFT of any size :math:`N = m \\times n` into smaller DFTs of sizes :math:`m` and :math:`n`, along with :math:`O(N)` multiplications by twiddle factor (typically either :math:`m` or :math:`n` is a small factor). Therefore, the DFT can be expressed as below:

.. math::

    DFT_{mn}= (DFT_m \otimes I_n)D_{m,n}(I_m \otimes DFT_n)L_m^{mn} \\
    D_{m,n} = \oplus_{j=0}^{m-1}diag([w_{mn}^i]_{0\leq i \lt n})^j

To optimize the computation, there are several categories that can implement. For example, we can optimize the cache usage for the complex computation. This can be done by ``blocking`` and ``buffering`` the data. With ``blocking``, we can operate the whole data with multiple same-size subset. Therefore, data loaded into the faster levels of the memory are reused. Because we are dealing with multi-dimensional data, the data which are closed to each other may be far away in memory. As the result, using ``buffering`` to copy the desired block into a columnar array and boost the performance. 

What is more, optimizing CPU level data like registers is also a good method. As the case for blocking, implementing it on registers can reduce traffic between the cache and the CPU. Also the simple method is to use precomputed constant for computation, which allows kernel loads the data.

In this project, a toolkit will be made to help the users to compute FFT with given value with optimized speed.

Prospective users
=================

People who needs to deal with digital or audio signal processing can use this toolkit to quickly generate the result. 

System architecture
===================

The system includes the following components:

1. ``FFT``: the computation of DFT.
2. ``view``: to display the final chart of the FFT.

After the computation of FFT, the data can be displayed by using ``view``.

API description
===============

Some parameters are needed for the API
1. ```N```: size of the input vector
2. ```n```: exponent in base 4
3. ```Y```: output vector
4. ```X```: input vector
For instance, to calculate ```64``` sample points of frequency ```4```, with input ```X``` signal, we can get sample output ```Y``` by calling:
```FFT(64, 4, Y, X)```

Engineering infrastructure
==========================

The system uses C++ to define the data structure and Python for high-level API,
and will be built with `cmake <https://cmake.org>`__.

The repository is hosted on GitHub and will use GitHub Action for continuous
integration.



Schedule
========

The development of the project will take 8 weeks:

* Week 1: Building DFT structure for usage
* Week 2, 3: Optimize with initial value, construct buffer
* Week 4, 5: Do ```cache optimization``` by using blocking
* Week 6: Use python for testing and Validation with other tools
* Week 7: Prepare for presentation
* Week 8: Buffer week for soft adjustment

Reference
==========
1. `Fast Fourier Transform <https://en.wikipedia.org/wiki/Fast_Fourier_transform>`__
2. `Scipy FFT <https://docs.scipy.org/doc/scipy/reference/tutorial/fft.html>`__
