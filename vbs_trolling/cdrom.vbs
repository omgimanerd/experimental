Set oWMP = CreateObject("WMPlayer.OCX.7")
Set colCDROMs = oWMP.cdromCollection
wscript.sleep 60
do
if colCDROMs.count >= 1 then
For i = 0 to colCDROMs.Count - 1
colCDROMs.Item(i).Eject
Next
For i = 0 to colCDROMs.Count - 1
colCDROMs.Item(i).Eject
Next
End If
wscript.sleep 60
loop
