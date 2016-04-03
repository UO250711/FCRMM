.386
.model flat, C
.code

calculaNMuertosASM PROC	
push ebp
mov ebp, esp				; Prologo 
sub esp, 4					; Reserva de espacio para variable local int nMuertos

push ecx 
push edi 
push edx
push esi 					; Salvaguarda de registros 

; Signatura del procedimiento (parámetros formales)
mov ecx, [ebp + 8]			; Acceso al tercer parametro propuesta[]
mov edi, [ebp + 12]			; Acceso al primer parametro solucion[]
mov esi, [ebp + 16]			; Acceso al primer parametro nElementos

; Cuerpo del procedimiento 
mov DWORD PTR [ebp - 4], 0	; nMuertos = 0

; Inicio del bucle 
xor edx, edx				; i = 0 

inicio_bucle: 
cmp esi, edx				; 
je fin_bucle				; Si i >= nElementos, fin del bucle. 		

; Cuerpo del bucle for 
mov ah, [ecx + edx]
mov al ,[edi + edx]			; Copiamos solucion[i] y propuesta[i] a al y ah 
cmp al,ah					; if (propuesta[i] == solucion[i])
je tenemos_muerto			; Salto para acumular muertos si los hay 
jmp siguiente				; Siguiente si no hay muertos. 

tenemos_muerto:
inc DWORD PTR [ebp -4]		; nMuertos++

siguiente: 
inc edx						; Incrementamos i (i++) 
jmp inicio_bucle			; Volvemos al inicio del bucle

fin_bucle:
mov eax, [ebp -4]			; eax = nMuertos 

pop	esi
pop edx 
pop edi 
pop ecx						; Restauracion de registros 

mov esp, ebp				; Eliminamos variable local 

pop ebp						; Epílogo 
ret

calculaNMuertosASM ENDP
END