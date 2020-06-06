object FilmEditor: TFilmEditor
  Left = 0
  Top = 0
  Width = 327
  Height = 760
  Color = clBtnFace
  ParentColor = False
  TabOrder = 0
  object NamesLabel: TLabel
    Left = 16
    Top = 8
    Width = 50
    Height = 13
    Caption = #1053#1072#1079#1074#1072#1085#1080#1103
  end
  object ActorsLabel: TLabel
    Left = 192
    Top = 8
    Width = 38
    Height = 13
    Caption = #1040#1082#1090#1077#1088#1099
  end
  object YearLabel: TLabel
    Left = 96
    Top = 128
    Width = 18
    Height = 13
    Caption = #1043#1086#1076
  end
  object DirectorsLabel: TLabel
    Left = 16
    Top = 128
    Width = 59
    Height = 13
    Caption = #1056#1077#1078#1080#1089#1089#1077#1088#1099
  end
  object fileImagesPanel: TPanel
    Left = 16
    Top = 464
    Width = 297
    Height = 257
    BorderStyle = bsSingle
    TabOrder = 8
    object assignExternalImageButton: TButton
      Left = 256
      Top = 8
      Width = 33
      Height = 25
      Caption = '...'
      TabOrder = 0
      OnClick = assignExternalImageButtonClick
    end
    inline imageViewerFrame: TImageViewerFrame
      Left = 3
      Top = 40
      Width = 290
      Height = 209
      TabOrder = 1
    end
    object imageFileBox: TComboBox
      Left = 48
      Top = 8
      Width = 201
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      OnChange = imageFileBoxChange
    end
    object renameImageFileButton: TButton
      Left = 0
      Top = 8
      Width = 41
      Height = 25
      Caption = 'R'
      TabOrder = 3
      OnClick = renameImageFileButtonClick
    end
  end
  object actors: TListBox
    Left = 184
    Top = 24
    Width = 129
    Height = 217
    ItemHeight = 13
    ParentShowHint = False
    PopupMenu = listEditPopup
    ShowHint = True
    TabOrder = 0
    OnDblClick = fieldDblClick
  end
  object year: TEdit
    Left = 120
    Top = 120
    Width = 49
    Height = 21
    TabOrder = 1
    OnChange = change
  end
  object directors: TListBox
    Left = 16
    Top = 144
    Width = 153
    Height = 97
    ItemHeight = 13
    ParentShowHint = False
    PopupMenu = listEditPopup
    ShowHint = True
    TabOrder = 2
    OnClick = fieldToClboard
    OnDblClick = fieldDblClick
    OnKeyDown = KeyDownListBox
    OnMouseMove = listHint
  end
  object saveChangeButton: TButton
    Left = 16
    Top = 728
    Width = 81
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 3
    OnClick = saveChangeButtonClick
  end
  object filmNames: TListBox
    Left = 16
    Top = 24
    Width = 153
    Height = 89
    ItemHeight = 13
    ParentShowHint = False
    PopupMenu = listEditPopup
    ShowHint = True
    TabOrder = 4
    OnClick = fieldToClboard
    OnContextPopup = ListPopUpMenuCreator
    OnDblClick = fieldDblClick
    OnKeyDown = KeyDownListBox
    OnMouseMove = listHint
  end
  object filmText: TMemo
    Left = 16
    Top = 248
    Width = 297
    Height = 129
    Lines.Strings = (
      '')
    TabOrder = 5
  end
  object fileSearchButton: TButton
    Left = 104
    Top = 728
    Width = 97
    Height = 25
    Caption = #1092#1072#1081#1083#1086#1074#1099#1081' '#1087#1086#1080#1089#1082
    TabOrder = 6
    OnClick = fileSearchButtonClick
  end
  object dayAndChannelPanel: TPanel
    Left = 16
    Top = 384
    Width = 297
    Height = 73
    BorderStyle = bsSingle
    TabOrder = 7
    object TimeLabel: TLabel
      Left = 80
      Top = 8
      Width = 51
      Height = 24
      Caption = '00:00'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object weekDayBox: TComboBox
      Left = 144
      Top = 8
      Width = 141
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      OnChange = changeWeekDayBox
      Items.Strings = (
        #1053#1045'_'#1044#1045#1053#1068'_'#1053#1045#1044#1045#1051#1048
        #1087#1086#1085#1077#1076#1077#1083#1100#1085#1080#1082
        #1074#1090#1086#1088#1085#1080#1082
        #1089#1088#1077#1076#1072
        #1095#1077#1090#1074#1077#1088#1075
        #1087#1103#1090#1085#1080#1094#1072
        #1089#1091#1073#1073#1086#1090#1072
        #1074#1086#1089#1082#1088#1077#1089#1077#1085#1100#1077)
    end
    object channelBox: TComboBox
      Left = 144
      Top = 40
      Width = 141
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      OnChange = change
      OnEnter = channelBoxClick
    end
    object filmTypeBox: TComboBox
      Left = 8
      Top = 40
      Width = 129
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      OnChange = change
      Items.Strings = (
        #1061#1091#1076#1086#1078#1077#1089#1090#1074#1077#1085#1085#1099#1081
        #1057#1077#1088#1080#1072#1083
        #1052#1091#1083#1100#1090#1092#1080#1083#1100#1084
        #1053#1091#1072#1095#1085#1086#1087#1086#1091#1083#1103#1088#1085#1099#1081)
    end
  end
  object listEditPopup: TPopupMenu
    Left = 208
    Top = 720
    object MChangeToBased: TMenuItem
      Caption = #1054#1089#1085#1086#1074#1085#1086#1081
      OnClick = MChangeToBasedClick
    end
    object MDelete: TMenuItem
      Caption = #1059#1076#1072#1083#1080#1090#1100
      OnClick = MDeleteClick
    end
    object MPasteInBuffer: TMenuItem
      Caption = #1042#1089#1090#1072#1074#1080#1090#1100
      OnClick = MPasteInBufferClick
    end
  end
end
