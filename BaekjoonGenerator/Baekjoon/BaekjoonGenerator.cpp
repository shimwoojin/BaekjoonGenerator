#include "stdafx.h"
#include "BaekjoonGenerator.h"
#include "Util/FileManager/CsvManager.h"

void Baekjoon_CsvData::Push(std::wstring data)
{
	if (count == 0)
	{
		sequence = data;
	}
	else if (count == 1)
	{
		number = data;
	}
	else if (count == 2)
	{
		name = data;
	}
	else if (count == 3)
	{
		tier = data;
	}
	else if (count == 4)
	{
		algorithm = data;
	}
	else if (count == 5)
	{
		is_try = data;
	}

	++count;
}

BaekjoonGenerator::BaekjoonGenerator()
{
	base_address = "acmicpc.net/problem/";
	column_names = { L"순서", L"번호", L"이름", L"티어", L"알고리즘", L"풀이 여부" };
	gen.seed(rd());
}

void BaekjoonGenerator::Init()
{
}

void BaekjoonGenerator::Execute()
{
	GiveStartSelection();
}

int BaekjoonGenerator::GetRandom(int min, int max)
{
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

std::wstring BaekjoonGenerator::GetRandomNumberFromCsvData(const std::vector<Baekjoon_CsvData>& in_datas)
{
	assert(in_datas.size() > 0);

	const int min = 1;
	const int max = (int)in_datas.size() - 1;

	int random = GetRandom(min, max);

	return in_datas[random].number;
}

std::wstring BaekjoonGenerator::GetRandomNumberFromCsvData_NoTry(const std::vector<Baekjoon_CsvData>& in_datas)
{
	std::vector<Baekjoon_CsvData> temp;
	temp.reserve(in_datas.size());

	for (const Baekjoon_CsvData& data : in_datas)
	{
		if (data.is_try == L"X" || data.is_try == L"x" || data.is_try == L"No" || data.is_try == L"no")
		{
			temp.push_back(data);
		}
	}

	if (temp.empty())
	{
		return L"";
	}

	const int min = 0;
	const int max = (int)temp.size() - 1;

	int random = GetRandom(min, max);

	return temp[random].number;
}

void BaekjoonGenerator::ReadCsv(const std::wstring& file_name)
{
	using namespace std;

	CsvManager<wstring> csv_manager(file_name);

	vector<vector<wstring>> csv_datas;
	csv_manager.Read(csv_datas);

	datas.clear();

	for (int i = 0; i < csv_datas.size(); i++)
	{
		Baekjoon_CsvData data;
		for (int j = 0; j < csv_datas[i].size(); j++)
		{
			data.Push(csv_datas[i][j]);
		}
		datas.push_back(data);
	}
}

void BaekjoonGenerator::WriteCsv(const std::wstring& file_name, std::wstring line)
{
	using namespace std;

	CsvManager<wstring> csv_manager(file_name);

	csv_manager.Write(line);
}

void BaekjoonGenerator::FilterAsAlgorithm(const std::wstring& algorithm, const std::vector<Baekjoon_CsvData>& in_datas, std::vector<Baekjoon_CsvData>& out_datas)
{
	out_datas.reserve(datas.size());
	for (const auto& data : in_datas)
	{
		if (data.algorithm == algorithm)
		{
			out_datas.push_back(data);
		}
	}
	out_datas.shrink_to_fit();
}

void BaekjoonGenerator::FilterAsTier(const std::wstring& tier, const std::vector<Baekjoon_CsvData>& in_datas, std::vector<Baekjoon_CsvData>& out_datas)
{
	out_datas.reserve(datas.size());
	for (const auto& data : in_datas)
	{
		if (data.tier == tier)
		{
			out_datas.push_back(data);
		}
	}
	out_datas.shrink_to_fit();
}

bool BaekjoonGenerator::Open(std::string problem_number)
{
	std::string address = base_address + problem_number;
	return ConnectTo(address);
}

void BaekjoonGenerator::GiveStartSelection()
{
	using namespace std;
	Screen::Clear();
	int select;

	cout << "환영합니다. 백준 문제 풀이를 도와주는 프로그램입니다." << "\n\n";

	cout << "1 : 문제 번호를 입력하여 직접 연결" << '\n';
	cout << "2 : 랜덤 문제 부여" << '\n';
	cout << "3 : 난이도 + 알고리즘 선택" << '\n';
	cout << "4 : 문제 목록" << '\n';
	cout << "5 : 문제 추가" << '\n';
	cout << "6 : 문제 해결 마킹" << "\n\n";
	
	cout << "0 : 프로그램 종료" << "\n\n";

	cin >> select;
	ExecuteSelection(select);
}

void BaekjoonGenerator::ExecuteSelection(const int number)
{
	Screen::Clear();

	switch (number)
	{
	case 0 : 
		Selection_0();
		break;
	case 1:
		Selection_1();
		break;
	case 2:
		Selection_2();
		break;
	case 3:
		Selection_3();
		break;
	case 4:
		Selection_4();
		break;
	case 5:
		Selection_5();
		break;
	case 6:
		Selection_6();
		break;
	default: 
		break;
	}
}

//0 : 프로그램 종료
void BaekjoonGenerator::Selection_0()
{
	exit(0);
}

//1 : 문제 번호를 입력하여 직접 연결
void BaekjoonGenerator::Selection_1()
{
	using namespace std;

	cout << "문제 번호를 입력하세요 : ";

	string number;
	Input(number)->Open(number);
}

//2 : 랜덤 문제 부여
void BaekjoonGenerator::Selection_2()
{
	using namespace std;

	ReadCsv(L"Baekjoon.csv");

	wstring random = GetRandomNumberFromCsvData_NoTry(datas);
	string address(random.begin(), random.end());
	Open(address);
}

//3 : 난이도 + 알고리즘 선택
void BaekjoonGenerator::Selection_3()
{
	using namespace std;

	ReadCsv(L"Baekjoon.csv");

	wstring w_tier;
	wstring w_algorithm;
	std::vector<Baekjoon_CsvData> data_filter_algorithm;
	std::vector<Baekjoon_CsvData> data_filter_tier;
	wcin.ignore();

	{
		cout << "알고리즘을 선택해주세요 : " << endl;
		cout << "ex. 입력 : DP" << endl;

		getline(wcin, w_algorithm);

		if (!w_algorithm.empty())
		{
			FilterAsAlgorithm(w_algorithm, datas, data_filter_algorithm);
		}
		else
		{
			data_filter_algorithm = move(datas);
		}
	}

	{
		cout << "티어를 선택해주세요 : " << endl;
		cout << "ex. 입력 : 골드5" << endl;

		getline(wcin, w_tier);

		if (!w_tier.empty())
		{
			FilterAsTier(w_tier, data_filter_algorithm, data_filter_tier);
		}
		else
		{
			data_filter_tier = move(data_filter_algorithm);
		}
	}

	wstring number = GetRandomNumberFromCsvData_NoTry(data_filter_tier);
	string address(number.begin(), number.end());
	Open(address);
}

//4 : 문제 목록
void BaekjoonGenerator::Selection_4()
{
	using namespace std;

	ReadCsv(L"Baekjoon.csv");

	for (const Baekjoon_CsvData& data : datas)
	{
		wcout.setf(ios::left);
		wcout << setw(12) << data.sequence;
		wcout << setw(12) << data.number;
		wcout << setw(12) << data.name;
		wcout << setw(12) << data.tier;
		wcout << setw(12) << data.algorithm;
		wcout << setw(12) << data.is_try;

		wcout << endl;
	}

	system("pause");
}

//5 : 문제 추가
void BaekjoonGenerator::Selection_5()
{
	using namespace std;

	ReadCsv(L"Baekjoon.csv");

	wcout << L"문제를 추가합니다. 입력 규칙을 맞춰주세요." << endl;
	wcout << L"순서, 번호, 이름, 티어, 알고리즘, 풀이 여부" << endl;

	int sequence = 1;
	if (!datas.empty())
	{
		sequence = stoi(datas.back().sequence) + 1;
	}

	wstring line;
	wstring temp = to_wstring(sequence);

	line += temp;
	line += L',';

	wcin.ignore();
	for (int i = 1; i < column_names.size() - 1; i++)
	{
		wcout << column_names[i] << L"를 입력해주세요." << endl;
		getline(wcin, temp, L'\n');
		line += temp;
		line += L',';
	}

	line += L'X';

	WriteCsv(L"Baekjoon.csv", line);
}

void BaekjoonGenerator::Selection_6()
{
	using namespace std;

	ReadCsv(L"Baekjoon.csv");

	CsvManager<wstring> csv_manager(L"Baekjoon.csv");

	int number;

	cout << "풀이한 문제의 번호를 입력해주세요 : ";
	cin >> number;

	wstring w_number = to_wstring(number);

	for (int i = 0; i < datas.size(); i++)
	{
		if (datas[i].number == w_number)
		{
			int column_istry = Baekjoon_CsvData::Size() - 1;
			csv_manager.Modify(L"O", i + 1, column_istry);
		}
	}
}

bool BaekjoonGenerator::ConnectTo(std::string address)
{
	return ConnectSystem::Get()->ConnectTo(address);
}
