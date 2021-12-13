
bomb:     file format elf64-x86-64


Disassembly of section .init:

0000000000400b00 <_init>:
  400b00:	48 83 ec 08          	sub    $0x8,%rsp
  400b04:	48 8b 05 ed 34 20 00 	mov    0x2034ed(%rip),%rax        # 603ff8 <__gmon_start__>
  400b0b:	48 85 c0             	test   %rax,%rax
  400b0e:	74 05                	je     400b15 <_init+0x15>
  400b10:	e8 db 01 00 00       	callq  400cf0 <__gmon_start__@plt>
  400b15:	48 83 c4 08          	add    $0x8,%rsp
  400b19:	c3                   	retq   

Disassembly of section .plt:

0000000000400b20 <.plt>:
  400b20:	ff 35 e2 34 20 00    	pushq  0x2034e2(%rip)        # 604008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400b26:	ff 25 e4 34 20 00    	jmpq   *0x2034e4(%rip)        # 604010 <_GLOBAL_OFFSET_TABLE_+0x10>
  400b2c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400b30 <getenv@plt>:
  400b30:	ff 25 e2 34 20 00    	jmpq   *0x2034e2(%rip)        # 604018 <getenv@GLIBC_2.2.5>
  400b36:	68 00 00 00 00       	pushq  $0x0
  400b3b:	e9 e0 ff ff ff       	jmpq   400b20 <.plt>

0000000000400b40 <strcasecmp@plt>:
  400b40:	ff 25 da 34 20 00    	jmpq   *0x2034da(%rip)        # 604020 <strcasecmp@GLIBC_2.2.5>
  400b46:	68 01 00 00 00       	pushq  $0x1
  400b4b:	e9 d0 ff ff ff       	jmpq   400b20 <.plt>

0000000000400b50 <__errno_location@plt>:
  400b50:	ff 25 d2 34 20 00    	jmpq   *0x2034d2(%rip)        # 604028 <__errno_location@GLIBC_2.2.5>
  400b56:	68 02 00 00 00       	pushq  $0x2
  400b5b:	e9 c0 ff ff ff       	jmpq   400b20 <.plt>

0000000000400b60 <strcpy@plt>:
  400b60:	ff 25 ca 34 20 00    	jmpq   *0x2034ca(%rip)        # 604030 <strcpy@GLIBC_2.2.5>
  400b66:	68 03 00 00 00       	pushq  $0x3
  400b6b:	e9 b0 ff ff ff       	jmpq   400b20 <.plt>

0000000000400b70 <puts@plt>:
  400b70:	ff 25 c2 34 20 00    	jmpq   *0x2034c2(%rip)        # 604038 <puts@GLIBC_2.2.5>
  400b76:	68 04 00 00 00       	pushq  $0x4
  400b7b:	e9 a0 ff ff ff       	jmpq   400b20 <.plt>

0000000000400b80 <write@plt>:
  400b80:	ff 25 ba 34 20 00    	jmpq   *0x2034ba(%rip)        # 604040 <write@GLIBC_2.2.5>
  400b86:	68 05 00 00 00       	pushq  $0x5
  400b8b:	e9 90 ff ff ff       	jmpq   400b20 <.plt>

0000000000400b90 <__stack_chk_fail@plt>:
  400b90:	ff 25 b2 34 20 00    	jmpq   *0x2034b2(%rip)        # 604048 <__stack_chk_fail@GLIBC_2.4>
  400b96:	68 06 00 00 00       	pushq  $0x6
  400b9b:	e9 80 ff ff ff       	jmpq   400b20 <.plt>

0000000000400ba0 <alarm@plt>:
  400ba0:	ff 25 aa 34 20 00    	jmpq   *0x2034aa(%rip)        # 604050 <alarm@GLIBC_2.2.5>
  400ba6:	68 07 00 00 00       	pushq  $0x7
  400bab:	e9 70 ff ff ff       	jmpq   400b20 <.plt>

0000000000400bb0 <close@plt>:
  400bb0:	ff 25 a2 34 20 00    	jmpq   *0x2034a2(%rip)        # 604058 <close@GLIBC_2.2.5>
  400bb6:	68 08 00 00 00       	pushq  $0x8
  400bbb:	e9 60 ff ff ff       	jmpq   400b20 <.plt>

0000000000400bc0 <read@plt>:
  400bc0:	ff 25 9a 34 20 00    	jmpq   *0x20349a(%rip)        # 604060 <read@GLIBC_2.2.5>
  400bc6:	68 09 00 00 00       	pushq  $0x9
  400bcb:	e9 50 ff ff ff       	jmpq   400b20 <.plt>

0000000000400bd0 <__libc_start_main@plt>:
  400bd0:	ff 25 92 34 20 00    	jmpq   *0x203492(%rip)        # 604068 <__libc_start_main@GLIBC_2.2.5>
  400bd6:	68 0a 00 00 00       	pushq  $0xa
  400bdb:	e9 40 ff ff ff       	jmpq   400b20 <.plt>

0000000000400be0 <fgets@plt>:
  400be0:	ff 25 8a 34 20 00    	jmpq   *0x20348a(%rip)        # 604070 <fgets@GLIBC_2.2.5>
  400be6:	68 0b 00 00 00       	pushq  $0xb
  400beb:	e9 30 ff ff ff       	jmpq   400b20 <.plt>

0000000000400bf0 <signal@plt>:
  400bf0:	ff 25 82 34 20 00    	jmpq   *0x203482(%rip)        # 604078 <signal@GLIBC_2.2.5>
  400bf6:	68 0c 00 00 00       	pushq  $0xc
  400bfb:	e9 20 ff ff ff       	jmpq   400b20 <.plt>

0000000000400c00 <gethostbyname@plt>:
  400c00:	ff 25 7a 34 20 00    	jmpq   *0x20347a(%rip)        # 604080 <gethostbyname@GLIBC_2.2.5>
  400c06:	68 0d 00 00 00       	pushq  $0xd
  400c0b:	e9 10 ff ff ff       	jmpq   400b20 <.plt>

0000000000400c10 <__memmove_chk@plt>:
  400c10:	ff 25 72 34 20 00    	jmpq   *0x203472(%rip)        # 604088 <__memmove_chk@GLIBC_2.3.4>
  400c16:	68 0e 00 00 00       	pushq  $0xe
  400c1b:	e9 00 ff ff ff       	jmpq   400b20 <.plt>

0000000000400c20 <strtol@plt>:
  400c20:	ff 25 6a 34 20 00    	jmpq   *0x20346a(%rip)        # 604090 <strtol@GLIBC_2.2.5>
  400c26:	68 0f 00 00 00       	pushq  $0xf
  400c2b:	e9 f0 fe ff ff       	jmpq   400b20 <.plt>

0000000000400c30 <fflush@plt>:
  400c30:	ff 25 62 34 20 00    	jmpq   *0x203462(%rip)        # 604098 <fflush@GLIBC_2.2.5>
  400c36:	68 10 00 00 00       	pushq  $0x10
  400c3b:	e9 e0 fe ff ff       	jmpq   400b20 <.plt>

0000000000400c40 <__isoc99_sscanf@plt>:
  400c40:	ff 25 5a 34 20 00    	jmpq   *0x20345a(%rip)        # 6040a0 <__isoc99_sscanf@GLIBC_2.7>
  400c46:	68 11 00 00 00       	pushq  $0x11
  400c4b:	e9 d0 fe ff ff       	jmpq   400b20 <.plt>

0000000000400c50 <__printf_chk@plt>:
  400c50:	ff 25 52 34 20 00    	jmpq   *0x203452(%rip)        # 6040a8 <__printf_chk@GLIBC_2.3.4>
  400c56:	68 12 00 00 00       	pushq  $0x12
  400c5b:	e9 c0 fe ff ff       	jmpq   400b20 <.plt>

0000000000400c60 <fopen@plt>:
  400c60:	ff 25 4a 34 20 00    	jmpq   *0x20344a(%rip)        # 6040b0 <fopen@GLIBC_2.2.5>
  400c66:	68 13 00 00 00       	pushq  $0x13
  400c6b:	e9 b0 fe ff ff       	jmpq   400b20 <.plt>

0000000000400c70 <gethostname@plt>:
  400c70:	ff 25 42 34 20 00    	jmpq   *0x203442(%rip)        # 6040b8 <gethostname@GLIBC_2.2.5>
  400c76:	68 14 00 00 00       	pushq  $0x14
  400c7b:	e9 a0 fe ff ff       	jmpq   400b20 <.plt>

0000000000400c80 <exit@plt>:
  400c80:	ff 25 3a 34 20 00    	jmpq   *0x20343a(%rip)        # 6040c0 <exit@GLIBC_2.2.5>
  400c86:	68 15 00 00 00       	pushq  $0x15
  400c8b:	e9 90 fe ff ff       	jmpq   400b20 <.plt>

0000000000400c90 <connect@plt>:
  400c90:	ff 25 32 34 20 00    	jmpq   *0x203432(%rip)        # 6040c8 <connect@GLIBC_2.2.5>
  400c96:	68 16 00 00 00       	pushq  $0x16
  400c9b:	e9 80 fe ff ff       	jmpq   400b20 <.plt>

0000000000400ca0 <__fprintf_chk@plt>:
  400ca0:	ff 25 2a 34 20 00    	jmpq   *0x20342a(%rip)        # 6040d0 <__fprintf_chk@GLIBC_2.3.4>
  400ca6:	68 17 00 00 00       	pushq  $0x17
  400cab:	e9 70 fe ff ff       	jmpq   400b20 <.plt>

0000000000400cb0 <sleep@plt>:
  400cb0:	ff 25 22 34 20 00    	jmpq   *0x203422(%rip)        # 6040d8 <sleep@GLIBC_2.2.5>
  400cb6:	68 18 00 00 00       	pushq  $0x18
  400cbb:	e9 60 fe ff ff       	jmpq   400b20 <.plt>

0000000000400cc0 <__ctype_b_loc@plt>:
  400cc0:	ff 25 1a 34 20 00    	jmpq   *0x20341a(%rip)        # 6040e0 <__ctype_b_loc@GLIBC_2.3>
  400cc6:	68 19 00 00 00       	pushq  $0x19
  400ccb:	e9 50 fe ff ff       	jmpq   400b20 <.plt>

0000000000400cd0 <__sprintf_chk@plt>:
  400cd0:	ff 25 12 34 20 00    	jmpq   *0x203412(%rip)        # 6040e8 <__sprintf_chk@GLIBC_2.3.4>
  400cd6:	68 1a 00 00 00       	pushq  $0x1a
  400cdb:	e9 40 fe ff ff       	jmpq   400b20 <.plt>

0000000000400ce0 <socket@plt>:
  400ce0:	ff 25 0a 34 20 00    	jmpq   *0x20340a(%rip)        # 6040f0 <socket@GLIBC_2.2.5>
  400ce6:	68 1b 00 00 00       	pushq  $0x1b
  400ceb:	e9 30 fe ff ff       	jmpq   400b20 <.plt>

Disassembly of section .plt.got:

0000000000400cf0 <__gmon_start__@plt>:
  400cf0:	ff 25 02 33 20 00    	jmpq   *0x203302(%rip)        # 603ff8 <__gmon_start__>
  400cf6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000400d00 <_start>:
  400d00:	31 ed                	xor    %ebp,%ebp
  400d02:	49 89 d1             	mov    %rdx,%r9
  400d05:	5e                   	pop    %rsi
  400d06:	48 89 e2             	mov    %rsp,%rdx
  400d09:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400d0d:	50                   	push   %rax
  400d0e:	54                   	push   %rsp
  400d0f:	49 c7 c0 30 25 40 00 	mov    $0x402530,%r8
  400d16:	48 c7 c1 c0 24 40 00 	mov    $0x4024c0,%rcx
  400d1d:	48 c7 c7 f6 0d 40 00 	mov    $0x400df6,%rdi
  400d24:	e8 a7 fe ff ff       	callq  400bd0 <__libc_start_main@plt>
  400d29:	f4                   	hlt    
  400d2a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400d30 <deregister_tm_clones>:
  400d30:	b8 87 47 60 00       	mov    $0x604787,%eax
  400d35:	55                   	push   %rbp
  400d36:	48 2d 80 47 60 00    	sub    $0x604780,%rax
  400d3c:	48 83 f8 0e          	cmp    $0xe,%rax
  400d40:	48 89 e5             	mov    %rsp,%rbp
  400d43:	76 1b                	jbe    400d60 <deregister_tm_clones+0x30>
  400d45:	b8 00 00 00 00       	mov    $0x0,%eax
  400d4a:	48 85 c0             	test   %rax,%rax
  400d4d:	74 11                	je     400d60 <deregister_tm_clones+0x30>
  400d4f:	5d                   	pop    %rbp
  400d50:	bf 80 47 60 00       	mov    $0x604780,%edi
  400d55:	ff e0                	jmpq   *%rax
  400d57:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  400d5e:	00 00 
  400d60:	5d                   	pop    %rbp
  400d61:	c3                   	retq   
  400d62:	0f 1f 40 00          	nopl   0x0(%rax)
  400d66:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400d6d:	00 00 00 

0000000000400d70 <register_tm_clones>:
  400d70:	be 80 47 60 00       	mov    $0x604780,%esi
  400d75:	55                   	push   %rbp
  400d76:	48 81 ee 80 47 60 00 	sub    $0x604780,%rsi
  400d7d:	48 c1 fe 03          	sar    $0x3,%rsi
  400d81:	48 89 e5             	mov    %rsp,%rbp
  400d84:	48 89 f0             	mov    %rsi,%rax
  400d87:	48 c1 e8 3f          	shr    $0x3f,%rax
  400d8b:	48 01 c6             	add    %rax,%rsi
  400d8e:	48 d1 fe             	sar    %rsi
  400d91:	74 15                	je     400da8 <register_tm_clones+0x38>
  400d93:	b8 00 00 00 00       	mov    $0x0,%eax
  400d98:	48 85 c0             	test   %rax,%rax
  400d9b:	74 0b                	je     400da8 <register_tm_clones+0x38>
  400d9d:	5d                   	pop    %rbp
  400d9e:	bf 80 47 60 00       	mov    $0x604780,%edi
  400da3:	ff e0                	jmpq   *%rax
  400da5:	0f 1f 00             	nopl   (%rax)
  400da8:	5d                   	pop    %rbp
  400da9:	c3                   	retq   
  400daa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400db0 <__do_global_dtors_aux>:
  400db0:	80 3d f1 39 20 00 00 	cmpb   $0x0,0x2039f1(%rip)        # 6047a8 <completed.7594>
  400db7:	75 11                	jne    400dca <__do_global_dtors_aux+0x1a>
  400db9:	55                   	push   %rbp
  400dba:	48 89 e5             	mov    %rsp,%rbp
  400dbd:	e8 6e ff ff ff       	callq  400d30 <deregister_tm_clones>
  400dc2:	5d                   	pop    %rbp
  400dc3:	c6 05 de 39 20 00 01 	movb   $0x1,0x2039de(%rip)        # 6047a8 <completed.7594>
  400dca:	f3 c3                	repz retq 
  400dcc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400dd0 <frame_dummy>:
  400dd0:	bf 20 3e 60 00       	mov    $0x603e20,%edi
  400dd5:	48 83 3f 00          	cmpq   $0x0,(%rdi)
  400dd9:	75 05                	jne    400de0 <frame_dummy+0x10>
  400ddb:	eb 93                	jmp    400d70 <register_tm_clones>
  400ddd:	0f 1f 00             	nopl   (%rax)
  400de0:	b8 00 00 00 00       	mov    $0x0,%eax
  400de5:	48 85 c0             	test   %rax,%rax
  400de8:	74 f1                	je     400ddb <frame_dummy+0xb>
  400dea:	55                   	push   %rbp
  400deb:	48 89 e5             	mov    %rsp,%rbp
  400dee:	ff d0                	callq  *%rax
  400df0:	5d                   	pop    %rbp
  400df1:	e9 7a ff ff ff       	jmpq   400d70 <register_tm_clones>

0000000000400df6 <main>:
  400df6:	53                   	push   %rbx
  400df7:	83 ff 01             	cmp    $0x1,%edi
  400dfa:	75 10                	jne    400e0c <main+0x16>
  400dfc:	48 8b 05 8d 39 20 00 	mov    0x20398d(%rip),%rax        # 604790 <stdin@@GLIBC_2.2.5>
  400e03:	48 89 05 a6 39 20 00 	mov    %rax,0x2039a6(%rip)        # 6047b0 <infile>
  400e0a:	eb 63                	jmp    400e6f <main+0x79>
  400e0c:	48 89 f3             	mov    %rsi,%rbx
  400e0f:	83 ff 02             	cmp    $0x2,%edi
  400e12:	75 3a                	jne    400e4e <main+0x58>
  400e14:	48 8b 7e 08          	mov    0x8(%rsi),%rdi
  400e18:	be 44 25 40 00       	mov    $0x402544,%esi
  400e1d:	e8 3e fe ff ff       	callq  400c60 <fopen@plt>
  400e22:	48 89 05 87 39 20 00 	mov    %rax,0x203987(%rip)        # 6047b0 <infile>
  400e29:	48 85 c0             	test   %rax,%rax
  400e2c:	75 41                	jne    400e6f <main+0x79>
  400e2e:	48 8b 4b 08          	mov    0x8(%rbx),%rcx
  400e32:	48 8b 13             	mov    (%rbx),%rdx
  400e35:	be 46 25 40 00       	mov    $0x402546,%esi
  400e3a:	bf 01 00 00 00       	mov    $0x1,%edi
  400e3f:	e8 0c fe ff ff       	callq  400c50 <__printf_chk@plt>
  400e44:	bf 08 00 00 00       	mov    $0x8,%edi
  400e49:	e8 32 fe ff ff       	callq  400c80 <exit@plt>
  400e4e:	48 8b 16             	mov    (%rsi),%rdx
  400e51:	be 63 25 40 00       	mov    $0x402563,%esi
  400e56:	bf 01 00 00 00       	mov    $0x1,%edi
  400e5b:	b8 00 00 00 00       	mov    $0x0,%eax
  400e60:	e8 eb fd ff ff       	callq  400c50 <__printf_chk@plt>
  400e65:	bf 08 00 00 00       	mov    $0x8,%edi
  400e6a:	e8 11 fe ff ff       	callq  400c80 <exit@plt>
  400e6f:	e8 e0 05 00 00       	callq  401454 <initialize_bomb>
  400e74:	bf c8 25 40 00       	mov    $0x4025c8,%edi
  400e79:	e8 f2 fc ff ff       	callq  400b70 <puts@plt>
  400e7e:	bf 08 26 40 00       	mov    $0x402608,%edi
  400e83:	e8 e8 fc ff ff       	callq  400b70 <puts@plt>
  400e88:	e8 a9 08 00 00       	callq  401736 <read_line>
  400e8d:	48 89 c7             	mov    %rax,%rdi
  400e90:	e8 98 00 00 00       	callq  400f2d <phase_1>
  400e95:	e8 c2 09 00 00       	callq  40185c <phase_defused>
  400e9a:	bf 38 26 40 00       	mov    $0x402638,%edi
  400e9f:	e8 cc fc ff ff       	callq  400b70 <puts@plt>
  400ea4:	e8 8d 08 00 00       	callq  401736 <read_line>
  400ea9:	48 89 c7             	mov    %rax,%rdi
  400eac:	e8 98 00 00 00       	callq  400f49 <phase_2>
  400eb1:	e8 a6 09 00 00       	callq  40185c <phase_defused>
  400eb6:	bf 7d 25 40 00       	mov    $0x40257d,%edi
  400ebb:	e8 b0 fc ff ff       	callq  400b70 <puts@plt>
  400ec0:	e8 71 08 00 00       	callq  401736 <read_line>
  400ec5:	48 89 c7             	mov    %rax,%rdi
  400ec8:	e8 e4 00 00 00       	callq  400fb1 <phase_3>
  400ecd:	e8 8a 09 00 00       	callq  40185c <phase_defused>
  400ed2:	bf 9b 25 40 00       	mov    $0x40259b,%edi
  400ed7:	e8 94 fc ff ff       	callq  400b70 <puts@plt>
  400edc:	e8 55 08 00 00       	callq  401736 <read_line>
  400ee1:	48 89 c7             	mov    %rax,%rdi
  400ee4:	e8 d4 01 00 00       	callq  4010bd <phase_4>
  400ee9:	e8 6e 09 00 00       	callq  40185c <phase_defused>
  400eee:	bf 68 26 40 00       	mov    $0x402668,%edi
  400ef3:	e8 78 fc ff ff       	callq  400b70 <puts@plt>
  400ef8:	e8 39 08 00 00       	callq  401736 <read_line>
  400efd:	48 89 c7             	mov    %rax,%rdi
  400f00:	e8 2b 02 00 00       	callq  401130 <phase_5>
  400f05:	e8 52 09 00 00       	callq  40185c <phase_defused>
  400f0a:	bf aa 25 40 00       	mov    $0x4025aa,%edi
  400f0f:	e8 5c fc ff ff       	callq  400b70 <puts@plt>
  400f14:	e8 1d 08 00 00       	callq  401736 <read_line>
  400f19:	48 89 c7             	mov    %rax,%rdi
  400f1c:	e8 9b 02 00 00       	callq  4011bc <phase_6>
  400f21:	e8 36 09 00 00       	callq  40185c <phase_defused>
  400f26:	b8 00 00 00 00       	mov    $0x0,%eax
  400f2b:	5b                   	pop    %rbx
  400f2c:	c3                   	retq   

0000000000400f2d <phase_1>:
  400f2d:	48 83 ec 08          	sub    $0x8,%rsp
  400f31:	be 90 26 40 00       	mov    $0x402690,%esi
  400f36:	e8 b2 04 00 00       	callq  4013ed <strings_not_equal>
  400f3b:	85 c0                	test   %eax,%eax
  400f3d:	74 05                	je     400f44 <phase_1+0x17>
  400f3f:	e8 7d 07 00 00       	callq  4016c1 <explode_bomb>
  400f44:	48 83 c4 08          	add    $0x8,%rsp
  400f48:	c3                   	retq   

0000000000400f49 <phase_2>:
  400f49:	55                   	push   %rbp
  400f4a:	53                   	push   %rbx
  400f4b:	48 83 ec 28          	sub    $0x28,%rsp
  400f4f:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  400f56:	00 00 
  400f58:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  400f5d:	31 c0                	xor    %eax,%eax
  400f5f:	48 89 e6             	mov    %rsp,%rsi
  400f62:	e8 90 07 00 00       	callq  4016f7 <read_six_numbers>
  400f67:	83 3c 24 00          	cmpl   $0x0,(%rsp)
  400f6b:	79 05                	jns    400f72 <phase_2+0x29>
  400f6d:	e8 4f 07 00 00       	callq  4016c1 <explode_bomb>
  400f72:	48 89 e5             	mov    %rsp,%rbp
  400f75:	bb 01 00 00 00       	mov    $0x1,%ebx
  400f7a:	89 d8                	mov    %ebx,%eax
  400f7c:	03 45 00             	add    0x0(%rbp),%eax
  400f7f:	39 45 04             	cmp    %eax,0x4(%rbp)
  400f82:	74 05                	je     400f89 <phase_2+0x40>
  400f84:	e8 38 07 00 00       	callq  4016c1 <explode_bomb>
  400f89:	83 c3 01             	add    $0x1,%ebx
  400f8c:	48 83 c5 04          	add    $0x4,%rbp
  400f90:	83 fb 06             	cmp    $0x6,%ebx
  400f93:	75 e5                	jne    400f7a <phase_2+0x31>
  400f95:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  400f9a:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  400fa1:	00 00 
  400fa3:	74 05                	je     400faa <phase_2+0x61>
  400fa5:	e8 e6 fb ff ff       	callq  400b90 <__stack_chk_fail@plt>
  400faa:	48 83 c4 28          	add    $0x28,%rsp
  400fae:	5b                   	pop    %rbx
  400faf:	5d                   	pop    %rbp
  400fb0:	c3                   	retq   

0000000000400fb1 <phase_3>:
  400fb1:	48 83 ec 18          	sub    $0x18,%rsp
  400fb5:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  400fbc:	00 00 
  400fbe:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  400fc3:	31 c0                	xor    %eax,%eax
  400fc5:	48 8d 4c 24 04       	lea    0x4(%rsp),%rcx
  400fca:	48 89 e2             	mov    %rsp,%rdx
  400fcd:	be cd 29 40 00       	mov    $0x4029cd,%esi
  400fd2:	e8 69 fc ff ff       	callq  400c40 <__isoc99_sscanf@plt>
  400fd7:	83 f8 01             	cmp    $0x1,%eax
  400fda:	7f 05                	jg     400fe1 <phase_3+0x30>
  400fdc:	e8 e0 06 00 00       	callq  4016c1 <explode_bomb>
  400fe1:	83 3c 24 07          	cmpl   $0x7,(%rsp)
  400fe5:	77 63                	ja     40104a <phase_3+0x99>
  400fe7:	8b 04 24             	mov    (%rsp),%eax
  400fea:	ff 24 c5 00 27 40 00 	jmpq   *0x402700(,%rax,8)
  400ff1:	b8 79 02 00 00       	mov    $0x279,%eax
  400ff6:	eb 05                	jmp    400ffd <phase_3+0x4c>
  400ff8:	b8 00 00 00 00       	mov    $0x0,%eax
  400ffd:	83 e8 4e             	sub    $0x4e,%eax
  401000:	eb 05                	jmp    401007 <phase_3+0x56>
  401002:	b8 00 00 00 00       	mov    $0x0,%eax
  401007:	05 a6 03 00 00       	add    $0x3a6,%eax
  40100c:	eb 05                	jmp    401013 <phase_3+0x62>
  40100e:	b8 00 00 00 00       	mov    $0x0,%eax
  401013:	2d e0 01 00 00       	sub    $0x1e0,%eax
  401018:	eb 05                	jmp    40101f <phase_3+0x6e>
  40101a:	b8 00 00 00 00       	mov    $0x0,%eax
  40101f:	05 e0 01 00 00       	add    $0x1e0,%eax
  401024:	eb 05                	jmp    40102b <phase_3+0x7a>
  401026:	b8 00 00 00 00       	mov    $0x0,%eax
  40102b:	2d e0 01 00 00       	sub    $0x1e0,%eax
  401030:	eb 05                	jmp    401037 <phase_3+0x86>
  401032:	b8 00 00 00 00       	mov    $0x0,%eax
  401037:	05 e0 01 00 00       	add    $0x1e0,%eax
  40103c:	eb 05                	jmp    401043 <phase_3+0x92>
  40103e:	b8 00 00 00 00       	mov    $0x0,%eax
  401043:	2d e0 01 00 00       	sub    $0x1e0,%eax
  401048:	eb 0a                	jmp    401054 <phase_3+0xa3>
  40104a:	e8 72 06 00 00       	callq  4016c1 <explode_bomb>
  40104f:	b8 00 00 00 00       	mov    $0x0,%eax
  401054:	83 3c 24 05          	cmpl   $0x5,(%rsp)
  401058:	7f 06                	jg     401060 <phase_3+0xaf>
  40105a:	3b 44 24 04          	cmp    0x4(%rsp),%eax
  40105e:	74 05                	je     401065 <phase_3+0xb4>
  401060:	e8 5c 06 00 00       	callq  4016c1 <explode_bomb>
  401065:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  40106a:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401071:	00 00 
  401073:	74 05                	je     40107a <phase_3+0xc9>
  401075:	e8 16 fb ff ff       	callq  400b90 <__stack_chk_fail@plt>
  40107a:	48 83 c4 18          	add    $0x18,%rsp
  40107e:	c3                   	retq   

000000000040107f <func4>:
  40107f:	48 83 ec 08          	sub    $0x8,%rsp
  401083:	89 d0                	mov    %edx,%eax
  401085:	29 f0                	sub    %esi,%eax
  401087:	89 c1                	mov    %eax,%ecx
  401089:	c1 e9 1f             	shr    $0x1f,%ecx
  40108c:	01 c8                	add    %ecx,%eax
  40108e:	d1 f8                	sar    %eax
  401090:	8d 0c 30             	lea    (%rax,%rsi,1),%ecx
  401093:	39 f9                	cmp    %edi,%ecx
  401095:	7e 0c                	jle    4010a3 <func4+0x24>
  401097:	8d 51 ff             	lea    -0x1(%rcx),%edx
  40109a:	e8 e0 ff ff ff       	callq  40107f <func4>
  40109f:	01 c0                	add    %eax,%eax
  4010a1:	eb 15                	jmp    4010b8 <func4+0x39>
  4010a3:	b8 00 00 00 00       	mov    $0x0,%eax
  4010a8:	39 f9                	cmp    %edi,%ecx
  4010aa:	7d 0c                	jge    4010b8 <func4+0x39>
  4010ac:	8d 71 01             	lea    0x1(%rcx),%esi
  4010af:	e8 cb ff ff ff       	callq  40107f <func4>
  4010b4:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
  4010b8:	48 83 c4 08          	add    $0x8,%rsp
  4010bc:	c3                   	retq   

00000000004010bd <phase_4>:
  4010bd:	48 83 ec 18          	sub    $0x18,%rsp
  4010c1:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4010c8:	00 00 
  4010ca:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  4010cf:	31 c0                	xor    %eax,%eax
  4010d1:	48 8d 4c 24 04       	lea    0x4(%rsp),%rcx
  4010d6:	48 89 e2             	mov    %rsp,%rdx
  4010d9:	be cd 29 40 00       	mov    $0x4029cd,%esi
  4010de:	e8 5d fb ff ff       	callq  400c40 <__isoc99_sscanf@plt>
  4010e3:	83 f8 02             	cmp    $0x2,%eax
  4010e6:	75 06                	jne    4010ee <phase_4+0x31>
  4010e8:	83 3c 24 0e          	cmpl   $0xe,(%rsp)
  4010ec:	76 05                	jbe    4010f3 <phase_4+0x36>
  4010ee:	e8 ce 05 00 00       	callq  4016c1 <explode_bomb>
  4010f3:	ba 0e 00 00 00       	mov    $0xe,%edx
  4010f8:	be 00 00 00 00       	mov    $0x0,%esi
  4010fd:	8b 3c 24             	mov    (%rsp),%edi
  401100:	e8 7a ff ff ff       	callq  40107f <func4>
  401105:	83 f8 07             	cmp    $0x7,%eax
  401108:	75 07                	jne    401111 <phase_4+0x54>
  40110a:	83 7c 24 04 07       	cmpl   $0x7,0x4(%rsp)
  40110f:	74 05                	je     401116 <phase_4+0x59>
  401111:	e8 ab 05 00 00       	callq  4016c1 <explode_bomb>
  401116:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  40111b:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401122:	00 00 
  401124:	74 05                	je     40112b <phase_4+0x6e>
  401126:	e8 65 fa ff ff       	callq  400b90 <__stack_chk_fail@plt>
  40112b:	48 83 c4 18          	add    $0x18,%rsp
  40112f:	c3                   	retq   

0000000000401130 <phase_5>:
  401130:	48 83 ec 18          	sub    $0x18,%rsp
  401134:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40113b:	00 00 
  40113d:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  401142:	31 c0                	xor    %eax,%eax
  401144:	48 8d 4c 24 04       	lea    0x4(%rsp),%rcx
  401149:	48 89 e2             	mov    %rsp,%rdx
  40114c:	be cd 29 40 00       	mov    $0x4029cd,%esi
  401151:	e8 ea fa ff ff       	callq  400c40 <__isoc99_sscanf@plt>
  401156:	83 f8 01             	cmp    $0x1,%eax
  401159:	7f 05                	jg     401160 <phase_5+0x30>
  40115b:	e8 61 05 00 00       	callq  4016c1 <explode_bomb>
  401160:	8b 04 24             	mov    (%rsp),%eax
  401163:	83 e0 0f             	and    $0xf,%eax
  401166:	89 04 24             	mov    %eax,(%rsp)
  401169:	83 f8 0f             	cmp    $0xf,%eax
  40116c:	74 2f                	je     40119d <phase_5+0x6d>
  40116e:	b9 00 00 00 00       	mov    $0x0,%ecx
  401173:	ba 00 00 00 00       	mov    $0x0,%edx
  401178:	83 c2 01             	add    $0x1,%edx
  40117b:	48 98                	cltq   
  40117d:	8b 04 85 40 27 40 00 	mov    0x402740(,%rax,4),%eax
  401184:	01 c1                	add    %eax,%ecx
  401186:	83 f8 0f             	cmp    $0xf,%eax
  401189:	75 ed                	jne    401178 <phase_5+0x48>
  40118b:	c7 04 24 0f 00 00 00 	movl   $0xf,(%rsp)
  401192:	83 fa 0f             	cmp    $0xf,%edx
  401195:	75 06                	jne    40119d <phase_5+0x6d>
  401197:	3b 4c 24 04          	cmp    0x4(%rsp),%ecx
  40119b:	74 05                	je     4011a2 <phase_5+0x72>
  40119d:	e8 1f 05 00 00       	callq  4016c1 <explode_bomb>
  4011a2:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  4011a7:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4011ae:	00 00 
  4011b0:	74 05                	je     4011b7 <phase_5+0x87>
  4011b2:	e8 d9 f9 ff ff       	callq  400b90 <__stack_chk_fail@plt>
  4011b7:	48 83 c4 18          	add    $0x18,%rsp
  4011bb:	c3                   	retq   

00000000004011bc <phase_6>:
  4011bc:	41 55                	push   %r13
  4011be:	41 54                	push   %r12
  4011c0:	55                   	push   %rbp
  4011c1:	53                   	push   %rbx
  4011c2:	48 83 ec 68          	sub    $0x68,%rsp
  4011c6:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4011cd:	00 00 
  4011cf:	48 89 44 24 58       	mov    %rax,0x58(%rsp)
  4011d4:	31 c0                	xor    %eax,%eax
  4011d6:	48 89 e6             	mov    %rsp,%rsi
  4011d9:	e8 19 05 00 00       	callq  4016f7 <read_six_numbers>
  4011de:	49 89 e4             	mov    %rsp,%r12
  4011e1:	41 bd 00 00 00 00    	mov    $0x0,%r13d
  4011e7:	4c 89 e5             	mov    %r12,%rbp
  4011ea:	41 8b 04 24          	mov    (%r12),%eax
  4011ee:	83 e8 01             	sub    $0x1,%eax
  4011f1:	83 f8 05             	cmp    $0x5,%eax
  4011f4:	76 05                	jbe    4011fb <phase_6+0x3f>
  4011f6:	e8 c6 04 00 00       	callq  4016c1 <explode_bomb>
  4011fb:	41 83 c5 01          	add    $0x1,%r13d
  4011ff:	41 83 fd 06          	cmp    $0x6,%r13d
  401203:	74 3d                	je     401242 <phase_6+0x86>
  401205:	44 89 eb             	mov    %r13d,%ebx
  401208:	48 63 c3             	movslq %ebx,%rax
  40120b:	8b 04 84             	mov    (%rsp,%rax,4),%eax
  40120e:	39 45 00             	cmp    %eax,0x0(%rbp)
  401211:	75 05                	jne    401218 <phase_6+0x5c>
  401213:	e8 a9 04 00 00       	callq  4016c1 <explode_bomb>
  401218:	83 c3 01             	add    $0x1,%ebx
  40121b:	83 fb 05             	cmp    $0x5,%ebx
  40121e:	7e e8                	jle    401208 <phase_6+0x4c>
  401220:	49 83 c4 04          	add    $0x4,%r12
  401224:	eb c1                	jmp    4011e7 <phase_6+0x2b>
  401226:	48 8b 52 08          	mov    0x8(%rdx),%rdx
  40122a:	83 c0 01             	add    $0x1,%eax
  40122d:	39 c8                	cmp    %ecx,%eax
  40122f:	75 f5                	jne    401226 <phase_6+0x6a>
  401231:	48 89 54 74 20       	mov    %rdx,0x20(%rsp,%rsi,2)
  401236:	48 83 c6 04          	add    $0x4,%rsi
  40123a:	48 83 fe 18          	cmp    $0x18,%rsi
  40123e:	75 07                	jne    401247 <phase_6+0x8b>
  401240:	eb 19                	jmp    40125b <phase_6+0x9f>
  401242:	be 00 00 00 00       	mov    $0x0,%esi
  401247:	8b 0c 34             	mov    (%rsp,%rsi,1),%ecx
  40124a:	b8 01 00 00 00       	mov    $0x1,%eax
  40124f:	ba f0 42 60 00       	mov    $0x6042f0,%edx
  401254:	83 f9 01             	cmp    $0x1,%ecx
  401257:	7f cd                	jg     401226 <phase_6+0x6a>
  401259:	eb d6                	jmp    401231 <phase_6+0x75>
  40125b:	48 8b 5c 24 20       	mov    0x20(%rsp),%rbx
  401260:	48 8d 44 24 20       	lea    0x20(%rsp),%rax
  401265:	48 8d 74 24 48       	lea    0x48(%rsp),%rsi
  40126a:	48 89 d9             	mov    %rbx,%rcx
  40126d:	48 8b 50 08          	mov    0x8(%rax),%rdx
  401271:	48 89 51 08          	mov    %rdx,0x8(%rcx)
  401275:	48 83 c0 08          	add    $0x8,%rax
  401279:	48 89 d1             	mov    %rdx,%rcx
  40127c:	48 39 f0             	cmp    %rsi,%rax
  40127f:	75 ec                	jne    40126d <phase_6+0xb1>
  401281:	48 c7 42 08 00 00 00 	movq   $0x0,0x8(%rdx)
  401288:	00 
  401289:	bd 05 00 00 00       	mov    $0x5,%ebp
  40128e:	48 8b 43 08          	mov    0x8(%rbx),%rax
  401292:	8b 00                	mov    (%rax),%eax
  401294:	39 03                	cmp    %eax,(%rbx)
  401296:	7d 05                	jge    40129d <phase_6+0xe1>
  401298:	e8 24 04 00 00       	callq  4016c1 <explode_bomb>
  40129d:	48 8b 5b 08          	mov    0x8(%rbx),%rbx
  4012a1:	83 ed 01             	sub    $0x1,%ebp
  4012a4:	75 e8                	jne    40128e <phase_6+0xd2>
  4012a6:	48 8b 44 24 58       	mov    0x58(%rsp),%rax
  4012ab:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4012b2:	00 00 
  4012b4:	74 05                	je     4012bb <phase_6+0xff>
  4012b6:	e8 d5 f8 ff ff       	callq  400b90 <__stack_chk_fail@plt>
  4012bb:	48 83 c4 68          	add    $0x68,%rsp
  4012bf:	5b                   	pop    %rbx
  4012c0:	5d                   	pop    %rbp
  4012c1:	41 5c                	pop    %r12
  4012c3:	41 5d                	pop    %r13
  4012c5:	c3                   	retq   

00000000004012c6 <fun7>:
  4012c6:	48 83 ec 08          	sub    $0x8,%rsp
  4012ca:	48 85 ff             	test   %rdi,%rdi
  4012cd:	74 2b                	je     4012fa <fun7+0x34>
  4012cf:	8b 17                	mov    (%rdi),%edx
  4012d1:	39 f2                	cmp    %esi,%edx
  4012d3:	7e 0d                	jle    4012e2 <fun7+0x1c>
  4012d5:	48 8b 7f 08          	mov    0x8(%rdi),%rdi
  4012d9:	e8 e8 ff ff ff       	callq  4012c6 <fun7>
  4012de:	01 c0                	add    %eax,%eax
  4012e0:	eb 1d                	jmp    4012ff <fun7+0x39>
  4012e2:	b8 00 00 00 00       	mov    $0x0,%eax
  4012e7:	39 f2                	cmp    %esi,%edx
  4012e9:	74 14                	je     4012ff <fun7+0x39>
  4012eb:	48 8b 7f 10          	mov    0x10(%rdi),%rdi
  4012ef:	e8 d2 ff ff ff       	callq  4012c6 <fun7>
  4012f4:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
  4012f8:	eb 05                	jmp    4012ff <fun7+0x39>
  4012fa:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4012ff:	48 83 c4 08          	add    $0x8,%rsp
  401303:	c3                   	retq   

0000000000401304 <secret_phase>:
  401304:	53                   	push   %rbx
  401305:	e8 2c 04 00 00       	callq  401736 <read_line>
  40130a:	ba 0a 00 00 00       	mov    $0xa,%edx
  40130f:	be 00 00 00 00       	mov    $0x0,%esi
  401314:	48 89 c7             	mov    %rax,%rdi
  401317:	e8 04 f9 ff ff       	callq  400c20 <strtol@plt>
  40131c:	48 89 c3             	mov    %rax,%rbx
  40131f:	8d 40 ff             	lea    -0x1(%rax),%eax
  401322:	3d e8 03 00 00       	cmp    $0x3e8,%eax
  401327:	76 05                	jbe    40132e <secret_phase+0x2a>
  401329:	e8 93 03 00 00       	callq  4016c1 <explode_bomb>
  40132e:	89 de                	mov    %ebx,%esi
  401330:	bf 10 41 60 00       	mov    $0x604110,%edi
  401335:	e8 8c ff ff ff       	callq  4012c6 <fun7>
  40133a:	85 c0                	test   %eax,%eax
  40133c:	74 05                	je     401343 <secret_phase+0x3f>
  40133e:	e8 7e 03 00 00       	callq  4016c1 <explode_bomb>
  401343:	bf c0 26 40 00       	mov    $0x4026c0,%edi
  401348:	e8 23 f8 ff ff       	callq  400b70 <puts@plt>
  40134d:	e8 0a 05 00 00       	callq  40185c <phase_defused>
  401352:	5b                   	pop    %rbx
  401353:	c3                   	retq   

0000000000401354 <sig_handler>:
  401354:	48 83 ec 08          	sub    $0x8,%rsp
  401358:	bf 80 27 40 00       	mov    $0x402780,%edi
  40135d:	e8 0e f8 ff ff       	callq  400b70 <puts@plt>
  401362:	bf 03 00 00 00       	mov    $0x3,%edi
  401367:	e8 44 f9 ff ff       	callq  400cb0 <sleep@plt>
  40136c:	be 49 29 40 00       	mov    $0x402949,%esi
  401371:	bf 01 00 00 00       	mov    $0x1,%edi
  401376:	b8 00 00 00 00       	mov    $0x0,%eax
  40137b:	e8 d0 f8 ff ff       	callq  400c50 <__printf_chk@plt>
  401380:	48 8b 3d f9 33 20 00 	mov    0x2033f9(%rip),%rdi        # 604780 <stdout@@GLIBC_2.2.5>
  401387:	e8 a4 f8 ff ff       	callq  400c30 <fflush@plt>
  40138c:	bf 01 00 00 00       	mov    $0x1,%edi
  401391:	e8 1a f9 ff ff       	callq  400cb0 <sleep@plt>
  401396:	bf 51 29 40 00       	mov    $0x402951,%edi
  40139b:	e8 d0 f7 ff ff       	callq  400b70 <puts@plt>
  4013a0:	bf 10 00 00 00       	mov    $0x10,%edi
  4013a5:	e8 d6 f8 ff ff       	callq  400c80 <exit@plt>

00000000004013aa <invalid_phase>:
  4013aa:	48 83 ec 08          	sub    $0x8,%rsp
  4013ae:	48 89 fa             	mov    %rdi,%rdx
  4013b1:	be 59 29 40 00       	mov    $0x402959,%esi
  4013b6:	bf 01 00 00 00       	mov    $0x1,%edi
  4013bb:	b8 00 00 00 00       	mov    $0x0,%eax
  4013c0:	e8 8b f8 ff ff       	callq  400c50 <__printf_chk@plt>
  4013c5:	bf 08 00 00 00       	mov    $0x8,%edi
  4013ca:	e8 b1 f8 ff ff       	callq  400c80 <exit@plt>

00000000004013cf <string_length>:
  4013cf:	80 3f 00             	cmpb   $0x0,(%rdi)
  4013d2:	74 13                	je     4013e7 <string_length+0x18>
  4013d4:	b8 00 00 00 00       	mov    $0x0,%eax
  4013d9:	48 83 c7 01          	add    $0x1,%rdi
  4013dd:	83 c0 01             	add    $0x1,%eax
  4013e0:	80 3f 00             	cmpb   $0x0,(%rdi)
  4013e3:	75 f4                	jne    4013d9 <string_length+0xa>
  4013e5:	f3 c3                	repz retq 
  4013e7:	b8 00 00 00 00       	mov    $0x0,%eax
  4013ec:	c3                   	retq   

00000000004013ed <strings_not_equal>:
  4013ed:	41 54                	push   %r12
  4013ef:	55                   	push   %rbp
  4013f0:	53                   	push   %rbx
  4013f1:	48 89 fb             	mov    %rdi,%rbx
  4013f4:	48 89 f5             	mov    %rsi,%rbp
  4013f7:	e8 d3 ff ff ff       	callq  4013cf <string_length>
  4013fc:	41 89 c4             	mov    %eax,%r12d
  4013ff:	48 89 ef             	mov    %rbp,%rdi
  401402:	e8 c8 ff ff ff       	callq  4013cf <string_length>
  401407:	ba 01 00 00 00       	mov    $0x1,%edx
  40140c:	41 39 c4             	cmp    %eax,%r12d
  40140f:	75 3c                	jne    40144d <strings_not_equal+0x60>
  401411:	0f b6 03             	movzbl (%rbx),%eax
  401414:	84 c0                	test   %al,%al
  401416:	74 22                	je     40143a <strings_not_equal+0x4d>
  401418:	3a 45 00             	cmp    0x0(%rbp),%al
  40141b:	74 07                	je     401424 <strings_not_equal+0x37>
  40141d:	eb 22                	jmp    401441 <strings_not_equal+0x54>
  40141f:	3a 45 00             	cmp    0x0(%rbp),%al
  401422:	75 24                	jne    401448 <strings_not_equal+0x5b>
  401424:	48 83 c3 01          	add    $0x1,%rbx
  401428:	48 83 c5 01          	add    $0x1,%rbp
  40142c:	0f b6 03             	movzbl (%rbx),%eax
  40142f:	84 c0                	test   %al,%al
  401431:	75 ec                	jne    40141f <strings_not_equal+0x32>
  401433:	ba 00 00 00 00       	mov    $0x0,%edx
  401438:	eb 13                	jmp    40144d <strings_not_equal+0x60>
  40143a:	ba 00 00 00 00       	mov    $0x0,%edx
  40143f:	eb 0c                	jmp    40144d <strings_not_equal+0x60>
  401441:	ba 01 00 00 00       	mov    $0x1,%edx
  401446:	eb 05                	jmp    40144d <strings_not_equal+0x60>
  401448:	ba 01 00 00 00       	mov    $0x1,%edx
  40144d:	89 d0                	mov    %edx,%eax
  40144f:	5b                   	pop    %rbx
  401450:	5d                   	pop    %rbp
  401451:	41 5c                	pop    %r12
  401453:	c3                   	retq   

0000000000401454 <initialize_bomb>:
  401454:	53                   	push   %rbx
  401455:	48 81 ec 50 20 00 00 	sub    $0x2050,%rsp
  40145c:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401463:	00 00 
  401465:	48 89 84 24 48 20 00 	mov    %rax,0x2048(%rsp)
  40146c:	00 
  40146d:	31 c0                	xor    %eax,%eax
  40146f:	be 54 13 40 00       	mov    $0x401354,%esi
  401474:	bf 02 00 00 00       	mov    $0x2,%edi
  401479:	e8 72 f7 ff ff       	callq  400bf0 <signal@plt>
  40147e:	be 40 00 00 00       	mov    $0x40,%esi
  401483:	48 89 e7             	mov    %rsp,%rdi
  401486:	e8 e5 f7 ff ff       	callq  400c70 <gethostname@plt>
  40148b:	85 c0                	test   %eax,%eax
  40148d:	75 13                	jne    4014a2 <initialize_bomb+0x4e>
  40148f:	48 8b 3d ea 2e 20 00 	mov    0x202eea(%rip),%rdi        # 604380 <host_table>
  401496:	bb 88 43 60 00       	mov    $0x604388,%ebx
  40149b:	48 85 ff             	test   %rdi,%rdi
  40149e:	75 16                	jne    4014b6 <initialize_bomb+0x62>
  4014a0:	eb 52                	jmp    4014f4 <initialize_bomb+0xa0>
  4014a2:	bf b8 27 40 00       	mov    $0x4027b8,%edi
  4014a7:	e8 c4 f6 ff ff       	callq  400b70 <puts@plt>
  4014ac:	bf 08 00 00 00       	mov    $0x8,%edi
  4014b1:	e8 ca f7 ff ff       	callq  400c80 <exit@plt>
  4014b6:	48 89 e6             	mov    %rsp,%rsi
  4014b9:	e8 82 f6 ff ff       	callq  400b40 <strcasecmp@plt>
  4014be:	85 c0                	test   %eax,%eax
  4014c0:	74 46                	je     401508 <initialize_bomb+0xb4>
  4014c2:	48 83 c3 08          	add    $0x8,%rbx
  4014c6:	48 8b 7b f8          	mov    -0x8(%rbx),%rdi
  4014ca:	48 85 ff             	test   %rdi,%rdi
  4014cd:	75 e7                	jne    4014b6 <initialize_bomb+0x62>
  4014cf:	eb 23                	jmp    4014f4 <initialize_bomb+0xa0>
  4014d1:	48 8d 54 24 40       	lea    0x40(%rsp),%rdx
  4014d6:	be 6a 29 40 00       	mov    $0x40296a,%esi
  4014db:	bf 01 00 00 00       	mov    $0x1,%edi
  4014e0:	b8 00 00 00 00       	mov    $0x0,%eax
  4014e5:	e8 66 f7 ff ff       	callq  400c50 <__printf_chk@plt>
  4014ea:	bf 08 00 00 00       	mov    $0x8,%edi
  4014ef:	e8 8c f7 ff ff       	callq  400c80 <exit@plt>
  4014f4:	bf f0 27 40 00       	mov    $0x4027f0,%edi
  4014f9:	e8 72 f6 ff ff       	callq  400b70 <puts@plt>
  4014fe:	bf 08 00 00 00       	mov    $0x8,%edi
  401503:	e8 78 f7 ff ff       	callq  400c80 <exit@plt>
  401508:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
  40150d:	e8 49 0d 00 00       	callq  40225b <init_driver>
  401512:	85 c0                	test   %eax,%eax
  401514:	78 bb                	js     4014d1 <initialize_bomb+0x7d>
  401516:	48 8b 84 24 48 20 00 	mov    0x2048(%rsp),%rax
  40151d:	00 
  40151e:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401525:	00 00 
  401527:	74 05                	je     40152e <initialize_bomb+0xda>
  401529:	e8 62 f6 ff ff       	callq  400b90 <__stack_chk_fail@plt>
  40152e:	48 81 c4 50 20 00 00 	add    $0x2050,%rsp
  401535:	5b                   	pop    %rbx
  401536:	c3                   	retq   

0000000000401537 <initialize_bomb_solve>:
  401537:	f3 c3                	repz retq 

0000000000401539 <blank_line>:
  401539:	55                   	push   %rbp
  40153a:	53                   	push   %rbx
  40153b:	48 83 ec 08          	sub    $0x8,%rsp
  40153f:	48 89 fd             	mov    %rdi,%rbp
  401542:	eb 17                	jmp    40155b <blank_line+0x22>
  401544:	e8 77 f7 ff ff       	callq  400cc0 <__ctype_b_loc@plt>
  401549:	48 83 c5 01          	add    $0x1,%rbp
  40154d:	48 0f be db          	movsbq %bl,%rbx
  401551:	48 8b 00             	mov    (%rax),%rax
  401554:	f6 44 58 01 20       	testb  $0x20,0x1(%rax,%rbx,2)
  401559:	74 0f                	je     40156a <blank_line+0x31>
  40155b:	0f b6 5d 00          	movzbl 0x0(%rbp),%ebx
  40155f:	84 db                	test   %bl,%bl
  401561:	75 e1                	jne    401544 <blank_line+0xb>
  401563:	b8 01 00 00 00       	mov    $0x1,%eax
  401568:	eb 05                	jmp    40156f <blank_line+0x36>
  40156a:	b8 00 00 00 00       	mov    $0x0,%eax
  40156f:	48 83 c4 08          	add    $0x8,%rsp
  401573:	5b                   	pop    %rbx
  401574:	5d                   	pop    %rbp
  401575:	c3                   	retq   

0000000000401576 <skip>:
  401576:	53                   	push   %rbx
  401577:	48 63 05 2e 32 20 00 	movslq 0x20322e(%rip),%rax        # 6047ac <num_input_strings>
  40157e:	48 8d 3c 80          	lea    (%rax,%rax,4),%rdi
  401582:	48 c1 e7 04          	shl    $0x4,%rdi
  401586:	48 81 c7 c0 47 60 00 	add    $0x6047c0,%rdi
  40158d:	48 8b 15 1c 32 20 00 	mov    0x20321c(%rip),%rdx        # 6047b0 <infile>
  401594:	be 50 00 00 00       	mov    $0x50,%esi
  401599:	e8 42 f6 ff ff       	callq  400be0 <fgets@plt>
  40159e:	48 89 c3             	mov    %rax,%rbx
  4015a1:	48 85 c0             	test   %rax,%rax
  4015a4:	74 0c                	je     4015b2 <skip+0x3c>
  4015a6:	48 89 c7             	mov    %rax,%rdi
  4015a9:	e8 8b ff ff ff       	callq  401539 <blank_line>
  4015ae:	85 c0                	test   %eax,%eax
  4015b0:	75 c5                	jne    401577 <skip+0x1>
  4015b2:	48 89 d8             	mov    %rbx,%rax
  4015b5:	5b                   	pop    %rbx
  4015b6:	c3                   	retq   

00000000004015b7 <send_msg>:
  4015b7:	48 81 ec 18 40 00 00 	sub    $0x4018,%rsp
  4015be:	41 89 f8             	mov    %edi,%r8d
  4015c1:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4015c8:	00 00 
  4015ca:	48 89 84 24 08 40 00 	mov    %rax,0x4008(%rsp)
  4015d1:	00 
  4015d2:	31 c0                	xor    %eax,%eax
  4015d4:	8b 35 d2 31 20 00    	mov    0x2031d2(%rip),%esi        # 6047ac <num_input_strings>
  4015da:	8d 46 ff             	lea    -0x1(%rsi),%eax
  4015dd:	48 98                	cltq   
  4015df:	48 8d 14 80          	lea    (%rax,%rax,4),%rdx
  4015e3:	48 c1 e2 04          	shl    $0x4,%rdx
  4015e7:	48 81 c2 c0 47 60 00 	add    $0x6047c0,%rdx
  4015ee:	b8 00 00 00 00       	mov    $0x0,%eax
  4015f3:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4015fa:	48 89 d7             	mov    %rdx,%rdi
  4015fd:	f2 ae                	repnz scas %es:(%rdi),%al
  4015ff:	48 f7 d1             	not    %rcx
  401602:	48 83 c1 63          	add    $0x63,%rcx
  401606:	48 81 f9 00 20 00 00 	cmp    $0x2000,%rcx
  40160d:	76 19                	jbe    401628 <send_msg+0x71>
  40160f:	be 28 28 40 00       	mov    $0x402828,%esi
  401614:	bf 01 00 00 00       	mov    $0x1,%edi
  401619:	e8 32 f6 ff ff       	callq  400c50 <__printf_chk@plt>
  40161e:	bf 08 00 00 00       	mov    $0x8,%edi
  401623:	e8 58 f6 ff ff       	callq  400c80 <exit@plt>
  401628:	45 85 c0             	test   %r8d,%r8d
  40162b:	41 b9 8c 29 40 00    	mov    $0x40298c,%r9d
  401631:	b8 84 29 40 00       	mov    $0x402984,%eax
  401636:	4c 0f 45 c8          	cmovne %rax,%r9
  40163a:	52                   	push   %rdx
  40163b:	56                   	push   %rsi
  40163c:	44 8b 05 31 2d 20 00 	mov    0x202d31(%rip),%r8d        # 604374 <bomb_id>
  401643:	b9 95 29 40 00       	mov    $0x402995,%ecx
  401648:	ba 00 20 00 00       	mov    $0x2000,%edx
  40164d:	be 01 00 00 00       	mov    $0x1,%esi
  401652:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
  401657:	b8 00 00 00 00       	mov    $0x0,%eax
  40165c:	e8 6f f6 ff ff       	callq  400cd0 <__sprintf_chk@plt>
  401661:	4c 8d 84 24 10 20 00 	lea    0x2010(%rsp),%r8
  401668:	00 
  401669:	b9 00 00 00 00       	mov    $0x0,%ecx
  40166e:	48 8d 54 24 10       	lea    0x10(%rsp),%rdx
  401673:	be 50 43 60 00       	mov    $0x604350,%esi
  401678:	bf 68 43 60 00       	mov    $0x604368,%edi
  40167d:	e8 cc 0d 00 00       	callq  40244e <driver_post>
  401682:	48 83 c4 10          	add    $0x10,%rsp
  401686:	85 c0                	test   %eax,%eax
  401688:	79 17                	jns    4016a1 <send_msg+0xea>
  40168a:	48 8d bc 24 00 20 00 	lea    0x2000(%rsp),%rdi
  401691:	00 
  401692:	e8 d9 f4 ff ff       	callq  400b70 <puts@plt>
  401697:	bf 00 00 00 00       	mov    $0x0,%edi
  40169c:	e8 df f5 ff ff       	callq  400c80 <exit@plt>
  4016a1:	48 8b 84 24 08 40 00 	mov    0x4008(%rsp),%rax
  4016a8:	00 
  4016a9:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4016b0:	00 00 
  4016b2:	74 05                	je     4016b9 <send_msg+0x102>
  4016b4:	e8 d7 f4 ff ff       	callq  400b90 <__stack_chk_fail@plt>
  4016b9:	48 81 c4 18 40 00 00 	add    $0x4018,%rsp
  4016c0:	c3                   	retq   

00000000004016c1 <explode_bomb>:
  4016c1:	48 83 ec 08          	sub    $0x8,%rsp
  4016c5:	bf a1 29 40 00       	mov    $0x4029a1,%edi
  4016ca:	e8 a1 f4 ff ff       	callq  400b70 <puts@plt>
  4016cf:	bf aa 29 40 00       	mov    $0x4029aa,%edi
  4016d4:	e8 97 f4 ff ff       	callq  400b70 <puts@plt>
  4016d9:	bf 00 00 00 00       	mov    $0x0,%edi
  4016de:	e8 d4 fe ff ff       	callq  4015b7 <send_msg>
  4016e3:	bf 50 28 40 00       	mov    $0x402850,%edi
  4016e8:	e8 83 f4 ff ff       	callq  400b70 <puts@plt>
  4016ed:	bf 08 00 00 00       	mov    $0x8,%edi
  4016f2:	e8 89 f5 ff ff       	callq  400c80 <exit@plt>

00000000004016f7 <read_six_numbers>:
  4016f7:	48 83 ec 08          	sub    $0x8,%rsp
  4016fb:	48 89 f2             	mov    %rsi,%rdx
  4016fe:	48 8d 4e 04          	lea    0x4(%rsi),%rcx
  401702:	48 8d 46 14          	lea    0x14(%rsi),%rax
  401706:	50                   	push   %rax
  401707:	48 8d 46 10          	lea    0x10(%rsi),%rax
  40170b:	50                   	push   %rax
  40170c:	4c 8d 4e 0c          	lea    0xc(%rsi),%r9
  401710:	4c 8d 46 08          	lea    0x8(%rsi),%r8
  401714:	be c1 29 40 00       	mov    $0x4029c1,%esi
  401719:	b8 00 00 00 00       	mov    $0x0,%eax
  40171e:	e8 1d f5 ff ff       	callq  400c40 <__isoc99_sscanf@plt>
  401723:	48 83 c4 10          	add    $0x10,%rsp
  401727:	83 f8 05             	cmp    $0x5,%eax
  40172a:	7f 05                	jg     401731 <read_six_numbers+0x3a>
  40172c:	e8 90 ff ff ff       	callq  4016c1 <explode_bomb>
  401731:	48 83 c4 08          	add    $0x8,%rsp
  401735:	c3                   	retq   

0000000000401736 <read_line>:
  401736:	48 83 ec 08          	sub    $0x8,%rsp
  40173a:	b8 00 00 00 00       	mov    $0x0,%eax
  40173f:	e8 32 fe ff ff       	callq  401576 <skip>
  401744:	48 85 c0             	test   %rax,%rax
  401747:	75 6e                	jne    4017b7 <read_line+0x81>
  401749:	48 8b 05 40 30 20 00 	mov    0x203040(%rip),%rax        # 604790 <stdin@@GLIBC_2.2.5>
  401750:	48 39 05 59 30 20 00 	cmp    %rax,0x203059(%rip)        # 6047b0 <infile>
  401757:	75 14                	jne    40176d <read_line+0x37>
  401759:	bf d3 29 40 00       	mov    $0x4029d3,%edi
  40175e:	e8 0d f4 ff ff       	callq  400b70 <puts@plt>
  401763:	bf 08 00 00 00       	mov    $0x8,%edi
  401768:	e8 13 f5 ff ff       	callq  400c80 <exit@plt>
  40176d:	bf f1 29 40 00       	mov    $0x4029f1,%edi
  401772:	e8 b9 f3 ff ff       	callq  400b30 <getenv@plt>
  401777:	48 85 c0             	test   %rax,%rax
  40177a:	74 0a                	je     401786 <read_line+0x50>
  40177c:	bf 00 00 00 00       	mov    $0x0,%edi
  401781:	e8 fa f4 ff ff       	callq  400c80 <exit@plt>
  401786:	48 8b 05 03 30 20 00 	mov    0x203003(%rip),%rax        # 604790 <stdin@@GLIBC_2.2.5>
  40178d:	48 89 05 1c 30 20 00 	mov    %rax,0x20301c(%rip)        # 6047b0 <infile>
  401794:	b8 00 00 00 00       	mov    $0x0,%eax
  401799:	e8 d8 fd ff ff       	callq  401576 <skip>
  40179e:	48 85 c0             	test   %rax,%rax
  4017a1:	75 14                	jne    4017b7 <read_line+0x81>
  4017a3:	bf d3 29 40 00       	mov    $0x4029d3,%edi
  4017a8:	e8 c3 f3 ff ff       	callq  400b70 <puts@plt>
  4017ad:	bf 00 00 00 00       	mov    $0x0,%edi
  4017b2:	e8 c9 f4 ff ff       	callq  400c80 <exit@plt>
  4017b7:	8b 35 ef 2f 20 00    	mov    0x202fef(%rip),%esi        # 6047ac <num_input_strings>
  4017bd:	48 63 c6             	movslq %esi,%rax
  4017c0:	48 8d 14 80          	lea    (%rax,%rax,4),%rdx
  4017c4:	48 c1 e2 04          	shl    $0x4,%rdx
  4017c8:	48 81 c2 c0 47 60 00 	add    $0x6047c0,%rdx
  4017cf:	b8 00 00 00 00       	mov    $0x0,%eax
  4017d4:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4017db:	48 89 d7             	mov    %rdx,%rdi
  4017de:	f2 ae                	repnz scas %es:(%rdi),%al
  4017e0:	48 f7 d1             	not    %rcx
  4017e3:	48 83 e9 01          	sub    $0x1,%rcx
  4017e7:	83 f9 4e             	cmp    $0x4e,%ecx
  4017ea:	7e 46                	jle    401832 <read_line+0xfc>
  4017ec:	bf fc 29 40 00       	mov    $0x4029fc,%edi
  4017f1:	e8 7a f3 ff ff       	callq  400b70 <puts@plt>
  4017f6:	8b 05 b0 2f 20 00    	mov    0x202fb0(%rip),%eax        # 6047ac <num_input_strings>
  4017fc:	8d 50 01             	lea    0x1(%rax),%edx
  4017ff:	89 15 a7 2f 20 00    	mov    %edx,0x202fa7(%rip)        # 6047ac <num_input_strings>
  401805:	48 98                	cltq   
  401807:	48 6b c0 50          	imul   $0x50,%rax,%rax
  40180b:	48 bf 2a 2a 2a 74 72 	movabs $0x636e7572742a2a2a,%rdi
  401812:	75 6e 63 
  401815:	48 89 b8 c0 47 60 00 	mov    %rdi,0x6047c0(%rax)
  40181c:	48 bf 61 74 65 64 2a 	movabs $0x2a2a2a64657461,%rdi
  401823:	2a 2a 00 
  401826:	48 89 b8 c8 47 60 00 	mov    %rdi,0x6047c8(%rax)
  40182d:	e8 8f fe ff ff       	callq  4016c1 <explode_bomb>
  401832:	83 e9 01             	sub    $0x1,%ecx
  401835:	48 63 c9             	movslq %ecx,%rcx
  401838:	48 63 c6             	movslq %esi,%rax
  40183b:	48 8d 04 80          	lea    (%rax,%rax,4),%rax
  40183f:	48 c1 e0 04          	shl    $0x4,%rax
  401843:	c6 84 01 c0 47 60 00 	movb   $0x0,0x6047c0(%rcx,%rax,1)
  40184a:	00 
  40184b:	8d 46 01             	lea    0x1(%rsi),%eax
  40184e:	89 05 58 2f 20 00    	mov    %eax,0x202f58(%rip)        # 6047ac <num_input_strings>
  401854:	48 89 d0             	mov    %rdx,%rax
  401857:	48 83 c4 08          	add    $0x8,%rsp
  40185b:	c3                   	retq   

000000000040185c <phase_defused>:
  40185c:	48 83 ec 78          	sub    $0x78,%rsp
  401860:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401867:	00 00 
  401869:	48 89 44 24 68       	mov    %rax,0x68(%rsp)
  40186e:	31 c0                	xor    %eax,%eax
  401870:	bf 01 00 00 00       	mov    $0x1,%edi
  401875:	e8 3d fd ff ff       	callq  4015b7 <send_msg>
  40187a:	83 3d 2b 2f 20 00 06 	cmpl   $0x6,0x202f2b(%rip)        # 6047ac <num_input_strings>
  401881:	75 6d                	jne    4018f0 <phase_defused+0x94>
  401883:	4c 8d 44 24 10       	lea    0x10(%rsp),%r8
  401888:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  40188d:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  401892:	be 17 2a 40 00       	mov    $0x402a17,%esi
  401897:	bf b0 48 60 00       	mov    $0x6048b0,%edi
  40189c:	b8 00 00 00 00       	mov    $0x0,%eax
  4018a1:	e8 9a f3 ff ff       	callq  400c40 <__isoc99_sscanf@plt>
  4018a6:	83 f8 03             	cmp    $0x3,%eax
  4018a9:	75 31                	jne    4018dc <phase_defused+0x80>
  4018ab:	be 20 2a 40 00       	mov    $0x402a20,%esi
  4018b0:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi
  4018b5:	e8 33 fb ff ff       	callq  4013ed <strings_not_equal>
  4018ba:	85 c0                	test   %eax,%eax
  4018bc:	75 1e                	jne    4018dc <phase_defused+0x80>
  4018be:	bf 78 28 40 00       	mov    $0x402878,%edi
  4018c3:	e8 a8 f2 ff ff       	callq  400b70 <puts@plt>
  4018c8:	bf a0 28 40 00       	mov    $0x4028a0,%edi
  4018cd:	e8 9e f2 ff ff       	callq  400b70 <puts@plt>
  4018d2:	b8 00 00 00 00       	mov    $0x0,%eax
  4018d7:	e8 28 fa ff ff       	callq  401304 <secret_phase>
  4018dc:	bf d8 28 40 00       	mov    $0x4028d8,%edi
  4018e1:	e8 8a f2 ff ff       	callq  400b70 <puts@plt>
  4018e6:	bf 08 29 40 00       	mov    $0x402908,%edi
  4018eb:	e8 80 f2 ff ff       	callq  400b70 <puts@plt>
  4018f0:	48 8b 44 24 68       	mov    0x68(%rsp),%rax
  4018f5:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4018fc:	00 00 
  4018fe:	74 05                	je     401905 <phase_defused+0xa9>
  401900:	e8 8b f2 ff ff       	callq  400b90 <__stack_chk_fail@plt>
  401905:	48 83 c4 78          	add    $0x78,%rsp
  401909:	c3                   	retq   

000000000040190a <sigalrm_handler>:
  40190a:	48 83 ec 08          	sub    $0x8,%rsp
  40190e:	b9 00 00 00 00       	mov    $0x0,%ecx
  401913:	ba 50 2a 40 00       	mov    $0x402a50,%edx
  401918:	be 01 00 00 00       	mov    $0x1,%esi
  40191d:	48 8b 3d 7c 2e 20 00 	mov    0x202e7c(%rip),%rdi        # 6047a0 <stderr@@GLIBC_2.2.5>
  401924:	b8 00 00 00 00       	mov    $0x0,%eax
  401929:	e8 72 f3 ff ff       	callq  400ca0 <__fprintf_chk@plt>
  40192e:	bf 01 00 00 00       	mov    $0x1,%edi
  401933:	e8 48 f3 ff ff       	callq  400c80 <exit@plt>

0000000000401938 <rio_readlineb>:
  401938:	41 56                	push   %r14
  40193a:	41 55                	push   %r13
  40193c:	41 54                	push   %r12
  40193e:	55                   	push   %rbp
  40193f:	53                   	push   %rbx
  401940:	48 83 ec 10          	sub    $0x10,%rsp
  401944:	48 89 fb             	mov    %rdi,%rbx
  401947:	49 89 f5             	mov    %rsi,%r13
  40194a:	49 89 d6             	mov    %rdx,%r14
  40194d:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401954:	00 00 
  401956:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  40195b:	31 c0                	xor    %eax,%eax
  40195d:	41 bc 01 00 00 00    	mov    $0x1,%r12d
  401963:	48 8d 6f 10          	lea    0x10(%rdi),%rbp
  401967:	48 83 fa 01          	cmp    $0x1,%rdx
  40196b:	77 2c                	ja     401999 <rio_readlineb+0x61>
  40196d:	eb 6d                	jmp    4019dc <rio_readlineb+0xa4>
  40196f:	ba 00 20 00 00       	mov    $0x2000,%edx
  401974:	48 89 ee             	mov    %rbp,%rsi
  401977:	8b 3b                	mov    (%rbx),%edi
  401979:	e8 42 f2 ff ff       	callq  400bc0 <read@plt>
  40197e:	89 43 04             	mov    %eax,0x4(%rbx)
  401981:	85 c0                	test   %eax,%eax
  401983:	79 0c                	jns    401991 <rio_readlineb+0x59>
  401985:	e8 c6 f1 ff ff       	callq  400b50 <__errno_location@plt>
  40198a:	83 38 04             	cmpl   $0x4,(%rax)
  40198d:	74 0a                	je     401999 <rio_readlineb+0x61>
  40198f:	eb 6c                	jmp    4019fd <rio_readlineb+0xc5>
  401991:	85 c0                	test   %eax,%eax
  401993:	74 71                	je     401a06 <rio_readlineb+0xce>
  401995:	48 89 6b 08          	mov    %rbp,0x8(%rbx)
  401999:	8b 43 04             	mov    0x4(%rbx),%eax
  40199c:	85 c0                	test   %eax,%eax
  40199e:	7e cf                	jle    40196f <rio_readlineb+0x37>
  4019a0:	48 8b 53 08          	mov    0x8(%rbx),%rdx
  4019a4:	0f b6 0a             	movzbl (%rdx),%ecx
  4019a7:	88 4c 24 07          	mov    %cl,0x7(%rsp)
  4019ab:	48 83 c2 01          	add    $0x1,%rdx
  4019af:	48 89 53 08          	mov    %rdx,0x8(%rbx)
  4019b3:	83 e8 01             	sub    $0x1,%eax
  4019b6:	89 43 04             	mov    %eax,0x4(%rbx)
  4019b9:	49 83 c5 01          	add    $0x1,%r13
  4019bd:	41 88 4d ff          	mov    %cl,-0x1(%r13)
  4019c1:	80 f9 0a             	cmp    $0xa,%cl
  4019c4:	75 0a                	jne    4019d0 <rio_readlineb+0x98>
  4019c6:	eb 14                	jmp    4019dc <rio_readlineb+0xa4>
  4019c8:	41 83 fc 01          	cmp    $0x1,%r12d
  4019cc:	75 0e                	jne    4019dc <rio_readlineb+0xa4>
  4019ce:	eb 16                	jmp    4019e6 <rio_readlineb+0xae>
  4019d0:	41 83 c4 01          	add    $0x1,%r12d
  4019d4:	49 63 c4             	movslq %r12d,%rax
  4019d7:	4c 39 f0             	cmp    %r14,%rax
  4019da:	72 bd                	jb     401999 <rio_readlineb+0x61>
  4019dc:	41 c6 45 00 00       	movb   $0x0,0x0(%r13)
  4019e1:	49 63 c4             	movslq %r12d,%rax
  4019e4:	eb 05                	jmp    4019eb <rio_readlineb+0xb3>
  4019e6:	b8 00 00 00 00       	mov    $0x0,%eax
  4019eb:	48 8b 4c 24 08       	mov    0x8(%rsp),%rcx
  4019f0:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  4019f7:	00 00 
  4019f9:	74 22                	je     401a1d <rio_readlineb+0xe5>
  4019fb:	eb 1b                	jmp    401a18 <rio_readlineb+0xe0>
  4019fd:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  401a04:	eb 05                	jmp    401a0b <rio_readlineb+0xd3>
  401a06:	b8 00 00 00 00       	mov    $0x0,%eax
  401a0b:	85 c0                	test   %eax,%eax
  401a0d:	74 b9                	je     4019c8 <rio_readlineb+0x90>
  401a0f:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  401a16:	eb d3                	jmp    4019eb <rio_readlineb+0xb3>
  401a18:	e8 73 f1 ff ff       	callq  400b90 <__stack_chk_fail@plt>
  401a1d:	48 83 c4 10          	add    $0x10,%rsp
  401a21:	5b                   	pop    %rbx
  401a22:	5d                   	pop    %rbp
  401a23:	41 5c                	pop    %r12
  401a25:	41 5d                	pop    %r13
  401a27:	41 5e                	pop    %r14
  401a29:	c3                   	retq   

0000000000401a2a <submitr>:
  401a2a:	41 57                	push   %r15
  401a2c:	41 56                	push   %r14
  401a2e:	41 55                	push   %r13
  401a30:	41 54                	push   %r12
  401a32:	55                   	push   %rbp
  401a33:	53                   	push   %rbx
  401a34:	48 81 ec 68 a0 00 00 	sub    $0xa068,%rsp
  401a3b:	49 89 fd             	mov    %rdi,%r13
  401a3e:	89 f5                	mov    %esi,%ebp
  401a40:	48 89 14 24          	mov    %rdx,(%rsp)
  401a44:	48 89 4c 24 08       	mov    %rcx,0x8(%rsp)
  401a49:	4c 89 44 24 18       	mov    %r8,0x18(%rsp)
  401a4e:	4c 89 4c 24 10       	mov    %r9,0x10(%rsp)
  401a53:	48 8b 9c 24 a0 a0 00 	mov    0xa0a0(%rsp),%rbx
  401a5a:	00 
  401a5b:	4c 8b bc 24 a8 a0 00 	mov    0xa0a8(%rsp),%r15
  401a62:	00 
  401a63:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401a6a:	00 00 
  401a6c:	48 89 84 24 58 a0 00 	mov    %rax,0xa058(%rsp)
  401a73:	00 
  401a74:	31 c0                	xor    %eax,%eax
  401a76:	c7 44 24 2c 00 00 00 	movl   $0x0,0x2c(%rsp)
  401a7d:	00 
  401a7e:	ba 00 00 00 00       	mov    $0x0,%edx
  401a83:	be 01 00 00 00       	mov    $0x1,%esi
  401a88:	bf 02 00 00 00       	mov    $0x2,%edi
  401a8d:	e8 4e f2 ff ff       	callq  400ce0 <socket@plt>
  401a92:	85 c0                	test   %eax,%eax
  401a94:	79 50                	jns    401ae6 <submitr+0xbc>
  401a96:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  401a9d:	3a 20 43 
  401aa0:	49 89 07             	mov    %rax,(%r15)
  401aa3:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  401aaa:	20 75 6e 
  401aad:	49 89 47 08          	mov    %rax,0x8(%r15)
  401ab1:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401ab8:	74 6f 20 
  401abb:	49 89 47 10          	mov    %rax,0x10(%r15)
  401abf:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  401ac6:	65 20 73 
  401ac9:	49 89 47 18          	mov    %rax,0x18(%r15)
  401acd:	41 c7 47 20 6f 63 6b 	movl   $0x656b636f,0x20(%r15)
  401ad4:	65 
  401ad5:	66 41 c7 47 24 74 00 	movw   $0x74,0x24(%r15)
  401adc:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401ae1:	e9 12 06 00 00       	jmpq   4020f8 <submitr+0x6ce>
  401ae6:	41 89 c4             	mov    %eax,%r12d
  401ae9:	4c 89 ef             	mov    %r13,%rdi
  401aec:	e8 0f f1 ff ff       	callq  400c00 <gethostbyname@plt>
  401af1:	48 85 c0             	test   %rax,%rax
  401af4:	75 6b                	jne    401b61 <submitr+0x137>
  401af6:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  401afd:	3a 20 44 
  401b00:	49 89 07             	mov    %rax,(%r15)
  401b03:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  401b0a:	20 75 6e 
  401b0d:	49 89 47 08          	mov    %rax,0x8(%r15)
  401b11:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401b18:	74 6f 20 
  401b1b:	49 89 47 10          	mov    %rax,0x10(%r15)
  401b1f:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  401b26:	76 65 20 
  401b29:	49 89 47 18          	mov    %rax,0x18(%r15)
  401b2d:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  401b34:	72 20 61 
  401b37:	49 89 47 20          	mov    %rax,0x20(%r15)
  401b3b:	41 c7 47 28 64 64 72 	movl   $0x65726464,0x28(%r15)
  401b42:	65 
  401b43:	66 41 c7 47 2c 73 73 	movw   $0x7373,0x2c(%r15)
  401b4a:	41 c6 47 2e 00       	movb   $0x0,0x2e(%r15)
  401b4f:	44 89 e7             	mov    %r12d,%edi
  401b52:	e8 59 f0 ff ff       	callq  400bb0 <close@plt>
  401b57:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401b5c:	e9 97 05 00 00       	jmpq   4020f8 <submitr+0x6ce>
  401b61:	48 c7 44 24 30 00 00 	movq   $0x0,0x30(%rsp)
  401b68:	00 00 
  401b6a:	48 c7 44 24 38 00 00 	movq   $0x0,0x38(%rsp)
  401b71:	00 00 
  401b73:	66 c7 44 24 30 02 00 	movw   $0x2,0x30(%rsp)
  401b7a:	48 63 50 14          	movslq 0x14(%rax),%rdx
  401b7e:	48 8b 40 18          	mov    0x18(%rax),%rax
  401b82:	48 8d 7c 24 34       	lea    0x34(%rsp),%rdi
  401b87:	b9 0c 00 00 00       	mov    $0xc,%ecx
  401b8c:	48 8b 30             	mov    (%rax),%rsi
  401b8f:	e8 7c f0 ff ff       	callq  400c10 <__memmove_chk@plt>
  401b94:	66 c1 cd 08          	ror    $0x8,%bp
  401b98:	66 89 6c 24 32       	mov    %bp,0x32(%rsp)
  401b9d:	ba 10 00 00 00       	mov    $0x10,%edx
  401ba2:	48 8d 74 24 30       	lea    0x30(%rsp),%rsi
  401ba7:	44 89 e7             	mov    %r12d,%edi
  401baa:	e8 e1 f0 ff ff       	callq  400c90 <connect@plt>
  401baf:	85 c0                	test   %eax,%eax
  401bb1:	79 5d                	jns    401c10 <submitr+0x1e6>
  401bb3:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  401bba:	3a 20 55 
  401bbd:	49 89 07             	mov    %rax,(%r15)
  401bc0:	48 b8 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rax
  401bc7:	20 74 6f 
  401bca:	49 89 47 08          	mov    %rax,0x8(%r15)
  401bce:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  401bd5:	65 63 74 
  401bd8:	49 89 47 10          	mov    %rax,0x10(%r15)
  401bdc:	48 b8 20 74 6f 20 74 	movabs $0x20656874206f7420,%rax
  401be3:	68 65 20 
  401be6:	49 89 47 18          	mov    %rax,0x18(%r15)
  401bea:	41 c7 47 20 73 65 72 	movl   $0x76726573,0x20(%r15)
  401bf1:	76 
  401bf2:	66 41 c7 47 24 65 72 	movw   $0x7265,0x24(%r15)
  401bf9:	41 c6 47 26 00       	movb   $0x0,0x26(%r15)
  401bfe:	44 89 e7             	mov    %r12d,%edi
  401c01:	e8 aa ef ff ff       	callq  400bb0 <close@plt>
  401c06:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401c0b:	e9 e8 04 00 00       	jmpq   4020f8 <submitr+0x6ce>
  401c10:	49 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%r9
  401c17:	b8 00 00 00 00       	mov    $0x0,%eax
  401c1c:	4c 89 c9             	mov    %r9,%rcx
  401c1f:	48 89 df             	mov    %rbx,%rdi
  401c22:	f2 ae                	repnz scas %es:(%rdi),%al
  401c24:	48 f7 d1             	not    %rcx
  401c27:	48 89 ce             	mov    %rcx,%rsi
  401c2a:	4c 89 c9             	mov    %r9,%rcx
  401c2d:	48 8b 3c 24          	mov    (%rsp),%rdi
  401c31:	f2 ae                	repnz scas %es:(%rdi),%al
  401c33:	49 89 c8             	mov    %rcx,%r8
  401c36:	4c 89 c9             	mov    %r9,%rcx
  401c39:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  401c3e:	f2 ae                	repnz scas %es:(%rdi),%al
  401c40:	48 f7 d1             	not    %rcx
  401c43:	48 89 ca             	mov    %rcx,%rdx
  401c46:	4c 89 c9             	mov    %r9,%rcx
  401c49:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
  401c4e:	f2 ae                	repnz scas %es:(%rdi),%al
  401c50:	4c 29 c2             	sub    %r8,%rdx
  401c53:	48 29 ca             	sub    %rcx,%rdx
  401c56:	48 8d 44 76 fd       	lea    -0x3(%rsi,%rsi,2),%rax
  401c5b:	48 8d 44 02 7b       	lea    0x7b(%rdx,%rax,1),%rax
  401c60:	48 3d 00 20 00 00    	cmp    $0x2000,%rax
  401c66:	76 73                	jbe    401cdb <submitr+0x2b1>
  401c68:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  401c6f:	3a 20 52 
  401c72:	49 89 07             	mov    %rax,(%r15)
  401c75:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  401c7c:	20 73 74 
  401c7f:	49 89 47 08          	mov    %rax,0x8(%r15)
  401c83:	48 b8 72 69 6e 67 20 	movabs $0x6f6f7420676e6972,%rax
  401c8a:	74 6f 6f 
  401c8d:	49 89 47 10          	mov    %rax,0x10(%r15)
  401c91:	48 b8 20 6c 61 72 67 	movabs $0x202e656772616c20,%rax
  401c98:	65 2e 20 
  401c9b:	49 89 47 18          	mov    %rax,0x18(%r15)
  401c9f:	48 b8 49 6e 63 72 65 	movabs $0x6573616572636e49,%rax
  401ca6:	61 73 65 
  401ca9:	49 89 47 20          	mov    %rax,0x20(%r15)
  401cad:	48 b8 20 53 55 42 4d 	movabs $0x5254494d42555320,%rax
  401cb4:	49 54 52 
  401cb7:	49 89 47 28          	mov    %rax,0x28(%r15)
  401cbb:	48 b8 5f 4d 41 58 42 	movabs $0x46554258414d5f,%rax
  401cc2:	55 46 00 
  401cc5:	49 89 47 30          	mov    %rax,0x30(%r15)
  401cc9:	44 89 e7             	mov    %r12d,%edi
  401ccc:	e8 df ee ff ff       	callq  400bb0 <close@plt>
  401cd1:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401cd6:	e9 1d 04 00 00       	jmpq   4020f8 <submitr+0x6ce>
  401cdb:	48 8d 94 24 50 40 00 	lea    0x4050(%rsp),%rdx
  401ce2:	00 
  401ce3:	b9 00 04 00 00       	mov    $0x400,%ecx
  401ce8:	b8 00 00 00 00       	mov    $0x0,%eax
  401ced:	48 89 d7             	mov    %rdx,%rdi
  401cf0:	f3 48 ab             	rep stos %rax,%es:(%rdi)
  401cf3:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  401cfa:	48 89 df             	mov    %rbx,%rdi
  401cfd:	f2 ae                	repnz scas %es:(%rdi),%al
  401cff:	48 89 c8             	mov    %rcx,%rax
  401d02:	48 f7 d0             	not    %rax
  401d05:	48 83 e8 01          	sub    $0x1,%rax
  401d09:	85 c0                	test   %eax,%eax
  401d0b:	0f 84 90 04 00 00    	je     4021a1 <submitr+0x777>
  401d11:	8d 40 ff             	lea    -0x1(%rax),%eax
  401d14:	4c 8d 74 03 01       	lea    0x1(%rbx,%rax,1),%r14
  401d19:	48 89 d5             	mov    %rdx,%rbp
  401d1c:	49 bd d9 ff 00 00 00 	movabs $0x2000000000ffd9,%r13
  401d23:	00 20 00 
  401d26:	44 0f b6 03          	movzbl (%rbx),%r8d
  401d2a:	41 8d 40 d6          	lea    -0x2a(%r8),%eax
  401d2e:	3c 35                	cmp    $0x35,%al
  401d30:	77 06                	ja     401d38 <submitr+0x30e>
  401d32:	49 0f a3 c5          	bt     %rax,%r13
  401d36:	72 0d                	jb     401d45 <submitr+0x31b>
  401d38:	44 89 c0             	mov    %r8d,%eax
  401d3b:	83 e0 df             	and    $0xffffffdf,%eax
  401d3e:	83 e8 41             	sub    $0x41,%eax
  401d41:	3c 19                	cmp    $0x19,%al
  401d43:	77 0a                	ja     401d4f <submitr+0x325>
  401d45:	44 88 45 00          	mov    %r8b,0x0(%rbp)
  401d49:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  401d4d:	eb 6c                	jmp    401dbb <submitr+0x391>
  401d4f:	41 80 f8 20          	cmp    $0x20,%r8b
  401d53:	75 0a                	jne    401d5f <submitr+0x335>
  401d55:	c6 45 00 2b          	movb   $0x2b,0x0(%rbp)
  401d59:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  401d5d:	eb 5c                	jmp    401dbb <submitr+0x391>
  401d5f:	41 8d 40 e0          	lea    -0x20(%r8),%eax
  401d63:	3c 5f                	cmp    $0x5f,%al
  401d65:	76 0a                	jbe    401d71 <submitr+0x347>
  401d67:	41 80 f8 09          	cmp    $0x9,%r8b
  401d6b:	0f 85 a3 03 00 00    	jne    402114 <submitr+0x6ea>
  401d71:	45 0f b6 c0          	movzbl %r8b,%r8d
  401d75:	b9 00 2b 40 00       	mov    $0x402b00,%ecx
  401d7a:	ba 08 00 00 00       	mov    $0x8,%edx
  401d7f:	be 01 00 00 00       	mov    $0x1,%esi
  401d84:	48 8d bc 24 50 80 00 	lea    0x8050(%rsp),%rdi
  401d8b:	00 
  401d8c:	b8 00 00 00 00       	mov    $0x0,%eax
  401d91:	e8 3a ef ff ff       	callq  400cd0 <__sprintf_chk@plt>
  401d96:	0f b6 84 24 50 80 00 	movzbl 0x8050(%rsp),%eax
  401d9d:	00 
  401d9e:	88 45 00             	mov    %al,0x0(%rbp)
  401da1:	0f b6 84 24 51 80 00 	movzbl 0x8051(%rsp),%eax
  401da8:	00 
  401da9:	88 45 01             	mov    %al,0x1(%rbp)
  401dac:	0f b6 84 24 52 80 00 	movzbl 0x8052(%rsp),%eax
  401db3:	00 
  401db4:	88 45 02             	mov    %al,0x2(%rbp)
  401db7:	48 8d 6d 03          	lea    0x3(%rbp),%rbp
  401dbb:	48 83 c3 01          	add    $0x1,%rbx
  401dbf:	49 39 de             	cmp    %rbx,%r14
  401dc2:	0f 85 5e ff ff ff    	jne    401d26 <submitr+0x2fc>
  401dc8:	e9 d4 03 00 00       	jmpq   4021a1 <submitr+0x777>
  401dcd:	48 89 da             	mov    %rbx,%rdx
  401dd0:	48 89 ee             	mov    %rbp,%rsi
  401dd3:	44 89 e7             	mov    %r12d,%edi
  401dd6:	e8 a5 ed ff ff       	callq  400b80 <write@plt>
  401ddb:	48 85 c0             	test   %rax,%rax
  401dde:	7f 0f                	jg     401def <submitr+0x3c5>
  401de0:	e8 6b ed ff ff       	callq  400b50 <__errno_location@plt>
  401de5:	83 38 04             	cmpl   $0x4,(%rax)
  401de8:	75 12                	jne    401dfc <submitr+0x3d2>
  401dea:	b8 00 00 00 00       	mov    $0x0,%eax
  401def:	48 01 c5             	add    %rax,%rbp
  401df2:	48 29 c3             	sub    %rax,%rbx
  401df5:	75 d6                	jne    401dcd <submitr+0x3a3>
  401df7:	4d 85 ed             	test   %r13,%r13
  401dfa:	79 5f                	jns    401e5b <submitr+0x431>
  401dfc:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  401e03:	3a 20 43 
  401e06:	49 89 07             	mov    %rax,(%r15)
  401e09:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  401e10:	20 75 6e 
  401e13:	49 89 47 08          	mov    %rax,0x8(%r15)
  401e17:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401e1e:	74 6f 20 
  401e21:	49 89 47 10          	mov    %rax,0x10(%r15)
  401e25:	48 b8 77 72 69 74 65 	movabs $0x6f74206574697277,%rax
  401e2c:	20 74 6f 
  401e2f:	49 89 47 18          	mov    %rax,0x18(%r15)
  401e33:	48 b8 20 74 68 65 20 	movabs $0x7265732065687420,%rax
  401e3a:	73 65 72 
  401e3d:	49 89 47 20          	mov    %rax,0x20(%r15)
  401e41:	41 c7 47 28 76 65 72 	movl   $0x726576,0x28(%r15)
  401e48:	00 
  401e49:	44 89 e7             	mov    %r12d,%edi
  401e4c:	e8 5f ed ff ff       	callq  400bb0 <close@plt>
  401e51:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401e56:	e9 9d 02 00 00       	jmpq   4020f8 <submitr+0x6ce>
  401e5b:	44 89 64 24 40       	mov    %r12d,0x40(%rsp)
  401e60:	c7 44 24 44 00 00 00 	movl   $0x0,0x44(%rsp)
  401e67:	00 
  401e68:	48 8d 44 24 50       	lea    0x50(%rsp),%rax
  401e6d:	48 89 44 24 48       	mov    %rax,0x48(%rsp)
  401e72:	ba 00 20 00 00       	mov    $0x2000,%edx
  401e77:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
  401e7e:	00 
  401e7f:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
  401e84:	e8 af fa ff ff       	callq  401938 <rio_readlineb>
  401e89:	48 85 c0             	test   %rax,%rax
  401e8c:	7f 74                	jg     401f02 <submitr+0x4d8>
  401e8e:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  401e95:	3a 20 43 
  401e98:	49 89 07             	mov    %rax,(%r15)
  401e9b:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  401ea2:	20 75 6e 
  401ea5:	49 89 47 08          	mov    %rax,0x8(%r15)
  401ea9:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401eb0:	74 6f 20 
  401eb3:	49 89 47 10          	mov    %rax,0x10(%r15)
  401eb7:	48 b8 72 65 61 64 20 	movabs $0x7269662064616572,%rax
  401ebe:	66 69 72 
  401ec1:	49 89 47 18          	mov    %rax,0x18(%r15)
  401ec5:	48 b8 73 74 20 68 65 	movabs $0x6564616568207473,%rax
  401ecc:	61 64 65 
  401ecf:	49 89 47 20          	mov    %rax,0x20(%r15)
  401ed3:	48 b8 72 20 66 72 6f 	movabs $0x73206d6f72662072,%rax
  401eda:	6d 20 73 
  401edd:	49 89 47 28          	mov    %rax,0x28(%r15)
  401ee1:	41 c7 47 30 65 72 76 	movl   $0x65767265,0x30(%r15)
  401ee8:	65 
  401ee9:	66 41 c7 47 34 72 00 	movw   $0x72,0x34(%r15)
  401ef0:	44 89 e7             	mov    %r12d,%edi
  401ef3:	e8 b8 ec ff ff       	callq  400bb0 <close@plt>
  401ef8:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401efd:	e9 f6 01 00 00       	jmpq   4020f8 <submitr+0x6ce>
  401f02:	4c 8d 84 24 50 80 00 	lea    0x8050(%rsp),%r8
  401f09:	00 
  401f0a:	48 8d 4c 24 2c       	lea    0x2c(%rsp),%rcx
  401f0f:	48 8d 94 24 50 60 00 	lea    0x6050(%rsp),%rdx
  401f16:	00 
  401f17:	be 07 2b 40 00       	mov    $0x402b07,%esi
  401f1c:	48 8d bc 24 50 20 00 	lea    0x2050(%rsp),%rdi
  401f23:	00 
  401f24:	b8 00 00 00 00       	mov    $0x0,%eax
  401f29:	e8 12 ed ff ff       	callq  400c40 <__isoc99_sscanf@plt>
  401f2e:	44 8b 44 24 2c       	mov    0x2c(%rsp),%r8d
  401f33:	41 81 f8 c8 00 00 00 	cmp    $0xc8,%r8d
  401f3a:	0f 84 be 00 00 00    	je     401ffe <submitr+0x5d4>
  401f40:	4c 8d 8c 24 50 80 00 	lea    0x8050(%rsp),%r9
  401f47:	00 
  401f48:	b9 78 2a 40 00       	mov    $0x402a78,%ecx
  401f4d:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  401f54:	be 01 00 00 00       	mov    $0x1,%esi
  401f59:	4c 89 ff             	mov    %r15,%rdi
  401f5c:	b8 00 00 00 00       	mov    $0x0,%eax
  401f61:	e8 6a ed ff ff       	callq  400cd0 <__sprintf_chk@plt>
  401f66:	44 89 e7             	mov    %r12d,%edi
  401f69:	e8 42 ec ff ff       	callq  400bb0 <close@plt>
  401f6e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401f73:	e9 80 01 00 00       	jmpq   4020f8 <submitr+0x6ce>
  401f78:	ba 00 20 00 00       	mov    $0x2000,%edx
  401f7d:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
  401f84:	00 
  401f85:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
  401f8a:	e8 a9 f9 ff ff       	callq  401938 <rio_readlineb>
  401f8f:	48 85 c0             	test   %rax,%rax
  401f92:	7f 6a                	jg     401ffe <submitr+0x5d4>
  401f94:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  401f9b:	3a 20 43 
  401f9e:	49 89 07             	mov    %rax,(%r15)
  401fa1:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  401fa8:	20 75 6e 
  401fab:	49 89 47 08          	mov    %rax,0x8(%r15)
  401faf:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  401fb6:	74 6f 20 
  401fb9:	49 89 47 10          	mov    %rax,0x10(%r15)
  401fbd:	48 b8 72 65 61 64 20 	movabs $0x6165682064616572,%rax
  401fc4:	68 65 61 
  401fc7:	49 89 47 18          	mov    %rax,0x18(%r15)
  401fcb:	48 b8 64 65 72 73 20 	movabs $0x6f72662073726564,%rax
  401fd2:	66 72 6f 
  401fd5:	49 89 47 20          	mov    %rax,0x20(%r15)
  401fd9:	48 b8 6d 20 73 65 72 	movabs $0x726576726573206d,%rax
  401fe0:	76 65 72 
  401fe3:	49 89 47 28          	mov    %rax,0x28(%r15)
  401fe7:	41 c6 47 30 00       	movb   $0x0,0x30(%r15)
  401fec:	44 89 e7             	mov    %r12d,%edi
  401fef:	e8 bc eb ff ff       	callq  400bb0 <close@plt>
  401ff4:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  401ff9:	e9 fa 00 00 00       	jmpq   4020f8 <submitr+0x6ce>
  401ffe:	80 bc 24 50 20 00 00 	cmpb   $0xd,0x2050(%rsp)
  402005:	0d 
  402006:	0f 85 6c ff ff ff    	jne    401f78 <submitr+0x54e>
  40200c:	80 bc 24 51 20 00 00 	cmpb   $0xa,0x2051(%rsp)
  402013:	0a 
  402014:	0f 85 5e ff ff ff    	jne    401f78 <submitr+0x54e>
  40201a:	80 bc 24 52 20 00 00 	cmpb   $0x0,0x2052(%rsp)
  402021:	00 
  402022:	0f 85 50 ff ff ff    	jne    401f78 <submitr+0x54e>
  402028:	ba 00 20 00 00       	mov    $0x2000,%edx
  40202d:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
  402034:	00 
  402035:	48 8d 7c 24 40       	lea    0x40(%rsp),%rdi
  40203a:	e8 f9 f8 ff ff       	callq  401938 <rio_readlineb>
  40203f:	48 85 c0             	test   %rax,%rax
  402042:	7f 70                	jg     4020b4 <submitr+0x68a>
  402044:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  40204b:	3a 20 43 
  40204e:	49 89 07             	mov    %rax,(%r15)
  402051:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402058:	20 75 6e 
  40205b:	49 89 47 08          	mov    %rax,0x8(%r15)
  40205f:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402066:	74 6f 20 
  402069:	49 89 47 10          	mov    %rax,0x10(%r15)
  40206d:	48 b8 72 65 61 64 20 	movabs $0x6174732064616572,%rax
  402074:	73 74 61 
  402077:	49 89 47 18          	mov    %rax,0x18(%r15)
  40207b:	48 b8 74 75 73 20 6d 	movabs $0x7373656d20737574,%rax
  402082:	65 73 73 
  402085:	49 89 47 20          	mov    %rax,0x20(%r15)
  402089:	48 b8 61 67 65 20 66 	movabs $0x6d6f726620656761,%rax
  402090:	72 6f 6d 
  402093:	49 89 47 28          	mov    %rax,0x28(%r15)
  402097:	48 b8 20 73 65 72 76 	movabs $0x72657672657320,%rax
  40209e:	65 72 00 
  4020a1:	49 89 47 30          	mov    %rax,0x30(%r15)
  4020a5:	44 89 e7             	mov    %r12d,%edi
  4020a8:	e8 03 eb ff ff       	callq  400bb0 <close@plt>
  4020ad:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4020b2:	eb 44                	jmp    4020f8 <submitr+0x6ce>
  4020b4:	48 8d b4 24 50 20 00 	lea    0x2050(%rsp),%rsi
  4020bb:	00 
  4020bc:	4c 89 ff             	mov    %r15,%rdi
  4020bf:	e8 9c ea ff ff       	callq  400b60 <strcpy@plt>
  4020c4:	44 89 e7             	mov    %r12d,%edi
  4020c7:	e8 e4 ea ff ff       	callq  400bb0 <close@plt>
  4020cc:	41 0f b6 17          	movzbl (%r15),%edx
  4020d0:	b8 4f 00 00 00       	mov    $0x4f,%eax
  4020d5:	29 d0                	sub    %edx,%eax
  4020d7:	75 15                	jne    4020ee <submitr+0x6c4>
  4020d9:	41 0f b6 57 01       	movzbl 0x1(%r15),%edx
  4020de:	b8 4b 00 00 00       	mov    $0x4b,%eax
  4020e3:	29 d0                	sub    %edx,%eax
  4020e5:	75 07                	jne    4020ee <submitr+0x6c4>
  4020e7:	41 0f b6 47 02       	movzbl 0x2(%r15),%eax
  4020ec:	f7 d8                	neg    %eax
  4020ee:	85 c0                	test   %eax,%eax
  4020f0:	0f 95 c0             	setne  %al
  4020f3:	0f b6 c0             	movzbl %al,%eax
  4020f6:	f7 d8                	neg    %eax
  4020f8:	48 8b 8c 24 58 a0 00 	mov    0xa058(%rsp),%rcx
  4020ff:	00 
  402100:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  402107:	00 00 
  402109:	0f 84 12 01 00 00    	je     402221 <submitr+0x7f7>
  40210f:	e9 08 01 00 00       	jmpq   40221c <submitr+0x7f2>
  402114:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  40211b:	3a 20 52 
  40211e:	49 89 07             	mov    %rax,(%r15)
  402121:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  402128:	20 73 74 
  40212b:	49 89 47 08          	mov    %rax,0x8(%r15)
  40212f:	48 b8 72 69 6e 67 20 	movabs $0x6e6f6320676e6972,%rax
  402136:	63 6f 6e 
  402139:	49 89 47 10          	mov    %rax,0x10(%r15)
  40213d:	48 b8 74 61 69 6e 73 	movabs $0x6e6120736e696174,%rax
  402144:	20 61 6e 
  402147:	49 89 47 18          	mov    %rax,0x18(%r15)
  40214b:	48 b8 20 69 6c 6c 65 	movabs $0x6c6167656c6c6920,%rax
  402152:	67 61 6c 
  402155:	49 89 47 20          	mov    %rax,0x20(%r15)
  402159:	48 b8 20 6f 72 20 75 	movabs $0x72706e7520726f20,%rax
  402160:	6e 70 72 
  402163:	49 89 47 28          	mov    %rax,0x28(%r15)
  402167:	48 b8 69 6e 74 61 62 	movabs $0x20656c6261746e69,%rax
  40216e:	6c 65 20 
  402171:	49 89 47 30          	mov    %rax,0x30(%r15)
  402175:	48 b8 63 68 61 72 61 	movabs $0x6574636172616863,%rax
  40217c:	63 74 65 
  40217f:	49 89 47 38          	mov    %rax,0x38(%r15)
  402183:	66 41 c7 47 40 72 2e 	movw   $0x2e72,0x40(%r15)
  40218a:	41 c6 47 42 00       	movb   $0x0,0x42(%r15)
  40218f:	44 89 e7             	mov    %r12d,%edi
  402192:	e8 19 ea ff ff       	callq  400bb0 <close@plt>
  402197:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40219c:	e9 57 ff ff ff       	jmpq   4020f8 <submitr+0x6ce>
  4021a1:	48 8d 9c 24 50 20 00 	lea    0x2050(%rsp),%rbx
  4021a8:	00 
  4021a9:	48 83 ec 08          	sub    $0x8,%rsp
  4021ad:	48 8d 84 24 58 40 00 	lea    0x4058(%rsp),%rax
  4021b4:	00 
  4021b5:	50                   	push   %rax
  4021b6:	ff 74 24 20          	pushq  0x20(%rsp)
  4021ba:	ff 74 24 30          	pushq  0x30(%rsp)
  4021be:	4c 8b 4c 24 28       	mov    0x28(%rsp),%r9
  4021c3:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
  4021c8:	b9 a8 2a 40 00       	mov    $0x402aa8,%ecx
  4021cd:	ba 00 20 00 00       	mov    $0x2000,%edx
  4021d2:	be 01 00 00 00       	mov    $0x1,%esi
  4021d7:	48 89 df             	mov    %rbx,%rdi
  4021da:	b8 00 00 00 00       	mov    $0x0,%eax
  4021df:	e8 ec ea ff ff       	callq  400cd0 <__sprintf_chk@plt>
  4021e4:	b8 00 00 00 00       	mov    $0x0,%eax
  4021e9:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4021f0:	48 89 df             	mov    %rbx,%rdi
  4021f3:	f2 ae                	repnz scas %es:(%rdi),%al
  4021f5:	48 89 c8             	mov    %rcx,%rax
  4021f8:	48 f7 d0             	not    %rax
  4021fb:	4c 8d 68 ff          	lea    -0x1(%rax),%r13
  4021ff:	48 83 c4 20          	add    $0x20,%rsp
  402203:	4c 89 eb             	mov    %r13,%rbx
  402206:	48 8d ac 24 50 20 00 	lea    0x2050(%rsp),%rbp
  40220d:	00 
  40220e:	4d 85 ed             	test   %r13,%r13
  402211:	0f 85 b6 fb ff ff    	jne    401dcd <submitr+0x3a3>
  402217:	e9 3f fc ff ff       	jmpq   401e5b <submitr+0x431>
  40221c:	e8 6f e9 ff ff       	callq  400b90 <__stack_chk_fail@plt>
  402221:	48 81 c4 68 a0 00 00 	add    $0xa068,%rsp
  402228:	5b                   	pop    %rbx
  402229:	5d                   	pop    %rbp
  40222a:	41 5c                	pop    %r12
  40222c:	41 5d                	pop    %r13
  40222e:	41 5e                	pop    %r14
  402230:	41 5f                	pop    %r15
  402232:	c3                   	retq   

0000000000402233 <init_timeout>:
  402233:	85 ff                	test   %edi,%edi
  402235:	74 22                	je     402259 <init_timeout+0x26>
  402237:	53                   	push   %rbx
  402238:	89 fb                	mov    %edi,%ebx
  40223a:	be 0a 19 40 00       	mov    $0x40190a,%esi
  40223f:	bf 0e 00 00 00       	mov    $0xe,%edi
  402244:	e8 a7 e9 ff ff       	callq  400bf0 <signal@plt>
  402249:	85 db                	test   %ebx,%ebx
  40224b:	bf 00 00 00 00       	mov    $0x0,%edi
  402250:	0f 49 fb             	cmovns %ebx,%edi
  402253:	e8 48 e9 ff ff       	callq  400ba0 <alarm@plt>
  402258:	5b                   	pop    %rbx
  402259:	f3 c3                	repz retq 

000000000040225b <init_driver>:
  40225b:	55                   	push   %rbp
  40225c:	53                   	push   %rbx
  40225d:	48 83 ec 28          	sub    $0x28,%rsp
  402261:	48 89 fd             	mov    %rdi,%rbp
  402264:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40226b:	00 00 
  40226d:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  402272:	31 c0                	xor    %eax,%eax
  402274:	be 01 00 00 00       	mov    $0x1,%esi
  402279:	bf 0d 00 00 00       	mov    $0xd,%edi
  40227e:	e8 6d e9 ff ff       	callq  400bf0 <signal@plt>
  402283:	be 01 00 00 00       	mov    $0x1,%esi
  402288:	bf 1d 00 00 00       	mov    $0x1d,%edi
  40228d:	e8 5e e9 ff ff       	callq  400bf0 <signal@plt>
  402292:	be 01 00 00 00       	mov    $0x1,%esi
  402297:	bf 1d 00 00 00       	mov    $0x1d,%edi
  40229c:	e8 4f e9 ff ff       	callq  400bf0 <signal@plt>
  4022a1:	ba 00 00 00 00       	mov    $0x0,%edx
  4022a6:	be 01 00 00 00       	mov    $0x1,%esi
  4022ab:	bf 02 00 00 00       	mov    $0x2,%edi
  4022b0:	e8 2b ea ff ff       	callq  400ce0 <socket@plt>
  4022b5:	85 c0                	test   %eax,%eax
  4022b7:	79 4f                	jns    402308 <init_driver+0xad>
  4022b9:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4022c0:	3a 20 43 
  4022c3:	48 89 45 00          	mov    %rax,0x0(%rbp)
  4022c7:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4022ce:	20 75 6e 
  4022d1:	48 89 45 08          	mov    %rax,0x8(%rbp)
  4022d5:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4022dc:	74 6f 20 
  4022df:	48 89 45 10          	mov    %rax,0x10(%rbp)
  4022e3:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  4022ea:	65 20 73 
  4022ed:	48 89 45 18          	mov    %rax,0x18(%rbp)
  4022f1:	c7 45 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbp)
  4022f8:	66 c7 45 24 74 00    	movw   $0x74,0x24(%rbp)
  4022fe:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402303:	e9 2a 01 00 00       	jmpq   402432 <init_driver+0x1d7>
  402308:	89 c3                	mov    %eax,%ebx
  40230a:	bf 18 2b 40 00       	mov    $0x402b18,%edi
  40230f:	e8 ec e8 ff ff       	callq  400c00 <gethostbyname@plt>
  402314:	48 85 c0             	test   %rax,%rax
  402317:	75 68                	jne    402381 <init_driver+0x126>
  402319:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  402320:	3a 20 44 
  402323:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402327:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  40232e:	20 75 6e 
  402331:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402335:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  40233c:	74 6f 20 
  40233f:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402343:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  40234a:	76 65 20 
  40234d:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402351:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  402358:	72 20 61 
  40235b:	48 89 45 20          	mov    %rax,0x20(%rbp)
  40235f:	c7 45 28 64 64 72 65 	movl   $0x65726464,0x28(%rbp)
  402366:	66 c7 45 2c 73 73    	movw   $0x7373,0x2c(%rbp)
  40236c:	c6 45 2e 00          	movb   $0x0,0x2e(%rbp)
  402370:	89 df                	mov    %ebx,%edi
  402372:	e8 39 e8 ff ff       	callq  400bb0 <close@plt>
  402377:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40237c:	e9 b1 00 00 00       	jmpq   402432 <init_driver+0x1d7>
  402381:	48 c7 04 24 00 00 00 	movq   $0x0,(%rsp)
  402388:	00 
  402389:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
  402390:	00 00 
  402392:	66 c7 04 24 02 00    	movw   $0x2,(%rsp)
  402398:	48 63 50 14          	movslq 0x14(%rax),%rdx
  40239c:	48 8b 40 18          	mov    0x18(%rax),%rax
  4023a0:	48 8d 7c 24 04       	lea    0x4(%rsp),%rdi
  4023a5:	b9 0c 00 00 00       	mov    $0xc,%ecx
  4023aa:	48 8b 30             	mov    (%rax),%rsi
  4023ad:	e8 5e e8 ff ff       	callq  400c10 <__memmove_chk@plt>
  4023b2:	66 c7 44 24 02 4b 29 	movw   $0x294b,0x2(%rsp)
  4023b9:	ba 10 00 00 00       	mov    $0x10,%edx
  4023be:	48 89 e6             	mov    %rsp,%rsi
  4023c1:	89 df                	mov    %ebx,%edi
  4023c3:	e8 c8 e8 ff ff       	callq  400c90 <connect@plt>
  4023c8:	85 c0                	test   %eax,%eax
  4023ca:	79 50                	jns    40241c <init_driver+0x1c1>
  4023cc:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  4023d3:	3a 20 55 
  4023d6:	48 89 45 00          	mov    %rax,0x0(%rbp)
  4023da:	48 b8 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rax
  4023e1:	20 74 6f 
  4023e4:	48 89 45 08          	mov    %rax,0x8(%rbp)
  4023e8:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  4023ef:	65 63 74 
  4023f2:	48 89 45 10          	mov    %rax,0x10(%rbp)
  4023f6:	48 b8 20 74 6f 20 73 	movabs $0x76726573206f7420,%rax
  4023fd:	65 72 76 
  402400:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402404:	66 c7 45 20 65 72    	movw   $0x7265,0x20(%rbp)
  40240a:	c6 45 22 00          	movb   $0x0,0x22(%rbp)
  40240e:	89 df                	mov    %ebx,%edi
  402410:	e8 9b e7 ff ff       	callq  400bb0 <close@plt>
  402415:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40241a:	eb 16                	jmp    402432 <init_driver+0x1d7>
  40241c:	89 df                	mov    %ebx,%edi
  40241e:	e8 8d e7 ff ff       	callq  400bb0 <close@plt>
  402423:	66 c7 45 00 4f 4b    	movw   $0x4b4f,0x0(%rbp)
  402429:	c6 45 02 00          	movb   $0x0,0x2(%rbp)
  40242d:	b8 00 00 00 00       	mov    $0x0,%eax
  402432:	48 8b 4c 24 18       	mov    0x18(%rsp),%rcx
  402437:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  40243e:	00 00 
  402440:	74 05                	je     402447 <init_driver+0x1ec>
  402442:	e8 49 e7 ff ff       	callq  400b90 <__stack_chk_fail@plt>
  402447:	48 83 c4 28          	add    $0x28,%rsp
  40244b:	5b                   	pop    %rbx
  40244c:	5d                   	pop    %rbp
  40244d:	c3                   	retq   

000000000040244e <driver_post>:
  40244e:	53                   	push   %rbx
  40244f:	4c 89 c3             	mov    %r8,%rbx
  402452:	85 c9                	test   %ecx,%ecx
  402454:	74 24                	je     40247a <driver_post+0x2c>
  402456:	be 25 2b 40 00       	mov    $0x402b25,%esi
  40245b:	bf 01 00 00 00       	mov    $0x1,%edi
  402460:	b8 00 00 00 00       	mov    $0x0,%eax
  402465:	e8 e6 e7 ff ff       	callq  400c50 <__printf_chk@plt>
  40246a:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  40246f:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  402473:	b8 00 00 00 00       	mov    $0x0,%eax
  402478:	eb 41                	jmp    4024bb <driver_post+0x6d>
  40247a:	48 85 ff             	test   %rdi,%rdi
  40247d:	74 2e                	je     4024ad <driver_post+0x5f>
  40247f:	80 3f 00             	cmpb   $0x0,(%rdi)
  402482:	74 29                	je     4024ad <driver_post+0x5f>
  402484:	41 50                	push   %r8
  402486:	52                   	push   %rdx
  402487:	41 b9 3c 2b 40 00    	mov    $0x402b3c,%r9d
  40248d:	49 89 f0             	mov    %rsi,%r8
  402490:	48 89 f9             	mov    %rdi,%rcx
  402493:	ba 40 2b 40 00       	mov    $0x402b40,%edx
  402498:	be 29 4b 00 00       	mov    $0x4b29,%esi
  40249d:	bf 18 2b 40 00       	mov    $0x402b18,%edi
  4024a2:	e8 83 f5 ff ff       	callq  401a2a <submitr>
  4024a7:	48 83 c4 10          	add    $0x10,%rsp
  4024ab:	eb 0e                	jmp    4024bb <driver_post+0x6d>
  4024ad:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  4024b2:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  4024b6:	b8 00 00 00 00       	mov    $0x0,%eax
  4024bb:	5b                   	pop    %rbx
  4024bc:	c3                   	retq   
  4024bd:	0f 1f 00             	nopl   (%rax)

00000000004024c0 <__libc_csu_init>:
  4024c0:	41 57                	push   %r15
  4024c2:	41 56                	push   %r14
  4024c4:	41 89 ff             	mov    %edi,%r15d
  4024c7:	41 55                	push   %r13
  4024c9:	41 54                	push   %r12
  4024cb:	4c 8d 25 3e 19 20 00 	lea    0x20193e(%rip),%r12        # 603e10 <__frame_dummy_init_array_entry>
  4024d2:	55                   	push   %rbp
  4024d3:	48 8d 2d 3e 19 20 00 	lea    0x20193e(%rip),%rbp        # 603e18 <__do_global_dtors_aux_fini_array_entry>
  4024da:	53                   	push   %rbx
  4024db:	49 89 f6             	mov    %rsi,%r14
  4024de:	49 89 d5             	mov    %rdx,%r13
  4024e1:	4c 29 e5             	sub    %r12,%rbp
  4024e4:	48 83 ec 08          	sub    $0x8,%rsp
  4024e8:	48 c1 fd 03          	sar    $0x3,%rbp
  4024ec:	e8 0f e6 ff ff       	callq  400b00 <_init>
  4024f1:	48 85 ed             	test   %rbp,%rbp
  4024f4:	74 20                	je     402516 <__libc_csu_init+0x56>
  4024f6:	31 db                	xor    %ebx,%ebx
  4024f8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  4024ff:	00 
  402500:	4c 89 ea             	mov    %r13,%rdx
  402503:	4c 89 f6             	mov    %r14,%rsi
  402506:	44 89 ff             	mov    %r15d,%edi
  402509:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40250d:	48 83 c3 01          	add    $0x1,%rbx
  402511:	48 39 eb             	cmp    %rbp,%rbx
  402514:	75 ea                	jne    402500 <__libc_csu_init+0x40>
  402516:	48 83 c4 08          	add    $0x8,%rsp
  40251a:	5b                   	pop    %rbx
  40251b:	5d                   	pop    %rbp
  40251c:	41 5c                	pop    %r12
  40251e:	41 5d                	pop    %r13
  402520:	41 5e                	pop    %r14
  402522:	41 5f                	pop    %r15
  402524:	c3                   	retq   
  402525:	90                   	nop
  402526:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40252d:	00 00 00 

0000000000402530 <__libc_csu_fini>:
  402530:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000402534 <_fini>:
  402534:	48 83 ec 08          	sub    $0x8,%rsp
  402538:	48 83 c4 08          	add    $0x8,%rsp
  40253c:	c3                   	retq   
