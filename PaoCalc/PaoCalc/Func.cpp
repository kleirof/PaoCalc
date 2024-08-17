#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Func.h"
#include "PaoArngmt.h"
#include "ConsoleColor.h"
using namespace std;

int mod(int a, int b)
{
	if (a >= 0)
		return a % b;
	else
	{
		if (a % b == 0)
			return a % b;
		else
			return a % b + b;
	}
}

double mod(double a, double b)
{
	return a - floor(a / b) * b;
}

int dvd(int a, int b)
{
	if (a >= 0)
		return a / b;
	else
	{
		if (a % b == 0)
			return a / b;
		else
			return a / b - 1;
	}
}

int dvd(double a, double b)
{
	return (int)floor(a / b);
}

bool double_equal(double a, double b)
{
	const double epsilon = 1e-8;
	return abs(a - b) < epsilon;
}

int insert(const vector<double>& _v, double _x, int _left, int _right)
{
	int lp = _left;
	int rp = _right == 0 ? _v.size() : _right;
	int temp = 0;
	while (lp < rp)
	{
		temp = (lp + rp) / 2;
		if (temp == _v.size())
			return temp;
		if (double_equal(_v[temp], _x))
		{
			rp = temp;
			break;
		}
		if (_v[temp] < _x)
			lp = temp + 1;
		if (_v[temp] > _x)
			rp = temp;
	}

	while (rp - 1 >= 0)
	{
		if (double_equal(_v[rp - 1], _v[rp]))
			rp--;
		else
			break;
	}
	return rp;
}

bool end_with(const string& str, const string& end)
{
	if (str.length() < end.length())
		return false;
	return str.substr(str.length() - end.length()) == end;
}

void interact()
{
	system("cls");
	cout << setiosflags(ios::fixed) << setprecision(2);

	while (true)
	{
		cout << _LBLUE "炮轨计算器 PaoCalc v0.5.0 by kleirof：" _NORMAL << endl << endl;

		double t_loop;
		int n_yard;
		vector<double> v_a;

		cout << _YELLOW "打开炮轨文件（回车跳过，0默认default.pa）：>> " _NORMAL;
		string f_name;

		char next = cin.get();
		if (next != '\n')
		{
			cin.putback(next);
			cin >> f_name;
		}

		if (f_name == "0")
			f_name = "default.pa";
		ifstream fin(f_name);
		if (f_name == "" || !fin.is_open())
		{
			if (!(f_name == ""))
				cout << _RED "打开失败" _NORMAL << endl;

			cout << endl << _YELLOW "新建炮轨：" _NORMAL << endl;
			cout << _YELLOW "请输入循环周期（单位s）：>> " _NORMAL;
			cin >> t_loop;
			cout << _YELLOW "请输入场地炮数（-1表示自动计算所需的最小值）：>> " _NORMAL;
			cin >> n_yard;
			cout << _YELLOW "请输入炮序安排（单位s，可以为空，以回车结束）：>> " _NORMAL;

			double buff1;
			cin.clear();
			cin.ignore();
			char next = cin.get();
			if (next != '\n')
			{
				cin.putback(next);
				while (cin >> buff1)
				{
					v_a.push_back(buff1);
					if (cin.get() == '\n')
						break;
				}
			}
		}
		else
		{
			cout << _YELLOW "导入炮轨文件" _NORMAL << f_name << _YELLOW "成功" _NORMAL << endl;
			fin >> t_loop;
			fin >> n_yard;

			double buff1;
			fin.clear();
			fin.ignore();
			char next = fin.get();
			if (next != '\n')
			{
				fin.putback(next);
				while (fin >> buff1)
				{
					v_a.push_back(buff1);
					if (fin.get() == '\n')
						break;
				}
			}
			fin.close();
		}
		cout << endl;

		PaoArngmt p = PaoArngmt(v_a, n_yard, t_loop);
		cout << p << endl;

		bool quit = false;

		while (!quit)
		{
			cout << _LBLUE "炮轨计算器 PaoCalc v0.5.0 by kleirof：" _NORMAL << endl << endl;

			cout << "	1. 计算插入新炮区间（单或多）" << endl;
			cout << "	2. 插入新炮（单或多）" << endl;
			cout << "	3. 移除炮（单或多）" << endl;
			cout << "	4. 计算移动炮区间（单或多）" << endl;
			cout << "	5. 移动炮（单或多）" << endl;
			cout << "	6. 计算某段时间内有几炮（包含端点）" << endl;
			cout << "	7. 计算某炮实际时间（可取负索引或超索引）" << endl;
			cout << "	8. 计算某炮之后某段时间内有几炮（不包含自身，可取负时间）" << endl;
			cout << "	9. 计算场地至少需要几炮" << endl;
			cout << "	10. 修改场地炮数" << endl;
			cout << "	11. 打印炮轨" << endl;
			cout << "	12. 保存炮轨" << endl;
			cout << "	13. 新建炮轨" << endl;
			cout << endl << _YELLOW "输入相应操作：>> " _NORMAL;

			int command;
			cin >> command;

			switch (command)
			{
			case 1:
			{
				cout << endl << "计算插入新炮区间（单或多）" << endl 
					<< _YELLOW "请输入要插入的炮的时间关系（如果炮轨相对0存在偏移，结果也存在偏移）：>> "  _NORMAL;
				vector<double> v_insert;
				double buff_insert;
				while (cin >> buff_insert)
				{
					v_insert.push_back(buff_insert);
					if (cin.get() == '\n')
						break;
				}
				cout << endl << _YELLOW "可以插入区间为："  _NORMAL << p.get_insert_range(v_insert) << endl << endl;
				break;
			}
			case 2:
			{
				cout << endl << "插入新炮（单或多）" << endl << _YELLOW "请输入要插入的炮的时间：>> "  _NORMAL;
				vector<double> v_insert;
				double buff_insert;
				while (cin >> buff_insert)
				{
					v_insert.push_back(buff_insert);
					if (cin.get() == '\n')
						break;
				}
				p.add_pao(v_insert);
				cout << endl << _YELLOW "插入成功"  _NORMAL << endl;
				cout << p << endl;
				break;
			}
			case 3:
			{
				cout << endl << "移除炮（单或多）" << endl << _YELLOW "请输入要移除的炮的序号：>> "  _NORMAL;
				vector<int> v_remove;
				int buff_remove;
				while (cin >> buff_remove)
				{
					v_remove.push_back(buff_remove);
					if (cin.get() == '\n')
						break;
				}
				p.remove_pao(v_remove);
				cout << endl << _YELLOW "移除成功"  _NORMAL << endl;
				cout << p << endl;
				break;
			}
			case 4:
			{
				cout << endl << "计算移动炮区间（单或多）" << endl << _YELLOW "请输入要移动的炮的序号：>> "  _NORMAL;
				vector<int> v_move;
				int buff_move;
				while (cin >> buff_move)
				{
					v_move.push_back(buff_move);
					if (cin.get() == '\n')
						break;
				}
				cout << endl << _YELLOW "可以移动区间为："  _NORMAL << p.get_move_range(v_move) << endl << endl;
				break;
			}
			case 5:
			{
				cout << endl << "移动炮（单或多）" << endl << _YELLOW "请输入要移动的炮的序号：>> "  _NORMAL;
				vector<int> v_move;
				int buff_move;
				while (cin >> buff_move)
				{
					v_move.push_back(buff_move);
					if (cin.get() == '\n')
						break;
				}
				cout << _YELLOW "请输入要整体移动到的时间：>> "  _NORMAL;
				double t;
				cin >> t;
				p.move_pao(v_move, t);
				cout << endl << _YELLOW "移动成功"  _NORMAL << endl;
				cout << p << endl;
				break;
			}
			case 6:
			{
				cout << endl << "计算某段时间内有几炮（包含端点）" << endl << _YELLOW "请输入起始时间：>> "  _NORMAL;
				double t1;
				cin >> t1;
				cout << _YELLOW "请输入结束时间：>> "  _NORMAL;
				double t2;
				cin >> t2;
				cout << endl << _YELLOW "从"  _NORMAL << t1 << _YELLOW "到"  _NORMAL << t2 << _YELLOW "时间内存在 "  _NORMAL
					<< p.get_pao_num_form_t1_to_t2(t1, t2) << " 炮" << endl << endl;
				break;
			}
			case 7:
			{
				cout << endl << "计算某炮实际时间（可取负索引或超索引）" << endl << _YELLOW "请输入炮的序号：>> "  _NORMAL;
				int n;
				cin >> n;
				cout << endl << _YELLOW "炮的实际时间为 "  _NORMAL << p.get_real_time(n) << endl << endl;
				break;
			}
			case 8:
			{
				cout << endl << "计算某炮之后某段时间内有几炮（不包含自身，可取负时间）" << endl << _YELLOW "请输入炮的序号：>> "  _NORMAL;
				int n;
				cin >> n;
				cout << _YELLOW "请输入要查看的时间长度：>> "  _NORMAL;
				double t;
				cin >> t;
				cout << endl << _YELLOW "炮"  _NORMAL << n << _YELLOW "之后的"  _NORMAL << t << _YELLOW "时间内有 "  _NORMAL << p.get_num_in_tx(n, t) << _YELLOW " 炮"  _NORMAL << endl << endl;
				break;
			}
			case 9:
			{
				cout << endl << "计算场地至少需要几炮" << endl;
				cout << endl << _YELLOW "场地至少需要 "  _NORMAL << p.get_min_pao_num_needed() << _YELLOW " 炮"  _NORMAL << endl << endl;
				break;
			}
			case 10:
			{
				cout << endl << "修改场地炮数" << endl << _YELLOW "请输入场地炮数：>> "  _NORMAL;
				int n;
				cin >> n;
				p.change_n_yard(n);
				cout << endl << _YELLOW "修改成功"  _NORMAL << endl;
				cout << p << endl;
				break;
			}
			case 11:
			{
				cout << endl << "打印炮轨" << endl << endl;
				cout << p << endl;
				break;
			}
			case 12:
			{
				cout << endl << "保存炮轨" << endl << _YELLOW "请输入文件路径（回车取消，0默认default.pa）： >> "  _NORMAL;
				string f_save;

				cin.clear();
				cin.ignore();
				char next = cin.get();
				if (next != '\n')
				{
					cin.putback(next);
					cin >> f_save;
				}
				if (f_save != "")
				{
					if (f_save == "0")
						f_save = "default.pa";
					if (!end_with(f_save, ".pa"))
						f_save = f_save.append(".pa");
					ofstream fout(f_save);
					if (fout.is_open())
					{
						fout << p.T_loop << endl;
						fout << p.N_yard << endl;
						for (int i = 0; i < (int)p.v_arngmt.size(); i++)
						{
							fout << p.v_arngmt[i];
							if (i < (int)p.v_arngmt.size() - 1)
								fout << " ";
						}
						fout.close();
						cout << f_save << _YELLOW "保存成功"  _NORMAL << endl << endl;
					}
					else
						cout << _RED "保存失败"  _NORMAL << endl << endl;
				}
				else
					cout << _YELLOW "已取消"  _NORMAL << endl << endl;

				break;
			}
			case 13:
			{
				cin.clear();
				cin.ignore();
				cout << endl << _RED "是否删除原有炮轨并新建？(y/n) >> "  _NORMAL;
				char a = cin.get();
				if (a == 'y' || a == 'Y')
				{
					cout << endl << endl << endl << endl << endl << endl << endl << endl;
					quit = true;
					cin.clear();
					cin.ignore();
				}
				else
				{
					cout << _YELLOW "已取消"  _NORMAL << endl << endl;;
				}
				break;
			}
			default:
				break;
			}
		}
	}
}