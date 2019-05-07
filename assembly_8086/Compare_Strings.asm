
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; add your code here

LEA SI,PASS
LEA DI,INPUT

MOV CX,LEN
DEC CX

OUTER:
    MOV BL,[SI]
    MOV BH,[DI]

    CMP BH,BL
    JNE NOMATCH    
    
    INC SI
    INC DI
    
    LOOP OUTER

     
MATCH:
    MOV AH,9
    MOV DX,OFFSET RIGHT
    INT 21H
    JMP FINISH 
    
NOMATCH:                
    MOV AH,9
    MOV DX,OFFSET WRONG
    INT 21H
             
FINISH:             
    MOV AH,00H
    INT 16H  

ret

PASS  DB   "AKB$"
LEN   EQU  ($-PASS)
INPUT DB   "AKB$"
WRONG DB   "THIS IS THE WRONG ANSWER$"
RIGHT DB   "THIS IS THE CORRECT ANSWER$"


