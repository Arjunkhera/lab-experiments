
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; PRINT THE SUM AND AVERAGE OF ELEMENTS IN ARRAY

MOV CX,LEN
LEA BX,ARR 

MOV DX,0

OUTER:      
    MOV AH,0
    MOV AL,[BX]
    ADD DX,AX
    INC BX
    LOOP OUTER

; STORING SUM    
MOV SUM,DX

; STORING AVERAGE
MOV AX,DX
MOV BL,LEN     
DIV BL
MOV AVG,AX   
    
    
; TO PRINT THE ANSWER ON SCREEN    
MOV AH,9  
MOV DX,OFFSET STRA
INT 21H 

LEA SI,SUM
CALL PRINT

MOV AH,9  
MOV DX,OFFSET STRB
INT 21H           

LEA SI,AVG
CALL PRINT
    
ret

ARR  DB 1,2,3
LEN  EQU ($-ARR)
SUM  DW ?
AVG  DW ?
STRA DB 'THE SUM IS: $'
STRB DB ' AND AVERAGE IS: $'

; TO DISPLAY THE NUMBER IS DECIMAL FORM
PRINT PROC NEAR 

    MOV BL,BYTE PTR[SI]
    MOV BH,10
    MOV CX,0

METHOD:
    MOV AH,0
    MOV AL,BL
    DIV BH
    
    MOV BL,AL
    MOV DH,0
    MOV DL,AH
    ADD DL,30H
    PUSH DX
        
    INC CX
    
    CMP BL,00H
    JZ DISPLAY
    JMP METHOD       

DISPLAY:      
    MOV AH,02
    POP DX
    INT 21H
    LOOP DISPLAY
    
    RET      
PRINT ENDP    

