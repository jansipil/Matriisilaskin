#ifndef ELEMENTARYSQUAREMATRIX_H_INCLUDED
#define ELEMENTARYSQUAREMATRIX_H_INCLUDED
#include "squarematrix.h"
#include <string>
#include <ostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <locale>

template <typename Type>
class ElementarySquareMatrix : public SquareMatrix{

	private:
		unsigned int n;
		std::vector<std::vector<std::shared_ptr<Type>>> elements;
		friend ElementarySquareMatrix<Element>;

	public:
		ElementarySquareMatrix():n(0){};

		ElementarySquareMatrix(const std::string& str_m){
			try{
				isSquareMatrix(str_m);
			}
			catch(bool virhe){
				throw std::invalid_argument("Matriisin parametrit eivät kelvanneet");
			}
		}

		ElementarySquareMatrix(const ElementarySquareMatrix<Type>& m){
		    std::vector<std::shared_ptr<Type> > rivi;
		    n = m.n;
			for(int i = 0; i < n; i++){
				elements.push_back(rivi);
				for(auto it = m.elements[i].begin(); it != m.elements[i].end(); ++it){
					elements[i].push_back(std::shared_ptr<Type>(static_cast<Type*>((*(*it)).clone())));
				}
			}
		}

		ElementarySquareMatrix(ElementarySquareMatrix<Type>&& m){
			n = m.n;
		    elements = std::move(m.elements);
		    m.n=0;
		}


		ElementarySquareMatrix<Type>& operator=(const ElementarySquareMatrix<Type>& m){
			if(*this == m){
				return *this;
			}
			std::vector<std::shared_ptr<Type> > rivi;
			elements.clear();
			n=m.n;
			for(unsigned int i = 0; i < n; i++){
				elements.push_back(rivi);
				for(auto it : m.elements[i]){
					elements[i].push_back(std::shared_ptr<Type>(static_cast<Type*>((it->clone()))));
				}
			}
			return *this;
		}

		ElementarySquareMatrix<Type>& operator=(ElementarySquareMatrix<Type>&& m){
			if(*this == m) return *this;
			elements = std::move(m.elements);
			n = m.n;
			m.n=0;
			return *this;
		}

		ElementarySquareMatrix<Type> transpose() const{
			ElementarySquareMatrix<Type> sm;
		    unsigned int i=0;
		    std::vector<std::vector<std::shared_ptr<Type> > > elem;
		    std::vector<std::shared_ptr<Type> > rivi;
		    while(i<n){
		        elem.push_back(rivi);
		        i++;
		    }
		    for(auto it1: this->elements){
		        i=0;
		        for(auto it2: it1){
		            elem[i].push_back(std::shared_ptr<Type>(static_cast<Type*>((it2->clone()))));
		            i++;
		        }
		    }
		    sm.setVector(elem);
		    return sm;
		}

		bool operator==(const ElementarySquareMatrix<Type>& m) const{
			std::string itse = toString();
			std::string toinen = m.toString();
    		if(itse == toinen) return true;
    		return false;
		}

		std::string toString() const{
			std::string matriisi;
			std::stringstream ss;
			unsigned int i;
			ss << "[[";
			for(i=0;i<n;i++){
				for(auto it = elements[i].begin(); it != elements[i].end(); ++it){
					ss << ((*(*it)).toString());
					if(it+1 != elements[i].end()){
						ss << ',';
					}
				}
				if(i+1 != n){
					ss << "][";
				}
			}
			ss << "]]";
		    ss >> matriisi;

			return matriisi;
		}

		virtual ~ElementarySquareMatrix() = default;
		void setN(unsigned int i){n = i;}
		unsigned int getN() const{return n;}
		void setVector(std::vector<std::vector<std::shared_ptr<Type>>> vec){elements = vec; n = elements.size();}
		std::vector<std::vector<std::shared_ptr<Type>>> getVector() const{return elements;}
		SquareMatrix* clone() const{return new ElementarySquareMatrix<Type>(*this);}
		void print(std::ostream& os) const{os << toString();}

		ElementarySquareMatrix<IntElement> evaluate(const Valuation& val)const;
		bool isSquareMatrix(const std::string& jono);
		ElementarySquareMatrix<Type>& operator+=(const ElementarySquareMatrix<Type>& m);
		ElementarySquareMatrix<Type>& operator-=(const ElementarySquareMatrix<Type>& m);
		ElementarySquareMatrix<Type>& operator*=(const ElementarySquareMatrix<Type>& m);
};


#endif // ELEMENTARYSQUAREMATRIX_H_INCLUDED
