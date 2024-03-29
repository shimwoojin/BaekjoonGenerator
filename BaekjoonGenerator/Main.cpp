#include "stdafx.h"
#include "Program.h"
#include "Baekjoon/BaekjoonGenerator.h"

int main()
{
	Program program;

	program.AddExecute((IExecute*)BaekjoonGenerator::Get());

	program.Init();
	program.Start();

	return 0;
}
