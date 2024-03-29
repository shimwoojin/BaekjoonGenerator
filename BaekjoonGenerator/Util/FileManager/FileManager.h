#pragma once
#include "stdafx.h"

template<typename FileName>
class FileManager
{
public:
	FileManager(FileName file_name);
	virtual ~FileManager() {}

	virtual void Read(std::vector<std::vector<std::wstring>>& datas) = 0;
	virtual void Write(std::wstring line) = 0;

	void SetFileName(FileName file_name) { this->file_name = file_name; }
	FileName GetFileName() { return file_name; }

protected:
	FileName file_name;
};

template<typename FileName>
inline FileManager<FileName>::FileManager(FileName file_name)
{
	this->file_name = file_name;
}