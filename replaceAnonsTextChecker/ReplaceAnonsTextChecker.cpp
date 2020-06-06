#include "ReplaceAnonsTextChecker.h"

ReplaceAnonsTextChecker::ReplaceAnonsTextChecker(SessionManager *inSessionManager){
	sessionManager = inSessionManager;
}

bool ReplaceAnonsTextChecker::checkText(TStringList *checkText, AnsiString channelName){
	int checkLinesSize=5;
        TStringList *oldText = sessionManager->getChannelTextPervisionSession(channelName);

	if (oldText == NULL) return true;

	for(int ch=0;
        ((ch<checkLinesSize) && (ch<checkText->Count) && (ch<oldText->Count));
        ch++
        ){
	        if (oldText->Strings[ch] != checkText->Strings[ch]) return true;

        }

        return false;
}
