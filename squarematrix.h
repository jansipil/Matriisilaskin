#ifndef SQUAREMATRIX_H_INCLUDED
#define SQUAREMATRIX_H_INCLUDED
#include <iostream>
#include <string>
#include <map>
#include "element.h"

//class ConcreteSquareMatrix;
template <typename Type>
class ElementarySquareMatrix;

class SquareMatrix{
public:
	//!\brief Destructori
	virtual ~SquareMatrix() = default;
	//!brief Palauttaa pointterin oliosta
	//!return pointteri SquareMatrix luokan oliosta (tai sen alaluokan oliosta)
	virtual SquareMatrix* clone() const = 0;
	//!\brief funktio tulostaa olion sisällön
    //!\param joku outputstream
	virtual void print(std::ostream& os) const = 0;
	//!\brief funktio kertoo olion sisällön string muodossa
	virtual std::string toString() const = 0;
	//!\brief luo uuden ConcreteSquareMatrixin annetun std:mapin avulla
	//!\param std::map jota halutaan käyttää
	//!\return uusi ConcreteSquareMatrix
	virtual ElementarySquareMatrix<IntElement> evaluate(const Valuation& v) const = 0;
};

using ConcreteSquareMatrix = ElementarySquareMatrix<IntElement>;
using SymbolicSquareMatrix = ElementarySquareMatrix<Element>;


std::ostream& operator<<(std::ostream& out, const SquareMatrix& sm);

ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& c1, const ConcreteSquareMatrix& c2);
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& c1, const ConcreteSquareMatrix& c2);
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& c1, const ConcreteSquareMatrix& c2);


#endif // SQUAREMATRIX_H_INCLUDED
