
class Raft {

	int _x;
	int _y;
	int _symbole = '8';

	public:
		Raft(int x = 0, int y = 0);
		~Raft();
		int getX();
		int getY();
		void setPosition(int x, int y);
		char getSymbole();

		


};

