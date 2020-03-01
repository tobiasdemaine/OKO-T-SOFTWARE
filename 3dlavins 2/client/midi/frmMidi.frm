VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmMidi 
   BackColor       =   &H00404040&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "OKO T MIDI interface "
   ClientHeight    =   1710
   ClientLeft      =   6300
   ClientTop       =   9315
   ClientWidth     =   7965
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1710
   ScaleWidth      =   7965
   Begin VB.OptionButton optPorts 
      BackColor       =   &H00808080&
      Caption         =   "Connect to synth"
      Height          =   360
      Index           =   3
      Left            =   120
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   0
      Width           =   2535
   End
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      BackColor       =   &H00808080&
      ForeColor       =   &H80000008&
      Height          =   1215
      Left            =   2745
      ScaleHeight     =   1185
      ScaleWidth      =   5145
      TabIndex        =   4
      Top             =   0
      Width           =   5175
      Begin VB.CheckBox tswitch 
         BackColor       =   &H00808080&
         Caption         =   "use as two hit switch"
         Height          =   345
         Left            =   3240
         Style           =   1  'Graphical
         TabIndex        =   15
         Top             =   795
         Width           =   1815
      End
      Begin VB.CommandButton savefile 
         Caption         =   "save"
         Height          =   255
         Left            =   720
         TabIndex        =   14
         Top             =   0
         Width           =   735
      End
      Begin VB.CommandButton openfile 
         Caption         =   "open"
         Height          =   255
         Left            =   0
         TabIndex        =   13
         Top             =   0
         Width           =   735
      End
      Begin VB.CommandButton Command1 
         BackColor       =   &H00808080&
         Caption         =   "assign to key"
         Height          =   375
         Left            =   3240
         TabIndex        =   12
         Top             =   360
         Width           =   1815
      End
      Begin VB.TextBox codeoff 
         Appearance      =   0  'Flat
         BackColor       =   &H00C0C0C0&
         Height          =   285
         Left            =   840
         TabIndex        =   9
         Top             =   840
         Width           =   1935
      End
      Begin VB.TextBox codeon 
         Appearance      =   0  'Flat
         BackColor       =   &H00C0C0C0&
         Height          =   285
         Left            =   840
         TabIndex        =   6
         Top             =   480
         Width           =   1935
      End
      Begin VB.Label Label3 
         BackStyle       =   0  'Transparent
         Caption         =   "off code"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   11
         Top             =   840
         Width           =   735
      End
      Begin VB.Label Label3 
         BackStyle       =   0  'Transparent
         Caption         =   "on code"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   10
         Top             =   480
         Width           =   735
      End
      Begin VB.Line Line1 
         X1              =   0
         X2              =   5160
         Y1              =   240
         Y2              =   240
      End
      Begin VB.Label lblMseNote 
         BackColor       =   &H00C0C0C0&
         Height          =   255
         Left            =   4560
         TabIndex        =   5
         Top             =   0
         Width           =   585
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         BackColor       =   &H00C0C0C0&
         Caption         =   "current key "
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   0
         TabIndex        =   8
         Top             =   0
         Width           =   4560
      End
      Begin VB.Label Label1 
         BackStyle       =   0  'Transparent
         Caption         =   "3dlavins code"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   105
         TabIndex        =   7
         Top             =   240
         Width           =   1365
      End
   End
   Begin VB.PictureBox picKlav 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H00404040&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   45
      MousePointer    =   10  'Up Arrow
      ScaleHeight     =   25
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   525
      TabIndex        =   2
      Top             =   1320
      Width           =   7875
      Begin MSComDlg.CommonDialog CommonDialog1 
         Left            =   6945
         Top             =   0
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
      End
      Begin VB.Timer Timer1 
         Interval        =   1
         Left            =   7440
         Top             =   30
      End
   End
   Begin VB.CommandButton cmdAllNotesOff 
      Caption         =   "All Notes Off"
      Height          =   270
      Left            =   0
      Style           =   1  'Graphical
      TabIndex        =   0
      ToolTipText     =   "All Notes Off"
      Top             =   3840
      UseMaskColor    =   -1  'True
      Width           =   1065
   End
   Begin VB.Label lblMidiInfo 
      Appearance      =   0  'Flat
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   " Midi INFO"
      ForeColor       =   &H80000008&
      Height          =   855
      Left            =   120
      TabIndex        =   1
      Top             =   360
      Width           =   2535
   End
End
Attribute VB_Name = "frmMidi"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' this is the main startup form
Option Explicit
Dim CurKeyID As Long          ' remember note on for note off
Dim send As Boolean
Dim currentnote
Public sockit As String

' generate piano klavier in picture
Public Sub MakePiano(pic As PictureBox)
   Dim wX1 As Long, wY1 As Long
   Dim wdX As Long, wdY As Long
   Dim zX1 As Long, zY1 As Long
   Dim zdX As Long, zdY As Long
   Dim AaWTs As Long                   ' count white keys
   Dim I As Long                       ' counter
   
   wX1 = 0: wY1 = 0: wdX = 7: wdY = 22 ' witte toets
   zX1 = 5: zY1 = 0: zdX = 4: zdY = 16 ' zwarte

   AaWTs = (128 / 12) * 7

   pic.Width = AaWTs * wdX * 15
   pic.AutoRedraw = True
   
   ' make 1st white key & copy other white keys
   pic.Line (wX1, wY1)-Step(wdX, wdY), QBColor(15), BF
   pic.Line (wX1, wY1)-Step(wdX, wdY), QBColor(0), B
   For I = 0 To AaWTs - 1
      BitBlt pic.hdc, wX1 + I * wdX, wY1, wdX, wdY + 1, pic.hdc, wX1, wY1, SRCCOPY
   Next I
      
   ' 1st black & copy other
   pic.Line (zX1, zY1)-Step(zdX, zdY), QBColor(0), BF
   For I = 1 To AaWTs - 1
      If Mid("110111", (I Mod 7) + 1, 1) = "1" Then
         BitBlt pic.hdc, zX1 + I * wdX, zY1, zdX + 1, zdY, pic.hdc, zX1, zY1, SRCCOPY
         End If
   Next I
   
   pic.Line (pic.ScaleWidth - 1, wY1)-Step(0, wdY), QBColor(0)
   pic.Picture = pic.Image
   pic.AutoRedraw = False
End Sub


Public Sub ShowNote(ByVal Nr As Long, OnOff As Long)
   Dim octave As Long, note As Long, bw As Long
   Dim x As Long, y As Long, s As Long
   Dim color As Long
   
   octave = (Nr \ 12)
   note = Nr Mod 12
   bw = Choose(note + 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0) ' black or white
   x = octave * 49 + Choose(note + 1, 0, 3, 7, 10, 14, 21, 24, 28, 31, 35, 38, 42, 49)
   If bw = 1 Then
      y = 11: x = x + 3: s = 2 ' black key
      color = IIf(OnOff = 1, QBColor(15), 0)
      Else
      y = 17: x = x + 2: s = 3 ' white key
      color = IIf(OnOff = 1, 0, QBColor(15))
      End If
   picKlav.ForeColor = color
   picKlav.FillColor = color
   picKlav.Line (x, y)-Step(s, s), color, BF
End Sub


Private Sub cmdAllNotesOff_Click()
   If send = False Then Exit Sub
   midiMessageOut = CONTROLLER_CHANGE + CurChannel
   midiData1 = &H7B
   midiData2 = CByte(0)
   SendMidiShortOut
End Sub

Private Sub Command1_Click()
    onarray(currentnote) = codeon
    offarray(currentnote) = codeoff
    If tswitch.Value = 0 Then
        ifswitch(currentnote) = ""
    Else
        ifswitch(currentnote) = "on"
    End If
End Sub


Private Sub Form_Load()

   mMPU401OUT = 256 ' =empty
   mMPU401IN = 256
   CurChannel = 0
   MakePiano picKlav
End Sub

Private Sub Form_Unload(Cancel As Integer)
   MidiIN_Port "close"
   MidiOUT_Port "close"
   
End Sub



Private Sub openfile_Click()
Dim I As Integer, j As Integer

'number of entries in the file for the current list box
Dim iCount As Integer

'temporary variable to hold input data
Dim sTemp As String

'error handler: if the file is not found, the program will not attempt to load data
On Error GoTo Err_Form_Load

CommonDialog1.InitDir = App.Path
'set the filter the *.dat files
CommonDialog1.Filter = "Data files (*.dat)|*.dat"
'hide the read-only check box
CommonDialog1.flags = &H4&
'force the dialog box to prompt for a file to Open
CommonDialog1.Action = 1

'open the DATA_FILE in the program's directory
'For Input means we will be reading from the file
'As #1 means the #1 will be used to refer to the file
Open CommonDialog1.FileName For Input As #1

    'cycle through all list boxes
    For I = 0 To 3 - 1
    
        'read a line
        Line Input #1, sTemp
        
        'this line in the file tells us how many entries exist for the current list box
        iCount = CInt(sTemp)
        
        'cycle through all of these entries
        For j = 1 To iCount
        
            'read a line
            Line Input #1, sTemp
            
            'this is data for a list box, so add it to the current list box
            If I = 0 Then
                If sTemp <> "null" Then
                onarray(j - 1) = sTemp
                Else
                onarray(j - 1) = ""
                End If
            ElseIf I = 1 Then
                If sTemp <> "null" Then
                offarray(j - 1) = sTemp
                Else
                offarray(j - 1) = ""
                End If
             Else
                If sTemp <> "null" Then
                    ifswitch(j - 1) = sTemp
                Else
                    ifswitch(j - 1) = ""
                End If
            
            End If
        Next j
        
        'we have gotten all of the data for this list box
        'move on to the next one or quit if there are no more
        
    Next I
    
    'we are all done loading data so close the file
    
Close #1

'the procedure jumps to this point if the file was not found
Err_Form_Load:
End Sub

Private Sub optPorts_Click(Index As Integer)
   MidiIN_Port "close"
   MidiOUT_Port "close"
   Select Case Index
   Case 0
      lblMidiInfo.Caption = "All ports closed"
   Case 1
      MidiOUT_Port "open"
      lblMidiInfo.Caption = "Mouse input only"
   Case 2
      MidiTHRU_Port "open"
      lblMidiInfo.Caption = "Midi THRU"
   Case 3
      MidiOUT_Port "open"
      MidiIN_Port "open"
   End Select
   send = IIf(Index = 0, False, True)
End Sub

Private Sub picKlav_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
   Dim oct As Long
   Dim No As Long
   Dim mX As Single
   
   oct = x \ 49
   If picKlav.Point(x, y) = 0 And y < 17 Then
      mX = x - 4
      No = oct * 12 + Choose(((mX \ 7) Mod 7) + 1, 1, 3, 5, 6, 8, 10, 11)
      Else
      mX = x
      No = oct * 12 + Choose(((mX \ 7) Mod 7) + 1, 0, 2, 4, 5, 7, 9, 11)
      End If
   
   CurKeyID = No
   
   '' selector
   currentnote = No
   codeon.Text = onarray(No)
   codeoff.Text = offarray(No)
   
   If ifswitch(No) = "" Then
     tswitch.Value = 0
   Else
    tswitch.Value = 1
   End If
   ShowNote No, 1
   lblMseNote.Caption = isNote(No)
   If send = True Then
      midiMessageOut = NOTE_ON + CurChannel
      midiData1 = No
      midiData2 = 120
      SendMidiShortOut
      End If
End Sub

Private Sub picKlav_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
   If send = True Then
      midiMessageOut = NOTE_OFF + CurChannel
      midiData1 = CurKeyID
      midiData2 = 120
      SendMidiShortOut
      End If
   ShowNote CurKeyID, 0
End Sub




Private Sub savefile_Click()
    Dim I As Integer, j As Integer
    
    'error handler: if the file is not found, the program will not attempt to save data
    On Error GoTo Err_Form_Unload
    
    'set the dialog box's starting path to the program's path
    CommonDialog1.InitDir = App.Path
    'set the filter the *.dat files
    CommonDialog1.Filter = "Data files (*.dat)|*.dat"
    'hide the read-only check box
    CommonDialog1.flags = &H4&
    'force the dialog box to prompt for a file to Save As
    CommonDialog1.Action = 1
    
    'open the file
    'For Output means we will be writing to the file
    'As #1 means the #1 will be used to refer to the file
    Open CommonDialog1.FileName For Output As #1
    
        'cycle through all list boxes
        For I = 0 To 3 - 1
        
            'write how many entires there are for the list box
            Print #1, 300
            
            'cycle through all entries in the list box
            '(they are numbered starting with 0)
            For j = 0 To 300 - 1
            
                'write each entry to the file
                
              If I = 0 Then
                    If onarray(j) = "" Then
                        Print #1, "null"
                    Else
                        Print #1, onarray(j)
                    End If
               ElseIf I = 1 Then
                    If offarray(j) = "" Then
                        Print #1, "null"
                    Else
                        Print #1, offarray(j)
                    End If
               Else
                    If ifswitch(j) = "" Then
                        Print #1, "null"
                    Else
                        Print #1, ifswitch(j)
                    End If
                End If
            Next j
            
            'all done with that list box
        Next I
        
        'we are all done writing data so close the file
    Close #1
    
    'the procedure jumps to this point if the file was not found
Err_Form_Unload:
    End Sub

Private Sub Timer1_Timer()
If sockit <> "" Then
masterclient.winsock1.SendData sockit
sockit = ""
End If
End Sub

Private Sub Winsock1_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
MsgBox Description
End Sub
