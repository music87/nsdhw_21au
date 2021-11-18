Job shop scheduling
===================

Basic information (including the GitHub repository)
===================

Job-shop scheduling or the job-shop problem (JSP) is an optimization
problem in computer science and operations research.

I would try to use genetic-algorithm solve the JSP.

**GitHub repository**: https://github.com/BoWeii/job-shop-scheduling 

Problem to solve
===================
In a general job scheduling problem, we are given n jobs **J1, J2, ...,
Jn** of varying processing times,each job consists of a set of
operations **O1, O2, ..., On** which need to be processed in a specific
order (known as precedence constraints). Each operation has a specific
machine that it needs to be processed on and only one operation in a job
can be processed at a given time. We need to schedule the jobs on **m**
machines with varying processing power, while trying to minimize the
makespan. |image0|

Perspective users
===================

Some automated processing factories or people with similar needs will
need this algorithm

System architecture
===================
-  **Requure parameters and datas**

   1. population size 
   2. crossover rate 
   3. mutation rate 
   4. number of iteration
   5. processing table for Jobs/Operations (Job size <=1000)
   6. machine sequence table for Jobs/Operations (machine size <=100)
   
-  **Python:**

   1. initialize the informantion and parameters 
   2. output the time consume
   3. render the result as Gantt Chart


-  **C++:**  

   All of Genetic-Algorithm working
   
   1. make the problem could be a representation to solved
   2. make evaluation function, In our case, the fitness of each individual is evaluated as the following total elapsed time of the corresponding schedule:
      f(Si) = max{ ft(j) | 1<= j <= N}  Where ft(j) is the finishing time of job j.
   3.	make a Crossover, delete relatively excessive genes or to add relatively necessary genes to make them become to the legal offsprings.
   4.	make a Mutation: generate randomly two positions in the list and exchange their genes, and if the two genes are same one, retry to select new positions.
   5.	select the best pop-size individuals conforming their fitness for next generation
   6.	keep the best individual

     

-  **Workflow:** 
|image1|

API description
===================

-  **Python**

   1. **__init__()**: init the params and table data
   2. **Gen_gantt()** : generate the Grantt Chart by plotly

-  C++

   1. **Gen_init_group()** : random the Initializaion group.
   2. **Evaluate()** : evaluation function rating solutions in terms
      of their fitness
   3. **Keep_best()**: all individuals are compared with the best
      one, if an individual which is better than the current best
      individual, the individual is kept as the new best one.
   4. **Crossover()** : propose a partial schedule of exchanging
      crossover.
   5. **Mutation()** : generate randomly two positions in the list and
      exchange their genes, and if the two genes are same one, retry to
      select new positions.
   6. **Elitist_select()**: select the best pop-size individuals
      conforming their fitness for next generation

Engineering infrastructure
==========================
-  **Build System**

   make

-  **Testing Tool**

   1. C++: GoogleTest
   2. Python: pytest

-  **Version Control**

   git

Schedule
========

- Week 1: create the structure and environment in python and c++
- Week 2: implement the **Gen_init_group()**
- Week 3: implement the **Evaluate()** and **Keep_best()**
- Week 4: implement the **Crossover()**
- Week 5: implement the **Mutation()** 
- Week 6: implement the **Elitist_select()** and check the correctness of some unit_test 
- Week 7: output the result as Grantt-Chart
- Week 8: prepare presentation


References
==========

| [1]: https://en.wikipedia.org/wiki/Job-shop\_scheduling
| [2]: https://ieeexplore.ieee.org/document/400072
| [3]: https://plotly.com/python/

.. |image0| image:: https://i.imgur.com/XMlXh4Z.png
.. |image1| image:: https://i.imgur.com/YCJHWZh.jpg
