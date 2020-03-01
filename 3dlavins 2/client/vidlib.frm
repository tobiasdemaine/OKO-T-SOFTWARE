VERSION 5.00
Begin VB.Form vidlib 
   Caption         =   "VIDEO SOURCE SELECTOR"
   ClientHeight    =   4740
   ClientLeft      =   6270
   ClientTop       =   4500
   ClientWidth     =   3570
   LinkTopic       =   "Form1"
   ScaleHeight     =   4740
   ScaleWidth      =   3570
End
Attribute VB_Name = "vidlib"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Private Sub lfeed_Click()
    MsgBox "got to do this yet in the server"
End Sub




Private Sub vidlib_Click()
    '' populate the list box with the data from the vidlibarray in masterclient form
    For i = 0 To UBound(masterclient.vidlib)
        List1.AddItem masterclient.vidlib(i), i
    Next i
End Sub
