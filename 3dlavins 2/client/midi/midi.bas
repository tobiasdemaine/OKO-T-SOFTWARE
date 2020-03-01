Attribute VB_Name = "midi"
Option Explicit

' *** my variables ***
' midi out
Public hMidiOUT As Long             ' handle midi out port
Public mMPU401OUT As Long           ' roland mpu401 out device
Public midiMessageOut As Long       ' short message status byte
Public midiData1 As Long            ' short message data byte
Public midiData2 As Long            ' short message data byte
Public CurChannel As Integer        ' short msg channel/part sequence 0-15

' midi in
Public hMidiIN As Long              ' only used for midi thru
Public mMPU401IN As Long            ' roland mpu401 in device

Public offarray(300) As String
Public onarray(300) As String
Public ifswitch(300)
Public ifswitchtest(300)
' *** API ***
' general
Declare Function SetWindowPos Lib "user32" (ByVal hwnd As Long, ByVal hWndInsertAfter As Long, ByVal X As Long, ByVal Y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long) As Long
Public Const SWP_NOMOVE = &H2
Public Const SWP_NOSIZE = &H1
Public Const HWND_NOTOPMOST = -2
Public Const HWND_TOPMOST = -1

Declare Function BitBlt Lib "gdi32" (ByVal hDestDC As Long, ByVal X As Long, ByVal Y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hSrcDC As Long, ByVal xSrc As Long, ByVal ySrc As Long, ByVal dwRop As Long) As Long
Public Const SRCCOPY = &HCC0020     ' (DWORD) dest = source

' midi
Public Const MAXPNAMELEN = 32       '  max product name length (including NULL)

Type MIDIINCAPS
        wMid As Integer
        wPid As Integer
        vDriverVersion As Long
        szPname As String * MAXPNAMELEN
End Type
Type MIDIOUTCAPS
        wMid As Integer
        wPid As Integer
        vDriverVersion As Long
        szPname As String * MAXPNAMELEN
        wTechnology As Integer
        wVoices As Integer
        wNotes As Integer
        wChannelMask As Integer
        dwSupport As Long
End Type

' MIDI API Functions for Windows 95
Declare Function midiConnect Lib "winmm.dll" (ByVal hmi As Long, ByVal hmo As Long, pReserved As Any) As Long
Declare Function midiDisconnect Lib "winmm.dll" (ByVal hmi As Long, ByVal hmo As Long, pReserved As Any) As Long
Declare Function midiInClose Lib "winmm.dll" (ByVal hMidiIN As Long) As Long
Declare Function midiInGetDevCaps Lib "winmm.dll" Alias "midiInGetDevCapsA" (ByVal uDeviceID As Long, lpCaps As MIDIINCAPS, ByVal uSize As Long) As Long
Declare Function midiInGetErrorText Lib "winmm.dll" Alias "midiInGetErrorTextA" (ByVal err As Long, ByVal lpText As String, ByVal uSize As Long) As Long
Declare Function midiInGetNumDevs Lib "winmm.dll" () As Long
Declare Function midiInOpen Lib "winmm.dll" (lphMidiIn As Long, ByVal uDeviceID As Long, ByVal dwCallback As Long, ByVal dwInstance As Long, ByVal dwFlags As Long) As Long
Declare Function midiInReset Lib "winmm.dll" (ByVal hMidiIN As Long) As Long
Declare Function midiInStart Lib "winmm.dll" (ByVal hMidiIN As Long) As Long
Declare Function midiInStop Lib "winmm.dll" (ByVal hMidiIN As Long) As Long
Declare Function midiOutClose Lib "winmm.dll" (ByVal hMidiOUT As Long) As Long
Declare Function midiOutGetDevCaps Lib "winmm.dll" Alias "midiOutGetDevCapsA" (ByVal uDeviceID As Long, lpCaps As MIDIOUTCAPS, ByVal uSize As Long) As Long
Declare Function midiOutGetErrorText Lib "winmm.dll" Alias "midiOutGetErrorTextA" (ByVal err As Long, ByVal lpText As String, ByVal uSize As Long) As Long
Declare Function midiOutGetNumDevs Lib "winmm" () As Integer
Declare Function midiOutMessage Lib "winmm.dll" (ByVal hMidiOUT As Long, ByVal msg As Long, ByVal dw1 As Long, ByVal dw2 As Long) As Long
Declare Function midiOutOpen Lib "winmm.dll" (lphMidiOut As Long, ByVal uDeviceID As Long, ByVal dwCallback As Long, ByVal dwInstance As Long, ByVal dwFlags As Long) As Long
Declare Function midiOutReset Lib "winmm.dll" (ByVal hMidiOUT As Long) As Long
Declare Function midiOutShortMsg Lib "winmm.dll" (ByVal hMidiOUT As Long, ByVal dwMsg As Long) As Long

Public Const MMSYSERR_NOERROR = 0               '  no error

Public Const CALLBACK_NULL = &H0                '  no callback
Public Const CALLBACK_FUNCTION = &H30000        '  dwCallback is a FARPROC

Public Const MM_MIM_OPEN = &H3C1                '  MIDI input
Public Const MM_MIM_CLOSE = &H3C2
Public Const MM_MIM_DATA = &H3C3
Public Const MM_MIM_LONGDATA = &H3C4
Public Const MM_MIM_ERROR = &H3C5
Public Const MM_MIM_LONGERROR = &H3C6

' MIDI status messages
Public Const NOTE_OFF = &H80
Public Const NOTE_ON = &H90
Public Const POLY_KEY_PRESS = &HA0
Public Const CONTROLLER_CHANGE = &HB0
Public Const PROGRAM_CHANGE = &HC0
Public Const CHANNEL_PRESSURE = &HD0
Public Const PITCH_BEND = &HE0

'MIDI Mapper
Public Const MIDI_MAPPER = -1

'  flags for wTechnology field of MIDIOUTCAPS structure
Public Const MOD_MIDIPORT = 1    '  output port
Public Const MOD_SYNTH = 2       '  generic internal synth
Public Const MOD_SQSYNTH = 3     '  square wave internal synth
Public Const MOD_FMSYNTH = 4     '  FM internal synth
Public Const MOD_MAPPER = 5      '  MIDI mapper

'  flags for dwSupport field of MIDIOUTCAPS
Public Const MIDICAPS_VOLUME = &H1           '  supports volume control
Public Const MIDICAPS_LRVOLUME = &H2         '  separate left-right volume control
Public Const MIDICAPS_CACHE = &H4

Public Function isNote(ByVal Nr As Long) As String
   Dim octave As Long
   Dim note As String
   octave = (Nr \ 12)
   note = Nr Mod 12
   isNote = Choose(note + 1, "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B") & Format(octave - 1)
End Function

Public Sub MidiIN_Port(ByVal OpenClose As String)
   Dim midiError As Long
   
   If OpenClose = "open" Then
      midiError = midiInOpen(hMidiIN, mMPU401IN, AddressOf MidiIN_Proc, 0, CALLBACK_FUNCTION)
      If midiError <> MMSYSERR_NOERROR Then
         ShowMMErr "midiIN_Open", midiError
         Else
         midiError = midiInStart(hMidiIN)
         If midiError <> MMSYSERR_NOERROR Then ShowMMErr "midiIN_Open-Start", midiError
         End If
      Else
      If hMidiIN <> 0 Then
         midiError = midiInStop(hMidiIN)
         If midiError <> MMSYSERR_NOERROR Then ShowMMErr "midiIN_Open-Stop", midiError
         midiError = midiInClose(hMidiIN)
         If midiError <> MMSYSERR_NOERROR Then ShowMMErr "midiIN_Close", midiError
         hMidiIN = 0
         End If
      End If
End Sub

Public Sub MidiIN_Proc(ByVal hmIN As Long, ByVal wMsg As Long, ByVal dwInstance As Long, ByVal dwParam1 As Long, ByVal dwParam2 As Long)
   Dim txt As String
   Dim Status As Long, OnOff As Long
   Dim NoteNr As Long
   Dim Velocity As Long
   
   On Error Resume Next
   Select Case wMsg
      Case MM_MIM_OPEN: txt = "open"
      Case MM_MIM_CLOSE: txt = "close"
      Case MM_MIM_DATA:
         Status = (dwParam1 Mod 256)
         If Status < &HF0 Then
            Select Case (Status \ 16) ' filter 4-bit channel "n"
               Case &H8, &H9
                  NoteNr = ((dwParam1 \ 256) Mod 256)
                  Velocity = ((dwParam1 \ (256 ^ 2)) Mod 256)
                  OnOff = IIf(Velocity = 0 Or Status = &H80, 0, 1)
                  txt = txt & "Status : Note " & IIf(OnOff = 0, "Off", "On") & vbCrLf
                  txt = txt & "NoteNr : " & isNote(NoteNr) & vbCrLf
                  txt = txt & "Velo   :" & Str(Velocity)
                  frmMidi.ShowNote NoteNr, OnOff
                  Dim wss
                 '   On Error Resume Next
                 
                    If ifswitch(NoteNr) = "on" Then
                        If ifswitchtest(NoteNr) = 3 Or ifswitchtest(NoteNr) > 3 Then
                            ' insert double counter in here
                            frmMidi.sockit = offarray(NoteNr)
                            ifswitchtest(NoteNr) = 0
                        Else
                            frmMidi.sockit = onarray(NoteNr)
                            ifswitchtest(NoteNr) = ifswitchtest(NoteNr) + 1
                        End If
                    Else
                        If OnOff = 1 Then
                            'If onarray(note) <> "" Then
                            'wss =
                            frmMidi.sockit = onarray(NoteNr) 'wss
                           ' End If
                        Else
                            'If offarray(note) <> "" Then
                            'wss =
                            frmMidi.sockit = offarray(NoteNr) 'wss
                            'End If
                        End If
                    End If
                
               Case &HB
                  txt = "Status : Controller Change"
               Case &HC
                  txt = "Status : Program Change"
               Case &HE
                  txt = "Status : Bender Change"
            End Select
            midiOutShortMsg hMidiOUT, dwParam1 ' send data = Thru-function
            End If
      Case MM_MIM_LONGDATA: txt = "longdata" & " " & Hex(dwParam1) & " " & Hex(dwParam2)
      Case MM_MIM_ERROR: txt = "error" & " " & Hex(dwParam1) & " " & Hex(dwParam2)
      Case MM_MIM_LONGERROR: txt = "longerror"
      Case Else: txt = "???"
   End Select
   If txt <> "" Then frmMidi.lblMidiInfo.Caption = "Midi IN " & vbCrLf & txt
   
End Sub

Public Sub MidiOUT_Port(ByVal OpenClose As String)
   Dim midiError As Long
      
   If OpenClose = "open" Then
      If mMPU401OUT = 256 Then frmDevCap.Show 1
      midiError = midiOutOpen(hMidiOUT, mMPU401OUT, vbNull, 0, CALLBACK_NULL)
      If midiError <> MMSYSERR_NOERROR Then ShowMMErr "midiOUT_Open", midiError
      Else
      If hMidiOUT <> 0 Then
         midiError = midiOutClose(hMidiOUT)
         hMidiOUT = 0
         If midiError <> MMSYSERR_NOERROR Then ShowMMErr "midiOUT_Close", midiError
         End If
      End If
End Sub

' this function only works when no midiIn port opened yet
Public Sub MidiTHRU_Port(ByVal OpenClose As String)
   Dim midiError As Long
   
   If OpenClose = "open" Then
      If hMidiOUT = 0 Then MidiOUT_Port "open"
      If hMidiOUT = 0 Then Exit Sub
      midiError = midiInOpen(hMidiIN, mMPU401IN, 0, 0, CALLBACK_NULL)
      If midiError <> MMSYSERR_NOERROR Then
         ShowMMErr "midiTHRU_Open", midiError
         Else
         midiError = midiConnect(hMidiIN, hMidiOUT, 0)
         If midiError <> MMSYSERR_NOERROR Then ShowMMErr "midiConnect", midiError
         midiError = midiInStart(hMidiIN)
         End If

      Else
      If hMidiIN <> 0 Then
         midiError = midiInStop(hMidiIN)
         If hMidiOUT <> 0 Then
            midiError = midiDisconnect(hMidiIN, hMidiOUT, 0)
            If midiError <> MMSYSERR_NOERROR Then ShowMMErr "midiDisconnect", midiError
            End If
         midiError = midiInClose(hMidiIN)
         If midiError <> MMSYSERR_NOERROR Then ShowMMErr "midiTHRU_Close", midiError
         End If
      End If
End Sub

Public Sub SendMidiShortOut()
    Dim midiMessage As Long
    Dim lowint As Long, highint As Long
    
    'Pack MIDI message data into 4 byte long integer
    lowint = (midiData1 * 256) + midiMessageOut
    highint = (midiData2 * 256) * 256
    midiMessage = lowint + highint
    'Windows MIDI API function
    midiOutShortMsg hMidiOUT, midiMessage
End Sub

Public Sub ShowMMErr(InFunct As String, MMErr)
   Dim msg As String
   
   msg = String(255, " ")
   If InStr(1, InFunct, "out", vbTextCompare) = 0 Then
      midiInGetErrorText MMErr, msg, 255
      Else
      midiOutGetErrorText MMErr, msg, 255
      End If
   msg = InFunct & vbCrLf & msg & vbCrLf
   MsgBox msg
End Sub

