object HistorySelector: THistorySelector
  Left = 450
  Top = 256
  Width = 334
  Height = 473
  Caption = 'HistorySelector'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object sessionsBox: TListBox
    Left = 24
    Top = 16
    Width = 273
    Height = 393
    ItemHeight = 13
    TabOrder = 0
    OnDblClick = sessionsBoxDblClick
  end
end
