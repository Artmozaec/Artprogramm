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
		case 'à':
			variation->Add(*new AnsiString("a"));
			break;
		case 'á':
			variation->Add(*new AnsiString("b"));
			break;
		case 'â':
			variation->Add(*new AnsiString("v"));
			break;
		case 'ã':
			variation->Add(*new AnsiString("g"));
			break;
		case 'ä':
			variation->Add(*new AnsiString("d"));
			break;
		case 'å':
			variation->Add(*new AnsiString("e"));
                        variation->Add(*new AnsiString("io"));
			break;
		case '¸':
			variation->Add(*new AnsiString("io"));
			variation->Add(*new AnsiString("yo"));
			variation->Add(*new AnsiString("e"));
			break;
		case 'æ':
			variation->Add(*new AnsiString("j"));
			variation->Add(*new AnsiString("z"));
                        variation->Add(*new AnsiString("g"));
			break;
		case 'ç':
			variation->Add(*new AnsiString("z"));
			break;
		case 'è':
                        if (nextSymbol == 'ÿ'){
                                variation->Add(*new AnsiString("a"));
                                variation->Add(*new AnsiString("ya"));
                                variation->Add(*new AnsiString("ia"));
                                nextChar();
                        }
			variation->Add(*new AnsiString("i"));
                        variation->Add(*new AnsiString("y"));
			break;
		case 'é':
			variation->Add(*new AnsiString("i"));
			variation->Add(*new AnsiString("y"));
			break;
		case 'ê':
			variation->Add(*new AnsiString("k"));
			break;
		case 'ë':
			variation->Add(*new AnsiString("l"));
			break;
		case 'ì':
			variation->Add(*new AnsiString("m"));
			break;
		case 'í':
			variation->Add(*new AnsiString("n"));
			break;
		case 'î':
			variation->Add(*new AnsiString("o"));
			break;
		case 'ï':
			variation->Add(*new AnsiString("p"));
			break;
		case 'ð':
			variation->Add(*new AnsiString("r"));
			break;
		case 'ñ':
                        if (nextSymbol == 'ø'){
                                variation->Add(*new AnsiString("sh"));
                                nextChar();
                        }
			variation->Add(*new AnsiString("s"));
			break;
		case 'ò':
			variation->Add(*new AnsiString("t"));
			break;
		case 'ó':
			variation->Add(*new AnsiString("y"));
			variation->Add(*new AnsiString("u"));
			break;
		case 'ô':
			variation->Add(*new AnsiString("f"));
			break;
		case 'õ':
			variation->Add(*new AnsiString("x"));
			variation->Add(*new AnsiString("h"));
                        variation->Add(*new AnsiString("ch"));
			break;
		case 'ö':
			variation->Add(*new AnsiString("c"));
			break;
		case '÷':
			variation->Add(*new AnsiString("ch"));
			break;
		case 'ø':
			variation->Add(*new AnsiString("sh"));
			break;
		case 'ù':
			variation->Add(*new AnsiString("sh"));
			break;
		case 'ü':
			break;
		case 'û':
                        if (nextSymbol == 'é'){
                                variation->Add(*new AnsiString("iy"));
                                variation->Add(*new AnsiString("yi"));
                                nextChar();
                        }
			variation->Add(*new AnsiString("y"));
			variation->Add(*new AnsiString("i"));
			break;
		case 'ú':
			break;
		case 'ý':
			variation->Add(*new AnsiString("e"));
			break;
		case 'þ':
			variation->Add(*new AnsiString("u"));
                        variation->Add(*new AnsiString("iy"));
			break;
		case 'ÿ':
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