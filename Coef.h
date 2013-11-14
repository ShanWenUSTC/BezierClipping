#ifndef COE_H
#define COE_H

#include <math.h>
#include <iostream>
#include <vector>
#include "classdef.h"

typedef std::vector< std::vector<double> > mat;

class CCoef
{
public:
	CCoef(void);
	CCoef(int n, int k);
	~CCoef(void);

public:
	void Init(int n, int k);
	double BIner(int m, int i, int n, int j);
	double Cpq(int p, int q);
	double C(int n, int i);
	void CalculateMatrix();
    void GetMatrix(mat &coefMatrix);

private:
	int			m_nN;
	int			m_nK;
    mat	m_coefMatrix;
};

#endif
