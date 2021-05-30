#ifndef POST_H
#define POST_H
#include "structs.h"

class Post {
	public:
		Post();
		Post(int row, int col, char type);
		int getRow() const;
		int getCol() const;
		int getID() const;
		Position getPosition() const;
		char getSymbol() const;
		bool isElectrified() const;
		void setNoElectric();
	private:
		static int postCounter; //used to attribute automatically the id to the posts
		int id, row, col;
		char type;
};

#endif