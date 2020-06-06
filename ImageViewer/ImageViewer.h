//---------------------------------------------------------------------------


#ifndef ImageViewerH
#define ImageViewerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "ViewerErrors.cpp"

//---------------------------------------------------------------------------
class TImageViewerFrame : public TFrame
{
__published:	// IDE-managed Components
        TPanel *imagePanel;
        TImage *image;
        TLabel *messageLabel;
public:		// User declarations
        void showImage(AnsiString patch);

        //Очистить содержимое
        void clear();
        __fastcall TImageViewerFrame(TComponent* Owner);

private:	// User declarations
        //Подстраивает размер image таким образом,
        //что-бы когда туда поместили bitmap, пропорции не нарушились
        void changeProportionalImageSize(int bitmapHeigth, int bitmapWidth);

        //Устанавливает image в центер панели
        void alignImageToCenter();

        //Рисует ошибку на картинке
        void drawError(ViewerErrors errorCode);

        int static const IMAGE_BORDER = 10;

};
//---------------------------------------------------------------------------
extern PACKAGE TImageViewerFrame *ImageViewerFrame;
//---------------------------------------------------------------------------
#endif
