#include "elementarymatrix.h"

template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator+=(const ElementarySquareMatrix<IntElement>& m){
	if(n != m.n){
		throw std::invalid_argument("Väärän kokoinen matriisi");
	}
	int j;
	for(unsigned int i = 0; i < n; i++){
		j=0;
		for(auto it = m.elements[i].begin(); it != m.elements[i].end(); ++it, j++){

			*elements[i][j] += *(*it);
		}
	}
	return *this;
}

template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator-=(const ElementarySquareMatrix<IntElement>& m){
	if(n != m.n){
		throw std::invalid_argument("Väärän kokoinen matriisi");
	}
	unsigned int j;
	for(unsigned int i = 0; i < n; i++){
		j=0;
		for(auto it = m.elements[i].begin(); it != m.elements[i].end(); ++it, j++){
			*elements[i][j] -= *(*it);
		}
	}
	return *this;
}

template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator*=(const ElementarySquareMatrix<IntElement>& m){
	if(n != m.n){
		throw std::invalid_argument("Väärän kokoinen matriisi");
	}
    ElementarySquareMatrix<IntElement> temp;
    ElementarySquareMatrix<IntElement> trans(m.transpose());
    IntElement ele;
    std::vector<std::shared_ptr<IntElement> > rivi;
    unsigned int i=0;
    unsigned int j=0;
    while(i<n){
        temp.elements.push_back(rivi);
        i++;
    }
	for(i = 0; i < n; i++){

		for(j=0;j<n;j++){

			auto it1 = elements[i].begin();
			auto it2 = trans.elements[j].begin();
			for( ; it1 != elements[i].end(); ++it1,++it2){
	            ele += (*(*it1) * *(*it2));
			}
	        temp.elements[i].push_back(std::shared_ptr<IntElement>(static_cast<IntElement*>(ele.clone())));
	        ele.setVal(0);
	    }
	}
	elements = temp.elements;
	return *this;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::evaluate(const Valuation& val)const{
	return *this;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<Element>::evaluate(const Valuation& val)const{
	ElementarySquareMatrix<IntElement> sm;
    unsigned int i=0;
    int luku;
    std::vector<std::vector<std::shared_ptr<IntElement>>> elem;
    std::vector<std::shared_ptr<IntElement>> rivi;
    while(i<n){
        elem.push_back(rivi);
        i++;
    }
	i=0;
    for(auto it1: this->elements){
        for(auto it2: it1){
        	try{
        		luku = it2->evaluate(val);
        		std::shared_ptr<IntElement> ieptr(new IntElement(luku));
        		elem[i].push_back(ieptr);
        	}
        	catch(...){
        		throw std::invalid_argument("Evaluointia ei pystytty tekemään");
        	}
        }
    	i++;
    }
    sm.setVector(elem);
    sm.setN(n);
    return sm;
}

template<>
bool ElementarySquareMatrix<IntElement>::isSquareMatrix(const std::string& jono){
	std::string sana;
	std::string jotain;
	std::istringstream iss(jono);
	std::vector<std::shared_ptr<IntElement> > rivi;

	unsigned int i = 0;
	unsigned int j = 0;
	n = 0;
	int luku;
	char c;

	iss >> c;
	if(c != '[') throw false;
	iss >> c;
	if(c != '[') throw false;

	while(!iss.eof()){

		elements.push_back(rivi);
		j = 0;
		getline(iss, jotain, ']');
		std::istringstream temp(jotain);
		while(!temp.eof()){
			getline(temp, sana, ',');
			try{
			    luku = std::stoi(sana);
			    std::shared_ptr<IntElement> ieptr(new IntElement(luku));
			    elements[i].push_back(ieptr);
            }
			catch(const std::invalid_argument& ia){
				throw false;
			}
			j++;
		}
		if(n == 0){
			n = j;
			iss >> c;
        	i++;
		}
		else if(n != j){
			throw false;
		}
		else{
        	iss >> c;
        	i++;
        	if(iss.str().back() == ']'){
        	    if(i == n){
        	    	iss >> c;
        	    	if(iss.eof()){
	        	        return true;
        	    	}
        	    }
        	}
        }
	}
	throw false;
}

template<>
bool ElementarySquareMatrix<Element>::isSquareMatrix(const std::string& jono){
	std::string sana;
	std::string jotain;
	std::istringstream iss(jono);
	std::vector<std::shared_ptr<Element> > rivi;
	std::locale loc;

	unsigned int i = 0;
	unsigned int j = 0;
	n = 0;
	int luku;
	char merkki;
	char c;

	iss >> c;
	if(c != '[') throw false;
	iss >> c;
	if(c != '[') throw false;

	while(!iss.eof()){

		elements.push_back(rivi);
		j = 0;
		getline(iss, jotain, ']');
		std::istringstream temp(jotain);
		while(!temp.eof()){
			getline(temp, sana, ',');
			try{
			    luku = std::stoi(sana);
			    std::shared_ptr<Element> ieptr(new IntElement(luku));
			    elements[i].push_back(ieptr);
            }
			catch(const std::invalid_argument& ia){
				try{
					if(sana.size() > 1) throw false;
					merkki = sana[0];
					if(std::isalpha(merkki,loc) == false) throw false;
					std::shared_ptr<Element> veptr(new VariableElement(merkki));
					elements[i].push_back(veptr);
				}
				catch(bool vika){
					throw false;
				}
			}
			j++;
		}
		if(n == 0){
			n = j;
			iss >> c;
        	i++;
		}
		else if(n != j){
			throw false;
		}
		else{
        	iss >> c;
        	i++;
        	if(iss.str().back() == ']'){
        	    if(i == n){
        	    	iss >> c;
        	    	if(iss.eof()){
	        	        return true;
        	    	}
        	    }
        	}
        }
	}
	throw false;
}
