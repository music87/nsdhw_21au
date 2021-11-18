================
My Universe
================
--------------------------
chrisPyr @ 2021 NSD autumn
--------------------------

Basic Information
=================
Project Github Link: https://github.com/chrisPyr/My_Universe

Problem to Solve
================

| We all learned "Kepler's laws of planetary motion"[1] in high school.
| The Kepler's laws can be explained and proved by Newtonian Mechanics[2].
| Though the laws would fail to predict the orbits or speed of planets accurately in some certain conditions, e.g. Perihelion Motion of Mercury[3](fig. 1) and that's why we need "Theory of Relativity" to help us to describe and predict more precisely.
| Einstein did prove this on his paper[4].
| But that's not a point I need to worry about, Newtonian Mechanics should predict precise enough. I plan to build up a program that can predict the orbits of planets only take Newtonian Mechanics into account.
| The kind of problem is actually a N-Body problem. And there is no general solution to N-Body problem, we can only try to simulate it with a numerical method.
| The simplest idea is to compute all interation force between each body, which is a Brute-force method.
| By calculating the acceleration and velocity of each time step, we can predict the position of bodies next moment. However, in real life the acceleration and velocity changes even in each time step.
| Although when time step is small enough, the results should be good enough. But we can try to use "Runge-Kuta Methods"[5] to improve results.
| In my plan, the final product should be able to show the orbits, periods of planets. And it can be compared with the real world data to prove the correctness and also incorrectness of Newtonian Mechanics.
| And also do I want to add some intersting feature into it, e.g. users can add/delete planets into/in the system to see how the entire system changes.


.. image:: images/Precessing_Kepler_orbit_280frames_e0.6_smaller.gif

Prospective Users
=================

| This can be used as a supplementary tutorial to high school students and a example to N-body simulation.

System Architecture
===================

| The default of building the system would create the solar system in a gif or mp4 format. I plan to use Python matplotlib to do the animatin creation part[6].
| Users can add one or more planets by providing three parameters: intial velocity, position, and mass.
| To build the solar system I also need information about solar system initial parameters, I plan to get the data from "JPL Horizon(NASA)"[7].

Needed Parameters:
    - default(build a solar system)
    - initial acceleration, velocity, position
    - time step, time period(tunable)

Program Features:
    - export information of calculated result such as formula of orbit, speed/period of a planet
    - export a gif or mp4 file to show the drawing result within a time period
    - add user-defined planets
    - delete planets

Constraints:
    - only be able to simulate a period of time, because N-body problem is a chaos system, we don't know the trajectory after our simulation
    - we cannot perform real integration on computer, so the results may not be perfectly match the real world

System Major Components

| 1. Parameter Parser: Python, check validity of parameters
| 2. Planet class: C++ class, store information of a planet, including mass, velocity, acceleration, position
| 3. System class: C++ class, contains all planets object, and prvide operation for computing new position at each time step for each planet
| 4. ODE class: C++ class, contains several ODE integration methods for system class to call(I will implement Euler Method and Runge-Kutta Method at least)
| 5. Animation Printer: Python, print the simulated trajectory


| In ODE class, I will implement Runge-Kutta method in 4th order, and Runge-Kutta method is designed for initial value problem. The key idea of it is that it takes few acceleration values in each time step and average them.
| More details about how to simulate a orbit by Runge-Kutta method: http://spiff.rit.edu/richmond/nbody/OrbitRungeKutta4.pdf

API description
===============

**Python API**:

- main(): Python, select operation(e.g. default, add planets, remove planets,...)
- addPlanet(initial velocity, acceleration, mass): Python wrapper, create a C++ planet object
- rmPlanet(name): Python wrapper, delete a planet from C++ system object
- computeOrbit(time period, time step):Python wrapper, compute the simulation results by given time step and time period
- printOrbit(trajectory): print the trajectory into an animation and export data

**C++ API**:

- system::addPlanet(initial velocity, acceleration, mass): create a new planet in this System
- system::rmPlanet(name): delete certain planet in this system
- system::update(): call ode method to update position
- ode::euler(system): compute position by Euler Method
- ode::RK4(system): compute position by Runge-Kutta Method



Engineering Infrastructure
==========================
**Build System**
make
(includes make, make run, make clean, make test)

**Testing Tool**
C++: Google Test
Python: pytest

I will verify my simulated results with data provided on "JPL Horizon".

**Version Control**
Git

Schedule
========

- Week 1: complete stucture of classes
- Week 2: Brute-Force method(Euler Mehtod) of two-body system
- Week 3: Brute-Force method(Euler Method) of N-body system
- Week 4: Runge-Kutta method of two-body system
- Week 5: Runge-Kutta method of N-body system
- Week 6: Print results
- Week 7: Use parallel techniques to speed up calculation
- Week 8: Prepare presentation

References
==========

| [1]: https://en.wikipedia.org/wiki/Kepler%27s_laws_of_planetary_motion
| [2]: http://vmm.math.uci.edu/odeandcm/PDF_Files/ChapterFirstPages/Chapt4Frst6Pages.pdf
| [3]: https://aether.lbl.gov/www/classes/p10/gr/PrecessionperihelionMercury.htm
| [4]: “Explanation of the Perihelion Motion of Mercury from General Relativity Theory”, 1915
| [5]: http://www.cyber-omelette.com/2017/02/RK4.html
| [6]: https://zingale.github.io/astro_animations/
| [7]: https://ssd.jpl.nasa.gov/horizons/
