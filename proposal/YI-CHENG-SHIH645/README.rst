Basic Information
=================
Project Link: https://github.com/YI-CHENG-SHIH645/RecommenderSystem

Collaborative Filtering (CF) is a technique used by recommender systems.


Problem To Solve
=================
Implement User-based top-N recommendation CF.
Given a user, we want to find top-k users similar
to the user from the user-item rating matrix,
the definition of similarity between user x and
user y is given as follow:

.. math::
    simil(x,y) = \frac{\sum_{i \in I_{xy}}r_{x,i} r_{y,i}}{\sqrt{\sum_{i \in I_{xy}}r_{x,i}^2} \sqrt{\sum_{i \in I_{xy}}r_{y,i}^2}}

where

:math:`r_{x, i}` : user x rate :math:`r_{x, i}` on item i

:math:`I_{xy}` : the set of items rated by both user x and user y

We can do Full Search to find top-k similar users,
but it's time complexity is :math:`O(Nd)` where N/d
is the number of rows/cols, usually we'll have a very
large user-item rating matrix, it's very slow to use
the naive approach. We'll use Locality-Sensitive Hashing(LSH)
to get this job done, which has time complexity :math:`O(d log N)`.

So now we have got k nearest users (and it's simil(x,y) values)
based on the definition of similarity, then the predicted
rating of the given user is given as follow:

.. math::
    r_{u, i} = \bar{r}_u \sum_{u' \in U} simil(u, u') (r_{u', i}-\bar{r}_{u'})

where

:math:`\bar{r}_u` : the average rating of user u for all the items rated by u.

:math:`U` :  the set of top k users that are most similar to user u.

Finally we return top n :math:`r_{u, i}` items from items that
are not yet rated by the given user u,  as the recommendation.


Perspective users
==================
Anyone who wants to get recommendation for users, the item can
be whatever it might be, like movie, book, music...


System architecture
===================
    LSH(user_id, input_file, k): return user_ids (k nearest neighbor)

    recommend(user_ids, input_file, output_file, k): write recommendations to the output_file
        aggregate result from LSH with user-item matrix

user_ids: It can receive multiple users at once.

input_file: each row contains user_id, item_id, rating.

output_file: write the recommendations for each users to here.


API description
================
python API:

    recommend(user_ids: list[int], input_file: str, output_file: str, k: int)

k: 'k' nearest neighbor


Engineering infrastructure
===========================

* build system
    * make

* testing framework
    * c++: GoogleTest
    * Python: pytest


Schedule
=========
week1:
    prototype on C++

week2:
    prototype on C++
    implement LSH

week3:
    implement LSH

week4:
    implement LSH

week5:
    aggregate result from LSH with user-item matrix to recommend

week6:
    aggregate result from LSH with user-item matrix to recommend
    python11 python API

week7:
    prepare presentation

week8:
    prepare presentation


References
==========
https://en.wikipedia.org/wiki/Collaborative_filtering

https://github.com/bowbowbow/CollaborativeFiltering

https://github.com/cchatzis/Nearest-Neighbour-LSH
