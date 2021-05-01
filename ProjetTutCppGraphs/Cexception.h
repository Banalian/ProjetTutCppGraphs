#pragma once

#define ErrNewMallocFailed 100
class Cexception
{
private:
	int iEXCCode;

public:

	Cexception();
	Cexception(int iCode);
	~Cexception();

	int EXCLire_Code();
	void EXCModifier_Code(int iCode);
};

