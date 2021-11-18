Basic Information
=================

Ramanflow - a library for Raman data analysis. Check out [here](https://github.com/anva-kn/ramanflow)

Problem to Solve
=================

Raman Spectroscopy, Surface Enhanced Raman Spectroscopy (SERS), and High-Performance Liquid Chromatography (HPLC) promise to be a great tool for 2 main purposes:

1.  Detecting low concentrations (ppm and ppb scale) of hazardous chemicals inside the object of interest.
2.  Analyzing mixtures of multiple analytes.

However, up until now, the tools to analyze the spectral data and model background and peaks are not quite there yet. Even proprietary software domain there are only a few notable ones, the most prominent of them being Igor and Origin.

Nonetheless, they are GUI programs that cost money and don't integrate the pipelines that data scientists and ML researchers have established. What that community need is a python library.

Prospective Users
=================

Data scientists, scientists, and enthusiasts that are willing to explore spectroscopic data, settle for nothing less than full control of their program, don't mind writing code for that, and most importantly, do not wish to pay!

System Architecture
=================

The module should be compatible with NumPy arrays

.. image:: ramanflow_flowchart.jpeg
    :width: 400
    :height: 400

API Description
=================

Ideally, it would be available on PyPI, and one can install it using pip.

However, an alternative means of installation would be git cloning the repo and installing using make.

- Read/Save the data
    - Read .txt format files
    - Read .dat format files
    - Read .tiff format files
    - Read all files (.txt, .dat, tiff) inside one directory
- Preprocess the data
    - Remove noise
        - FFT noise removal (TBD)
        - Moving window smoothening function
    - Calculate SNR
    - Remove zeros or nans
    - Remove cosmic rays
- Process the data
    - Background modeling, interpolation
    - Peaks modeling, fitting
    - Peak clusters modeling (TBD)
    - PCA (TBD)
    - NMF (TBD)

In my mind, the user interface would be akin to any other python module. 

.. code-block:: python
   
    import ramanflow as rf
    import numpy as np

    # Assume 1d array
    example_data = rf.read('exampple.txt') # or any other format
    preprocessed_example_data = rf.preprocess.remove_cosmic_rays(example_data) # or any other preprocessing function
    # Data cleaning till this point should be sufficient for basic ML pipeline 
    # Now lets say a scientist wants to know the parameters of background or peaks
    # here he/she would create an object for background and peaks
    background_model = rf.process.background(preprocessed_data, args=...) # will take some parameters. Ex: degree of polynomial for background interpolation
    peaks_model = rf.process.peaks(preprocessed_data, args=...) # this one as well. Ex. peak shape function (Gaussian, Voight)


Engineering Infrastructure
=================


- Build System
    - make (test, clean)
- Testing Framework
    - Google Test for C++
    - Pytest for python
- Version Control
    - Git

Schedule
=================

+-------+-------------------------------------------------------------------------+
| Week  | To-Do                                                                   |
+-------+-------------------------------------------------------------------------+
| 1     | Implement read module                                                   |
+-------+-------------------------------------------------------------------------+
| 2     |   Implement Preprocessing part 1 (Noise removal)                        |
+-------+-------------------------------------------------------------------------+
| 3     |   Implement Preprocessing part 2 (Cosmic rays removal, SNR)             |
+-------+-------------------------------------------------------------------------+
| 4     |   Implement Processing part 1 (Background modeling and interpolation)   |
+-------+-------------------------------------------------------------------------+
| 5     |   Implement Processing part 2 (Peak fitting)                            |
+-------+-------------------------------------------------------------------------+
| 6     |   Binding to python, unittesting, debugging, writing basic documentation|
+-------+-------------------------------------------------------------------------+
| 7     |   Probably more debugging and feature implementation                    |
+-------+-------------------------------------------------------------------------+
| 8     |   Prepare the presenation                                               |
+-------+-------------------------------------------------------------------------+

# References

To be added
