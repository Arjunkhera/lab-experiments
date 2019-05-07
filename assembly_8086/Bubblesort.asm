; Made by Arjun Khera

; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; BUBBLESORT

MOV CL,LEN
DEC CL

OUTER:
    LEA SI,ARR
    MOV DL,CL
INNER:    
    MOV BL,[SI]
    MOV BH,[SI+1]
    MOV AL,BL
    
    SUB AL,BH
    JS NOTHING
    MOV [SI],BH
    MOV [SI+1],BL
    
NOTHING:
    INC SI  
    DEC DL
    JNZ INNER
    LOOP OUTER

MOV CX,LEN
LEA SI,ARR

SCREEN:       
    CALL PRINT
    
    MOV AH,02
    MOV DL,32
    INT 21H
    
    INC SI    
    LOOP SCREEN       

ret

ARR DB 105,13,10,22,17,71,99,103,1
LEN EQU ($-ARR)
NUMBER DB ?


; TO DISPLAY THE NUMBER IS DECIMAL FORM
PRINT PROC NEAR 

    PUSH CX

    MOV BL,[SI]
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
    
    POP CX
    RET      
PRINT ENDP    
    
    
    
