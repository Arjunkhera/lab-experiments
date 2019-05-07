; Made by Arjun Khera

; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; PRINTING A NUMBER IN BINARY FORM ON SCREEN

MOV BL,NUMBER
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

NUMBER DB 0FFH


