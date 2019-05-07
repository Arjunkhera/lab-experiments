; multi-segment executable file template.

data segment
    ; add your data here!
    pkey    db "press any key...$"
    len     dw 4  
    answer  dw ?  
    divisor dw 10
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax

    ; add your code here                   
    
    mov cx,len
    mov ax,1
    mov bx,1
    
factorial:  
    
    mul bx
    inc bx                  
                  
    loop factorial
    
    mov answer,ax
    
    call print
    
    mov ah,02
    mov dl,32
    int 21h
            
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
    
    
    
    ; procedure to print the decimal number
print proc near
    mov cx,0
    mov bx,answer
    
method:
    mov dl,10
    mov ax,bx
    div dl
    
    mov bl,al
    mov dl,ah
    add dl,30h
    push dx
    
    inc cx                  
    
    cmp bl,00H
    jz display
    jmp method
                  
display:   
    mov ah,02
    pop dx
    int 21h              
    loop display
    
    ret                    
print endp    
              
ends
end start ; set entry point and stop the assembler.
