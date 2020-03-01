VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{0D452EE1-E08F-101A-852E-02608C4D0BB4}#2.0#0"; "FM20.DLL"
Begin VB.Form masterclient 
   BackColor       =   &H00404040&
   Caption         =   "oko t : T vj"
   ClientHeight    =   8130
   ClientLeft      =   60
   ClientTop       =   630
   ClientWidth     =   13350
   LinkTopic       =   "Form1"
   ScaleHeight     =   542
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   890
   Begin VB.Timer autotimer 
      Interval        =   100
      Left            =   480
      Top             =   4920
   End
   Begin VB.PictureBox membar 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   1
      Left            =   4410
      Picture         =   "masterclient.frx":0000
      ScaleHeight     =   285
      ScaleWidth      =   1725
      TabIndex        =   71
      Top             =   7425
      Width           =   1725
   End
   Begin VB.PictureBox membar 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   285
      Index           =   0
      Left            =   2610
      Picture         =   "masterclient.frx":1E01
      ScaleHeight     =   285
      ScaleWidth      =   1725
      TabIndex        =   70
      Top             =   7425
      Width           =   1725
   End
   Begin VB.Timer getinfo 
      Enabled         =   0   'False
      Interval        =   360
      Left            =   480
      Top             =   5400
   End
   Begin VB.PictureBox thecolor 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   7020
      ScaleHeight     =   345
      ScaleWidth      =   405
      TabIndex        =   49
      Top             =   7305
      Width           =   435
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   990
      Top             =   6825
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.PictureBox textobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   870
      Left            =   2610
      Picture         =   "masterclient.frx":3C02
      ScaleHeight     =   870
      ScaleWidth      =   5535
      TabIndex        =   43
      Top             =   4065
      Width           =   5535
      Begin VB.ListBox fontz 
         Appearance      =   0  'Flat
         BackColor       =   &H00404040&
         Height          =   615
         ItemData        =   "masterclient.frx":65DE
         Left            =   105
         List            =   "masterclient.frx":65E0
         TabIndex        =   48
         Top             =   120
         Width           =   1455
      End
      Begin VB.TextBox textedit 
         Appearance      =   0  'Flat
         BackColor       =   &H00404040&
         ForeColor       =   &H00000000&
         Height          =   615
         Left            =   1800
         TabIndex        =   44
         Text            =   "Text1"
         Top             =   135
         Width           =   3030
      End
      Begin VB.Label texttype 
         BackStyle       =   0  'Transparent
         Caption         =   "2D"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   225
         Left            =   5025
         TabIndex        =   45
         Top             =   570
         Width           =   270
      End
      Begin VB.Image sendtext 
         Height          =   510
         Left            =   4875
         Picture         =   "masterclient.frx":65E2
         Top             =   90
         Width           =   570
      End
   End
   Begin VB.PictureBox meshobject 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   3105
      Left            =   2565
      Picture         =   "masterclient.frx":7E6C
      ScaleHeight     =   3105
      ScaleWidth      =   5655
      TabIndex        =   32
      Top             =   4080
      Visible         =   0   'False
      Width           =   5655
      Begin VB.PictureBox fontsizet 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   1050
         Left            =   4230
         Picture         =   "masterclient.frx":13794
         ScaleHeight     =   1050
         ScaleWidth      =   1335
         TabIndex        =   46
         Top             =   2010
         Width           =   1335
         Begin VB.TextBox fontzize 
            Appearance      =   0  'Flat
            BackColor       =   &H00404040&
            ForeColor       =   &H00000000&
            Height          =   285
            Left            =   225
            TabIndex        =   47
            Top             =   405
            Width           =   420
         End
         Begin VB.Image submit 
            Height          =   510
            Index           =   2
            Left            =   690
            Picture         =   "masterclient.frx":15E86
            Top             =   375
            Width           =   570
         End
      End
      Begin VB.TextBox rotation 
         Appearance      =   0  'Flat
         BackColor       =   &H00404040&
         Height          =   290
         Index           =   3
         Left            =   1785
         TabIndex        =   39
         Top             =   1935
         Width           =   420
      End
      Begin VB.TextBox rotation 
         Appearance      =   0  'Flat
         BackColor       =   &H00404040&
         Height          =   290
         Index           =   2
         Left            =   1785
         TabIndex        =   38
         Top             =   1605
         Width           =   420
      End
      Begin VB.TextBox rotation 
         Appearance      =   0  'Flat
         BackColor       =   &H00404040&
         Height          =   290
         Index           =   1
         Left            =   1785
         TabIndex        =   37
         Top             =   1275
         Width           =   420
      End
      Begin VB.TextBox rotation 
         Appearance      =   0  'Flat
         BackColor       =   &H00404040&
         Height          =   290
         Index           =   0
         Left            =   1785
         TabIndex        =   36
         Top             =   945
         Width           =   420
      End
      Begin VB.TextBox position 
         Appearance      =   0  'Flat
         BackColor       =   &H00404040&
         Height          =   290
         Index           =   2
         Left            =   510
         TabIndex        =   35
         Top             =   1650
         Width           =   435
      End
      Begin VB.TextBox position 
         Appearance      =   0  'Flat
         BackColor       =   &H00404040&
         Height          =   290
         Index           =   1
         Left            =   510
         TabIndex        =   34
         Top             =   1305
         Width           =   435
      End
      Begin VB.TextBox position 
         Appearance      =   0  'Flat
         BackColor       =   &H00404040&
         Height          =   290
         Index           =   0
         Left            =   510
         TabIndex        =   33
         Top             =   960
         Width           =   435
      End
      Begin VB.Image fxswitches 
         Height          =   495
         Index           =   3
         Left            =   3585
         Picture         =   "masterclient.frx":17710
         Top             =   2475
         Width           =   525
      End
      Begin MSForms.ComboBox blendtype 
         Height          =   285
         Left            =   2565
         TabIndex        =   42
         Top             =   2175
         Width           =   1515
         VariousPropertyBits=   746588179
         BackColor       =   4210752
         ForeColor       =   14737632
         BorderStyle     =   1
         DisplayStyle    =   7
         Size            =   "2672;503"
         MatchEntry      =   1
         DropButtonStyle =   0
         SpecialEffect   =   0
         FontHeight      =   165
         FontCharSet     =   0
         FontPitchAndFamily=   2
      End
      Begin VB.Image fxswitches 
         Height          =   495
         Index           =   2
         Left            =   4710
         Picture         =   "masterclient.frx":18E23
         Top             =   990
         Width           =   525
      End
      Begin VB.Image fxswitches 
         Height          =   495
         Index           =   1
         Left            =   3765
         Picture         =   "masterclient.frx":1A536
         Top             =   990
         Width           =   525
      End
      Begin VB.Image fxswitches 
         Height          =   495
         Index           =   0
         Left            =   2820
         Picture         =   "masterclient.frx":1BC49
         Top             =   1005
         Width           =   525
      End
      Begin VB.Image textdis 
         Height          =   585
         Left            =   4635
         Stretch         =   -1  'True
         Top             =   150
         Width           =   825
      End
      Begin VB.Image submit 
         Height          =   510
         Index           =   1
         Left            =   1560
         Picture         =   "masterclient.frx":1D35C
         Top             =   2265
         Width           =   570
      End
      Begin VB.Image submit 
         Height          =   510
         Index           =   0
         Left            =   330
         Picture         =   "masterclient.frx":1EBE6
         Top             =   2265
         Width           =   570
      End
      Begin VB.Label textpath 
         BackColor       =   &H00404040&
         BackStyle       =   0  'Transparent
         ForeColor       =   &H00E0E0E0&
         Height          =   240
         Left            =   150
         TabIndex        =   41
         Top             =   540
         Width           =   4365
      End
      Begin VB.Label meshpath 
         BackColor       =   &H00404040&
         BackStyle       =   0  'Transparent
         ForeColor       =   &H00E0E0E0&
         Height          =   240
         Left            =   135
         TabIndex        =   40
         Top             =   120
         Width           =   4185
      End
   End
   Begin MSComctlLib.ImageList imglst 
      Left            =   480
      Top             =   6720
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   10
      ImageHeight     =   10
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   5
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "masterclient.frx":20470
            Key             =   "fxon"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "masterclient.frx":2191D
            Key             =   "fxoff"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "masterclient.frx":22DCF
            Key             =   "fxroot"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "masterclient.frx":24283
            Key             =   "fxedit"
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "masterclient.frx":25662
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.PictureBox clipper 
      Appearance      =   0  'Flat
      BackColor       =   &H00808080&
      ForeColor       =   &H80000008&
      Height          =   1905
      Left            =   13125
      ScaleHeight     =   125
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   7
      TabIndex        =   29
      Top             =   6150
      Width           =   135
   End
   Begin VB.PictureBox vidselect 
      Appearance      =   0  'Flat
      BackColor       =   &H00E0E0E0&
      ForeColor       =   &H80000008&
      Height          =   3270
      Left            =   4320
      ScaleHeight     =   3240
      ScaleWidth      =   3465
      TabIndex        =   22
      Top             =   480
      Visible         =   0   'False
      Width           =   3495
      Begin VB.CommandButton cancellib 
         Caption         =   "CANCEL"
         Height          =   420
         Left            =   0
         TabIndex        =   27
         Top             =   2820
         Width           =   3465
      End
      Begin VB.PictureBox vidbuts 
         Appearance      =   0  'Flat
         BackColor       =   &H00E0E0E0&
         ForeColor       =   &H80000008&
         Height          =   2565
         Left            =   0
         ScaleHeight     =   2535
         ScaleWidth      =   3405
         TabIndex        =   24
         Top             =   240
         Width           =   3435
         Begin VB.FileListBox avidir 
            Appearance      =   0  'Flat
            BackColor       =   &H00404040&
            Height          =   2370
            Left            =   45
            Pattern         =   "*.avi"
            TabIndex        =   73
            Top             =   30
            Visible         =   0   'False
            Width           =   3315
         End
         Begin VB.CommandButton sysavi 
            Caption         =   "system AVI"
            Height          =   420
            Left            =   660
            TabIndex        =   72
            Top             =   1185
            Width           =   2070
         End
         Begin VB.CommandButton vidlib 
            Caption         =   "video library"
            Height          =   420
            Left            =   645
            TabIndex        =   26
            Top             =   135
            Width           =   2070
         End
         Begin VB.CommandButton lfeed 
            Caption         =   "live feed"
            Height          =   420
            Left            =   645
            TabIndex        =   25
            Top             =   660
            Width           =   2085
         End
      End
      Begin VB.ListBox List1 
         Appearance      =   0  'Flat
         BackColor       =   &H00404040&
         ForeColor       =   &H00E0E0E0&
         Height          =   2565
         ItemData        =   "masterclient.frx":26AE4
         Left            =   15
         List            =   "masterclient.frx":26AE6
         TabIndex        =   28
         Top             =   240
         Width           =   3420
      End
      Begin VB.Label Label1 
         Alignment       =   2  'Center
         BackColor       =   &H00404040&
         Caption         =   "select video source"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   240
         Left            =   -180
         TabIndex        =   23
         Top             =   -15
         Width           =   3660
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   19
      Left            =   12000
      Picture         =   "masterclient.frx":26AE8
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   21
      Top             =   1545
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   19
         Left            =   330
         TabIndex        =   69
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   19
         Left            =   1050
         Picture         =   "masterclient.frx":29EBC
         Top             =   810
         Width           =   255
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   19
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   19
         Left            =   735
         Picture         =   "masterclient.frx":2B835
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   19
         Left            =   345
         Picture         =   "masterclient.frx":2CFF7
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   19
         Left            =   15
         Picture         =   "masterclient.frx":2E76B
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   19
         Left            =   1035
         Picture         =   "masterclient.frx":2FEF0
         Top             =   0
         Width           =   285
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   19
         Left            =   690
         Picture         =   "masterclient.frx":31686
         Top             =   0
         Width           =   330
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   19
         Left            =   360
         Picture         =   "masterclient.frx":32C6A
         Top             =   0
         Width           =   330
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   19
         Left            =   0
         Picture         =   "masterclient.frx":3424E
         Top             =   0
         Width           =   360
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   18
      Left            =   10650
      Picture         =   "masterclient.frx":3586A
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   20
      Top             =   1575
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   18
         Left            =   330
         TabIndex        =   68
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   18
         Left            =   1050
         Picture         =   "masterclient.frx":38C3E
         Top             =   795
         Width           =   255
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   18
         Left            =   0
         Picture         =   "masterclient.frx":3A5B7
         Top             =   0
         Width           =   360
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   18
         Left            =   360
         Picture         =   "masterclient.frx":3BBD3
         Top             =   0
         Width           =   330
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   18
         Left            =   690
         Picture         =   "masterclient.frx":3D1B7
         Top             =   0
         Width           =   330
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   18
         Left            =   1035
         Picture         =   "masterclient.frx":3E79B
         Top             =   0
         Width           =   285
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   18
         Left            =   15
         Picture         =   "masterclient.frx":3FF31
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   18
         Left            =   345
         Picture         =   "masterclient.frx":416B6
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   18
         Left            =   735
         Picture         =   "masterclient.frx":42E2A
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   18
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   17
      Left            =   9300
      Picture         =   "masterclient.frx":445EC
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   19
      Top             =   1560
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   17
         Left            =   330
         TabIndex        =   67
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   17
         Left            =   1050
         Picture         =   "masterclient.frx":479C0
         Top             =   795
         Width           =   255
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   17
         Left            =   0
         Picture         =   "masterclient.frx":49339
         Top             =   0
         Width           =   360
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   17
         Left            =   360
         Picture         =   "masterclient.frx":4A955
         Top             =   0
         Width           =   330
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   17
         Left            =   690
         Picture         =   "masterclient.frx":4BF39
         Top             =   0
         Width           =   330
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   17
         Left            =   1035
         Picture         =   "masterclient.frx":4D51D
         Top             =   0
         Width           =   285
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   17
         Left            =   15
         Picture         =   "masterclient.frx":4ECB3
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   17
         Left            =   345
         Picture         =   "masterclient.frx":50438
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   17
         Left            =   735
         Picture         =   "masterclient.frx":51BAC
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   17
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   16
      Left            =   7950
      Picture         =   "masterclient.frx":5336E
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   18
      Top             =   1620
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   16
         Left            =   330
         TabIndex        =   66
         Top             =   435
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   16
         Left            =   1050
         Picture         =   "masterclient.frx":56742
         Top             =   795
         Width           =   255
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   16
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   16
         Left            =   735
         Picture         =   "masterclient.frx":580BB
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   16
         Left            =   345
         Picture         =   "masterclient.frx":5987D
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   16
         Left            =   15
         Picture         =   "masterclient.frx":5AFF1
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   16
         Left            =   1035
         Picture         =   "masterclient.frx":5C776
         Top             =   0
         Width           =   285
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   16
         Left            =   690
         Picture         =   "masterclient.frx":5DF0C
         Top             =   0
         Width           =   330
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   16
         Left            =   360
         Picture         =   "masterclient.frx":5F4F0
         Top             =   0
         Width           =   330
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   16
         Left            =   0
         Picture         =   "masterclient.frx":60AD4
         Top             =   0
         Width           =   360
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   15
      Left            =   6615
      Picture         =   "masterclient.frx":620F0
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   17
      Top             =   1605
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   15
         Left            =   330
         TabIndex        =   65
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   15
         Left            =   1050
         Picture         =   "masterclient.frx":654C4
         Top             =   795
         Width           =   255
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   15
         Left            =   0
         Picture         =   "masterclient.frx":66E3D
         Top             =   0
         Width           =   360
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   15
         Left            =   360
         Picture         =   "masterclient.frx":68459
         Top             =   0
         Width           =   330
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   15
         Left            =   690
         Picture         =   "masterclient.frx":69A3D
         Top             =   0
         Width           =   330
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   15
         Left            =   1035
         Picture         =   "masterclient.frx":6B021
         Top             =   0
         Width           =   285
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   15
         Left            =   15
         Picture         =   "masterclient.frx":6C7B7
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   15
         Left            =   345
         Picture         =   "masterclient.frx":6DF3C
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   15
         Left            =   735
         Picture         =   "masterclient.frx":6F6B0
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   15
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   14
      Left            =   5340
      Picture         =   "masterclient.frx":70E72
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   16
      Top             =   1575
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   14
         Left            =   330
         TabIndex        =   64
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   14
         Left            =   1050
         Picture         =   "masterclient.frx":74246
         Top             =   795
         Width           =   255
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   14
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   14
         Left            =   735
         Picture         =   "masterclient.frx":75BBF
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   14
         Left            =   345
         Picture         =   "masterclient.frx":77381
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   14
         Left            =   15
         Picture         =   "masterclient.frx":78AF5
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   14
         Left            =   1035
         Picture         =   "masterclient.frx":7A27A
         Top             =   0
         Width           =   285
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   14
         Left            =   690
         Picture         =   "masterclient.frx":7BA10
         Top             =   0
         Width           =   330
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   14
         Left            =   360
         Picture         =   "masterclient.frx":7CFF4
         Top             =   0
         Width           =   330
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   14
         Left            =   0
         Picture         =   "masterclient.frx":7E5D8
         Top             =   0
         Width           =   360
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   13
      Left            =   4020
      Picture         =   "masterclient.frx":7FBF4
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   15
      Top             =   1590
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   13
         Left            =   330
         TabIndex        =   63
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   13
         Left            =   1050
         Picture         =   "masterclient.frx":82FC8
         Top             =   795
         Width           =   255
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   13
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   13
         Left            =   735
         Picture         =   "masterclient.frx":84941
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   13
         Left            =   345
         Picture         =   "masterclient.frx":86103
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   13
         Left            =   15
         Picture         =   "masterclient.frx":87877
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   13
         Left            =   1035
         Picture         =   "masterclient.frx":88FFC
         Top             =   0
         Width           =   285
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   13
         Left            =   690
         Picture         =   "masterclient.frx":8A792
         Top             =   0
         Width           =   330
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   13
         Left            =   360
         Picture         =   "masterclient.frx":8BD76
         Top             =   0
         Width           =   330
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   13
         Left            =   0
         Picture         =   "masterclient.frx":8D35A
         Top             =   0
         Width           =   360
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   12
      Left            =   2670
      Picture         =   "masterclient.frx":8E976
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   14
      Top             =   1575
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   12
         Left            =   330
         TabIndex        =   62
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   12
         Left            =   1050
         Picture         =   "masterclient.frx":91D4A
         Top             =   795
         Width           =   255
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   12
         Left            =   0
         Picture         =   "masterclient.frx":936C3
         Top             =   0
         Width           =   360
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   12
         Left            =   360
         Picture         =   "masterclient.frx":94CDF
         Top             =   0
         Width           =   330
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   12
         Left            =   690
         Picture         =   "masterclient.frx":962C3
         Top             =   0
         Width           =   330
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   12
         Left            =   1035
         Picture         =   "masterclient.frx":978A7
         Top             =   0
         Width           =   285
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   12
         Left            =   15
         Picture         =   "masterclient.frx":9903D
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   12
         Left            =   345
         Picture         =   "masterclient.frx":9A7C2
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   12
         Left            =   735
         Picture         =   "masterclient.frx":9BF36
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   12
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   11
      Left            =   1335
      Picture         =   "masterclient.frx":9D6F8
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   13
      Top             =   1575
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   11
         Left            =   330
         TabIndex        =   61
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   11
         Left            =   1050
         Picture         =   "masterclient.frx":A0ACC
         Top             =   795
         Width           =   255
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   11
         Left            =   0
         Picture         =   "masterclient.frx":A2445
         Top             =   0
         Width           =   360
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   11
         Left            =   360
         Picture         =   "masterclient.frx":A3A61
         Top             =   0
         Width           =   330
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   11
         Left            =   690
         Picture         =   "masterclient.frx":A5045
         Top             =   0
         Width           =   330
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   11
         Left            =   1035
         Picture         =   "masterclient.frx":A6629
         Top             =   0
         Width           =   285
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   11
         Left            =   15
         Picture         =   "masterclient.frx":A7DBF
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   11
         Left            =   345
         Picture         =   "masterclient.frx":A9544
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   11
         Left            =   735
         Picture         =   "masterclient.frx":AACB8
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   11
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   10
      Left            =   0
      Picture         =   "masterclient.frx":AC47A
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   12
      Top             =   1590
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   10
         Left            =   330
         TabIndex        =   60
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   10
         Left            =   1050
         Picture         =   "masterclient.frx":AF84E
         Top             =   795
         Width           =   255
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   10
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   10
         Left            =   735
         Picture         =   "masterclient.frx":B11C7
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   10
         Left            =   345
         Picture         =   "masterclient.frx":B2989
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   10
         Left            =   15
         Picture         =   "masterclient.frx":B40FD
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   10
         Left            =   1035
         Picture         =   "masterclient.frx":B5882
         Top             =   0
         Width           =   285
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   10
         Left            =   690
         Picture         =   "masterclient.frx":B7018
         Top             =   0
         Width           =   330
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   10
         Left            =   360
         Picture         =   "masterclient.frx":B85FC
         Top             =   0
         Width           =   330
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   10
         Left            =   0
         Picture         =   "masterclient.frx":B9BE0
         Top             =   0
         Width           =   360
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   9
      Left            =   12000
      Picture         =   "masterclient.frx":BB1FC
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   11
      Top             =   -15
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   9
         Left            =   330
         TabIndex        =   59
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   9
         Left            =   1050
         Picture         =   "masterclient.frx":BE5D0
         Top             =   795
         Width           =   255
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   9
         Left            =   0
         Picture         =   "masterclient.frx":BFF49
         Top             =   0
         Width           =   360
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   9
         Left            =   360
         Picture         =   "masterclient.frx":C1565
         Top             =   0
         Width           =   330
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   9
         Left            =   690
         Picture         =   "masterclient.frx":C2B49
         Top             =   0
         Width           =   330
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   9
         Left            =   1035
         Picture         =   "masterclient.frx":C412D
         Top             =   0
         Width           =   285
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   9
         Left            =   15
         Picture         =   "masterclient.frx":C58C3
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   9
         Left            =   345
         Picture         =   "masterclient.frx":C7048
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   9
         Left            =   735
         Picture         =   "masterclient.frx":C87BC
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   9
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   8
      Left            =   10665
      Picture         =   "masterclient.frx":C9F7E
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   10
      Top             =   0
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   8
         Left            =   330
         TabIndex        =   58
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   8
         Left            =   1050
         Picture         =   "masterclient.frx":CD352
         Top             =   795
         Width           =   255
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   8
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   8
         Left            =   735
         Picture         =   "masterclient.frx":CECCB
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   8
         Left            =   345
         Picture         =   "masterclient.frx":D048D
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   8
         Left            =   15
         Picture         =   "masterclient.frx":D1C01
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   8
         Left            =   1035
         Picture         =   "masterclient.frx":D3386
         Top             =   0
         Width           =   285
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   8
         Left            =   690
         Picture         =   "masterclient.frx":D4B1C
         Top             =   0
         Width           =   330
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   8
         Left            =   360
         Picture         =   "masterclient.frx":D6100
         Top             =   0
         Width           =   330
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   8
         Left            =   0
         Picture         =   "masterclient.frx":D76E4
         Top             =   0
         Width           =   360
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   7
      Left            =   9330
      Picture         =   "masterclient.frx":D8D00
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   9
      Top             =   0
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   7
         Left            =   330
         TabIndex        =   57
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   7
         Left            =   1050
         Picture         =   "masterclient.frx":DC0D4
         Top             =   795
         Width           =   255
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   7
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   7
         Left            =   735
         Picture         =   "masterclient.frx":DDA4D
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   7
         Left            =   345
         Picture         =   "masterclient.frx":DF20F
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   7
         Left            =   15
         Picture         =   "masterclient.frx":E0983
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   7
         Left            =   1035
         Picture         =   "masterclient.frx":E2108
         Top             =   0
         Width           =   285
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   7
         Left            =   690
         Picture         =   "masterclient.frx":E389E
         Top             =   0
         Width           =   330
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   7
         Left            =   360
         Picture         =   "masterclient.frx":E4E82
         Top             =   0
         Width           =   330
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   7
         Left            =   0
         Picture         =   "masterclient.frx":E6466
         Top             =   0
         Width           =   360
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   6
      Left            =   7995
      Picture         =   "masterclient.frx":E7A82
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   8
      Top             =   45
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   6
         Left            =   330
         TabIndex        =   56
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   6
         Left            =   1050
         Picture         =   "masterclient.frx":EAE56
         Top             =   795
         Width           =   255
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   6
         Left            =   0
         Picture         =   "masterclient.frx":EC7CF
         Top             =   0
         Width           =   360
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   6
         Left            =   360
         Picture         =   "masterclient.frx":EDDEB
         Top             =   0
         Width           =   330
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   6
         Left            =   690
         Picture         =   "masterclient.frx":EF3CF
         Top             =   0
         Width           =   330
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   6
         Left            =   1035
         Picture         =   "masterclient.frx":F09B3
         Top             =   0
         Width           =   285
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   6
         Left            =   15
         Picture         =   "masterclient.frx":F2149
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   6
         Left            =   345
         Picture         =   "masterclient.frx":F38CE
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   6
         Left            =   735
         Picture         =   "masterclient.frx":F5042
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   6
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   5
      Left            =   6660
      Picture         =   "masterclient.frx":F6804
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   7
      Top             =   30
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   5
         Left            =   330
         TabIndex        =   55
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   5
         Left            =   1050
         Picture         =   "masterclient.frx":F9BD8
         Top             =   795
         Width           =   255
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   5
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   5
         Left            =   735
         Picture         =   "masterclient.frx":FB551
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   5
         Left            =   345
         Picture         =   "masterclient.frx":FCD13
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   5
         Left            =   15
         Picture         =   "masterclient.frx":FE487
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   5
         Left            =   1035
         Picture         =   "masterclient.frx":FFC0C
         Top             =   0
         Width           =   285
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   5
         Left            =   690
         Picture         =   "masterclient.frx":1013A2
         Top             =   0
         Width           =   330
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   5
         Left            =   360
         Picture         =   "masterclient.frx":102986
         Top             =   0
         Width           =   330
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   5
         Left            =   0
         Picture         =   "masterclient.frx":103F6A
         Top             =   0
         Width           =   360
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   4
      Left            =   5325
      Picture         =   "masterclient.frx":105586
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   6
      Top             =   15
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   4
         Left            =   330
         TabIndex        =   54
         Top             =   465
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   4
         Left            =   1050
         Picture         =   "masterclient.frx":10895A
         Top             =   795
         Width           =   255
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   4
         Left            =   0
         Picture         =   "masterclient.frx":10A2D3
         Top             =   0
         Width           =   360
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   4
         Left            =   360
         Picture         =   "masterclient.frx":10B8EF
         Top             =   0
         Width           =   330
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   4
         Left            =   690
         Picture         =   "masterclient.frx":10CED3
         Top             =   0
         Width           =   330
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   4
         Left            =   1035
         Picture         =   "masterclient.frx":10E4B7
         Top             =   0
         Width           =   285
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   4
         Left            =   15
         Picture         =   "masterclient.frx":10FC4D
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   4
         Left            =   345
         Picture         =   "masterclient.frx":1113D2
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   4
         Left            =   735
         Picture         =   "masterclient.frx":112B46
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   4
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   3
      Left            =   4005
      Picture         =   "masterclient.frx":114308
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   5
      Top             =   30
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   3
         Left            =   330
         TabIndex        =   53
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   3
         Left            =   1050
         Picture         =   "masterclient.frx":1176DC
         Top             =   795
         Width           =   255
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   3
         Left            =   0
         Picture         =   "masterclient.frx":119055
         Top             =   0
         Width           =   360
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   3
         Left            =   360
         Picture         =   "masterclient.frx":11A671
         Top             =   0
         Width           =   330
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   3
         Left            =   690
         Picture         =   "masterclient.frx":11BC55
         Top             =   0
         Width           =   330
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   3
         Left            =   1035
         Picture         =   "masterclient.frx":11D239
         Top             =   0
         Width           =   285
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   3
         Left            =   15
         Picture         =   "masterclient.frx":11E9CF
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   3
         Left            =   345
         Picture         =   "masterclient.frx":120154
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   3
         Left            =   735
         Picture         =   "masterclient.frx":1218C8
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   3
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   2
      Left            =   2670
      Picture         =   "masterclient.frx":12308A
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   4
      Top             =   15
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   2
         Left            =   330
         TabIndex        =   52
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   2
         Left            =   1050
         Picture         =   "masterclient.frx":12645E
         Top             =   795
         Width           =   255
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   2
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   2
         Left            =   735
         Picture         =   "masterclient.frx":127DD7
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   2
         Left            =   345
         Picture         =   "masterclient.frx":129599
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   2
         Left            =   15
         Picture         =   "masterclient.frx":12AD0D
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   2
         Left            =   1035
         Picture         =   "masterclient.frx":12C492
         Top             =   0
         Width           =   285
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   2
         Left            =   690
         Picture         =   "masterclient.frx":12DC28
         Top             =   0
         Width           =   330
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   2
         Left            =   360
         Picture         =   "masterclient.frx":12F20C
         Top             =   0
         Width           =   330
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   2
         Left            =   0
         Picture         =   "masterclient.frx":1307F0
         Top             =   0
         Width           =   360
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   1
      Left            =   1335
      Picture         =   "masterclient.frx":131E0C
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   3
      Top             =   15
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   1
         Left            =   330
         TabIndex        =   51
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   1
         Left            =   1050
         Picture         =   "masterclient.frx":1351E0
         Top             =   795
         Width           =   255
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   1
         Left            =   0
         Picture         =   "masterclient.frx":136B59
         Top             =   0
         Width           =   360
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   1
         Left            =   360
         Picture         =   "masterclient.frx":138175
         Top             =   0
         Width           =   330
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   1
         Left            =   690
         Picture         =   "masterclient.frx":139759
         Top             =   0
         Width           =   330
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   1
         Left            =   1035
         Picture         =   "masterclient.frx":13AD3D
         Top             =   0
         Width           =   285
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   1
         Left            =   15
         Picture         =   "masterclient.frx":13C4D3
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   1
         Left            =   345
         Picture         =   "masterclient.frx":13DC58
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   1
         Left            =   735
         Picture         =   "masterclient.frx":13F3CC
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   1
         Left            =   15
         Stretch         =   -1  'True
         Top             =   300
         Width           =   1020
      End
   End
   Begin VB.PictureBox Vobject 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1560
      Index           =   0
      Left            =   1260
      Picture         =   "masterclient.frx":140B8E
      ScaleHeight     =   1560
      ScaleWidth      =   1335
      TabIndex        =   2
      Top             =   -30
      Width           =   1335
      Begin VB.Label loading 
         BackStyle       =   0  'Transparent
         Caption         =   "L"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   29.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H000080FF&
         Height          =   645
         Index           =   0
         Left            =   330
         TabIndex        =   50
         Top             =   450
         Visible         =   0   'False
         Width           =   435
      End
      Begin VB.Image vfx 
         Height          =   495
         Index           =   0
         Left            =   1050
         Picture         =   "masterclient.frx":143F62
         Top             =   795
         Width           =   255
      End
      Begin VB.Image vidhold 
         Height          =   975
         Index           =   0
         Left            =   0
         Stretch         =   -1  'True
         Top             =   285
         Width           =   1020
      End
      Begin VB.Image reset 
         Height          =   270
         Index           =   0
         Left            =   735
         Picture         =   "masterclient.frx":1458DB
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image underlay 
         Height          =   270
         Index           =   0
         Left            =   345
         Picture         =   "masterclient.frx":14709D
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image overlay 
         Height          =   270
         Index           =   0
         Left            =   15
         Picture         =   "masterclient.frx":148811
         Top             =   1290
         Width           =   300
      End
      Begin VB.Image vidman 
         Height          =   270
         Index           =   0
         Left            =   1035
         Picture         =   "masterclient.frx":149F96
         Top             =   0
         Width           =   285
      End
      Begin VB.Image fwd 
         Height          =   270
         Index           =   0
         Left            =   690
         Picture         =   "masterclient.frx":14B72C
         Top             =   0
         Width           =   330
      End
      Begin VB.Image pingpong 
         Height          =   270
         Index           =   0
         Left            =   360
         Picture         =   "masterclient.frx":14CD10
         Top             =   0
         Width           =   330
      End
      Begin VB.Image rwd 
         Height          =   270
         Index           =   0
         Left            =   0
         Picture         =   "masterclient.frx":14E2F4
         Top             =   0
         Width           =   360
      End
   End
   Begin MSWinsockLib.Winsock winsock1 
      Left            =   12285
      Top             =   7650
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.Timer tmrLiveSpec 
      Enabled         =   0   'False
      Left            =   12705
      Top             =   7635
   End
   Begin VB.PictureBox display 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   1905
      Left            =   8460
      ScaleHeight     =   125
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   310
      TabIndex        =   1
      Top             =   6165
      Width           =   4680
   End
   Begin MSComctlLib.TreeView TreeView1 
      Height          =   4650
      Left            =   45
      TabIndex        =   0
      Top             =   3405
      Width           =   2355
      _ExtentX        =   4154
      _ExtentY        =   8202
      _Version        =   393217
      Indentation     =   497
      Sorted          =   -1  'True
      Style           =   7
      ImageList       =   "imglst"
      BorderStyle     =   1
      Appearance      =   0
      MousePointer    =   10
   End
   Begin VB.Image submit 
      Height          =   510
      Index           =   3
      Left            =   7485
      Picture         =   "masterclient.frx":14F910
      Top             =   7245
      Width           =   570
   End
   Begin VB.Image Image16 
      Height          =   780
      Left            =   2625
      Picture         =   "masterclient.frx":15119A
      Top             =   7185
      Width           =   5505
   End
   Begin VB.Image sendauon 
      Height          =   225
      Left            =   105
      Picture         =   "masterclient.frx":155309
      Top             =   990
      Width           =   720
   End
   Begin VB.Image sendauoff 
      Height          =   225
      Left            =   30
      Picture         =   "masterclient.frx":156EC6
      Top             =   630
      Width           =   720
   End
   Begin VB.Image audinbf 
      Height          =   225
      Left            =   0
      Picture         =   "masterclient.frx":158A65
      Top             =   0
      Width           =   735
   End
   Begin VB.Image audinbo 
      Height          =   225
      Left            =   0
      Picture         =   "masterclient.frx":15A72A
      Top             =   225
      Width           =   735
   End
   Begin VB.Image ainb 
      Height          =   225
      Left            =   11745
      Picture         =   "masterclient.frx":15C402
      Top             =   5880
      Width           =   735
   End
   Begin VB.Image aup 
      Height          =   225
      Left            =   12495
      Picture         =   "masterclient.frx":15E0C7
      Top             =   5880
      Width           =   720
   End
   Begin VB.Image Image15 
      Height          =   255
      Left            =   8460
      Picture         =   "masterclient.frx":15FC84
      Top             =   5865
      Width           =   4815
   End
   Begin VB.Image mbeaton 
      Height          =   270
      Left            =   -15
      Picture         =   "masterclient.frx":1612DF
      Top             =   255
      Width           =   1065
   End
   Begin VB.Image mbeatof 
      Height          =   270
      Left            =   0
      Picture         =   "masterclient.frx":1632B2
      Top             =   0
      Width           =   1065
   End
   Begin VB.Image mbeat 
      Height          =   270
      Left            =   7245
      Picture         =   "masterclient.frx":16533B
      Top             =   3390
      Width           =   1065
   End
   Begin MSForms.TabStrip TabStrip1 
      Height          =   4275
      Left            =   2520
      TabIndex        =   31
      Top             =   3765
      Width           =   5835
      ListIndex       =   0
      BackColor       =   4210752
      Size            =   "10292;7541"
      Items           =   "Tab1;Tab2;"
      TipStrings      =   ";;"
      Names           =   "Tab1;Tab2;"
      NewVersion      =   -1  'True
      TabsAllocated   =   2
      Tags            =   ";;"
      TabData         =   2
      Accelerator     =   ";;"
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      TabState        =   "3;3"
   End
   Begin VB.Label fxtitle 
      BackStyle       =   0  'Transparent
      Caption         =   "test text"
      ForeColor       =   &H00E0E0E0&
      Height          =   270
      Left            =   2580
      TabIndex        =   30
      Top             =   3420
      Width           =   3555
   End
   Begin VB.Image vidfxoff 
      Height          =   495
      Left            =   135
      Picture         =   "masterclient.frx":1673C4
      Top             =   615
      Width           =   255
   End
   Begin VB.Image vidfxon 
      Height          =   495
      Left            =   405
      Picture         =   "masterclient.frx":168D0C
      Top             =   360
      Width           =   255
   End
   Begin VB.Image Image13 
      Height          =   195
      Left            =   8460
      Picture         =   "masterclient.frx":16A685
      Top             =   4335
      Width           =   1725
   End
   Begin VB.Image render 
      Height          =   510
      Index           =   3
      Left            =   12210
      Picture         =   "masterclient.frx":16C56A
      Top             =   4710
      Width           =   570
   End
   Begin VB.Image render 
      Height          =   510
      Index           =   2
      Left            =   11085
      Picture         =   "masterclient.frx":16DDF4
      Top             =   4710
      Width           =   570
   End
   Begin VB.Image render 
      Height          =   510
      Index           =   1
      Left            =   9990
      Picture         =   "masterclient.frx":16F67E
      Top             =   4710
      Width           =   570
   End
   Begin VB.Image render 
      Height          =   510
      Index           =   0
      Left            =   8880
      Picture         =   "masterclient.frx":170F08
      Top             =   4680
      Width           =   570
   End
   Begin VB.Image cambeat 
      Height          =   510
      Left            =   12660
      Picture         =   "masterclient.frx":1727F7
      Top             =   3465
      Width           =   570
   End
   Begin VB.Image Image10 
      Height          =   195
      Left            =   8445
      Picture         =   "masterclient.frx":174081
      Top             =   3165
      Width           =   1725
   End
   Begin VB.Image cam 
      Height          =   495
      Index           =   7
      Left            =   11850
      Picture         =   "masterclient.frx":175816
      Top             =   3465
      Width           =   525
   End
   Begin VB.Image cam 
      Height          =   495
      Index           =   6
      Left            =   11370
      Picture         =   "masterclient.frx":176F29
      Top             =   3465
      Width           =   525
   End
   Begin VB.Image cam 
      Height          =   495
      Index           =   5
      Left            =   10890
      Picture         =   "masterclient.frx":17863C
      Top             =   3465
      Width           =   525
   End
   Begin VB.Image cam 
      Height          =   495
      Index           =   4
      Left            =   10410
      Picture         =   "masterclient.frx":179D4F
      Top             =   3465
      Width           =   525
   End
   Begin VB.Image cam 
      Height          =   495
      Index           =   3
      Left            =   9930
      Picture         =   "masterclient.frx":17B462
      Top             =   3465
      Width           =   525
   End
   Begin VB.Image cam 
      Height          =   495
      Index           =   2
      Left            =   9450
      Picture         =   "masterclient.frx":17CB75
      Top             =   3465
      Width           =   525
   End
   Begin VB.Image cam 
      Height          =   495
      Index           =   1
      Left            =   8970
      Picture         =   "masterclient.frx":17E288
      Top             =   3465
      Width           =   525
   End
   Begin VB.Image cam 
      Height          =   495
      Index           =   0
      Left            =   8490
      Picture         =   "masterclient.frx":17F99B
      Top             =   3465
      Width           =   525
   End
   Begin VB.Image Image9 
      Height          =   270
      Left            =   960
      Picture         =   "masterclient.frx":181046
      Top             =   2055
      Width           =   360
   End
   Begin VB.Image Image8 
      Height          =   255
      Left            =   945
      Top             =   2070
      Width           =   330
   End
   Begin VB.Image Image7 
      Height          =   270
      Left            =   975
      Picture         =   "masterclient.frx":182662
      Top             =   2040
      Width           =   330
   End
   Begin VB.Image Image6 
      Height          =   270
      Left            =   945
      Picture         =   "masterclient.frx":183C46
      Top             =   2040
      Width           =   330
   End
   Begin VB.Image Image5 
      Height          =   270
      Left            =   930
      Picture         =   "masterclient.frx":18522A
      Top             =   2055
      Width           =   285
   End
   Begin VB.Image Image4 
      Height          =   270
      Left            =   960
      Picture         =   "masterclient.frx":1869C0
      Top             =   2010
      Width           =   300
   End
   Begin VB.Image Image3 
      Height          =   270
      Left            =   975
      Picture         =   "masterclient.frx":188134
      Top             =   2070
      Width           =   300
   End
   Begin VB.Image Image1 
      Height          =   270
      Left            =   960
      Picture         =   "masterclient.frx":1898B9
      Top             =   2025
      Width           =   300
   End
   Begin VB.Image treset 
      Height          =   270
      Left            =   960
      Picture         =   "masterclient.frx":18B07B
      Top             =   465
      Width           =   300
   End
   Begin VB.Image toverlay 
      Height          =   270
      Left            =   975
      Picture         =   "masterclient.frx":18C83D
      Top             =   510
      Width           =   300
   End
   Begin VB.Image tunderlay 
      Height          =   270
      Left            =   960
      Picture         =   "masterclient.frx":18DFC2
      Top             =   450
      Width           =   300
   End
   Begin VB.Image tvidman 
      Height          =   270
      Left            =   930
      Picture         =   "masterclient.frx":18F736
      Top             =   495
      Width           =   285
   End
   Begin VB.Image tpong 
      Height          =   270
      Left            =   945
      Picture         =   "masterclient.frx":190ECC
      Top             =   480
      Width           =   330
   End
   Begin VB.Image tfwd 
      Height          =   270
      Left            =   975
      Picture         =   "masterclient.frx":1924B0
      Top             =   480
      Width           =   330
   End
   Begin VB.Image blank 
      Height          =   255
      Left            =   945
      Top             =   510
      Width           =   330
   End
   Begin VB.Image trwd 
      Height          =   270
      Left            =   960
      Picture         =   "masterclient.frx":193A94
      Top             =   495
      Width           =   360
   End
   Begin VB.Image Image2 
      Height          =   195
      Left            =   60
      Picture         =   "masterclient.frx":1950B0
      Top             =   3150
      Width           =   1725
   End
   Begin VB.Image editortitle 
      Height          =   195
      Left            =   2445
      Picture         =   "masterclient.frx":196C28
      Top             =   3165
      Width           =   1725
   End
   Begin VB.Image audiotitle 
      Height          =   195
      Left            =   8460
      Picture         =   "masterclient.frx":198419
      Top             =   5655
      Width           =   1725
   End
   Begin VB.Image buttondown 
      Height          =   495
      Left            =   330
      Picture         =   "masterclient.frx":19A2A6
      Top             =   870
      Width           =   525
   End
   Begin VB.Image buttonup 
      Height          =   495
      Left            =   120
      Picture         =   "masterclient.frx":19B951
      Top             =   480
      Width           =   525
   End
   Begin VB.Image obuttondown 
      Height          =   510
      Left            =   405
      Picture         =   "masterclient.frx":19D064
      Top             =   525
      Width           =   570
   End
   Begin VB.Image obuttonup 
      Height          =   510
      Left            =   300
      Picture         =   "masterclient.frx":19E953
      Top             =   165
      Width           =   570
   End
   Begin VB.Image Image11 
      Height          =   945
      Left            =   8430
      Picture         =   "masterclient.frx":1A01DD
      Top             =   3345
      Width           =   4860
   End
   Begin VB.Image Image12 
      Height          =   1020
      Left            =   8445
      Picture         =   "masterclient.frx":1A3168
      Top             =   4575
      Width           =   4815
   End
   Begin VB.Image Image14 
      Height          =   360
      Left            =   2430
      Picture         =   "masterclient.frx":1A7227
      Top             =   3345
      Width           =   5970
   End
   Begin VB.Image sysavibmp 
      Height          =   975
      Left            =   150
      Picture         =   "masterclient.frx":1A8F20
      Top             =   225
      Width           =   1035
   End
   Begin VB.Image lfeedimg 
      Height          =   1500
      Left            =   645
      Picture         =   "masterclient.frx":1AB4E1
      Top             =   1050
      Width           =   1500
   End
   Begin VB.Menu connect 
      Caption         =   "connect"
   End
   Begin VB.Menu hostz 
      Caption         =   "server type"
      Begin VB.Menu wq 
         Caption         =   "192.168.0.11"
      End
      Begin VB.Menu multi 
         Caption         =   "multiserver / localhost"
      End
   End
   Begin VB.Menu sayt 
      Caption         =   "say T"
   End
   Begin VB.Menu keyboard 
      Caption         =   "keyboard-jam"
   End
   Begin VB.Menu midi 
      Caption         =   "midiclient"
   End
   Begin VB.Menu auto 
      Caption         =   "autopilot"
      Begin VB.Menu autoplay 
         Caption         =   "play"
      End
      Begin VB.Menu autorecord 
         Caption         =   "record"
      End
      Begin VB.Menu autoload 
         Caption         =   "load pilot"
      End
      Begin VB.Menu autosave 
         Caption         =   "save pilot"
      End
   End
End
Attribute VB_Name = "masterclient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim fx(1000) As String
Dim fxc As Integer
Dim tsobjcloop As Integer
Dim host As String
Dim pong(4, 20) As Integer
Dim under(20) As Integer
Dim over(20) As Integer
Dim tvidlib() As String
Dim tvidfolder() As String
Dim loadedvid(20) As Integer
Dim vidset(20) As Integer
Dim currentvid As Integer
Dim tcambeat As Integer
Dim audioclip As Integer
Public leftclip As Long
Public rightclip As Long
Public clipclicker As Integer
Dim currentfx As Integer
Dim Dragvid As Integer
Dim deletvid As Integer
Dim vidtofx(1000, 20) As Integer
Dim sliderdrag
Dim Mesha()
Dim Mesht()
Dim Meshpatha()
Dim meshtexture()
Dim currentmesh
Dim meshpos(1000, 3)
Dim meshrot(1000, 4)
Dim fxswt(5)
Dim forcewireframe()
Dim beatscale()
Dim videomapped()
Dim blendmode()
Dim blend()
Dim textstring(1000)
Dim txttype(1000)
Dim tfont(1000)
Dim tfontsize(1000)
Dim mmbeat(1000)
Dim loadingvid
Dim loadingvidok
Dim mbar(2)
Dim colour(1000)
Dim internalaudio
Dim sysavienabled
Dim sysavislot
Dim lfeedslot
Dim lfeedenabled
Dim cyclef(1000)
Public meshcount
Dim fontcount
Dim fc
Dim autocount As Integer
Dim autoevent(100000, 3)
Dim autoframe
Dim eventcount
        
        
Private Sub ainb_Click()
    If internalaudio = 1 Then
        ainb.Picture = audinbo.Picture
        internalaudio = 0
    Else
        ainb.Picture = audinbf.Picture
        internalaudio = 1
    End If
End Sub

Private Sub ani_Click()
 If animate.Visible = True Then
    animate.Visible = False
 Else
    animate.Visible = True
    cyclefonts.Value = cyclef(currentmesh)
 End If
End Sub



Private Sub aup_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    aup.Picture = sendauoff.Picture
End Sub

Private Sub aup_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
    aup.Picture = sendauon.Picture
End Sub

Private Sub autoload_Click()
On Error GoTo Err_Form_Load
CommonDialog1.InitDir = App.Path
CommonDialog1.Filter = "auto pilot files (*.auto)|*.auto"
CommonDialog1.flags = &H4&
CommonDialog1.Action = 1
Open CommonDialog1.FileName For Input As #1
    Dim uin
    uin = 0
    Do While Not EOF(1)
    Line Input #1, tees
    If InStr(1, tees, ";", 1) Then
    temps = tees
     
    autoevent(uin, 0) = Mid(tees, 1, InStr(1, tees, ";", 1) - 1)
         
    temps = Mid(temps, InStr(1, temps, ";", 1) + 1, Len(temps))
    autoevent(uin, 1) = Mid(temps, 1, InStr(1, temps, ";", 1) - 1)
     
    temps = Mid(temps, InStr(1, temps, ";", 1) + 1, Len(temps))
    autoevent(uin, 2) = Mid(temps, 1, InStr(1, temps, ";", 1) - 1)
     
        
    uin = uin + 1
    End If
  Loop
  framecount = uin
Close #1

Err_Form_Load:


End Sub

Private Sub autoplay_Click()
    If autoplay.Caption = "play" Then
        autoplay.Caption = "stop"
        autocount = 0
        eventcount = 0
    Else
        autoplay.Caption = "play"
        
    End If
    
End Sub

Private Sub autorecord_Click()
    If autorecord.Caption = "record" Then
        autorecord.Caption = "stop"
        autocount = 0
        autoframe = 0
    Else
        autorecord.Caption = "record"
        
    End If
End Sub
   
Private Sub autosave_Click()
Dim I As Integer, j As Integer

'error handler: if the file is not found, the program will not attempt to save data
On Error GoTo Err_Form_Unload

'set the dialog box's starting path to the program's path
CommonDialog1.InitDir = App.Path
'set the filter the *.dat files
CommonDialog1.Filter = "autopilot (*.auto)|*.auto"
'hide the read-only check box
CommonDialog1.flags = &H4&
'force the dialog box to prompt for a file to Save As
CommonDialog1.Action = 2

'open the file
'For Output means we will be writing to the file
'As #1 means the #1 will be used to refer to the file
Open CommonDialog1.FileName For Output As #1
        Print #1, framecount
        For j = 0 To framecount - 1
                  Print #1, autoevent(j, 0) & ";" & autoevent(j, 1) & ";" & autoevent(j, 2) & ";"
        Next j
Close #1
Err_Form_Unload:
End Sub

Private Sub autotimer_Timer()
    If autorecord.Caption = "stop" Then
        autocount = autocount + 1
    End If
    If autoplay.Caption = "stop" Then
        If autoevent(eventcount, 0) = autocount Then
            If autoevent(eventcount, 2) = 1 Then
                 If TreeView1.Nodes.Item(autoevent(eventcount, 1)).Image = 2 Then
                    TreeView1.Nodes.Item(autoevent(eventcount, 1)).Image = 1
                 ElseIf TreeView1.Nodes.Item(autoevent(eventcount, 1)).Image = 1 Then
                    TreeView1.Nodes.Item(autoevent(eventcount, 1)).Image = 2
                 End If
                 If winsock1.State = sckConnected Then
                    winsock1.SendData "effect(" & Val(TreeView1.Nodes.Item(autoevent(eventcount, 1)).Key) & ")"
                 End If
            End If
            If autoevent(eventcount, 2) = 2 Then
                cam_Click (autoevent(eventcount, 1))
            End If
            If autoevent(eventcount, 2) = 3 Then
                render_Click (autoevent(eventcount, 1))
            End If
            If autoevent(eventcount, 2) = 4 Then
                overlay_Click (autoevent(eventcount, 1))
            End If
            If autoevent(eventcount, 2) = 5 Then
                underlay_Click (autoevent(eventcount, 1))
            End If
            If eventcount = framecount Then
                eventcount = 0
                autcount = -1
            Else
                eventcount = eventcount + 1
            End If
        End If
        autocount = autocount + 1
        
    End If
    
End Sub

Private Sub avidir_Click()
    
    avidir.Visible = False
    vidselect.Visible = False
    vidhold(currentvid).Picture = sysavibmp.Picture
        If winsock1.State = sckConnected Then
            winsock1.SendData "sysavi(" & currentvid & ")(" & avidir.FileName & ")"
        End If
    sysavienabled = 1
    loadedvid(currentvid) = 1
    sysavislot = currentvid

End Sub

Private Sub cam_Click(Index As Integer)
    For I = 0 To 7
        cam(I).Picture = buttonup.Picture
    Next I
    cam(Index).Picture = buttondown.Picture
    If winsock1.State = sckConnected Then
        winsock1.SendData "camera(" & Index & ")"
    End If
    
    If autorecord.Caption = "stop" Then
        autoevent(autoframe, 0) = autocount
        autoevent(autoframe, 1) = Index
        autoevent(autoframe, 2) = 2
        autoframe = autoframe + 1
    End If
End Sub

Private Sub cambeat_Click()
    If tcambeat = 1 Then
        cambeat.Picture = obuttonup.Picture
        tcambeat = 0
    Else
        cambeat.Picture = obuttondown.Picture
        tcambeat = 1
    End If
    If winsock1.State = sckConnected Then
        winsock1.SendData "camerabeat()"
    End If
End Sub

Private Sub cancellib_Click()
    vidselect.Visible = False
    avidir.Visible = False
End Sub

Private Sub clipper_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    audioclip = clipper.Height - y
    updateaudiovis
End Sub

Private Sub connect_Click()
    If connect.Caption <> "connected" Then
        winsock1.RemoteHost = host
        winsock1.RemotePort = 1009
        connect.Caption = "connected"
        winsock1.connect
        getinfo.Enabled = True
    End If
End Sub

Private Sub cyclefonts_Click()
    If cyclefonts.Value = True Then
        cyclef(currentmesh) = 1
    Else
        cyclef(currentmesh) = 0
    End If
    
End Sub

Private Sub display_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button = 1 Then
        If clipclicker = 0 Then
            leftclip = x / 2
            rightclip = x / 2 + 2
            clipclicker = 1
        ElseIf clipclicker = 1 Then
            rightclip = x / 2
            clipclicker = 0
        End If
    End If
End Sub



Private Sub fontz_Click()
   If winsock1.State = sckConnected Then
       winsock1.SendData "font(" & currentmesh & " " & fontz.ListIndex & ")"
   End If
End Sub



Public Sub Form_Load()
    fc = 0
    
    'change and set the current path
    'so it won't ever tell you that bass.dll isn't found
''    ChDrive App.Path
''    ChDir App.Path
        avidir.Path = "..\lib\avi\"
    
    'check if bass.dll is exists
    If FileExists(RPP(App.Path) & "bass.dll") = False Then
        MsgBox "BASS.DLL not exists", vbCritical
    ''End
    End If
    
    'Check that BASS 1.5 was loaded
    If BASS_GetStringVersion <> "1.5" Then
        MsgBox "BASS version 1.5 was not loaded", vbCritical
      ''  End
    End If
    
    'initialize BASS recording (default device)
    If BASS_RecordInit(-1) = 0 Then
        MsgBox "Error: Can't initialize device", vbCritical
     ''   End
    End If
        
    'start recording (44100hz mono 16-bit)
    'calling a CALLBACK function DuffRecording!
    If BASS_RecordStart(44100, BASS_SAMPLE_MONO, AddressOf BuffRecording, 2) = 0 Then
        MsgBox "Error: Can't start recording", vbCritical
       '' End
    End If
  
    specpos = 0
    specmode = False
    SPECWIDTH = display.Width
    SPECHEIGHT = display.Height
    
    Me.ScaleMode = vbPixels
    
    'create bitmap to draw spectrum in - 8 bit for easy updating :)
    With bh.bmiHeader
        .biBitCount = 8
        .biPlanes = 1
        .biSize = Len(bh.bmiHeader)
        .biWidth = SPECWIDTH
        .biHeight = SPECHEIGHT  'upside down (line 0=bottom)
        .biClrUsed = 256
        .biClrImportant = 256
    End With
    
    Dim a As Byte
                 
    audioclip = 120
    leftclip = 0
    rightclip = 0
    updateaudiovis
    mbar(0) = membar(0).Width
    mbar(1) = membar(1).Width
    
    loadfonts
    
    tmrLiveSpec.Enabled = True
    Set nodX = TreeView1.Nodes.Add(, , "t", "{ FX }")
    nodX.Expanded = True
    nodX.Image = 3
    setupvidui
    loadvidlib
    loadtscript
    displayfx 3
    internalaudio = 1
    blendtype.AddItem "blend1", 0
    blendtype.AddItem "blend2", 1
    blendtype.AddItem "blend3", 2

       
    host = "192.168.0.10"
End Sub
Public Sub updateaudiovis()
Dim Colors(256) As RGBQUAD
   
    
   For a = 1 To audioclip
        Colors(a).rgbGreen = 255 - 2 * a
        Colors(a).rgbRed = 2 * a
    Next a
    For a = 0 To 31
        Colors(audioclip + a).rgbBlue = 255 ' 8 * a
        Colors(audioclip + 32 + a).rgbBlue = 255
        Colors(audioclip + 32 + a).rgbRed = 8 * a
        Colors(audioclip + 64 + a).rgbRed = 255
        Colors(audioclip + 64 + a).rgbBlue = 8 * (31 - a)
        Colors(audioclip + 64 + a).rgbGreen = 8 * a
        Colors(audioclip + 96 + a).rgbRed = 255
        Colors(audioclip + 96 + a).rgbGreen = 255
        Colors(audioclip + 96 + a).rgbBlue = 8 * a
    Next a
    For a = 0 To 255
    bh.bmiColors(a) = Colors(a)
    Next a
End Sub

Private Sub loadfonts()
Open "../lib/fonts.okot" For Input As #1
    Dim uin
    uin = 0
    Do While Not EOF(1)
        Line Input #1, Fonts
            '' this is the thing that makes if work
    If InStr(1, Fonts, ";", 1) Then
    fontz.AddItem Mid(Fonts, 1, InStr(1, Fonts, ";", 1) - 1), uin
    uin = uin + 1
    End If
        Loop
Close #1
fontcount = uin
End Sub

Private Sub loadtscript()
   '' loads the tscript file into the system and configs the layout
    fxc = 0
    tsobjcloop = 0
    Dim tC(3)
    Open "../tscript/tscript.okot" For Input As #1
    Dim tmp
    Dim cmesh
    Dim uin
    Dim tmper
    uin = 1
    Do While Not EOF(1)
        Line Input #1, tscript
        '' GET ALL OF THE EFFECTS OUT AND
        
        If InStr(1, tscript, "effect(", 0) Then
            fx(fxc) = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
            Set nodX = TreeView1.Nodes.Add("t", tvwChild, tsobjcloop & "ts", fx(fxc))
            nodX.Image = 1
            Set nodX = TreeView1.Nodes.Add(tsobjcloop & "ts", tvwChild, tsobjcloop & "tedit", "[ EDIT ]")
            nodX.Image = 4
            fxc = fxc + 1
            tsobjcloop = tsobjcloop + 1
        End If
        
        If InStr(1, tscript, "mesh(", 0) Then
            cmesh = cmesh + 1
            tmp = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
            'Set nodX = TreeView1.Nodes.Add((tsobjcloop - 1) & "ts", tvwChild, cmesh & "mesh", "mesh : " & tmp)
            ReDim Preserve Mesha(cmesh)
            ReDim Preserve Mesht(cmesh)
            ReDim Preserve Meshpatha(cmesh)
            ReDim Preserve meshtexture(cmesh)
            ReDim Preserve forcewireframe(cmesh)
            ReDim Preserve beatscale(cmesh)
            ReDim Preserve videomapped(cmesh)
            ReDim Preserve blendmode(cmesh)
            ReDim Preserve blend(cmesh)
            
            colour(cmesh - 1) = RGB(255, 255, 255)
            Mesha(cmesh - 1) = tsobjcloop - 1
            If InStr(1, tscript, "3ds", 0) Then
                Mesht(cmesh - 1) = 1
            End If
            If InStr(1, tscript, "text", 0) Then
                Mesht(cmesh - 1) = 2
                
            End If
            If InStr(1, tscript, "oscilloscope", 0) Then
                Mesht(cmesh - 1) = 3
            End If
        End If
        
        If InStr(1, tscript, "location(", 0) Then
            tmp = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
            'Set nodX = TreeView1.Nodes.Add(cmesh & "mesh", tvwChild, "location" & cmesh, tmp)
            Meshpatha(cmesh - 1) = tmp
            
            uin = uin + 1
        End If
        
        If InStr(1, tscript, "position(", 0) Then
            tmp = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
            tmper = Mid(tmp, 1, (InStr(1, tmp, " ", 1) - 1))
            tmp = Mid(tmp, (InStr(1, tmp, " ", 1) + 1), Len(tmp))
            meshpos(cmesh - 1, 0) = tmper
            tmper = Mid(tmp, 1, (InStr(1, tmp, " ", 1) - 1))
            tmp = Mid(tmp, (InStr(1, tmp, " ", 1) + 1), Len(tmp))
            meshpos(cmesh - 1, 1) = tmper
            meshpos(cmesh - 1, 2) = tmp
        End If
        If InStr(1, tscript, "rotation(", 0) Then
            tmp = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
            tmper = Mid(tmp, 1, (InStr(1, tmp, " ", 1) - 1))
            tmp = Mid(tmp, (InStr(1, tmp, " ", 1) + 1), Len(tmp))
            meshrot(cmesh - 1, 0) = tmper
            tmper = Mid(tmp, 1, (InStr(1, tmp, " ", 1) - 1))
            tmp = Mid(tmp, (InStr(1, tmp, " ", 1) + 1), Len(tmp))
            meshrot(cmesh - 1, 1) = tmper
            tmper = Mid(tmp, 1, (InStr(1, tmp, " ", 1) - 1))
            tmp = Mid(tmp, (InStr(1, tmp, " ", 1) + 1), Len(tmp))
            meshrot(cmesh - 1, 2) = tmper
            meshrot(cmesh - 1, 3) = tmp
            
            uin = uin + 1
        End If
        If InStr(1, tscript, "bindtexture(", 0) Then
            tmp = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
            meshtexture(cmesh - 1) = tmp
            uin = uin + 1
        End If
        If InStr(1, tscript, "locktocamera(", 0) Then
            uin = uin + 1
        End If
        If InStr(1, tscript, "blend(", 0) Then
            blend(cmesh - 1) = 1
            uin = uin + 1
        End If
        If InStr(1, tscript, "beatscale(", 0) Then
            beatscale(cmesh - 1) = 1
            tmp = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
            
            uin = uin + 1
        End If
        If InStr(1, tscript, "fftscale(", 0) Then
            tmp = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
            
            uin = uin + 1
        End If
        If InStr(1, tscript, "forcewireframe(", 0) Then
            forcewireframe(cmesh - 1) = 1
        End If
        
        If InStr(1, tscript, "applyvideomap(", 0) Then
            videomapped(cmesh - 1) = 1
        End If
        
        If InStr(1, tscript, "text(", 0) Then
            textstring(cmesh - 1) = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
        End If
        
        If InStr(1, tscript, "texttype(", 0) Then
            txttype(cmesh - 1) = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
        End If
        If InStr(1, tscript, "font(", 0) Then
            tfont(cmesh - 1) = Val(Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1)))
        End If
        If InStr(1, tscript, "fontsize(", 0) Then
            tfontsize(cmesh - 1) = Val(Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1)))
        End If
        If InStr(1, tscript, "colour(", 0) Then
            tmp = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
            tC(0) = Mid(tmp, 1, (InStr(1, tmp, " ", 1) - 1))
            tmp = Mid(tmp, (InStr(1, tmp, " ", 1) + 1), Len(tmp))
            tC(1) = Mid(tmp, 1, (InStr(1, tmp, " ", 1) - 1))
            tC(2) = Mid(tmp, (InStr(1, tmp, " ", 1) + 1), Len(tmp))
            colour(cmesh - 1) = RGB(tC(0), tC(1), tC(2))
        End If
        
    Loop
Close #1
meshcount = cmesh
   
End Sub

Private Sub loadvidlib()
    Dim vlc As Integer
    Dim tmp As String
    vlc = 0
    Open "../lib/vidlib.okot" For Input As #1
    Do While Not EOF(1)
        Line Input #1, tscript
        ReDim Preserve tvidlib(vlc)
        ReDim Preserve tvidfolder(vlc)
        
            tvidlib(vlc) = Mid(tscript, 1, (InStr(1, tscript, ";", 1) - 1))
            tmp = Mid(tscript, InStr(1, tscript, ";", 1) + 1, Len(tscript) - (InStr(1, tscript, ";", 1) + 1))
            tvidfolder(vlc) = Mid(tmp, 1, (InStr(1, tmp, ";", 1) - 1))
        vlc = vlc + 1
    Loop
Close #1
For I = 0 To UBound(tvidlib)
  List1.AddItem tvidlib(I), I
Next I
End Sub



Private Sub Form_Unload(Cancel As Integer)
      BASS_RecordFree
End Sub

Private Sub fxswitches_Click(Index As Integer)
    
    If Index = 0 Then
        If forcewireframe(currentmesh) = 1 Then
            fxswitches(Index).Picture = buttonup.Picture
            forcewireframe(currentmesh) = 0
        Else
            fxswitches(Index).Picture = buttondown.Picture
            forcewireframe(currentmesh) = 1
        End If
        If winsock1.State = sckConnected Then
            winsock1.SendData "forcewireframe(" & currentmesh & ")"
        End If
    End If
    If Index = 1 Then
        If beatscale(currentmesh) = 1 Then
            fxswitches(Index).Picture = buttonup.Picture
            beatscale(currentmesh) = 0
        Else
            fxswitches(Index).Picture = buttondown.Picture
            beatscale(currentmesh) = 1
        End If
        If winsock1.State = sckConnected Then
            winsock1.SendData "beatscale(" & currentmesh & ")"
        End If
    End If
    If Index = 2 Then
        If videomapped(currentmesh) = 1 Then
            fxswitches(Index).Picture = buttonup.Picture
            videomapped(currentmesh) = 0
        Else
            fxswitches(Index).Picture = buttondown.Picture
            videomapped(currentmesh) = 1
        End If
        If winsock1.State = sckConnected Then
            winsock1.SendData "videomapped(" & currentmesh & ")"
        End If
    End If
    If Index = 3 Then
        If blend(currentmesh) = 1 Then
            fxswitches(Index).Picture = buttonup.Picture
            blend(currentmesh) = 0
        Else
            fxswitches(Index).Picture = buttondown.Picture
            blend(currentmesh) = 1
        End If
        If winsock1.State = sckConnected Then
            winsock1.SendData "blend(" & currentmesh & ")"
        End If
    End If
    
End Sub

Private Sub getinfo_Timer()
    If winsock1.State = sckConnected Then
     winsock1.SendData "getsys()"
    End If
End Sub



Private Sub Label2_Click()
animate.Visible = False
End Sub
    
Private Sub keyboard_Click()

    Load mykeys
    mykeys.Show
    

End Sub

Private Sub lfeed_Click()
    If winsock1.State = sckConnected Then
        winsock1.SendData "loadfeed(" & currentvid & ")"
    End If
    lfeed.Enabled = False
    lfeedslot = currentvid
    lfeedenabled = 1
    vidhold(currentvid).Picture = lfeedimg.Picture
    vidselect.Visible = False
    loadedvid(currentvid) = 1
End Sub

Private Sub List1_Click()
    vidselect.Visible = False
    vidhold(currentvid).Picture = LoadPicture("../lib/vid/" & tvidfolder(List1.ListIndex) & "/0.oko")
    loading(currentvid).Visible = True
    If winsock1.State = sckConnected Then
        winsock1.SendData "loadvid(" & List1.ListIndex & " " & currentvid & ")"
    End If
    loadedvid(currentvid) = 1
    vidset(currentvid) = List1.ListIndex
    loadingvid = currentvid
    loadingvidok = 1
End Sub

Private Sub mbeat_Click()
    If mmbeat(currentfx) = 1 Then
        mbeat.Picture = mbeatof.Picture
        mmbeat(currentfx) = 0
    Else
        mbeat.Picture = mbeaton.Picture
        mmbeat(currentfx) = 1
    End If
    If winsock1.State = sckConnected Then
        winsock1.SendData "meshbeat(" & currentfx & ")"
    End If
End Sub

    Private Sub midi_Click()
        Load frmMidi
        frmMidi.Show
    End Sub

Private Sub multi_Click()
If multi.Checked = True Then
    multi.Checked = False
    host = "192.168.0.10"
Else
    multi.Checked = True
    host = "localhost"
End If
End Sub

''''''''''''''video UI stuff
'''''''''''''''''''''''''''''
Private Sub setupvidui()
    For I = 0 To 19
        reset(I).Stretch = True
        reset(I).Picture = blank.Picture
        fwd(I).Stretch = True
        rwd(I).Stretch = True
        rwd(I).Picture = blank.Picture
        pingpong(I).Stretch = True
        pingpong(I).Picture = blank.Picture
        vidman(I).Stretch = True
        vidman(I).Picture = blank.Picture
        underlay(I).Stretch = True
        underlay(I).Picture = blank.Picture
        overlay(I).Stretch = True
        overlay(I).Picture = blank.Picture
        If I < 10 Then
            Vobject(I).Left = (I * 89)
            Vobject(I).top = 0
        Else
            Vobject(I).Left = (I - 10) * 89
            Vobject(I).top = 105
        End If
    Next I
End Sub

Private Sub OptionButton1_Click()

End Sub

Private Sub position_Change(Index As Integer)
    If position(Index).Text = "" Then
        position(Index).Text = 0
    Else
        position(Index).Text = Val(position(Index).Text)
    End If
    
End Sub

Private Sub render_Click(Index As Integer)
        For I = 0 To 3
        render(I).Picture = obuttonup.Picture
    Next I
    render(Index).Picture = obuttondown.Picture
    If winsock1.State = sckConnected Then
        winsock1.SendData "render(" & Index & ")"
    End If
    If autorecord.Caption = "stop" Then
        autoevent(autoframe, 0) = autocount
        autoevent(autoframe, 1) = Index
        autoevent(autoframe, 2) = 3
        autoframe = autoframe + 1
    End If
End Sub

Private Sub sayt_Click()
    Load sayit
    sayit.Show
End Sub

Private Sub sendtext_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    sendtext.Picture = obuttondown.Picture
End Sub

Private Sub sendtext_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
    sendtext.Picture = obuttonup.Picture
    If winsock1.State = sckConnected Then
             winsock1.SendData "text(" & currentmesh & ")(" & textedit.Text & ")"
             textstring(currentmesh) = textedit.Text
    End If
End Sub

Private Sub submit_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
        submit(Index).Picture = obuttondown.Picture
End Sub

Private Sub submit_MouseUp(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
    submit(Index).Picture = obuttonup.Picture
    If Index = 0 Then
       If winsock1.State = sckConnected Then
             winsock1.SendData "meshposition(" & currentmesh & " " & position(0) & " " & position(1) & " " & position(2) & ")"
        End If
        meshpos(currentmesh, 0) = position(0)
        meshpos(currentmesh, 1) = position(1)
        meshpos(currentmesh, 2) = position(2)
    End If
    If Index = 1 Then
        If winsock1.State = sckConnected Then
             winsock1.SendData "meshrotation(" & currentmesh & " " & rotation(0) & " " & rotation(1) & " " & rotation(2) & " " & rotation(3) & ")"
        End If
        meshrot(currentmesh, 0) = rotation(0)
        meshrot(currentmesh, 1) = rotation(1)
        meshrot(currentmesh, 2) = rotation(2)
        meshrot(currentmesh, 3) = rotation(3)
    End If
    If Index = 2 Then
        tfontsize(currentmesh) = fontzize.Text
        If winsock1.State = sckConnected Then
             winsock1.SendData "textsize(" & currentmesh & " " & tfontsize(currentmesh) & ")"
        End If
    End If
    If Index = 3 Then
        CommonDialog1.CancelError = True
        On Error GoTo ErrHandler
        'Set the Flags property
        CommonDialog1.flags = cdlCCRGBInit
        ' Display the Color Dialog box
        CommonDialog1.ShowColor
        ' Set the form's background color to selected color
        thecolor.BackColor = CommonDialog1.color
        colour(currentmesh) = CommonDialog1.color
        Dim lColor, iRed, iGreen, iBlue
        lColor = CommonDialog1.color    'work long
        iRed = lColor Mod &H100  'get red component
        lColor = lColor \ &H100  'divide
        iGreen = lColor Mod &H100 'get green component
        lColor = lColor \ &H100  'divide
        iBlue = lColor Mod &H100 'get blue component
        If winsock1.State = sckConnected Then
             winsock1.SendData "colour(" & currentmesh & " " & iRed & " " & iGreen & " " & iBlue & ")"
        End If
        
        Exit Sub

ErrHandler:

    End If
End Sub

Private Sub sysavi_Click()
    If sysavienabled = 1 Then
        MsgBox "Can not load more than system avi", vbOKOnly, "VIDEO DELETE WARNING"
    Else
        avidir.Visible = True
    End If
End Sub

Private Sub TabStrip1_Change()
currentmesh = TabStrip1.SelectedItem.name
    thecolor.BackColor = colour(currentmesh)
   If TabStrip1.SelectedItem.Caption = "3ds" Then
    textobject.Visible = False
    fontsizet.Visible = False
   End If
        If meshpos(currentmesh, 0) = "" Then
            meshpos(currentmesh, 0) = 0
        End If
        If meshpos(currentmesh, 1) = "" Then
            meshpos(currentmesh, 1) = 0
        End If
        If meshpos(currentmesh, 2) = "" Then
            meshpos(currentmesh, 2) = 0
        End If
        
        position(0).Text = meshpos(currentmesh, 0)
        position(1).Text = meshpos(currentmesh, 1)
        position(2).Text = meshpos(currentmesh, 2)
        
        If meshrot(currentmesh, 0) = "" Then
            meshrot(currentmesh, 0) = 0
        End If
        If meshrot(currentmesh, 1) = "" Then
            meshrot(currentmesh, 1) = 0
        End If
        If meshrot(currentmesh, 2) = "" Then
            meshrot(currentmesh, 2) = 0
        End If
        If meshrot(currentmesh, 3) = "" Then
            meshrot(currentmesh, 3) = 0
        End If
        rotation(0).Text = meshrot(currentmesh, 0)
        rotation(1).Text = meshrot(currentmesh, 1)
        rotation(2).Text = meshrot(currentmesh, 2)
        rotation(3).Text = meshrot(currentmesh, 3)
        
        If forcewireframe(currentmesh) = 1 Then
            fxswitches(0).Picture = buttondown.Picture
        Else
            fxswitches(0).Picture = buttonup.Picture
        End If
        If beatscale(currentmesh) = 1 Then
            fxswitches(1).Picture = buttondown.Picture
        Else
            fxswitches(1).Picture = buttonup.Picture
        End If
        If videomapped(currentmesh) = 1 Then
            fxswitches(2).Picture = buttondown.Picture
        Else
            fxswitches(2).Picture = buttonup.Picture
        End If
        If blend(currentmesh) = 1 Then
            fxswitches(3).Picture = buttondown.Picture
        Else
            fxswitches(3).Picture = buttonup.Picture
        End If
          
        ''blendmode (currentmesh)
        meshobject.Visible = True
        
        
        meshpath.Caption = Meshpatha(TabStrip1.SelectedItem.name)
        textpath.Caption = meshtexture(TabStrip1.SelectedItem.name)
        If InStr(1, meshtexture(TabStrip1.SelectedItem.name), ":", 0) Then
            On Error Resume Next
            textdis = LoadPicture(meshtexture(TabStrip1.SelectedItem.name))
        Else
            On Error Resume Next
            textdis = LoadPicture("../" & meshtexture(TabStrip1.SelectedItem.name))
        End If
   
   If TabStrip1.SelectedItem.Caption = "text" Then
    textedit.Text = textstring(currentmesh)
    texttype.Caption = txttype(currentmesh)
    fontz.Selected(tfont(currentmesh)) = True
    fontzize.Text = tfontsize(currentmesh)
    fontsizet.Visible = True
    textobject.Visible = True
   End If
   If TabStrip1.SelectedItem.Caption = "oscil" Then
    meshobject.Visible = False
    textobject.Visible = False
    fontsizet.Visible = False
   End If
End Sub

Private Sub vfx_Click(Index As Integer)
    
    If vidtofx(currentfx, Index) = 1 Then
        vfx(Index).Picture = vidfxon.Picture
        vidtofx(currentfx, Index) = 0
    Else
        vfx(Index).Picture = vidfxoff.Picture
        vidtofx(currentfx, Index) = 1
    End If
    If winsock1.State = sckConnected Then
            winsock1.SendData "vidtofx(" & currentfx & " " & Index & ")"
    End If
    
End Sub
Private Sub vidlib_Click()
    '' populate the list box with the data from the vidlibarray in masterclient form
    vidbuts.Visible = False
    
End Sub
Private Sub vidman_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
    If vidselect.Visible = False Then
        vidman(Index).Picture = tvidman.Picture
    End If
End Sub
Private Sub vidman_MouseUp(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
    Dim msg, Style, Title, Response
    msg = "Do you want to delete this video  ?"   ' Define message.
    Style = vbYesNo + vbCritical + vbDefaultButton2 ' Define buttons.
    Title = "VIDEO DELETE WARNING"  ' Define title.
    If loadingvidok <> 1 Then
       If vidselect.Visible = False Then
            vidman(Index).Picture = blank.Picture
            If sysavislot = Index And sysavienabled = 1 Then
                Response = MsgBox(msg, Style, Title)
                If Response = vbYes Then
                    If winsock1.State = sckConnected Then
                       winsock1.SendData "sysavi(" & Index & ")(" & avidir.FileName & ")"
                    End If
                    vidhold(Index).Picture = blank.Picture
                    sysavienabled = 0
                    loadedvid(Index) = 0
                End If
            ElseIf lfeedslot = Index And lfeedenabled = 1 Then
                Response = MsgBox(msg, Style, Title)
                If Response = vbYes Then
                    If winsock1.State = sckConnected Then
                       winsock1.SendData "loadfeed(" & Index & ")"
                    End If
                    vidhold(Index).Picture = blank.Picture
                    lfeedenabled = 0
                    lfeed.Enabled = True
                    loadedvid(Index) = 0
                End If
            ElseIf loadedvid(Index) = 1 Then
                Response = MsgBox(msg, Style, Title)
                If Response = vbYes Then
                    '' this needs to loop through all items that the video is connect to and alert that they have to be deleted
                    
                    vidhold(Index).Picture = blank.Picture
                    loadedvid(Index) = 0
                    If winsock1.State = sckConnected Then
                        winsock1.SendData "deletevid(" & vidset(Index) & " vbYesNo + vbCritical + vbDefaultButton2 " & Index & ")"
                    End If
                    
                End If
            Else
                vidbuts.Visible = True
                vidselect.Visible = True
                currentvid = Index
            End If
        End If
    Else
        MsgBox "a video loading : wait until it finishes, to load or unload a video", , "VIDEO WARNING"
    End If
End Sub
Private Sub reset_MouseDown(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
If loadedvid(Index) = 1 Then
    reset(Index).Picture = treset.Picture
End If
End Sub

Private Sub reset_MouseUp(Index As Integer, Button As Integer, Shift As Integer, x As Single, y As Single)
If loadedvid(Index) = 1 Then
    reset(Index).Picture = blank.Picture
    If winsock1.State = sckConnected Then
        winsock1.SendData "resetframe(" & Index & ")"
    End If
End If
End Sub

Public Sub clicktrans(Index As Integer)
    overlay_Click Index
End Sub

Public Sub resetk(Index As Integer)
    reset_MouseDown Index, 0, 0, 1, 1
    reset_MouseUp Index, 0, 0, 1, 1
End Sub

Private Sub overlay_Click(Index As Integer)
    If loadedvid(Index) = 1 Then
    If over(Index) = 1 Then
        overlay(Index).Picture = blank.Picture
        over(Index) = 0
    Else
        overlay(Index).Picture = toverlay.Picture
        over(Index) = 1
    End If
    If winsock1.State = sckConnected Then
        winsock1.SendData "overlay(" & Index & ")"
    End If
    
    
    If autorecord.Caption = "stop" Then
        autoevent(autoframe, 0) = autocount
        autoevent(autoframe, 1) = Index
        autoevent(autoframe, 2) = 4
        autoframe = autoframe + 1
    End If
    End If
End Sub

Private Sub underlay_Click(Index As Integer)
If loadedvid(Index) = 1 Then
    If under(Index) = 1 Then
        underlay(Index).Picture = blank.Picture
        under(Index) = 0
    Else
        underlay(Index).Picture = tunderlay.Picture
        under(Index) = 1
    End If
    If winsock1.State = sckConnected Then
        winsock1.SendData "underlay(" & Index & ")"
    End If
    If autorecord.Caption = "stop" Then
        autoevent(autoframe, 0) = autocount
        autoevent(autoframe, 1) = Index
        autoevent(autoframe, 2) = 5
        autoframe = autoframe + 1
    End If
    End If
End Sub
Private Sub fwd_Click(Index As Integer)
    If loadedvid(Index) = 1 Then
    fwd(Index).Picture = tfwd.Picture
    rwd(Index).Picture = blank.Picture
    pingpong(Index).Picture = blank.Picture
    If winsock1.State = sckConnected Then
        winsock1.SendData "pingpong(" & Index & " 0)"
    End If
    End If
End Sub

Private Sub pingpong_Click(Index As Integer)
   If loadedvid(Index) = 1 Then
    pingpong(Index).Picture = tpong.Picture
    fwd(Index).Picture = blank.Picture
    rwd(Index).Picture = blank.Picture
    If winsock1.State = sckConnected Then
        winsock1.SendData "pingpong(" & Index & " 2)"
    End If
    End If
End Sub

Private Sub rwd_Click(Index As Integer)
    If loadedvid(Index) = 1 Then
        pingpong(Index).Picture = blank.Picture
        fwd(Index).Picture = blank.Picture
        rwd(Index).Picture = trwd.Picture
        If winsock1.State = sckConnected Then
            winsock1.SendData "pingpong(" & Index & " 1)"
        End If
    End If
End Sub
''''''''''''''''''''''''''''''''''''''''''''''
Private Sub tmrLiveSpec_Timer()
    ''Call UpdateSpectrum(0, 0, 0, 0, 0)
End Sub

Private Sub TreeView1_NodeClick(ByVal Node As MSComctlLib.Node)
       Dim nod
   Dim fg
   '' access the nodedata
       
      If InStr(1, Node.Key, "ts", 1) Then
             If Node.Image = 2 Then
                Node.Image = 1
             ElseIf Node.Image = 1 Then
                Node.Image = 2
             End If
      If winsock1.State = sckConnected Then
             winsock1.SendData "effect(" & Val(Node.Key) & ")"
      End If
      '' record data
      
   End If
   
   If autorecord.Caption = "stop" Then
        autoevent(autoframe, 0) = autocount
        autoevent(autoframe, 1) = Node.Index
        autoevent(autoframe, 2) = 1
        autoframe = autoframe + 1
   End If
      
   currentfx = Val(Node.Key)
   If InStr(1, Node.Key, "tedit", 1) Then
        ''animate.Visible = False
        displayfx Node.Index
        currentfx = Val(Node.Parent.Key)
   End If
End Sub

Public Sub displayfx(nod As Integer)
    fxtitle.Caption = "FX selected : " & TreeView1.Nodes(nod).Parent.Text
    For I = 0 To 19
        If vidtofx(currentfx, I) = 1 Then
            vfx(I).Picture = vidfxoff.Picture
        Else
            vfx(I).Picture = vidfxon.Picture
        End If
    Next I
    TabStrip1.Tabs.Clear
        
    For I = 0 To UBound(Mesha)
        If Mesha(I) = currentfx Then
            If Mesht(I) = 1 Then
                TabStrip1.Tabs.Add I, "3ds", 0
            End If
            If Mesht(I) = 2 Then
                TabStrip1.Tabs.Add I, "text", 0
            End If
            If Mesht(I) = 3 Then
                TabStrip1.Tabs.Add I, "oscil", 0
            End If
        End If
    Next I
    If mmbeat(currentfx) = 1 Then
        mbeat.Picture = mbeaton.Picture
    Else
        mbeat.Picture = mbeatof.Picture
    End If
End Sub

Private Sub window_Click()

End Sub

Private Sub winsock1_DataArrival(ByVal bytesTotal As Long)
    Dim line As String
    Dim tmper
    Dim tmp
    Dim mem0
    Dim mem1
    winsock1.GetData line
    If InStr(1, line, "vidloaded", 0) Then
         loading(loadingvid).Visible = False
         loadingvidok = 0
    Else
        '' parse the sys info and make it gui able
        
        tmper = Mid(line, 1, (InStr(1, line, " ", 1) - 1))
        tmp = Mid(line, InStr(1, line, " ", 1) + 1, Len(line))
        
        mem0 = Val(tmper)
        tmper = Mid(tmp, 1, (InStr(1, tmp, " ", 1) - 1))
        mem1 = Val(tmper)
        membar(0).Width = (mbar(0) / 100) * mem0
        membar(1).Width = (mbar(1) / 100) * mem1
    End If
End Sub


Private Sub wq_Click()
    host = "192.168.0.11"
End Sub
