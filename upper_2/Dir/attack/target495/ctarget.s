
ctarget:     file format elf64-x86-64


Disassembly of section .init:

0000000000400c48 <_init>:
  400c48:	48 83 ec 08          	sub    $0x8,%rsp
  400c4c:	48 8b 05 a5 43 20 00 	mov    0x2043a5(%rip),%rax        # 604ff8 <__gmon_start__>
  400c53:	48 85 c0             	test   %rax,%rax
  400c56:	74 05                	je     400c5d <_init+0x15>
  400c58:	e8 43 02 00 00       	callq  400ea0 <__gmon_start__@plt>
  400c5d:	48 83 c4 08          	add    $0x8,%rsp
  400c61:	c3                   	retq   

Disassembly of section .plt:

0000000000400c70 <.plt>:
  400c70:	ff 35 92 43 20 00    	pushq  0x204392(%rip)        # 605008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400c76:	ff 25 94 43 20 00    	jmpq   *0x204394(%rip)        # 605010 <_GLOBAL_OFFSET_TABLE_+0x10>
  400c7c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400c80 <strcasecmp@plt>:
  400c80:	ff 25 92 43 20 00    	jmpq   *0x204392(%rip)        # 605018 <strcasecmp@GLIBC_2.2.5>
  400c86:	68 00 00 00 00       	pushq  $0x0
  400c8b:	e9 e0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400c90 <__errno_location@plt>:
  400c90:	ff 25 8a 43 20 00    	jmpq   *0x20438a(%rip)        # 605020 <__errno_location@GLIBC_2.2.5>
  400c96:	68 01 00 00 00       	pushq  $0x1
  400c9b:	e9 d0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400ca0 <srandom@plt>:
  400ca0:	ff 25 82 43 20 00    	jmpq   *0x204382(%rip)        # 605028 <srandom@GLIBC_2.2.5>
  400ca6:	68 02 00 00 00       	pushq  $0x2
  400cab:	e9 c0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cb0 <strncmp@plt>:
  400cb0:	ff 25 7a 43 20 00    	jmpq   *0x20437a(%rip)        # 605030 <strncmp@GLIBC_2.2.5>
  400cb6:	68 03 00 00 00       	pushq  $0x3
  400cbb:	e9 b0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cc0 <strcpy@plt>:
  400cc0:	ff 25 72 43 20 00    	jmpq   *0x204372(%rip)        # 605038 <strcpy@GLIBC_2.2.5>
  400cc6:	68 04 00 00 00       	pushq  $0x4
  400ccb:	e9 a0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cd0 <puts@plt>:
  400cd0:	ff 25 6a 43 20 00    	jmpq   *0x20436a(%rip)        # 605040 <puts@GLIBC_2.2.5>
  400cd6:	68 05 00 00 00       	pushq  $0x5
  400cdb:	e9 90 ff ff ff       	jmpq   400c70 <.plt>

0000000000400ce0 <write@plt>:
  400ce0:	ff 25 62 43 20 00    	jmpq   *0x204362(%rip)        # 605048 <write@GLIBC_2.2.5>
  400ce6:	68 06 00 00 00       	pushq  $0x6
  400ceb:	e9 80 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cf0 <__stack_chk_fail@plt>:
  400cf0:	ff 25 5a 43 20 00    	jmpq   *0x20435a(%rip)        # 605050 <__stack_chk_fail@GLIBC_2.4>
  400cf6:	68 07 00 00 00       	pushq  $0x7
  400cfb:	e9 70 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d00 <mmap@plt>:
  400d00:	ff 25 52 43 20 00    	jmpq   *0x204352(%rip)        # 605058 <mmap@GLIBC_2.2.5>
  400d06:	68 08 00 00 00       	pushq  $0x8
  400d0b:	e9 60 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d10 <memset@plt>:
  400d10:	ff 25 4a 43 20 00    	jmpq   *0x20434a(%rip)        # 605060 <memset@GLIBC_2.2.5>
  400d16:	68 09 00 00 00       	pushq  $0x9
  400d1b:	e9 50 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d20 <alarm@plt>:
  400d20:	ff 25 42 43 20 00    	jmpq   *0x204342(%rip)        # 605068 <alarm@GLIBC_2.2.5>
  400d26:	68 0a 00 00 00       	pushq  $0xa
  400d2b:	e9 40 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d30 <close@plt>:
  400d30:	ff 25 3a 43 20 00    	jmpq   *0x20433a(%rip)        # 605070 <close@GLIBC_2.2.5>
  400d36:	68 0b 00 00 00       	pushq  $0xb
  400d3b:	e9 30 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d40 <read@plt>:
  400d40:	ff 25 32 43 20 00    	jmpq   *0x204332(%rip)        # 605078 <read@GLIBC_2.2.5>
  400d46:	68 0c 00 00 00       	pushq  $0xc
  400d4b:	e9 20 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d50 <__libc_start_main@plt>:
  400d50:	ff 25 2a 43 20 00    	jmpq   *0x20432a(%rip)        # 605080 <__libc_start_main@GLIBC_2.2.5>
  400d56:	68 0d 00 00 00       	pushq  $0xd
  400d5b:	e9 10 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d60 <signal@plt>:
  400d60:	ff 25 22 43 20 00    	jmpq   *0x204322(%rip)        # 605088 <signal@GLIBC_2.2.5>
  400d66:	68 0e 00 00 00       	pushq  $0xe
  400d6b:	e9 00 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d70 <gethostbyname@plt>:
  400d70:	ff 25 1a 43 20 00    	jmpq   *0x20431a(%rip)        # 605090 <gethostbyname@GLIBC_2.2.5>
  400d76:	68 0f 00 00 00       	pushq  $0xf
  400d7b:	e9 f0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400d80 <__memmove_chk@plt>:
  400d80:	ff 25 12 43 20 00    	jmpq   *0x204312(%rip)        # 605098 <__memmove_chk@GLIBC_2.3.4>
  400d86:	68 10 00 00 00       	pushq  $0x10
  400d8b:	e9 e0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400d90 <strtol@plt>:
  400d90:	ff 25 0a 43 20 00    	jmpq   *0x20430a(%rip)        # 6050a0 <strtol@GLIBC_2.2.5>
  400d96:	68 11 00 00 00       	pushq  $0x11
  400d9b:	e9 d0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400da0 <memcpy@plt>:
  400da0:	ff 25 02 43 20 00    	jmpq   *0x204302(%rip)        # 6050a8 <memcpy@GLIBC_2.14>
  400da6:	68 12 00 00 00       	pushq  $0x12
  400dab:	e9 c0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400db0 <time@plt>:
  400db0:	ff 25 fa 42 20 00    	jmpq   *0x2042fa(%rip)        # 6050b0 <time@GLIBC_2.2.5>
  400db6:	68 13 00 00 00       	pushq  $0x13
  400dbb:	e9 b0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400dc0 <random@plt>:
  400dc0:	ff 25 f2 42 20 00    	jmpq   *0x2042f2(%rip)        # 6050b8 <random@GLIBC_2.2.5>
  400dc6:	68 14 00 00 00       	pushq  $0x14
  400dcb:	e9 a0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400dd0 <_IO_getc@plt>:
  400dd0:	ff 25 ea 42 20 00    	jmpq   *0x2042ea(%rip)        # 6050c0 <_IO_getc@GLIBC_2.2.5>
  400dd6:	68 15 00 00 00       	pushq  $0x15
  400ddb:	e9 90 fe ff ff       	jmpq   400c70 <.plt>

0000000000400de0 <__isoc99_sscanf@plt>:
  400de0:	ff 25 e2 42 20 00    	jmpq   *0x2042e2(%rip)        # 6050c8 <__isoc99_sscanf@GLIBC_2.7>
  400de6:	68 16 00 00 00       	pushq  $0x16
  400deb:	e9 80 fe ff ff       	jmpq   400c70 <.plt>

0000000000400df0 <munmap@plt>:
  400df0:	ff 25 da 42 20 00    	jmpq   *0x2042da(%rip)        # 6050d0 <munmap@GLIBC_2.2.5>
  400df6:	68 17 00 00 00       	pushq  $0x17
  400dfb:	e9 70 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e00 <__printf_chk@plt>:
  400e00:	ff 25 d2 42 20 00    	jmpq   *0x2042d2(%rip)        # 6050d8 <__printf_chk@GLIBC_2.3.4>
  400e06:	68 18 00 00 00       	pushq  $0x18
  400e0b:	e9 60 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e10 <fopen@plt>:
  400e10:	ff 25 ca 42 20 00    	jmpq   *0x2042ca(%rip)        # 6050e0 <fopen@GLIBC_2.2.5>
  400e16:	68 19 00 00 00       	pushq  $0x19
  400e1b:	e9 50 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e20 <getopt@plt>:
  400e20:	ff 25 c2 42 20 00    	jmpq   *0x2042c2(%rip)        # 6050e8 <getopt@GLIBC_2.2.5>
  400e26:	68 1a 00 00 00       	pushq  $0x1a
  400e2b:	e9 40 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e30 <strtoul@plt>:
  400e30:	ff 25 ba 42 20 00    	jmpq   *0x2042ba(%rip)        # 6050f0 <strtoul@GLIBC_2.2.5>
  400e36:	68 1b 00 00 00       	pushq  $0x1b
  400e3b:	e9 30 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e40 <gethostname@plt>:
  400e40:	ff 25 b2 42 20 00    	jmpq   *0x2042b2(%rip)        # 6050f8 <gethostname@GLIBC_2.2.5>
  400e46:	68 1c 00 00 00       	pushq  $0x1c
  400e4b:	e9 20 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e50 <exit@plt>:
  400e50:	ff 25 aa 42 20 00    	jmpq   *0x2042aa(%rip)        # 605100 <exit@GLIBC_2.2.5>
  400e56:	68 1d 00 00 00       	pushq  $0x1d
  400e5b:	e9 10 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e60 <connect@plt>:
  400e60:	ff 25 a2 42 20 00    	jmpq   *0x2042a2(%rip)        # 605108 <connect@GLIBC_2.2.5>
  400e66:	68 1e 00 00 00       	pushq  $0x1e
  400e6b:	e9 00 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e70 <__fprintf_chk@plt>:
  400e70:	ff 25 9a 42 20 00    	jmpq   *0x20429a(%rip)        # 605110 <__fprintf_chk@GLIBC_2.3.4>
  400e76:	68 1f 00 00 00       	pushq  $0x1f
  400e7b:	e9 f0 fd ff ff       	jmpq   400c70 <.plt>

0000000000400e80 <__sprintf_chk@plt>:
  400e80:	ff 25 92 42 20 00    	jmpq   *0x204292(%rip)        # 605118 <__sprintf_chk@GLIBC_2.3.4>
  400e86:	68 20 00 00 00       	pushq  $0x20
  400e8b:	e9 e0 fd ff ff       	jmpq   400c70 <.plt>

0000000000400e90 <socket@plt>:
  400e90:	ff 25 8a 42 20 00    	jmpq   *0x20428a(%rip)        # 605120 <socket@GLIBC_2.2.5>
  400e96:	68 21 00 00 00       	pushq  $0x21
  400e9b:	e9 d0 fd ff ff       	jmpq   400c70 <.plt>

Disassembly of section .plt.got:

0000000000400ea0 <__gmon_start__@plt>:
  400ea0:	ff 25 52 41 20 00    	jmpq   *0x204152(%rip)        # 604ff8 <__gmon_start__>
  400ea6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000400eb0 <_start>:
  400eb0:	31 ed                	xor    %ebp,%ebp
  400eb2:	49 89 d1             	mov    %rdx,%r9
  400eb5:	5e                   	pop    %rsi
  400eb6:	48 89 e2             	mov    %rsp,%rdx
  400eb9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400ebd:	50                   	push   %rax
  400ebe:	54                   	push   %rsp
  400ebf:	49 c7 c0 50 2f 40 00 	mov    $0x402f50,%r8
  400ec6:	48 c7 c1 e0 2e 40 00 	mov    $0x402ee0,%rcx
  400ecd:	48 c7 c7 b5 11 40 00 	mov    $0x4011b5,%rdi
  400ed4:	e8 77 fe ff ff       	callq  400d50 <__libc_start_main@plt>
  400ed9:	f4                   	hlt    
  400eda:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400ee0 <deregister_tm_clones>:
  400ee0:	b8 b7 54 60 00       	mov    $0x6054b7,%eax
  400ee5:	55                   	push   %rbp
  400ee6:	48 2d b0 54 60 00    	sub    $0x6054b0,%rax
  400eec:	48 83 f8 0e          	cmp    $0xe,%rax
  400ef0:	48 89 e5             	mov    %rsp,%rbp
  400ef3:	76 1b                	jbe    400f10 <deregister_tm_clones+0x30>
  400ef5:	b8 00 00 00 00       	mov    $0x0,%eax
  400efa:	48 85 c0             	test   %rax,%rax
  400efd:	74 11                	je     400f10 <deregister_tm_clones+0x30>
  400eff:	5d                   	pop    %rbp
  400f00:	bf b0 54 60 00       	mov    $0x6054b0,%edi
  400f05:	ff e0                	jmpq   *%rax
  400f07:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  400f0e:	00 00 
  400f10:	5d                   	pop    %rbp
  400f11:	c3                   	retq   
  400f12:	0f 1f 40 00          	nopl   0x0(%rax)
  400f16:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400f1d:	00 00 00 

0000000000400f20 <register_tm_clones>:
  400f20:	be b0 54 60 00       	mov    $0x6054b0,%esi
  400f25:	55                   	push   %rbp
  400f26:	48 81 ee b0 54 60 00 	sub    $0x6054b0,%rsi
  400f2d:	48 c1 fe 03          	sar    $0x3,%rsi
  400f31:	48 89 e5             	mov    %rsp,%rbp
  400f34:	48 89 f0             	mov    %rsi,%rax
  400f37:	48 c1 e8 3f          	shr    $0x3f,%rax
  400f3b:	48 01 c6             	add    %rax,%rsi
  400f3e:	48 d1 fe             	sar    %rsi
  400f41:	74 15                	je     400f58 <register_tm_clones+0x38>
  400f43:	b8 00 00 00 00       	mov    $0x0,%eax
  400f48:	48 85 c0             	test   %rax,%rax
  400f4b:	74 0b                	je     400f58 <register_tm_clones+0x38>
  400f4d:	5d                   	pop    %rbp
  400f4e:	bf b0 54 60 00       	mov    $0x6054b0,%edi
  400f53:	ff e0                	jmpq   *%rax
  400f55:	0f 1f 00             	nopl   (%rax)
  400f58:	5d                   	pop    %rbp
  400f59:	c3                   	retq   
  400f5a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400f60 <__do_global_dtors_aux>:
  400f60:	80 3d 81 45 20 00 00 	cmpb   $0x0,0x204581(%rip)        # 6054e8 <completed.7594>
  400f67:	75 11                	jne    400f7a <__do_global_dtors_aux+0x1a>
  400f69:	55                   	push   %rbp
  400f6a:	48 89 e5             	mov    %rsp,%rbp
  400f6d:	e8 6e ff ff ff       	callq  400ee0 <deregister_tm_clones>
  400f72:	5d                   	pop    %rbp
  400f73:	c6 05 6e 45 20 00 01 	movb   $0x1,0x20456e(%rip)        # 6054e8 <completed.7594>
  400f7a:	f3 c3                	repz retq 
  400f7c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400f80 <frame_dummy>:
  400f80:	bf 20 4e 60 00       	mov    $0x604e20,%edi
  400f85:	48 83 3f 00          	cmpq   $0x0,(%rdi)
  400f89:	75 05                	jne    400f90 <frame_dummy+0x10>
  400f8b:	eb 93                	jmp    400f20 <register_tm_clones>
  400f8d:	0f 1f 00             	nopl   (%rax)
  400f90:	b8 00 00 00 00       	mov    $0x0,%eax
  400f95:	48 85 c0             	test   %rax,%rax
  400f98:	74 f1                	je     400f8b <frame_dummy+0xb>
  400f9a:	55                   	push   %rbp
  400f9b:	48 89 e5             	mov    %rsp,%rbp
  400f9e:	ff d0                	callq  *%rax
  400fa0:	5d                   	pop    %rbp
  400fa1:	e9 7a ff ff ff       	jmpq   400f20 <register_tm_clones>

0000000000400fa6 <usage>:
  400fa6:	48 83 ec 08          	sub    $0x8,%rsp
  400faa:	48 89 fa             	mov    %rdi,%rdx
  400fad:	83 3d 74 45 20 00 00 	cmpl   $0x0,0x204574(%rip)        # 605528 <is_checker>
  400fb4:	74 3e                	je     400ff4 <usage+0x4e>
  400fb6:	be 68 2f 40 00       	mov    $0x402f68,%esi
  400fbb:	bf 01 00 00 00       	mov    $0x1,%edi
  400fc0:	b8 00 00 00 00       	mov    $0x0,%eax
  400fc5:	e8 36 fe ff ff       	callq  400e00 <__printf_chk@plt>
  400fca:	bf a0 2f 40 00       	mov    $0x402fa0,%edi
  400fcf:	e8 fc fc ff ff       	callq  400cd0 <puts@plt>
  400fd4:	bf 18 31 40 00       	mov    $0x403118,%edi
  400fd9:	e8 f2 fc ff ff       	callq  400cd0 <puts@plt>
  400fde:	bf c8 2f 40 00       	mov    $0x402fc8,%edi
  400fe3:	e8 e8 fc ff ff       	callq  400cd0 <puts@plt>
  400fe8:	bf 32 31 40 00       	mov    $0x403132,%edi
  400fed:	e8 de fc ff ff       	callq  400cd0 <puts@plt>
  400ff2:	eb 32                	jmp    401026 <usage+0x80>
  400ff4:	be 4e 31 40 00       	mov    $0x40314e,%esi
  400ff9:	bf 01 00 00 00       	mov    $0x1,%edi
  400ffe:	b8 00 00 00 00       	mov    $0x0,%eax
  401003:	e8 f8 fd ff ff       	callq  400e00 <__printf_chk@plt>
  401008:	bf f0 2f 40 00       	mov    $0x402ff0,%edi
  40100d:	e8 be fc ff ff       	callq  400cd0 <puts@plt>
  401012:	bf 18 30 40 00       	mov    $0x403018,%edi
  401017:	e8 b4 fc ff ff       	callq  400cd0 <puts@plt>
  40101c:	bf 6c 31 40 00       	mov    $0x40316c,%edi
  401021:	e8 aa fc ff ff       	callq  400cd0 <puts@plt>
  401026:	bf 00 00 00 00       	mov    $0x0,%edi
  40102b:	e8 20 fe ff ff       	callq  400e50 <exit@plt>

0000000000401030 <initialize_target>:
  401030:	55                   	push   %rbp
  401031:	53                   	push   %rbx
  401032:	48 81 ec 18 21 00 00 	sub    $0x2118,%rsp
  401039:	89 f5                	mov    %esi,%ebp
  40103b:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401042:	00 00 
  401044:	48 89 84 24 08 21 00 	mov    %rax,0x2108(%rsp)
  40104b:	00 
  40104c:	31 c0                	xor    %eax,%eax
  40104e:	89 3d c4 44 20 00    	mov    %edi,0x2044c4(%rip)        # 605518 <check_level>
  401054:	8b 3d 0e 41 20 00    	mov    0x20410e(%rip),%edi        # 605168 <target_id>
  40105a:	e8 54 1e 00 00       	callq  402eb3 <gencookie>
  40105f:	89 05 bf 44 20 00    	mov    %eax,0x2044bf(%rip)        # 605524 <cookie>
  401065:	89 c7                	mov    %eax,%edi
  401067:	e8 47 1e 00 00       	callq  402eb3 <gencookie>
  40106c:	89 05 ae 44 20 00    	mov    %eax,0x2044ae(%rip)        # 605520 <authkey>
  401072:	8b 05 f0 40 20 00    	mov    0x2040f0(%rip),%eax        # 605168 <target_id>
  401078:	8d 78 01             	lea    0x1(%rax),%edi
  40107b:	e8 20 fc ff ff       	callq  400ca0 <srandom@plt>
  401080:	e8 3b fd ff ff       	callq  400dc0 <random@plt>
  401085:	89 c7                	mov    %eax,%edi
  401087:	e8 03 03 00 00       	callq  40138f <scramble>
  40108c:	89 c3                	mov    %eax,%ebx
  40108e:	85 ed                	test   %ebp,%ebp
  401090:	74 18                	je     4010aa <initialize_target+0x7a>
  401092:	bf 00 00 00 00       	mov    $0x0,%edi
  401097:	e8 14 fd ff ff       	callq  400db0 <time@plt>
  40109c:	89 c7                	mov    %eax,%edi
  40109e:	e8 fd fb ff ff       	callq  400ca0 <srandom@plt>
  4010a3:	e8 18 fd ff ff       	callq  400dc0 <random@plt>
  4010a8:	eb 05                	jmp    4010af <initialize_target+0x7f>
  4010aa:	b8 00 00 00 00       	mov    $0x0,%eax
  4010af:	01 c3                	add    %eax,%ebx
  4010b1:	0f b7 db             	movzwl %bx,%ebx
  4010b4:	8d 04 dd 00 01 00 00 	lea    0x100(,%rbx,8),%eax
  4010bb:	89 c0                	mov    %eax,%eax
  4010bd:	48 89 05 dc 43 20 00 	mov    %rax,0x2043dc(%rip)        # 6054a0 <buf_offset>
  4010c4:	c6 05 7d 50 20 00 63 	movb   $0x63,0x20507d(%rip)        # 606148 <target_prefix>
  4010cb:	83 3d d6 43 20 00 00 	cmpl   $0x0,0x2043d6(%rip)        # 6054a8 <notify>
  4010d2:	0f 84 bb 00 00 00    	je     401193 <initialize_target+0x163>
  4010d8:	83 3d 49 44 20 00 00 	cmpl   $0x0,0x204449(%rip)        # 605528 <is_checker>
  4010df:	0f 85 ae 00 00 00    	jne    401193 <initialize_target+0x163>
  4010e5:	be 00 01 00 00       	mov    $0x100,%esi
  4010ea:	48 89 e7             	mov    %rsp,%rdi
  4010ed:	e8 4e fd ff ff       	callq  400e40 <gethostname@plt>
  4010f2:	85 c0                	test   %eax,%eax
  4010f4:	74 25                	je     40111b <initialize_target+0xeb>
  4010f6:	bf 48 30 40 00       	mov    $0x403048,%edi
  4010fb:	e8 d0 fb ff ff       	callq  400cd0 <puts@plt>
  401100:	bf 08 00 00 00       	mov    $0x8,%edi
  401105:	e8 46 fd ff ff       	callq  400e50 <exit@plt>
  40110a:	48 89 e6             	mov    %rsp,%rsi
  40110d:	e8 6e fb ff ff       	callq  400c80 <strcasecmp@plt>
  401112:	85 c0                	test   %eax,%eax
  401114:	74 21                	je     401137 <initialize_target+0x107>
  401116:	83 c3 01             	add    $0x1,%ebx
  401119:	eb 05                	jmp    401120 <initialize_target+0xf0>
  40111b:	bb 00 00 00 00       	mov    $0x0,%ebx
  401120:	48 63 c3             	movslq %ebx,%rax
  401123:	48 8b 3c c5 80 51 60 	mov    0x605180(,%rax,8),%rdi
  40112a:	00 
  40112b:	48 85 ff             	test   %rdi,%rdi
  40112e:	75 da                	jne    40110a <initialize_target+0xda>
  401130:	b8 00 00 00 00       	mov    $0x0,%eax
  401135:	eb 05                	jmp    40113c <initialize_target+0x10c>
  401137:	b8 01 00 00 00       	mov    $0x1,%eax
  40113c:	85 c0                	test   %eax,%eax
  40113e:	75 1c                	jne    40115c <initialize_target+0x12c>
  401140:	48 89 e2             	mov    %rsp,%rdx
  401143:	be 80 30 40 00       	mov    $0x403080,%esi
  401148:	bf 01 00 00 00       	mov    $0x1,%edi
  40114d:	e8 ae fc ff ff       	callq  400e00 <__printf_chk@plt>
  401152:	bf 08 00 00 00       	mov    $0x8,%edi
  401157:	e8 f4 fc ff ff       	callq  400e50 <exit@plt>
  40115c:	48 8d bc 24 00 01 00 	lea    0x100(%rsp),%rdi
  401163:	00 
  401164:	e8 b4 1a 00 00       	callq  402c1d <init_driver>
  401169:	85 c0                	test   %eax,%eax
  40116b:	79 26                	jns    401193 <initialize_target+0x163>
  40116d:	48 8d 94 24 00 01 00 	lea    0x100(%rsp),%rdx
  401174:	00 
  401175:	be c0 30 40 00       	mov    $0x4030c0,%esi
  40117a:	bf 01 00 00 00       	mov    $0x1,%edi
  40117f:	b8 00 00 00 00       	mov    $0x0,%eax
  401184:	e8 77 fc ff ff       	callq  400e00 <__printf_chk@plt>
  401189:	bf 08 00 00 00       	mov    $0x8,%edi
  40118e:	e8 bd fc ff ff       	callq  400e50 <exit@plt>
  401193:	48 8b 84 24 08 21 00 	mov    0x2108(%rsp),%rax
  40119a:	00 
  40119b:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4011a2:	00 00 
  4011a4:	74 05                	je     4011ab <initialize_target+0x17b>
  4011a6:	e8 45 fb ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  4011ab:	48 81 c4 18 21 00 00 	add    $0x2118,%rsp
  4011b2:	5b                   	pop    %rbx
  4011b3:	5d                   	pop    %rbp
  4011b4:	c3                   	retq   

00000000004011b5 <main>:
  4011b5:	41 56                	push   %r14
  4011b7:	41 55                	push   %r13
  4011b9:	41 54                	push   %r12
  4011bb:	55                   	push   %rbp
  4011bc:	53                   	push   %rbx
  4011bd:	41 89 fc             	mov    %edi,%r12d
  4011c0:	48 89 f3             	mov    %rsi,%rbx
  4011c3:	be 58 1f 40 00       	mov    $0x401f58,%esi
  4011c8:	bf 0b 00 00 00       	mov    $0xb,%edi
  4011cd:	e8 8e fb ff ff       	callq  400d60 <signal@plt>
  4011d2:	be 0a 1f 40 00       	mov    $0x401f0a,%esi
  4011d7:	bf 07 00 00 00       	mov    $0x7,%edi
  4011dc:	e8 7f fb ff ff       	callq  400d60 <signal@plt>
  4011e1:	be a6 1f 40 00       	mov    $0x401fa6,%esi
  4011e6:	bf 04 00 00 00       	mov    $0x4,%edi
  4011eb:	e8 70 fb ff ff       	callq  400d60 <signal@plt>
  4011f0:	83 3d 31 43 20 00 00 	cmpl   $0x0,0x204331(%rip)        # 605528 <is_checker>
  4011f7:	74 20                	je     401219 <main+0x64>
  4011f9:	be f4 1f 40 00       	mov    $0x401ff4,%esi
  4011fe:	bf 0e 00 00 00       	mov    $0xe,%edi
  401203:	e8 58 fb ff ff       	callq  400d60 <signal@plt>
  401208:	bf 05 00 00 00       	mov    $0x5,%edi
  40120d:	e8 0e fb ff ff       	callq  400d20 <alarm@plt>
  401212:	bd 8a 31 40 00       	mov    $0x40318a,%ebp
  401217:	eb 05                	jmp    40121e <main+0x69>
  401219:	bd 85 31 40 00       	mov    $0x403185,%ebp
  40121e:	48 8b 05 9b 42 20 00 	mov    0x20429b(%rip),%rax        # 6054c0 <stdin@@GLIBC_2.2.5>
  401225:	48 89 05 e4 42 20 00 	mov    %rax,0x2042e4(%rip)        # 605510 <infile>
  40122c:	41 bd 00 00 00 00    	mov    $0x0,%r13d
  401232:	41 be 00 00 00 00    	mov    $0x0,%r14d
  401238:	e9 c6 00 00 00       	jmpq   401303 <main+0x14e>
  40123d:	83 e8 61             	sub    $0x61,%eax
  401240:	3c 10                	cmp    $0x10,%al
  401242:	0f 87 9c 00 00 00    	ja     4012e4 <main+0x12f>
  401248:	0f b6 c0             	movzbl %al,%eax
  40124b:	ff 24 c5 d0 31 40 00 	jmpq   *0x4031d0(,%rax,8)
  401252:	48 8b 3b             	mov    (%rbx),%rdi
  401255:	e8 4c fd ff ff       	callq  400fa6 <usage>
  40125a:	be 5d 34 40 00       	mov    $0x40345d,%esi
  40125f:	48 8b 3d 62 42 20 00 	mov    0x204262(%rip),%rdi        # 6054c8 <optarg@@GLIBC_2.2.5>
  401266:	e8 a5 fb ff ff       	callq  400e10 <fopen@plt>
  40126b:	48 89 05 9e 42 20 00 	mov    %rax,0x20429e(%rip)        # 605510 <infile>
  401272:	48 85 c0             	test   %rax,%rax
  401275:	0f 85 88 00 00 00    	jne    401303 <main+0x14e>
  40127b:	48 8b 0d 46 42 20 00 	mov    0x204246(%rip),%rcx        # 6054c8 <optarg@@GLIBC_2.2.5>
  401282:	ba 92 31 40 00       	mov    $0x403192,%edx
  401287:	be 01 00 00 00       	mov    $0x1,%esi
  40128c:	48 8b 3d 4d 42 20 00 	mov    0x20424d(%rip),%rdi        # 6054e0 <stderr@@GLIBC_2.2.5>
  401293:	e8 d8 fb ff ff       	callq  400e70 <__fprintf_chk@plt>
  401298:	b8 01 00 00 00       	mov    $0x1,%eax
  40129d:	e9 e4 00 00 00       	jmpq   401386 <main+0x1d1>
  4012a2:	ba 10 00 00 00       	mov    $0x10,%edx
  4012a7:	be 00 00 00 00       	mov    $0x0,%esi
  4012ac:	48 8b 3d 15 42 20 00 	mov    0x204215(%rip),%rdi        # 6054c8 <optarg@@GLIBC_2.2.5>
  4012b3:	e8 78 fb ff ff       	callq  400e30 <strtoul@plt>
  4012b8:	41 89 c6             	mov    %eax,%r14d
  4012bb:	eb 46                	jmp    401303 <main+0x14e>
  4012bd:	ba 0a 00 00 00       	mov    $0xa,%edx
  4012c2:	be 00 00 00 00       	mov    $0x0,%esi
  4012c7:	48 8b 3d fa 41 20 00 	mov    0x2041fa(%rip),%rdi        # 6054c8 <optarg@@GLIBC_2.2.5>
  4012ce:	e8 bd fa ff ff       	callq  400d90 <strtol@plt>
  4012d3:	41 89 c5             	mov    %eax,%r13d
  4012d6:	eb 2b                	jmp    401303 <main+0x14e>
  4012d8:	c7 05 c6 41 20 00 00 	movl   $0x0,0x2041c6(%rip)        # 6054a8 <notify>
  4012df:	00 00 00 
  4012e2:	eb 1f                	jmp    401303 <main+0x14e>
  4012e4:	0f be d2             	movsbl %dl,%edx
  4012e7:	be af 31 40 00       	mov    $0x4031af,%esi
  4012ec:	bf 01 00 00 00       	mov    $0x1,%edi
  4012f1:	b8 00 00 00 00       	mov    $0x0,%eax
  4012f6:	e8 05 fb ff ff       	callq  400e00 <__printf_chk@plt>
  4012fb:	48 8b 3b             	mov    (%rbx),%rdi
  4012fe:	e8 a3 fc ff ff       	callq  400fa6 <usage>
  401303:	48 89 ea             	mov    %rbp,%rdx
  401306:	48 89 de             	mov    %rbx,%rsi
  401309:	44 89 e7             	mov    %r12d,%edi
  40130c:	e8 0f fb ff ff       	callq  400e20 <getopt@plt>
  401311:	89 c2                	mov    %eax,%edx
  401313:	3c ff                	cmp    $0xff,%al
  401315:	0f 85 22 ff ff ff    	jne    40123d <main+0x88>
  40131b:	be 00 00 00 00       	mov    $0x0,%esi
  401320:	44 89 ef             	mov    %r13d,%edi
  401323:	e8 08 fd ff ff       	callq  401030 <initialize_target>
  401328:	83 3d f9 41 20 00 00 	cmpl   $0x0,0x2041f9(%rip)        # 605528 <is_checker>
  40132f:	74 2a                	je     40135b <main+0x1a6>
  401331:	44 3b 35 e8 41 20 00 	cmp    0x2041e8(%rip),%r14d        # 605520 <authkey>
  401338:	74 21                	je     40135b <main+0x1a6>
  40133a:	44 89 f2             	mov    %r14d,%edx
  40133d:	be e8 30 40 00       	mov    $0x4030e8,%esi
  401342:	bf 01 00 00 00       	mov    $0x1,%edi
  401347:	b8 00 00 00 00       	mov    $0x0,%eax
  40134c:	e8 af fa ff ff       	callq  400e00 <__printf_chk@plt>
  401351:	b8 00 00 00 00       	mov    $0x0,%eax
  401356:	e8 4b 08 00 00       	callq  401ba6 <check_fail>
  40135b:	8b 15 c3 41 20 00    	mov    0x2041c3(%rip),%edx        # 605524 <cookie>
  401361:	be c2 31 40 00       	mov    $0x4031c2,%esi
  401366:	bf 01 00 00 00       	mov    $0x1,%edi
  40136b:	b8 00 00 00 00       	mov    $0x0,%eax
  401370:	e8 8b fa ff ff       	callq  400e00 <__printf_chk@plt>
  401375:	48 8b 3d 24 41 20 00 	mov    0x204124(%rip),%rdi        # 6054a0 <buf_offset>
  40137c:	e8 73 0d 00 00       	callq  4020f4 <stable_launch>
  401381:	b8 00 00 00 00       	mov    $0x0,%eax
  401386:	5b                   	pop    %rbx
  401387:	5d                   	pop    %rbp
  401388:	41 5c                	pop    %r12
  40138a:	41 5d                	pop    %r13
  40138c:	41 5e                	pop    %r14
  40138e:	c3                   	retq   

000000000040138f <scramble>:
  40138f:	48 83 ec 38          	sub    $0x38,%rsp
  401393:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40139a:	00 00 
  40139c:	48 89 44 24 28       	mov    %rax,0x28(%rsp)
  4013a1:	31 c0                	xor    %eax,%eax
  4013a3:	eb 10                	jmp    4013b5 <scramble+0x26>
  4013a5:	69 d0 11 8e 00 00    	imul   $0x8e11,%eax,%edx
  4013ab:	01 fa                	add    %edi,%edx
  4013ad:	89 c1                	mov    %eax,%ecx
  4013af:	89 14 8c             	mov    %edx,(%rsp,%rcx,4)
  4013b2:	83 c0 01             	add    $0x1,%eax
  4013b5:	83 f8 09             	cmp    $0x9,%eax
  4013b8:	76 eb                	jbe    4013a5 <scramble+0x16>
  4013ba:	8b 44 24 04          	mov    0x4(%rsp),%eax
  4013be:	69 c0 85 52 00 00    	imul   $0x5285,%eax,%eax
  4013c4:	89 44 24 04          	mov    %eax,0x4(%rsp)
  4013c8:	8b 44 24 14          	mov    0x14(%rsp),%eax
  4013cc:	69 c0 5d 27 00 00    	imul   $0x275d,%eax,%eax
  4013d2:	89 44 24 14          	mov    %eax,0x14(%rsp)
  4013d6:	8b 04 24             	mov    (%rsp),%eax
  4013d9:	69 c0 b8 94 00 00    	imul   $0x94b8,%eax,%eax
  4013df:	89 04 24             	mov    %eax,(%rsp)
  4013e2:	8b 44 24 08          	mov    0x8(%rsp),%eax
  4013e6:	69 c0 f4 8a 00 00    	imul   $0x8af4,%eax,%eax
  4013ec:	89 44 24 08          	mov    %eax,0x8(%rsp)
  4013f0:	8b 44 24 08          	mov    0x8(%rsp),%eax
  4013f4:	69 c0 56 90 00 00    	imul   $0x9056,%eax,%eax
  4013fa:	89 44 24 08          	mov    %eax,0x8(%rsp)
  4013fe:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  401402:	69 c0 90 44 00 00    	imul   $0x4490,%eax,%eax
  401408:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  40140c:	8b 44 24 08          	mov    0x8(%rsp),%eax
  401410:	69 c0 cb 83 00 00    	imul   $0x83cb,%eax,%eax
  401416:	89 44 24 08          	mov    %eax,0x8(%rsp)
  40141a:	8b 04 24             	mov    (%rsp),%eax
  40141d:	69 c0 95 91 00 00    	imul   $0x9195,%eax,%eax
  401423:	89 04 24             	mov    %eax,(%rsp)
  401426:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  40142a:	69 c0 66 a0 00 00    	imul   $0xa066,%eax,%eax
  401430:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  401434:	8b 44 24 18          	mov    0x18(%rsp),%eax
  401438:	69 c0 be 60 00 00    	imul   $0x60be,%eax,%eax
  40143e:	89 44 24 18          	mov    %eax,0x18(%rsp)
  401442:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  401446:	69 c0 a9 2b 00 00    	imul   $0x2ba9,%eax,%eax
  40144c:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  401450:	8b 44 24 24          	mov    0x24(%rsp),%eax
  401454:	69 c0 bf 1b 00 00    	imul   $0x1bbf,%eax,%eax
  40145a:	89 44 24 24          	mov    %eax,0x24(%rsp)
  40145e:	8b 44 24 14          	mov    0x14(%rsp),%eax
  401462:	69 c0 9c ee 00 00    	imul   $0xee9c,%eax,%eax
  401468:	89 44 24 14          	mov    %eax,0x14(%rsp)
  40146c:	8b 44 24 20          	mov    0x20(%rsp),%eax
  401470:	69 c0 e7 12 00 00    	imul   $0x12e7,%eax,%eax
  401476:	89 44 24 20          	mov    %eax,0x20(%rsp)
  40147a:	8b 44 24 08          	mov    0x8(%rsp),%eax
  40147e:	69 c0 7e a0 00 00    	imul   $0xa07e,%eax,%eax
  401484:	89 44 24 08          	mov    %eax,0x8(%rsp)
  401488:	8b 44 24 08          	mov    0x8(%rsp),%eax
  40148c:	69 c0 46 52 00 00    	imul   $0x5246,%eax,%eax
  401492:	89 44 24 08          	mov    %eax,0x8(%rsp)
  401496:	8b 44 24 04          	mov    0x4(%rsp),%eax
  40149a:	69 c0 cd b2 00 00    	imul   $0xb2cd,%eax,%eax
  4014a0:	89 44 24 04          	mov    %eax,0x4(%rsp)
  4014a4:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  4014a8:	69 c0 4d 03 00 00    	imul   $0x34d,%eax,%eax
  4014ae:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  4014b2:	8b 44 24 04          	mov    0x4(%rsp),%eax
  4014b6:	69 c0 13 66 00 00    	imul   $0x6613,%eax,%eax
  4014bc:	89 44 24 04          	mov    %eax,0x4(%rsp)
  4014c0:	8b 44 24 24          	mov    0x24(%rsp),%eax
  4014c4:	69 c0 ec c2 00 00    	imul   $0xc2ec,%eax,%eax
  4014ca:	89 44 24 24          	mov    %eax,0x24(%rsp)
  4014ce:	8b 44 24 08          	mov    0x8(%rsp),%eax
  4014d2:	69 c0 f5 bf 00 00    	imul   $0xbff5,%eax,%eax
  4014d8:	89 44 24 08          	mov    %eax,0x8(%rsp)
  4014dc:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  4014e0:	69 c0 9f 30 00 00    	imul   $0x309f,%eax,%eax
  4014e6:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  4014ea:	8b 04 24             	mov    (%rsp),%eax
  4014ed:	69 c0 bd b0 00 00    	imul   $0xb0bd,%eax,%eax
  4014f3:	89 04 24             	mov    %eax,(%rsp)
  4014f6:	8b 44 24 14          	mov    0x14(%rsp),%eax
  4014fa:	69 c0 c7 c6 00 00    	imul   $0xc6c7,%eax,%eax
  401500:	89 44 24 14          	mov    %eax,0x14(%rsp)
  401504:	8b 44 24 14          	mov    0x14(%rsp),%eax
  401508:	69 c0 26 a6 00 00    	imul   $0xa626,%eax,%eax
  40150e:	89 44 24 14          	mov    %eax,0x14(%rsp)
  401512:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  401516:	69 c0 b5 93 00 00    	imul   $0x93b5,%eax,%eax
  40151c:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  401520:	8b 04 24             	mov    (%rsp),%eax
  401523:	69 c0 40 4e 00 00    	imul   $0x4e40,%eax,%eax
  401529:	89 04 24             	mov    %eax,(%rsp)
  40152c:	8b 04 24             	mov    (%rsp),%eax
  40152f:	69 c0 fb 76 00 00    	imul   $0x76fb,%eax,%eax
  401535:	89 04 24             	mov    %eax,(%rsp)
  401538:	8b 44 24 20          	mov    0x20(%rsp),%eax
  40153c:	69 c0 30 e0 00 00    	imul   $0xe030,%eax,%eax
  401542:	89 44 24 20          	mov    %eax,0x20(%rsp)
  401546:	8b 44 24 10          	mov    0x10(%rsp),%eax
  40154a:	69 c0 11 01 00 00    	imul   $0x111,%eax,%eax
  401550:	89 44 24 10          	mov    %eax,0x10(%rsp)
  401554:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  401558:	69 c0 32 2a 00 00    	imul   $0x2a32,%eax,%eax
  40155e:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  401562:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  401566:	69 c0 b2 73 00 00    	imul   $0x73b2,%eax,%eax
  40156c:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  401570:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  401574:	69 c0 fa cc 00 00    	imul   $0xccfa,%eax,%eax
  40157a:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  40157e:	8b 44 24 08          	mov    0x8(%rsp),%eax
  401582:	69 c0 85 24 00 00    	imul   $0x2485,%eax,%eax
  401588:	89 44 24 08          	mov    %eax,0x8(%rsp)
  40158c:	8b 44 24 24          	mov    0x24(%rsp),%eax
  401590:	69 c0 40 05 00 00    	imul   $0x540,%eax,%eax
  401596:	89 44 24 24          	mov    %eax,0x24(%rsp)
  40159a:	8b 44 24 18          	mov    0x18(%rsp),%eax
  40159e:	69 c0 77 29 00 00    	imul   $0x2977,%eax,%eax
  4015a4:	89 44 24 18          	mov    %eax,0x18(%rsp)
  4015a8:	8b 44 24 20          	mov    0x20(%rsp),%eax
  4015ac:	69 c0 ed ee 00 00    	imul   $0xeeed,%eax,%eax
  4015b2:	89 44 24 20          	mov    %eax,0x20(%rsp)
  4015b6:	8b 04 24             	mov    (%rsp),%eax
  4015b9:	69 c0 f7 08 00 00    	imul   $0x8f7,%eax,%eax
  4015bf:	89 04 24             	mov    %eax,(%rsp)
  4015c2:	8b 44 24 10          	mov    0x10(%rsp),%eax
  4015c6:	69 c0 4b 1c 00 00    	imul   $0x1c4b,%eax,%eax
  4015cc:	89 44 24 10          	mov    %eax,0x10(%rsp)
  4015d0:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  4015d4:	69 c0 cd f0 00 00    	imul   $0xf0cd,%eax,%eax
  4015da:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  4015de:	8b 44 24 24          	mov    0x24(%rsp),%eax
  4015e2:	69 c0 43 f7 00 00    	imul   $0xf743,%eax,%eax
  4015e8:	89 44 24 24          	mov    %eax,0x24(%rsp)
  4015ec:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  4015f0:	69 c0 40 94 00 00    	imul   $0x9440,%eax,%eax
  4015f6:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  4015fa:	8b 44 24 04          	mov    0x4(%rsp),%eax
  4015fe:	69 c0 f7 33 00 00    	imul   $0x33f7,%eax,%eax
  401604:	89 44 24 04          	mov    %eax,0x4(%rsp)
  401608:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  40160c:	69 c0 60 82 00 00    	imul   $0x8260,%eax,%eax
  401612:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  401616:	8b 44 24 14          	mov    0x14(%rsp),%eax
  40161a:	69 c0 1e 95 00 00    	imul   $0x951e,%eax,%eax
  401620:	89 44 24 14          	mov    %eax,0x14(%rsp)
  401624:	8b 44 24 08          	mov    0x8(%rsp),%eax
  401628:	69 c0 d6 94 00 00    	imul   $0x94d6,%eax,%eax
  40162e:	89 44 24 08          	mov    %eax,0x8(%rsp)
  401632:	8b 44 24 08          	mov    0x8(%rsp),%eax
  401636:	69 c0 c8 d6 00 00    	imul   $0xd6c8,%eax,%eax
  40163c:	89 44 24 08          	mov    %eax,0x8(%rsp)
  401640:	8b 44 24 08          	mov    0x8(%rsp),%eax
  401644:	69 c0 50 9c 00 00    	imul   $0x9c50,%eax,%eax
  40164a:	89 44 24 08          	mov    %eax,0x8(%rsp)
  40164e:	8b 44 24 24          	mov    0x24(%rsp),%eax
  401652:	69 c0 88 7f 00 00    	imul   $0x7f88,%eax,%eax
  401658:	89 44 24 24          	mov    %eax,0x24(%rsp)
  40165c:	8b 44 24 08          	mov    0x8(%rsp),%eax
  401660:	69 c0 d0 d6 00 00    	imul   $0xd6d0,%eax,%eax
  401666:	89 44 24 08          	mov    %eax,0x8(%rsp)
  40166a:	8b 44 24 20          	mov    0x20(%rsp),%eax
  40166e:	69 c0 46 a8 00 00    	imul   $0xa846,%eax,%eax
  401674:	89 44 24 20          	mov    %eax,0x20(%rsp)
  401678:	8b 44 24 04          	mov    0x4(%rsp),%eax
  40167c:	69 c0 fe 49 00 00    	imul   $0x49fe,%eax,%eax
  401682:	89 44 24 04          	mov    %eax,0x4(%rsp)
  401686:	8b 44 24 14          	mov    0x14(%rsp),%eax
  40168a:	69 c0 5e 5a 00 00    	imul   $0x5a5e,%eax,%eax
  401690:	89 44 24 14          	mov    %eax,0x14(%rsp)
  401694:	8b 44 24 04          	mov    0x4(%rsp),%eax
  401698:	69 c0 de 36 00 00    	imul   $0x36de,%eax,%eax
  40169e:	89 44 24 04          	mov    %eax,0x4(%rsp)
  4016a2:	8b 44 24 04          	mov    0x4(%rsp),%eax
  4016a6:	69 c0 b3 22 00 00    	imul   $0x22b3,%eax,%eax
  4016ac:	89 44 24 04          	mov    %eax,0x4(%rsp)
  4016b0:	8b 04 24             	mov    (%rsp),%eax
  4016b3:	69 c0 1a 39 00 00    	imul   $0x391a,%eax,%eax
  4016b9:	89 04 24             	mov    %eax,(%rsp)
  4016bc:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  4016c0:	69 c0 2e ac 00 00    	imul   $0xac2e,%eax,%eax
  4016c6:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  4016ca:	8b 04 24             	mov    (%rsp),%eax
  4016cd:	69 c0 7a 5f 00 00    	imul   $0x5f7a,%eax,%eax
  4016d3:	89 04 24             	mov    %eax,(%rsp)
  4016d6:	8b 44 24 08          	mov    0x8(%rsp),%eax
  4016da:	69 c0 96 d8 00 00    	imul   $0xd896,%eax,%eax
  4016e0:	89 44 24 08          	mov    %eax,0x8(%rsp)
  4016e4:	8b 44 24 20          	mov    0x20(%rsp),%eax
  4016e8:	69 c0 4d f4 00 00    	imul   $0xf44d,%eax,%eax
  4016ee:	89 44 24 20          	mov    %eax,0x20(%rsp)
  4016f2:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  4016f6:	69 c0 4b 65 00 00    	imul   $0x654b,%eax,%eax
  4016fc:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  401700:	8b 44 24 04          	mov    0x4(%rsp),%eax
  401704:	69 c0 05 2d 00 00    	imul   $0x2d05,%eax,%eax
  40170a:	89 44 24 04          	mov    %eax,0x4(%rsp)
  40170e:	8b 44 24 14          	mov    0x14(%rsp),%eax
  401712:	69 c0 ac 91 00 00    	imul   $0x91ac,%eax,%eax
  401718:	89 44 24 14          	mov    %eax,0x14(%rsp)
  40171c:	8b 04 24             	mov    (%rsp),%eax
  40171f:	69 c0 d5 df 00 00    	imul   $0xdfd5,%eax,%eax
  401725:	89 04 24             	mov    %eax,(%rsp)
  401728:	8b 44 24 08          	mov    0x8(%rsp),%eax
  40172c:	69 c0 2a 8a 00 00    	imul   $0x8a2a,%eax,%eax
  401732:	89 44 24 08          	mov    %eax,0x8(%rsp)
  401736:	8b 44 24 10          	mov    0x10(%rsp),%eax
  40173a:	69 c0 fc 95 00 00    	imul   $0x95fc,%eax,%eax
  401740:	89 44 24 10          	mov    %eax,0x10(%rsp)
  401744:	8b 44 24 14          	mov    0x14(%rsp),%eax
  401748:	69 c0 ee b6 00 00    	imul   $0xb6ee,%eax,%eax
  40174e:	89 44 24 14          	mov    %eax,0x14(%rsp)
  401752:	8b 04 24             	mov    (%rsp),%eax
  401755:	69 c0 a3 c9 00 00    	imul   $0xc9a3,%eax,%eax
  40175b:	89 04 24             	mov    %eax,(%rsp)
  40175e:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  401762:	69 c0 f0 32 00 00    	imul   $0x32f0,%eax,%eax
  401768:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  40176c:	8b 44 24 10          	mov    0x10(%rsp),%eax
  401770:	69 c0 f6 87 00 00    	imul   $0x87f6,%eax,%eax
  401776:	89 44 24 10          	mov    %eax,0x10(%rsp)
  40177a:	8b 44 24 20          	mov    0x20(%rsp),%eax
  40177e:	69 c0 2d 28 00 00    	imul   $0x282d,%eax,%eax
  401784:	89 44 24 20          	mov    %eax,0x20(%rsp)
  401788:	8b 44 24 14          	mov    0x14(%rsp),%eax
  40178c:	69 c0 9a 6f 00 00    	imul   $0x6f9a,%eax,%eax
  401792:	89 44 24 14          	mov    %eax,0x14(%rsp)
  401796:	8b 44 24 10          	mov    0x10(%rsp),%eax
  40179a:	69 c0 6b 8e 00 00    	imul   $0x8e6b,%eax,%eax
  4017a0:	89 44 24 10          	mov    %eax,0x10(%rsp)
  4017a4:	8b 44 24 08          	mov    0x8(%rsp),%eax
  4017a8:	69 c0 81 b4 00 00    	imul   $0xb481,%eax,%eax
  4017ae:	89 44 24 08          	mov    %eax,0x8(%rsp)
  4017b2:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  4017b6:	69 c0 ee b0 00 00    	imul   $0xb0ee,%eax,%eax
  4017bc:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  4017c0:	8b 44 24 14          	mov    0x14(%rsp),%eax
  4017c4:	69 c0 b6 d4 00 00    	imul   $0xd4b6,%eax,%eax
  4017ca:	89 44 24 14          	mov    %eax,0x14(%rsp)
  4017ce:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  4017d2:	69 c0 f2 31 00 00    	imul   $0x31f2,%eax,%eax
  4017d8:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  4017dc:	8b 04 24             	mov    (%rsp),%eax
  4017df:	69 c0 4c 52 00 00    	imul   $0x524c,%eax,%eax
  4017e5:	89 04 24             	mov    %eax,(%rsp)
  4017e8:	8b 44 24 10          	mov    0x10(%rsp),%eax
  4017ec:	69 c0 10 cb 00 00    	imul   $0xcb10,%eax,%eax
  4017f2:	89 44 24 10          	mov    %eax,0x10(%rsp)
  4017f6:	8b 04 24             	mov    (%rsp),%eax
  4017f9:	69 c0 d2 d4 00 00    	imul   $0xd4d2,%eax,%eax
  4017ff:	89 04 24             	mov    %eax,(%rsp)
  401802:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  401806:	69 c0 c8 e8 00 00    	imul   $0xe8c8,%eax,%eax
  40180c:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  401810:	8b 04 24             	mov    (%rsp),%eax
  401813:	69 c0 aa 87 00 00    	imul   $0x87aa,%eax,%eax
  401819:	89 04 24             	mov    %eax,(%rsp)
  40181c:	8b 44 24 10          	mov    0x10(%rsp),%eax
  401820:	69 c0 ca 4a 00 00    	imul   $0x4aca,%eax,%eax
  401826:	89 44 24 10          	mov    %eax,0x10(%rsp)
  40182a:	8b 44 24 18          	mov    0x18(%rsp),%eax
  40182e:	69 c0 02 b1 00 00    	imul   $0xb102,%eax,%eax
  401834:	89 44 24 18          	mov    %eax,0x18(%rsp)
  401838:	8b 44 24 18          	mov    0x18(%rsp),%eax
  40183c:	69 c0 cf 51 00 00    	imul   $0x51cf,%eax,%eax
  401842:	89 44 24 18          	mov    %eax,0x18(%rsp)
  401846:	8b 44 24 08          	mov    0x8(%rsp),%eax
  40184a:	69 c0 5e d3 00 00    	imul   $0xd35e,%eax,%eax
  401850:	89 44 24 08          	mov    %eax,0x8(%rsp)
  401854:	8b 44 24 24          	mov    0x24(%rsp),%eax
  401858:	69 c0 09 fa 00 00    	imul   $0xfa09,%eax,%eax
  40185e:	89 44 24 24          	mov    %eax,0x24(%rsp)
  401862:	8b 04 24             	mov    (%rsp),%eax
  401865:	69 c0 58 4e 00 00    	imul   $0x4e58,%eax,%eax
  40186b:	89 04 24             	mov    %eax,(%rsp)
  40186e:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  401872:	69 c0 0d 12 00 00    	imul   $0x120d,%eax,%eax
  401878:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  40187c:	8b 44 24 08          	mov    0x8(%rsp),%eax
  401880:	69 c0 76 ef 00 00    	imul   $0xef76,%eax,%eax
  401886:	89 44 24 08          	mov    %eax,0x8(%rsp)
  40188a:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  40188e:	69 c0 a8 ab 00 00    	imul   $0xaba8,%eax,%eax
  401894:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  401898:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  40189c:	69 c0 35 d9 00 00    	imul   $0xd935,%eax,%eax
  4018a2:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  4018a6:	8b 44 24 20          	mov    0x20(%rsp),%eax
  4018aa:	69 c0 e8 c5 00 00    	imul   $0xc5e8,%eax,%eax
  4018b0:	89 44 24 20          	mov    %eax,0x20(%rsp)
  4018b4:	8b 44 24 24          	mov    0x24(%rsp),%eax
  4018b8:	69 c0 39 a1 00 00    	imul   $0xa139,%eax,%eax
  4018be:	89 44 24 24          	mov    %eax,0x24(%rsp)
  4018c2:	8b 04 24             	mov    (%rsp),%eax
  4018c5:	69 c0 a4 5d 00 00    	imul   $0x5da4,%eax,%eax
  4018cb:	89 04 24             	mov    %eax,(%rsp)
  4018ce:	8b 04 24             	mov    (%rsp),%eax
  4018d1:	69 c0 33 e6 00 00    	imul   $0xe633,%eax,%eax
  4018d7:	89 04 24             	mov    %eax,(%rsp)
  4018da:	8b 44 24 18          	mov    0x18(%rsp),%eax
  4018de:	69 c0 db e0 00 00    	imul   $0xe0db,%eax,%eax
  4018e4:	89 44 24 18          	mov    %eax,0x18(%rsp)
  4018e8:	8b 44 24 04          	mov    0x4(%rsp),%eax
  4018ec:	69 c0 22 e6 00 00    	imul   $0xe622,%eax,%eax
  4018f2:	89 44 24 04          	mov    %eax,0x4(%rsp)
  4018f6:	8b 44 24 08          	mov    0x8(%rsp),%eax
  4018fa:	69 c0 2c bf 00 00    	imul   $0xbf2c,%eax,%eax
  401900:	89 44 24 08          	mov    %eax,0x8(%rsp)
  401904:	ba 00 00 00 00       	mov    $0x0,%edx
  401909:	b8 00 00 00 00       	mov    $0x0,%eax
  40190e:	eb 0a                	jmp    40191a <scramble+0x58b>
  401910:	89 d1                	mov    %edx,%ecx
  401912:	8b 0c 8c             	mov    (%rsp,%rcx,4),%ecx
  401915:	01 c8                	add    %ecx,%eax
  401917:	83 c2 01             	add    $0x1,%edx
  40191a:	83 fa 09             	cmp    $0x9,%edx
  40191d:	76 f1                	jbe    401910 <scramble+0x581>
  40191f:	48 8b 74 24 28       	mov    0x28(%rsp),%rsi
  401924:	64 48 33 34 25 28 00 	xor    %fs:0x28,%rsi
  40192b:	00 00 
  40192d:	74 05                	je     401934 <scramble+0x5a5>
  40192f:	e8 bc f3 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  401934:	48 83 c4 38          	add    $0x38,%rsp
  401938:	c3                   	retq   

0000000000401939 <getbuf>:
  401939:	48 83 ec 18          	sub    $0x18,%rsp
  40193d:	48 89 e7             	mov    %rsp,%rdi
  401940:	e8 96 02 00 00       	callq  401bdb <Gets>
  401945:	b8 01 00 00 00       	mov    $0x1,%eax
  40194a:	48 83 c4 18          	add    $0x18,%rsp
  40194e:	c3                   	retq   

000000000040194f <touch1>:
  40194f:	48 83 ec 08          	sub    $0x8,%rsp
  401953:	48 c1 ec 04          	shr    $0x4,%rsp
  401957:	48 c1 e4 04          	shl    $0x4,%rsp
  40195b:	c7 05 b7 3b 20 00 01 	movl   $0x1,0x203bb7(%rip)        # 60551c <vlevel>
  401962:	00 00 00 
  401965:	bf b0 32 40 00       	mov    $0x4032b0,%edi
  40196a:	e8 61 f3 ff ff       	callq  400cd0 <puts@plt>
  40196f:	bf 01 00 00 00       	mov    $0x1,%edi
  401974:	e8 a7 04 00 00       	callq  401e20 <validate>
  401979:	bf 00 00 00 00       	mov    $0x0,%edi
  40197e:	e8 cd f4 ff ff       	callq  400e50 <exit@plt>

0000000000401983 <touch2>:
  401983:	48 83 ec 08          	sub    $0x8,%rsp
  401987:	89 fa                	mov    %edi,%edx
  401989:	48 c1 ec 04          	shr    $0x4,%rsp
  40198d:	48 c1 e4 04          	shl    $0x4,%rsp
  401991:	c7 05 81 3b 20 00 02 	movl   $0x2,0x203b81(%rip)        # 60551c <vlevel>
  401998:	00 00 00 
  40199b:	39 3d 83 3b 20 00    	cmp    %edi,0x203b83(%rip)        # 605524 <cookie>
  4019a1:	75 20                	jne    4019c3 <touch2+0x40>
  4019a3:	be d8 32 40 00       	mov    $0x4032d8,%esi
  4019a8:	bf 01 00 00 00       	mov    $0x1,%edi
  4019ad:	b8 00 00 00 00       	mov    $0x0,%eax
  4019b2:	e8 49 f4 ff ff       	callq  400e00 <__printf_chk@plt>
  4019b7:	bf 02 00 00 00       	mov    $0x2,%edi
  4019bc:	e8 5f 04 00 00       	callq  401e20 <validate>
  4019c1:	eb 1e                	jmp    4019e1 <touch2+0x5e>
  4019c3:	be 00 33 40 00       	mov    $0x403300,%esi
  4019c8:	bf 01 00 00 00       	mov    $0x1,%edi
  4019cd:	b8 00 00 00 00       	mov    $0x0,%eax
  4019d2:	e8 29 f4 ff ff       	callq  400e00 <__printf_chk@plt>
  4019d7:	bf 02 00 00 00       	mov    $0x2,%edi
  4019dc:	e8 01 05 00 00       	callq  401ee2 <fail>
  4019e1:	bf 00 00 00 00       	mov    $0x0,%edi
  4019e6:	e8 65 f4 ff ff       	callq  400e50 <exit@plt>

00000000004019eb <hexmatch>:
  4019eb:	41 54                	push   %r12
  4019ed:	55                   	push   %rbp
  4019ee:	53                   	push   %rbx
  4019ef:	48 83 c4 80          	add    $0xffffffffffffff80,%rsp
  4019f3:	89 fd                	mov    %edi,%ebp
  4019f5:	48 89 f3             	mov    %rsi,%rbx
  4019f8:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4019ff:	00 00 
  401a01:	48 89 44 24 78       	mov    %rax,0x78(%rsp)
  401a06:	31 c0                	xor    %eax,%eax
  401a08:	e8 b3 f3 ff ff       	callq  400dc0 <random@plt>
  401a0d:	48 89 c1             	mov    %rax,%rcx
  401a10:	48 ba 0b d7 a3 70 3d 	movabs $0xa3d70a3d70a3d70b,%rdx
  401a17:	0a d7 a3 
  401a1a:	48 f7 ea             	imul   %rdx
  401a1d:	48 01 ca             	add    %rcx,%rdx
  401a20:	48 c1 fa 06          	sar    $0x6,%rdx
  401a24:	48 89 c8             	mov    %rcx,%rax
  401a27:	48 c1 f8 3f          	sar    $0x3f,%rax
  401a2b:	48 29 c2             	sub    %rax,%rdx
  401a2e:	48 8d 04 92          	lea    (%rdx,%rdx,4),%rax
  401a32:	48 8d 14 80          	lea    (%rax,%rax,4),%rdx
  401a36:	48 8d 04 95 00 00 00 	lea    0x0(,%rdx,4),%rax
  401a3d:	00 
  401a3e:	48 29 c1             	sub    %rax,%rcx
  401a41:	4c 8d 24 0c          	lea    (%rsp,%rcx,1),%r12
  401a45:	41 89 e8             	mov    %ebp,%r8d
  401a48:	b9 cd 32 40 00       	mov    $0x4032cd,%ecx
  401a4d:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  401a54:	be 01 00 00 00       	mov    $0x1,%esi
  401a59:	4c 89 e7             	mov    %r12,%rdi
  401a5c:	b8 00 00 00 00       	mov    $0x0,%eax
  401a61:	e8 1a f4 ff ff       	callq  400e80 <__sprintf_chk@plt>
  401a66:	ba 09 00 00 00       	mov    $0x9,%edx
  401a6b:	4c 89 e6             	mov    %r12,%rsi
  401a6e:	48 89 df             	mov    %rbx,%rdi
  401a71:	e8 3a f2 ff ff       	callq  400cb0 <strncmp@plt>
  401a76:	85 c0                	test   %eax,%eax
  401a78:	0f 94 c0             	sete   %al
  401a7b:	48 8b 5c 24 78       	mov    0x78(%rsp),%rbx
  401a80:	64 48 33 1c 25 28 00 	xor    %fs:0x28,%rbx
  401a87:	00 00 
  401a89:	74 05                	je     401a90 <hexmatch+0xa5>
  401a8b:	e8 60 f2 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  401a90:	0f b6 c0             	movzbl %al,%eax
  401a93:	48 83 ec 80          	sub    $0xffffffffffffff80,%rsp
  401a97:	5b                   	pop    %rbx
  401a98:	5d                   	pop    %rbp
  401a99:	41 5c                	pop    %r12
  401a9b:	c3                   	retq   

0000000000401a9c <touch3>:
  401a9c:	53                   	push   %rbx
  401a9d:	48 89 fb             	mov    %rdi,%rbx
  401aa0:	48 c1 ec 04          	shr    $0x4,%rsp
  401aa4:	48 c1 e4 04          	shl    $0x4,%rsp
  401aa8:	c7 05 6a 3a 20 00 03 	movl   $0x3,0x203a6a(%rip)        # 60551c <vlevel>
  401aaf:	00 00 00 
  401ab2:	48 89 fe             	mov    %rdi,%rsi
  401ab5:	8b 3d 69 3a 20 00    	mov    0x203a69(%rip),%edi        # 605524 <cookie>
  401abb:	e8 2b ff ff ff       	callq  4019eb <hexmatch>
  401ac0:	85 c0                	test   %eax,%eax
  401ac2:	74 23                	je     401ae7 <touch3+0x4b>
  401ac4:	48 89 da             	mov    %rbx,%rdx
  401ac7:	be 28 33 40 00       	mov    $0x403328,%esi
  401acc:	bf 01 00 00 00       	mov    $0x1,%edi
  401ad1:	b8 00 00 00 00       	mov    $0x0,%eax
  401ad6:	e8 25 f3 ff ff       	callq  400e00 <__printf_chk@plt>
  401adb:	bf 03 00 00 00       	mov    $0x3,%edi
  401ae0:	e8 3b 03 00 00       	callq  401e20 <validate>
  401ae5:	eb 21                	jmp    401b08 <touch3+0x6c>
  401ae7:	48 89 da             	mov    %rbx,%rdx
  401aea:	be 50 33 40 00       	mov    $0x403350,%esi
  401aef:	bf 01 00 00 00       	mov    $0x1,%edi
  401af4:	b8 00 00 00 00       	mov    $0x0,%eax
  401af9:	e8 02 f3 ff ff       	callq  400e00 <__printf_chk@plt>
  401afe:	bf 03 00 00 00       	mov    $0x3,%edi
  401b03:	e8 da 03 00 00       	callq  401ee2 <fail>
  401b08:	bf 00 00 00 00       	mov    $0x0,%edi
  401b0d:	e8 3e f3 ff ff       	callq  400e50 <exit@plt>

0000000000401b12 <test>:
  401b12:	48 83 ec 08          	sub    $0x8,%rsp
  401b16:	b8 00 00 00 00       	mov    $0x0,%eax
  401b1b:	e8 19 fe ff ff       	callq  401939 <getbuf>
  401b20:	89 c2                	mov    %eax,%edx
  401b22:	be 78 33 40 00       	mov    $0x403378,%esi
  401b27:	bf 01 00 00 00       	mov    $0x1,%edi
  401b2c:	b8 00 00 00 00       	mov    $0x0,%eax
  401b31:	e8 ca f2 ff ff       	callq  400e00 <__printf_chk@plt>
  401b36:	48 83 c4 08          	add    $0x8,%rsp
  401b3a:	c3                   	retq   

0000000000401b3b <save_char>:
  401b3b:	8b 05 03 46 20 00    	mov    0x204603(%rip),%eax        # 606144 <gets_cnt>
  401b41:	3d ff 03 00 00       	cmp    $0x3ff,%eax
  401b46:	7f 49                	jg     401b91 <save_char+0x56>
  401b48:	8d 14 40             	lea    (%rax,%rax,2),%edx
  401b4b:	89 f9                	mov    %edi,%ecx
  401b4d:	c0 e9 04             	shr    $0x4,%cl
  401b50:	83 e1 0f             	and    $0xf,%ecx
  401b53:	0f b6 b1 a0 36 40 00 	movzbl 0x4036a0(%rcx),%esi
  401b5a:	48 63 ca             	movslq %edx,%rcx
  401b5d:	40 88 b1 40 55 60 00 	mov    %sil,0x605540(%rcx)
  401b64:	8d 4a 01             	lea    0x1(%rdx),%ecx
  401b67:	83 e7 0f             	and    $0xf,%edi
  401b6a:	0f b6 b7 a0 36 40 00 	movzbl 0x4036a0(%rdi),%esi
  401b71:	48 63 c9             	movslq %ecx,%rcx
  401b74:	40 88 b1 40 55 60 00 	mov    %sil,0x605540(%rcx)
  401b7b:	83 c2 02             	add    $0x2,%edx
  401b7e:	48 63 d2             	movslq %edx,%rdx
  401b81:	c6 82 40 55 60 00 20 	movb   $0x20,0x605540(%rdx)
  401b88:	83 c0 01             	add    $0x1,%eax
  401b8b:	89 05 b3 45 20 00    	mov    %eax,0x2045b3(%rip)        # 606144 <gets_cnt>
  401b91:	f3 c3                	repz retq 

0000000000401b93 <save_term>:
  401b93:	8b 05 ab 45 20 00    	mov    0x2045ab(%rip),%eax        # 606144 <gets_cnt>
  401b99:	8d 04 40             	lea    (%rax,%rax,2),%eax
  401b9c:	48 98                	cltq   
  401b9e:	c6 80 40 55 60 00 00 	movb   $0x0,0x605540(%rax)
  401ba5:	c3                   	retq   

0000000000401ba6 <check_fail>:
  401ba6:	48 83 ec 08          	sub    $0x8,%rsp
  401baa:	0f be 15 97 45 20 00 	movsbl 0x204597(%rip),%edx        # 606148 <target_prefix>
  401bb1:	41 b8 40 55 60 00    	mov    $0x605540,%r8d
  401bb7:	8b 0d 5b 39 20 00    	mov    0x20395b(%rip),%ecx        # 605518 <check_level>
  401bbd:	be 9b 33 40 00       	mov    $0x40339b,%esi
  401bc2:	bf 01 00 00 00       	mov    $0x1,%edi
  401bc7:	b8 00 00 00 00       	mov    $0x0,%eax
  401bcc:	e8 2f f2 ff ff       	callq  400e00 <__printf_chk@plt>
  401bd1:	bf 01 00 00 00       	mov    $0x1,%edi
  401bd6:	e8 75 f2 ff ff       	callq  400e50 <exit@plt>

0000000000401bdb <Gets>:
  401bdb:	41 54                	push   %r12
  401bdd:	55                   	push   %rbp
  401bde:	53                   	push   %rbx
  401bdf:	49 89 fc             	mov    %rdi,%r12
  401be2:	c7 05 58 45 20 00 00 	movl   $0x0,0x204558(%rip)        # 606144 <gets_cnt>
  401be9:	00 00 00 
  401bec:	48 89 fb             	mov    %rdi,%rbx
  401bef:	eb 11                	jmp    401c02 <Gets+0x27>
  401bf1:	48 8d 6b 01          	lea    0x1(%rbx),%rbp
  401bf5:	88 03                	mov    %al,(%rbx)
  401bf7:	0f b6 f8             	movzbl %al,%edi
  401bfa:	e8 3c ff ff ff       	callq  401b3b <save_char>
  401bff:	48 89 eb             	mov    %rbp,%rbx
  401c02:	48 8b 3d 07 39 20 00 	mov    0x203907(%rip),%rdi        # 605510 <infile>
  401c09:	e8 c2 f1 ff ff       	callq  400dd0 <_IO_getc@plt>
  401c0e:	83 f8 ff             	cmp    $0xffffffff,%eax
  401c11:	74 05                	je     401c18 <Gets+0x3d>
  401c13:	83 f8 0a             	cmp    $0xa,%eax
  401c16:	75 d9                	jne    401bf1 <Gets+0x16>
  401c18:	c6 03 00             	movb   $0x0,(%rbx)
  401c1b:	b8 00 00 00 00       	mov    $0x0,%eax
  401c20:	e8 6e ff ff ff       	callq  401b93 <save_term>
  401c25:	4c 89 e0             	mov    %r12,%rax
  401c28:	5b                   	pop    %rbx
  401c29:	5d                   	pop    %rbp
  401c2a:	41 5c                	pop    %r12
  401c2c:	c3                   	retq   

0000000000401c2d <notify_server>:
  401c2d:	53                   	push   %rbx
  401c2e:	48 81 ec 10 40 00 00 	sub    $0x4010,%rsp
  401c35:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401c3c:	00 00 
  401c3e:	48 89 84 24 08 40 00 	mov    %rax,0x4008(%rsp)
  401c45:	00 
  401c46:	31 c0                	xor    %eax,%eax
  401c48:	83 3d d9 38 20 00 00 	cmpl   $0x0,0x2038d9(%rip)        # 605528 <is_checker>
  401c4f:	0f 85 aa 01 00 00    	jne    401dff <notify_server+0x1d2>
  401c55:	89 fb                	mov    %edi,%ebx
  401c57:	8b 05 e7 44 20 00    	mov    0x2044e7(%rip),%eax        # 606144 <gets_cnt>
  401c5d:	83 c0 64             	add    $0x64,%eax
  401c60:	3d 00 20 00 00       	cmp    $0x2000,%eax
  401c65:	7e 1e                	jle    401c85 <notify_server+0x58>
  401c67:	be d0 34 40 00       	mov    $0x4034d0,%esi
  401c6c:	bf 01 00 00 00       	mov    $0x1,%edi
  401c71:	b8 00 00 00 00       	mov    $0x0,%eax
  401c76:	e8 85 f1 ff ff       	callq  400e00 <__printf_chk@plt>
  401c7b:	bf 01 00 00 00       	mov    $0x1,%edi
  401c80:	e8 cb f1 ff ff       	callq  400e50 <exit@plt>
  401c85:	0f be 05 bc 44 20 00 	movsbl 0x2044bc(%rip),%eax        # 606148 <target_prefix>
  401c8c:	83 3d 15 38 20 00 00 	cmpl   $0x0,0x203815(%rip)        # 6054a8 <notify>
  401c93:	74 08                	je     401c9d <notify_server+0x70>
  401c95:	8b 15 85 38 20 00    	mov    0x203885(%rip),%edx        # 605520 <authkey>
  401c9b:	eb 05                	jmp    401ca2 <notify_server+0x75>
  401c9d:	ba ff ff ff ff       	mov    $0xffffffff,%edx
  401ca2:	85 db                	test   %ebx,%ebx
  401ca4:	74 08                	je     401cae <notify_server+0x81>
  401ca6:	41 b9 b1 33 40 00    	mov    $0x4033b1,%r9d
  401cac:	eb 06                	jmp    401cb4 <notify_server+0x87>
  401cae:	41 b9 b6 33 40 00    	mov    $0x4033b6,%r9d
  401cb4:	68 40 55 60 00       	pushq  $0x605540
  401cb9:	56                   	push   %rsi
  401cba:	50                   	push   %rax
  401cbb:	52                   	push   %rdx
  401cbc:	44 8b 05 a5 34 20 00 	mov    0x2034a5(%rip),%r8d        # 605168 <target_id>
  401cc3:	b9 bb 33 40 00       	mov    $0x4033bb,%ecx
  401cc8:	ba 00 20 00 00       	mov    $0x2000,%edx
  401ccd:	be 01 00 00 00       	mov    $0x1,%esi
  401cd2:	48 8d 7c 24 20       	lea    0x20(%rsp),%rdi
  401cd7:	b8 00 00 00 00       	mov    $0x0,%eax
  401cdc:	e8 9f f1 ff ff       	callq  400e80 <__sprintf_chk@plt>
  401ce1:	48 83 c4 20          	add    $0x20,%rsp
  401ce5:	83 3d bc 37 20 00 00 	cmpl   $0x0,0x2037bc(%rip)        # 6054a8 <notify>
  401cec:	0f 84 81 00 00 00    	je     401d73 <notify_server+0x146>
  401cf2:	85 db                	test   %ebx,%ebx
  401cf4:	74 6e                	je     401d64 <notify_server+0x137>
  401cf6:	4c 8d 8c 24 00 20 00 	lea    0x2000(%rsp),%r9
  401cfd:	00 
  401cfe:	41 b8 00 00 00 00    	mov    $0x0,%r8d
  401d04:	48 89 e1             	mov    %rsp,%rcx
  401d07:	48 8b 15 62 34 20 00 	mov    0x203462(%rip),%rdx        # 605170 <lab>
  401d0e:	48 8b 35 63 34 20 00 	mov    0x203463(%rip),%rsi        # 605178 <course>
  401d15:	48 8b 3d 44 34 20 00 	mov    0x203444(%rip),%rdi        # 605160 <user_id>
  401d1c:	e8 ef 10 00 00       	callq  402e10 <driver_post>
  401d21:	85 c0                	test   %eax,%eax
  401d23:	79 26                	jns    401d4b <notify_server+0x11e>
  401d25:	48 8d 94 24 00 20 00 	lea    0x2000(%rsp),%rdx
  401d2c:	00 
  401d2d:	be d7 33 40 00       	mov    $0x4033d7,%esi
  401d32:	bf 01 00 00 00       	mov    $0x1,%edi
  401d37:	b8 00 00 00 00       	mov    $0x0,%eax
  401d3c:	e8 bf f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401d41:	bf 01 00 00 00       	mov    $0x1,%edi
  401d46:	e8 05 f1 ff ff       	callq  400e50 <exit@plt>
  401d4b:	bf 00 35 40 00       	mov    $0x403500,%edi
  401d50:	e8 7b ef ff ff       	callq  400cd0 <puts@plt>
  401d55:	bf e3 33 40 00       	mov    $0x4033e3,%edi
  401d5a:	e8 71 ef ff ff       	callq  400cd0 <puts@plt>
  401d5f:	e9 9b 00 00 00       	jmpq   401dff <notify_server+0x1d2>
  401d64:	bf ed 33 40 00       	mov    $0x4033ed,%edi
  401d69:	e8 62 ef ff ff       	callq  400cd0 <puts@plt>
  401d6e:	e9 8c 00 00 00       	jmpq   401dff <notify_server+0x1d2>
  401d73:	85 db                	test   %ebx,%ebx
  401d75:	74 07                	je     401d7e <notify_server+0x151>
  401d77:	ba b1 33 40 00       	mov    $0x4033b1,%edx
  401d7c:	eb 05                	jmp    401d83 <notify_server+0x156>
  401d7e:	ba b6 33 40 00       	mov    $0x4033b6,%edx
  401d83:	be 38 35 40 00       	mov    $0x403538,%esi
  401d88:	bf 01 00 00 00       	mov    $0x1,%edi
  401d8d:	b8 00 00 00 00       	mov    $0x0,%eax
  401d92:	e8 69 f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401d97:	48 8b 15 c2 33 20 00 	mov    0x2033c2(%rip),%rdx        # 605160 <user_id>
  401d9e:	be f4 33 40 00       	mov    $0x4033f4,%esi
  401da3:	bf 01 00 00 00       	mov    $0x1,%edi
  401da8:	b8 00 00 00 00       	mov    $0x0,%eax
  401dad:	e8 4e f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401db2:	48 8b 15 bf 33 20 00 	mov    0x2033bf(%rip),%rdx        # 605178 <course>
  401db9:	be 01 34 40 00       	mov    $0x403401,%esi
  401dbe:	bf 01 00 00 00       	mov    $0x1,%edi
  401dc3:	b8 00 00 00 00       	mov    $0x0,%eax
  401dc8:	e8 33 f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401dcd:	48 8b 15 9c 33 20 00 	mov    0x20339c(%rip),%rdx        # 605170 <lab>
  401dd4:	be 0d 34 40 00       	mov    $0x40340d,%esi
  401dd9:	bf 01 00 00 00       	mov    $0x1,%edi
  401dde:	b8 00 00 00 00       	mov    $0x0,%eax
  401de3:	e8 18 f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401de8:	48 89 e2             	mov    %rsp,%rdx
  401deb:	be 16 34 40 00       	mov    $0x403416,%esi
  401df0:	bf 01 00 00 00       	mov    $0x1,%edi
  401df5:	b8 00 00 00 00       	mov    $0x0,%eax
  401dfa:	e8 01 f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401dff:	48 8b 84 24 08 40 00 	mov    0x4008(%rsp),%rax
  401e06:	00 
  401e07:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401e0e:	00 00 
  401e10:	74 05                	je     401e17 <notify_server+0x1ea>
  401e12:	e8 d9 ee ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  401e17:	48 81 c4 10 40 00 00 	add    $0x4010,%rsp
  401e1e:	5b                   	pop    %rbx
  401e1f:	c3                   	retq   

0000000000401e20 <validate>:
  401e20:	53                   	push   %rbx
  401e21:	89 fb                	mov    %edi,%ebx
  401e23:	83 3d fe 36 20 00 00 	cmpl   $0x0,0x2036fe(%rip)        # 605528 <is_checker>
  401e2a:	74 6b                	je     401e97 <validate+0x77>
  401e2c:	39 3d ea 36 20 00    	cmp    %edi,0x2036ea(%rip)        # 60551c <vlevel>
  401e32:	74 14                	je     401e48 <validate+0x28>
  401e34:	bf 22 34 40 00       	mov    $0x403422,%edi
  401e39:	e8 92 ee ff ff       	callq  400cd0 <puts@plt>
  401e3e:	b8 00 00 00 00       	mov    $0x0,%eax
  401e43:	e8 5e fd ff ff       	callq  401ba6 <check_fail>
  401e48:	8b 15 ca 36 20 00    	mov    0x2036ca(%rip),%edx        # 605518 <check_level>
  401e4e:	39 d7                	cmp    %edx,%edi
  401e50:	74 20                	je     401e72 <validate+0x52>
  401e52:	89 f9                	mov    %edi,%ecx
  401e54:	be 60 35 40 00       	mov    $0x403560,%esi
  401e59:	bf 01 00 00 00       	mov    $0x1,%edi
  401e5e:	b8 00 00 00 00       	mov    $0x0,%eax
  401e63:	e8 98 ef ff ff       	callq  400e00 <__printf_chk@plt>
  401e68:	b8 00 00 00 00       	mov    $0x0,%eax
  401e6d:	e8 34 fd ff ff       	callq  401ba6 <check_fail>
  401e72:	0f be 15 cf 42 20 00 	movsbl 0x2042cf(%rip),%edx        # 606148 <target_prefix>
  401e79:	41 b8 40 55 60 00    	mov    $0x605540,%r8d
  401e7f:	89 f9                	mov    %edi,%ecx
  401e81:	be 40 34 40 00       	mov    $0x403440,%esi
  401e86:	bf 01 00 00 00       	mov    $0x1,%edi
  401e8b:	b8 00 00 00 00       	mov    $0x0,%eax
  401e90:	e8 6b ef ff ff       	callq  400e00 <__printf_chk@plt>
  401e95:	eb 49                	jmp    401ee0 <validate+0xc0>
  401e97:	3b 3d 7f 36 20 00    	cmp    0x20367f(%rip),%edi        # 60551c <vlevel>
  401e9d:	74 18                	je     401eb7 <validate+0x97>
  401e9f:	bf 22 34 40 00       	mov    $0x403422,%edi
  401ea4:	e8 27 ee ff ff       	callq  400cd0 <puts@plt>
  401ea9:	89 de                	mov    %ebx,%esi
  401eab:	bf 00 00 00 00       	mov    $0x0,%edi
  401eb0:	e8 78 fd ff ff       	callq  401c2d <notify_server>
  401eb5:	eb 29                	jmp    401ee0 <validate+0xc0>
  401eb7:	0f be 0d 8a 42 20 00 	movsbl 0x20428a(%rip),%ecx        # 606148 <target_prefix>
  401ebe:	89 fa                	mov    %edi,%edx
  401ec0:	be 88 35 40 00       	mov    $0x403588,%esi
  401ec5:	bf 01 00 00 00       	mov    $0x1,%edi
  401eca:	b8 00 00 00 00       	mov    $0x0,%eax
  401ecf:	e8 2c ef ff ff       	callq  400e00 <__printf_chk@plt>
  401ed4:	89 de                	mov    %ebx,%esi
  401ed6:	bf 01 00 00 00       	mov    $0x1,%edi
  401edb:	e8 4d fd ff ff       	callq  401c2d <notify_server>
  401ee0:	5b                   	pop    %rbx
  401ee1:	c3                   	retq   

0000000000401ee2 <fail>:
  401ee2:	48 83 ec 08          	sub    $0x8,%rsp
  401ee6:	83 3d 3b 36 20 00 00 	cmpl   $0x0,0x20363b(%rip)        # 605528 <is_checker>
  401eed:	74 0a                	je     401ef9 <fail+0x17>
  401eef:	b8 00 00 00 00       	mov    $0x0,%eax
  401ef4:	e8 ad fc ff ff       	callq  401ba6 <check_fail>
  401ef9:	89 fe                	mov    %edi,%esi
  401efb:	bf 00 00 00 00       	mov    $0x0,%edi
  401f00:	e8 28 fd ff ff       	callq  401c2d <notify_server>
  401f05:	48 83 c4 08          	add    $0x8,%rsp
  401f09:	c3                   	retq   

0000000000401f0a <bushandler>:
  401f0a:	48 83 ec 08          	sub    $0x8,%rsp
  401f0e:	83 3d 13 36 20 00 00 	cmpl   $0x0,0x203613(%rip)        # 605528 <is_checker>
  401f15:	74 14                	je     401f2b <bushandler+0x21>
  401f17:	bf 55 34 40 00       	mov    $0x403455,%edi
  401f1c:	e8 af ed ff ff       	callq  400cd0 <puts@plt>
  401f21:	b8 00 00 00 00       	mov    $0x0,%eax
  401f26:	e8 7b fc ff ff       	callq  401ba6 <check_fail>
  401f2b:	bf c0 35 40 00       	mov    $0x4035c0,%edi
  401f30:	e8 9b ed ff ff       	callq  400cd0 <puts@plt>
  401f35:	bf 5f 34 40 00       	mov    $0x40345f,%edi
  401f3a:	e8 91 ed ff ff       	callq  400cd0 <puts@plt>
  401f3f:	be 00 00 00 00       	mov    $0x0,%esi
  401f44:	bf 00 00 00 00       	mov    $0x0,%edi
  401f49:	e8 df fc ff ff       	callq  401c2d <notify_server>
  401f4e:	bf 01 00 00 00       	mov    $0x1,%edi
  401f53:	e8 f8 ee ff ff       	callq  400e50 <exit@plt>

0000000000401f58 <seghandler>:
  401f58:	48 83 ec 08          	sub    $0x8,%rsp
  401f5c:	83 3d c5 35 20 00 00 	cmpl   $0x0,0x2035c5(%rip)        # 605528 <is_checker>
  401f63:	74 14                	je     401f79 <seghandler+0x21>
  401f65:	bf 75 34 40 00       	mov    $0x403475,%edi
  401f6a:	e8 61 ed ff ff       	callq  400cd0 <puts@plt>
  401f6f:	b8 00 00 00 00       	mov    $0x0,%eax
  401f74:	e8 2d fc ff ff       	callq  401ba6 <check_fail>
  401f79:	bf e0 35 40 00       	mov    $0x4035e0,%edi
  401f7e:	e8 4d ed ff ff       	callq  400cd0 <puts@plt>
  401f83:	bf 5f 34 40 00       	mov    $0x40345f,%edi
  401f88:	e8 43 ed ff ff       	callq  400cd0 <puts@plt>
  401f8d:	be 00 00 00 00       	mov    $0x0,%esi
  401f92:	bf 00 00 00 00       	mov    $0x0,%edi
  401f97:	e8 91 fc ff ff       	callq  401c2d <notify_server>
  401f9c:	bf 01 00 00 00       	mov    $0x1,%edi
  401fa1:	e8 aa ee ff ff       	callq  400e50 <exit@plt>

0000000000401fa6 <illegalhandler>:
  401fa6:	48 83 ec 08          	sub    $0x8,%rsp
  401faa:	83 3d 77 35 20 00 00 	cmpl   $0x0,0x203577(%rip)        # 605528 <is_checker>
  401fb1:	74 14                	je     401fc7 <illegalhandler+0x21>
  401fb3:	bf 88 34 40 00       	mov    $0x403488,%edi
  401fb8:	e8 13 ed ff ff       	callq  400cd0 <puts@plt>
  401fbd:	b8 00 00 00 00       	mov    $0x0,%eax
  401fc2:	e8 df fb ff ff       	callq  401ba6 <check_fail>
  401fc7:	bf 08 36 40 00       	mov    $0x403608,%edi
  401fcc:	e8 ff ec ff ff       	callq  400cd0 <puts@plt>
  401fd1:	bf 5f 34 40 00       	mov    $0x40345f,%edi
  401fd6:	e8 f5 ec ff ff       	callq  400cd0 <puts@plt>
  401fdb:	be 00 00 00 00       	mov    $0x0,%esi
  401fe0:	bf 00 00 00 00       	mov    $0x0,%edi
  401fe5:	e8 43 fc ff ff       	callq  401c2d <notify_server>
  401fea:	bf 01 00 00 00       	mov    $0x1,%edi
  401fef:	e8 5c ee ff ff       	callq  400e50 <exit@plt>

0000000000401ff4 <sigalrmhandler>:
  401ff4:	48 83 ec 08          	sub    $0x8,%rsp
  401ff8:	83 3d 29 35 20 00 00 	cmpl   $0x0,0x203529(%rip)        # 605528 <is_checker>
  401fff:	74 14                	je     402015 <sigalrmhandler+0x21>
  402001:	bf 9c 34 40 00       	mov    $0x40349c,%edi
  402006:	e8 c5 ec ff ff       	callq  400cd0 <puts@plt>
  40200b:	b8 00 00 00 00       	mov    $0x0,%eax
  402010:	e8 91 fb ff ff       	callq  401ba6 <check_fail>
  402015:	ba 05 00 00 00       	mov    $0x5,%edx
  40201a:	be 38 36 40 00       	mov    $0x403638,%esi
  40201f:	bf 01 00 00 00       	mov    $0x1,%edi
  402024:	b8 00 00 00 00       	mov    $0x0,%eax
  402029:	e8 d2 ed ff ff       	callq  400e00 <__printf_chk@plt>
  40202e:	be 00 00 00 00       	mov    $0x0,%esi
  402033:	bf 00 00 00 00       	mov    $0x0,%edi
  402038:	e8 f0 fb ff ff       	callq  401c2d <notify_server>
  40203d:	bf 01 00 00 00       	mov    $0x1,%edi
  402042:	e8 09 ee ff ff       	callq  400e50 <exit@plt>

0000000000402047 <launch>:
  402047:	55                   	push   %rbp
  402048:	48 89 e5             	mov    %rsp,%rbp
  40204b:	48 83 ec 10          	sub    $0x10,%rsp
  40204f:	48 89 fa             	mov    %rdi,%rdx
  402052:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  402059:	00 00 
  40205b:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  40205f:	31 c0                	xor    %eax,%eax
  402061:	48 8d 47 1e          	lea    0x1e(%rdi),%rax
  402065:	48 83 e0 f0          	and    $0xfffffffffffffff0,%rax
  402069:	48 29 c4             	sub    %rax,%rsp
  40206c:	48 8d 7c 24 0f       	lea    0xf(%rsp),%rdi
  402071:	48 83 e7 f0          	and    $0xfffffffffffffff0,%rdi
  402075:	be f4 00 00 00       	mov    $0xf4,%esi
  40207a:	e8 91 ec ff ff       	callq  400d10 <memset@plt>
  40207f:	48 8b 05 3a 34 20 00 	mov    0x20343a(%rip),%rax        # 6054c0 <stdin@@GLIBC_2.2.5>
  402086:	48 39 05 83 34 20 00 	cmp    %rax,0x203483(%rip)        # 605510 <infile>
  40208d:	75 14                	jne    4020a3 <launch+0x5c>
  40208f:	be a4 34 40 00       	mov    $0x4034a4,%esi
  402094:	bf 01 00 00 00       	mov    $0x1,%edi
  402099:	b8 00 00 00 00       	mov    $0x0,%eax
  40209e:	e8 5d ed ff ff       	callq  400e00 <__printf_chk@plt>
  4020a3:	c7 05 6f 34 20 00 00 	movl   $0x0,0x20346f(%rip)        # 60551c <vlevel>
  4020aa:	00 00 00 
  4020ad:	b8 00 00 00 00       	mov    $0x0,%eax
  4020b2:	e8 5b fa ff ff       	callq  401b12 <test>
  4020b7:	83 3d 6a 34 20 00 00 	cmpl   $0x0,0x20346a(%rip)        # 605528 <is_checker>
  4020be:	74 14                	je     4020d4 <launch+0x8d>
  4020c0:	bf b1 34 40 00       	mov    $0x4034b1,%edi
  4020c5:	e8 06 ec ff ff       	callq  400cd0 <puts@plt>
  4020ca:	b8 00 00 00 00       	mov    $0x0,%eax
  4020cf:	e8 d2 fa ff ff       	callq  401ba6 <check_fail>
  4020d4:	bf bc 34 40 00       	mov    $0x4034bc,%edi
  4020d9:	e8 f2 eb ff ff       	callq  400cd0 <puts@plt>
  4020de:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4020e2:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4020e9:	00 00 
  4020eb:	74 05                	je     4020f2 <launch+0xab>
  4020ed:	e8 fe eb ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  4020f2:	c9                   	leaveq 
  4020f3:	c3                   	retq   

00000000004020f4 <stable_launch>:
  4020f4:	53                   	push   %rbx
  4020f5:	48 89 3d 0c 34 20 00 	mov    %rdi,0x20340c(%rip)        # 605508 <global_offset>
  4020fc:	41 b9 00 00 00 00    	mov    $0x0,%r9d
  402102:	41 b8 00 00 00 00    	mov    $0x0,%r8d
  402108:	b9 32 01 00 00       	mov    $0x132,%ecx
  40210d:	ba 07 00 00 00       	mov    $0x7,%edx
  402112:	be 00 00 10 00       	mov    $0x100000,%esi
  402117:	bf 00 60 58 55       	mov    $0x55586000,%edi
  40211c:	e8 df eb ff ff       	callq  400d00 <mmap@plt>
  402121:	48 89 c3             	mov    %rax,%rbx
  402124:	48 3d 00 60 58 55    	cmp    $0x55586000,%rax
  40212a:	74 37                	je     402163 <stable_launch+0x6f>
  40212c:	be 00 00 10 00       	mov    $0x100000,%esi
  402131:	48 89 c7             	mov    %rax,%rdi
  402134:	e8 b7 ec ff ff       	callq  400df0 <munmap@plt>
  402139:	b9 00 60 58 55       	mov    $0x55586000,%ecx
  40213e:	ba 70 36 40 00       	mov    $0x403670,%edx
  402143:	be 01 00 00 00       	mov    $0x1,%esi
  402148:	48 8b 3d 91 33 20 00 	mov    0x203391(%rip),%rdi        # 6054e0 <stderr@@GLIBC_2.2.5>
  40214f:	b8 00 00 00 00       	mov    $0x0,%eax
  402154:	e8 17 ed ff ff       	callq  400e70 <__fprintf_chk@plt>
  402159:	bf 01 00 00 00       	mov    $0x1,%edi
  40215e:	e8 ed ec ff ff       	callq  400e50 <exit@plt>
  402163:	48 8d 90 f8 ff 0f 00 	lea    0xffff8(%rax),%rdx
  40216a:	48 89 15 df 3f 20 00 	mov    %rdx,0x203fdf(%rip)        # 606150 <stack_top>
  402171:	48 89 e0             	mov    %rsp,%rax
  402174:	48 89 d4             	mov    %rdx,%rsp
  402177:	48 89 c2             	mov    %rax,%rdx
  40217a:	48 89 15 7f 33 20 00 	mov    %rdx,0x20337f(%rip)        # 605500 <global_save_stack>
  402181:	48 8b 3d 80 33 20 00 	mov    0x203380(%rip),%rdi        # 605508 <global_offset>
  402188:	e8 ba fe ff ff       	callq  402047 <launch>
  40218d:	48 8b 05 6c 33 20 00 	mov    0x20336c(%rip),%rax        # 605500 <global_save_stack>
  402194:	48 89 c4             	mov    %rax,%rsp
  402197:	be 00 00 10 00       	mov    $0x100000,%esi
  40219c:	48 89 df             	mov    %rbx,%rdi
  40219f:	e8 4c ec ff ff       	callq  400df0 <munmap@plt>
  4021a4:	5b                   	pop    %rbx
  4021a5:	c3                   	retq   

00000000004021a6 <rio_readinitb>:
  4021a6:	89 37                	mov    %esi,(%rdi)
  4021a8:	c7 47 04 00 00 00 00 	movl   $0x0,0x4(%rdi)
  4021af:	48 8d 47 10          	lea    0x10(%rdi),%rax
  4021b3:	48 89 47 08          	mov    %rax,0x8(%rdi)
  4021b7:	c3                   	retq   

00000000004021b8 <sigalrm_handler>:
  4021b8:	48 83 ec 08          	sub    $0x8,%rsp
  4021bc:	b9 00 00 00 00       	mov    $0x0,%ecx
  4021c1:	ba b0 36 40 00       	mov    $0x4036b0,%edx
  4021c6:	be 01 00 00 00       	mov    $0x1,%esi
  4021cb:	48 8b 3d 0e 33 20 00 	mov    0x20330e(%rip),%rdi        # 6054e0 <stderr@@GLIBC_2.2.5>
  4021d2:	b8 00 00 00 00       	mov    $0x0,%eax
  4021d7:	e8 94 ec ff ff       	callq  400e70 <__fprintf_chk@plt>
  4021dc:	bf 01 00 00 00       	mov    $0x1,%edi
  4021e1:	e8 6a ec ff ff       	callq  400e50 <exit@plt>

00000000004021e6 <rio_writen>:
  4021e6:	41 55                	push   %r13
  4021e8:	41 54                	push   %r12
  4021ea:	55                   	push   %rbp
  4021eb:	53                   	push   %rbx
  4021ec:	48 83 ec 08          	sub    $0x8,%rsp
  4021f0:	41 89 fc             	mov    %edi,%r12d
  4021f3:	48 89 f5             	mov    %rsi,%rbp
  4021f6:	49 89 d5             	mov    %rdx,%r13
  4021f9:	48 89 d3             	mov    %rdx,%rbx
  4021fc:	eb 28                	jmp    402226 <rio_writen+0x40>
  4021fe:	48 89 da             	mov    %rbx,%rdx
  402201:	48 89 ee             	mov    %rbp,%rsi
  402204:	44 89 e7             	mov    %r12d,%edi
  402207:	e8 d4 ea ff ff       	callq  400ce0 <write@plt>
  40220c:	48 85 c0             	test   %rax,%rax
  40220f:	7f 0f                	jg     402220 <rio_writen+0x3a>
  402211:	e8 7a ea ff ff       	callq  400c90 <__errno_location@plt>
  402216:	83 38 04             	cmpl   $0x4,(%rax)
  402219:	75 15                	jne    402230 <rio_writen+0x4a>
  40221b:	b8 00 00 00 00       	mov    $0x0,%eax
  402220:	48 29 c3             	sub    %rax,%rbx
  402223:	48 01 c5             	add    %rax,%rbp
  402226:	48 85 db             	test   %rbx,%rbx
  402229:	75 d3                	jne    4021fe <rio_writen+0x18>
  40222b:	4c 89 e8             	mov    %r13,%rax
  40222e:	eb 07                	jmp    402237 <rio_writen+0x51>
  402230:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  402237:	48 83 c4 08          	add    $0x8,%rsp
  40223b:	5b                   	pop    %rbx
  40223c:	5d                   	pop    %rbp
  40223d:	41 5c                	pop    %r12
  40223f:	41 5d                	pop    %r13
  402241:	c3                   	retq   

0000000000402242 <rio_read>:
  402242:	41 55                	push   %r13
  402244:	41 54                	push   %r12
  402246:	55                   	push   %rbp
  402247:	53                   	push   %rbx
  402248:	48 83 ec 08          	sub    $0x8,%rsp
  40224c:	48 89 fb             	mov    %rdi,%rbx
  40224f:	49 89 f5             	mov    %rsi,%r13
  402252:	49 89 d4             	mov    %rdx,%r12
  402255:	eb 2e                	jmp    402285 <rio_read+0x43>
  402257:	48 8d 6b 10          	lea    0x10(%rbx),%rbp
  40225b:	8b 3b                	mov    (%rbx),%edi
  40225d:	ba 00 20 00 00       	mov    $0x2000,%edx
  402262:	48 89 ee             	mov    %rbp,%rsi
  402265:	e8 d6 ea ff ff       	callq  400d40 <read@plt>
  40226a:	89 43 04             	mov    %eax,0x4(%rbx)
  40226d:	85 c0                	test   %eax,%eax
  40226f:	79 0c                	jns    40227d <rio_read+0x3b>
  402271:	e8 1a ea ff ff       	callq  400c90 <__errno_location@plt>
  402276:	83 38 04             	cmpl   $0x4,(%rax)
  402279:	74 0a                	je     402285 <rio_read+0x43>
  40227b:	eb 37                	jmp    4022b4 <rio_read+0x72>
  40227d:	85 c0                	test   %eax,%eax
  40227f:	74 3c                	je     4022bd <rio_read+0x7b>
  402281:	48 89 6b 08          	mov    %rbp,0x8(%rbx)
  402285:	8b 6b 04             	mov    0x4(%rbx),%ebp
  402288:	85 ed                	test   %ebp,%ebp
  40228a:	7e cb                	jle    402257 <rio_read+0x15>
  40228c:	89 e8                	mov    %ebp,%eax
  40228e:	49 39 c4             	cmp    %rax,%r12
  402291:	77 03                	ja     402296 <rio_read+0x54>
  402293:	44 89 e5             	mov    %r12d,%ebp
  402296:	4c 63 e5             	movslq %ebp,%r12
  402299:	48 8b 73 08          	mov    0x8(%rbx),%rsi
  40229d:	4c 89 e2             	mov    %r12,%rdx
  4022a0:	4c 89 ef             	mov    %r13,%rdi
  4022a3:	e8 f8 ea ff ff       	callq  400da0 <memcpy@plt>
  4022a8:	4c 01 63 08          	add    %r12,0x8(%rbx)
  4022ac:	29 6b 04             	sub    %ebp,0x4(%rbx)
  4022af:	4c 89 e0             	mov    %r12,%rax
  4022b2:	eb 0e                	jmp    4022c2 <rio_read+0x80>
  4022b4:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  4022bb:	eb 05                	jmp    4022c2 <rio_read+0x80>
  4022bd:	b8 00 00 00 00       	mov    $0x0,%eax
  4022c2:	48 83 c4 08          	add    $0x8,%rsp
  4022c6:	5b                   	pop    %rbx
  4022c7:	5d                   	pop    %rbp
  4022c8:	41 5c                	pop    %r12
  4022ca:	41 5d                	pop    %r13
  4022cc:	c3                   	retq   

00000000004022cd <rio_readlineb>:
  4022cd:	41 55                	push   %r13
  4022cf:	41 54                	push   %r12
  4022d1:	55                   	push   %rbp
  4022d2:	53                   	push   %rbx
  4022d3:	48 83 ec 18          	sub    $0x18,%rsp
  4022d7:	49 89 fd             	mov    %rdi,%r13
  4022da:	48 89 f5             	mov    %rsi,%rbp
  4022dd:	49 89 d4             	mov    %rdx,%r12
  4022e0:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4022e7:	00 00 
  4022e9:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  4022ee:	31 c0                	xor    %eax,%eax
  4022f0:	bb 01 00 00 00       	mov    $0x1,%ebx
  4022f5:	eb 3f                	jmp    402336 <rio_readlineb+0x69>
  4022f7:	ba 01 00 00 00       	mov    $0x1,%edx
  4022fc:	48 8d 74 24 07       	lea    0x7(%rsp),%rsi
  402301:	4c 89 ef             	mov    %r13,%rdi
  402304:	e8 39 ff ff ff       	callq  402242 <rio_read>
  402309:	83 f8 01             	cmp    $0x1,%eax
  40230c:	75 15                	jne    402323 <rio_readlineb+0x56>
  40230e:	48 8d 45 01          	lea    0x1(%rbp),%rax
  402312:	0f b6 54 24 07       	movzbl 0x7(%rsp),%edx
  402317:	88 55 00             	mov    %dl,0x0(%rbp)
  40231a:	80 7c 24 07 0a       	cmpb   $0xa,0x7(%rsp)
  40231f:	75 0e                	jne    40232f <rio_readlineb+0x62>
  402321:	eb 1a                	jmp    40233d <rio_readlineb+0x70>
  402323:	85 c0                	test   %eax,%eax
  402325:	75 22                	jne    402349 <rio_readlineb+0x7c>
  402327:	48 83 fb 01          	cmp    $0x1,%rbx
  40232b:	75 13                	jne    402340 <rio_readlineb+0x73>
  40232d:	eb 23                	jmp    402352 <rio_readlineb+0x85>
  40232f:	48 83 c3 01          	add    $0x1,%rbx
  402333:	48 89 c5             	mov    %rax,%rbp
  402336:	4c 39 e3             	cmp    %r12,%rbx
  402339:	72 bc                	jb     4022f7 <rio_readlineb+0x2a>
  40233b:	eb 03                	jmp    402340 <rio_readlineb+0x73>
  40233d:	48 89 c5             	mov    %rax,%rbp
  402340:	c6 45 00 00          	movb   $0x0,0x0(%rbp)
  402344:	48 89 d8             	mov    %rbx,%rax
  402347:	eb 0e                	jmp    402357 <rio_readlineb+0x8a>
  402349:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  402350:	eb 05                	jmp    402357 <rio_readlineb+0x8a>
  402352:	b8 00 00 00 00       	mov    $0x0,%eax
  402357:	48 8b 4c 24 08       	mov    0x8(%rsp),%rcx
  40235c:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  402363:	00 00 
  402365:	74 05                	je     40236c <rio_readlineb+0x9f>
  402367:	e8 84 e9 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  40236c:	48 83 c4 18          	add    $0x18,%rsp
  402370:	5b                   	pop    %rbx
  402371:	5d                   	pop    %rbp
  402372:	41 5c                	pop    %r12
  402374:	41 5d                	pop    %r13
  402376:	c3                   	retq   

0000000000402377 <urlencode>:
  402377:	41 54                	push   %r12
  402379:	55                   	push   %rbp
  40237a:	53                   	push   %rbx
  40237b:	48 83 ec 10          	sub    $0x10,%rsp
  40237f:	48 89 fb             	mov    %rdi,%rbx
  402382:	48 89 f5             	mov    %rsi,%rbp
  402385:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40238c:	00 00 
  40238e:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  402393:	31 c0                	xor    %eax,%eax
  402395:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  40239c:	f2 ae                	repnz scas %es:(%rdi),%al
  40239e:	48 f7 d1             	not    %rcx
  4023a1:	8d 41 ff             	lea    -0x1(%rcx),%eax
  4023a4:	e9 aa 00 00 00       	jmpq   402453 <urlencode+0xdc>
  4023a9:	44 0f b6 03          	movzbl (%rbx),%r8d
  4023ad:	41 80 f8 2a          	cmp    $0x2a,%r8b
  4023b1:	0f 94 c2             	sete   %dl
  4023b4:	41 80 f8 2d          	cmp    $0x2d,%r8b
  4023b8:	0f 94 c0             	sete   %al
  4023bb:	08 c2                	or     %al,%dl
  4023bd:	75 24                	jne    4023e3 <urlencode+0x6c>
  4023bf:	41 80 f8 2e          	cmp    $0x2e,%r8b
  4023c3:	74 1e                	je     4023e3 <urlencode+0x6c>
  4023c5:	41 80 f8 5f          	cmp    $0x5f,%r8b
  4023c9:	74 18                	je     4023e3 <urlencode+0x6c>
  4023cb:	41 8d 40 d0          	lea    -0x30(%r8),%eax
  4023cf:	3c 09                	cmp    $0x9,%al
  4023d1:	76 10                	jbe    4023e3 <urlencode+0x6c>
  4023d3:	41 8d 40 bf          	lea    -0x41(%r8),%eax
  4023d7:	3c 19                	cmp    $0x19,%al
  4023d9:	76 08                	jbe    4023e3 <urlencode+0x6c>
  4023db:	41 8d 40 9f          	lea    -0x61(%r8),%eax
  4023df:	3c 19                	cmp    $0x19,%al
  4023e1:	77 0a                	ja     4023ed <urlencode+0x76>
  4023e3:	44 88 45 00          	mov    %r8b,0x0(%rbp)
  4023e7:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  4023eb:	eb 5f                	jmp    40244c <urlencode+0xd5>
  4023ed:	41 80 f8 20          	cmp    $0x20,%r8b
  4023f1:	75 0a                	jne    4023fd <urlencode+0x86>
  4023f3:	c6 45 00 2b          	movb   $0x2b,0x0(%rbp)
  4023f7:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  4023fb:	eb 4f                	jmp    40244c <urlencode+0xd5>
  4023fd:	41 8d 40 e0          	lea    -0x20(%r8),%eax
  402401:	3c 5f                	cmp    $0x5f,%al
  402403:	0f 96 c2             	setbe  %dl
  402406:	41 80 f8 09          	cmp    $0x9,%r8b
  40240a:	0f 94 c0             	sete   %al
  40240d:	08 c2                	or     %al,%dl
  40240f:	74 50                	je     402461 <urlencode+0xea>
  402411:	45 0f b6 c0          	movzbl %r8b,%r8d
  402415:	b9 48 37 40 00       	mov    $0x403748,%ecx
  40241a:	ba 08 00 00 00       	mov    $0x8,%edx
  40241f:	be 01 00 00 00       	mov    $0x1,%esi
  402424:	48 89 e7             	mov    %rsp,%rdi
  402427:	b8 00 00 00 00       	mov    $0x0,%eax
  40242c:	e8 4f ea ff ff       	callq  400e80 <__sprintf_chk@plt>
  402431:	0f b6 04 24          	movzbl (%rsp),%eax
  402435:	88 45 00             	mov    %al,0x0(%rbp)
  402438:	0f b6 44 24 01       	movzbl 0x1(%rsp),%eax
  40243d:	88 45 01             	mov    %al,0x1(%rbp)
  402440:	0f b6 44 24 02       	movzbl 0x2(%rsp),%eax
  402445:	88 45 02             	mov    %al,0x2(%rbp)
  402448:	48 8d 6d 03          	lea    0x3(%rbp),%rbp
  40244c:	48 83 c3 01          	add    $0x1,%rbx
  402450:	44 89 e0             	mov    %r12d,%eax
  402453:	44 8d 60 ff          	lea    -0x1(%rax),%r12d
  402457:	85 c0                	test   %eax,%eax
  402459:	0f 85 4a ff ff ff    	jne    4023a9 <urlencode+0x32>
  40245f:	eb 05                	jmp    402466 <urlencode+0xef>
  402461:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402466:	48 8b 74 24 08       	mov    0x8(%rsp),%rsi
  40246b:	64 48 33 34 25 28 00 	xor    %fs:0x28,%rsi
  402472:	00 00 
  402474:	74 05                	je     40247b <urlencode+0x104>
  402476:	e8 75 e8 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  40247b:	48 83 c4 10          	add    $0x10,%rsp
  40247f:	5b                   	pop    %rbx
  402480:	5d                   	pop    %rbp
  402481:	41 5c                	pop    %r12
  402483:	c3                   	retq   

0000000000402484 <submitr>:
  402484:	41 57                	push   %r15
  402486:	41 56                	push   %r14
  402488:	41 55                	push   %r13
  40248a:	41 54                	push   %r12
  40248c:	55                   	push   %rbp
  40248d:	53                   	push   %rbx
  40248e:	48 81 ec 58 a0 00 00 	sub    $0xa058,%rsp
  402495:	49 89 fc             	mov    %rdi,%r12
  402498:	89 74 24 04          	mov    %esi,0x4(%rsp)
  40249c:	49 89 d7             	mov    %rdx,%r15
  40249f:	49 89 ce             	mov    %rcx,%r14
  4024a2:	4c 89 44 24 08       	mov    %r8,0x8(%rsp)
  4024a7:	4d 89 cd             	mov    %r9,%r13
  4024aa:	48 8b 9c 24 90 a0 00 	mov    0xa090(%rsp),%rbx
  4024b1:	00 
  4024b2:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4024b9:	00 00 
  4024bb:	48 89 84 24 48 a0 00 	mov    %rax,0xa048(%rsp)
  4024c2:	00 
  4024c3:	31 c0                	xor    %eax,%eax
  4024c5:	c7 44 24 1c 00 00 00 	movl   $0x0,0x1c(%rsp)
  4024cc:	00 
  4024cd:	ba 00 00 00 00       	mov    $0x0,%edx
  4024d2:	be 01 00 00 00       	mov    $0x1,%esi
  4024d7:	bf 02 00 00 00       	mov    $0x2,%edi
  4024dc:	e8 af e9 ff ff       	callq  400e90 <socket@plt>
  4024e1:	85 c0                	test   %eax,%eax
  4024e3:	79 4e                	jns    402533 <submitr+0xaf>
  4024e5:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4024ec:	3a 20 43 
  4024ef:	48 89 03             	mov    %rax,(%rbx)
  4024f2:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4024f9:	20 75 6e 
  4024fc:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402500:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402507:	74 6f 20 
  40250a:	48 89 43 10          	mov    %rax,0x10(%rbx)
  40250e:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  402515:	65 20 73 
  402518:	48 89 43 18          	mov    %rax,0x18(%rbx)
  40251c:	c7 43 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbx)
  402523:	66 c7 43 24 74 00    	movw   $0x74,0x24(%rbx)
  402529:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40252e:	e9 97 06 00 00       	jmpq   402bca <submitr+0x746>
  402533:	89 c5                	mov    %eax,%ebp
  402535:	4c 89 e7             	mov    %r12,%rdi
  402538:	e8 33 e8 ff ff       	callq  400d70 <gethostbyname@plt>
  40253d:	48 85 c0             	test   %rax,%rax
  402540:	75 67                	jne    4025a9 <submitr+0x125>
  402542:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  402549:	3a 20 44 
  40254c:	48 89 03             	mov    %rax,(%rbx)
  40254f:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  402556:	20 75 6e 
  402559:	48 89 43 08          	mov    %rax,0x8(%rbx)
  40255d:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402564:	74 6f 20 
  402567:	48 89 43 10          	mov    %rax,0x10(%rbx)
  40256b:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  402572:	76 65 20 
  402575:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402579:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  402580:	72 20 61 
  402583:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402587:	c7 43 28 64 64 72 65 	movl   $0x65726464,0x28(%rbx)
  40258e:	66 c7 43 2c 73 73    	movw   $0x7373,0x2c(%rbx)
  402594:	c6 43 2e 00          	movb   $0x0,0x2e(%rbx)
  402598:	89 ef                	mov    %ebp,%edi
  40259a:	e8 91 e7 ff ff       	callq  400d30 <close@plt>
  40259f:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4025a4:	e9 21 06 00 00       	jmpq   402bca <submitr+0x746>
  4025a9:	48 c7 44 24 20 00 00 	movq   $0x0,0x20(%rsp)
  4025b0:	00 00 
  4025b2:	48 c7 44 24 28 00 00 	movq   $0x0,0x28(%rsp)
  4025b9:	00 00 
  4025bb:	66 c7 44 24 20 02 00 	movw   $0x2,0x20(%rsp)
  4025c2:	48 63 50 14          	movslq 0x14(%rax),%rdx
  4025c6:	48 8b 40 18          	mov    0x18(%rax),%rax
  4025ca:	48 8b 30             	mov    (%rax),%rsi
  4025cd:	48 8d 7c 24 24       	lea    0x24(%rsp),%rdi
  4025d2:	b9 0c 00 00 00       	mov    $0xc,%ecx
  4025d7:	e8 a4 e7 ff ff       	callq  400d80 <__memmove_chk@plt>
  4025dc:	0f b7 44 24 04       	movzwl 0x4(%rsp),%eax
  4025e1:	66 c1 c8 08          	ror    $0x8,%ax
  4025e5:	66 89 44 24 22       	mov    %ax,0x22(%rsp)
  4025ea:	ba 10 00 00 00       	mov    $0x10,%edx
  4025ef:	48 8d 74 24 20       	lea    0x20(%rsp),%rsi
  4025f4:	89 ef                	mov    %ebp,%edi
  4025f6:	e8 65 e8 ff ff       	callq  400e60 <connect@plt>
  4025fb:	85 c0                	test   %eax,%eax
  4025fd:	79 59                	jns    402658 <submitr+0x1d4>
  4025ff:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  402606:	3a 20 55 
  402609:	48 89 03             	mov    %rax,(%rbx)
  40260c:	48 b8 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rax
  402613:	20 74 6f 
  402616:	48 89 43 08          	mov    %rax,0x8(%rbx)
  40261a:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  402621:	65 63 74 
  402624:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402628:	48 b8 20 74 6f 20 74 	movabs $0x20656874206f7420,%rax
  40262f:	68 65 20 
  402632:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402636:	c7 43 20 73 65 72 76 	movl   $0x76726573,0x20(%rbx)
  40263d:	66 c7 43 24 65 72    	movw   $0x7265,0x24(%rbx)
  402643:	c6 43 26 00          	movb   $0x0,0x26(%rbx)
  402647:	89 ef                	mov    %ebp,%edi
  402649:	e8 e2 e6 ff ff       	callq  400d30 <close@plt>
  40264e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402653:	e9 72 05 00 00       	jmpq   402bca <submitr+0x746>
  402658:	48 c7 c6 ff ff ff ff 	mov    $0xffffffffffffffff,%rsi
  40265f:	b8 00 00 00 00       	mov    $0x0,%eax
  402664:	48 89 f1             	mov    %rsi,%rcx
  402667:	4c 89 ef             	mov    %r13,%rdi
  40266a:	f2 ae                	repnz scas %es:(%rdi),%al
  40266c:	48 f7 d1             	not    %rcx
  40266f:	48 89 ca             	mov    %rcx,%rdx
  402672:	48 89 f1             	mov    %rsi,%rcx
  402675:	4c 89 ff             	mov    %r15,%rdi
  402678:	f2 ae                	repnz scas %es:(%rdi),%al
  40267a:	48 f7 d1             	not    %rcx
  40267d:	49 89 c8             	mov    %rcx,%r8
  402680:	48 89 f1             	mov    %rsi,%rcx
  402683:	4c 89 f7             	mov    %r14,%rdi
  402686:	f2 ae                	repnz scas %es:(%rdi),%al
  402688:	48 f7 d1             	not    %rcx
  40268b:	4d 8d 44 08 fe       	lea    -0x2(%r8,%rcx,1),%r8
  402690:	48 89 f1             	mov    %rsi,%rcx
  402693:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  402698:	f2 ae                	repnz scas %es:(%rdi),%al
  40269a:	48 89 c8             	mov    %rcx,%rax
  40269d:	48 f7 d0             	not    %rax
  4026a0:	49 8d 4c 00 ff       	lea    -0x1(%r8,%rax,1),%rcx
  4026a5:	48 8d 44 52 fd       	lea    -0x3(%rdx,%rdx,2),%rax
  4026aa:	48 8d 84 01 80 00 00 	lea    0x80(%rcx,%rax,1),%rax
  4026b1:	00 
  4026b2:	48 3d 00 20 00 00    	cmp    $0x2000,%rax
  4026b8:	76 72                	jbe    40272c <submitr+0x2a8>
  4026ba:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  4026c1:	3a 20 52 
  4026c4:	48 89 03             	mov    %rax,(%rbx)
  4026c7:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  4026ce:	20 73 74 
  4026d1:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4026d5:	48 b8 72 69 6e 67 20 	movabs $0x6f6f7420676e6972,%rax
  4026dc:	74 6f 6f 
  4026df:	48 89 43 10          	mov    %rax,0x10(%rbx)
  4026e3:	48 b8 20 6c 61 72 67 	movabs $0x202e656772616c20,%rax
  4026ea:	65 2e 20 
  4026ed:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4026f1:	48 b8 49 6e 63 72 65 	movabs $0x6573616572636e49,%rax
  4026f8:	61 73 65 
  4026fb:	48 89 43 20          	mov    %rax,0x20(%rbx)
  4026ff:	48 b8 20 53 55 42 4d 	movabs $0x5254494d42555320,%rax
  402706:	49 54 52 
  402709:	48 89 43 28          	mov    %rax,0x28(%rbx)
  40270d:	48 b8 5f 4d 41 58 42 	movabs $0x46554258414d5f,%rax
  402714:	55 46 00 
  402717:	48 89 43 30          	mov    %rax,0x30(%rbx)
  40271b:	89 ef                	mov    %ebp,%edi
  40271d:	e8 0e e6 ff ff       	callq  400d30 <close@plt>
  402722:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402727:	e9 9e 04 00 00       	jmpq   402bca <submitr+0x746>
  40272c:	48 8d b4 24 40 40 00 	lea    0x4040(%rsp),%rsi
  402733:	00 
  402734:	b9 00 04 00 00       	mov    $0x400,%ecx
  402739:	b8 00 00 00 00       	mov    $0x0,%eax
  40273e:	48 89 f7             	mov    %rsi,%rdi
  402741:	f3 48 ab             	rep stos %rax,%es:(%rdi)
  402744:	4c 89 ef             	mov    %r13,%rdi
  402747:	e8 2b fc ff ff       	callq  402377 <urlencode>
  40274c:	85 c0                	test   %eax,%eax
  40274e:	0f 89 8a 00 00 00    	jns    4027de <submitr+0x35a>
  402754:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  40275b:	3a 20 52 
  40275e:	48 89 03             	mov    %rax,(%rbx)
  402761:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  402768:	20 73 74 
  40276b:	48 89 43 08          	mov    %rax,0x8(%rbx)
  40276f:	48 b8 72 69 6e 67 20 	movabs $0x6e6f6320676e6972,%rax
  402776:	63 6f 6e 
  402779:	48 89 43 10          	mov    %rax,0x10(%rbx)
  40277d:	48 b8 74 61 69 6e 73 	movabs $0x6e6120736e696174,%rax
  402784:	20 61 6e 
  402787:	48 89 43 18          	mov    %rax,0x18(%rbx)
  40278b:	48 b8 20 69 6c 6c 65 	movabs $0x6c6167656c6c6920,%rax
  402792:	67 61 6c 
  402795:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402799:	48 b8 20 6f 72 20 75 	movabs $0x72706e7520726f20,%rax
  4027a0:	6e 70 72 
  4027a3:	48 89 43 28          	mov    %rax,0x28(%rbx)
  4027a7:	48 b8 69 6e 74 61 62 	movabs $0x20656c6261746e69,%rax
  4027ae:	6c 65 20 
  4027b1:	48 89 43 30          	mov    %rax,0x30(%rbx)
  4027b5:	48 b8 63 68 61 72 61 	movabs $0x6574636172616863,%rax
  4027bc:	63 74 65 
  4027bf:	48 89 43 38          	mov    %rax,0x38(%rbx)
  4027c3:	66 c7 43 40 72 2e    	movw   $0x2e72,0x40(%rbx)
  4027c9:	c6 43 42 00          	movb   $0x0,0x42(%rbx)
  4027cd:	89 ef                	mov    %ebp,%edi
  4027cf:	e8 5c e5 ff ff       	callq  400d30 <close@plt>
  4027d4:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4027d9:	e9 ec 03 00 00       	jmpq   402bca <submitr+0x746>
  4027de:	4c 8d ac 24 40 20 00 	lea    0x2040(%rsp),%r13
  4027e5:	00 
  4027e6:	41 54                	push   %r12
  4027e8:	48 8d 84 24 48 40 00 	lea    0x4048(%rsp),%rax
  4027ef:	00 
  4027f0:	50                   	push   %rax
  4027f1:	4d 89 f9             	mov    %r15,%r9
  4027f4:	4d 89 f0             	mov    %r14,%r8
  4027f7:	b9 d8 36 40 00       	mov    $0x4036d8,%ecx
  4027fc:	ba 00 20 00 00       	mov    $0x2000,%edx
  402801:	be 01 00 00 00       	mov    $0x1,%esi
  402806:	4c 89 ef             	mov    %r13,%rdi
  402809:	b8 00 00 00 00       	mov    $0x0,%eax
  40280e:	e8 6d e6 ff ff       	callq  400e80 <__sprintf_chk@plt>
  402813:	b8 00 00 00 00       	mov    $0x0,%eax
  402818:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  40281f:	4c 89 ef             	mov    %r13,%rdi
  402822:	f2 ae                	repnz scas %es:(%rdi),%al
  402824:	48 f7 d1             	not    %rcx
  402827:	48 8d 51 ff          	lea    -0x1(%rcx),%rdx
  40282b:	4c 89 ee             	mov    %r13,%rsi
  40282e:	89 ef                	mov    %ebp,%edi
  402830:	e8 b1 f9 ff ff       	callq  4021e6 <rio_writen>
  402835:	48 83 c4 10          	add    $0x10,%rsp
  402839:	48 85 c0             	test   %rax,%rax
  40283c:	79 6e                	jns    4028ac <submitr+0x428>
  40283e:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402845:	3a 20 43 
  402848:	48 89 03             	mov    %rax,(%rbx)
  40284b:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402852:	20 75 6e 
  402855:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402859:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402860:	74 6f 20 
  402863:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402867:	48 b8 77 72 69 74 65 	movabs $0x6f74206574697277,%rax
  40286e:	20 74 6f 
  402871:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402875:	48 b8 20 74 68 65 20 	movabs $0x7365722065687420,%rax
  40287c:	72 65 73 
  40287f:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402883:	48 b8 75 6c 74 20 73 	movabs $0x7672657320746c75,%rax
  40288a:	65 72 76 
  40288d:	48 89 43 28          	mov    %rax,0x28(%rbx)
  402891:	66 c7 43 30 65 72    	movw   $0x7265,0x30(%rbx)
  402897:	c6 43 32 00          	movb   $0x0,0x32(%rbx)
  40289b:	89 ef                	mov    %ebp,%edi
  40289d:	e8 8e e4 ff ff       	callq  400d30 <close@plt>
  4028a2:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4028a7:	e9 1e 03 00 00       	jmpq   402bca <submitr+0x746>
  4028ac:	89 ee                	mov    %ebp,%esi
  4028ae:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  4028b3:	e8 ee f8 ff ff       	callq  4021a6 <rio_readinitb>
  4028b8:	ba 00 20 00 00       	mov    $0x2000,%edx
  4028bd:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  4028c4:	00 
  4028c5:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  4028ca:	e8 fe f9 ff ff       	callq  4022cd <rio_readlineb>
  4028cf:	48 85 c0             	test   %rax,%rax
  4028d2:	7f 7d                	jg     402951 <submitr+0x4cd>
  4028d4:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4028db:	3a 20 43 
  4028de:	48 89 03             	mov    %rax,(%rbx)
  4028e1:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4028e8:	20 75 6e 
  4028eb:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4028ef:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4028f6:	74 6f 20 
  4028f9:	48 89 43 10          	mov    %rax,0x10(%rbx)
  4028fd:	48 b8 72 65 61 64 20 	movabs $0x7269662064616572,%rax
  402904:	66 69 72 
  402907:	48 89 43 18          	mov    %rax,0x18(%rbx)
  40290b:	48 b8 73 74 20 68 65 	movabs $0x6564616568207473,%rax
  402912:	61 64 65 
  402915:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402919:	48 b8 72 20 66 72 6f 	movabs $0x72206d6f72662072,%rax
  402920:	6d 20 72 
  402923:	48 89 43 28          	mov    %rax,0x28(%rbx)
  402927:	48 b8 65 73 75 6c 74 	movabs $0x657320746c757365,%rax
  40292e:	20 73 65 
  402931:	48 89 43 30          	mov    %rax,0x30(%rbx)
  402935:	c7 43 38 72 76 65 72 	movl   $0x72657672,0x38(%rbx)
  40293c:	c6 43 3c 00          	movb   $0x0,0x3c(%rbx)
  402940:	89 ef                	mov    %ebp,%edi
  402942:	e8 e9 e3 ff ff       	callq  400d30 <close@plt>
  402947:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40294c:	e9 79 02 00 00       	jmpq   402bca <submitr+0x746>
  402951:	4c 8d 84 24 40 80 00 	lea    0x8040(%rsp),%r8
  402958:	00 
  402959:	48 8d 4c 24 1c       	lea    0x1c(%rsp),%rcx
  40295e:	48 8d 94 24 40 60 00 	lea    0x6040(%rsp),%rdx
  402965:	00 
  402966:	be 4f 37 40 00       	mov    $0x40374f,%esi
  40296b:	48 8d bc 24 40 20 00 	lea    0x2040(%rsp),%rdi
  402972:	00 
  402973:	b8 00 00 00 00       	mov    $0x0,%eax
  402978:	e8 63 e4 ff ff       	callq  400de0 <__isoc99_sscanf@plt>
  40297d:	e9 95 00 00 00       	jmpq   402a17 <submitr+0x593>
  402982:	ba 00 20 00 00       	mov    $0x2000,%edx
  402987:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  40298e:	00 
  40298f:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  402994:	e8 34 f9 ff ff       	callq  4022cd <rio_readlineb>
  402999:	48 85 c0             	test   %rax,%rax
  40299c:	7f 79                	jg     402a17 <submitr+0x593>
  40299e:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4029a5:	3a 20 43 
  4029a8:	48 89 03             	mov    %rax,(%rbx)
  4029ab:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4029b2:	20 75 6e 
  4029b5:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4029b9:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4029c0:	74 6f 20 
  4029c3:	48 89 43 10          	mov    %rax,0x10(%rbx)
  4029c7:	48 b8 72 65 61 64 20 	movabs $0x6165682064616572,%rax
  4029ce:	68 65 61 
  4029d1:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4029d5:	48 b8 64 65 72 73 20 	movabs $0x6f72662073726564,%rax
  4029dc:	66 72 6f 
  4029df:	48 89 43 20          	mov    %rax,0x20(%rbx)
  4029e3:	48 b8 6d 20 74 68 65 	movabs $0x657220656874206d,%rax
  4029ea:	20 72 65 
  4029ed:	48 89 43 28          	mov    %rax,0x28(%rbx)
  4029f1:	48 b8 73 75 6c 74 20 	movabs $0x72657320746c7573,%rax
  4029f8:	73 65 72 
  4029fb:	48 89 43 30          	mov    %rax,0x30(%rbx)
  4029ff:	c7 43 38 76 65 72 00 	movl   $0x726576,0x38(%rbx)
  402a06:	89 ef                	mov    %ebp,%edi
  402a08:	e8 23 e3 ff ff       	callq  400d30 <close@plt>
  402a0d:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402a12:	e9 b3 01 00 00       	jmpq   402bca <submitr+0x746>
  402a17:	0f b6 94 24 40 20 00 	movzbl 0x2040(%rsp),%edx
  402a1e:	00 
  402a1f:	b8 0d 00 00 00       	mov    $0xd,%eax
  402a24:	29 d0                	sub    %edx,%eax
  402a26:	75 1b                	jne    402a43 <submitr+0x5bf>
  402a28:	0f b6 94 24 41 20 00 	movzbl 0x2041(%rsp),%edx
  402a2f:	00 
  402a30:	b8 0a 00 00 00       	mov    $0xa,%eax
  402a35:	29 d0                	sub    %edx,%eax
  402a37:	75 0a                	jne    402a43 <submitr+0x5bf>
  402a39:	0f b6 84 24 42 20 00 	movzbl 0x2042(%rsp),%eax
  402a40:	00 
  402a41:	f7 d8                	neg    %eax
  402a43:	85 c0                	test   %eax,%eax
  402a45:	0f 85 37 ff ff ff    	jne    402982 <submitr+0x4fe>
  402a4b:	ba 00 20 00 00       	mov    $0x2000,%edx
  402a50:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  402a57:	00 
  402a58:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  402a5d:	e8 6b f8 ff ff       	callq  4022cd <rio_readlineb>
  402a62:	48 85 c0             	test   %rax,%rax
  402a65:	0f 8f 83 00 00 00    	jg     402aee <submitr+0x66a>
  402a6b:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402a72:	3a 20 43 
  402a75:	48 89 03             	mov    %rax,(%rbx)
  402a78:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402a7f:	20 75 6e 
  402a82:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402a86:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402a8d:	74 6f 20 
  402a90:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402a94:	48 b8 72 65 61 64 20 	movabs $0x6174732064616572,%rax
  402a9b:	73 74 61 
  402a9e:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402aa2:	48 b8 74 75 73 20 6d 	movabs $0x7373656d20737574,%rax
  402aa9:	65 73 73 
  402aac:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402ab0:	48 b8 61 67 65 20 66 	movabs $0x6d6f726620656761,%rax
  402ab7:	72 6f 6d 
  402aba:	48 89 43 28          	mov    %rax,0x28(%rbx)
  402abe:	48 b8 20 72 65 73 75 	movabs $0x20746c7573657220,%rax
  402ac5:	6c 74 20 
  402ac8:	48 89 43 30          	mov    %rax,0x30(%rbx)
  402acc:	c7 43 38 73 65 72 76 	movl   $0x76726573,0x38(%rbx)
  402ad3:	66 c7 43 3c 65 72    	movw   $0x7265,0x3c(%rbx)
  402ad9:	c6 43 3e 00          	movb   $0x0,0x3e(%rbx)
  402add:	89 ef                	mov    %ebp,%edi
  402adf:	e8 4c e2 ff ff       	callq  400d30 <close@plt>
  402ae4:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402ae9:	e9 dc 00 00 00       	jmpq   402bca <submitr+0x746>
  402aee:	44 8b 44 24 1c       	mov    0x1c(%rsp),%r8d
  402af3:	41 81 f8 c8 00 00 00 	cmp    $0xc8,%r8d
  402afa:	74 37                	je     402b33 <submitr+0x6af>
  402afc:	4c 8d 8c 24 40 80 00 	lea    0x8040(%rsp),%r9
  402b03:	00 
  402b04:	b9 18 37 40 00       	mov    $0x403718,%ecx
  402b09:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  402b10:	be 01 00 00 00       	mov    $0x1,%esi
  402b15:	48 89 df             	mov    %rbx,%rdi
  402b18:	b8 00 00 00 00       	mov    $0x0,%eax
  402b1d:	e8 5e e3 ff ff       	callq  400e80 <__sprintf_chk@plt>
  402b22:	89 ef                	mov    %ebp,%edi
  402b24:	e8 07 e2 ff ff       	callq  400d30 <close@plt>
  402b29:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402b2e:	e9 97 00 00 00       	jmpq   402bca <submitr+0x746>
  402b33:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  402b3a:	00 
  402b3b:	48 89 df             	mov    %rbx,%rdi
  402b3e:	e8 7d e1 ff ff       	callq  400cc0 <strcpy@plt>
  402b43:	89 ef                	mov    %ebp,%edi
  402b45:	e8 e6 e1 ff ff       	callq  400d30 <close@plt>
  402b4a:	0f b6 03             	movzbl (%rbx),%eax
  402b4d:	ba 4f 00 00 00       	mov    $0x4f,%edx
  402b52:	29 c2                	sub    %eax,%edx
  402b54:	75 22                	jne    402b78 <submitr+0x6f4>
  402b56:	0f b6 4b 01          	movzbl 0x1(%rbx),%ecx
  402b5a:	b8 4b 00 00 00       	mov    $0x4b,%eax
  402b5f:	29 c8                	sub    %ecx,%eax
  402b61:	75 17                	jne    402b7a <submitr+0x6f6>
  402b63:	0f b6 4b 02          	movzbl 0x2(%rbx),%ecx
  402b67:	b8 0a 00 00 00       	mov    $0xa,%eax
  402b6c:	29 c8                	sub    %ecx,%eax
  402b6e:	75 0a                	jne    402b7a <submitr+0x6f6>
  402b70:	0f b6 43 03          	movzbl 0x3(%rbx),%eax
  402b74:	f7 d8                	neg    %eax
  402b76:	eb 02                	jmp    402b7a <submitr+0x6f6>
  402b78:	89 d0                	mov    %edx,%eax
  402b7a:	85 c0                	test   %eax,%eax
  402b7c:	74 40                	je     402bbe <submitr+0x73a>
  402b7e:	bf 60 37 40 00       	mov    $0x403760,%edi
  402b83:	b9 05 00 00 00       	mov    $0x5,%ecx
  402b88:	48 89 de             	mov    %rbx,%rsi
  402b8b:	f3 a6                	repz cmpsb %es:(%rdi),%ds:(%rsi)
  402b8d:	0f 97 c0             	seta   %al
  402b90:	0f 92 c1             	setb   %cl
  402b93:	29 c8                	sub    %ecx,%eax
  402b95:	0f be c0             	movsbl %al,%eax
  402b98:	85 c0                	test   %eax,%eax
  402b9a:	74 2e                	je     402bca <submitr+0x746>
  402b9c:	85 d2                	test   %edx,%edx
  402b9e:	75 13                	jne    402bb3 <submitr+0x72f>
  402ba0:	0f b6 43 01          	movzbl 0x1(%rbx),%eax
  402ba4:	ba 4b 00 00 00       	mov    $0x4b,%edx
  402ba9:	29 c2                	sub    %eax,%edx
  402bab:	75 06                	jne    402bb3 <submitr+0x72f>
  402bad:	0f b6 53 02          	movzbl 0x2(%rbx),%edx
  402bb1:	f7 da                	neg    %edx
  402bb3:	85 d2                	test   %edx,%edx
  402bb5:	75 0e                	jne    402bc5 <submitr+0x741>
  402bb7:	b8 00 00 00 00       	mov    $0x0,%eax
  402bbc:	eb 0c                	jmp    402bca <submitr+0x746>
  402bbe:	b8 00 00 00 00       	mov    $0x0,%eax
  402bc3:	eb 05                	jmp    402bca <submitr+0x746>
  402bc5:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402bca:	48 8b 9c 24 48 a0 00 	mov    0xa048(%rsp),%rbx
  402bd1:	00 
  402bd2:	64 48 33 1c 25 28 00 	xor    %fs:0x28,%rbx
  402bd9:	00 00 
  402bdb:	74 05                	je     402be2 <submitr+0x75e>
  402bdd:	e8 0e e1 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  402be2:	48 81 c4 58 a0 00 00 	add    $0xa058,%rsp
  402be9:	5b                   	pop    %rbx
  402bea:	5d                   	pop    %rbp
  402beb:	41 5c                	pop    %r12
  402bed:	41 5d                	pop    %r13
  402bef:	41 5e                	pop    %r14
  402bf1:	41 5f                	pop    %r15
  402bf3:	c3                   	retq   

0000000000402bf4 <init_timeout>:
  402bf4:	85 ff                	test   %edi,%edi
  402bf6:	74 23                	je     402c1b <init_timeout+0x27>
  402bf8:	53                   	push   %rbx
  402bf9:	89 fb                	mov    %edi,%ebx
  402bfb:	85 ff                	test   %edi,%edi
  402bfd:	79 05                	jns    402c04 <init_timeout+0x10>
  402bff:	bb 00 00 00 00       	mov    $0x0,%ebx
  402c04:	be b8 21 40 00       	mov    $0x4021b8,%esi
  402c09:	bf 0e 00 00 00       	mov    $0xe,%edi
  402c0e:	e8 4d e1 ff ff       	callq  400d60 <signal@plt>
  402c13:	89 df                	mov    %ebx,%edi
  402c15:	e8 06 e1 ff ff       	callq  400d20 <alarm@plt>
  402c1a:	5b                   	pop    %rbx
  402c1b:	f3 c3                	repz retq 

0000000000402c1d <init_driver>:
  402c1d:	55                   	push   %rbp
  402c1e:	53                   	push   %rbx
  402c1f:	48 83 ec 28          	sub    $0x28,%rsp
  402c23:	48 89 fd             	mov    %rdi,%rbp
  402c26:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  402c2d:	00 00 
  402c2f:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  402c34:	31 c0                	xor    %eax,%eax
  402c36:	be 01 00 00 00       	mov    $0x1,%esi
  402c3b:	bf 0d 00 00 00       	mov    $0xd,%edi
  402c40:	e8 1b e1 ff ff       	callq  400d60 <signal@plt>
  402c45:	be 01 00 00 00       	mov    $0x1,%esi
  402c4a:	bf 1d 00 00 00       	mov    $0x1d,%edi
  402c4f:	e8 0c e1 ff ff       	callq  400d60 <signal@plt>
  402c54:	be 01 00 00 00       	mov    $0x1,%esi
  402c59:	bf 1d 00 00 00       	mov    $0x1d,%edi
  402c5e:	e8 fd e0 ff ff       	callq  400d60 <signal@plt>
  402c63:	ba 00 00 00 00       	mov    $0x0,%edx
  402c68:	be 01 00 00 00       	mov    $0x1,%esi
  402c6d:	bf 02 00 00 00       	mov    $0x2,%edi
  402c72:	e8 19 e2 ff ff       	callq  400e90 <socket@plt>
  402c77:	85 c0                	test   %eax,%eax
  402c79:	79 4f                	jns    402cca <init_driver+0xad>
  402c7b:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402c82:	3a 20 43 
  402c85:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402c89:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402c90:	20 75 6e 
  402c93:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402c97:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402c9e:	74 6f 20 
  402ca1:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402ca5:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  402cac:	65 20 73 
  402caf:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402cb3:	c7 45 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbp)
  402cba:	66 c7 45 24 74 00    	movw   $0x74,0x24(%rbp)
  402cc0:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402cc5:	e9 2a 01 00 00       	jmpq   402df4 <init_driver+0x1d7>
  402cca:	89 c3                	mov    %eax,%ebx
  402ccc:	bf 65 37 40 00       	mov    $0x403765,%edi
  402cd1:	e8 9a e0 ff ff       	callq  400d70 <gethostbyname@plt>
  402cd6:	48 85 c0             	test   %rax,%rax
  402cd9:	75 68                	jne    402d43 <init_driver+0x126>
  402cdb:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  402ce2:	3a 20 44 
  402ce5:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402ce9:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  402cf0:	20 75 6e 
  402cf3:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402cf7:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402cfe:	74 6f 20 
  402d01:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402d05:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  402d0c:	76 65 20 
  402d0f:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402d13:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  402d1a:	72 20 61 
  402d1d:	48 89 45 20          	mov    %rax,0x20(%rbp)
  402d21:	c7 45 28 64 64 72 65 	movl   $0x65726464,0x28(%rbp)
  402d28:	66 c7 45 2c 73 73    	movw   $0x7373,0x2c(%rbp)
  402d2e:	c6 45 2e 00          	movb   $0x0,0x2e(%rbp)
  402d32:	89 df                	mov    %ebx,%edi
  402d34:	e8 f7 df ff ff       	callq  400d30 <close@plt>
  402d39:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402d3e:	e9 b1 00 00 00       	jmpq   402df4 <init_driver+0x1d7>
  402d43:	48 c7 04 24 00 00 00 	movq   $0x0,(%rsp)
  402d4a:	00 
  402d4b:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
  402d52:	00 00 
  402d54:	66 c7 04 24 02 00    	movw   $0x2,(%rsp)
  402d5a:	48 63 50 14          	movslq 0x14(%rax),%rdx
  402d5e:	48 8b 40 18          	mov    0x18(%rax),%rax
  402d62:	48 8b 30             	mov    (%rax),%rsi
  402d65:	48 8d 7c 24 04       	lea    0x4(%rsp),%rdi
  402d6a:	b9 0c 00 00 00       	mov    $0xc,%ecx
  402d6f:	e8 0c e0 ff ff       	callq  400d80 <__memmove_chk@plt>
  402d74:	66 c7 44 24 02 4b 8d 	movw   $0x8d4b,0x2(%rsp)
  402d7b:	ba 10 00 00 00       	mov    $0x10,%edx
  402d80:	48 89 e6             	mov    %rsp,%rsi
  402d83:	89 df                	mov    %ebx,%edi
  402d85:	e8 d6 e0 ff ff       	callq  400e60 <connect@plt>
  402d8a:	85 c0                	test   %eax,%eax
  402d8c:	79 50                	jns    402dde <init_driver+0x1c1>
  402d8e:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  402d95:	3a 20 55 
  402d98:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402d9c:	48 b8 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rax
  402da3:	20 74 6f 
  402da6:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402daa:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  402db1:	65 63 74 
  402db4:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402db8:	48 b8 20 74 6f 20 73 	movabs $0x76726573206f7420,%rax
  402dbf:	65 72 76 
  402dc2:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402dc6:	66 c7 45 20 65 72    	movw   $0x7265,0x20(%rbp)
  402dcc:	c6 45 22 00          	movb   $0x0,0x22(%rbp)
  402dd0:	89 df                	mov    %ebx,%edi
  402dd2:	e8 59 df ff ff       	callq  400d30 <close@plt>
  402dd7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402ddc:	eb 16                	jmp    402df4 <init_driver+0x1d7>
  402dde:	89 df                	mov    %ebx,%edi
  402de0:	e8 4b df ff ff       	callq  400d30 <close@plt>
  402de5:	66 c7 45 00 4f 4b    	movw   $0x4b4f,0x0(%rbp)
  402deb:	c6 45 02 00          	movb   $0x0,0x2(%rbp)
  402def:	b8 00 00 00 00       	mov    $0x0,%eax
  402df4:	48 8b 4c 24 18       	mov    0x18(%rsp),%rcx
  402df9:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  402e00:	00 00 
  402e02:	74 05                	je     402e09 <init_driver+0x1ec>
  402e04:	e8 e7 de ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  402e09:	48 83 c4 28          	add    $0x28,%rsp
  402e0d:	5b                   	pop    %rbx
  402e0e:	5d                   	pop    %rbp
  402e0f:	c3                   	retq   

0000000000402e10 <driver_post>:
  402e10:	53                   	push   %rbx
  402e11:	4c 89 cb             	mov    %r9,%rbx
  402e14:	45 85 c0             	test   %r8d,%r8d
  402e17:	74 27                	je     402e40 <driver_post+0x30>
  402e19:	48 89 ca             	mov    %rcx,%rdx
  402e1c:	be 72 37 40 00       	mov    $0x403772,%esi
  402e21:	bf 01 00 00 00       	mov    $0x1,%edi
  402e26:	b8 00 00 00 00       	mov    $0x0,%eax
  402e2b:	e8 d0 df ff ff       	callq  400e00 <__printf_chk@plt>
  402e30:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  402e35:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  402e39:	b8 00 00 00 00       	mov    $0x0,%eax
  402e3e:	eb 3f                	jmp    402e7f <driver_post+0x6f>
  402e40:	48 85 ff             	test   %rdi,%rdi
  402e43:	74 2c                	je     402e71 <driver_post+0x61>
  402e45:	80 3f 00             	cmpb   $0x0,(%rdi)
  402e48:	74 27                	je     402e71 <driver_post+0x61>
  402e4a:	48 83 ec 08          	sub    $0x8,%rsp
  402e4e:	41 51                	push   %r9
  402e50:	49 89 c9             	mov    %rcx,%r9
  402e53:	49 89 d0             	mov    %rdx,%r8
  402e56:	48 89 f9             	mov    %rdi,%rcx
  402e59:	48 89 f2             	mov    %rsi,%rdx
  402e5c:	be 8d 4b 00 00       	mov    $0x4b8d,%esi
  402e61:	bf 65 37 40 00       	mov    $0x403765,%edi
  402e66:	e8 19 f6 ff ff       	callq  402484 <submitr>
  402e6b:	48 83 c4 10          	add    $0x10,%rsp
  402e6f:	eb 0e                	jmp    402e7f <driver_post+0x6f>
  402e71:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  402e76:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  402e7a:	b8 00 00 00 00       	mov    $0x0,%eax
  402e7f:	5b                   	pop    %rbx
  402e80:	c3                   	retq   

0000000000402e81 <check>:
  402e81:	89 f8                	mov    %edi,%eax
  402e83:	c1 e8 1c             	shr    $0x1c,%eax
  402e86:	85 c0                	test   %eax,%eax
  402e88:	74 1d                	je     402ea7 <check+0x26>
  402e8a:	b9 00 00 00 00       	mov    $0x0,%ecx
  402e8f:	eb 0b                	jmp    402e9c <check+0x1b>
  402e91:	89 f8                	mov    %edi,%eax
  402e93:	d3 e8                	shr    %cl,%eax
  402e95:	3c 0a                	cmp    $0xa,%al
  402e97:	74 14                	je     402ead <check+0x2c>
  402e99:	83 c1 08             	add    $0x8,%ecx
  402e9c:	83 f9 1f             	cmp    $0x1f,%ecx
  402e9f:	7e f0                	jle    402e91 <check+0x10>
  402ea1:	b8 01 00 00 00       	mov    $0x1,%eax
  402ea6:	c3                   	retq   
  402ea7:	b8 00 00 00 00       	mov    $0x0,%eax
  402eac:	c3                   	retq   
  402ead:	b8 00 00 00 00       	mov    $0x0,%eax
  402eb2:	c3                   	retq   

0000000000402eb3 <gencookie>:
  402eb3:	53                   	push   %rbx
  402eb4:	83 c7 01             	add    $0x1,%edi
  402eb7:	e8 e4 dd ff ff       	callq  400ca0 <srandom@plt>
  402ebc:	e8 ff de ff ff       	callq  400dc0 <random@plt>
  402ec1:	89 c3                	mov    %eax,%ebx
  402ec3:	89 c7                	mov    %eax,%edi
  402ec5:	e8 b7 ff ff ff       	callq  402e81 <check>
  402eca:	85 c0                	test   %eax,%eax
  402ecc:	74 ee                	je     402ebc <gencookie+0x9>
  402ece:	89 d8                	mov    %ebx,%eax
  402ed0:	5b                   	pop    %rbx
  402ed1:	c3                   	retq   
  402ed2:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  402ed9:	00 00 00 
  402edc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000402ee0 <__libc_csu_init>:
  402ee0:	41 57                	push   %r15
  402ee2:	41 56                	push   %r14
  402ee4:	41 89 ff             	mov    %edi,%r15d
  402ee7:	41 55                	push   %r13
  402ee9:	41 54                	push   %r12
  402eeb:	4c 8d 25 1e 1f 20 00 	lea    0x201f1e(%rip),%r12        # 604e10 <__frame_dummy_init_array_entry>
  402ef2:	55                   	push   %rbp
  402ef3:	48 8d 2d 1e 1f 20 00 	lea    0x201f1e(%rip),%rbp        # 604e18 <__do_global_dtors_aux_fini_array_entry>
  402efa:	53                   	push   %rbx
  402efb:	49 89 f6             	mov    %rsi,%r14
  402efe:	49 89 d5             	mov    %rdx,%r13
  402f01:	4c 29 e5             	sub    %r12,%rbp
  402f04:	48 83 ec 08          	sub    $0x8,%rsp
  402f08:	48 c1 fd 03          	sar    $0x3,%rbp
  402f0c:	e8 37 dd ff ff       	callq  400c48 <_init>
  402f11:	48 85 ed             	test   %rbp,%rbp
  402f14:	74 20                	je     402f36 <__libc_csu_init+0x56>
  402f16:	31 db                	xor    %ebx,%ebx
  402f18:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  402f1f:	00 
  402f20:	4c 89 ea             	mov    %r13,%rdx
  402f23:	4c 89 f6             	mov    %r14,%rsi
  402f26:	44 89 ff             	mov    %r15d,%edi
  402f29:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  402f2d:	48 83 c3 01          	add    $0x1,%rbx
  402f31:	48 39 eb             	cmp    %rbp,%rbx
  402f34:	75 ea                	jne    402f20 <__libc_csu_init+0x40>
  402f36:	48 83 c4 08          	add    $0x8,%rsp
  402f3a:	5b                   	pop    %rbx
  402f3b:	5d                   	pop    %rbp
  402f3c:	41 5c                	pop    %r12
  402f3e:	41 5d                	pop    %r13
  402f40:	41 5e                	pop    %r14
  402f42:	41 5f                	pop    %r15
  402f44:	c3                   	retq   
  402f45:	90                   	nop
  402f46:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  402f4d:	00 00 00 

0000000000402f50 <__libc_csu_fini>:
  402f50:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000402f54 <_fini>:
  402f54:	48 83 ec 08          	sub    $0x8,%rsp
  402f58:	48 83 c4 08          	add    $0x8,%rsp
  402f5c:	c3                   	retq   
