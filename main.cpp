#include <iostream>
#include <array>
#include <vector>
#include <random>
#include <Windows.h>
#include <algorithm>
#include <locale.h>

using namespace std;

class Game {
public:
	Game() : m_errors{ 0 }, m_deleted_from_temp_word{ 0 }, m_words{ "�����", "��������", "���������" } {}
	void play() {
		cout << "����� ���������� � ���� \"��������\"!\n";
		m_word = get_random_word();
		m_temp_word = m_word;
		bool right{ false };
		do {
			print_hiden_word(right);
			char letter{ set_letter() };
			int result = is_found(letter);
			if (result == 1)
				right = true;
			else if (result == 0) {
				right = false;
			}
			else {
				right = false;
				m_errors++;
				if (m_errors < 6)
					cout << "�������! ����� ����� ���, � ��� �������� " << 6 - m_errors << " ������� ������� ������� �����!\n";
			}
		} while (m_word.size() != m_found_positions.size() && m_errors != 6);
		if (m_errors == 6) {
			cout << "�� ���������!\n";
			cout << "���������� �����: " << m_word << "\n";
			play_again();
		}
		else {
			cout << "�� ��������!\n";
			cout << "���������� �����: " << m_word << '\n';
			play_again();
		}
	}

private:
	int m_errors, m_deleted_from_temp_word; //���������� ��� �������� ���������� ������ m_errors //�-�� ��������� �������� �� ���������� �����
	array <string, 3> m_words; //��� ����
	vector <int> m_found_positions; //������ �������� ������ ����
	string m_word, m_temp_word; //��������
	string get_random_word() {
		mt19937 mercene_vortex(random_device{}()); //��������� ��������� �����
		return m_words.at(mercene_vortex() % (m_words.size()));
	}
	
	void print_hiden_word(bool right)
	{
		if (m_found_positions.size() == 0 || !right)
			cout << "����� - ";
		else
			cout << "����� - ";
		for (int i = 0; i < m_word.size(); i++)
		{
			auto iter = find(m_found_positions.begin(), m_found_positions.end(), i);
			if (iter != m_found_positions.end())
				cout << m_word.at(*iter);
			else
				cout << "_";
		}
		cout << "\n";
	}
	char set_letter()
	{
		char choise;
		do
		{
			cout << "�������� �����: ";
			cin >> choise;
			cin.clear();
			cin.ignore(32767, '\n');
		} while (choise<-32 && choise>-1);
		return choise;
	}
	//���� ����� ������� = 1, ���� �� ������� = -1, ���� �� ��������, �� �� ������������� = 0
	int is_found(char letter)
	{
		auto iter_word = find(m_word.begin(), m_word.end(), letter);
		if (iter_word == m_word.end())
		{
			return -1;
		}
		else
		{
			int pos = static_cast <int> (iter_word - m_word.begin());
			auto iter_pos = find(m_found_positions.begin(), m_found_positions.end(), pos);
			if (iter_pos == m_found_positions.end())
			{
				m_found_positions.push_back(pos);
				m_temp_word.erase(find(m_temp_word.begin(), m_temp_word.end(), m_word.at(pos)));
				m_deleted_from_temp_word++;
				return 1;
			}
			else
			{
				auto iter = find(m_temp_word.begin(), m_temp_word.end(), m_word.at(pos));
				if (iter != m_temp_word.end())
				{
					int p = static_cast <int>(iter - m_temp_word.begin());
					m_found_positions.push_back(p + m_deleted_from_temp_word);
					m_temp_word.erase(m_temp_word.begin() + p);
					m_deleted_from_temp_word++;
					return 1;
				}
				else
					return 0;
			}
		}
	}
	void play_again()
	{
		char choise;
		do
		{
			cout << "������ ������� ���? (�/�): ";
			cin >> choise;
			cin.clear();
			cin.ignore(32767, '\n');
		} while (choise != '�' && choise != '�');
		if (choise == '�')
		{
			m_errors = 0;
			m_deleted_from_temp_word = 0;
			m_found_positions.erase(m_found_positions.begin(), m_found_positions.end());
			play();
		}
		else
			exit(0);
	}
};
int main()
{
	SetConsoleCP(CP_UTF8); 
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, "russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Game().play();
	return 0;
}