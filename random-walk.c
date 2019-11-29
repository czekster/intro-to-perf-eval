/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 * Following code simulates a Discrete Time Markov Chain (DTMC). 
 * Input is a DTMC (stochastic matrix).
 * Output is a uniformised probability vector.
 * Author: Ricardo M. Czekster (rczekster@gmail.com)
 * Date: 25/11/2019
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ORDER 3         // model size
#define MAXRUNS 1000000 // number of runs

int main(int argc, char *argv[]) {
   float D[ORDER][ORDER] = {
      { 0.470588235, 0.176470588, 0.352941176 },
      { 0.470588235, 0.0        , 0.529411765 },
      { 0.176470588, 0.117647059, 0.705882353 }
   };
   int i;
   float r;             // variable for saving random number
   int runs = 0;
   int state = 0; // starts at 0 state (could be any -- selected at random)
   int visits[ORDER];
   float acc;
   srand(time(NULL));            // set initial random seed -- based on now
   for (i = 0; i < ORDER; i++)   // states initialisation
      visits[i] = 0;
   while (runs++ < MAXRUNS) {
      r = (float) rand()/RAND_MAX;
      acc = 0.0;
      for (i = 0; i < ORDER; i++) {
         acc += D[state][i];
         if (r < acc) {
            visits[i]++;
            state = i;
            break;
         }
      }
   }
   for (i = 0; i < ORDER; i++)
      printf("%d=%f\n", i, (float)visits[i]/runs);
}
