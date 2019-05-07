
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; add your code here

MOV AL,LETTER

; TO STORE LOWER PART
MOV BL,0FH    
AND BL,AL

; TO STORE HIGHER PART
MOV CL,0F0H            
AND CL,AL 
SHR CL,4


MOV AL,BL
ADD BL,48
SUB AL,10

JS  PRINTA
ADD BL,7
   
; PRINTA : IS NOT SAME AS PRINTA:   
PRINTA:
    MOV AH,5
    MOV DL,BL
    INT 21H         
    
    
MOV AL,CL
ADD CL,48
SUB AL,10

JS  PRINTB
ADD CL,7
   
PRINTB:
    MOV AH,5
    MOV DL,CL
    INT 21H         

ret

NUMBER DB 023H
LETTER DB 0A1H

; IS EQUIVALENT TO ADD 30H
;ADD BL,48
