//---------------------------------------------------------------------------

#include <vcl.h>
#include <SysUtils.hpp>
#pragma hdrstop

#include "ImageViewer.h"
#include "GraphicEx\GraphicEx.hpp"
#include "ImageFileFormats.cpp"
#include "jpeg.hpp"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TImageViewerFrame *ImageViewerFrame;
//---------------------------------------------------------------------------
__fastcall TImageViewerFrame::TImageViewerFrame(TComponent* Owner)
        : TFrame(Owner)
{
        clear();
}
//---------------------------------------------------------------------------

void TImageViewerFrame::clear(){
        image->Picture = NULL;
}


void  TImageViewerFrame::showImage(AnsiString patch){
        //Если там была ошибка - вытираем её
        messageLabel->Caption ="";

        //Если файла нет, рисуем заставку - ошибку
        if (!FileExists(patch)){
                drawError(NOT_EXIST);
                return;
        }


        ImageFileFormats format = getFileFormat(patch);
        try{
                switch(format){
                case TIF:{
                        TTIFFGraphic *bitmap = new TTIFFGraphic();
                        bitmap->LoadFromFile(patch);
                        changeProportionalImageSize(bitmap->Height, bitmap->Width);
                        alignImageToCenter();
                        image->Picture->Assign(bitmap);
                        return;
                }
                case JPG:{
                        TJPEGImage *bitmap = new TJPEGImage();
                        bitmap->LoadFromFile(patch);
                        changeProportionalImageSize(bitmap->Height, bitmap->Width);
                        alignImageToCenter();
                        image->Picture->Assign(bitmap);
                        return;
                }
                case PNG:{
                        TPNGGraphic *bitmap = new TPNGGraphic();
                        bitmap->LoadFromFile(patch);
                        changeProportionalImageSize(bitmap->Height, bitmap->Width);
                        alignImageToCenter();
                        image->Picture->Assign(bitmap);
                        return;
                }
/*                case GIF:{
                        ShowMessage("GIF бля");
                        TGIFGraphic *bitmap = new TGIFGraphic();
                        bitmap->LoadFromFile(*patch);
                        changeProportionalImageSize(bitmap->Height, bitmap->Width);
                        alignImageToCenter();
                        image->Picture->Assign(bitmap);
                        return;
                }
                case PSD:{
                        ShowMessage("PSD бля");
                        return;
                }
                case BMP:{
                        ShowMessage("BMP бля");
                        return;
                }*/
                case ERROR_FORMAT:{
                        drawError(FORMAT_ERROR);
                        return;
                }
                }
        }catch(EInvalidGraphic&){
                //ShowMessage("Формат не поддерживается");
                drawError(FORMAT_ERROR);
        }

}


void TImageViewerFrame::changeProportionalImageSize(int bitmapHeight, int bitmapWidth){

        if (bitmapHeight>=bitmapWidth){
                image->Height = imagePanel->Height-IMAGE_BORDER;
                image->Width = (float)bitmapWidth/((float)bitmapHeight/(float)image->Height);
        } else {
                image->Width = imagePanel->Width-IMAGE_BORDER;
                image->Height =(float)bitmapHeight/((float)bitmapWidth/(float)image->Width);
        }
}

void TImageViewerFrame::alignImageToCenter(){
        image->Left = (imagePanel->Width-image->Width)/2;
        image->Top = (imagePanel->Height-image->Height)/2;
}



void TImageViewerFrame::drawError(ViewerErrors errorCode){
        image->Picture = NULL;

        switch(errorCode){
                case FORMAT_ERROR:{
                        messageLabel->Caption = "ОШИБКА - НЕВЕРНЫЙ ФОРМАТ";
                        return;
                }
                case NOT_EXIST:{
                        messageLabel->Caption = "ОШИБКА - ФАЙЛА НЕТ";
                        return;
                }
        }

}
