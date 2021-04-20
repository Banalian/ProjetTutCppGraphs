#pragma once
class Carc
{
private:
	int iDestination;
public:

	Carc(int iDest);
	~Carc();

	void ARCModifDest(int iNewDest);
	int ARCgetDest();
};

