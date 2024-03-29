#pragma once
#include "System/IConnectInterface.h"
#include "Util/IExecute.h"

enum class Tier
{
	unrated,
	bronze,
	silver,
	gold,
	platinum,
	diamond
};

struct Baekjoon_CsvData
{
	std::wstring sequence;
	std::wstring number;
	std::wstring name;
	std::wstring tier;
	std::wstring algorithm;
	std::wstring is_try;

	void Push(std::wstring data);
	static int Size() { return 6; }

	int count = 0;
};

class BaekjoonGenerator : public IConnectInterface, public Singleton<BaekjoonGenerator>, public IExecute
{
	friend class Singleton<BaekjoonGenerator>;

public:
	BaekjoonGenerator();

	//IExecute
	virtual void Init() override;
	virtual void Execute() override;
	//~IExecute

private:
	int GetRandom(int min, int max);
	std::wstring GetRandomNumberFromCsvData(const std::vector<Baekjoon_CsvData>& in_datas);
	std::wstring GetRandomNumberFromCsvData_NoTry(const std::vector<Baekjoon_CsvData>& in_datas);

	void ReadCsv(const std::wstring& file_name);
	void WriteCsv(const std::wstring& file_name, std::wstring line);
	void FilterAsAlgorithm(const std::wstring& algorithm, const std::vector<Baekjoon_CsvData>& in_datas, std::vector<Baekjoon_CsvData>& out_datas);
	void FilterAsTier(const std::wstring& tier, const std::vector<Baekjoon_CsvData>& in_datas, std::vector<Baekjoon_CsvData>& out_datas);

private:
	virtual bool Open(std::string problem_number);
	
	template<typename T>
	BaekjoonGenerator* Input(T&& rhs)
	{
		std::cin >> std::forward<T>(rhs);
		return this;
	}

private:
	void GiveStartSelection();
	void ExecuteSelection(const int number);

private:
	void Selection_0();
	void Selection_1();
	void Selection_2();
	void Selection_3();
	void Selection_4();
	void Selection_5();
	void Selection_6();

private:
	//IConnectInterface
	virtual bool ConnectTo(std::string address) override;
	//~IConnectInterface

private:
	std::string base_address;
	std::vector<std::wstring> column_names;

	std::random_device rd;
	std::mt19937 gen;

	std::vector<Baekjoon_CsvData> datas;
};