#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include <iostream>
#include <memory>
#include <string>
#include <map>

//! käytetään std::map kirjastoa nimellä Valuation

using Valuation = std::map<char,int>;


//!\brief Element luokka
//! abstrakti yläluokka
class Element{
public:
	virtual ~Element()=default;
	//!\brief funktio tekee pointterin kyseisen Elementin alaluokan olioon
	//!\return pointteri Element olioon
	virtual Element* clone() const = 0;
	//!\brief muuttaa olion arvon string muotoon
	//!\return olion arvo stringinä
	virtual std::string toString() const = 0;
	//!\brief antaa kyseisen olion numerisen arvon
	//!\param std::map jonka avulla päätellään numerinen arvo jos Element olio on kirjain
	//!\return olion arvo kokonaislukuna (tai kyseistä kirjainta vastaava kokonaisluku)
	virtual int evaluate(const Valuation& val) const = 0;
};

template <typename T>
class TElement : public Element{

private:
	T val;

public:
	TElement(): val(0){};
	TElement(T t): val(t){};
	virtual ~TElement() = default;
	T getVal() const{return val;}
	void setVal(T t){val = t;}
	Element* clone() const{return new TElement<T>(val);}
	std::string toString() const;
	int evaluate(const Valuation& v) const;
	bool operator==(const TElement<T>& i) const{
		if(val == i.val) return true;
		return false;
	}
	
	TElement<T>& operator+=(const TElement<T>& i);
	TElement<T>& operator-=(const TElement<T>& i);
	TElement<T>& operator*=(const TElement<T>& i);
	
};

using IntElement = TElement<int>;
using VariableElement = TElement<char>;


//!\brief Yhteiset operaatiot

//!\brief overload operator <<
//!\param joku tulostusstreami
//!\param vakio Elementin oliosta
//!\return ostream olio tulostusstreamiin
std::ostream& operator<<(std::ostream& out, const Element& i);

//!\brief overload operator +
//!\param vakio IntElementin oliosta
//!\param vakio toisesti IntElementin oliosta
//!\return väliaikainen olio
IntElement operator+(const IntElement& a, const IntElement& i);

//!\brief overload operator -
//!\param vakio IntElementin oliosta
//!\param vakio toisesti IntElementin oliosta
//!\return väliaikainen olio
IntElement operator-(const IntElement& a, const IntElement& i);

//!\brief overload operator *
//!\param vakio IntElementin oliosta
//!\param vakio toisesti IntElementin oliosta
//!\return väliaikainen olio
IntElement operator*(const IntElement& a, const IntElement& i);


#endif // ELEMENT_H_INCLUDED
