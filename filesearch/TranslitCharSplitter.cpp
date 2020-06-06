#include "TranslitCharSplitter.h"

TranslitCharSplitter::TranslitCharSplitter(AnsiString *inString){
	length = inString->Length();
	contentPtr = inString->c_str();
	pointer = 0;
}

bool TranslitCharSplitter::nextChar(){
	pointer++;
	if (pointer>length){
		pointer--;
		return false;
	}
	return true;
}

TStringList *TranslitCharSplitter::getTranslitList(){
	TStringList *variation = new TStringList();
        char currentSymbol = contentPtr[pointer];
        char nextSymbol;
        if (pointer+1>length){
                nextSymbol = 0;
        } else {
                nextSymbol = contentPtr[pointer+1];
        }

	switch(currentSymbol){
		case '�':
			variation->Add(*new AnsiString("a"));
			break;
		case '�':
			variation->Add(*new AnsiString("b"));
			break;
		case '�':
			variation->Add(*new AnsiString("v"));
			break;
		case '�':
			variation->Add(*new AnsiString("g"));
			break;
		case '�':
			variation->Add(*new AnsiString("d"));
			break;
		case '�':
			variation->Add(*new AnsiString("e"));
                        variation->Add(*new AnsiString("io"));
			break;
		case '�':
			variation->Add(*new AnsiString("io"));
			variation->Add(*new AnsiString("yo"));
			variation->Add(*new AnsiString("e"));
			break;
		case '�':
			variation->Add(*new AnsiString("j"));
			variation->Add(*new AnsiString("z"));
                        variation->Add(*new AnsiString("g"));
			break;
		case '�':
			variation->Add(*new AnsiString("z"));
			break;
		case '�':
                        if (nextSymbol == '�'){
                                variation->Add(*new AnsiString("a"));
                                variation->Add(*new AnsiString("ya"));
                                variation->Add(*new AnsiString("ia"));
                                nextChar();
                        }
			variation->Add(*new AnsiString("i"));
                        variation->Add(*new AnsiString("y"));
			break;
		case '�':
			variation->Add(*new AnsiString("i"));
			variation->Add(*new AnsiString("y"));
			break;
		case '�':
			variation->Add(*new AnsiString("k"));
			break;
		case '�':
			variation->Add(*new AnsiString("l"));
			break;
		case '�':
			variation->Add(*new AnsiString("m"));
			break;
		case '�':
			variation->Add(*new AnsiString("n"));
			break;
		case '�':
			variation->Add(*new AnsiString("o"));
			break;
		case '�':
			variation->Add(*new AnsiString("p"));
			break;
		case '�':
			variation->Add(*new AnsiString("r"));
			break;
		case '�':
                        if (nextSymbol == '�'){
                                variation->Add(*new AnsiString("sh"));
                                nextChar();
                        }
			variation->Add(*new AnsiString("s"));
			break;
		case '�':
			variation->Add(*new AnsiString("t"));
			break;
		case '�':
			variation->Add(*new AnsiString("y"));
			variation->Add(*new AnsiString("u"));
			break;
		case '�':
			variation->Add(*new AnsiString("f"));
			break;
		case '�':
			variation->Add(*new AnsiString("x"));
			variation->Add(*new AnsiString("h"));
                        variation->Add(*new AnsiString("ch"));
			break;
		case '�':
			variation->Add(*new AnsiString("c"));
			break;
		case '�':
			variation->Add(*new AnsiString("ch"));
			break;
		case '�':
			variation->Add(*new AnsiString("sh"));
			break;
		case '�':
			variation->Add(*new AnsiString("sh"));
			break;
		case '�':
			break;
		case '�':
                        if (nextSymbol == '�'){
                                variation->Add(*new AnsiString("iy"));
                                variation->Add(*new AnsiString("yi"));
                                nextChar();
                        }
			variation->Add(*new AnsiString("y"));
			variation->Add(*new AnsiString("i"));
			break;
		case '�':
			break;
		case '�':
			variation->Add(*new AnsiString("e"));
			break;
		case '�':
			variation->Add(*new AnsiString("u"));
                        variation->Add(*new AnsiString("iy"));
			break;
		case '�':
			variation->Add(*new AnsiString("ya"));
			variation->Add(*new AnsiString("ia"));
                        variation->Add(*new AnsiString("a"));
			break;
		default:
			variation->Add(*new AnsiString(contentPtr[pointer]));
	}

	if (!nextChar()) return NULL;

	return variation;
}