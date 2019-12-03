/**
Author: Ricardo M. Czekster (rczekster@gmail.com)
Date: 2019-11-25
Modifications:
   2017-09-26 - add uniform random generation
*/

/*
This is YACS, Yet Another Computer Simulation software, using DES to simulate an M/M/c queue.
Copyright (C) 2019  Ricardo M. Czekster
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "defs.h"

/**
 * Returns the next exponential random variable according to a given rate (as parameter).
 * It converts a uniformly random variable to an exponential random variable.
 */
double nextexponential(double rate) {
   double unif;
   do {
      unif = rand() / (double) RAND_MAX; // a uniformly distributed variable
   } while (unif == 0.0 || unif == 1.0);
   //return (-1 * log(1 - unif) * (1.0 / rate));
   return (-log(unif) / rate); // from William Stewart's book (2009) 'Probability, Markov Chains,
                               //   Queues, and Simulation: The Mathematical Basis of
                               //   Performance Modeling'
}

/**
 * Returns the next uniform between 0 and 1.
 *
 */
double nextuniform01() {
   return (nextuniform(0, 1));
}

/**
 * Returns the next uniform between a and b.
 * If b >= a, then returns a number between 0 and 1.
 */
double nextuniform(double a, double b) {
   double unif = rand() / (double) RAND_MAX;
   if (a < b)
      unif = unif * (b - a) + a;
   return (unif);
}

