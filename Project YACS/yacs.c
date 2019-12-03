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

#include "defs.h"

/**
 *
 */
void init(simulation* s) {
   srand(time(NULL));
   s->CLOCK = 0.0;
   s->eventlist = NULL;
   s->props = (properties*) malloc(sizeof(properties));
   s->props->stopcriteria = SC_DURATION;
   s->props->maxtime = 100000.0;  // simulation target time (10.000 min)
   // if you would want to use number of events as stop criteria, uncomment the following lines
   //s->props->stopcriteria = SC_EVENTS;
   //s->props->maxevents = 100;           // e.g. 100 events
}

/**
 *
 */
void simulate(simulation* s) {
   int numevents = 0;       // number of events
   double duration;
   double utilization;      // perf metrics
   double population;       // ""
   int entities = 0;
   int numarrivals = 0;     // counter for arrivals in the system
   int numdepartures = 0;   // counter for departures in the system
   int processed = 0;
   int departed = 0;
   int servers = 1;         // ---> change the number of servers
   node* nextevent;
   double elapsedtime;
   double busytime = 0.0;
   double queuelength = 0.0; // counter for queuelength (number waiting)
   double queueing = 0.0;
   double totaltime = 0.0;
   double servicetime = 0.0;
   double saveclock = 0.0;
   double mu = 0.0;
   FILE *fp;                 // file for logging
   // rates
   double arr_rate = 60.0/11.0; // rates over one hour
   double dep_rate = 60.0/(8.0/(double)servers); // rates over one hour - increases velocity for more servers

   // start the scheduler with an arrival schedule to happen according to the arrival rate
   duration = nextexponential(arr_rate);  // according to the arrival rate
   ordered_insert(ARR, s->CLOCK, duration, &(s->eventlist)); // schedule an arrival

   // creates a log file
   fp = fopen("output.txt", "w");
   if (fp == NULL) {
      printf("Error opening file!\n");
      exit(EXIT_FAILURE);
   }

   // start consuming events from the event list (this is the DES core implementation)
   do {
      nextevent = dequeue(&(s->eventlist)); // dequeue next node from the event list
      elapsedtime = nextevent->duration - s->CLOCK;
      if (numevents % 1000 == 0)
         printf("simulation clock: %f events: %d\r", s->CLOCK, numevents);

      if (entities != 0)
         busytime = busytime + elapsedtime;
      saveclock = s->CLOCK;
      s->CLOCK = nextevent->duration; // updates the simulation clock (discrete time)
      // microcode for each possible event within the DES
      switch (nextevent->type) {
         case ARR: // arrivals
            queuelength = queuelength + entities;
            entities = entities + 1;
            if (entities <= 1) {
               duration = nextexponential(dep_rate);  // according to the departure rate
               ordered_insert(DEP, s->CLOCK, duration, &(s->eventlist)); // schedule a departure
               mu = mu + duration;
               processed = processed + 1;
               //queueing = queueing + (s->CLOCK - nextevent->beginqueue);
            }
            // schedule the next arrival
            duration = nextexponential(arr_rate);
            ordered_insert(ARR, s->CLOCK, duration, &(s->eventlist));
            numarrivals = numarrivals + 1; // count only arrivals
            break;
         case DEP: // departures
            entities = entities - 1;
            if (entities >= 1) { // schedule the departure for the next entity (starts serving the next)
               duration = nextexponential(dep_rate);  // according to the departure rate
               ordered_insert(DEP, s->CLOCK, duration, &(s->eventlist)); // schedule a departure
               departed = departed + 1;
               queueing = queueing + (saveclock - nextevent->beginqueue);
            }
            numdepartures = numdepartures + 1; // count only departures
            break;
      }
      numevents = numevents + 1;
      // free the node
      free(nextevent);
   } while ((s->props->stopcriteria == SC_DURATION && s->props->maxtime >= s->CLOCK) ||
            (s->props->stopcriteria == SC_EVENTS && s->props->maxevents >= numevents));

   // reporting
   printf("simulation clock: %f events: %d\r", s->CLOCK, numevents); // flushes previous \r
   printf("\nEvents: %d\n", numevents);
   printf("Busy Time: %f\n\n", busytime);
   printf("Arrivals: %d\n", numarrivals);
   printf("Departures: %d\n", numdepartures);
   printf("Processed departures: %d\n", processed);
   printf("Servers: %d\n", servers);
   printf("Arrival   [time=%f -> rate=%f]\n", 60.0/arr_rate, arr_rate);
   printf("Departure [time=%f -> rate=%f]\n\n", 60.0/dep_rate, dep_rate);
   // performance metrics
   printf("\nPerformance metrics\n");
   utilization = busytime / s->CLOCK;
   printf("\tUtilization: %f\n", utilization);
   population = queuelength / (double)numarrivals;
   printf("\tQueue length: %f\n", population);
   totaltime = (queueing + mu) / (double)processed;
   queueing = queueing / (double)processed;
   servicetime = mu / (double)processed;
   printf("\tavg total time: %f\n", totaltime*60);
   printf("\tavg queueing time: %f\n", queueing*60);
   printf("\tavg service time: %f\n", servicetime*60);
   fclose(fp);
}

/**
 * Dealloc the entire simulation and its structures
 */
void dealloc_simulation(simulation* s) {
   dealloc(&(s->eventlist)); // frees the remaining nodes from the dynamic list
   free(s->props);
}
