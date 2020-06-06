//---------------------------------------------------------------------------

#ifndef FileSearchFrmH
#define FileSearchFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "FilmEditorFrm.h"
#include "ImageViewer.h"
#include <Menus.hpp>
#include "ImageManager.h"

//---------------------------------------------------------------------------
class TFilmEditor;
class TFileSearch : public TForm
{
__published:	// IDE-managed Components
        TEdit *queryTextField;
        TButton *searchButton;
        TListBox *resultListBox;
        TPopupMenu *pastePopUp;
        TImageViewerFrame *imageViewerFrame;
        TButton *backResultButton;
        TButton *searchInResultButton;
        void __fastcall searchButtonClick(TObject *Sender);
        void __fastcall resultListBoxClick(TObject *Sender);
        void __fastcall assignButtonClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall resultListBoxMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall queryTextFieldKeyPress(TObject *Sender, char &Key);
        void __fastcall resultListBoxDblClick(TObject *Sender);
        void __fastcall backResultButtonClick(TObject *Sender);
        void __fastcall searchInResultButtonClick(TObject *Sender);
public:		// User declarations
        __fastcall TFileSearch(TComponent* Owner);

        void changeFilmEditor(TFilmEditor *inFilmEditor);

        void changeImageManager(ImageManager *inImageManager);

        void setPopUpStrings(TStringList *popUpList);

        void introduce(AnsiString searchString);

private:	// User declarations

        //Предыдущий результат
       TStringList *pervisionResult;
        //Форма куда будет возвращён результат
       TFilmEditor *filmEditor;

       ImageManager *imageManager;

       void __fastcall myPopUpItemClick(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TFileSearch *FileSearch;
//---------------------------------------------------------------------------
#endif
