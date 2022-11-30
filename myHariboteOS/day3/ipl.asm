; haribote-os

; Initial Program Loader

cyls equ 10 ; number of cylinders to read

org 0x7c00 ; The address where the program loads.

; For standard FAT12 soft disk
jmp entry ; jump instruction
nop
db "haribote" ; 8-bit OEM Identifier
dw 512 ; bytes per sector, must be 512 bytes.
db 1 ; Sectors per cluster, must be 1.
dw 1 ; Number of sectors preserved in FAT (boot sector included)
db 2 ; Number of FAT tables, usually 2.
dw 224 ; Max number of files under foot directory.
dw 2880 ; Number of sectors on disk. If zero, it means that there's more than
; 65535 sectors, then use the number recorded at line 24.
db 0xf0 ; Type of disk. 0xf0 means 1.44MB soft disk.
dw 9 ; Length of per FAT, must be 9 sectors.
dw 18 ; Number of sectors belonging to a track, must be 18
dw 2 ; Number of magnetic heads, must be 2.
dd 0 ; Number of hidden sectors.
dd 2880 ; Number or large volume sectors, use this number if line 18 is 0.
db 0 ; Device ID of interrupt 0x13.
db 0 ; Windows NT Identifier.
db 0x29 ; Extended Boot ID
dd 0xffffffff ; Volume sequential number
db "hariboteos " ; Volune Identifier, 11 bytes.
db "FAT12   " ; File system type, 8 bytes.
resb 18 ; Leave 18 blank bytes reserved.

; Core of program
entry:
  mov ax, 0 ; Initialize registers.
  mov ss, ax;
  mov sp, 0x7c00
  mov ds, ax

  ; Read data from disk
  mov ax, 0x0820
  mov es, ax
  mov ch, 0 ; Cylinder 0
  mov dh, 0 ; Magnetic head 0
  mov cl, 2 ; Sector 2

; Read Loop
readloop:
  mov si, 0 ; Register that records times of failures.
retry:
  mov ah, 0x02 ; ah=0x02: Read disk
  mov al, 1 ; 1 Sector
  mov bx, 0
  mov dl, 0x00 ; Driver A
  int 0x13 ; Call disk BIOS
  jnc next ; Jump to next if there's no error.

  add si, 1 ; Failure counter register auto-increment.
  cmp si, 5 ; Determine whether the number of failures reaches 5 times.
  jae error ; If the number of failures reached 5 times, jump to error.
  mov ah, 0x00 ; 
  mov dl, 0x00 ; Driver A
  int 0x13 ; Reset driver A
  jmp retry

next:
  mov ax, es ; Move the address back by 5 bits.
  add ax, 0x0020
  mov es, ax ; Implement ex += 0x0020

  ; Sectors range 1 to 18.
  add cl, 1 ; Sector += 1.
  cmp cl, 18 ; Determine whether sector 18 has been read.
  jbe readloop ; If current sector BLE sector 18, jump to readloop.

  mov cl, 1 ; Recover to sector 1
  ; Magnetic head range 0 to 1 (front side 0, back side 1)
  add dh, 1
  cmp dh, 2
  jb readloop ; Read all both magnetic heads.

  mov dh, 0
  ; Cylinder range 0 to 79
  add ch, 1
  cmp ch, cyls
  jb readloop ; Read cylinders by jumping to readloop until the number of
  ; clylinders read reaches CYLE.

  ; End of reading, print message.
  mov si, msg

error:
  mov si, error_msg

msg:
  db 0x0a, 0x0a ; 2 newlines.
  db "hello, world"
  db 0x0a ; newline
  db "--" ; newline
  db "from cute micuks' haribote"
  db 0x0a ; newline
  db 0

error_msg:
  db 0x0a, 0x0a ; 2 newlines
  db "load error"
  db 0x0a ; newline
  db 0

; ------ END OF ASSEMBLY ------
RESB 0x1fe - ($-$$) ; Fill with byte 0x00 until 0x001fe
; End of boot sector identifier, fixed to be 0xaa55 ( Little-endian)
db 0x55 0xaa
