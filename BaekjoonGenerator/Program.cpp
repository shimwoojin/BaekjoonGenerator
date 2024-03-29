#include "stdafx.h"
#include "Program.h"
#include "Util/IExecute.h"
#include "Baekjoon/BaekjoonGenerator.h"

Program::Program()
{
	
}

void Program::Init()
{
	for (IExecute* exe : executables)
	{
		exe->Init();
	}
}

void Program::Start()
{
	while (true)
	{
		for (IExecute* exe : executables)
		{
			exe->Execute();
		}
	}
}

void Program::AddExecute(IExecute* execute)
{
	executables.push_back(execute);
}
