#include "position.hpp"

int main() {
  Position p;

  srand(time(0));
  
  while (! p.endOfGame()) {
    p.display();
    vector<Move> jouables = p.coupsJouables();    // trouve coups lÃ©gaux
    Move m;
    
    if (p.getProchain() == Blanc) { // humain 
      m = p.getMove();
      while (find(jouables.begin(), jouables.end(), m) == jouables.end()) {
        m = p.getMove();  // erreur, resaisir
      }
    } else { // machine
      //m = p.getMoveAlea(jouables); // Ã  amÃ©liorer...
      m = p.getMoveAlphaBeta(); // Ã  amÃ©liorer...
    }
    
    p.doMove(m); 
    p.prochainJoueur();
  }
  p.display();
  string msg = (p.gagne(Blanc)) ? "Blanc" : "Noir";
  cout << msg << " gagne !" << endl;
  return 0;
}
