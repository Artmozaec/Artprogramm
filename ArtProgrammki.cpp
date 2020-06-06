//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("ArtProgrammFrm.cpp", ArtProgramm);
USEFORM("anonstree\AnonsTree.cpp", AnonsTree); /* TFrame: File Type */
USEFORM("channeltexteditor\ChannelTxtEditorFrm.cpp", ChannelText); /* TFrame: File Type */
USEFORM("filmeditor\FilmEditorFrm.cpp", FilmEditor); /* TFrame: File Type */
USEFORM("filesearch\FileSearchFrm.cpp", FileSearch);
USEFORM("ImageViewer\ImageViewer.cpp", ImageViewerFrame); /* TFrame: File Type */
USEFORM("imageselectorform\ImageSelectorFrm.cpp", ImageSelector);
USEFORM("filmeditor\stringeditor\StringEditorFrm.cpp", StringEditor);
USEFORM("historyform\HistoryForm.cpp", HistorySelector);
USEFORM("settingseditor\SettingsEditorFrm.cpp", SettingsEditor);
USEFORM("filmsinweekdays\FilmsInWeekDaysFrm.cpp", FilmsInWeekDaysFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TArtProgramm), &ArtProgramm);
		Application->CreateForm(__classid(TStringEditor), &StringEditor);
		Application->CreateForm(__classid(THistorySelector), &HistorySelector);
		Application->CreateForm(__classid(TSettingsEditor), &SettingsEditor);
		Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
