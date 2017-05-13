#include<vector>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>

#include "move.cpp"

using namespace std;
	   
class Position{
  vector<Couleur> plateau;
  Couleur joueur = Blanc; // joueur ayant le trait
  int nb_coups= 0; // compteur de pions dÃ©jÃ  placÃ©s
public:
  Couleur getProchain() const { return joueur;}
  Position();
  Position(const Position &p);
  bool endOfGame();
  void display();
  Move getMove();
  Move getMoveAlea(vector<Move> jouables); 
  void doMove(Move m);
  void prochainJoueur();
  vector<Move> coupsJouables();
  bool gagne(Couleur joueur);
  float eval(Couleur j);
  Move getMoveAlphaBeta();
  float getMoveAlphaBetaAux(Couleur jo, int currentDepth,
				   int depthMax, Move *m);
};
