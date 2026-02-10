#include "Case.h"

Case::Case() {
	_symbole = " ~ ";
	_isEmpty = 1;
	_isWater = 1;
}

void Case::printCase() {
	cout << _symbole;
}

bool Case::isEmpty() {
	return _isEmpty;
}

bool Case::isWater() {
	return _isWater;
}

void Case::setEmptyState(bool state) {
	_isEmpty = state;
}

 void Case::setWaterState(bool state) {
	 _isWater = state;
}
