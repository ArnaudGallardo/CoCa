/*
 *
 * Project : Complexité et Calculabilité 2016, Coloration de graphe
 * Author : Arnaud GALLARDO and Khaled FAYSAL AHMED
 * Master 1 Informatique, Université de Bordeaux
 * dmSat.c
 * Used by start.sh to create a DIMACS file read by the glucose solver
 * How to : ./dmSat <nb_colors>
 *
 * dmSat must be compiled with a graph.c file following the all.h interface
 *
 */

#include "all.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/* function to calculate a factorial*/

unsigned long factorial(unsigned long f){
  if(f == 0)
    return 1;
  return (f*factorial(f-1));
}


int main(int argc, char **argv) {
  int cpt =0;
  FILE * fp = fopen("GtoD.txt", "w");
  assert (fp!=NULL);
  int k = atoi(argv[1]);
  assert(k>=2 && "The number of colors must be at least 2"); //display error messages
  int order = orderG();
  int nbClause = order + (order *factorial(k)/(factorial(2)*factorial(k-2)) +k*sizeG());
  fprintf(fp,"p cnf %d %d \n", orderG()*k, nbClause);

  printf("nb sommets: %d\n", order);

  //At least one color for each vertices
  for(int i = 1; i<= order*k; i+=k){
    for(int j = 0; j< k; j++){
      fprintf(fp, "%d ", i+j);
    }
    cpt++;
    fprintf(fp, "0\n");
  }

  //Only one color for each vertices
  for(int i=0; i < order; i++){
    for(int j = 1; j <= k; j++){
      for(int l = j+1; l <= k; l++){
	fprintf(fp, "-%d -%d 0 \n", k*i+j, k*i+l);
	cpt++;
      }
    }
  }

  //Can't share a color with any adjacent vertices
  for (int i=0; i< order; i++){
    for(int j= i+1; j<order; j++){
      if(are_adjacent(i,j)){
	for(int l =1; l<=k; l++){
	  fprintf(fp, "-%d -%d 0 \n", k*i+l, k*j+l);
	  cpt++;
	}
      }
    }
  }
  
  printf ("Clauses counter = %d \n", cpt);
  fclose (fp);
  return EXIT_SUCCESS;
}
