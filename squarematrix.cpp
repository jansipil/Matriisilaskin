#include "squarematrix.h"
#include "elementarymatrix.h"
#include <iostream>


///////////////////////////////////////////////////
/////////////////// Yhteiset //////////////////////
///////////////////////////////////////////////////


//! Tulostusoperaattori
std::ostream& operator<<(std::ostream& out, const SquareMatrix& sm){
	return out << sm.toString();
}

//! Laskuoperaattorit joita voidaan käyttää CompositeSquareMatrix luokkaa muodostaessa

ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& c1, const ConcreteSquareMatrix& c2){
	ConcreteSquareMatrix temp(c1);
	temp += c2;
	return temp;
}

ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& c1, const ConcreteSquareMatrix& c2){
	ConcreteSquareMatrix temp(c1);
	temp -= c2;
	return temp;
}

ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& c1, const ConcreteSquareMatrix& c2){
	ConcreteSquareMatrix temp(c1);
	temp *= c2;
	return temp;
}
