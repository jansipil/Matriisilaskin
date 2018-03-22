#include <iostream>
#include "element.h"
#include <memory>
#include <algorithm>


template<>
std::string TElement<int>::toString() const{
	return std::to_string(val);
}

template<>
std::string TElement<char>::toString() const{
	return std::string(1, val);
}

template<>
int TElement<int>::evaluate(const Valuation& v) const{
	return val;
}

template<>
int TElement<char>::evaluate(const Valuation& v) const{
	auto result = v.find(val);
	if(result != v.end()){
        return result->second;
	}
	throw "Ei löytynyt";
}

//! yhteenlaskee parametrin ja käsiteltävän olion kokonaisluvun ja sijoittaa sen käsiteltävälle oliolle
template<>
TElement<int>& TElement<int>::operator+=(const TElement<int>& i){
	val = i.val + val;
	return *this;
}

//! vähentään käsiteltävän olion arvosta parametriolion arvon
template<>
TElement<int>& TElement<int>::operator-=(const TElement<int>& i){
	val = val - i.val;
	return *this;
}

//! kertoo olioiden arvot keskenään ja sijoittaa käsiteltävään olioon
template<>
TElement<int>& TElement<int>::operator*=(const TElement<int>& i){
	val = i.val * val;
	return *this;
}






//! tekee temp olion parametriolioiden arvojen summasta
IntElement operator+(const IntElement& a, const IntElement& i){
	IntElement temp(a);
	temp += i;
	return temp;
}
//! tekee temp olion vähentämällä ensimmäisestä parametriolion arvosta toisen olion arvon
IntElement operator-(const IntElement& a, const IntElement& i){
	IntElement temp(a);
	temp -= i;
	return temp;
}

//! tekee temp olion parametriolioiden arvojen kertolaskusta
IntElement operator*(const IntElement& a, const IntElement& i){
	IntElement temp(a);
	temp *= i;
	return temp;
}
//! sijoittaa käsiteltävän olion arvon streamiin
std::ostream& operator<<(std::ostream& out, const Element& i){
    out << i.toString();
	return out;
}


