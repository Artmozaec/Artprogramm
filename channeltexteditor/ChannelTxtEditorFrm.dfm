object ChannelText: TChannelText
  Left = 0
  Top = 0
  Width = 482
  Height = 849
  TabOrder = 0
  object currentDayLabel: TLabel
    Left = 40
    Top = 8
    Width = 140
    Height = 20
    Caption = #1044#1045#1053#1068' '#1053#1045#1044#1045#1051#1048' :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object currentTimeLabel: TLabel
    Left = 328
    Top = 8
    Width = 73
    Height = 20
    Caption = #1042#1056#1045#1052#1071' :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object channelTextEditor: TMemo
    Left = 40
    Top = 32
    Width = 409
    Height = 697
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    HideSelection = False
    Lines.Strings = (
      '')
    ParentFont = False
    PopupMenu = popupMenu
    ScrollBars = ssVertical
    TabOrder = 0
    OnChange = channelTextEditorChange
    OnClick = channelTextEditorClick
    OnContextPopup = channelTextEditorContextPopup
    OnKeyDown = channelTextEditorKeyDown
  end
  object popupMenu: TPopupMenu
    Left = 40
    Top = 728
    object MTextToFilmName: TMenuItem
      Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1092#1080#1083#1100#1084#1072
      OnClick = MTextToFilmNameClick
    end
    object MToDirector: TMenuItem
      Caption = #1056#1077#1078#1080#1089#1089#1105#1088
      OnClick = MToDirectorClick
    end
    object MToYear: TMenuItem
      Caption = #1043#1086#1076
      OnClick = MToYearClick
    end
  end
end
