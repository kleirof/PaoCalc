#pragma once
#include <vector>
#include "Sequence.h"
#include "Range.h"

class PaoArngmt
{
public:
	vector<double> v_arngmt;
	int N_loop;
	int N_yard;
	double T_loop;
	const double T_pao = 34.75f;
	vector<int> v_exmn_num;
	vector<bool> v_exmn_res;
	bool exmn_res;

	friend ostream& operator<<(ostream& cout, const PaoArngmt& r);

	PaoArngmt(vector<double> _v, int _n_y, double _t_l);

	double get_real_time(int nx);

	int get_pao_num_form_t1_to_t2(double t1, double t2);

	int get_num_in_tx(int nx, double tx);

	int get_min_pao_num_needed();

	bool exmn_loop();

	void add_pao(double _t);

	void add_pao(vector<double> _v);

	void remove_pao(int _n);

	void remove_pao(vector<int> _v);

	void move_pao(int _n, double _t);

	void move_pao(vector<int> _v, double _t);

	Sequence get_seq_of_argmnt();

	Range get_insert_range();

	Range get_insert_range(const vector<double>& _v);

	Range get_move_range(int _n);

	Range get_move_range(vector<int> _v);

	void change_n_yard(int n);
};
