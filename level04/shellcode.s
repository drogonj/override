section .text
    global _start

_start:
    ; Ouverture du fichier
    mov eax, 5                  ; syscall: open
    lea ebx, [filename]         ; adresse du fichier
    mov ecx, 0                  ; O_RDONLY
    int 0x80                    ; appel système
    mov [fd], eax               ; stocke le descripteur de fichier

    ; Lecture de 41 octets
    mov eax, 3                  ; syscall: read
    mov ebx, [fd]               ; descripteur de fichier
    lea ecx, [buffer]           ; buffer pour la lecture
    mov edx, 41                 ; nombre d'octets
    int 0x80                    ; appel système

    ; Écriture sur stdout
    mov eax, 4                  ; syscall: write
    mov ebx, 1                  ; stdout
    lea ecx, [buffer]           ; buffer
    mov edx, 41                 ; nombre d'octets
    int 0x80                    ; appel système

    ; Fermeture du fichier
    mov eax, 6                  ; syscall: close
    mov ebx, [fd]               ; descripteur de fichier
    int 0x80                    ; appel système

    ; Sortie
    mov eax, 1                  ; syscall: exit
    xor ebx, ebx                ; code de sortie 0
    int 0x80                    ; appel système

section .data
filename db '/home/ngalzand/.validated_msg', 0
buffer db 41 dup(0)
fd dd 0
