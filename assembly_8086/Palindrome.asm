; Made by Arjun Khera

; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; FIND WHETHER STRING IS A PALINDROME OR NOT

LEA SI,STR
LEA DI,PREFIX

SUB DI,2

OUTER:
    MOV BL,[SI]
    MOV BH,[DI]
    
    CMP BL,BH
    JNZ NOTSAME
    
    INC SI
    DEC DI
    
    MOV AX,SI
    MOV CX,DI
    
    CMP AX,CX
    JBE OUTER
    
SAME: 
    MOV AH,9  
    MOV DX,OFFSET PREFIX
    INT 21H     
    
    MOV AH,9  
    MOV DX,OFFSET STR
    INT 21H     
    
    MOV AH,9  
    MOV DX,OFFSET MATCH
    INT 21H     
    
    JMP END
    
NOTSAME:  
    MOV AH,9  
    MOV DX,OFFSET PREFIX
    INT 21H     
    
    MOV AH,9  
    MOV DX,OFFSET STR
    INT 21H     
    
    MOV AH,9  
    MOV DX,OFFSET NOMATCH
    INT 21H     
    
END:
    MOV AH,00H
    INT 16H    

ret

STR     DB 'MALAYALAM$'
PREFIX  DB 'The string $'
MATCH   DB ' is a palindrome$'
NOMATCH DB ' is not a palindrome$'



