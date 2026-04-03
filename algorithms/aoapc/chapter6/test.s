
test:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	callq  *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	retq   

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 62 2f 00 00    	pushq  0x2f62(%rip)        # 3f88 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 63 2f 00 00 	bnd jmpq *0x2f63(%rip)        # 3f90 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	pushq  $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmpq 1020 <.plt>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	pushq  $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmpq 1020 <.plt>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	pushq  $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmpq 1020 <.plt>
    105f:	90                   	nop
    1060:	f3 0f 1e fa          	endbr64 
    1064:	68 03 00 00 00       	pushq  $0x3
    1069:	f2 e9 b1 ff ff ff    	bnd jmpq 1020 <.plt>
    106f:	90                   	nop
    1070:	f3 0f 1e fa          	endbr64 
    1074:	68 04 00 00 00       	pushq  $0x4
    1079:	f2 e9 a1 ff ff ff    	bnd jmpq 1020 <.plt>
    107f:	90                   	nop
    1080:	f3 0f 1e fa          	endbr64 
    1084:	68 05 00 00 00       	pushq  $0x5
    1089:	f2 e9 91 ff ff ff    	bnd jmpq 1020 <.plt>
    108f:	90                   	nop

Disassembly of section .plt.got:

0000000000001090 <__cxa_finalize@plt>:
    1090:	f3 0f 1e fa          	endbr64 
    1094:	f2 ff 25 2d 2f 00 00 	bnd jmpq *0x2f2d(%rip)        # 3fc8 <__cxa_finalize@GLIBC_2.2.5>
    109b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

00000000000010a0 <__cxa_atexit@plt>:
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	f2 ff 25 ed 2e 00 00 	bnd jmpq *0x2eed(%rip)        # 3f98 <__cxa_atexit@GLIBC_2.2.5>
    10ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010b0 <_ZNSolsEPFRSoS_E@plt>:
    10b0:	f3 0f 1e fa          	endbr64 
    10b4:	f2 ff 25 e5 2e 00 00 	bnd jmpq *0x2ee5(%rip)        # 3fa0 <_ZNSolsEPFRSoS_E@GLIBCXX_3.4>
    10bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010c0 <__stack_chk_fail@plt>:
    10c0:	f3 0f 1e fa          	endbr64 
    10c4:	f2 ff 25 dd 2e 00 00 	bnd jmpq *0x2edd(%rip)        # 3fa8 <__stack_chk_fail@GLIBC_2.4>
    10cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010d0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@plt>:
    10d0:	f3 0f 1e fa          	endbr64 
    10d4:	f2 ff 25 d5 2e 00 00 	bnd jmpq *0x2ed5(%rip)        # 3fb0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@GLIBCXX_3.4>
    10db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010e0 <_ZNSt8ios_base4InitC1Ev@plt>:
    10e0:	f3 0f 1e fa          	endbr64 
    10e4:	f2 ff 25 cd 2e 00 00 	bnd jmpq *0x2ecd(%rip)        # 3fb8 <_ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4>
    10eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010f0 <_ZNSolsEi@plt>:
    10f0:	f3 0f 1e fa          	endbr64 
    10f4:	f2 ff 25 c5 2e 00 00 	bnd jmpq *0x2ec5(%rip)        # 3fc0 <_ZNSolsEi@GLIBCXX_3.4>
    10fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001100 <_start>:
    1100:	f3 0f 1e fa          	endbr64 
    1104:	31 ed                	xor    %ebp,%ebp
    1106:	49 89 d1             	mov    %rdx,%r9
    1109:	5e                   	pop    %rsi
    110a:	48 89 e2             	mov    %rsp,%rdx
    110d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1111:	50                   	push   %rax
    1112:	54                   	push   %rsp
    1113:	4c 8d 05 46 03 00 00 	lea    0x346(%rip),%r8        # 1460 <__libc_csu_fini>
    111a:	48 8d 0d cf 02 00 00 	lea    0x2cf(%rip),%rcx        # 13f0 <__libc_csu_init>
    1121:	48 8d 3d 9e 01 00 00 	lea    0x19e(%rip),%rdi        # 12c6 <main>
    1128:	ff 15 b2 2e 00 00    	callq  *0x2eb2(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    112e:	f4                   	hlt    
    112f:	90                   	nop

0000000000001130 <deregister_tm_clones>:
    1130:	48 8d 3d d9 2e 00 00 	lea    0x2ed9(%rip),%rdi        # 4010 <__TMC_END__>
    1137:	48 8d 05 d2 2e 00 00 	lea    0x2ed2(%rip),%rax        # 4010 <__TMC_END__>
    113e:	48 39 f8             	cmp    %rdi,%rax
    1141:	74 15                	je     1158 <deregister_tm_clones+0x28>
    1143:	48 8b 05 8e 2e 00 00 	mov    0x2e8e(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    114a:	48 85 c0             	test   %rax,%rax
    114d:	74 09                	je     1158 <deregister_tm_clones+0x28>
    114f:	ff e0                	jmpq   *%rax
    1151:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1158:	c3                   	retq   
    1159:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001160 <register_tm_clones>:
    1160:	48 8d 3d a9 2e 00 00 	lea    0x2ea9(%rip),%rdi        # 4010 <__TMC_END__>
    1167:	48 8d 35 a2 2e 00 00 	lea    0x2ea2(%rip),%rsi        # 4010 <__TMC_END__>
    116e:	48 29 fe             	sub    %rdi,%rsi
    1171:	48 89 f0             	mov    %rsi,%rax
    1174:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1178:	48 c1 f8 03          	sar    $0x3,%rax
    117c:	48 01 c6             	add    %rax,%rsi
    117f:	48 d1 fe             	sar    %rsi
    1182:	74 14                	je     1198 <register_tm_clones+0x38>
    1184:	48 8b 05 65 2e 00 00 	mov    0x2e65(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    118b:	48 85 c0             	test   %rax,%rax
    118e:	74 08                	je     1198 <register_tm_clones+0x38>
    1190:	ff e0                	jmpq   *%rax
    1192:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1198:	c3                   	retq   
    1199:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011a0 <__do_global_dtors_aux>:
    11a0:	f3 0f 1e fa          	endbr64 
    11a4:	80 3d a5 2f 00 00 00 	cmpb   $0x0,0x2fa5(%rip)        # 4150 <completed.8060>
    11ab:	75 2b                	jne    11d8 <__do_global_dtors_aux+0x38>
    11ad:	55                   	push   %rbp
    11ae:	48 83 3d 12 2e 00 00 	cmpq   $0x0,0x2e12(%rip)        # 3fc8 <__cxa_finalize@GLIBC_2.2.5>
    11b5:	00 
    11b6:	48 89 e5             	mov    %rsp,%rbp
    11b9:	74 0c                	je     11c7 <__do_global_dtors_aux+0x27>
    11bb:	48 8b 3d 46 2e 00 00 	mov    0x2e46(%rip),%rdi        # 4008 <__dso_handle>
    11c2:	e8 c9 fe ff ff       	callq  1090 <__cxa_finalize@plt>
    11c7:	e8 64 ff ff ff       	callq  1130 <deregister_tm_clones>
    11cc:	c6 05 7d 2f 00 00 01 	movb   $0x1,0x2f7d(%rip)        # 4150 <completed.8060>
    11d3:	5d                   	pop    %rbp
    11d4:	c3                   	retq   
    11d5:	0f 1f 00             	nopl   (%rax)
    11d8:	c3                   	retq   
    11d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011e0 <frame_dummy>:
    11e0:	f3 0f 1e fa          	endbr64 
    11e4:	e9 77 ff ff ff       	jmpq   1160 <register_tm_clones>

00000000000011e9 <_Z4swapRiS_>:
    11e9:	f3 0f 1e fa          	endbr64 
    11ed:	55                   	push   %rbp
    11ee:	48 89 e5             	mov    %rsp,%rbp
    11f1:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    11f5:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    11f9:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    11fd:	8b 00                	mov    (%rax),%eax
    11ff:	89 45 fc             	mov    %eax,-0x4(%rbp)
    1202:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1206:	8b 10                	mov    (%rax),%edx
    1208:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    120c:	89 10                	mov    %edx,(%rax)
    120e:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1212:	8b 55 fc             	mov    -0x4(%rbp),%edx
    1215:	89 10                	mov    %edx,(%rax)
    1217:	90                   	nop
    1218:	5d                   	pop    %rbp
    1219:	c3                   	retq   

000000000000121a <_Z4sortPii>:
    121a:	f3 0f 1e fa          	endbr64 
    121e:	55                   	push   %rbp
    121f:	48 89 e5             	mov    %rsp,%rbp
    1222:	48 83 ec 20          	sub    $0x20,%rsp
    1226:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    122a:	89 75 e4             	mov    %esi,-0x1c(%rbp)
    122d:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
    1234:	8b 45 f8             	mov    -0x8(%rbp),%eax
    1237:	3b 45 e4             	cmp    -0x1c(%rbp),%eax
    123a:	0f 8d 83 00 00 00    	jge    12c3 <_Z4sortPii+0xa9>
    1240:	8b 45 e4             	mov    -0x1c(%rbp),%eax
    1243:	83 e8 01             	sub    $0x1,%eax
    1246:	89 45 fc             	mov    %eax,-0x4(%rbp)
    1249:	8b 45 fc             	mov    -0x4(%rbp),%eax
    124c:	3b 45 f8             	cmp    -0x8(%rbp),%eax
    124f:	7e 69                	jle    12ba <_Z4sortPii+0xa0>
    1251:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1254:	48 98                	cltq   
    1256:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    125d:	00 
    125e:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1262:	48 01 d0             	add    %rdx,%rax
    1265:	8b 10                	mov    (%rax),%edx
    1267:	8b 45 fc             	mov    -0x4(%rbp),%eax
    126a:	48 98                	cltq   
    126c:	48 c1 e0 02          	shl    $0x2,%rax
    1270:	48 8d 48 fc          	lea    -0x4(%rax),%rcx
    1274:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1278:	48 01 c8             	add    %rcx,%rax
    127b:	8b 00                	mov    (%rax),%eax
    127d:	39 c2                	cmp    %eax,%edx
    127f:	7e 33                	jle    12b4 <_Z4sortPii+0x9a>
    1281:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1284:	48 98                	cltq   
    1286:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    128d:	00 
    128e:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1292:	48 01 c2             	add    %rax,%rdx
    1295:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1298:	48 98                	cltq   
    129a:	48 c1 e0 02          	shl    $0x2,%rax
    129e:	48 8d 48 fc          	lea    -0x4(%rax),%rcx
    12a2:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    12a6:	48 01 c8             	add    %rcx,%rax
    12a9:	48 89 d6             	mov    %rdx,%rsi
    12ac:	48 89 c7             	mov    %rax,%rdi
    12af:	e8 35 ff ff ff       	callq  11e9 <_Z4swapRiS_>
    12b4:	83 6d fc 01          	subl   $0x1,-0x4(%rbp)
    12b8:	eb 8f                	jmp    1249 <_Z4sortPii+0x2f>
    12ba:	83 45 f8 01          	addl   $0x1,-0x8(%rbp)
    12be:	e9 71 ff ff ff       	jmpq   1234 <_Z4sortPii+0x1a>
    12c3:	90                   	nop
    12c4:	c9                   	leaveq 
    12c5:	c3                   	retq   

00000000000012c6 <main>:
    12c6:	f3 0f 1e fa          	endbr64 
    12ca:	55                   	push   %rbp
    12cb:	48 89 e5             	mov    %rsp,%rbp
    12ce:	48 83 ec 30          	sub    $0x30,%rsp
    12d2:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    12d9:	00 00 
    12db:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    12df:	31 c0                	xor    %eax,%eax
    12e1:	c7 45 e0 01 00 00 00 	movl   $0x1,-0x20(%rbp)
    12e8:	c7 45 e4 02 00 00 00 	movl   $0x2,-0x1c(%rbp)
    12ef:	c7 45 e8 03 00 00 00 	movl   $0x3,-0x18(%rbp)
    12f6:	c7 45 ec 04 00 00 00 	movl   $0x4,-0x14(%rbp)
    12fd:	c7 45 f0 05 00 00 00 	movl   $0x5,-0x10(%rbp)
    1304:	c7 45 dc 05 00 00 00 	movl   $0x5,-0x24(%rbp)
    130b:	8b 55 dc             	mov    -0x24(%rbp),%edx
    130e:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
    1312:	89 d6                	mov    %edx,%esi
    1314:	48 89 c7             	mov    %rax,%rdi
    1317:	e8 fe fe ff ff       	callq  121a <_Z4sortPii>
    131c:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
    1323:	8b 45 d8             	mov    -0x28(%rbp),%eax
    1326:	3b 45 dc             	cmp    -0x24(%rbp),%eax
    1329:	7d 2a                	jge    1355 <main+0x8f>
    132b:	8b 45 d8             	mov    -0x28(%rbp),%eax
    132e:	48 98                	cltq   
    1330:	8b 44 85 e0          	mov    -0x20(%rbp,%rax,4),%eax
    1334:	89 c6                	mov    %eax,%esi
    1336:	48 8d 3d 03 2d 00 00 	lea    0x2d03(%rip),%rdi        # 4040 <_ZSt4cout@@GLIBCXX_3.4>
    133d:	e8 ae fd ff ff       	callq  10f0 <_ZNSolsEi@plt>
    1342:	be 20 00 00 00       	mov    $0x20,%esi
    1347:	48 89 c7             	mov    %rax,%rdi
    134a:	e8 81 fd ff ff       	callq  10d0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@plt>
    134f:	83 45 d8 01          	addl   $0x1,-0x28(%rbp)
    1353:	eb ce                	jmp    1323 <main+0x5d>
    1355:	48 8b 05 74 2c 00 00 	mov    0x2c74(%rip),%rax        # 3fd0 <_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GLIBCXX_3.4>
    135c:	48 89 c6             	mov    %rax,%rsi
    135f:	48 8d 3d da 2c 00 00 	lea    0x2cda(%rip),%rdi        # 4040 <_ZSt4cout@@GLIBCXX_3.4>
    1366:	e8 45 fd ff ff       	callq  10b0 <_ZNSolsEPFRSoS_E@plt>
    136b:	b8 00 00 00 00       	mov    $0x0,%eax
    1370:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
    1374:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
    137b:	00 00 
    137d:	74 05                	je     1384 <main+0xbe>
    137f:	e8 3c fd ff ff       	callq  10c0 <__stack_chk_fail@plt>
    1384:	c9                   	leaveq 
    1385:	c3                   	retq   

0000000000001386 <_Z41__static_initialization_and_destruction_0ii>:
    1386:	f3 0f 1e fa          	endbr64 
    138a:	55                   	push   %rbp
    138b:	48 89 e5             	mov    %rsp,%rbp
    138e:	48 83 ec 10          	sub    $0x10,%rsp
    1392:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1395:	89 75 f8             	mov    %esi,-0x8(%rbp)
    1398:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
    139c:	75 32                	jne    13d0 <_Z41__static_initialization_and_destruction_0ii+0x4a>
    139e:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
    13a5:	75 29                	jne    13d0 <_Z41__static_initialization_and_destruction_0ii+0x4a>
    13a7:	48 8d 3d a3 2d 00 00 	lea    0x2da3(%rip),%rdi        # 4151 <_ZStL8__ioinit>
    13ae:	e8 2d fd ff ff       	callq  10e0 <_ZNSt8ios_base4InitC1Ev@plt>
    13b3:	48 8d 15 4e 2c 00 00 	lea    0x2c4e(%rip),%rdx        # 4008 <__dso_handle>
    13ba:	48 8d 35 90 2d 00 00 	lea    0x2d90(%rip),%rsi        # 4151 <_ZStL8__ioinit>
    13c1:	48 8b 05 30 2c 00 00 	mov    0x2c30(%rip),%rax        # 3ff8 <_ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4>
    13c8:	48 89 c7             	mov    %rax,%rdi
    13cb:	e8 d0 fc ff ff       	callq  10a0 <__cxa_atexit@plt>
    13d0:	90                   	nop
    13d1:	c9                   	leaveq 
    13d2:	c3                   	retq   

00000000000013d3 <_GLOBAL__sub_I__Z4swapRiS_>:
    13d3:	f3 0f 1e fa          	endbr64 
    13d7:	55                   	push   %rbp
    13d8:	48 89 e5             	mov    %rsp,%rbp
    13db:	be ff ff 00 00       	mov    $0xffff,%esi
    13e0:	bf 01 00 00 00       	mov    $0x1,%edi
    13e5:	e8 9c ff ff ff       	callq  1386 <_Z41__static_initialization_and_destruction_0ii>
    13ea:	5d                   	pop    %rbp
    13eb:	c3                   	retq   
    13ec:	0f 1f 40 00          	nopl   0x0(%rax)

00000000000013f0 <__libc_csu_init>:
    13f0:	f3 0f 1e fa          	endbr64 
    13f4:	41 57                	push   %r15
    13f6:	4c 8d 3d 6b 29 00 00 	lea    0x296b(%rip),%r15        # 3d68 <__frame_dummy_init_array_entry>
    13fd:	41 56                	push   %r14
    13ff:	49 89 d6             	mov    %rdx,%r14
    1402:	41 55                	push   %r13
    1404:	49 89 f5             	mov    %rsi,%r13
    1407:	41 54                	push   %r12
    1409:	41 89 fc             	mov    %edi,%r12d
    140c:	55                   	push   %rbp
    140d:	48 8d 2d 64 29 00 00 	lea    0x2964(%rip),%rbp        # 3d78 <__do_global_dtors_aux_fini_array_entry>
    1414:	53                   	push   %rbx
    1415:	4c 29 fd             	sub    %r15,%rbp
    1418:	48 83 ec 08          	sub    $0x8,%rsp
    141c:	e8 df fb ff ff       	callq  1000 <_init>
    1421:	48 c1 fd 03          	sar    $0x3,%rbp
    1425:	74 1f                	je     1446 <__libc_csu_init+0x56>
    1427:	31 db                	xor    %ebx,%ebx
    1429:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1430:	4c 89 f2             	mov    %r14,%rdx
    1433:	4c 89 ee             	mov    %r13,%rsi
    1436:	44 89 e7             	mov    %r12d,%edi
    1439:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    143d:	48 83 c3 01          	add    $0x1,%rbx
    1441:	48 39 dd             	cmp    %rbx,%rbp
    1444:	75 ea                	jne    1430 <__libc_csu_init+0x40>
    1446:	48 83 c4 08          	add    $0x8,%rsp
    144a:	5b                   	pop    %rbx
    144b:	5d                   	pop    %rbp
    144c:	41 5c                	pop    %r12
    144e:	41 5d                	pop    %r13
    1450:	41 5e                	pop    %r14
    1452:	41 5f                	pop    %r15
    1454:	c3                   	retq   
    1455:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    145c:	00 00 00 00 

0000000000001460 <__libc_csu_fini>:
    1460:	f3 0f 1e fa          	endbr64 
    1464:	c3                   	retq   

Disassembly of section .fini:

0000000000001468 <_fini>:
    1468:	f3 0f 1e fa          	endbr64 
    146c:	48 83 ec 08          	sub    $0x8,%rsp
    1470:	48 83 c4 08          	add    $0x8,%rsp
    1474:	c3                   	retq   
