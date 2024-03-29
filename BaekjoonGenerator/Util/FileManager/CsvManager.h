#pragma once
#include "stdafx.h"
#include "FileManager.h"

template<typename FileName>
class CsvManager : public FileManager<FileName>
{
public:
	CsvManager(FileName file_name);

	virtual void Read(std::vector<std::vector<std::wstring>>& datas) override;
	virtual void Write(std::wstring line) override;
	void Modify(std::wstring after, int low, int column);
};

template<typename FileName>
inline CsvManager<FileName>::CsvManager(FileName file_name)
	: FileManager<FileName>(file_name)
{
}

template<typename FileName>
inline void CsvManager<FileName>::Write(std::wstring line)
{
	using namespace std;

	std::locale::global(std::locale(".UTF-8"));

	wofstream output_stream;
	
	output_stream.open(this->file_name, ios::out | ios::app);

	if (output_stream.is_open())
	{
		output_stream << endl;
		output_stream << line;
	}

	output_stream.close();
	std::locale::global(std::locale(""));
}

template<typename FileName>
inline void CsvManager<FileName>::Modify(std::wstring after, int low, int column)
{
	using namespace std;

	std::locale::global(std::locale(".UTF-8"));

	wfstream w_fs;
	wstring buffer;

	w_fs.open(this->file_name, ios::in | ios::out);

	if (w_fs.is_open())
	{
		while (low--)
		{
			getline(w_fs, buffer);
		}

		while (column--)
		{
			getline(w_fs, buffer, L',');
		}

		auto pos = w_fs.tellp();
		w_fs.seekp(pos);

		w_fs << after;
	}

	w_fs.close();

	std::locale::global(std::locale(""));
}

template<typename FileName>
inline void CsvManager<FileName>::Read(std::vector<std::vector<std::wstring>>& datas)
{
	using namespace std;

	std::locale::global(std::locale(".UTF-8"));

	wifstream input_stream;
	wstring line, column;

	input_stream.open(this->file_name, ios::in);

	int count = 0;
	if (input_stream.is_open())
	{
		while (!input_stream.eof())
		{
			getline(input_stream, line);
			wstringstream wss(line);
			std::vector<std::wstring> line_data;

			while (getline(wss, column, L','))
			{
				line_data.push_back(column);
			}

			if (count != 0 && !line_data.empty())
			{
				datas.push_back(line_data);
			}
			++count;
		}
	}

	input_stream.close();
	std::locale::global(std::locale(""));
}