#include<vector>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>

using namespace std;
	   
enum Couleur {Vide=0, Blanc=1, Noir=2};

class Move {
public:
  Couleur joueur;
  int depuis, vers; // case numÃ©rotÃ©es de 0 Ã  8 (si depuis = -1 => placement)
  Move() {}
  Move(Couleur j, int d, int v) : joueur(j), depuis(d), vers(v) {};
  bool operator==(const Move &b) {
    return joueur==b.joueur and depuis==b.depuis and vers==b.vers;
  };
};
