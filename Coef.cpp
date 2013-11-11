#include "Coef.h"
#include <QDebug>

CCoef::CCoef(void)
{
}

CCoef::CCoef(int n, int k)
{
	m_nK	=	k;
	m_nN	=	n;
}


CCoef::~CCoef(void)
{
}

void CCoef::Init(int n, int k)
{
	m_nK	=	k;
	m_nN	=	n;
}

double CCoef::C(int n, int i)
{
	double fResult	=	1.0f;
	for (int j=1; j<i+1; j++)
	{
		fResult	=	fResult * (n + 1 - j) /(1.0 * (i-j+1));
	}
	return(fResult);
}

double CCoef::BIner(int m, int i, int n, int j)
{
	double fResult	=	1.0f;
	fResult	=	C(m, i) * C(n, j) /(1.0 * (m + n +1) * C(m+n, i+j));
	return(fResult);
}

double CCoef::Cpq(int p, int q)
{
	double fReuslt	=	0.0f;
	double fCoef;
	/*double fCoef		=	pow(-1.0, p+q) * (C(m_nK, p) * C(m_nK, q));*/
	if ((p+q)%2 == 0)
	{
		fCoef		=	(C(m_nK, p) * C(m_nK, q));
	}
	else
	{
		fCoef		=	-(C(m_nK, p) * C(m_nK, q));
	}
	if (p>q)
	{
		double fTemp	=	p;
		p	=	q;
		q	=	fTemp;
	}
	for (int j=0; j<p+1; j++)
	{
		double fTemp;
		fTemp	=	(2*j+1) * C(m_nK+j+1, m_nK-p) * C(m_nK-j, m_nK-p) * C(m_nK+j+1, m_nK-q) * C(m_nK-j, m_nK-q);
		fReuslt	=	fReuslt + fTemp;
	}
	fReuslt	=	fReuslt / (1.0f * fCoef);
	return(fReuslt);
}

void CCoef::CalculateMatrix()
{
    m_coefMatrix.resize(m_nN+1);
    for(size_t i=0; i<m_nN+1; i++)
    {
        m_coefMatrix[i].resize(m_nK+1);
    }

	for (int i=0; i<m_nN+1; i++)
	{
		for (int j=0; j<m_nK+1; j++)
		{
			double fTemp	=	0;
			for (int k=0; k<m_nK+1; k++)
			{
				fTemp	=	fTemp + Cpq(k,j)*BIner(m_nN, i, m_nK, k);
			}
            m_coefMatrix[i][j]	=	fTemp;
		}
	}

}

void CCoef::GetMatrix(mat &coefMatrix)
{
    qDebug()<<"matrix size"<<m_coefMatrix.size();
    CalculateMatrix();
	coefMatrix	=	m_coefMatrix;
}
