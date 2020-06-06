object FilmsInWeekDaysFrame: TFilmsInWeekDaysFrame
  Left = 0
  Top = 0
  Width = 232
  Height = 209
  TabOrder = 0
  object weekDaysList: TListBox
    Left = 8
    Top = 8
    Width = 161
    Height = 193
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 26
    Items.Strings = (
      #1055#1086#1085#1077#1076#1077#1083#1100#1085#1080#1082
      #1042#1090#1086#1088#1085#1080#1082
      #1057#1088#1077#1076#1072
      #1063#1077#1090#1074#1077#1088#1075
      #1055#1103#1090#1085#1080#1094#1072
      #1057#1091#1073#1073#1086#1090#1072
      #1042#1086#1089#1082#1088#1077#1089#1077#1085#1100#1077)
    ParentFont = False
    TabOrder = 0
    OnDblClick = weekDaysListDblClick
  end
  object filmsDaySum: TListBox
    Left = 184
    Top = 8
    Width = 33
    Height = 193
    ExtendedSelect = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -23
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 26
    Items.Strings = (
      '0'
      '0'
      '0'
      '0'
      '0'
      '0'
      '0')
    ParentFont = False
    TabOrder = 1
    OnClick = selectReset
  end
end
