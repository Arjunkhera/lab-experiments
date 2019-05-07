
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; PRINTING DECIMAL NUMBER

MOV BL,NUMBER
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
    JZ PRINT
    JMP METHOD       

PRINT:      
    MOV AH,02
    POP DX
    INT 21H
    LOOP PRINT
    
MOV AH,00H
INT 16H

ret

NUMBER DB 255


