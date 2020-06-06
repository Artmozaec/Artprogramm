#ifndef ImageFileFormatsH
#define ImageFileFormatsH
#include <vcl>

enum ImageFileFormats{
	TIF,
	JPG,
	PNG,
	GIF,
	PSD,
        BMP,
        ERROR_FORMAT
};


ImageFileFormats getFileFormat(AnsiString patch){
	AnsiString ext = ExtractFileExt(patch).LowerCase();
	//ShowMessage(ext);
        if (ext==".tif") return TIF;
        if (ext==".jpg") return JPG;
	if (ext==".jpeg") return JPG;
        if (ext==".png") return PNG;
        if (ext==".gif") return GIF;
        if (ext==".psd") return PSD;
        if (ext==".bmp") return BMP;
        return ERROR_FORMAT;
}
#endif