section .text
global myDjb2

; djv2 hash func


myDjb2:
    
    push rbx

    
    mov ebx, 5381          

.loop:
    
    movzx eax, byte [rdi]  
    test al, al            
    jz .done               

    ; hash = ((hash << 5) + hash) + *word
    mov ecx, ebx
    shl ecx, 5             ; hash << 5
    add ecx, ebx           ; (hash << 5) + hash = hash * 33
    add ecx, eax           ; + *word
    mov ebx, ecx

    
    inc rdi                
    jmp .loop              

.done:
    
    mov eax, ebx           
    xor edx, edx           
    mov ecx, 750         
    div ecx                
    mov eax, edx           

    
    pop rbx
    ret
