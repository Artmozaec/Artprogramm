object ImageSelector: TImageSelector
  Left = 257
  Top = 167
  Width = 579
  Height = 283
  Caption = 'ImageSelector'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object imageFilesBox: TListBox
    Left = 16
    Top = 16
    Width = 241
    Height = 209
    ItemHeight = 13
    TabOrder = 0
    OnClick = imageFilesBoxClick
    OnDblClick = imageFilesBoxDblClick
  end
  inline imageViewerFrame: TImageViewerFrame
    Left = 270
    Top = 16
    Width = 290
    Height = 209
    TabOrder = 1
  end
end
