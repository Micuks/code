; hello-os

; Part 1: FAT12 Boot record
; Standard code for FAT12 format soft disk
DB 0xeb, 0x4e ; Jump instruction
DB 0x90 ; NOP Instruction
DB "HELLOIPL" ; OEM Identifier(8 bytes)
DW 512 ; Number of bytes per sector ( Must be 512 bytes )
DB 1 ; Number of sectors per cluster ( Must be 1 sector )
DW 1 ; Number of FAT preserved sectors ( Boot sector included )
DB 2 ; Number of FAT tables, usually is 2
DW 224 ; Max number of root directory files ( 224 by default )
DW 2880 ; Total amount of sectors in disk, it means there's more than 65535
; sectors if set to 0, need to use 19 lines to record
DB 0xf0 ; Type of disk ( 0xf0 means 1.44MB soft disk )
DW 9 ; Length of per FAT ( must be 9 sectors )
DW 18 ; Number of sectors per track ( must be 18 )
DW 2 ; number of magnetic heads ( must be 2 )
DD 0 ; hidden sectors
DD 2880 ; Total number of large volume sectors, if value of line 13 is 0, use
; sector number recorded in this line
DB 0 ; Device id of interrupt 0x13
DB 0 ; Identifier of Windows NT
DB 0x29 ; Extended boot ID
DD 0xffffffff ; Volume serial number
DB "HELLO-OS   " ; Volume Identifier ( 11 bytes )
DB "FAT12   " ; File system type ( 8 bytes )

; Part 2: Boot code, data and other informations
RESB 18 ; leave 18 blank bytes 

; Main program
DB    0xb8, 0x00, 0x00, 0x8e, 0xd0, 0xbc, 0x00, 0x7c
DB    0x8e, 0xd8, 0x8e, 0xc0, 0xbe, 0x74, 0x7c, 0x8a
DB    0x04, 0x83, 0xc6, 0x01, 0x3c, 0x00, 0x74, 0x09
DB    0xb4, 0x0e, 0xbb, 0x0f, 0x00, 0xcd, 0x10, 0xeb
DB    0xee, 0xf4, 0xeb, 0xfd

; Data of information display part
DB 0x0a, 0x0a ; two newlines (\n)
DB "Hello, World!"
DB 0x0a ; newline
DB 0

RESB 0x1fe - ($ - $$) ; fill 0x00 until 0x001fe

; Part 3: end of boot sector identifier, fixed to be 0xaa55 ( Little endian )
DB 0x55, 0xaa

; Context outside bootloader sector
DB 0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
RESB 4600
DB 0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
RESB 1469432
