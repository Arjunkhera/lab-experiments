; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; BCD TO BINARY CONVERSION

MOV AL,NUMBER
AND AL,0F0H

SHR AL,4     

MOV BL,10
MUL BL
MOV ANSWER,AL

MOV AL,NUMBER
AND AL,0FH

ADD AL,ANSWER
MOV ANSWER,AL


; PRINT RESULT IN BINARY

MOV BL,ANSWER
MOV CX,08H

METHOD:        
    SHL BL,1
    MOV AH,2
    MOV DL,'0'
    JNC PRINT
    MOV DL,'1'
PRINT:    
    INT 21H
    LOOP METHOD
  
MOV AH,02H
MOV DL,'B'    
INT 21H

; WAIT FOR KEY PRESS
MOV AH,0
INT 16H

ret

; variables:
NUMBER DB 16H
ANSWER DB 0
