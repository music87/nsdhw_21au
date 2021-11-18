Basic Information
-------------------
Github Repositroy: TBD

https://github.com/S413/AllThatJazz

Problem to Solve
-----------------
Harmony Search algorithm is a heuristic optimization algorithm.
It is inspired from the method jazz musicians employ when playing
a piece, in order to find the best harmoics. The algorithm stores
a series of 'harmonies', and at each iteration generates a new one.
This new harmony is compared to the worst harmony in memory, and if
it is judged superior, the harmony memory is updated.

The algorithm has seen much use since its initial publication in 2001,
so much so that many modified versions have been created;
on the other hand, it has also been under harsh criticism. 

In any case, there seem to be few options for those wanting to use the
algorithms in python. 

Prospective Users
------------------
Anyone with an interest in optimization problems. 
The applications for the algorithm range from bullet
design to musical composition (as its origin would have it). 

System Architecture
--------------------
Harmony Search begins by initializing a Harmony Memory (HM). HM can be saved
as a matrix of size (N, HMMS), where N is the number of parameters, and HMMS
is the HM size. 

The User provides an objective function, which is stored as an array of the coefficients. 
The HM is initialized and entries are fit to the function. Keeping tabs on the worst and
best fit is important.

On every iteration of the algorithm, a new harmony is created with a probability of 1-HMCR 
(Harmony Memory Considering Rate). If an existing entry is chosen instead (p=HCMR), then it
is altered according to a Pitch Rate (PR).

The new harmony is then fit against the worst fitting entry in HM. IF the new harmony is a better
fit, then HM is overwritten; otherwise, the new harmony is simply discarded.

Harmony Search can be written as a class containing it required elements HM, HMCR, PR, and the methods
required to produce and fit the harmonies to the objective function.
The class should also store the best and worst fits in HM.

::

class HarmonySearch

{
	
	vector<vector<float>> HM;
	
	float PR;
	
	float HCMR;
	
	vector<float> best; //can consider just saving an index so as not to copy
	
	vector<float> worst; //""""
	
	vector<float> objectiveFunction;
	
	init_HM(HM); //should initialize the HM randomly
	
	fit(objectiveFunction, harmony); //should fit a harmony into Objective
	
	generate_harmony(HM, HCMR); //should generate new harmonies at every iteration either from scratch or by calling change_pitch
	
	compare_fit(new_harmony, worst, HM); //should compare the new harmony and the worst harmony in HM fit
	
	change_pitch(HM, PR); // if a new harmony is not made from scratch, one from HM is modified

}


This is a bare-bone rough idea of what the class will be.
There is also the issue of including different variations 
of the algorithm. I'm yet unsure if it would require
separate classes (with base as parent).

API Description
----------------
The harmony search algorithm class will be written in C++.
This will be wrapped in python for python use.

The user can also provide an initialized HM in addition to choosing
what mode of HSA to use.



Engineering Infrastructure
---------------------------
Testing will be done with python unittest.

The Harmony Search algorithm can be tested against other ER optimization algorithms (since they
have been compared before as well).


Schedule
--------

* Week 1: Write base Harmony Search Class.
* Week 2: Write python side: input (OF, optional HM...) reading, output (best harmony, add options for HM output...).
* Week 3: Pybind and initial testing for bare bones class.
* Week 4: Catch up on any left over work.
* Week 5: Start writing up improved HS, GHS, others (time allowing).
* Week 6: Pybind and testing.
* Week 7: Start working on Presentation.
* Week 8: Wrap up any unfinished work.


References
-----------

*https://iaeme.com/MasterAdmin/Journal_uploads/IJCET/VOLUME_10_ISSUE_1/IJCET_10_01_017.pdf
*https://www.hindawi.com/journals/cin/2015/258491/
*https://sites.google.com/a/hydroteq.com/www/
