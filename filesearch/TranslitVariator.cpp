#include "TranslitVariator.h"


TranslitVariator::TranslitVariator(AnsiString *inString){
	charSplitter = new TranslitCharSplitter(inString);
	variations = new TStringList();

	TStringList *charVar = new TStringList();
	do{
                //�������� �������� ������� �������
		charVar = charSplitter->getTranslitList();

                //��������� �� ���������� �� ������
                if (charVar == NULL) break;

                //��������� �� � ����������
                addVariatonChars(charVar);

	}while(true);
}

void TranslitVariator::addVariatonChars(TStringList *charVar){
        if (charVar->Count ==0 ) return;
        TStringList *newVariations = new TStringList();

        //���� ��� ������ ���������� ������ Variations = 0
        if (variations->Count == 0){
                variations = charVar;
                return;
        }


        //������ ���������� ���� ��������� �������� ����� �� �������� charVar
        for (int variationsCh=0; variationsCh<variations->Count; variationsCh++){
                for (int charVarCh=0; charVarCh<charVar->Count; charVarCh++){
                        //ShowMessage(variations->Strings[variationsCh]+charVar->Strings[charVarCh]);

                        newVariations->Add(variations->Strings[variationsCh]+
                                           charVar->Strings[charVarCh]
                        );
                }
        }

      variations = newVariations;
}


TStringList *TranslitVariator::getVariationList(){
	return variations;
}