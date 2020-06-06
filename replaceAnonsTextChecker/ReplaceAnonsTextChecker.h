#ifndef ReplaceAnonsTextCheckerH
#define ReplaceAnonsTextCheckerH
#include <vcl.h>
#include "SessionManager.h"

class ReplaceAnonsTextChecker{
public:
	ReplaceAnonsTextChecker(SessionManager *inSessionManager);
        bool checkText(TStringList *checkText, AnsiString channelName);
private:
	SessionManager *sessionManager;

};

#endif