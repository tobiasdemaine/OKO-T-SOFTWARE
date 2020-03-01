VERSION 5.00
Begin VB.Form frmDevCap 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Devices"
   ClientHeight    =   3285
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3105
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3285
   ScaleWidth      =   3105
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdEigensch 
      Caption         =   "Properties"
      Height          =   465
      Left            =   120
      TabIndex        =   5
      Top             =   2610
      Width           =   1515
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   465
      Left            =   2040
      TabIndex        =   4
      Top             =   2610
      Width           =   885
   End
   Begin VB.ListBox lstIn 
      Height          =   840
      Left            =   90
      TabIndex        =   2
      Top             =   330
      Width           =   2835
   End
   Begin VB.ListBox lstOut 
      Height          =   840
      Left            =   90
      TabIndex        =   0
      Top             =   1530
      Width           =   2835
   End
   Begin VB.Label lbl 
      Caption         =   "IN"
      Height          =   225
      Index           =   1
      Left            =   90
      TabIndex        =   3
      Top             =   120
      Width           =   885
   End
   Begin VB.Label lbl 
      Caption         =   "OUT"
      Height          =   225
      Index           =   0
      Left            =   90
      TabIndex        =   1
      Top             =   1320
      Width           =   885
   End
End
Attribute VB_Name = "frmDevCap"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' this form enumerates the midi devices and lets the user choose
' one of them, suggesting the MPU-401 's
Option Explicit
Dim NumDevsOut As Integer
Dim NumDevsIn As Integer
Dim DevO() As MIDIOUTCAPS
Dim DevI() As MIDIINCAPS

Private Function GetDevInProps() As String
   Dim ID As Integer
   Dim txt As String
   ID = lstIn.ListIndex
   On Error Resume Next
   txt = "Manufacturer identifier: " & Hex(DevI(ID).wMid) & vbCrLf
   On Error Resume Next
   txt = txt & "Product identifier: " & Hex(DevI(ID).wPid) & vbCrLf
   On Error Resume Next
   txt = txt & "Driver version: " & Hex(DevI(ID).vDriverVersion) & vbCrLf
   GetDevInProps = txt
End Function

Private Function GetDevOutProps() As String
   Dim ID As Integer
   Dim txt As String
   ID = lstOut.ListIndex
   On Error Resume Next
   txt = "Manufacturer identifier: " & Hex(DevO(ID).wMid) & vbCrLf
   On Error Resume Next
   txt = txt & "Product identifier: " & Hex(DevO(ID).wPid) & vbCrLf
   On Error Resume Next
   txt = txt & "Driver version: " & Hex(DevO(ID).vDriverVersion) & vbCrLf
   On Error Resume Next
   txt = txt & "Technology:"
   If DevO(ID).wTechnology = MOD_MIDIPORT Then txt = txt & " output port"
   If DevO(ID).wTechnology = MOD_SYNTH Then txt = txt & " generic internal synth"
   If DevO(ID).wTechnology = MOD_SQSYNTH Then txt = txt & " square wave internal synth"
   If DevO(ID).wTechnology = MOD_FMSYNTH Then txt = txt & " FM internal synth"
   If DevO(ID).wTechnology = MOD_MAPPER Then txt = txt & " MIDI mapper"
   txt = txt & vbCrLf
   txt = txt & "Voices: " & Hex(DevO(ID).wVoices) & vbCrLf
   txt = txt & "Notes: " & Hex(DevO(ID).wNotes) & vbCrLf
   txt = txt & "ChannelMask: " & Hex(DevO(ID).wChannelMask) & vbCrLf
   txt = txt & "Support: " & vbCrLf
   If DevO(ID).dwSupport And MIDICAPS_VOLUME = &H1 Then txt = txt & "          volume control" & vbCrLf
   If DevO(ID).dwSupport And MIDICAPS_LRVOLUME = &H2 Then txt = txt & "          separate left-right volume control" & vbCrLf
   If DevO(ID).dwSupport And MIDICAPS_CACHE = &H4 Then txt = txt & "          patch catching" & vbCrLf
   GetDevOutProps = txt
   
End Function

Private Sub cmdEigensch_Click()
   Dim msg As String
   msg = "I N : " & lstIn.List(lstIn.ListIndex) & vbCrLf
   msg = msg & GetDevInProps() & vbCrLf
   msg = msg & "O U T : " & lstOut.List(lstOut.ListIndex) & vbCrLf
   msg = msg & GetDevOutProps() & vbCrLf
   MsgBox msg
End Sub

Private Sub cmdOK_Click()
   Unload Me
End Sub

Private Sub Form_Load()
   Dim I As Long
   Dim midiError As Long
   Dim name As String
   
   ' out devices
   NumDevsOut = midiOutGetNumDevs()
   ReDim DevO(NumDevsOut + 1)
   For I = 0 To NumDevsOut - 1
      midiError = midiOutGetDevCaps(I, DevO(I), 52)
      If midiError <> MMSYSERR_NOERROR Then ShowMMErr "OUTCaps", midiError: Exit Sub
   Next I
   midiError = midiOutGetDevCaps(MIDI_MAPPER, DevO(I), 52)
   For I = 0 To NumDevsOut - 1
      name = Left(DevO(I).szPname, InStr(1, DevO(I).szPname, Chr(0)) - 1)
      lstOut.AddItem name
      If InStr(1, name, "MPU-401") > 0 Then mMPU401OUT = I
   Next I
   name = Left(DevO(I).szPname, InStr(1, DevO(I).szPname, Chr(0)) - 1)
   lstOut.AddItem name
   
   ' in devices
   NumDevsIn = midiInGetNumDevs()
   ReDim DevI(NumDevsIn + 1)
   For I = 0 To NumDevsIn - 1
      midiError = midiInGetDevCaps(I, DevI(I), 52)
      If midiError <> MMSYSERR_NOERROR Then ShowMMErr "INCaps", midiError: Exit Sub
   Next I
   For I = 0 To NumDevsIn - 1
      name = Left(DevI(I).szPname, InStr(1, DevI(I).szPname, Chr(0)) - 1)
      lstIn.AddItem name
      If InStr(1, name, "MPU-401") > 0 Then mMPU401IN = I
   Next I
   On Error Resume Next
   lstOut.ListIndex = mMPU401OUT
   On Error Resume Next
   lstIn.ListIndex = mMPU401IN
   
   ' always on top
   SetWindowPos Me.hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE Or SWP_NOSIZE
   
End Sub




