#ifndef CharClassificatorH
#define CharClassificatorH
#include "CharClasses.cpp"
#include "CharClassificator.h"

class CharClassificator{
public:
	CharClassificator();
	CharClass classificateCurrentChar(char symbol);
private:
	const static CharClass symbolTable[];

};
#endif