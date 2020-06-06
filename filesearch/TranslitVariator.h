#ifndef TranslitVariatorH
#define TranslitVariatorH
#include <vcl.h>
#include "TranslitCharSplitter.h"

class TranslitVariator{
public:
	TranslitVariator(AnsiString *inString);
	
	TStringList *getVariationList();
private:
	//Конвертор русских букв в латинницу
	TranslitCharSplitter *charSplitter;
	
	TStringList *variations;
	
	void addVariatonChars(TStringList *);
	
};
#endif