Dump of assembler code for function _ZN6synfig18blendfunc_MULTIPLYINS_5ColorEEET_RS2_S3_f:
=> 0x00007ffff78d1930 <+0>:	pxor   %xmm2,%xmm2
   0x00007ffff78d1934 <+4>:	movss  0xc(%rdi),%xmm3
   0x00007ffff78d1939 <+9>:	movss  (%rdi),%xmm1
   0x00007ffff78d193d <+13>:	mov    %rdi,%rdx
   0x00007ffff78d1940 <+16>:	comiss %xmm0,%xmm2
   0x00007ffff78d1943 <+19>:	mov    %rsi,%rax
   0x00007ffff78d1946 <+22>:	jbe    0x7ffff78d197d <_ZN6synfig18blendfunc_MULTIPLYINS_5ColorEEET_RS2_S3_f+77>
   0x00007ffff78d1948 <+24>:	movss  0x598a78(%rip),%xmm2        # 0x7ffff7e6a3c8
   0x00007ffff78d1950 <+32>:	xorps  0x599ca9(%rip),%xmm0        # 0x7ffff7e6b600
   0x00007ffff78d1957 <+39>:	movaps %xmm2,%xmm6
   0x00007ffff78d195a <+42>:	movaps %xmm2,%xmm5
   0x00007ffff78d195d <+45>:	subss  0x8(%rdi),%xmm2
   0x00007ffff78d1962 <+50>:	subss  %xmm1,%xmm6
   0x00007ffff78d1966 <+54>:	subss  0x4(%rdi),%xmm5
   0x00007ffff78d196b <+59>:	unpcklps %xmm3,%xmm2
   0x00007ffff78d196e <+62>:	movaps %xmm6,%xmm4
   0x00007ffff78d1971 <+65>:	movaps %xmm6,%xmm1
   0x00007ffff78d1974 <+68>:	unpcklps %xmm5,%xmm4
   0x00007ffff78d1977 <+71>:	movlhps %xmm2,%xmm4
   0x00007ffff78d197a <+74>:	movups %xmm4,(%rdi)
   0x00007ffff78d197d <+77>:	movss  (%rax),%xmm2
   0x00007ffff78d1981 <+81>:	mulss  %xmm3,%xmm0
   0x00007ffff78d1985 <+85>:	mulss  %xmm2,%xmm1
   0x00007ffff78d1989 <+89>:	subss  %xmm2,%xmm1
   0x00007ffff78d198d <+93>:	mulss  %xmm0,%xmm1
   0x00007ffff78d1991 <+97>:	addss  %xmm2,%xmm1
   0x00007ffff78d1995 <+101>:	movss  0x4(%rax),%xmm2
   0x00007ffff78d199a <+106>:	movss  %xmm1,(%rax)
   0x00007ffff78d199e <+110>:	movss  0x4(%rdx),%xmm1
   0x00007ffff78d19a3 <+115>:	mulss  %xmm2,%xmm1
   0x00007ffff78d19a7 <+119>:	subss  %xmm2,%xmm1
   0x00007ffff78d19ab <+123>:	mulss  %xmm0,%xmm1
   0x00007ffff78d19af <+127>:	addss  %xmm2,%xmm1
   0x00007ffff78d19b3 <+131>:	movss  0x8(%rax),%xmm2
   0x00007ffff78d19b8 <+136>:	movss  %xmm1,0x4(%rax)
   0x00007ffff78d19bd <+141>:	movss  0x8(%rdx),%xmm1
   0x00007ffff78d19c2 <+146>:	mov    (%rax),%rdx
   0x00007ffff78d19c5 <+149>:	mulss  %xmm2,%xmm1
   0x00007ffff78d19c9 <+153>:	subss  %xmm2,%xmm1
   0x00007ffff78d19cd <+157>:	mulss  %xmm1,%xmm0
   0x00007ffff78d19d1 <+161>:	addss  %xmm2,%xmm0
   0x00007ffff78d19d5 <+165>:	movss  %xmm0,0x8(%rax)
   0x00007ffff78d19da <+170>:	mov    0x8(%rax),%rax
   0x00007ffff78d19de <+174>:	movq   %rdx,%xmm0
   0x00007ffff78d19e3 <+179>:	movq   %rax,%xmm1
   0x00007ffff78d19e8 <+184>:	ret    
