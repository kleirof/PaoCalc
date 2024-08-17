#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

class Range
{
public:
	vector<double> v_range;

	friend Range operator&&(const Range& r1, const Range& r2);
	friend Range operator||(const Range& r1, const Range& r2);
	friend Range operator-(const Range& r1, const Range& r2);
	friend ostream& operator<<(ostream& cout, const Range& r);

	Range(double _lf = 0, double _rf = 0, bool _null = false);

	Range(const vector<double> _v);

	Range get_period(const Range& r0);
};

