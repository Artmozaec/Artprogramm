object ImageViewerFrame: TImageViewerFrame
  Left = 0
  Top = 0
  Width = 290
  Height = 209
  TabOrder = 0
  object imagePanel: TPanel
    Left = 0
    Top = 0
    Width = 289
    Height = 209
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 0
    object image: TImage
      Left = 8
      Top = 8
      Width = 273
      Height = 193
      Stretch = True
    end
    object messageLabel: TLabel
      Left = 42
      Top = 80
      Width = 5
      Height = 24
      Alignment = taCenter
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
  end
end
