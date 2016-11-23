/*
 *
 * Project : Complexité et Calculabilité 2016, Coloration de graphe
 * Author : Arnaud GALLARDO and Khaled FAYSAL AHMED
 * Master 1 Informatique, Université de Bordeaux
 * dmSatParser.c
 * Used by start.sh to create a JSON file read by arborjs to display the colored graph\
 * (dmSatParser is also used to display the node/color array)
 * How to : ./dmSatParser <nb_colors> <glucose_result_file>
 *
 * dmSatParser must be compiled with a graph.c file following the all.h interface
 *
 */

#include "all.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  //A small list of colors for the HTML/JS part
  const char *colors[13];
  colors[0] = "blue";
  colors[1] = "red";
  colors[2] = "green";
  colors[3] = "yellow";
  colors[4] = "orange";
  colors[5] = "pink";
  colors[6] = "indigo";
  colors[7] = "steelblue";
  colors[8] = "saddlebrown";
  colors[9] = "paleturquoise";
  colors[10] = "palegreen";
  colors[11] = "palegoldenrod";
  colors[12] = "oldlace";

  FILE * fp = fopen("web/data/graph.json", "w");
  assert (fp!=NULL);
  int k = atoi(argv[1]);
  assert(k>=2 && "The number of colors must be at least 2"); //display error messages

  int order = orderG();

  FILE * resultFile = fopen(argv[2], "r");
  assert (resultFile!=NULL && "The second argument is probably missing.");

  //We create a nbNodes sized array where the k_iest value equals the color id
  int colorsArray[order];
  //We create an array where the k value is the k+1 glucose variable status (0 = false, 1 = true)
  int exctractedColors[order*k];

  char * line = NULL;
  size_t len = 0;
  size_t read;

  //After finding the 'v' line, we are splitting the string using a space delimiter
  while ((read = getline(&line, &len, resultFile)) != -1) {
    if (line[0] == 'v') {
      //Code taken from http://en.cppreference.com/w/c/string/byte/strtok
      //printf("Parsing the input string '%s'\n", line);
      char *token = strtok(line, " ");
      while(token) {
        //puts(token);
        if (strncmp(token,"v",1) != 0) {
          if(token[0] == '-') {
            exctractedColors[-atoi(token)-1] = 0;
          }
          else {
            if(token[0] != '0') {
              exctractedColors[atoi(token)-1] = 1;
            }
          }
        }
        token = strtok(NULL, " ");
      }
    }
  }

  for(int i=0;i<order;i++) {
    for(int j=0;j<k;j++) {
      if (exctractedColors[i*k+j]==1) {
        colorsArray[i]=j;
      }
    }
  }
  //If k > 13 we don't have enough HTML colors so we are not displaying them
  if (k>13) {
    printf("Node|Color\n");
    printf("----------\n");
    for(int i=0;i<order;i++) {
      printf("%4d|%5d\n",i,colorsArray[i]);
    }
    return EXIT_SUCCESS;
  }

  //The JSON file is a dict
  fprintf(fp, "{");

  //First we create all the nodes
  fprintf(fp, "\"nodes\":{");
  for(int i = 1; i<order;++i) {
    fprintf(fp,"\"%d\": {\"color\":\"%s\"}, ",i,colors[colorsArray[i-1]]);
  }
  fprintf(fp,"\"%d\": {\"color\":\"%s\"}",order,colors[colorsArray[order-1]]); //To avoid a useless coma
  fprintf(fp, "},");

  //Then we create all the edges
  fprintf(fp, "\"edges\":{");
  for (int i=0; i< order; i++){
    fprintf(fp,"\"%d\": {",i+1);
    int first = 1;
    for(int j= i+1; j<order; j++){
      if(are_adjacent(i,j)){
        if (first > 0) {
          fprintf(fp,"\"%d\": {}",j+1); //To avoid a useless coma
          first--;
        }
        else {
          fprintf(fp,",\"%d\": {}",j+1);
        }
      }
    }
    fprintf(fp,"}");
    if (i!=order-1) {
      fprintf(fp,","); //To avoid a useless coma
    }
  }
  fprintf(fp, "}}");

  printf("Node|Color\n");
  printf("----------\n");
  for(int i=0;i<order;i++) {
    printf("%4d|%5s(%d)\n",i,colors[colorsArray[i]],colorsArray[i]);
  }

  //We are done
  fclose (fp);
  return EXIT_SUCCESS;
}
