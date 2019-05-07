
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; CONVERTING ASCII TO PACKED BCD


MOV CL,30H

MOV BL,HIGH
SUB BL,CL

MOV DL,LOW
SUB DL,CL

MOV AL,BL
SHL AL,4
ADD AL,DL

MOV RESULT,AL

ret

HIGH    DB '4'
LOW     DB '1'
RESULT  DB ? 

