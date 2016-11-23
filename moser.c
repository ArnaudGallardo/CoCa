// Graphe de Moser
// X(G) = 4
// planaire

int graph[7][7] = {
  // 0  1  2  3  4  5  6
    {0, 1, 1, 0, 1, 1, 0}, //0
    {1, 0, 1, 1, 0, 0, 0}, //1
    {1, 1, 0, 1, 0, 0, 0}, //2
    {0, 1, 1, 0, 0, 0, 1}, //3
    {1, 0, 0, 0, 0, 1, 1}, //4
    {1, 0, 0, 0, 1, 0, 1}, //5
    {0, 0, 0, 1, 1, 1, 0}  //6
};

int orderG(){
return 7;
}

int sizeG(){
return 11;
}

int are_adjacent(int u, int v){
  if(0<= u && 0<=v && u<orderG() && v<orderG()){
      return graph[u][v];
  }
  return 0;
}
