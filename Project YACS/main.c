/**
************YET ANOTHER COMPUTER SIMULATION TOOL******************
**********************YACS****************************************
Author: Ricardo M. Czekster (rczekster@gmail.com)
Date: 2019-11-25
******************************************************************
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
int main() {

   simulation *sim = (simulation*) malloc(sizeof(simulation));
   init(sim);
   simulate(sim);

   dealloc_simulation(sim);
   free(sim);

   return EXIT_SUCCESS;
}
