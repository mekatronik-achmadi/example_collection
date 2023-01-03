$regfile = "m16def.dat"
$crystal = 16000000

'C6 as output
Ddrc.6 = 1

'C5 as pull up button
Portc.5 = 1

Do
   If Pinc.5 = 1 Then
      Portc.6 = 0
   Else
      Portc.6 = 1
   End If
Loop

End