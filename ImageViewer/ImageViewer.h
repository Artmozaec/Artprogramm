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

        //�������� ����������
        void clear();
        __fastcall TImageViewerFrame(TComponent* Owner);

private:	// User declarations
        //������������ ������ image ����� �������,
        //���-�� ����� ���� ��������� bitmap, ��������� �� ����������
        void changeProportionalImageSize(int bitmapHeigth, int bitmapWidth);

        //������������� image � ������ ������
        void alignImageToCenter();

        //������ ������ �� ��������
        void drawError(ViewerErrors errorCode);

        int static const IMAGE_BORDER = 10;

};
//---------------------------------------------------------------------------
extern PACKAGE TImageViewerFrame *ImageViewerFrame;
//---------------------------------------------------------------------------
#endif
