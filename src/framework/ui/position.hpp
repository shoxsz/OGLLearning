#ifndef _POSITION_HPP_
#define _POSITION_HPP_

class Position{
public:
	Position(){
		x = y = 0;
	}
	
	Position(int x, int y){
		this->x = x;
		this->y = y;
	}
	
	void set(int x, int y){
		this->x = x;
		this->y = y;
	}

	Position operator+(Position& pos)const{
		return Position(pos.x + x, pos.y + y);
	}

	Position operator-(Position& pos)const{
		return Position(pos.x - x, pos.y - y);
	}

	int x, y;
};

#endif