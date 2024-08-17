#include "Range.h"
#include "Func.h"
#include "ConsoleColor.h"

Range::Range(double _lf, double _rf, bool _null)
{
	if (_null == true || _lf >= _rf)
		return;
	else
	{
		v_range.push_back(_lf);
		v_range.push_back(_rf);
	}
}

Range::Range(const vector<double> _v)
{
	if (_v.empty())
		return;
	if (_v.size() % 2 == 1)
		return;
	for (int i = 0; i < (int)_v.size() - 1; i++)
	{
		if (_v[i] >= _v[i + 1])
			return;
	}
	v_range = _v;
}

Range Range::get_period(const Range& r0)
{
	if (v_range.empty())
		return Range(0, 0, true);
	if (r0.v_range.size() != 2)
		return Range(0, 0, true);
	double T = r0.v_range[1] - r0.v_range[0];
	double r0_offset = mod(r0.v_range[0], T);
	int r0_n = dvd(r0.v_range[0], T);

	double offset = mod(v_range[0] - r0_offset, T);
	int n = dvd(v_range[0] - r0_offset, T);

	Range r1 = Range(vector<double>({ v_range[0], ((double)n + 1) * T + r0_offset }));
	Range r2 = Range(vector<double>({ ((double)n + 1) * T + r0_offset, v_range[1] }));
	Range r3 = (*this) && r1;
	Range r4 = (*this) && r2;
	for (int i = 0; i < (int)r3.v_range.size(); i++)
		r3.v_range[i] -= (double)n * T + r0_offset;

	for (int i = 0; i < (int)r4.v_range.size(); i++)
		r4.v_range[i] -= ((double)n + 1) * T + r0_offset;

	Range res = r3 || r4;
	return res;
}

Range operator&&(const Range& r1, const Range& r2)
{
	vector<double> res;
	int l_pos = 0;
	int r_pos = 0;
	for (int i = 0; i < (int)r2.v_range.size(); i += 2)
	{
		l_pos = insert(r1.v_range, r2.v_range[i], r_pos);
		r_pos = insert(r1.v_range, r2.v_range[i + 1], l_pos);
		if (l_pos % 2 == 1)
			res.push_back(r2.v_range[i]);
		for (int j = l_pos; j < r_pos; j++)
			res.push_back(r1.v_range[j]);
		if (r_pos % 2 == 1)
			res.push_back(r2.v_range[i + 1]);
	}
	return Range(res);
}

Range operator||(const Range& r1, const Range& r2)
{
	vector<double> res;
	int l_pos = 0;
	int r_pos = 0;
	for (int i = 0; i < int(r2.v_range.size()); i += 2)
	{
		l_pos = insert(r1.v_range, r2.v_range[i], r_pos);
		for (int j = r_pos; j < l_pos; j++)
		{
			bool flag = true;
			if (j == r_pos)
				if (res.empty() == false)
					if (double_equal(res[res.size() - 1], r1.v_range[j]))
						flag = false;
			if (flag)
				res.push_back(r1.v_range[j]);
			else
				res.pop_back();
		}
		if (l_pos % 2 == 0)
			res.push_back(r2.v_range[i]);
		r_pos = insert(r1.v_range, r2.v_range[i + 1], l_pos);
		if (r_pos % 2 == 0)
			res.push_back(r2.v_range[i + 1]);
	}
	for (int j = r_pos; j < (int)r1.v_range.size(); j++)
	{
		bool flag = true;
		if (j == r_pos)
			if (res.empty() == false)
				if (double_equal(res[res.size() - 1], r1.v_range[j]))
					flag = false;
		if (flag)
			res.push_back(r1.v_range[j]);
		else
			res.pop_back();
	}

	return Range(res);
}

Range operator-(const Range& r1, const Range& r2)
{
	vector<double> res;
	int l_pos = 0;
	int r_pos = 0;
	for (int i = 0; i < (int)r2.v_range.size(); i += 2)
	{
		l_pos = insert(r1.v_range, r2.v_range[i], r_pos);
		for (int j = r_pos; j < l_pos; j++)
		{
			bool flag = true;
			if (j == r_pos)
				if (res.empty() == false)
					if (double_equal(res[res.size() - 1], r1.v_range[j]))
						flag = false;
			if (flag)
				res.push_back(r1.v_range[j]);
			else
				res.pop_back();
		}
		if (l_pos % 2 == 1)
			res.push_back(r2.v_range[i]);
		r_pos = insert(r1.v_range, r2.v_range[i + 1], l_pos);
		if (r_pos % 2 == 1)
			res.push_back(r2.v_range[i + 1]);
	}
	for (int j = r_pos; j < (int)r1.v_range.size(); j++)
	{
		bool flag = true;
		if (j == r_pos)
			if (res.empty() == false)
				if (double_equal(res[res.size() - 1], r1.v_range[j]))
					flag = false;
		if (flag)
			res.push_back(r1.v_range[j]);
		else
			res.pop_back();
	}

	return Range(res);
}

ostream& operator<<(ostream& cout, const Range& r)
{
	int num = r.v_range.size();
	for (int i = 0; i < num; i += 2)
	{
		cout << "(" << r.v_range[i] << ", " << r.v_range[i + 1] << ")";
		if (i < num - 2)
			cout << ", ";
	}
	if (r.v_range.empty())
		cout << _RED "¿Õ¼¯" _NORMAL;

	return cout;
}