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
int listsize(node** head) {
   int c = 0;
   node* aux = *head;
   while (aux!=NULL) {
      c = c + 1;
      aux = aux->next;
   }
   return c;
}

/**
 * Insert element on position.
 */
void position_insert(node** head, int pos, int value) {
    int i, tam;
    tam = listsize(*head);
    node* aux = *head;
    node* target;
    if (pos <= tam && pos >= 0){
        target = (node*) malloc(sizeof(node));
        target->duration = value;
        if (pos == 0){
            target->next = *head;
            *head = target;
        } else {
            for (i=0; i < pos - 1; i++) {
                aux = aux->next;
            }
            target->next = aux->next;
            aux->next = target;
        }
    }
}

/**
 * Insert element by ascending order considering 'value' parameter.
 */
void ordered_insert(int t, double clock, double value, node** head) {
   node* aux = *head;
   node* elem;
   node* next;
   elem = (node*) malloc(sizeof(node));
   elem->duration = clock + value; // T + value
   elem->beginqueue = clock;
   elem->type = t;
   cid = cid + 1;
   elem->id = cid;
   if (*head == NULL) {
      elem->next = NULL;
      elem->prev = NULL;
      *head = elem;
   } else {
      if (aux->duration >= elem->duration) {
         elem->next = *head;
         elem->prev = NULL;
         (*head)->prev = elem;
         *head = elem;
      } else {
         while (elem->duration > aux->duration && aux->next != NULL) {
            next = aux->next;
            if (elem->duration < next->duration)
               break;
            aux = aux->next;
         }
         elem->next = aux->next;
         elem->prev = aux;
         aux->next = elem;
         next = elem->next;
         if (elem->next != NULL)
            next->prev = elem;
      }
   }
}

/**
 * Consume the first element of the list.
 */
node* dequeue(node** head) {
   node* aux = *head;
   if (*head != NULL)
      *head = (*head)->next;
   return aux;
}

/**
 *
 */
void dealloc(node** head) {
   node* aux = *head;
   node* target = aux;
   while (target != NULL) {
      aux = aux->next;
      free(target);
      target = aux;
   }
   if (*head != NULL)
      free(*head);
}

/**
 *
 */
void show(node** head) {
   node* aux = *head;
   printf("List contents:\n");
   while(aux != NULL) {
      printf("%d -> %2.6f\n", aux->type, aux->duration);
      aux = aux->next;
   }
   printf("\n");
}

