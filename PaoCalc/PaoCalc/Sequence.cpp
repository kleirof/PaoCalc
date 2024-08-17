#include "Sequence.h"
#include "Func.h"

Sequence::Sequence(double _t)
{
	T = _t;
}

Sequence::Sequence(vector<double> _v, double _T_l, double _T_p)
{
	T = 0;
	if (_v.empty())
		return;
	T = _T_l;
	Range r0 = Range(0, _T_l);
	vector<Range> v_r;
	for (int i = 0; i < (int)_v.size(); i++)
		v_r.push_back(Range(_v[i] - _T_p, _v[i]).get_period(r0));

	vector<SeqElement> v0;
	for (int i = 0; i < (int)v_r.size(); i++)
	{
		for (int j = 0; j < (int)v_r[i].v_range.size(); j++)
			v0.push_back(SeqElement(v_r[i].v_range[j], j % 2 == 0 ? 1 : -1));
	}
	v_seq = recalc_seq(v0);
}

Sequence::Sequence(vector<Range> _v, double _t)
{
	T = 0;
	if (_v.empty())
		return;
	T = _t;
	vector<SeqElement> v0;
	for (int i = 0; i < (int)_v.size(); i++)
	{
		for (int j = 0; j < (int)_v[i].v_range.size(); j++)
		{
			v0.push_back(SeqElement(_v[i].v_range[j], j % 2 == 0 ? 1 : -1));
		}
	}
	v_seq = recalc_seq(v0);
}

vector<SeqElement> Sequence::recalc_seq(vector<SeqElement> v0)
{
	if (v0.empty())
		return v0;
	sort(v0.begin(), v0.end(), [&](const SeqElement& a, const SeqElement& b) -> bool {
		return a.time < b.time;
		});
	int sum = 0;
	for (int i = 0; i < (int)v0.size(); i++)
	{
		sum += v0[i].value;
		v0[i].value = sum;
	}
	int min = v0[0].value;
	for (int i = 1; i < (int)v0.size(); i++)
	{
		if (v0[i].value < min)
			min = v0[i].value;
	}
	for (int i = 0; i < (int)v0.size(); i++)
	{
		v0[i].value -= min;
	}
	int j = 0;
	while (j < (int)v0.size())
	{
		if (double_equal(v0[j].time, v0[mod(j + 1, v0.size())].time))
			v0.erase(v0.begin() + j);
		else
			j++;
	}
	j = 0;
	while (j < (int)v0.size())
	{
		if (v0[j].value == v0[mod(j - 1, v0.size())].value)
			v0.erase(v0.begin() + j);
		else
			j++;
	}
	return v0;
}

vector<SeqElement> Sequence::break_down()
{
	vector<SeqElement> res;
	for (int i = 0; i < (int)v_seq.size(); i++)
	{
		res.push_back(SeqElement{ v_seq[i].time, v_seq[i].value - v_seq[mod(i - 1,v_seq.size())].value });
	}
	return res;
}

Sequence Sequence::add_seq(Sequence l)
{
	vector<SeqElement> v1 = break_down();
	vector<SeqElement> v2 = l.break_down();
	for (int i = 0; i < (int)l.v_seq.size(); i++)
		v1.push_back(v2[i]);
	Sequence res(T);
	res.v_seq = recalc_seq(v1);
	return res;
}

Sequence Sequence::roll_seq(double _t)
{
	Sequence res(T);
	vector<SeqElement> v = break_down();
	for (int i = 0; i < (int)v.size(); i++)
	{
		v[i].time = mod(v[i].time + _t, T);
	}
	sort(v.begin(), v.end(), [&](const SeqElement& a, const SeqElement& b) -> bool {
		return a.time < b.time;
		});
	vector<SeqElement> temp = recalc_seq(v);
	if (!v.empty())
	{
		if (!double_equal(v[0].time, 0))
			v.insert(v.begin(), SeqElement(0, temp[temp.size() - 1].value));
		if (!double_equal(v[v.size() - 1].time, T))
			v.push_back(SeqElement(T, -temp[temp.size() - 1].value));
	}
	v = recalc_seq(v);
	res.v_seq = v;
	return res;
}

double Sequence::get_closest_from_t(double _t)
{
	_t = mod(_t, T);
	double min = T;
	for (int i = 0; i < (int)v_seq.size(); i++)
	{
		double temp;
		if (_t > v_seq[i].time || double_equal(_t, v_seq[i].time))
			temp = T - (_t - v_seq[i].time);
		else
			temp = v_seq[i].time - _t;
		if (temp < min)
			min = temp;
	}
	return min;
}

double Sequence::get_closest_from_Seq(Sequence l)
{
	double min = T;
	for (int i = 0; i < (int)l.v_seq.size(); i++)
	{
		double temp = get_closest_from_t(l.v_seq[i].time);
		if (temp < min)
			min = temp;
	}
	return min;
}

int Sequence::get_peak_value()
{
	int max = 0;
	for (int i = 0; i < (int)v_seq.size(); i++)
	{
		if (v_seq[i].value > max)
			max = v_seq[i].value;
	}
	return max;
}

Range Sequence::get_avai_range(Sequence l, int _n)
{
	double init_t = get_closest_from_Seq(l);
	double crt_t = init_t;
	Sequence l_t = l.roll_seq(init_t);
	l = l_t;
	Range r0 = Range(0, T);
	Range res;
	double roll_t = get_closest_from_Seq(l_t) / 2;
	while ((crt_t < T + init_t || double_equal(crt_t, T + init_t)) && roll_t > 0)
	{
		l_t = l.roll_seq(roll_t);
		l = l.roll_seq(2 * roll_t);
		Sequence l1 = add_seq(l_t);
		int n1 = l1.get_peak_value();
		if (n1 <= _n)
		{
			Range r1 = Range(crt_t, crt_t + 2 * roll_t).get_period(r0);
			res = res || r1;
		}
		crt_t += 2 * roll_t;
		roll_t = get_closest_from_Seq(l) / 2;
	}
	return res;
}

ostream& operator<<(ostream& cout, const Sequence& s)
{
	int num = s.v_seq.size();
	for (int i = 0; i < num; i++)
		cout << "{" << i + 1 << ": {" << s.v_seq[i].time << ", " << s.v_seq[i].value << "}}, ";

	cout << " T = " << s.T << endl;

	return cout;
}