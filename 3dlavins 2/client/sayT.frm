VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{0D452EE1-E08F-101A-852E-02608C4D0BB4}#2.0#0"; "fm20.dll"
Begin VB.Form sayit 
   BackColor       =   &H00404040&
   BorderStyle     =   5  'Sizable ToolWindow
   Caption         =   "SAY T"
   ClientHeight    =   2790
   ClientLeft      =   60
   ClientTop       =   9450
   ClientWidth     =   7770
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2790
   ScaleWidth      =   7770
   ShowInTaskbar   =   0   'False
   Begin VB.TextBox iscale 
      Appearance      =   0  'Flat
      BackColor       =   &H00808080&
      Height          =   375
      Left            =   5205
      TabIndex        =   8
      Top             =   1695
      Width           =   615
   End
   Begin VB.Timer Timer1 
      Interval        =   200
      Left            =   930
      Top             =   1980
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   360
      Top             =   1920
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton preview 
      Caption         =   "preview"
      Height          =   255
      Left            =   4470
      TabIndex        =   6
      Top             =   2505
      Width           =   1575
   End
   Begin VB.CommandButton update 
      Caption         =   "update"
      Height          =   255
      Left            =   6120
      TabIndex        =   4
      Top             =   2505
      Width           =   1575
   End
   Begin VB.TextBox linet 
      Appearance      =   0  'Flat
      BackColor       =   &H00808080&
      Height          =   495
      Left            =   4440
      TabIndex        =   3
      Top             =   405
      Width           =   3255
   End
   Begin VB.TextBox time 
      Appearance      =   0  'Flat
      BackColor       =   &H00808080&
      Height          =   375
      Left            =   5205
      TabIndex        =   2
      Top             =   2070
      Width           =   615
   End
   Begin VB.TextBox y 
      Appearance      =   0  'Flat
      BackColor       =   &H00808080&
      Height          =   375
      Left            =   5205
      TabIndex        =   1
      Top             =   1320
      Width           =   615
   End
   Begin VB.TextBox x 
      Appearance      =   0  'Flat
      BackColor       =   &H00808080&
      Height          =   375
      Left            =   5205
      TabIndex        =   0
      Top             =   945
      Width           =   615
   End
   Begin MSForms.ComboBox meshes 
      Height          =   315
      Left            =   4470
      TabIndex        =   9
      Top             =   45
      Width           =   3225
      VariousPropertyBits=   746604571
      BackColor       =   12632256
      BorderStyle     =   1
      DisplayStyle    =   3
      Size            =   "5689;556"
      MatchEntry      =   1
      ShowDropButtonWhen=   2
      SpecialEffect   =   0
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
   End
   Begin MSForms.ListBox fontz 
      Height          =   1500
      Left            =   5880
      TabIndex        =   7
      Top             =   945
      Width           =   1815
      BackColor       =   8421504
      BorderStyle     =   1
      ScrollBars      =   3
      DisplayStyle    =   2
      Size            =   "3201;2646"
      MatchEntry      =   0
      SpecialEffect   =   0
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
   End
   Begin MSForms.ListBox tline 
      Height          =   2700
      Left            =   45
      TabIndex        =   5
      Top             =   15
      Width           =   4365
      BackColor       =   8421504
      BorderStyle     =   1
      ScrollBars      =   3
      DisplayStyle    =   2
      Size            =   "7699;4762"
      MatchEntry      =   0
      SpecialEffect   =   0
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
   End
   Begin VB.Menu fi 
      Caption         =   "File"
      Begin VB.Menu ne 
         Caption         =   "new"
      End
      Begin VB.Menu lo 
         Caption         =   "load"
      End
      Begin VB.Menu sa 
         Caption         =   "save"
      End
   End
   Begin VB.Menu pla 
      Caption         =   "play"
   End
   Begin VB.Menu al 
      Caption         =   "add line"
   End
   Begin VB.Menu dl 
      Caption         =   "delete line"
   End
   Begin VB.Menu lu 
      Caption         =   "line up"
   End
   Begin VB.Menu ld 
      Caption         =   "line down"
   End
End
Attribute VB_Name = "sayit"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim tlines(3000) As String
Dim tx(3000) As Integer
Dim ty(3000) As Integer
Dim ttime(3000) As Integer
Dim tfont(3000) As Integer
Dim tscale(3000) As Integer
Dim textmeshes(3000) As Integer
Dim sayts As String
Dim ttcount
Dim holdfor

Private Sub al_Click()
    tline.AddItem "  "
End Sub

Private Sub ld_Click()
   Dim lin
   Dim ah(7) As Variant
   Dim ahh(7) As Variant
   If tline.ListIndex = -1 Then
    MsgBox "select a line to ove"
   ElseIf tline.ListIndex = 0 Then
    MsgBox "can not move top line upwards"
   Else
   lin = tline.ListIndex
   tline.RemoveItem lin
   tline.AddItem tlines(lin), lin + 1
   tline.Selected(lin + 1) = True
        ah(0) = tlines(lin)
        ah(1) = tx(lin)
        ah(2) = ty(lin)
        ah(3) = ttime(lin)
        ah(4) = tfont(lin)
        ah(5) = tscale(lin)
        ahh(0) = tlines(lin + 1)
        ahh(1) = tx(lin + 1)
        ahh(2) = ty(lin + 1)
        ahh(3) = ttime(lin + 1)
        ahh(4) = tfont(lin + 1)
        ahh(5) = tscale(lin + 1)
   '' now fix up the arrays
   For I = 0 To tline.ListCount
        If I = lin + 1 Then
        tlines(I) = ah(0)
        tx(I) = ah(1)
        ty(I) = ah(2)
        ttime(I) = ah(3)
        tfont(I) = ah(4)
        tscale(I) = ah(5)
        ElseIf I = lin Then
        tlines(I) = ahh(0)
        tx(I) = ahh(1)
        ty(I) = ahh(2)
        ttime(I) = ahh(3)
        tfont(I) = ahh(4)
        tscale(I) = ahh(5)
        End If
   Next I
   End If
   tline_Click
End Sub

Private Sub lu_Click()
   Dim lin
   Dim ah(7) As Variant
   Dim ahh(7) As Variant
   If tline.ListIndex = -1 Then
    MsgBox "select a line to ove"
   ElseIf tline.ListIndex = 0 Then
    MsgBox "can not move top line upwards"
   Else
   lin = tline.ListIndex
   tline.RemoveItem lin
   tline.AddItem tlines(lin), lin - 1
   tline.Selected(lin - 1) = True
        ah(0) = tlines(lin)
        ah(1) = tx(lin)
        ah(2) = ty(lin)
        ah(3) = ttime(lin)
        ah(4) = tfont(lin)
        ah(5) = tscale(lin)
        ahh(0) = tlines(lin - 1)
        ahh(1) = tx(lin - 1)
        ahh(2) = ty(lin - 1)
        ahh(3) = ttime(lin - 1)
        ahh(4) = tfont(lin - 1)
        ahh(5) = tscale(lin - 1)
   '' now fix up the arrays
   For I = 0 To tline.ListCount
        If I = lin - 1 Then
        tlines(I) = ah(0)
        tx(I) = ah(1)
        ty(I) = ah(2)
        ttime(I) = ah(3)
        tfont(I) = ah(4)
        tscale(I) = ah(5)
        ElseIf I = lin Then
        tlines(I) = ahh(0)
        tx(I) = ahh(1)
        ty(I) = ahh(2)
        ttime(I) = ahh(3)
        tfont(I) = ahh(4)
        tscale(I) = ahh(5)
        End If
   Next I
   End If
   tline_Click
End Sub

Private Sub Form_Load()
loadfonts

Dim cmesh
Dim iii
Dim effects
iii = 0
Open "../tscript/tscript.okot" For Input As #1
    Do While Not EOF(1)
    Line Input #1, tscript
    
    If InStr(1, tscript, "effect(", 0) Then
        effects = Mid(tscript, InStr(1, tscript, "(", 1) + 1, (InStr(1, tscript, ")", 1)) - (InStr(1, tscript, "(", 1) + 1))
        
    End If
    If InStr(1, tscript, "mesh(", 0) Then
    
            If InStr(1, tscript, "text", 0) Then
             textmeshes(iii) = cmesh
             meshes.AddItem "fx : " & effects & " :: mesh id " & cmesh, iii
             iii = iii + 1
            
            End If
            cmesh = cmesh + 1
    End If
    Loop
Close #1
    
End Sub

Private Sub lo_Click()
tline.Clear
    On Error GoTo Err_Form_Load
    CommonDialog1.InitDir = App.Path
    CommonDialog1.Filter = "Say T files (*.say)|*.say"
    CommonDialog1.flags = &H4&
    CommonDialog1.Action = 1
    Open CommonDialog1.FileName For Input As #1
        Dim uin
        uin = 0
        Do While Not EOF(1)
        Line Input #1, tees
        If InStr(1, tees, ";", 1) Then
        temps = tees
        tlines(uin) = Mid(tees, 1, InStr(1, tees, ";", 1) - 1)
        tline.AddItem tlines(uin), uin
        '' now we get out the rest of the lines and stick them in arrays
            
        temps = Mid(temps, InStr(1, temps, ";", 1) + 1, Len(temps))
        tx(uin) = Mid(temps, 1, InStr(1, temps, ";", 1) - 1)
        
        temps = Mid(temps, InStr(1, temps, ";", 1) + 1, Len(temps))
        ty(uin) = Mid(temps, 1, InStr(1, temps, ";", 1) - 1)
        
        temps = Mid(temps, InStr(1, temps, ";", 1) + 1, Len(temps))
        ttime(uin) = Mid(temps, 1, InStr(1, temps, ";", 1) - 1)
        
        temps = Mid(temps, InStr(1, temps, ";", 1) + 1, Len(temps))
        tfont(uin) = Mid(temps, 1, InStr(1, temps, ";", 1) - 1)
        
        temps = Mid(temps, InStr(1, temps, ";", 1) + 1, Len(temps))
        tscale(uin) = Mid(temps, 1, InStr(1, temps, ";", 1) - 1)
        
        uin = uin + 1
        End If
        Loop
    Close #1
    
Err_Form_Load:
    End Sub



Private Sub pla_Click()
If pla.Caption = "play" Then
    pla.Caption = "stop"
    '' now we start to through the interface
    
    
Else
    pla.Caption = "play"
End If

End Sub
Private Sub loadfonts()
Open "../lib/fonts.okot" For Input As #1
    Dim uin
    Dim tempstr As String
    
    uin = 0
    Do While Not EOF(1)
    Line Input #1, Fonts
            
    If InStr(1, Fonts, ";", 1) Then
   
    fontz.AddItem Mid(Fonts, 1, InStr(1, Fonts, ";", 1) - 1), uin
    uin = uin + 1
    
    End If
        Loop
Close #1
''fontcount = uin
End Sub

Private Sub preview_Click()
If meshes.ListIndex = -1 Then
 MsgBox "you must select a mesh"
Else
 If linet.Text = "" Then
    linet = "   "
 End If
 sayts = "group->text(" & textmeshes(meshes.ListIndex) & ")(" & linet.Text & ");meshposition(" & textmeshes(meshes.ListIndex) & " " & x & " " & y & " 0);textsize(" & textmeshes(meshes.ListIndex) & " " & iscale & ");font(" & textmeshes(meshes.ListIndex) & " " & fontz.ListIndex & ")"
 masterclient.winsock1.SendData sayts
 ''MsgBox sayts
End If
End Sub

Private Sub sa_Click()
Dim I As Integer, j As Integer

'error handler: if the file is not found, the program will not attempt to save data
On Error GoTo Err_Form_Unload

'set the dialog box's starting path to the program's path
CommonDialog1.InitDir = App.Path
'set the filter the *.dat files
CommonDialog1.Filter = "Data files (*.say)|*.say"
'hide the read-only check box
CommonDialog1.flags = &H4&
'force the dialog box to prompt for a file to Save As
CommonDialog1.Action = 1

'open the file
'For Output means we will be writing to the file
'As #1 means the #1 will be used to refer to the file
Open CommonDialog1.FileName For Output As #1
        Print #1, tline.ListCount
        For j = 0 To tline.ListCount - 1
                    Print #1, tlines(j) & ";" & tx(j) & ";" & ty(j) & ";" & ttime(j) & ";" & tfont(j) & ";" & tscale(j) & ";"
        Next j
Close #1
Err_Form_Unload:
End Sub
    
Private Sub Timer1_Timer()
If pla.Caption = "stop" Then
    If meshes.ListIndex = -1 Then
        MsgBox "you must select a mesh. Stopping Playback"
        pla.Caption = "play"
    End If
    If ttime(ttcount) = holdfor Then
        ttcount = ttcount + 1
        If tline.ListCount <= ttcount Then
            ttcount = 0
        End If
        tline.Selected(ttcount) = True
        tline_Click
        preview_Click
        holdfor = 1
    Else
        holdfor = holdfor + 1
    End If
    
Else
    ttcount = 0
End If
End Sub

Private Sub tline_Click()
    linet.Text = tlines(tline.ListIndex)
    x.Text = tx(tline.ListIndex)
    y.Text = ty(tline.ListIndex)
    time.Text = ttime(tline.ListIndex)
    fontz.Selected(tfont(tline.ListIndex)) = True
    iscale.Text = tscale(tline.ListIndex)
End Sub

Private Sub update_Click()
Dim lin
lin = tline.ListIndex
If tline.ListIndex = -1 Then
    MsgBox "there is nothing to update"
Else
    tfont(tline.ListIndex) = fontz.ListIndex
    tlines(tline.ListIndex) = linet.Text
    tx(tline.ListIndex) = x.Text
    ty(tline.ListIndex) = y.Text
    ttime(tline.ListIndex) = time.Text
    tscale(tline.ListIndex) = iscale.Text
    tline.RemoveItem tline.ListIndex
    tline.AddItem linet.Text, lin
    tline.Selected(lin) = True
End If
End Sub

