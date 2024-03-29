#pragma once

class IExecute;

class Program
{
public:
	Program();

	void Init();
	void Start();

	void AddExecute(IExecute* execute);

private:
	std::vector<IExecute*> executables;
};