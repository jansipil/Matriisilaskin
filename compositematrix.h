#ifndef COMPOSITESQUAREMATRIX_H_INCLUDED
#define COMPOSITESQUAREMATRIX_H_INCLUDED
#include <string>
#include <ostream>
#include "element.h"
#include <vector>
#include <memory>
#include "squarematrix.h"
#include "elementarymatrix.h"
#include <functional>

//!\brief SymbolicSquareMatrix luokka
//! matriisi sisältää Intelement olioita sekä VariableElement olioita
class CompositeSquareMatrix : public SquareMatrix{

	public:
		//!\brief Pääasiallinen konstruktori
	    //!\param kaksi matriisia joilla operaatiot tehdään sekä operaation tyyppi funktiona ja symbolina
		CompositeSquareMatrix(const SquareMatrix& op1, const SquareMatrix& op2, const std::function<ConcreteSquareMatrix(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&)>& opr, char ops);

		//!\brief Kopiokonstruktori valmiista SymbolicSquareMatrixista
	    //!\param CompositeSquareMatrix olio
		CompositeSquareMatrix(const CompositeSquareMatrix& m);

		//!\brief Movekonstruktori valmiista SymbolicSquareMatrixista
	    //!\param CompositeSquareMatrix olion rvalue reference
		CompositeSquareMatrix(CompositeSquareMatrix&& m);

		//!\brief Destructori
		virtual ~CompositeSquareMatrix() = default;

		//!\brief overload operator =, kopiointioperaattori
	    //!\param vakio CompositeSquareMatrixin oliosta
	    //!\return olio jonka arvot haluttiin muuttaa
		CompositeSquareMatrix& operator=(const CompositeSquareMatrix& m);

		//!\brief overload operator =, moveoperaattori
	    //!\param CompositeSquareMatrixin olion rvalue reference
	    //!\return olio johon parametrin arvot siirretään
		CompositeSquareMatrix& operator=(CompositeSquareMatrix&& m);

		//!brief Palauttaa pointterin oliosta
		//!return pointteri SquareMatrix luokan oliosta (tai sen alaluokan oliosta)
		SquareMatrix* clone() const;

        //!\brief funktio tulostaa olion sisällön
        //!\param joku outputstream
		void print(std::ostream& os) const;

		//!\brief funktio kertoo CompositeSquareMatrix olion sisällön string muodossa
		std::string toString() const;

		//!\brief tekee CompositeSquareMatrixista ConcreteSquareMatrixin annetun std:mapin avulla
		//!\param std::map jota halutaan käyttää
		//!\return uusi ConcreteSquareMatrix
		ConcreteSquareMatrix evaluate(const Valuation& v)const;

	private:
		//!brief operandit eli kaksi pointteria matriiseihin
		std::shared_ptr<SquareMatrix> oprnd1;
		std::shared_ptr<SquareMatrix> oprnd2;
		//!brief haluttava matematiikkaoperaattori
		std::function<ConcreteSquareMatrix(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&)> oprtor;
		//!brief matematiikkaoperaattorin symboli
		char op_sym;
};

#endif // COMPOSITESQUAREMATRIX_H_INCLUDED
