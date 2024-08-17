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
		cout << _LBLUE "�ڹ������ PaoCalc v0.5.0 by kleirof��" _NORMAL << endl << endl;

		double t_loop;
		int n_yard;
		vector<double> v_a;

		cout << _YELLOW "���ڹ��ļ����س�������0Ĭ��default.pa����>> " _NORMAL;
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
				cout << _RED "��ʧ��" _NORMAL << endl;

			cout << endl << _YELLOW "�½��ڹ죺" _NORMAL << endl;
			cout << _YELLOW "������ѭ�����ڣ���λs����>> " _NORMAL;
			cin >> t_loop;
			cout << _YELLOW "�����볡��������-1��ʾ�Զ������������Сֵ����>> " _NORMAL;
			cin >> n_yard;
			cout << _YELLOW "�����������ţ���λs������Ϊ�գ��Իس���������>> " _NORMAL;

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
			cout << _YELLOW "�����ڹ��ļ�" _NORMAL << f_name << _YELLOW "�ɹ�" _NORMAL << endl;
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
			cout << _LBLUE "�ڹ������ PaoCalc v0.5.0 by kleirof��" _NORMAL << endl << endl;

			cout << "	1. ��������������䣨����ࣩ" << endl;
			cout << "	2. �������ڣ�����ࣩ" << endl;
			cout << "	3. �Ƴ��ڣ�����ࣩ" << endl;
			cout << "	4. �����ƶ������䣨����ࣩ" << endl;
			cout << "	5. �ƶ��ڣ�����ࣩ" << endl;
			cout << "	6. ����ĳ��ʱ�����м��ڣ������˵㣩" << endl;
			cout << "	7. ����ĳ��ʵ��ʱ�䣨��ȡ��������������" << endl;
			cout << "	8. ����ĳ��֮��ĳ��ʱ�����м��ڣ�������������ȡ��ʱ�䣩" << endl;
			cout << "	9. ���㳡��������Ҫ����" << endl;
			cout << "	10. �޸ĳ�������" << endl;
			cout << "	11. ��ӡ�ڹ�" << endl;
			cout << "	12. �����ڹ�" << endl;
			cout << "	13. �½��ڹ�" << endl;
			cout << endl << _YELLOW "������Ӧ������>> " _NORMAL;

			int command;
			cin >> command;

			switch (command)
			{
			case 1:
			{
				cout << endl << "��������������䣨����ࣩ" << endl 
					<< _YELLOW "������Ҫ������ڵ�ʱ���ϵ������ڹ����0����ƫ�ƣ����Ҳ����ƫ�ƣ���>> "  _NORMAL;
				vector<double> v_insert;
				double buff_insert;
				while (cin >> buff_insert)
				{
					v_insert.push_back(buff_insert);
					if (cin.get() == '\n')
						break;
				}
				cout << endl << _YELLOW "���Բ�������Ϊ��"  _NORMAL << p.get_insert_range(v_insert) << endl << endl;
				break;
			}
			case 2:
			{
				cout << endl << "�������ڣ�����ࣩ" << endl << _YELLOW "������Ҫ������ڵ�ʱ�䣺>> "  _NORMAL;
				vector<double> v_insert;
				double buff_insert;
				while (cin >> buff_insert)
				{
					v_insert.push_back(buff_insert);
					if (cin.get() == '\n')
						break;
				}
				p.add_pao(v_insert);
				cout << endl << _YELLOW "����ɹ�"  _NORMAL << endl;
				cout << p << endl;
				break;
			}
			case 3:
			{
				cout << endl << "�Ƴ��ڣ�����ࣩ" << endl << _YELLOW "������Ҫ�Ƴ����ڵ���ţ�>> "  _NORMAL;
				vector<int> v_remove;
				int buff_remove;
				while (cin >> buff_remove)
				{
					v_remove.push_back(buff_remove);
					if (cin.get() == '\n')
						break;
				}
				p.remove_pao(v_remove);
				cout << endl << _YELLOW "�Ƴ��ɹ�"  _NORMAL << endl;
				cout << p << endl;
				break;
			}
			case 4:
			{
				cout << endl << "�����ƶ������䣨����ࣩ" << endl << _YELLOW "������Ҫ�ƶ����ڵ���ţ�>> "  _NORMAL;
				vector<int> v_move;
				int buff_move;
				while (cin >> buff_move)
				{
					v_move.push_back(buff_move);
					if (cin.get() == '\n')
						break;
				}
				cout << endl << _YELLOW "�����ƶ�����Ϊ��"  _NORMAL << p.get_move_range(v_move) << endl << endl;
				break;
			}
			case 5:
			{
				cout << endl << "�ƶ��ڣ�����ࣩ" << endl << _YELLOW "������Ҫ�ƶ����ڵ���ţ�>> "  _NORMAL;
				vector<int> v_move;
				int buff_move;
				while (cin >> buff_move)
				{
					v_move.push_back(buff_move);
					if (cin.get() == '\n')
						break;
				}
				cout << _YELLOW "������Ҫ�����ƶ�����ʱ�䣺>> "  _NORMAL;
				double t;
				cin >> t;
				p.move_pao(v_move, t);
				cout << endl << _YELLOW "�ƶ��ɹ�"  _NORMAL << endl;
				cout << p << endl;
				break;
			}
			case 6:
			{
				cout << endl << "����ĳ��ʱ�����м��ڣ������˵㣩" << endl << _YELLOW "��������ʼʱ�䣺>> "  _NORMAL;
				double t1;
				cin >> t1;
				cout << _YELLOW "���������ʱ�䣺>> "  _NORMAL;
				double t2;
				cin >> t2;
				cout << endl << _YELLOW "��"  _NORMAL << t1 << _YELLOW "��"  _NORMAL << t2 << _YELLOW "ʱ���ڴ��� "  _NORMAL
					<< p.get_pao_num_form_t1_to_t2(t1, t2) << " ��" << endl << endl;
				break;
			}
			case 7:
			{
				cout << endl << "����ĳ��ʵ��ʱ�䣨��ȡ��������������" << endl << _YELLOW "�������ڵ���ţ�>> "  _NORMAL;
				int n;
				cin >> n;
				cout << endl << _YELLOW "�ڵ�ʵ��ʱ��Ϊ "  _NORMAL << p.get_real_time(n) << endl << endl;
				break;
			}
			case 8:
			{
				cout << endl << "����ĳ��֮��ĳ��ʱ�����м��ڣ�������������ȡ��ʱ�䣩" << endl << _YELLOW "�������ڵ���ţ�>> "  _NORMAL;
				int n;
				cin >> n;
				cout << _YELLOW "������Ҫ�鿴��ʱ�䳤�ȣ�>> "  _NORMAL;
				double t;
				cin >> t;
				cout << endl << _YELLOW "��"  _NORMAL << n << _YELLOW "֮���"  _NORMAL << t << _YELLOW "ʱ������ "  _NORMAL << p.get_num_in_tx(n, t) << _YELLOW " ��"  _NORMAL << endl << endl;
				break;
			}
			case 9:
			{
				cout << endl << "���㳡��������Ҫ����" << endl;
				cout << endl << _YELLOW "����������Ҫ "  _NORMAL << p.get_min_pao_num_needed() << _YELLOW " ��"  _NORMAL << endl << endl;
				break;
			}
			case 10:
			{
				cout << endl << "�޸ĳ�������" << endl << _YELLOW "�����볡��������>> "  _NORMAL;
				int n;
				cin >> n;
				p.change_n_yard(n);
				cout << endl << _YELLOW "�޸ĳɹ�"  _NORMAL << endl;
				cout << p << endl;
				break;
			}
			case 11:
			{
				cout << endl << "��ӡ�ڹ�" << endl << endl;
				cout << p << endl;
				break;
			}
			case 12:
			{
				cout << endl << "�����ڹ�" << endl << _YELLOW "�������ļ�·�����س�ȡ����0Ĭ��default.pa���� >> "  _NORMAL;
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
						cout << f_save << _YELLOW "����ɹ�"  _NORMAL << endl << endl;
					}
					else
						cout << _RED "����ʧ��"  _NORMAL << endl << endl;
				}
				else
					cout << _YELLOW "��ȡ��"  _NORMAL << endl << endl;

				break;
			}
			case 13:
			{
				cin.clear();
				cin.ignore();
				cout << endl << _RED "�Ƿ�ɾ��ԭ���ڹ첢�½���(y/n) >> "  _NORMAL;
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
					cout << _YELLOW "��ȡ��"  _NORMAL << endl << endl;;
				}
				break;
			}
			default:
				break;
			}
		}
	}
}