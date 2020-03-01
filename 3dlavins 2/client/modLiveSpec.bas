Attribute VB_Name = "modLiveSpec"
    Public Type RECT
        Left As Long
        top As Long
        Right As Long
        Bottom As Long
End Type

Public Declare Function SetRect Lib "user32" (lpRect As RECT, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Long
Public Declare Function SetTextColor Lib "gdi32" (ByVal hdc As Long, ByVal crColor As Long) As Long
Public Declare Function SetBkMode Lib "gdi32" (ByVal hdc As Long, ByVal nBkMode As Long) As Long
Public Declare Function DrawText Lib "user32" Alias "DrawTextA" (ByVal hdc As Long, ByVal lpStr As String, ByVal nCount As Long, lpRect As RECT, ByVal wFormat As Long) As Long

Public Const TRANSPARENT = 1
Public Const DT_CENTER = &H1
Public Const DT_VCENTER = &H4
Public Const DT_SINGLELINE = &H20

Public Const BI_RGB = 0&
Public Const DIB_RGB_COLORS = 0& '  color table in RGBs

Public Type BITMAPINFOHEADER '40 bytes
        biSize As Long
        biWidth As Long
        biHeight As Long
        biPlanes As Integer
        biBitCount As Integer
        biCompression As Long
        biSizeImage As Long
        biXPelsPerMeter As Long
        biYPelsPerMeter As Long
        biClrUsed As Long
        biClrImportant As Long
End Type

Public Type RGBQUAD
        rgbBlue As Byte
        rgbGreen As Byte
        rgbRed As Byte
        rgbReserved As Byte
End Type

Public Type BITMAPINFO
        bmiHeader As BITMAPINFOHEADER
        bmiColors(256) As RGBQUAD
End Type

Public Declare Function SetDIBitsToDevice Lib "gdi32" (ByVal hdc As Long, ByVal x As Long, ByVal y As Long, ByVal dx As Long, ByVal dy As Long, ByVal SrcX As Long, ByVal SrcY As Long, ByVal Scan As Long, ByVal NumScans As Long, Bits As Any, BitsInfo As BITMAPINFO, ByVal wUsage As Long) As Long

'NOTE: Using an API timer will sometimes Crash your program
'Public Declare Function timeSetEvent Lib "winmm.dll" (ByVal uDelay As Long, ByVal uResolution As Long, ByVal lpFunction As Long, ByVal dwUser As Long, ByVal uFlags As Long) As Long
'Public Declare Function timeKillEvent Lib "winmm.dll" (ByVal uID As Long) As Long
'Public Const TIME_PERIODIC = 1  ' program for continuous periodic event
'Public timing As Long           ' an API timer Handle

Public SPECWIDTH As Long    'display width
Public SPECHEIGHT As Long   'height (changing requires palette adjustments too)
Public specmode As Boolean, specpos As Integer  ' spectrum mode (and marker pos for 2nd mode)
Public specbuf() As Byte    'a pointer

Public bh As BITMAPINFO     'bitmap header

Public fft(2024) As Single

'check if any file exists
Public Function FileExists(FileName) As Boolean
  On Local Error Resume Next
  FileExists = (Dir$(FileName) <> "")
End Function

' RPP = Return Proper Path
Public Function RPP(ByVal fp As String) As String
  If Right(fp, 1) <> "\" Then
    RPP = fp & "\"
  Else
    RPP = fp
  End If
End Function

Public Function Sqrt(ByVal num As Double) As Double
    Sqrt = num ^ 0.5
End Function

'update the spectrum display - the interesting bit :)
'function Variables are if using an API timer
Public Sub UpdateSpectrum(ByVal uTimerID As Long, ByVal uMsg As Long, ByVal dwUser As Long, ByVal dw1 As Long, ByVal dw2 As Long)
    Static quietcount As Integer
    Dim x As Long, y As Long, Y1 As Long, clr As Long
    'get the FFT data
    Call BASS_ChannelGetData(RECORDCHAN, fft(0), BASS_DATA_FFT2048)
    
        ReDim specbuf(SPECWIDTH * (SPECHEIGHT + 1)) As Byte  'clear display
        For x = 0 To (SPECWIDTH / 2) - 1
            'On Error Resume Next
           If (x > masterclient.leftclip) And (x < masterclient.rightclip) Then
                clr = 128
           Else
                clr = 1
           End If
            y = Sqrt(fft(x + 1)) * 1 * SPECHEIGHT - 4 ' scale it (sqrt to make low values more visible)
            'Y = fft(X + 1) * 10 * SPECHEIGHT 'scale it (linearly)
            'On Error Resume Next
            If (y > SPECHEIGHT) Then y = SPECHEIGHT ' cap it
               If (x) Then  'interpolate from previous to make the display smoother
                    Y1 = (y + Y1) / 2
                    Y1 = Y1 - 1
                    While (Y1 >= 0)
                        On Error Resume Next
                        specbuf(Y1 * SPECWIDTH + x * 2 - 1) = Y1 + clr
                        Y1 = Y1 - 1
                    Wend
                End If
                Y1 = y
                y = y - 1
                While (y >= 0)
                    On Error Resume Next
                    specbuf(y * SPECWIDTH + x * 2) = y + clr ' draw level
                    y = y - 1
                Wend
            
        Next x
   
    
    'display the update
    'to display in a PictureBox, simply change the .hDC to Picture1.hDC :)
    Call SetDIBitsToDevice(masterclient.display.hdc, 0, 0, SPECWIDTH, SPECHEIGHT, 0, 0, 0, SPECHEIGHT, specbuf(0), bh, 0)
    If (GetLoWord(BASS_ChannelGetLevel(RECORDCHAN)) < 3) Then 'check if it's quiet
        quietcount = quietcount + 1
        If (quietcount > 20 And (quietcount And 8)) Then 'it's been quiet for over a second
            Dim r As RECT
            Call SetRect(r, 0, 0, SPECWIDTH, SPECHEIGHT)
            Call SetTextColor(masterclient.hdc, &HFFFFFF)
''          Call SetBkMode(mastercient.hdc, TRANSPARENT)
''          Call DrawText(masterclient.hdc, "INSERT AUDIO", -1, r, DT_CENTER Or DT_VCENTER Or DT_SINGLELINE)
        End If
    Else
        quietcount = 0 'not quiet
    End If
End Sub

'Recording callback - not doing anything with the data
Public Function BuffRecording(ByVal buffer As Long, ByVal Length As Long, ByVal user As Long) As Integer
    DuffRecording = BASSTRUE 'continue recording
End Function