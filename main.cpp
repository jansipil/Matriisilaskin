#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "squarematrix.h"
#include "elementarymatrix.h"
#include "compositematrix.h"
#include "element.h"
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <functional>
#include <stack>




//! Kaikki testit luokille

//! Testataan Element luokkaa, sen alaluokkia, ja niiden funktioita
TEST_CASE("Element testit", "[value]"){
	IntElement ie1(2);
	IntElement ie2(3);
	VariableElement ve1('x');
	VariableElement ve2('y');

	CHECK(ve1.toString()=="x");
	ve2.setVal(ve1.getVal());
	CHECK(ve2.toString()=="x");

	ie1 += ie2;

	CHECK(ie1.getVal() == 5);

	ie1 -= ie2;

	CHECK(ie1.getVal() == 2);

	ie1 *= ie2;

	CHECK(ie1.getVal() == 6);


	ie2 = (ie1 + ie1 - ie1) * ie1;

	CHECK(ie2.getVal() == 36);

	CHECK_FALSE(ie1 == ie2);
}

//! Testataan ConcreteMatrixien luomista
TEST_CASE("ConcreteMatrix konstruktorit", "[string]"){
	ConcreteSquareMatrix test1;
	ConcreteSquareMatrix test2("[[1,2][3,4]]");
	ConcreteSquareMatrix test3(test2);

	CHECK(test2.toString() == "[[1,2][3,4]]");
	CHECK(test3.toString() == "[[1,2][3,4]]");
	CHECK(test1.getVector().empty());

	ConcreteSquareMatrix test4(std::move(test2));
	CHECK(test4.toString() == "[[1,2][3,4]]");
	CHECK(test2.getVector().empty());

	test2 = test4;
	test2 = test2;

	CHECK(test2.toString() == "[[1,2][3,4]]");

	CHECK_THROWS(ConcreteSquareMatrix("[[1,2][3,4][6,7]]"));
	CHECK_THROWS(ConcreteSquareMatrix("1,2][3,4][6,7]]"));
	CHECK_THROWS(ConcreteSquareMatrix("[[a,b][c,d]]"));
}

//! Testataan ConcreteMatrixien laskuoperaatioita
TEST_CASE("ConcreteMatrix laskut", "[string]"){

	ConcreteSquareMatrix mat1("[[1,2][3,4]]");
	ConcreteSquareMatrix mat2("[[4,3][2,1]]");
	ConcreteSquareMatrix mat3("[[1,2,3][4,5,6][7,8,9]");
	mat1 += mat2;

	CHECK(mat1.toString() == "[[5,5][5,5]]");

	CHECK_THROWS(mat1 += mat3);

	ConcreteSquareMatrix m1("[[5,4][3,2]]");
	ConcreteSquareMatrix m2("[[4,3][2,1]]");
	ConcreteSquareMatrix m3("[[1,2,3][4,5,6][7,8,9]]");
	m1 -= m2;

	CHECK(m1.toString() == "[[1,1][1,1]]");

	CHECK_THROWS(m1 -= m3);

	ConcreteSquareMatrix m("[[1,2,3][4,5,6][7,8,9]");
	ConcreteSquareMatrix x("[[1,2][3,4]]");

	m *= m;

	CHECK(m.toString() == "[[30,36,42][66,81,96][102,126,150]]");

	CHECK_THROWS(m *= x);
}

//! Testataan SymbolicMatrixien luomista
TEST_CASE("SymbolicMatrix konstruktorit", "[string]"){

	SymbolicSquareMatrix s1("[[5,4][3,2]]");
	SymbolicSquareMatrix s2("[[4,a][b,1]]");
	SymbolicSquareMatrix s3("[[y,2,a][4,g,6][p,m,n]]");
	SymbolicSquareMatrix s4(s3);
	SymbolicSquareMatrix s5(std::move(s4));

	CHECK(s5.toString() == "[[y,2,a][4,g,6][p,m,n]]");
	CHECK(s4.getVector().empty());

	std::map<char,int> valmap;

	valmap['a'] = 1;
	valmap['b'] = 2;
	valmap['y'] = 3;
	valmap['g'] = 4;
	valmap['p'] = 5;
	valmap['m'] = 6;
	valmap['n'] = 7;

	ConcreteSquareMatrix conc(s5.evaluate(valmap));
	CHECK(conc.toString() == "[[3,2,1][4,4,6][5,6,7]]");

	s4 = s5;
	s4 = s4;

    CHECK(s4.toString() == "[[y,2,a][4,g,6][p,m,n]]");

	CHECK_THROWS(SymbolicSquareMatrix("[[!,a][b,c]]"));

}

//! Testataan CompositeMatrixin luomista ja käyttöä
TEST_CASE("CompositeMatrix testit", "[string]"){

	ConcreteSquareMatrix temp1("[[1,2][3,4]]");
	ConcreteSquareMatrix temp2("[[4,3][2,1]]");
	SymbolicSquareMatrix temp3("[[a,b][c,d]]");

	CompositeSquareMatrix com1(temp1,temp2,std::plus<ConcreteSquareMatrix>(),'+');
	CompositeSquareMatrix com2(temp1,temp2,std::minus<ConcreteSquareMatrix>(),'-');
	CompositeSquareMatrix com3(temp1,temp2,std::multiplies<ConcreteSquareMatrix>(),'*');
	CompositeSquareMatrix com4(com1);
	CompositeSquareMatrix com5(std::move(com4));

	CHECK(com5.toString()=="([[1,2][3,4]]+[[4,3][2,1]])");

	std::map<char,int> valuemap;

	valuemap['a'] = 1;
	valuemap['b'] = 2;
	valuemap['c'] = 3;
	valuemap['d'] = 4;

    CompositeSquareMatrix com6(temp3.evaluate(valuemap), temp3.evaluate(valuemap), std::plus<ConcreteSquareMatrix>(), '+');
	ConcreteSquareMatrix com_eval1(com1.evaluate(valuemap));
	ConcreteSquareMatrix com_eval2(com2.evaluate(valuemap));
	ConcreteSquareMatrix com_eval3(com3.evaluate(valuemap));
	ConcreteSquareMatrix com_eval4(com6.evaluate(valuemap));

	CHECK(com_eval1.toString()=="[[5,5][5,5]]");
	CHECK(com_eval2.toString()=="[[-3,-1][1,3]]");
	CHECK(com_eval3.toString()=="[[8,5][20,13]]");
	CHECK(com_eval4.toString()=="[[2,4][6,8]]");

	CHECK_THROWS(CompositeSquareMatrix(temp1,temp2,std::plus<ConcreteSquareMatrix>(),'a'));

}

int main(int argc, char* argv[]){

    int result = Catch::Session().run( argc, argv );
    SymbolicSquareMatrix opr1;
    SymbolicSquareMatrix opr2;
	std::string syote;
	std::stack<std::shared_ptr<SquareMatrix>> stakki;
	std::map<char, int> valuation;
	char c1 = ' ';
	char c2 = ' ';
	int luku = 0;
	std::stringstream ss;

	while(true){
        ss.clear();
        ss.str("");
        std::cout << "Anna syote" << std::endl;
		std::cin >> syote;

		if(syote=="quit") return result;

		ss << syote;
		ss >> c1;
		ss >> c2;
		if(c2 == '='){
			ss >> luku;
			if(ss.fail()){
                std::cout << "Sinun pitaa maaritella merkille kokonaisluku" << std::endl;
                continue;
			}

			if(ss.rdbuf()->in_avail() == 0){
				valuation[c1] = luku;
				std::cout << "Annettiin merkille " << c1 << " arvoksi " << luku << std::endl;
				c2 = ' ';
			}
		}
		else{

			if(!syote.empty()) c1 = syote[0];
			if(c1 == '+'){
                if(stakki.empty()){
                	std::cout << "Pino on tyhja" << std::endl;
                	continue;
                }
                auto temp = stakki.top();
                try{
					opr1 = SymbolicSquareMatrix(stakki.top()->toString());
                }
				catch(std::invalid_argument ia){
					try{
						opr1 = SymbolicSquareMatrix(stakki.top()->evaluate(valuation).toString());
					}
					catch(std::invalid_argument ia){
						std::cout << "Evaluointia ei pystytty tekemaan, maarittele kirjaimia vastaavat luvut" << std::endl;
					}
				}
				stakki.pop();
				if(stakki.empty() == true){
                	std::cout << "Pinossa on vain yksi matriisi" << std::endl;
                	stakki.push(temp);
                	continue;
                }
				try{
					opr2 = SymbolicSquareMatrix(stakki.top()->toString());
				}
				catch(std::invalid_argument ia){
					try{
						opr2 = SymbolicSquareMatrix(stakki.top()->evaluate(valuation).toString());
					}
					catch(std::invalid_argument ia){
						std::cout << "Evaluointia ei pystytty tekemaan, maarittele kirjaimia vastaavat luvut" << std::endl;
					}
				}
				std::shared_ptr<SquareMatrix> laskinptr(new CompositeSquareMatrix(opr1,opr2,std::plus<ConcreteSquareMatrix>(), c1));
				stakki.push(laskinptr);
				std::cout << "Lisattiin laskutoimitus " << laskinptr->toString()  << " pinoon" << std::endl;

			}
			else if(c1 == '-'){
				if(stakki.empty()){
                	std::cout << "Pino on tyhja" << std::endl;
                	continue;
                }
                auto temp = stakki.top();
				try{
					opr1 = SymbolicSquareMatrix(stakki.top()->toString());
				}
				catch(std::invalid_argument ia){
					try{
						opr2 = SymbolicSquareMatrix(stakki.top()->evaluate(valuation).toString());
					}
					catch(std::invalid_argument ia){
						std::cout << "Evaluointia ei pystytty tekemaan, maarittele kirjaimia vastaavat luvut" << std::endl;
					}
				}
				stakki.pop();
				if(stakki.empty() == true){
                	std::cout << "Pinossa on vain yksi matriisi" << std::endl;
                	stakki.push(temp);
                	continue;
                }
				try{
					opr2 = SymbolicSquareMatrix(stakki.top()->toString());
				}
				catch(std::invalid_argument ia){
					try{
						opr2 = SymbolicSquareMatrix(stakki.top()->evaluate(valuation).toString());
					}
					catch(std::invalid_argument ia){
						std::cout << "Evaluointia ei pystytty tekemaan, maarittele kirjaimia vastaavat luvut" << std::endl;
					}
				}
				std::shared_ptr<SquareMatrix> laskinptr(new CompositeSquareMatrix(opr1,opr2,std::minus<ConcreteSquareMatrix>(), c1));
				stakki.push(laskinptr);
				std::cout << "Lisattiin laskutoimitus " << laskinptr->toString() << " pinoon" << std::endl;
			}
			else if(c1 == '*'){
				if(stakki.empty() == true){
                	std::cout << "Pino on tyhja" << std::endl;
                	continue;
                }
                auto temp = stakki.top();
				try{
					opr1 = SymbolicSquareMatrix(stakki.top()->toString());
				}
				catch(std::invalid_argument ia){
					try{
						opr1 = SymbolicSquareMatrix(stakki.top()->evaluate(valuation).toString());
					}
					catch(std::invalid_argument ia){
						std::cout << "Evaluointia ei pystytty tekemaan, maarittele kirjaimia vastaavat luvut" << std::endl;
					}
				}
				stakki.pop();
				if(stakki.empty() == true){
                	std::cout << "Pinossa on vain yksi matriisi" << std::endl;
                	stakki.push(temp);
                	continue;
                }
				try{
					opr2 = SymbolicSquareMatrix(stakki.top()->toString());
				}
				catch(std::invalid_argument ia){
					try{
						opr2 = SymbolicSquareMatrix(stakki.top()->evaluate(valuation).toString());
					}
					catch(std::invalid_argument ia){
						std::cout << "Evaluointia ei pystytty tekemaan, maarittele kirjaimia vastaavat luvut" << std::endl;
					}
				}
				std::shared_ptr<SquareMatrix> laskinptr(new CompositeSquareMatrix(opr1,opr2,std::multiplies<ConcreteSquareMatrix>(), c1));
				stakki.push(laskinptr);
				std::cout << "Lisattiin laskutoimitus " << laskinptr->toString() << " pinoon" << std::endl;
			}
			else if(c1 == '='){
				try{
					std::cout << stakki.top()->evaluate(valuation) << std::endl;
				}
				catch(std::invalid_argument ia){
					std::cout << "Evaluointia ei pystytty tekemaan, maarittele kirjaimia vastaavat luvut" << std::endl;
				}
			}
			else{
				try{
					std::shared_ptr<SquareMatrix> stackptr(new SymbolicSquareMatrix(syote));
					stakki.push(stackptr);
					std::cout << "Lisattiin matriisi pinoon" << std::endl;
				}
				catch(std::invalid_argument ia){
					std::cout << "Syotetta ei tunnistettu" << std::endl;
				}
			}
		}
	}
}




