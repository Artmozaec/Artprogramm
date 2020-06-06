object FileSearch: TFileSearch
  Left = 535
  Top = 162
  Width = 315
  Height = 755
  Caption = 'FileSearch'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object queryTextField: TEdit
    Left = 8
    Top = 8
    Width = 289
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    PopupMenu = pastePopUp
    TabOrder = 0
    OnKeyPress = queryTextFieldKeyPress
  end
  object searchButton: TButton
    Left = 24
    Top = 40
    Width = 73
    Height = 17
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 1
    OnClick = searchButtonClick
  end
  object resultListBox: TListBox
    Left = 8
    Top = 64
    Width = 289
    Height = 425
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 20
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = resultListBoxClick
    OnDblClick = resultListBoxDblClick
    OnMouseMove = resultListBoxMouseMove
  end
  inline imageViewerFrame: TImageViewerFrame
    Left = 8
    Top = 496
    Width = 290
    Height = 209
    TabOrder = 3
  end
  object backResultButton: TButton
    Left = 104
    Top = 40
    Width = 75
    Height = 17
    Caption = #1053#1072#1079#1072#1076
    TabOrder = 4
    OnClick = backResultButtonClick
  end
  object searchInResultButton: TButton
    Left = 184
    Top = 40
    Width = 89
    Height = 17
    Caption = #1042' '#1085#1072#1081#1076#1077#1085#1085#1086#1084
    TabOrder = 5
    OnClick = searchInResultButtonClick
  end
  object pastePopUp: TPopupMenu
    Left = 216
    Top = 680
  end
end
