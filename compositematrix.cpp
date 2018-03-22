#include "compositematrix.h"
#include <iostream>
#include <string>
#include <sstream>


//! Luodaan uusi CompositeMatrix
//! op1 ja op2 ovat vapaamuotoisia neliömatriiseja
//! opr on +, - tai * operaatio
//! ops on matematiikkaoperaation symboli
CompositeSquareMatrix::CompositeSquareMatrix(const SquareMatrix& op1, const SquareMatrix& op2, const std::function<ConcreteSquareMatrix(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&)>& opr, char ops){

    if(ops == '+' || ops == '-' || ops == '*'){
        op_sym = ops;
    }
    else{throw std::invalid_argument("Symboli täytyy olla +, - tai *");}

	oprnd1 = std::shared_ptr<SquareMatrix>(op1.clone());
	oprnd2 = std::shared_ptr<SquareMatrix>(op2.clone());
	oprtor = opr;
}

//! Luodaan uusi matriisi joka on samanlainen kuin parametriolio
CompositeSquareMatrix::CompositeSquareMatrix(const CompositeSquareMatrix& m){

 	oprnd1 = m.oprnd1;
	oprnd2 = m.oprnd2;
	oprtor = m.oprtor;
	op_sym = m.op_sym;
}

//! Siirretään parametrin tiedot toiseen olioon
//! Parametrinä annettu matriisi muuttuu tyhjäksi
CompositeSquareMatrix::CompositeSquareMatrix(CompositeSquareMatrix&& m){

    oprnd1 = std::move(m.oprnd1);
	oprnd2 = std::move(m.oprnd2);
	oprtor = std::move(m.oprtor);
	op_sym = std::move(m.op_sym);

}

//! Kopiointioperaattori
CompositeSquareMatrix& CompositeSquareMatrix::operator=(const CompositeSquareMatrix& m){

 	oprnd1 = m.oprnd1;
	oprnd2 = m.oprnd2;
	oprtor = m.oprtor;
	op_sym = m.op_sym;

	return *this;
}

//! Moveoperaattori
CompositeSquareMatrix& CompositeSquareMatrix::operator=(CompositeSquareMatrix&& m){

    oprnd1 = std::move(m.oprnd1);
	oprnd2 = std::move(m.oprnd2);
	oprtor = std::move(m.oprtor);
	op_sym = std::move(m.op_sym);

	return *this;

}

//! Luo pointterin oliosta
SquareMatrix* CompositeSquareMatrix::clone() const{
	return new CompositeSquareMatrix(*this);
}

//! Tulostaa olion sisällön
void CompositeSquareMatrix::print(std::ostream& os) const{

	os << toString();
}

//! Muuttaa olion sisällön stringiksi
std::string CompositeSquareMatrix::toString() const{

	std::stringstream ss;
	ss << '(' << *oprnd1 << op_sym << *oprnd2 << ')';
	return ss.str();

}

//! Evaluoi operandit ja palauttaa niillä lasketun operaation tuloksen
ConcreteSquareMatrix CompositeSquareMatrix::evaluate(const Valuation& v)const{

	return oprtor(oprnd1->evaluate(v), oprnd2->evaluate(v));
}
