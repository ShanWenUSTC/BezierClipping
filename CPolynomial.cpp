#include "CPolynomial.h"
#include <fstream>
#include <iostream>

#include <QDebug>

using namespace std;

CPolynomial::CPolynomial()
{
    m_nOrder = 1;
    m_nDegree = 0;
}

CPolynomial::CPolynomial(const char* filename)
{
    ReadFromFile(filename);
}

CPolynomial::~CPolynomial()
{

}

//CPolynomial& CPolynomial::operator+( CPolynomial &right )
//{
//    list<Node> m_Ptmp1(m_Polynomial);
//	list<Node>::iterator iter;

//	for (iter = right.m_Polynomial.begin(); iter != right.m_Polynomial.end(); iter++)
//	{
//		AddOneTerm(*iter);
//	}

//    static CPolynomial m_Ptmp2= *this;
//    m_Polynomial = m_Ptmp1;

//	return(m_Ptmp2);
//}

//CPolynomial& CPolynomial::operator-( CPolynomial &right )
//{
//    list<Node> m_Ptmp1(m_Polynomial);
//	list<Node>::iterator iter;
//	Node ntmp;

//	for (iter = right.m_Polynomial.begin(); iter != right.m_Polynomial.end(); iter++)
//	{
//		ntmp.deg = (*iter).deg;
//		ntmp.cof = (*iter).cof * (-1);

//		AddOneTerm(ntmp);
//	}

//    static CPolynomial m_Ptmp2 = *this;
//    m_Polynomial = m_Ptmp1;

//	return(m_Ptmp2);
//}

//CPolynomial& CPolynomial::operator*( CPolynomial &right )
//{
//    list<Node> m_Ptmp1(m_Polynomial);
//    m_Polynomial.clear();

//	list<Node>::iterator iter1;
//	list<Node>::iterator iter2;
//	Node ntmp;

//	for (iter1 = m_Ptmp1.begin(); iter1 != m_Ptmp1.end(); iter1++)
//	{
//		for (iter2 = right.m_Polynomial.begin(); iter2 != right.m_Polynomial.end(); iter2++)
//		{
//			ntmp.cof = (*iter1).cof * (*iter2).cof;
//			ntmp.deg = (*iter1).deg + (*iter2).deg;

//			AddOneTerm(ntmp);
//		}
//	}

//    static CPolynomial m_Ptmp2 = *this;
//    m_Polynomial = m_Ptmp1;

//	return(m_Ptmp2);
//}

//CPolynomial& CPolynomial::operator=( CPolynomial &right )
//{
//    m_Polynomial.clear();

//	list<Node>::iterator iter;

//	for (iter = right.m_Polynomial.begin(); iter != right.m_Polynomial.end(); iter++)
//	{
//		AddOneTerm(*iter);
//	}

//	return(*this);
//}

float CPolynomial::operator ()( float x )
{
    return value(x);
}

float CPolynomial::value( float x )
{
    float sum = m_vCoe[m_nDegree];

    for(int i=m_nDegree; i>0; i--)
    {
        sum = sum*x+m_vCoe[i-1];
    }

    return sum;
}

//void CPolynomial::Print()
//{
//	list<Node>::iterator iter;

//	cout << 'P' << "   " << m_Polynomial.size() << endl;

//	for (iter = m_Polynomial.begin(); iter != m_Polynomial.end(); iter++)
//	{
//		cout << (*iter).deg << "   " << (*iter).cof << endl;
//	}

//	cout << endl;
//}

void CPolynomial::ReadFromFile(const char* filename)
{
	ifstream infile;                          
    infile.open( filename );

    if(!infile)
	{
		cout << "ERROR! Can't open P1.txt!" 
			 << endl;
		return;
	}
    
	int n;
	char a;                                  
    infile >> a >> n;

	if (a != 'P')
	{
		cout << "ERROR! Wrong File!" 
		     << endl;
		return;
	}

    m_vCoe.resize(n+1);
    for(int i=0; i<n+1; i++)
    {
        m_vCoe[i] = 0;
    }

    m_nOrder = n+1;
    m_nDegree = n;
    qDebug()<<n;

    int deg;
    float coe;
    while(infile)
    {
        infile >> deg >> coe;
        m_vCoe[deg] = coe;
    }

    infile.close();
    test();
}

void CPolynomial::test()
{
    for(int i=0; i<m_nOrder; i++)
    {
        qDebug()<<i<<" "<<m_vCoe[i];
    }

    qDebug()<<(4.2);
}

//void CPolynomial::AddOneTerm(Node term)
//{
//    int i = 0;

//    if (m_Polynomial.size() == 0)
//	{
//		m_Polynomial.push_front(term);
//		return;
//	}

//	list<Node>::iterator iter;

//	for (iter = m_Polynomial.begin(); iter != m_Polynomial.end(); iter++)
//	{
//        if (term.deg == (*iter).deg)
//		{
//			(*iter).cof = (*iter).cof + term.cof;
//			i = 1;
//			return;
//		}

//		else
//		{
//            if (term.deg < (*iter).deg)
//			{
//				m_Polynomial.insert(iter, term);
//				i = 1;
//				return;
//			}
//		}
//	}

//    if (!i)
//		m_Polynomial.push_back(term);
//}

