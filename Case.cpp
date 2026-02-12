#include "Case.h"

Case::Case() {
	_symbole = " ~ ";
	_obstacle = nullptr;
	_x = 0;
	_y = 0;
	_isEmpty = 1;
	_isWater = 1;
}

void Case::printCase() {
	cout << _symbole;
}

int Case::positionX() {
	return _x;
}

int Case::positionY() {
	return _y;
}

bool Case::isEmpty() {
	return _isEmpty;
}

bool Case::isWater() {
	return _isWater;
}

void Case::setPositionX(int x) {
	_x = x;
}

void Case::setPositionY(int y) {
	_y = y;
}

void Case::setEmptyState(bool state) {
	_isEmpty = state;
}

void Case::setWaterState(bool state) {
	 _isWater = state;
}

void Case::setObstacle(Obstacle* obstacle) {
	_obstacle = obstacle;
	_symbole = string(" ") + _obstacle->getSymbole() + " ";
	setEmptyState(0);
}
