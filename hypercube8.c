// Hypercube de dimension 8
// X(G) = 2
// 8-regulier

// Fonction subsidiaire afin d'eviter de refaire les test are_adjacent
int sub(int u, int v);

// Soit Qi le graphe de dimension i
// nbSommets(Qi) = 2^i
int orderG() {
  return 256;
}


// Soit Qi le graphe de dimension i
// Q1 : nbSommets = 2, nbArretes = 1
// Recurrence: nbArretes(Qi + 1) = 2 * nbArretes(Qi) + nbSommets(Qi)
//             nbSommets(Qi + 1) = 2 * nbSommets(Qi)
//
// nbArretes(Qi) = nbSommets(Qi) * i / 2
int sizeG() {
  int nbS = 2;
  int nbA = 1;
  for (int i = 0; i < 7; i++) {
    nbA = nbA * 2 + nbS;
    nbS *= 2;
  }
  return nbA;
}

int are_adjacent(int u, int v) {
  if (u == v) return 0;
  else if (0 <= u && 0 <= v && u < orderG() && v < orderG()) {
    return sub(u, v);
  }
  return 0;
}

// u et v sont le codage binaire des sommets
// avec le bit de plus haut degré du coté du bit de poids faible (inverses)
int sub(int u, int v) {
  // Le sommet 0 et 1 sont adjacents
  if ((u == 0 && v == 1) || (u == 1 && v == 0)) return 1;
  else {
    int du = (u & 1);
    int dv = (v & 1);
    // Tant que les bits sont identiques on les ejecte
    if (du == dv) return are_adjacent(u >> 1, v >> 1);
    // A la 1e difference les restants doivent etre identiques
    else return u >> 1 == v >> 1;
  }
}
