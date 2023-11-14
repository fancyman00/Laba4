
#include <iostream>
#include <functional>
#include <Windows.h>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::function;
using std::ifstream;

int main_menu();
int sub_menu();
template<typename T, typename Predicat>
void read_and_check(T& x, Predicat condition, const char* message);
int check_file(std::ifstream& file);
void print_message(int n);
int is_arithmetic(int n, function<void(int&)> get_element);
int sum(int n, function<bool(int, int)> condition, int& s,  function<void(int&)> get_element, int digit);
void check_sum(int ind, int& s);
void check_arfm(int ind);


int main()
{
	SetConsoleOutputCP(1251);
	short choice;
	do
	{
		choice = main_menu();
		if (choice != 4)
		{
			int s = 0, n = 0, ind = 0;
			double aver = 0;
			function<bool(int, int)> check_first_digit = [](int x, int digit) {
				while (x >= 10)
					x /= 10;
				return x == digit;
			};
			switch (choice)
			{
				case 1:
				{
					ifstream file("datamain.txt");
					function<void(int&)> get_element = [&file](int& x) {
						file >> x;
					};
					switch (check_file(file))
					{
					case -1:
						cout << "������! ���� �� ����������!" << endl;
						break;
					case 0:
						cout << "������! ���� ����." << endl;
						break;
					default:
						file >> n; 
						choice = sub_menu();
						if (choice == 1) 
						{
							ind = is_arithmetic(n, get_element);
							check_arfm(ind);
						}
						else 
						{
							int digit = 0;
							read_and_check(
								digit,
								[](int x) -> bool { return x >= 0 && x < 10; },
								"������� �����: "
							);
							ind = sum(n, check_first_digit, s, get_element, digit);
							check_sum(ind, s);
						}
						file.close();
					}
					break;
				}
				case 2: 
				{
					choice = sub_menu();

					read_and_check(n, [](int x) {return x > 0; }, "������� ���������� ��������� ������������������ | n (n>0) = ");
					function<void(int&)> get_element = [](int& x) {
						istream& stream = cin;
						stream >> x;
					};
					if (choice == 1) 
					{
						print_message(n);
						ind = is_arithmetic(n, get_element);
						check_arfm(ind);
					}
					else
					{
						int digit = 0;
						read_and_check(
							digit,
							[](int x) -> bool { return x >= 0 && x < 10; },
							"������� �����: "
						);
						print_message(n);
						ind = sum(n, check_first_digit, s, get_element, digit);
						check_sum(ind, s);
					}
					break;
				}
				case 3: // random
				{
					choice = sub_menu();
					read_and_check(n, [](int x) {return x > 0; }, "������� ���������� ��������� ������������������ n (n>0) = ");
					int a = 0, b = 0;
					do
					{
						cout << "������� ������ ������� ������������������ = ";
						cin >> a;
						cout << "������� ������� ������� ������������������ = ";
						cin >> b;
						if (a >= b)
							cout << "������! ������� ������� ������ ���� ������, ��� ������!" << endl;
					} while (a >= b);
					function<void(int&)> get_element = [a, b](int& x) {
						x = rand() % (b - a) + a;
						cout << x << " ";
					};
					if (choice == 1) 
					{
						cout << "��������������� ������������������: ";
						ind = is_arithmetic(n, get_element);
						cout << endl;
						check_arfm(ind);
					}
					else 
					{
						int digit = 0;
						read_and_check(
							digit,
							[](int x) -> bool { return x >= 0 && x < 10; },
							"������� �����: "
						);
						cout << "��������������� ������������������: ";
						ind = sum(n, check_first_digit, s, get_element, digit);
						check_sum(ind, s);
					}
					break;
				}
			}
			cout << "��������� ������? (Y(y) - ���������/����� ������ ������� - ���������� ������): ";
			char isExit;
			cin >> isExit;
			if (isExit == 'Y' || isExit == 'y')
				choice = 4;
		}
	} while (choice != 4);
	return 0;
}

int main_menu()
{
	cout << "���� ���������." << endl;
	cout << "1. ���� ������������������ �� �����." << endl;
	cout << "2. ���� ������������������ � ����������." << endl;
	cout << "3. ������������� ������������������ ��������� �������." << endl;
	cout << "4. ������� ���������." << endl;
	function<bool(int)> Lambda = [](int x) {return x >= 1 && x <= 4; };
	int choice{};
	read_and_check(choice, Lambda, "->");
	return choice;
}

int sub_menu()
{
	cout << "����� ������ ������?" << endl;
	cout << "1. ���������, ��� ������������������ �������� �������������� �����������." << endl;
	cout << "2. ����� ����� ���������, ������������ �� �������� �����." << endl;
	function<bool(int)> Lambda = [](int x) {return x >= 1 && x <= 2; };
	int choice{};
	read_and_check(choice, Lambda, "->");
	return choice;
}

template<typename T, typename Predicat>
void read_and_check(T& x, Predicat condition, const char* message)
{
	cout << message;
	while (!(cin >> x && condition(x)))
	{
		cout << "������ �����!" << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << message;
	}
}

int check_file(std::ifstream& file)
{
	int result = 1;
	if (!file)
		result = -1;
	else
		if (file.peek() == EOF)
			result = 0;

	return result;
}

void print_message(int n)
{
	cout << "������� " << n << " �������";
	if (n % 100 >= 11 && n % 100 <= 14)
		cout << "��" << endl;
	else
	{
		switch (n % 10)
		{
		case 1:
			cout << endl;
			break;
		case 2:
		case 3:
		case 4:
			cout << "�" << endl;
			break;
		default:
			cout << "��" << endl;
		}
	}
}

int is_arithmetic(int n, function<void(int&)> get_element)
{
	int result = 1, cnttwo = 0, x = 0, prev = 0, dif = 0;
	for (int i = 1; i <= n; ++i)
	{
		get_element(x);
		if (i > 2) {
			result = (dif != x - prev) ? 0 : 1;
		}
		dif = x - prev;
		prev = x;
	}
	return result;
}

int sum(int n, function<bool(int, int)> check_first_digit, int& s, function<void(int&)> get_element, int digit)
{
	int result = 1, x = 0;
	for (int i = 1; i <= n; ++i)
	{
		get_element(x);
		if (check_first_digit(x, digit))s += x;
	}
	cout << endl;
	if (s == 0) result = -1;
	return result;
}

//int sum(int n, int a, int b, function<bool(int, int)> check_first_digit, int& s)
//{
//	int result = 1, x = 0, cnt = 0, digit = 0;
//	bool flag = false;
//	read_and_check(
//		digit,
//		[](int x) -> bool { return x >= 0 && x < 10; },
//		"������� �����: "
//	);
//	cout << "��������������� ������������������:" << endl;
//	for (int i = 1; i <= n; ++i)
//	{
//		x = rand() % (b - a) + a;
//		cout << x << ' ';
//
//		if (check_first_digit(x, digit))
//			s += x;
//	}
//	cout << endl;
//	if (s == 0) result = -1;
//	return result;
//}

void check_sum(int ind, int& s)
{
	if (ind == 1)
		cout << "����� ��������� ������������ �� �������� ����� = " << s << endl;
	else
		cout << "� ������������������ ��� ��������� ������������ �� �������� �����." << endl;
}

void check_arfm(int ind)
{
	cout << "������������������ ";
	if (ind == 0) cout << "�� ";
	cout << "�������� �������������� �����������." << endl;
}
