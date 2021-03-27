object Equator_Helical_Graphics_Check_form: TEquator_Helical_Graphics_Check_form
  Left = 0
  Top = 0
  AutoSize = True
  BorderWidth = 10
  Caption = 
    'Fixed Probe 3-Axis Helical Gear Measurement Feasibility         ' +
    '                 '
  ClientHeight = 706
  ClientWidth = 1013
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000077770000000000000000000007000000000000000000000000
    0000000000000000700000000000000000000000000000007777788000000000
    0000000000000000000007700000000000000000000000000007700000000000
    0000700000000000007777777000000000000000077700000088877777000000
    0000000088888000078888888000000000000007777FF0000000077800000000
    00000008888FFF00000000000000000000700008888FFF000000000000000000
    00000008FFFFFF0000008877000000000000000888FFFF0000FFF88888700000
    00000008888FFF0007778FFF0000000000000007777FF0000000777700000000
    7700000088888000000000000000000007000000077700000000000000000000
    0000000000000000000700000000000000000000000000088FFFF77700000000
    0000000000000000007888FFF7000000007700000000000000000F0000000000
    0007000000000000000000000000000000000008000000000000000000000000
    00000087000700087770000000000000000008880007700078FF770000000000
    0000000800777000788800000000000000000000000887777000000000000000
    000000000000000000000000000000000000000000000000000000000000FFFF
    FFFFFFF81FFFFFF000FFFF00001FFE00001FFE00001FFF00001FFF000007F800
    0003F0000003F0000007F800000FFC00000FFC000003F0000001E0000001E000
    000FE000000FF000000FF8000007F8000007F0000003F0000003F000003FFE00
    003FFE00003FFE00003FFF00003FFFE000FFFFFE07FFFFFFFFFFFFFFFFFF}
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox2: TGroupBox
    Left = 485
    Top = 0
    Width = 528
    Height = 184
    Caption = 'Trace Details'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label10: TLabel
      Left = 9
      Top = 50
      Width = 79
      Height = 13
      Hint = 'The Axial position of the Gear From The Table'
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Gear Position (Z)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowAccelChar = False
      ShowHint = True
    end
    object Label1: TLabel
      Left = 9
      Top = 74
      Width = 120
      Height = 13
      Hint = 'The Initial Rotational Position '
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Gear Tooth 1 Angle (deg)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowAccelChar = False
      ShowHint = True
    end
    object Label5: TLabel
      Left = 9
      Top = 98
      Width = 136
      Height = 13
      Hint = 'Which Tooth to Measure'
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Individual Tooth To Measure'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowAccelChar = False
      ShowHint = True
    end
    object Labelteethn: TLabel
      Left = 345
      Top = 98
      Width = 42
      Height = 13
      Caption = 'ZZZ       '
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
    object Label4: TLabel
      Left = 9
      Top = 122
      Width = 115
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Approach and Recess   '
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowAccelChar = False
      ShowHint = False
    end
    object ComboBoxFlankcut: TComboBox
      Left = 9
      Top = 20
      Width = 120
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      ParentFont = False
      TabOrder = 1
      Text = '1 Trace/Flank'#9#9
      Items.Strings = (
        '1 Trace/Flank'#9#9
        '3 Traces/Flank'#9)
    end
    object gearzposedit: TEdit
      Left = 157
      Top = 47
      Width = 65
      Height = 21
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      MaxLength = 12
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      Text = '0.000'
      OnChange = gearzposeditChange
      OnEnter = gearzposeditEnter
      OnExit = gearzposeditExit
    end
    object ComboBoxwidthdensity: TComboBox
      Left = 157
      Top = 20
      Width = 120
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 1
      ParentFont = False
      TabOrder = 2
      Text = 'Density - Coarse'
      Items.Strings = (
        'Density - Very Coarse'
        'Density - Coarse'
        'Density - Normal'
        'Density - Fine')
    end
    object gearthetaedit: TEdit
      Left = 157
      Top = 71
      Width = 65
      Height = 21
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      MaxLength = 12
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      Text = '0.000'
      OnChange = gearthetaeditChange
      OnEnter = gearthetaeditEnter
      OnExit = gearthetaeditExit
    end
    object CheckBoxunits: TCheckBox
      Left = 389
      Top = 20
      Width = 112
      Height = 22
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Use English Units'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnMouseUp = CheckBoxunitsMouseUp
    end
    object ComboBoxtoothtomeasure: TComboBox
      Left = 157
      Top = 95
      Width = 64
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      Items.Strings = (
        '1'
        '2'
        '3'
        '4')
    end
    object Buttonupdate: TButton
      Left = 8
      Top = 150
      Width = 175
      Height = 25
      Caption = 'Update Probe Path'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      OnClick = ButtonupdateClick
    end
    object CheckBox4teeth: TCheckBox
      Left = 227
      Top = 96
      Width = 112
      Height = 17
      Hint = 'Show the milling tool in the plot'
      Caption = '4 Teeth at 90 deg'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 7
    end
    object Button2: TButton
      Left = 219
      Top = 150
      Width = 175
      Height = 25
      Caption = 'Detect Clash and Update '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 8
      OnClick = Button2Click
    end
    object RadioGroupangulardatum: TRadioGroup
      Left = 234
      Top = 44
      Width = 273
      Height = 48
      Caption = 'Middle of Tooth Angular Datum on Width'
      Columns = 3
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 1
      Items.Strings = (
        'Bottom'
        'Middle'
        'Top')
      ParentFont = False
      TabOrder = 9
    end
    object approachdistedit: TEdit
      Left = 157
      Top = 119
      Width = 65
      Height = 21
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      MaxLength = 12
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 10
      Text = '0.300'
      OnChange = approachdisteditChange
      OnEnter = approachdisteditEnter
      OnExit = approachdisteditExit
    end
  end
  object RadioGroupfinish: TRadioGroup
    Left = 2
    Top = 0
    Width = 480
    Height = 83
    Caption = 'Process'
    Columns = 3
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 2
    Items.Strings = (
      'Profile'
      'Lead'
      'Profile and Lead')
    ParentFont = False
    TabOrder = 1
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 89
    Width = 482
    Height = 73
    Caption = 'Star Probe Data'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object Label8: TLabel
      Left = 12
      Top = 17
      Width = 69
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Stem Diameter'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowAccelChar = False
      ShowHint = False
    end
    object Label6: TLabel
      Left = 12
      Top = 42
      Width = 62
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Ball Diameter'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowAccelChar = False
      ShowHint = False
    end
    object Label7: TLabel
      Left = 180
      Top = 17
      Width = 63
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Stem Length '
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowAccelChar = False
      ShowHint = False
    end
    object Label9: TLabel
      Left = 180
      Top = 42
      Width = 55
      Height = 13
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Total Span '
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowAccelChar = False
      ShowHint = False
    end
    object stemdiaedit: TEdit
      Left = 96
      Top = 13
      Width = 65
      Height = 21
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      MaxLength = 12
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      Text = '0.300'
      OnChange = stemdiaeditChange
      OnEnter = stemdiaeditEnter
      OnExit = stemdiaeditExit
    end
    object stemlengthedit: TEdit
      Left = 252
      Top = 13
      Width = 65
      Height = 21
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      MaxLength = 12
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      Text = '7.00'
      OnChange = stemlengtheditChange
      OnEnter = stemlengtheditEnter
      OnExit = stemlengtheditExit
    end
    object balldiaedit: TEdit
      Left = 96
      Top = 38
      Width = 65
      Height = 21
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      MaxLength = 12
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      Text = '0.500'
      OnChange = balldiaeditChange
      OnEnter = balldiaeditEnter
      OnExit = balldiaeditExit
    end
    object totalspanedit: TEdit
      Left = 252
      Top = 38
      Width = 65
      Height = 21
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      MaxLength = 12
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      Text = '20.00'
      OnChange = totalspaneditChange
      OnEnter = totalspaneditEnter
      OnExit = totalspaneditExit
    end
    object ComboBoxprobe: TComboBox
      Left = 327
      Top = 14
      Width = 140
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      ParentFont = False
      TabOrder = 4
      Text = 'User Defined'
      OnSelect = ComboBoxprobeSelect
      Items.Strings = (
        'User Defined'
        '0.50   0.36   2.50   10.00'
        '0.50   0.30   7.00   20.00'
        '1.00   0.70   2.50   10.00'
        '1.00   0.70   7.50   20.00')
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 166
    Width = 482
    Height = 540
    Hint = #169' Dontyne Systems Ltd'
    BorderWidth = 5
    Caption = 'p'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    object Labelrotx: TLabel
      Left = 12
      Top = 26
      Width = 20
      Height = 13
      Hint = 'Click to set to zero'
      Caption = '+ X '
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnMouseUp = LabelrotxMouseUp
    end
    object Labelroty: TLabel
      Left = 12
      Top = 49
      Width = 20
      Height = 13
      Hint = 'Click to set to zero'
      Caption = '+ Y '
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnMouseUp = LabelrotyMouseUp
    end
    object Labelrotz: TLabel
      Left = 12
      Top = 72
      Width = 17
      Height = 13
      Hint = 'Click to set to zero'
      Caption = '+ Z'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnMouseUp = LabelrotzMouseUp
    end
    object Labelzoom: TLabel
      Left = 11
      Top = 95
      Width = 27
      Height = 13
      Hint = 'Click to reset'
      Caption = 'Zoom'
      ParentShowHint = False
      ShowHint = True
      OnMouseUp = LabelzoomMouseUp
    end
    object Label2: TLabel
      Left = 12
      Top = 5
      Width = 32
      Height = 13
      Caption = 'Rotate'
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
    object Labelunits: TLabel
      Left = 6
      Top = 509
      Width = 211
      Height = 13
      Hint = 'Outside diameter'
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'All length units in mm unless stated otherwise'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowAccelChar = False
      ShowHint = True
    end
    object Labelcopyright: TLabel
      Left = 238
      Top = 509
      Width = 139
      Height = 13
      Hint = 'Gear Machine Centre Software '#169' Dontyne Systems Ltd 2016'
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = #169' Dontyne Systems Ltd 2021'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowAccelChar = False
      ShowHint = True
    end
    object resetButton: TBitBtn
      Left = 10
      Top = 143
      Width = 45
      Height = 31
      Hint = 'Reset the zoom, rotate and pan etc'
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Reset'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnClick = resetButtonClick
    end
    object Panel3Dcolor: TPanel
      Left = 10
      Top = 215
      Width = 43
      Height = 163
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      BorderWidth = 3
      TabOrder = 1
      object Label3: TLabel
        Left = 8
        Top = 78
        Width = 24
        Height = 13
        Hint = 'Use sliders to adjust display color'
        Margins.Left = 2
        Margins.Top = 2
        Margins.Right = 2
        Margins.Bottom = 2
        Caption = 'Color'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowAccelChar = False
        ShowHint = True
      end
      object TrackBarGreen: TTrackBar
        Left = 16
        Top = 4
        Width = 10
        Height = 70
        Hint = 'Green'
        Margins.Left = 2
        Margins.Top = 2
        Margins.Right = 2
        Margins.Bottom = 2
        Max = 20
        Orientation = trVertical
        ParentShowHint = False
        Position = 7
        ShowHint = True
        TabOrder = 0
        ThumbLength = 10
        TickStyle = tsNone
        OnChange = TrackBarBlueChange
      end
      object TrackBarRed: TTrackBar
        Left = 4
        Top = 4
        Width = 10
        Height = 70
        Hint = 'Red'
        Margins.Left = 2
        Margins.Top = 2
        Margins.Right = 2
        Margins.Bottom = 2
        Max = 20
        Orientation = trVertical
        ParentShowHint = False
        Position = 7
        ShowHint = True
        TabOrder = 1
        ThumbLength = 10
        TickStyle = tsNone
        OnChange = TrackBarBlueChange
      end
      object TrackBarBlue: TTrackBar
        Left = 28
        Top = 4
        Width = 10
        Height = 70
        Hint = 'Blue'
        Margins.Left = 2
        Margins.Top = 2
        Margins.Right = 2
        Margins.Bottom = 2
        Max = 20
        Orientation = trVertical
        ParentShowHint = False
        Position = 7
        ShowHint = True
        TabOrder = 2
        ThumbLength = 10
        TickStyle = tsNone
        OnChange = TrackBarBlueChange
      end
      object RadioButtonprt: TRadioButton
        Left = 5
        Top = 96
        Width = 33
        Height = 25
        Hint = 'part color'
        Caption = 'prt'
        Checked = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        TabStop = True
      end
      object RadioButtonbk: TRadioButton
        Left = 5
        Top = 127
        Width = 33
        Height = 25
        Hint = 'background color'
        Caption = 'bk'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
      end
    end
    object TrackBarX: TTrackBar
      Left = 50
      Top = 26
      Width = 200
      Height = 23
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      BorderWidth = 1
      Max = 72
      Min = -72
      TabOrder = 2
      ThumbLength = 15
      TickStyle = tsNone
      OnChange = TrackBarBlueChange
    end
    object TrackBarY: TTrackBar
      Left = 50
      Top = 49
      Width = 200
      Height = 23
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      BorderWidth = 1
      Max = 72
      Min = -72
      Position = -18
      TabOrder = 3
      ThumbLength = 15
      TickStyle = tsNone
      OnChange = TrackBarBlueChange
    end
    object TrackBarZ: TTrackBar
      Left = 50
      Top = 72
      Width = 200
      Height = 23
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      BorderWidth = 1
      Max = 72
      Min = -72
      TabOrder = 4
      ThumbLength = 15
      TickStyle = tsNone
      OnChange = TrackBarBlueChange
    end
    object TrackBarZoom: TTrackBar
      Left = 50
      Top = 95
      Width = 200
      Height = 23
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      BorderWidth = 1
      Max = 350
      Min = 5
      Position = 70
      TabOrder = 5
      ThumbLength = 15
      TickStyle = tsNone
      OnChange = TrackBarBlueChange
    end
    object Memo1: TMemo
      Left = 64
      Top = 142
      Width = 409
      Height = 346
      Lines.Strings = (
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        ''
        '')
      ScrollBars = ssBoth
      TabOrder = 6
      OnExit = Memo1Exit
    end
    object Button4: TButton
      Left = 10
      Top = 179
      Width = 45
      Height = 31
      Hint = 'Update the plot'
      Caption = 'Update'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
      OnClick = Button4Click
    end
    object ComboBoxline: TComboBox
      Left = 63
      Top = 115
      Width = 410
      Height = 21
      Style = csDropDownList
      DropDownCount = 20
      ItemIndex = 0
      TabOrder = 8
      OnChange = ComboBoxlineChange
      Items.Strings = (
        '')
    end
    object CheckBoxshowstylus: TCheckBox
      Left = 255
      Top = 12
      Width = 97
      Height = 17
      Hint = 'Show the milling tool in the plot'
      Caption = 'Show Stylus'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 9
      OnMouseUp = CheckBoxshowstylusMouseUp
    end
    object Buttonright: TButton
      Left = 32
      Top = 114
      Width = 23
      Height = 23
      Hint = 'Move forward a line'
      Caption = '>'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 10
      OnMouseUp = ButtonrightMouseUp
    end
    object Buttonleft: TButton
      Left = 9
      Top = 114
      Width = 23
      Height = 23
      Hint = 'Move back a line'
      Caption = '<'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 11
      OnClick = ButtonleftClick
    end
    object fontbutton2: TButton
      Left = 9
      Top = 382
      Width = 23
      Height = 23
      Hint = 'Decrease report font size'
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = '-'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 12
      OnMouseUp = fontbutton2MouseUp
    end
    object fontbutton1: TButton
      Left = 32
      Top = 382
      Width = 23
      Height = 23
      Hint = 'increase report font size'
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = '+'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 13
      OnMouseUp = fontbutton1MouseUp
    end
    object CheckBoxshowtable: TCheckBox
      Left = 255
      Top = 35
      Width = 97
      Height = 17
      Hint = 'Show the milling tool in the plot'
      Caption = 'Show Table'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 14
      OnMouseUp = CheckBoxshowstylusMouseUp
    end
    object CheckBoxnormals: TCheckBox
      Left = 255
      Top = 83
      Width = 112
      Height = 22
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Show Normals (i,j,k)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 15
      OnMouseUp = CheckBoxunitsMouseUp
    end
    object CheckBoxshowsides: TCheckBox
      Left = 255
      Top = 57
      Width = 112
      Height = 22
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Show Gear Sides'
      Checked = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 16
      OnMouseUp = CheckBoxunitsMouseUp
    end
    object CheckBoxbtransparent: TCheckBox
      Left = 373
      Top = 12
      Width = 104
      Height = 17
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = 'Transparent Gear'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 17
      Visible = False
      OnMouseUp = CheckBoxbtransparentMouseUp
    end
  end
  object OpenGLAPPanel: TPanel
    Left = 485
    Top = 189
    Width = 528
    Height = 514
    Caption = 'Click to Refresh Image'
    Color = clWhite
    ParentBackground = False
    TabOrder = 4
    OnClick = OpenGLAPPanelClick
    OnMouseDown = OpenGLAPPanelMouseDown
    OnMouseMove = OpenGLAPPanelMouseMove
    OnMouseUp = OpenGLAPPanelMouseUp
  end
  object SaveDialog2: TSaveDialog
    DefaultExt = '*.txt'
    Filter = 'Text|*.txt|EIA|*.EIA'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 414
    Top = 65526
  end
  object MainMenu1: TMainMenu
    Left = 170
  end
end
