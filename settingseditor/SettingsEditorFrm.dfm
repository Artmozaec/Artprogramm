object SettingsEditor: TSettingsEditor
  Left = 326
  Top = 236
  Width = 537
  Height = 350
  Caption = 'SettingsEditor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object workFolderPatchLabel: TLabel
    Left = 32
    Top = 32
    Width = 104
    Height = 13
    Caption = #1056#1072#1073#1086#1095#1072#1103' '#1076#1080#1088#1077#1082#1090#1086#1088#1080#1103
  end
  object baseImagePatchLabel: TLabel
    Left = 32
    Top = 72
    Width = 195
    Height = 13
    Caption = #1055#1091#1090#1100' '#1082' '#1076#1080#1088#1077#1082#1090#1086#1088#1080#1080' '#1073#1072#1079#1099' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1081
  end
  object anonsTextPatchLabel: TLabel
    Left = 32
    Top = 112
    Width = 150
    Height = 13
    Caption = #1044#1080#1088#1077#1082#1090#1086#1088#1080#1103' '#1090#1077#1082#1089#1090#1086#1074' '#1072#1085#1086#1085#1089#1086#1074
  end
  object shareFolderPatchLabel: TLabel
    Left = 32
    Top = 152
    Width = 156
    Height = 13
    Caption = #1042#1099'x'#1086#1076#1085#1072#1103' '#1076#1080#1088#1077#1082#1090#1086#1088#1080#1103' '#1074#1077#1088#1089#1090#1082#1080
  end
  object sessionBasePatchLabel: TLabel
    Left = 32
    Top = 192
    Width = 130
    Height = 13
    Caption = #1044#1080#1088#1077#1082#1090#1086#1088#1080#1103' '#1073#1072#1079#1099' '#1089#1077#1089#1089#1080#1081
  end
  object workFolderPatchEdit: TEdit
    Left = 32
    Top = 48
    Width = 385
    Height = 21
    TabOrder = 0
    Text = 'workFolderPatchEdit'
  end
  object baseImagePatchEdit: TEdit
    Left = 32
    Top = 88
    Width = 385
    Height = 21
    TabOrder = 1
    Text = 'baseImagePatchEdit'
  end
  object anonsTextPatchEdit: TEdit
    Left = 32
    Top = 128
    Width = 385
    Height = 21
    TabOrder = 2
    Text = 'anonsTextPatchEdit'
  end
  object shareFolderPatchEdit: TEdit
    Left = 32
    Top = 168
    Width = 385
    Height = 21
    TabOrder = 3
    Text = 'shareFolderPatchEdit'
  end
  object sessionFolderPatchEdit: TEdit
    Left = 32
    Top = 208
    Width = 385
    Height = 21
    TabOrder = 4
    Text = 'sessionFolderPatchEdit'
  end
  object saveButton: TButton
    Left = 312
    Top = 248
    Width = 113
    Height = 25
    Caption = #1057#1054#1061#1056#1040#1053#1048#1058#1068
    TabOrder = 5
    OnClick = saveButtonClick
  end
  object workFolderPatchButton: TButton
    Left = 432
    Top = 48
    Width = 33
    Height = 25
    Caption = '...'
    TabOrder = 6
    OnClick = workFolderPatchButtonClick
  end
  object baseImagePatchButton: TButton
    Left = 432
    Top = 88
    Width = 33
    Height = 25
    Caption = '...'
    TabOrder = 7
    OnClick = baseImagePatchButtonClick
  end
  object anonsTextPatchButton: TButton
    Left = 432
    Top = 128
    Width = 33
    Height = 25
    Caption = '...'
    TabOrder = 8
    OnClick = anonsTextPatchButtonClick
  end
  object shareFolderPatchButton: TButton
    Left = 432
    Top = 168
    Width = 33
    Height = 25
    Caption = '...'
    TabOrder = 9
    OnClick = shareFolderPatchButtonClick
  end
  object sessionFolderPatchButton: TButton
    Left = 432
    Top = 208
    Width = 33
    Height = 25
    Caption = '...'
    TabOrder = 10
    OnClick = sessionFolderPatchButtonClick
  end
end
