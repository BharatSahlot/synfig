Dump of assembler code for function _ZN6synfig18blendfunc_MULTIPLYINS_5ColorEEET_RS2_S3_f:
=> 0x00007ffff78d1930 <+0>:	movaps %xmm0,%xmm2
   0x00007ffff78d1933 <+3>:	pxor   %xmm0,%xmm0
   0x00007ffff78d1937 <+7>:	movss  0xc(%rdi),%xmm3
   0x00007ffff78d193c <+12>:	mov    %rdi,%rdx
   0x00007ffff78d193f <+15>:	comiss %xmm2,%xmm0
   0x00007ffff78d1942 <+18>:	mov    %rsi,%rax
   0x00007ffff78d1945 <+21>:	jbe    0x7ffff78d1976 <_ZN6synfig18blendfunc_MULTIPLYINS_5ColorEEET_RS2_S3_f+70>
   0x00007ffff78d1947 <+23>:	movss  0x598a79(%rip),%xmm0        # 0x7ffff7e6a3c8
   0x00007ffff78d194f <+31>:	xorps  0x599caa(%rip),%xmm2        # 0x7ffff7e6b600
   0x00007ffff78d1956 <+38>:	movaps %xmm0,%xmm1
   0x00007ffff78d1959 <+41>:	movaps %xmm0,%xmm4
   0x00007ffff78d195c <+44>:	subss  (%rdi),%xmm1
   0x00007ffff78d1960 <+48>:	subss  0x4(%rdi),%xmm4
   0x00007ffff78d1965 <+53>:	subss  0x8(%rdi),%xmm0
   0x00007ffff78d196a <+58>:	unpcklps %xmm4,%xmm1
   0x00007ffff78d196d <+61>:	unpcklps %xmm3,%xmm0
   0x00007ffff78d1970 <+64>:	movlhps %xmm0,%xmm1
   0x00007ffff78d1973 <+67>:	movups %xmm1,(%rdi)
   0x00007ffff78d1976 <+70>:	lea    0x4(%rdx),%rcx
   0x00007ffff78d197a <+74>:	mulss  %xmm3,%xmm2
   0x00007ffff78d197e <+78>:	cmp    %rcx,%rax
   0x00007ffff78d1981 <+81>:	je     0x7ffff78d19d8 <_ZN6synfig18blendfunc_MULTIPLYINS_5ColorEEET_RS2_S3_f+168>
   0x00007ffff78d1983 <+83>:	movq   (%rax),%xmm0
   0x00007ffff78d1987 <+87>:	movq   (%rdx),%xmm1
   0x00007ffff78d198b <+91>:	movaps %xmm2,%xmm3
   0x00007ffff78d198e <+94>:	shufps $0xe0,%xmm3,%xmm3
   0x00007ffff78d1992 <+98>:	mulps  %xmm0,%xmm1
   0x00007ffff78d1995 <+101>:	subps  %xmm0,%xmm1
   0x00007ffff78d1998 <+104>:	mulps  %xmm3,%xmm1
   0x00007ffff78d199b <+107>:	addps  %xmm0,%xmm1
   0x00007ffff78d199e <+110>:	movlps %xmm1,(%rax)
   0x00007ffff78d19a1 <+113>:	movss  0x8(%rax),%xmm1
   0x00007ffff78d19a6 <+118>:	movss  0x8(%rdx),%xmm0
   0x00007ffff78d19ab <+123>:	mov    (%rax),%rdx
   0x00007ffff78d19ae <+126>:	mulss  %xmm1,%xmm0
   0x00007ffff78d19b2 <+130>:	subss  %xmm1,%xmm0
   0x00007ffff78d19b6 <+134>:	mulss  %xmm2,%xmm0
   0x00007ffff78d19ba <+138>:	addss  %xmm1,%xmm0
   0x00007ffff78d19be <+142>:	movss  %xmm0,0x8(%rax)
   0x00007ffff78d19c3 <+147>:	mov    0x8(%rax),%rax
   0x00007ffff78d19c7 <+151>:	movq   %rdx,%xmm0
   0x00007ffff78d19cc <+156>:	movq   %rax,%xmm1
   0x00007ffff78d19d1 <+161>:	ret    
   0x00007ffff78d19d2 <+162>:	nopw   0x0(%rax,%rax,1)
   0x00007ffff78d19d8 <+168>:	movss  (%rax),%xmm1
   0x00007ffff78d19dc <+172>:	movss  (%rdx),%xmm0
   0x00007ffff78d19e0 <+176>:	mulss  %xmm1,%xmm0
   0x00007ffff78d19e4 <+180>:	subss  %xmm1,%xmm0
   0x00007ffff78d19e8 <+184>:	mulss  %xmm2,%xmm0
   0x00007ffff78d19ec <+188>:	addss  %xmm1,%xmm0
   0x00007ffff78d19f0 <+192>:	movss  0x4(%rax),%xmm1
   0x00007ffff78d19f5 <+197>:	movss  %xmm0,(%rax)
   0x00007ffff78d19f9 <+201>:	movss  0x4(%rdx),%xmm0
   0x00007ffff78d19fe <+206>:	mulss  %xmm1,%xmm0
   0x00007ffff78d1a02 <+210>:	subss  %xmm1,%xmm0
   0x00007ffff78d1a06 <+214>:	mulss  %xmm2,%xmm0
   0x00007ffff78d1a0a <+218>:	addss  %xmm1,%xmm0
   0x00007ffff78d1a0e <+222>:	movss  %xmm0,0x4(%rax)
   0x00007ffff78d1a13 <+227>:	jmp    0x7ffff78d19a1 <_ZN6synfig18blendfunc_MULTIPLYINS_5ColorEEET_RS2_S3_f+113>
