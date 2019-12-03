/**
Author: Ricardo M. Czekster (rczekster@gmail.com)
Date: 2019-11-25
Modifications:
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

#ifndef __DEFS__
#define __DEFS__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/// List of events
#define ARR 0  // arrival event
#define DEP 1  // departure event

/// Properties
// stop criteria
#define SC_DURATION 0
#define SC_EVENTS   1

static int cid = 0;

/**
 * A node for the double linked list (of events).
 */
typedef struct {
   int id;
   double duration;
   double beginqueue;
   int type; // type of the event: arrival or a departure
   struct node* next;
   struct node* prev;
} node;

/**
 * Simulation properties.
 */
typedef struct {
   int stopcriteria; // look constants SC_DURATION and SC_EVENTS (above)
   double maxtime;   // if stopcriteria == SC_DURATION, then maxtime should be inspected
   int maxevents;    // if stopcriteria == SC_EVENTS, then maxevents should be inspected
} properties;

/**
 * Simulation main structure.
 */
typedef struct {
   double CLOCK;      // global time
   node* eventlist;
   properties* props; // simulation properties (see above)
} simulation;

/**
 * Function prototypes for the entire project.
 */

/////// linkedlist.c
extern int listsize(node** head);
extern void position_insert(node** head, int pos, int value);
extern void ordered_insert(int t, double clock, double value, node** head);
extern node* dequeue(node** head);
extern void dealloc(node** head);
extern void show(node** head);

/////// randomgenerators.c
extern double nextexponential(double rate);
extern double nextuniform01();
extern double nextuniform(double a, double b);

/////// yacs.c
extern void simulate();
extern void init(simulation* s);
extern void dealloc_simulation(simulation* s);

/**/

#endif // __DEFS__







