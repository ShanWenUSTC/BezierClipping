#ifndef CPOLYNOMIAL_H
#define CPOLYNOMIAL_H


#include <vector>
#include <string>
#include <QString>

using namespace std;

class CPolynomial
{
public:
	CPolynomial();
    CPolynomial(const char* filename);                     // initialization using file

	virtual ~CPolynomial();

    // overload operator
    /*CPolynomial& operator+( CPolynomial &right );	//Overload operator +
	CPolynomial& operator-( CPolynomial &right );	//Overload operator -
	CPolynomial& operator*( CPolynomial &right );	//Overload operator *
    CPolynomial& operator=( CPolynomial &right );*/	//Overload operator =

    float operator()( float x );                    //Overloat operator (), return value of polynomial

    //void Print();
    float value(float x);
    void test();


    void ReadFromFile(const char* file);
  //  void AddOneTerm(Node term);   // add one term into m_Polynomial

private:
    vector<float> m_vCoe;           // coefficients of polynomial
    int m_nOrder;                   // order of polynomial
    int m_nDegree;                  // degree of polynomial
};

#endif
