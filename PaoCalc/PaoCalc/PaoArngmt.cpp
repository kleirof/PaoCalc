#include "PaoArngmt.h"
#include "Func.h"
#include "ConsoleColor.h"

PaoArngmt::PaoArngmt(vector<double> _v, int _n_y, double _t_l)
{
	T_loop = _t_l;
	if (_v.empty() == false)
	{
		for (int i = 0; i < (int)_v.size(); i++)
		{
			_v[i] = mod(_v[i], T_loop);
		}
		sort(_v.begin(), _v.end());
	}
	v_arngmt = _v;
	N_loop = _v.size();
	if (_n_y == -1)
		N_yard = get_min_pao_num_needed();
	else
		N_yard = _n_y > 0 ? _n_y : 0;

	exmn_loop();
}

double PaoArngmt::get_real_time(int nx)
{
	return v_arngmt[mod(nx - 1, N_loop)] + dvd(nx - 1, N_loop) * T_loop;
}

int PaoArngmt::get_pao_num_form_t1_to_t2(double t1, double t2)
{
	if (t2 < t1)
	{
		double temp = t2;
		t2 = t1;
		t1 = temp;
	}
	int num_loop = dvd(t1, T_loop);
	double offset = mod(t1, T_loop);
	int start = mod(insert(v_arngmt, offset), N_loop);
	int count = 0;
	double t_temp = num_loop * T_loop;
	int i = start;

	while (v_arngmt[i] + t_temp < t2 || double_equal(v_arngmt[i] + t_temp, t2))
	{
		count++;
		i++;
		if (i == N_loop)
		{
			i = 0;
			t_temp += T_loop;
		}
	}
	return count;
}

int PaoArngmt::get_num_in_tx(int nx, double tx)
{
	int count = 0;
	double t_end = get_real_time(nx) + tx;
	if (tx >= 0)
	{
		double t_temp = dvd(nx, N_loop) * T_loop;
		int i = mod(nx, N_loop);

		while (v_arngmt[i] + t_temp <= t_end)
		{
			count++;
			i++;
			if (i == N_loop)
			{
				i = 0;
				t_temp += T_loop;
			}
		}
	}
	else
	{
		double t_temp = dvd(nx - 2, N_loop) * T_loop;
		int i = mod(nx - 2, N_loop);

		while (v_arngmt[i] + t_temp >= t_end)
		{
			count++;
			i--;
			if (i == -1)
			{
				i = N_loop - 1;
				t_temp -= T_loop;
			}
		}
	}
	return count;
}

int PaoArngmt::get_min_pao_num_needed()
{
	int num = 0;
	for (int i = 1; i <= N_loop; i++)
	{
		int temp = get_num_in_tx(i, T_pao);
		if (temp > num)
			num = temp;
	}
	return num + 1;
}

bool PaoArngmt::exmn_loop()
{
	v_exmn_num.clear();
	v_exmn_res.clear();
	int num;
	bool res = true;

	for (int i = 1; i <= N_loop; i++)
	{
		num = get_num_in_tx(i, T_pao);
		v_exmn_num.push_back(num);
		if (num < N_yard)
			v_exmn_res.push_back(true);
		else
		{
			v_exmn_res.push_back(false);
			res = false;
		}
	}
	exmn_res = res;
	return res;
}

void PaoArngmt::add_pao(double _t)
{
	_t = mod(_t, T_loop);
	int idx = insert(v_arngmt, _t);
	v_arngmt.insert(v_arngmt.begin() + idx, _t);
	N_loop++;
	exmn_loop();
}

void PaoArngmt::add_pao(vector<double> _v)
{
	for (int i = 0; i < (int)_v.size(); i++)
	{
		_v[i] = mod(_v[i], T_loop);
		int idx = insert(v_arngmt, _v[i]);
		v_arngmt.insert(v_arngmt.begin() + idx, _v[i]);
	}
	N_loop += _v.size();
	exmn_loop();
}

void PaoArngmt::remove_pao(int _n)
{
	_n = mod(_n - 1, N_loop) + 1;
	v_arngmt.erase(v_arngmt.begin() + _n - 1);
	N_loop--;
	exmn_loop();
}

void PaoArngmt::remove_pao(vector<int> _v)
{
	if (_v.empty())
		return;
	for (int i = 0; i < (int)_v.size(); i++)
		_v[i] = mod(_v[i] - 1, N_loop) + 1;
	sort(_v.begin(), _v.end());
	int j = 0;
	int cnt = 0;
	for (int j = 0; j < (int)_v.size(); j++)
		v_arngmt.erase(v_arngmt.begin() + _v[j] - j - 1);
	N_loop -= _v.size();
	exmn_loop();
}

void PaoArngmt::move_pao(int _n, double _t)
{
	remove_pao(_n);
	add_pao(_t);
}

void PaoArngmt::move_pao(vector<int> _v, double _t)
{
	for (int i = 0; i < (int)_v.size(); i++)
		_v[i] = mod(_v[i] - 1, N_loop) + 1;
	vector<double> v_t;
	for (int i = 0; i < (int)_v.size(); i++)
		v_t.push_back(v_arngmt[_v[i] - 1] - v_arngmt[_v[0] - 1] + _t);
	remove_pao(_v);
	add_pao(v_t);
}

Sequence PaoArngmt::get_seq_of_argmnt()
{
	vector<Range> v_r;
	Range r0 = Range(0, T_loop);
	for (int i = 0; i < (int)v_arngmt.size(); i++)
		v_r.push_back(Range(v_arngmt[i] - T_pao, v_arngmt[i]).get_period(r0));
	return Sequence(v_r, T_loop);
}

Range PaoArngmt::get_insert_range()
{
	if (v_arngmt.empty())
		return Range(0, 0, true);
	Range r0 = Range(0, T_loop);
	Range res = Range(0, 0, true);
	for (int i = 1; i <= (int)v_arngmt.size(); i++)
	{
		if (get_num_in_tx(i, T_pao) + 1 >= N_yard)
			res = res || Range(v_arngmt[i - 1], v_arngmt[i - 1] + T_pao).get_period(r0);
		if (get_num_in_tx(i, -T_pao) + 1 >= N_yard)
			res = res || Range(v_arngmt[i - 1] - T_pao, v_arngmt[i - 1]).get_period(r0);
	}
	return r0 - res;
}

Range PaoArngmt::get_insert_range(const vector<double>& _v)
{
	if (v_arngmt.empty())
		return Range(0, 0, true);
	Sequence insert_seq = Sequence(_v, T_loop, T_pao);
	Sequence seq = get_seq_of_argmnt();
	Range r = seq.get_avai_range(insert_seq, N_yard);
	return r;
}

Range PaoArngmt::get_move_range(int _n)
{
	_n = mod(_n - 1, N_loop) + 1;
	PaoArngmt p = *this;
	p.remove_pao(_n);
	return p.get_insert_range();
}

Range PaoArngmt::get_move_range(vector<int> _v)
{
	for (int i = 0; i < (int)_v.size(); i++)
		_v[i] = mod(_v[i] - 1, N_loop) + 1;
	PaoArngmt p = *this;
	p.remove_pao(_v);
	vector<double> v_d;
	for (int i = 0; i < (int)_v.size(); i++)
		v_d.push_back(v_arngmt[_v[i] - 1] - v_arngmt[_v[0] - 1]);
	return p.get_insert_range(v_d);
}

void PaoArngmt::change_n_yard(int n)
{
	N_yard = n > 0 ? n : 0;
	exmn_loop();
}

ostream& operator<<(ostream& cout, const PaoArngmt& r)
{
	cout << _PURPLE "循环炮数： " _NORMAL << r.N_loop << _PURPLE ", 场地炮数： " _NORMAL
		<< r.N_yard << _PURPLE ", 循环周期： " _NORMAL << r.T_loop << _PURPLE ", 冷却周期： " _NORMAL << r.T_pao
		<< endl << _PURPLE "炮序安排：" _NORMAL << endl << "{ ";

	int num = r.v_arngmt.size();
	for (int i = 0; i < num; i++)
	{
		cout << "{" << _BLUE << i + 1 << _NORMAL << ":" << r.v_arngmt[i] << "}";
		if (i < num - 1)
			cout << ", ";
	}
	cout << " }" << endl << _PURPLE "检查结果： " _NORMAL;
	cout << (r.exmn_res ? _GREEN "√" _NORMAL : _RED "×" _NORMAL) << endl;
	cout << _PURPLE "每炮结果：（是否可以复用，未来34.75内有几炮（不包含自身））" _NORMAL << endl << "{ ";

	num = r.v_exmn_res.size();
	for (int i = 0; i < num; i++)
	{
		cout << "{" << _BLUE << i + 1<< _NORMAL << ":";
		cout << (r.v_exmn_res[i] ? _GREEN "√" _NORMAL : _RED "×" _NORMAL) 
			<< " " << r.v_exmn_num[i] << "}";
		if (i < num - 1)
			cout << ", ";
	}
	cout << " }" << endl;

	return cout;
}