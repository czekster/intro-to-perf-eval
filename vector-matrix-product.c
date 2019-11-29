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

 * Following code does a Vector-Matrix Product (VMP) for a Discrete Time Markov Chain (DTMC). 
 * Input is a DTMC (stochastic matrix).
 * Output is a uniformised probability vector.
 * Author: Ricardo M. Czekster (rczekster@gmail.com)
 * Date: 25/11/2019
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>     // memcpy
#include <math.h>       // pow, sqrt

#define ORDER 3         // model size
#define MAXRUNS 1000000 // number of runs
#define RESIDUE 1e-10   // residual difference between two iterations

/** Checks for convergence, i.e., all positions from two vectors must be greater than the RESIDUE constant. */
int converge(float *r1, float *r2) {
   int i;
   for (i = 0; i < ORDER; i++)
      if (sqrt(pow(r1[i] - r2[i], 2)) > RESIDUE)
         return 0;
   return 1;
}

/** Performs a vector-matrix product. */
void multiply(float *v, float m[ORDER][ORDER]) {
   int i,j;
   float aux[ORDER];
   for (i = 0; i < ORDER; i++) {
      aux[i] = 0;
      for (j = 0; j < ORDER; j++)
         aux[i] += m[j][i] * v[j];
   }
   memcpy(v, aux, sizeof(float) * ORDER);
}

int main(int argc, char *argv[]) {
   /*Change to *your* matrix here or build a text file reader containing the input DTMC matrix.*/
   float D[ORDER][ORDER] = {
      { 0.470588235, 0.176470588, 0.352941176 },
      { 0.470588235, 0.0        , 0.529411765 },
      { 0.176470588, 0.117647059, 0.705882353 }
   };
   int i;
   int runs = 0;
   float pvec[ORDER];
   float old[ORDER];
   pvec[0] = 1.0;  // initialise first position
   for (i = 1; i < ORDER; i++)
      pvec[i] = 0.0;
   do {
      memcpy(old, pvec, sizeof(float) * ORDER); // copy to old array
      multiply(pvec, D);
      if (++runs > MAXRUNS)
         break;
   } while (!converge(old, pvec));
   printf("Number of iterations: %d\n", runs-1);
   for (i = 0; i < ORDER; i++)
      printf("%d=%f\n", i, pvec[i]);
}
