VERSION 5.00
Begin VB.Form mykeys 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Keyboard"
   ClientHeight    =   1830
   ClientLeft      =   6030
   ClientTop       =   9000
   ClientWidth     =   7425
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "keyboard.frx":0000
   ScaleHeight     =   1830
   ScaleWidth      =   7425
   ShowInTaskbar   =   0   'False
End
Attribute VB_Name = "mykeys"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_KeyPress(KeyAscii As Integer)
''MsgBox (KeyAscii)
 Select Case KeyAscii
 ''/// Keys for reseting animations
 Case Is = 49
    keyint (0)
 Case Is = 50
    keyint (1)
 Case Is = 51
    keyint (2)
 Case Is = 52
    keyint (3)
 Case Is = 53
    keyint (4)
 Case Is = 54
    keyint (5)
 Case Is = 55
    keyint (6)
 Case Is = 56
    keyint (7)
 Case Is = 57
    keyint (8)
 Case Is = 48
    keyint (9)
 Case Is = 113
    keyint (10)
 Case Is = 119
    keyint (11)
 Case Is = 101
    keyint (12)
 Case Is = 114
    keyint (13)
 Case Is = 116
    keyint (14)
 Case Is = 121
    keyint (15)
 Case Is = 117
    keyint (16)
 Case Is = 105
    keyint (17)
 Case Is = 111
    keyint (18)
 Case Is = 112
    keyint (19)
 
 ''// overlays
 Case Is = 33
    ovid (0)
 Case Is = 64
    ovid (1)
 Case Is = 35
    ovid (2)
 Case Is = 36
    ovid (3)
 Case Is = 37
    ovid (4)
 Case Is = 94
    ovid (5)
 Case Is = 38
    ovid (6)
 Case Is = 42
    ovid (7)
 Case Is = 40
    ovid (8)
 Case Is = 41
    ovid (9)
 Case Is = 81
    ovid (10)
 Case Is = 87
    ovid (11)
 Case Is = 69
    ovid (12)
 Case Is = 82
    ovid (13)
 Case Is = 84
    ovid (14)
 Case Is = 89
    ovid (15)
 Case Is = 85
    ovid (16)
 Case Is = 73
    ovid (17)
 Case Is = 79
    ovid (18)
 Case Is = 80
    ovid (19)
    
    
 End Select
End Sub
Private Sub keyint(Index As Integer)
masterclient.resetk (Index)

End Sub
Private Sub ovid(Index As Integer)
masterclient.clicktrans (Index)
End Sub
