#include "Obstacle.h"


class Roche : public Obstacle {
	protected:
		
		char _symbole = 'R';

	public:
		Roche(int x=0, int y=0, int taille=1, int orientation=0);
		~Roche();
		int getX();
		int getY();
};
