object StringEditor: TStringEditor
  Left = 442
  Top = 381
  Width = 491
  Height = 252
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1089#1090#1088#1086#1082#1080
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object editMemo: TMemo
    Left = 16
    Top = 16
    Width = 457
    Height = 145
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnKeyPress = editMemoKeyPress
  end
  object saveButton: TButton
    Left = 16
    Top = 168
    Width = 97
    Height = 33
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 1
    OnClick = saveButtonClick
  end
end
