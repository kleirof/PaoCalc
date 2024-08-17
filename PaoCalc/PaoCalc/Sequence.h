#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "SeqElement.h"
#include "Range.h"
using namespace std;

class Sequence
{
public:
	vector<SeqElement> v_seq;
	double T;

	friend ostream& operator<<(ostream& cout, const Sequence& s);

	Sequence(double _t);

	Sequence(vector<double> _v, double _T_l, double _T_p);

	Sequence(vector<Range> _v, double _t);

	vector<SeqElement> recalc_seq(vector<SeqElement> v0);

	vector<SeqElement> break_down();

	Sequence add_seq(Sequence l);

	Sequence roll_seq(double _t);

	double get_closest_from_t(double _t);

	double get_closest_from_Seq(Sequence l);

	int get_peak_value();

	Range get_avai_range(Sequence l, int _n);
};