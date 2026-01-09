; MARVIN stdio overrides

PUBLIC fputc_cons_native
PUBLIC _fputc_cons_native

fputc_cons_native:
_fputc_cons_native:
    pop     bc      ;return address
    pop     hl      ;character to print in l
    push    hl
    push    bc
    ld      a,l
    call    putchar
    ret

PUBLIC fgetc_cons
PUBLIC _fgetc_cons

fgetc_cons:
_fgetc_cons:
    call    getchar
    ;Return the result in hl
    ld      l,a
    ld      h,0
    ret


; additional MARVIN functions 

PUBLIC marvin_readchar
PUBLIC _marvin_readchar

; get a character from the console without waiting 
marvin_readchar:
_marvin_readchar:
    call readchar
    ; return the result in hl
    ld h,0                  
    ld l,a
    ret 
