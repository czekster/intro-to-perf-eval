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

 * Following code does a the Power Method to a matrix for a Discrete Time Markov Chain (DTMC).
 * Input is a DTMC (stochastic matrix).
 * Output is a matrix to the n-th power.
 * Author: Ricardo M. Czekster (rczekster@gmail.com)
 * Date: 25/11/2019
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>     // memcpy
#include <math.h>       // pow, sqrt

#define ORDER 3         // model size
#define MAXRUNS 10000   // number of runs
#define RESIDUE 1e-10   // residual difference between two iterations

/** Checks for convergence, i.e., all positions from two vectors must be greater than the RESIDUE constant. */
int converge(float m[ORDER][ORDER]) {
   int i, j;
   for (i = 0; i < ORDER-1; i++)
      for (j = 0; j < ORDER; j++)
         if (sqrt(pow(m[i][j] - m[i+1][j], 2)) > RESIDUE)
            return 0;
   return 1;
}

/** Performs a vector-matrix product - this is a classic algorithm available in the Internet */
// based on https://www.programmingsimplified.com/c-program-multiply-matrices
void multiply(float m[ORDER][ORDER]) {
   int c,d,k;
   float aux[ORDER][ORDER];
   float tot = 0.0;
   for (c = 0; c < ORDER; c++) {
      for (d = 0; d < ORDER; d++) {
        for (k = 0; k < ORDER; k++)
          tot += m[c][k] * m[k][d];
        aux[c][d] = tot;
        tot = 0;
      }
   }
   memcpy(m, aux, sizeof(float)*ORDER*ORDER);
}

int main(int argc, char *argv[]) {
   /*Change to *your* matrix here or build a text file reader containing the input DTMC matrix.*/
   float D[ORDER][ORDER] = {
      { 0.470588235, 0.176470588, 0.352941176 },
      { 0.470588235, 0.0        , 0.529411765 },
      { 0.176470588, 0.117647059, 0.705882353 }
   };
   int i, j;
   int runs = 0;
   do {
      multiply(D);
      if (++runs > MAXRUNS)
         break;
   } while (!converge(D));
   printf("Number of iterations: %d\n", runs-1);
   for (i = 0; i < ORDER; i++) {
      for (j = 0; j < ORDER; j++)
         printf("%f ", D[i][j]);
      printf("\n");
   }
}
