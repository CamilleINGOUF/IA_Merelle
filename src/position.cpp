#include "position.hpp"

Position::Position() {
  plateau = vector<Couleur>(9, Vide);
  joueur = Blanc;
}

Position::Position(const Position &p) :
  plateau(p.plateau), joueur(p.joueur), nb_coups(p.nb_coups) {
}

void Position::prochainJoueur() {
  joueur = (joueur == Blanc) ? Noir : Blanc; // swap noir et blanc
  nb_coups += 1;
}

bool Position::endOfGame() {
  if (gagne(Blanc) or gagne(Noir))
    return true;
  if (coupsJouables().size() == 0)
    return true;
  return false;
}

vector<Move> Position::coupsJouables() { // pour le joueur courant
  vector<Move> coups;
  // si phase de pose
  if (nb_coups < 6) {
    for (int i = 0; i < 9; i++) {
      // hors centre en 1er
      if (plateau[i] == Vide and (nb_coups != 0 or i != 4))
	coups.push_back({joueur, -1, i});
    }
    return coups;
  }
  // si phase de dÃ©placement
  for (int i = 0; i < 9; i++) { // chercher pion placÃ©s
    if (plateau[i] != joueur) // ignorer
      continue;
    // case Ã  gauche ?
    if (i % 3 != 0 and plateau[i-1] == Vide)
      coups.push_back({joueur, i, i-1});
    // case Ã  droite ?
    if (i % 3 != 2 and plateau[i+1] == Vide)
      coups.push_back({joueur, i, i+1});
    // case dessus ?
    if (i > 2 and plateau[i-3] == Vide)
      coups.push_back({joueur, i, i-3});
    // case dessous ?
    if (i < 6 and plateau[i+3] == Vide)
      coups.push_back({joueur, i, i+3});
    // diag NW ?
    if (i % 3 != 0 and i > 2 and plateau[i-4] == Vide)
      coups.push_back({joueur, i, i-4});
    // diag NE ?
    if (i % 3 != 2 and i > 2 and plateau[i-2] == Vide)
      coups.push_back({joueur, i, i-2});
    // diag SE ?
    if (i % 3 != 2 and i < 6 and plateau[i+4] == Vide)
      coups.push_back({joueur, i, i+4});
    // diag SW ?
    if (i % 3 != 0 and i < 6 and plateau[i+2] == Vide)
      coups.push_back({joueur, i, i+2});
  }
  return coups;
}

bool Position::gagne(Couleur joueur) {
  // horiz
  if (plateau[0] == joueur and plateau[1] == joueur and plateau[2] == joueur)
    return true;
  if (plateau[3] == joueur and plateau[4] == joueur and plateau[5] == joueur)
    return true;
  if (plateau[6] == joueur and plateau[7] == joueur and plateau[8] == joueur)
    return true;
  // vert
    if (plateau[0] == joueur and plateau[3] == joueur and plateau[6] == joueur)
    return true;
  if (plateau[1] == joueur and plateau[4] == joueur and plateau[7] == joueur)
    return true;
  if (plateau[2] == joueur and plateau[5] == joueur and plateau[8] == joueur)
    return true;
  // diago
    if (plateau[0] == joueur and plateau[4] == joueur and plateau[8] == joueur)
    return true;
  if (plateau[2] == joueur and plateau[4] == joueur and plateau[6] == joueur)
    return true;
  return false;
}

void Position::display() {
  int pos = 0;
  cout << "    0  1  2 " << endl << "   ---------";
  for (int i = 0; i < 9; i++) {    
    if (i%3 == 0)
      cout << "\n " << char('A'+(i/3)) << "|";
    if (plateau[i]==Vide)
      cout << " " << pos << " ";
    else if (plateau[i]==Blanc)
      cout << "[ ]";
    else
      cout << "[#]";
    pos++;
  }
  cout << endl;  
}

Move Position::getMove() {
  int pos, pos2;
  string msg = (joueur == Blanc) ? "blanc" : "noir";
  cout << "Joueur " << msg << " ? ";
  if (nb_coups < 6) {
    cin >> pos;
    return {joueur, -1, pos};
  } else {
    cout << "depuis/vers : ";
    cin >> pos >> pos2;
    return {joueur, pos, pos2};
  }
}

void Position::doMove(Move m) {
  if (m.depuis == -1) { // placement
      plateau[m.vers] = m.joueur; // ok
  } else {
    plateau[m.depuis] = Vide; // ok
    plateau[m.vers] = m.joueur; // ok
  }
}

Move Position::getMoveAlea(vector<Move> jouables) {
  return jouables[rand()%jouables.size()];
}

float Position::eval(Couleur joueur) {
  return
    (plateau[0] == joueur) ? 3 : (plateau[0] != Vide) ? -3 : 0 +
    (plateau[2] == joueur) ? 3 : (plateau[2] != Vide) ? -3 : 0 +
    (plateau[6] == joueur) ? 3 : (plateau[6] != Vide) ? -3 : 0 +
    (plateau[8] == joueur) ? 3 : (plateau[8] != Vide) ? -3 : 0 +
    (plateau[1] == joueur) ? 1 : (plateau[1] != Vide) ? -1 : 0 +
    (plateau[3] == joueur) ? 1 : (plateau[3] != Vide) ? -1 : 0 +
    (plateau[5] == joueur) ? 1 : (plateau[5] != Vide) ? -1 : 0 +
    (plateau[7] == joueur) ? 1 : (plateau[7] != Vide) ? -1 : 0 +
    (plateau[4] == joueur) ? 5 : (plateau[4] != Vide) ? -5 : 0;
}

Move Position::getMoveAlphaBeta() {
  Position p(*this); // copie pour protÃ©ger partie originale
  Couleur jo = joueur;
  Move m;
  p.getMoveAlphaBetaAux(jo, 1,4,&m);// depth
  return m;
}

float Position::getMoveAlphaBetaAux(Couleur jo, int currentDepth,
				   int depthMax, Move *m)
{
  if (currentDepth == depthMax and !endOfGame()) {
    // m = new Move(); //The best move
    return eval(jo);
  } else {
    // TODO
    // boucler sur coupsJouables retourner min ou max selon depth (odd -> max)
    // recupérer le move qui donne le max ou min
    // créer un copie de m, sinon référence fait n'importe quoi

    vector<Move> coupsJouables = (*this).coupsJouables();
    float evalToReturn = 0.0;
    for(Move move : coupsJouables)
      {
	float tempEval = eval(jo);
	if(currentDepth%2 == 1)//if odd currentDepth
	  { 
	    if(tempEval > evalToReturn)
	      {
		evalToReturn = tempEval;
	      }
	  }
	else//if even currentDepth
	  {
	    if(evalToReturn != 0 and tempEval < evalToReturn)
	      {
		evalToReturn = tempEval;
	      }
	  }
      }
    
    return getMoveAlphaBetaAux(jo, currentDepth + 1, depthMax, m);
  }
}
