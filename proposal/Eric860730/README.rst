============================
A simple virus spread simulation
============================

Basic Information
----------------------------
| Github repository url:
| https://github.com/Eric860730/A-simple-virus-spread-simulation

Problem to Solve
----------------------------
| In recent years, COVID-19 has been raging around the world.
| It has a great impact on everyone's lives.
| According to this article[1], the spread of COVID-19 is increasing exponentially.
| In order to prevent the spread of COVID-19, each country/region has implemented many policies (e.g. quarantine, restriction of in-store dining, lockdown...).
| These policies have produced different results in controlling the spread of COVID-19.


| I want to simulate the impact of different policies on the spread of pandemic viruses.
 User can adjust parameters(e.g. virus infection rate, virus mortality rate...) and policy to observe the final result.
 I will use animation to show the process of infection and print the distribution of the virus spread.
| Therefore, we can observe the difference in the distribution of infection under different policies.

Prospective Users
----------------------------
| Those who want to know if these policies help prevent the spread of COVID-19.
| Users can set different conditions, such as the total number of people, virus infection rate, death rate, and different policies.
| Then observe the distribution of the virus spread and the number of deaths.

System Architecture
----------------------------

Input
^^^^^^^^^^^^
* total number of people (optional, default = 1000(<= 2000))
* init number of infected people (**percentage** or **int**) (optional, default = 1%)
* moving speed of people (optional, default = 1)
* virus infection rate (optional, default = 70%)
* virus mortality rate (optional, default = 30%)
* recovery time (optional, default = 5 day)
* healthcare capacity (optional, default = The mortality rate is halved.)
* choose policy (optional, default = Free)

  Free, Attempted quarantine, Moderate distancing, Extensive distancing

* custom policy (optional, default = Free)

  * quarantine capacity (0 for no quarantine)
  * accept probability of quarantine
  * threshold of first human mobility (infected people, reduced mobility) (e.g. More than 10% of people are infected, and all people's activity is halved.)
  * threshold of second human mobility (infected people, reduced mobility) (Enhanced first human mobility)
  * threshold of free second human mobility (**percentage**) (if less than **percentage** poeple are infected, free the restriction of second human mobility)
  * threshold of free first human mobility (**percentage**) (if less than **percentage** poeple are infected, free the restriction of first human mobility)

Output
^^^^^^^^^^^^
* Animation of the virus spreading process.
* The distribution graph of virus spread.
* The number of uninfected people.
* The number of recovered people.
* The number of death people.

Mathematical Model Description
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
| This is a dynamicial system. A dynamic system is a fixed rule that describes how all points in a fixed space change over time.
| First of all, I will give an activity area, and a dot represents a person. I will use input parameters to init everyone's status and build my mathematical model.

| When running the Mathematical model, this model updates the status of everyone after each time slice. The following is the calculation of the model.
1. Check the status of everyone, find all infected poeple.
2. According to those who are infected, find out all the people who are exposed to the risk of infection around the infected person.
3. For those who are exposed at risk of infection

* check infection or not
    
  randomly produce a infection number(float) between 0 and 1, if the infection number less than virus infection rate, then this person is not infected. Otherwise, change the status of this person to infected.

4. For those who are already infected

* check death or not
    
  randomly produce a death number(float) between 0 and 1, if the death number less than virus mortality rate, then survive. Otherwise, change this person status to death.

* check recovery or not

5. Summary the status of everyone

* check whether the policy should be implemented.

* if there is no one be infected, then terminate.

6. For all survived people(at the end of update)

* check the status of position

  If there is a collision, change the direction randomly.

* check the policy implement or not.

| Execute above calculations at each time slice until there is no one be infected.

Program Workflow
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
1. Initialization

* Set up an activity area and randomly assign poeple to the area.
* Set up all input parameters.

2. Run simulator(mathematic model)

3. Print result

System Components
^^^^^^^^^^^^^^^^^
1. Parser: Python class. Parse user input parameters for simulation.
2. Simulator: C++ class. Use input parameters to simulate the spread of the virus.
3. Printer: Python class. Print simulation results with animation.

System Workflow
^^^^^^^^^^^^^^^^^
.. image:: images/system_workflow.png

Constraints
^^^^^^^^^^^^^^^^^
1. Cannot simulate the spread of virus between countries. (For example, different regions use different policies to observe the results of the spread of the virus.)
2. Cannot simulate the real situation of people moving. (Most people move regularly in daily life, but the movement of people is random during the simulation process.)
3. Cannot see the death rate of each age. (I did not consider the age of the person in the simulation. If there is enough time, I will try to finish it.)

API Description
----------------------------
1. Parser:
   
   getParameters(): Returns parsed parameters.

2. Simulator:
   
   simulateVirusSpread(parameters: parser's results): According to the user's input, the spread of the virus is simulated.
   
   customizePolicy(order=int, total_people=int, infected_poeple=int, recovered_people=int, dead_poeple=int, infection_rate=float, mortality_rate=float, recovered_time=int, people_speed=int, healthcare_cap=int, quarantine_cap=int, quarantine_accept=float)
  
* order : The order in which policy is executed. -1 indicates the policy implemented at the beginning.
* policy trigger conditions(Enter at least one) : total_people=int, infected_poeple=int, recovered_people=int, dead_poeple=int)
* all changeable parameters : other parameters.
   

3. Printer:
   
   printSpreadProcess(): Use animation to print the virus spreading process.
   
   printSpreadDistribution(): Print the distribution graph of virus spread.
   
   printConclusion(): Print the number of uninfected people, recovered people and death people.

Engineering Infrastructure
----------------------------

Build System
^^^^^^^^^^^^^^^^^^
make

Testing Framework
^^^^^^^^^^^^^^^^^^
| Python: pytest
| C++: Google test
| According to this article[1], these policies should show the following distribution(under same situation):
1. Free: exponential curve (smallest variance)

2. Attempted quarantine: flatten curve than Free (the second smallest variance)

3. Moderate distancing: flatten curve than Attempted quarantine (the third smallest variance)

4. Extensive distancing: flatten curve than Moderate distancing (largest variance)

Version control
^^^^^^^^^^^^^^^^^^
git

poetry (packaging and dependency management)

Schedule
----------------------------
* Week 1: Parser, Simulator
* Week 2: Simulator(policy: Free)
* Week 3: Simulator(policy: Attempted quarantine)
* Week 4: Simulator(policy: Moderate distancing)
* Week 5: Simulator(policy: Extensive distancing)
* Week 6: Printer
* Week 7: Flexible time(Add death rate of each age)
* Week 8: Flexible time(Add death rate of each age)

References
----------------------------
| [1]: `Why outbreaks like coronavirus spread exponentially, and how to “flatten the curve” <https://www.washingtonpost.com/graphics/2020/world/corona-simulator/>`__
| [2]: https://github.com/paulvangentcom/python_corona_simulation
