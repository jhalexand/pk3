
lib/libpkphysics.so:     file format elf32-sparc


Disassembly of section .text:

00002d58 <__0oSPKPhysicsInterfacectv-0x10>:
    2d58:	00 01 00 00 	unimp  0x10000
    2d5c:	00 01 00 00 	unimp  0x10000
    2d60:	00 01 00 00 	unimp  0x10000
    2d64:	00 01 00 00 	unimp  0x10000

00002d68 <__0oSPKPhysicsInterfacectv>:
    2d68:	9d e3 bf a0 	save  %sp, -96, %sp
    2d6c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
    2d70:	21 00 00 00 	sethi  %hi(0), %l0
    2d74:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    2d78:	e2 04 20 00 	ld  [ %l0 ], %l1
    2d7c:	e0 07 a0 44 	ld  [ %fp + 0x44 ], %l0
    2d80:	e2 24 20 00 	st  %l1, [ %l0 ]
    2d84:	81 c7 e0 08 	ret 
    2d88:	81 e8 00 00 	restore 
    2d8c:	00 01 00 00 	unimp  0x10000
    2d90:	00 01 00 00 	unimp  0x10000
    2d94:	00 01 00 00 	unimp  0x10000
    2d98:	00 01 00 00 	unimp  0x10000
    2d9c:	00 01 00 00 	unimp  0x10000

00002da0 <__0oSPKPhysicsInterfacedtv>:
    2da0:	9d e3 bf a0 	save  %sp, -96, %sp
    2da4:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
    2da8:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
    2dac:	e2 07 a0 44 	ld  [ %fp + 0x44 ], %l1
    2db0:	a0 10 20 00 	clr  %l0
    2db4:	80 a4 40 10 	cmp  %l1, %l0
    2db8:	12 80 00 04 	bne  2dc8 <__0oSPKPhysicsInterfacedtv+0x28>
    2dbc:	01 00 00 00 	nop 
    2dc0:	10 80 00 12 	b  2e08 <__0oSPKPhysicsInterfacedtv+0x68>
    2dc4:	01 00 00 00 	nop 
    2dc8:	21 00 00 00 	sethi  %hi(0), %l0
    2dcc:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    2dd0:	e2 04 20 00 	ld  [ %l0 ], %l1
    2dd4:	e0 07 a0 44 	ld  [ %fp + 0x44 ], %l0
    2dd8:	e2 24 20 00 	st  %l1, [ %l0 ]
    2ddc:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    2de0:	a0 0c 20 01 	and  %l0, 1, %l0
    2de4:	80 a4 20 00 	cmp  %l0, 0
    2de8:	02 80 00 08 	be  2e08 <__0oSPKPhysicsInterfacedtv+0x68>
    2dec:	01 00 00 00 	nop 
    2df0:	e0 07 a0 44 	ld  [ %fp + 0x44 ], %l0
    2df4:	90 14 00 00 	mov  %l0, %o0
    2df8:	40 00 00 00 	call  2df8 <__0oSPKPhysicsInterfacedtv+0x58>
    2dfc:	01 00 00 00 	nop 
    2e00:	10 80 00 02 	b  2e08 <__0oSPKPhysicsInterfacedtv+0x68>
    2e04:	01 00 00 00 	nop 
    2e08:	81 c7 e0 08 	ret 
    2e0c:	81 e8 00 00 	restore 
    2e10:	00 01 00 00 	unimp  0x10000
    2e14:	00 01 00 00 	unimp  0x10000
    2e18:	00 01 00 00 	unimp  0x10000
    2e1c:	00 01 00 00 	unimp  0x10000

00002e20 <__0fSPKPhysicsInterfaceGupdateP6MGEGameObject>:
    2e20:	9d e3 bf 18 	save  %sp, -232, %sp
    2e24:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
    2e28:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
    2e2c:	40 00 00 00 	call  2e2c <__0fSPKPhysicsInterfaceGupdateP6MGEGameObject+0xc>
    2e30:	01 00 00 00 	nop 
    2e34:	a2 12 40 00 	mov  %o1, %l1
    2e38:	a0 12 00 00 	mov  %o0, %l0
    2e3c:	e0 3f bf f0 	std  %l0, [ %fp + -16 ]
    2e40:	a2 07 bf d0 	add  %fp, -48, %l1
    2e44:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    2e48:	90 14 00 00 	mov  %l0, %o0
    2e4c:	40 00 06 75 	call  4820 <__0fIPKObjectLgetPositionvK>
    2e50:	01 00 00 00 	nop 
    2e54:	a0 12 00 00 	mov  %o0, %l0
    2e58:	90 14 40 00 	mov  %l1, %o0
    2e5c:	92 14 00 00 	mov  %l0, %o1
    2e60:	40 00 06 44 	call  4770 <__0oHPKPointctRC6HPKPoint>
    2e64:	01 00 00 00 	nop 
    2e68:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    2e6c:	90 14 00 00 	mov  %l0, %o0
    2e70:	40 00 06 2e 	call  4728 <__0fMGEGameObjectMgetTimeStampvK>
    2e74:	01 00 00 00 	nop 
    2e78:	a2 12 40 00 	mov  %o1, %l1
    2e7c:	a0 12 00 00 	mov  %o0, %l0
    2e80:	e0 3f bf 88 	std  %l0, [ %fp + -120 ]
    2e84:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    2e88:	90 14 00 00 	mov  %l0, %o0
    2e8c:	40 00 06 17 	call  46e8 <__0fIPKObjectJgetVectorvK>
    2e90:	01 00 00 00 	nop 
    2e94:	a0 12 00 00 	mov  %o0, %l0
    2e98:	e0 27 bf 84 	st  %l0, [ %fp + -124 ]
    2e9c:	aa 07 bf b0 	add  %fp, -80, %l5
    2ea0:	e0 1f bf f0 	ldd  [ %fp + -16 ], %l0
    2ea4:	e4 1f bf 88 	ldd  [ %fp + -120 ], %l2
    2ea8:	a6 a4 40 13 	subcc  %l1, %l3, %l3
    2eac:	a4 64 00 12 	subx  %l0, %l2, %l2
    2eb0:	a0 14 80 00 	mov  %l2, %l0
    2eb4:	e0 27 bf 80 	st  %l0, [ %fp + -128 ]
    2eb8:	c5 07 bf 80 	ld  [ %fp + -128 ], %f2
    2ebc:	89 a0 19 02 	fitod  %f2, %f4
    2ec0:	21 00 00 00 	sethi  %hi(0), %l0
    2ec4:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    2ec8:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    2ecc:	8d a1 09 42 	fmuld  %f4, %f2, %f6
    2ed0:	a2 14 c0 00 	mov  %l3, %l1
    2ed4:	21 10 cc 00 	sethi  %hi(0x43300000), %l0
    2ed8:	e0 27 bf 78 	st  %l0, [ %fp + -136 ]
    2edc:	e2 27 bf 7c 	st  %l1, [ %fp + -132 ]
    2ee0:	c9 1f bf 78 	ldd  [ %fp + -136 ], %f4
    2ee4:	a0 10 20 00 	clr  %l0
    2ee8:	e0 27 bf 7c 	st  %l0, [ %fp + -132 ]
    2eec:	c5 1f bf 78 	ldd  [ %fp + -136 ], %f2
    2ef0:	85 a1 08 c2 	fsubd  %f4, %f2, %f2
    2ef4:	89 a1 88 42 	faddd  %f6, %f2, %f4
    2ef8:	21 00 00 00 	sethi  %hi(0), %l0
    2efc:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    2f00:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    2f04:	85 a1 09 42 	fmuld  %f4, %f2, %f2
    2f08:	e0 07 bf 84 	ld  [ %fp + -124 ], %l0
    2f0c:	90 15 40 00 	mov  %l5, %o0
    2f10:	c5 3b a0 58 	std  %f2, [ %sp + 0x58 ]
    2f14:	d2 03 a0 58 	ld  [ %sp + 0x58 ], %o1
    2f18:	d4 03 a0 5c 	ld  [ %sp + 0x5c ], %o2
    2f1c:	96 14 00 00 	mov  %l0, %o3
    2f20:	40 00 05 c8 	call  4640 <__0OmldRC6IPKVector>
    2f24:	01 00 00 00 	nop 
    2f28:	a0 07 bf 90 	add  %fp, -112, %l0
    2f2c:	a2 07 bf d0 	add  %fp, -48, %l1
    2f30:	a4 07 bf b0 	add  %fp, -80, %l2
    2f34:	90 14 00 00 	mov  %l0, %o0
    2f38:	92 14 40 00 	mov  %l1, %o1
    2f3c:	94 14 80 00 	mov  %l2, %o2
    2f40:	40 00 05 ac 	call  45f0 <__0OplRC6HPKPointRC6IPKVector>
    2f44:	01 00 00 00 	nop 
    2f48:	a0 07 bf d0 	add  %fp, -48, %l0
    2f4c:	a2 07 bf 90 	add  %fp, -112, %l1
    2f50:	90 14 00 00 	mov  %l0, %o0
    2f54:	92 14 40 00 	mov  %l1, %o1
    2f58:	40 00 05 74 	call  4528 <__0oHPKPointasRC6HPKPoint>
    2f5c:	01 00 00 00 	nop 
    2f60:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    2f64:	a2 07 bf d0 	add  %fp, -48, %l1
    2f68:	90 14 00 00 	mov  %l0, %o0
    2f6c:	92 14 40 00 	mov  %l1, %o1
    2f70:	40 00 05 5e 	call  44e8 <__0fIPKObjectLsetPositionRC6HPKPoint>
    2f74:	01 00 00 00 	nop 
    2f78:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    2f7c:	e4 1f bf f0 	ldd  [ %fp + -16 ], %l2
    2f80:	90 14 00 00 	mov  %l0, %o0
    2f84:	92 14 80 00 	mov  %l2, %o1
    2f88:	94 14 c0 00 	mov  %l3, %o2
    2f8c:	40 00 05 47 	call  44a8 <__0fMGEGameObjectMsetTimeStampL>
    2f90:	01 00 00 00 	nop 
    2f94:	a0 07 bf 90 	add  %fp, -112, %l0
    2f98:	a2 10 20 02 	mov  2, %l1
    2f9c:	90 14 00 00 	mov  %l0, %o0
    2fa0:	92 14 40 00 	mov  %l1, %o1
    2fa4:	40 00 05 25 	call  4438 <__0oHPKPointdtv>
    2fa8:	01 00 00 00 	nop 
    2fac:	a0 07 bf b0 	add  %fp, -80, %l0
    2fb0:	a2 10 20 02 	mov  2, %l1
    2fb4:	90 14 00 00 	mov  %l0, %o0
    2fb8:	92 14 40 00 	mov  %l1, %o1
    2fbc:	40 00 05 03 	call  43c8 <__0oIPKVectordtv>
    2fc0:	01 00 00 00 	nop 
    2fc4:	a0 07 bf d0 	add  %fp, -48, %l0
    2fc8:	a2 10 20 02 	mov  2, %l1
    2fcc:	90 14 00 00 	mov  %l0, %o0
    2fd0:	92 14 40 00 	mov  %l1, %o1
    2fd4:	40 00 05 19 	call  4438 <__0oHPKPointdtv>
    2fd8:	01 00 00 00 	nop 
    2fdc:	10 80 00 16 	b  3034 <__0fSPKPhysicsInterfaceGupdateP6MGEGameObject+0x214>
    2fe0:	01 00 00 00 	nop 
    2fe4:	a0 07 bf 90 	add  %fp, -112, %l0
    2fe8:	a2 10 20 02 	mov  2, %l1
    2fec:	90 14 00 00 	mov  %l0, %o0
    2ff0:	92 14 40 00 	mov  %l1, %o1
    2ff4:	40 00 05 11 	call  4438 <__0oHPKPointdtv>
    2ff8:	01 00 00 00 	nop 
    2ffc:	a0 07 bf b0 	add  %fp, -80, %l0
    3000:	a2 10 20 02 	mov  2, %l1
    3004:	90 14 00 00 	mov  %l0, %o0
    3008:	92 14 40 00 	mov  %l1, %o1
    300c:	40 00 04 ef 	call  43c8 <__0oIPKVectordtv>
    3010:	01 00 00 00 	nop 
    3014:	a0 07 bf d0 	add  %fp, -48, %l0
    3018:	a2 10 20 02 	mov  2, %l1
    301c:	90 14 00 00 	mov  %l0, %o0
    3020:	92 14 40 00 	mov  %l1, %o1
    3024:	40 00 05 05 	call  4438 <__0oHPKPointdtv>
    3028:	01 00 00 00 	nop 
    302c:	40 00 00 00 	call  302c <__0fSPKPhysicsInterfaceGupdateP6MGEGameObject+0x20c>
    3030:	01 00 00 00 	nop 
    3034:	81 c7 e0 08 	ret 
    3038:	81 e8 00 00 	restore 
    303c:	00 01 00 00 	unimp  0x10000
    3040:	00 01 00 00 	unimp  0x10000
    3044:	00 01 00 00 	unimp  0x10000
    3048:	00 01 00 00 	unimp  0x10000
    304c:	00 01 00 00 	unimp  0x10000

00003050 <__0fSPKPhysicsInterfaceJintersectP6MGEGameObjectTB>:
    3050:	9d e3 be 88 	save  %sp, -376, %sp
    3054:	f4 27 a0 4c 	st  %i2, [ %fp + 0x4c ]
    3058:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
    305c:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
    3060:	a2 07 bf 78 	add  %fp, -136, %l1
    3064:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    3068:	90 14 00 00 	mov  %l0, %o0
    306c:	40 00 05 ed 	call  4820 <__0fIPKObjectLgetPositionvK>
    3070:	01 00 00 00 	nop 
    3074:	a0 12 00 00 	mov  %o0, %l0
    3078:	90 14 40 00 	mov  %l1, %o0
    307c:	92 14 00 00 	mov  %l0, %o1
    3080:	40 00 05 bc 	call  4770 <__0oHPKPointctRC6HPKPoint>
    3084:	01 00 00 00 	nop 
    3088:	e0 07 a0 4c 	ld  [ %fp + 0x4c ], %l0
    308c:	90 14 00 00 	mov  %l0, %o0
    3090:	40 00 05 e4 	call  4820 <__0fIPKObjectLgetPositionvK>
    3094:	01 00 00 00 	nop 
    3098:	a0 12 00 00 	mov  %o0, %l0
    309c:	e0 27 bf 50 	st  %l0, [ %fp + -176 ]
    30a0:	a0 07 bf 58 	add  %fp, -168, %l0
    30a4:	e2 07 bf 50 	ld  [ %fp + -176 ], %l1
    30a8:	90 14 00 00 	mov  %l0, %o0
    30ac:	92 14 40 00 	mov  %l1, %o1
    30b0:	40 00 05 b0 	call  4770 <__0oHPKPointctRC6HPKPoint>
    30b4:	01 00 00 00 	nop 
    30b8:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    30bc:	90 14 00 00 	mov  %l0, %o0
    30c0:	40 00 04 b2 	call  4388 <__0fMGEGameObjectIgetWidthv>
    30c4:	01 00 00 00 	nop 
    30c8:	a0 12 00 00 	mov  %o0, %l0
    30cc:	e0 27 bf 4c 	st  %l0, [ %fp + -180 ]
    30d0:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    30d4:	90 14 00 00 	mov  %l0, %o0
    30d8:	40 00 04 9c 	call  4348 <__0fMGEGameObjectOgetWidthAdjustv>
    30dc:	01 00 00 00 	nop 
    30e0:	a0 12 00 00 	mov  %o0, %l0
    30e4:	e0 27 bf 48 	st  %l0, [ %fp + -184 ]
    30e8:	e0 07 bf 4c 	ld  [ %fp + -180 ], %l0
    30ec:	e2 07 bf 48 	ld  [ %fp + -184 ], %l1
    30f0:	a0 04 00 11 	add  %l0, %l1, %l0
    30f4:	e0 27 be ec 	st  %l0, [ %fp + -276 ]
    30f8:	c5 07 be ec 	ld  [ %fp + -276 ], %f2
    30fc:	89 a0 19 02 	fitod  %f2, %f4
    3100:	21 00 00 00 	sethi  %hi(0), %l0
    3104:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3108:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    310c:	85 a1 09 c2 	fdivd  %f4, %f2, %f2
    3110:	a0 07 bf c8 	add  %fp, -56, %l0
    3114:	c5 3c 20 00 	std  %f2, [ %l0 ]
    3118:	e0 07 a0 4c 	ld  [ %fp + 0x4c ], %l0
    311c:	90 14 00 00 	mov  %l0, %o0
    3120:	40 00 04 9a 	call  4388 <__0fMGEGameObjectIgetWidthv>
    3124:	01 00 00 00 	nop 
    3128:	a0 12 00 00 	mov  %o0, %l0
    312c:	e0 27 bf 44 	st  %l0, [ %fp + -188 ]
    3130:	e0 07 a0 4c 	ld  [ %fp + 0x4c ], %l0
    3134:	90 14 00 00 	mov  %l0, %o0
    3138:	40 00 04 84 	call  4348 <__0fMGEGameObjectOgetWidthAdjustv>
    313c:	01 00 00 00 	nop 
    3140:	a0 12 00 00 	mov  %o0, %l0
    3144:	e0 27 bf 40 	st  %l0, [ %fp + -192 ]
    3148:	e0 07 bf 44 	ld  [ %fp + -188 ], %l0
    314c:	e2 07 bf 40 	ld  [ %fp + -192 ], %l1
    3150:	a0 04 00 11 	add  %l0, %l1, %l0
    3154:	e0 27 be ec 	st  %l0, [ %fp + -276 ]
    3158:	c5 07 be ec 	ld  [ %fp + -276 ], %f2
    315c:	89 a0 19 02 	fitod  %f2, %f4
    3160:	21 00 00 00 	sethi  %hi(0), %l0
    3164:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3168:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    316c:	85 a1 09 c2 	fdivd  %f4, %f2, %f2
    3170:	c5 3f bf d0 	std  %f2, [ %fp + -48 ]
    3174:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    3178:	90 14 00 00 	mov  %l0, %o0
    317c:	40 00 04 63 	call  4308 <__0fMGEGameObjectJgetHeightv>
    3180:	01 00 00 00 	nop 
    3184:	a0 12 00 00 	mov  %o0, %l0
    3188:	e0 27 bf 3c 	st  %l0, [ %fp + -196 ]
    318c:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    3190:	90 14 00 00 	mov  %l0, %o0
    3194:	40 00 04 4d 	call  42c8 <__0fMGEGameObjectPgetHeightAdjustv>
    3198:	01 00 00 00 	nop 
    319c:	a0 12 00 00 	mov  %o0, %l0
    31a0:	e0 27 bf 38 	st  %l0, [ %fp + -200 ]
    31a4:	e0 07 bf 3c 	ld  [ %fp + -196 ], %l0
    31a8:	e2 07 bf 38 	ld  [ %fp + -200 ], %l1
    31ac:	a0 04 00 11 	add  %l0, %l1, %l0
    31b0:	e0 27 be ec 	st  %l0, [ %fp + -276 ]
    31b4:	c5 07 be ec 	ld  [ %fp + -276 ], %f2
    31b8:	89 a0 19 02 	fitod  %f2, %f4
    31bc:	21 00 00 00 	sethi  %hi(0), %l0
    31c0:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    31c4:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    31c8:	85 a1 09 c2 	fdivd  %f4, %f2, %f2
    31cc:	a0 07 bf 98 	add  %fp, -104, %l0
    31d0:	c5 3c 20 00 	std  %f2, [ %l0 ]
    31d4:	e0 07 a0 4c 	ld  [ %fp + 0x4c ], %l0
    31d8:	90 14 00 00 	mov  %l0, %o0
    31dc:	40 00 04 4b 	call  4308 <__0fMGEGameObjectJgetHeightv>
    31e0:	01 00 00 00 	nop 
    31e4:	a0 12 00 00 	mov  %o0, %l0
    31e8:	e0 27 bf 34 	st  %l0, [ %fp + -204 ]
    31ec:	e0 07 a0 4c 	ld  [ %fp + 0x4c ], %l0
    31f0:	90 14 00 00 	mov  %l0, %o0
    31f4:	40 00 04 35 	call  42c8 <__0fMGEGameObjectPgetHeightAdjustv>
    31f8:	01 00 00 00 	nop 
    31fc:	a0 12 00 00 	mov  %o0, %l0
    3200:	e0 27 bf 30 	st  %l0, [ %fp + -208 ]
    3204:	e0 07 bf 34 	ld  [ %fp + -204 ], %l0
    3208:	e2 07 bf 30 	ld  [ %fp + -208 ], %l1
    320c:	a0 04 00 11 	add  %l0, %l1, %l0
    3210:	e0 27 be ec 	st  %l0, [ %fp + -276 ]
    3214:	c5 07 be ec 	ld  [ %fp + -276 ], %f2
    3218:	89 a0 19 02 	fitod  %f2, %f4
    321c:	21 00 00 00 	sethi  %hi(0), %l0
    3220:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3224:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3228:	85 a1 09 c2 	fdivd  %f4, %f2, %f2
    322c:	c5 3f bf a0 	std  %f2, [ %fp + -96 ]
    3230:	a0 07 bf 78 	add  %fp, -136, %l0
    3234:	a2 10 20 00 	clr  %l1
    3238:	90 14 00 00 	mov  %l0, %o0
    323c:	92 14 40 00 	mov  %l1, %o1
    3240:	40 00 04 0c 	call  4270 <__0oHPKPointvcCiK>
    3244:	01 00 00 00 	nop 
    3248:	87 a0 00 21 	fmovs  %f1, %f3
    324c:	85 a0 00 20 	fmovs  %f0, %f2
    3250:	c5 3f bf 28 	std  %f2, [ %fp + -216 ]
    3254:	c9 1f bf 28 	ldd  [ %fp + -216 ], %f4
    3258:	a0 07 bf c8 	add  %fp, -56, %l0
    325c:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3260:	85 a1 08 c2 	fsubd  %f4, %f2, %f2
    3264:	a0 07 bf d8 	add  %fp, -40, %l0
    3268:	c5 3c 20 00 	std  %f2, [ %l0 ]
    326c:	a0 07 bf 78 	add  %fp, -136, %l0
    3270:	a2 10 20 00 	clr  %l1
    3274:	90 14 00 00 	mov  %l0, %o0
    3278:	92 14 40 00 	mov  %l1, %o1
    327c:	40 00 03 fd 	call  4270 <__0oHPKPointvcCiK>
    3280:	01 00 00 00 	nop 
    3284:	87 a0 00 21 	fmovs  %f1, %f3
    3288:	85 a0 00 20 	fmovs  %f0, %f2
    328c:	c5 3f bf 20 	std  %f2, [ %fp + -224 ]
    3290:	c9 1f bf 20 	ldd  [ %fp + -224 ], %f4
    3294:	a0 07 bf c8 	add  %fp, -56, %l0
    3298:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    329c:	85 a1 08 42 	faddd  %f4, %f2, %f2
    32a0:	c5 3f bf e0 	std  %f2, [ %fp + -32 ]
    32a4:	a0 07 bf 58 	add  %fp, -168, %l0
    32a8:	a2 10 20 00 	clr  %l1
    32ac:	90 14 00 00 	mov  %l0, %o0
    32b0:	92 14 40 00 	mov  %l1, %o1
    32b4:	40 00 03 ef 	call  4270 <__0oHPKPointvcCiK>
    32b8:	01 00 00 00 	nop 
    32bc:	87 a0 00 21 	fmovs  %f1, %f3
    32c0:	85 a0 00 20 	fmovs  %f0, %f2
    32c4:	c5 3f bf 18 	std  %f2, [ %fp + -232 ]
    32c8:	c9 1f bf 18 	ldd  [ %fp + -232 ], %f4
    32cc:	c5 1f bf d0 	ldd  [ %fp + -48 ], %f2
    32d0:	85 a1 08 c2 	fsubd  %f4, %f2, %f2
    32d4:	c5 3f bf e8 	std  %f2, [ %fp + -24 ]
    32d8:	a0 07 bf 58 	add  %fp, -168, %l0
    32dc:	a2 10 20 00 	clr  %l1
    32e0:	90 14 00 00 	mov  %l0, %o0
    32e4:	92 14 40 00 	mov  %l1, %o1
    32e8:	40 00 03 e2 	call  4270 <__0oHPKPointvcCiK>
    32ec:	01 00 00 00 	nop 
    32f0:	87 a0 00 21 	fmovs  %f1, %f3
    32f4:	85 a0 00 20 	fmovs  %f0, %f2
    32f8:	c5 3f bf 10 	std  %f2, [ %fp + -240 ]
    32fc:	c9 1f bf 10 	ldd  [ %fp + -240 ], %f4
    3300:	c5 1f bf d0 	ldd  [ %fp + -48 ], %f2
    3304:	85 a1 08 42 	faddd  %f4, %f2, %f2
    3308:	c5 3f bf f0 	std  %f2, [ %fp + -16 ]
    330c:	a0 07 bf 78 	add  %fp, -136, %l0
    3310:	a2 10 20 01 	mov  1, %l1
    3314:	90 14 00 00 	mov  %l0, %o0
    3318:	92 14 40 00 	mov  %l1, %o1
    331c:	40 00 03 d5 	call  4270 <__0oHPKPointvcCiK>
    3320:	01 00 00 00 	nop 
    3324:	87 a0 00 21 	fmovs  %f1, %f3
    3328:	85 a0 00 20 	fmovs  %f0, %f2
    332c:	c5 3f bf 08 	std  %f2, [ %fp + -248 ]
    3330:	c9 1f bf 08 	ldd  [ %fp + -248 ], %f4
    3334:	a0 07 bf 98 	add  %fp, -104, %l0
    3338:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    333c:	85 a1 08 c2 	fsubd  %f4, %f2, %f2
    3340:	a0 07 bf a8 	add  %fp, -88, %l0
    3344:	c5 3c 20 00 	std  %f2, [ %l0 ]
    3348:	a0 07 bf 78 	add  %fp, -136, %l0
    334c:	a2 10 20 01 	mov  1, %l1
    3350:	90 14 00 00 	mov  %l0, %o0
    3354:	92 14 40 00 	mov  %l1, %o1
    3358:	40 00 03 c6 	call  4270 <__0oHPKPointvcCiK>
    335c:	01 00 00 00 	nop 
    3360:	87 a0 00 21 	fmovs  %f1, %f3
    3364:	85 a0 00 20 	fmovs  %f0, %f2
    3368:	c5 3f bf 00 	std  %f2, [ %fp + -256 ]
    336c:	c9 1f bf 00 	ldd  [ %fp + -256 ], %f4
    3370:	a0 07 bf 98 	add  %fp, -104, %l0
    3374:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3378:	85 a1 08 42 	faddd  %f4, %f2, %f2
    337c:	c5 3f bf b0 	std  %f2, [ %fp + -80 ]
    3380:	a0 07 bf 58 	add  %fp, -168, %l0
    3384:	a2 10 20 01 	mov  1, %l1
    3388:	90 14 00 00 	mov  %l0, %o0
    338c:	92 14 40 00 	mov  %l1, %o1
    3390:	40 00 03 b8 	call  4270 <__0oHPKPointvcCiK>
    3394:	01 00 00 00 	nop 
    3398:	87 a0 00 21 	fmovs  %f1, %f3
    339c:	85 a0 00 20 	fmovs  %f0, %f2
    33a0:	c5 3f be f8 	std  %f2, [ %fp + -264 ]
    33a4:	c9 1f be f8 	ldd  [ %fp + -264 ], %f4
    33a8:	c5 1f bf a0 	ldd  [ %fp + -96 ], %f2
    33ac:	85 a1 08 c2 	fsubd  %f4, %f2, %f2
    33b0:	c5 3f bf b8 	std  %f2, [ %fp + -72 ]
    33b4:	a0 07 bf 58 	add  %fp, -168, %l0
    33b8:	a2 10 20 01 	mov  1, %l1
    33bc:	90 14 00 00 	mov  %l0, %o0
    33c0:	92 14 40 00 	mov  %l1, %o1
    33c4:	40 00 03 ab 	call  4270 <__0oHPKPointvcCiK>
    33c8:	01 00 00 00 	nop 
    33cc:	87 a0 00 21 	fmovs  %f1, %f3
    33d0:	85 a0 00 20 	fmovs  %f0, %f2
    33d4:	c5 3f be f0 	std  %f2, [ %fp + -272 ]
    33d8:	c9 1f be f0 	ldd  [ %fp + -272 ], %f4
    33dc:	c5 1f bf a0 	ldd  [ %fp + -96 ], %f2
    33e0:	85 a1 08 42 	faddd  %f4, %f2, %f2
    33e4:	c5 3f bf c0 	std  %f2, [ %fp + -64 ]
    33e8:	a0 07 bf d8 	add  %fp, -40, %l0
    33ec:	c9 1c 20 00 	ldd  [ %l0 ], %f4
    33f0:	c5 1f bf f0 	ldd  [ %fp + -16 ], %f2
    33f4:	81 a9 0a c2 	fcmped  %f4, %f2
    33f8:	01 00 00 00 	nop 
    33fc:	19 80 00 19 	fbuge  3460 <__0fSPKPhysicsInterfaceJintersectP6MGEGameObjectTB+0x410>
    3400:	01 00 00 00 	nop 
    3404:	c9 1f bf e0 	ldd  [ %fp + -32 ], %f4
    3408:	c5 1f bf e8 	ldd  [ %fp + -24 ], %f2
    340c:	81 a9 0a c2 	fcmped  %f4, %f2
    3410:	01 00 00 00 	nop 
    3414:	1d 80 00 13 	fbule  3460 <__0fSPKPhysicsInterfaceJintersectP6MGEGameObjectTB+0x410>
    3418:	01 00 00 00 	nop 
    341c:	a0 07 bf a8 	add  %fp, -88, %l0
    3420:	c9 1c 20 00 	ldd  [ %l0 ], %f4
    3424:	c5 1f bf c0 	ldd  [ %fp + -64 ], %f2
    3428:	81 a9 0a c2 	fcmped  %f4, %f2
    342c:	01 00 00 00 	nop 
    3430:	19 80 00 0c 	fbuge  3460 <__0fSPKPhysicsInterfaceJintersectP6MGEGameObjectTB+0x410>
    3434:	01 00 00 00 	nop 
    3438:	c9 1f bf b0 	ldd  [ %fp + -80 ], %f4
    343c:	c5 1f bf b8 	ldd  [ %fp + -72 ], %f2
    3440:	81 a9 0a c2 	fcmped  %f4, %f2
    3444:	01 00 00 00 	nop 
    3448:	1d 80 00 06 	fbule  3460 <__0fSPKPhysicsInterfaceJintersectP6MGEGameObjectTB+0x410>
    344c:	01 00 00 00 	nop 
    3450:	a0 10 20 01 	mov  1, %l0	! 1 <_PROCEDURE_LINKAGE_TABLE_+0x1>
    3454:	e0 27 bf 54 	st  %l0, [ %fp + -172 ]
    3458:	10 80 00 04 	b  3468 <__0fSPKPhysicsInterfaceJintersectP6MGEGameObjectTB+0x418>
    345c:	01 00 00 00 	nop 
    3460:	a0 10 20 00 	clr  %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3464:	e0 27 bf 54 	st  %l0, [ %fp + -172 ]
    3468:	e0 07 bf 54 	ld  [ %fp + -172 ], %l0
    346c:	e0 27 bf fc 	st  %l0, [ %fp + -4 ]
    3470:	a0 07 bf 58 	add  %fp, -168, %l0
    3474:	a2 10 20 02 	mov  2, %l1
    3478:	90 14 00 00 	mov  %l0, %o0
    347c:	92 14 40 00 	mov  %l1, %o1
    3480:	40 00 03 ee 	call  4438 <__0oHPKPointdtv>
    3484:	01 00 00 00 	nop 
    3488:	a0 07 bf 78 	add  %fp, -136, %l0
    348c:	a2 10 20 02 	mov  2, %l1
    3490:	90 14 00 00 	mov  %l0, %o0
    3494:	92 14 40 00 	mov  %l1, %o1
    3498:	40 00 03 e8 	call  4438 <__0oHPKPointdtv>
    349c:	01 00 00 00 	nop 
    34a0:	10 80 00 12 	b  34e8 <__0fSPKPhysicsInterfaceJintersectP6MGEGameObjectTB+0x498>
    34a4:	01 00 00 00 	nop 
    34a8:	10 80 00 10 	b  34e8 <__0fSPKPhysicsInterfaceJintersectP6MGEGameObjectTB+0x498>
    34ac:	01 00 00 00 	nop 
    34b0:	a0 07 bf 58 	add  %fp, -168, %l0
    34b4:	a2 10 20 02 	mov  2, %l1
    34b8:	90 14 00 00 	mov  %l0, %o0
    34bc:	92 14 40 00 	mov  %l1, %o1
    34c0:	40 00 03 de 	call  4438 <__0oHPKPointdtv>
    34c4:	01 00 00 00 	nop 
    34c8:	a0 07 bf 78 	add  %fp, -136, %l0
    34cc:	a2 10 20 02 	mov  2, %l1
    34d0:	90 14 00 00 	mov  %l0, %o0
    34d4:	92 14 40 00 	mov  %l1, %o1
    34d8:	40 00 03 d8 	call  4438 <__0oHPKPointdtv>
    34dc:	01 00 00 00 	nop 
    34e0:	40 00 00 00 	call  34e0 <__0fSPKPhysicsInterfaceJintersectP6MGEGameObjectTB+0x490>
    34e4:	01 00 00 00 	nop 
    34e8:	e0 07 bf fc 	ld  [ %fp + -4 ], %l0
    34ec:	b0 14 00 00 	mov  %l0, %i0
    34f0:	81 c7 e0 08 	ret 
    34f4:	81 e8 00 00 	restore 
    34f8:	00 01 00 00 	unimp  0x10000
    34fc:	00 01 00 00 	unimp  0x10000
    3500:	00 01 00 00 	unimp  0x10000
    3504:	00 01 00 00 	unimp  0x10000

00003508 <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB>:
    3508:	9d e3 bf 00 	save  %sp, -256, %sp
    350c:	f4 27 a0 4c 	st  %i2, [ %fp + 0x4c ]
    3510:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
    3514:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
    3518:	e0 07 a0 4c 	ld  [ %fp + 0x4c ], %l0
    351c:	90 14 00 00 	mov  %l0, %o0
    3520:	40 00 03 44 	call  4230 <__0fIPKObjectJgetTypeIDvK>
    3524:	01 00 00 00 	nop 
    3528:	a0 12 00 00 	mov  %o0, %l0
    352c:	e0 27 bf f8 	st  %l0, [ %fp + -8 ]
    3530:	a2 07 bf d8 	add  %fp, -40, %l1
    3534:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    3538:	90 14 00 00 	mov  %l0, %o0
    353c:	40 00 04 6b 	call  46e8 <__0fIPKObjectJgetVectorvK>
    3540:	01 00 00 00 	nop 
    3544:	a0 12 00 00 	mov  %o0, %l0
    3548:	90 14 40 00 	mov  %l1, %o0
    354c:	92 14 00 00 	mov  %l0, %o1
    3550:	40 00 03 0c 	call  4180 <__0oIPKVectorctRC6IPKVector>
    3554:	01 00 00 00 	nop 
    3558:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    355c:	90 14 00 00 	mov  %l0, %o0
    3560:	40 00 04 b0 	call  4820 <__0fIPKObjectLgetPositionvK>
    3564:	01 00 00 00 	nop 
    3568:	a0 12 00 00 	mov  %o0, %l0
    356c:	e0 27 bf b4 	st  %l0, [ %fp + -76 ]
    3570:	a0 07 bf b8 	add  %fp, -72, %l0
    3574:	e2 07 bf b4 	ld  [ %fp + -76 ], %l1
    3578:	90 14 00 00 	mov  %l0, %o0
    357c:	92 14 40 00 	mov  %l1, %o1
    3580:	40 00 04 7c 	call  4770 <__0oHPKPointctRC6HPKPoint>
    3584:	01 00 00 00 	nop 
    3588:	e0 07 bf f8 	ld  [ %fp + -8 ], %l0
    358c:	80 a4 20 15 	cmp  %l0, 0x15
    3590:	12 80 00 5b 	bne  36fc <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x1f4>
    3594:	01 00 00 00 	nop 
    3598:	a0 07 bf b8 	add  %fp, -72, %l0
    359c:	a2 10 20 00 	clr  %l1
    35a0:	90 14 00 00 	mov  %l0, %o0
    35a4:	92 14 40 00 	mov  %l1, %o1
    35a8:	40 00 03 32 	call  4270 <__0oHPKPointvcCiK>
    35ac:	01 00 00 00 	nop 
    35b0:	87 a0 00 21 	fmovs  %f1, %f3
    35b4:	85 a0 00 20 	fmovs  %f0, %f2
    35b8:	c5 3f bf a8 	std  %f2, [ %fp + -88 ]
    35bc:	c9 1f bf a8 	ldd  [ %fp + -88 ], %f4
    35c0:	21 00 00 00 	sethi  %hi(0), %l0
    35c4:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    35c8:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    35cc:	81 a9 0a c2 	fcmped  %f4, %f2
    35d0:	01 00 00 00 	nop 
    35d4:	19 80 00 13 	fbuge  3620 <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x118>
    35d8:	01 00 00 00 	nop 
    35dc:	a0 07 bf d8 	add  %fp, -40, %l0
    35e0:	a2 10 20 00 	clr  %l1
    35e4:	90 14 00 00 	mov  %l0, %o0
    35e8:	92 14 40 00 	mov  %l1, %o1
    35ec:	40 00 02 cf 	call  4128 <__0oIPKVectorvcCiK>
    35f0:	01 00 00 00 	nop 
    35f4:	87 a0 00 21 	fmovs  %f1, %f3
    35f8:	85 a0 00 20 	fmovs  %f0, %f2
    35fc:	c5 3f bf a0 	std  %f2, [ %fp + -96 ]
    3600:	c9 1f bf a0 	ldd  [ %fp + -96 ], %f4
    3604:	21 00 00 00 	sethi  %hi(0), %l0
    3608:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    360c:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3610:	81 a9 0a c2 	fcmped  %f4, %f2
    3614:	01 00 00 00 	nop 
    3618:	09 80 00 24 	fbl  36a8 <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x1a0>
    361c:	01 00 00 00 	nop 
    3620:	a0 07 bf b8 	add  %fp, -72, %l0
    3624:	a2 10 20 00 	clr  %l1
    3628:	90 14 00 00 	mov  %l0, %o0
    362c:	92 14 40 00 	mov  %l1, %o1
    3630:	40 00 03 10 	call  4270 <__0oHPKPointvcCiK>
    3634:	01 00 00 00 	nop 
    3638:	87 a0 00 21 	fmovs  %f1, %f3
    363c:	85 a0 00 20 	fmovs  %f0, %f2
    3640:	c5 3f bf 98 	std  %f2, [ %fp + -104 ]
    3644:	c9 1f bf 98 	ldd  [ %fp + -104 ], %f4
    3648:	21 00 00 00 	sethi  %hi(0), %l0
    364c:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3650:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3654:	81 a9 0a c2 	fcmped  %f4, %f2
    3658:	01 00 00 00 	nop 
    365c:	1d 80 00 28 	fbule  36fc <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x1f4>
    3660:	01 00 00 00 	nop 
    3664:	a0 07 bf d8 	add  %fp, -40, %l0
    3668:	a2 10 20 00 	clr  %l1
    366c:	90 14 00 00 	mov  %l0, %o0
    3670:	92 14 40 00 	mov  %l1, %o1
    3674:	40 00 02 ad 	call  4128 <__0oIPKVectorvcCiK>
    3678:	01 00 00 00 	nop 
    367c:	87 a0 00 21 	fmovs  %f1, %f3
    3680:	85 a0 00 20 	fmovs  %f0, %f2
    3684:	c5 3f bf 90 	std  %f2, [ %fp + -112 ]
    3688:	c9 1f bf 90 	ldd  [ %fp + -112 ], %f4
    368c:	21 00 00 00 	sethi  %hi(0), %l0
    3690:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3694:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3698:	81 a9 0a c2 	fcmped  %f4, %f2
    369c:	01 00 00 00 	nop 
    36a0:	1d 80 00 17 	fbule  36fc <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x1f4>
    36a4:	01 00 00 00 	nop 
    36a8:	a0 07 bf d8 	add  %fp, -40, %l0
    36ac:	a2 10 20 00 	clr  %l1
    36b0:	90 14 00 00 	mov  %l0, %o0
    36b4:	92 14 40 00 	mov  %l1, %o1
    36b8:	40 00 02 9c 	call  4128 <__0oIPKVectorvcCiK>
    36bc:	01 00 00 00 	nop 
    36c0:	87 a0 00 21 	fmovs  %f1, %f3
    36c4:	85 a0 00 20 	fmovs  %f0, %f2
    36c8:	c5 3f bf 88 	std  %f2, [ %fp + -120 ]
    36cc:	a0 07 bf d8 	add  %fp, -40, %l0
    36d0:	a2 10 20 00 	clr  %l1
    36d4:	c5 1f bf 88 	ldd  [ %fp + -120 ], %f2
    36d8:	85 a0 00 a2 	fnegs  %f2, %f2
    36dc:	90 14 00 00 	mov  %l0, %o0
    36e0:	92 14 40 00 	mov  %l1, %o1
    36e4:	c5 3b a0 58 	std  %f2, [ %sp + 0x58 ]
    36e8:	d4 1b a0 58 	ldd  [ %sp + 0x58 ], %o2
    36ec:	40 00 02 79 	call  40d0 <__0fIPKVectorIsetCoordid>
    36f0:	01 00 00 00 	nop 
    36f4:	10 80 00 59 	b  3858 <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x350>
    36f8:	01 00 00 00 	nop 
    36fc:	a0 07 bf b8 	add  %fp, -72, %l0
    3700:	a2 10 20 01 	mov  1, %l1
    3704:	90 14 00 00 	mov  %l0, %o0
    3708:	92 14 40 00 	mov  %l1, %o1
    370c:	40 00 02 d9 	call  4270 <__0oHPKPointvcCiK>
    3710:	01 00 00 00 	nop 
    3714:	87 a0 00 21 	fmovs  %f1, %f3
    3718:	85 a0 00 20 	fmovs  %f0, %f2
    371c:	c5 3f bf 80 	std  %f2, [ %fp + -128 ]
    3720:	c9 1f bf 80 	ldd  [ %fp + -128 ], %f4
    3724:	21 00 00 00 	sethi  %hi(0), %l0
    3728:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    372c:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3730:	81 a9 0a c2 	fcmped  %f4, %f2
    3734:	01 00 00 00 	nop 
    3738:	19 80 00 13 	fbuge  3784 <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x27c>
    373c:	01 00 00 00 	nop 
    3740:	a0 07 bf d8 	add  %fp, -40, %l0
    3744:	a2 10 20 01 	mov  1, %l1
    3748:	90 14 00 00 	mov  %l0, %o0
    374c:	92 14 40 00 	mov  %l1, %o1
    3750:	40 00 02 76 	call  4128 <__0oIPKVectorvcCiK>
    3754:	01 00 00 00 	nop 
    3758:	87 a0 00 21 	fmovs  %f1, %f3
    375c:	85 a0 00 20 	fmovs  %f0, %f2
    3760:	c5 3f bf 78 	std  %f2, [ %fp + -136 ]
    3764:	c9 1f bf 78 	ldd  [ %fp + -136 ], %f4
    3768:	21 00 00 00 	sethi  %hi(0), %l0
    376c:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3770:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3774:	81 a9 0a c2 	fcmped  %f4, %f2
    3778:	01 00 00 00 	nop 
    377c:	09 80 00 24 	fbl  380c <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x304>
    3780:	01 00 00 00 	nop 
    3784:	a0 07 bf b8 	add  %fp, -72, %l0
    3788:	a2 10 20 01 	mov  1, %l1
    378c:	90 14 00 00 	mov  %l0, %o0
    3790:	92 14 40 00 	mov  %l1, %o1
    3794:	40 00 02 b7 	call  4270 <__0oHPKPointvcCiK>
    3798:	01 00 00 00 	nop 
    379c:	87 a0 00 21 	fmovs  %f1, %f3
    37a0:	85 a0 00 20 	fmovs  %f0, %f2
    37a4:	c5 3f bf 70 	std  %f2, [ %fp + -144 ]
    37a8:	c9 1f bf 70 	ldd  [ %fp + -144 ], %f4
    37ac:	21 00 00 00 	sethi  %hi(0), %l0
    37b0:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    37b4:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    37b8:	81 a9 0a c2 	fcmped  %f4, %f2
    37bc:	01 00 00 00 	nop 
    37c0:	1d 80 00 26 	fbule  3858 <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x350>
    37c4:	01 00 00 00 	nop 
    37c8:	a0 07 bf d8 	add  %fp, -40, %l0
    37cc:	a2 10 20 01 	mov  1, %l1
    37d0:	90 14 00 00 	mov  %l0, %o0
    37d4:	92 14 40 00 	mov  %l1, %o1
    37d8:	40 00 02 54 	call  4128 <__0oIPKVectorvcCiK>
    37dc:	01 00 00 00 	nop 
    37e0:	87 a0 00 21 	fmovs  %f1, %f3
    37e4:	85 a0 00 20 	fmovs  %f0, %f2
    37e8:	c5 3f bf 68 	std  %f2, [ %fp + -152 ]
    37ec:	c9 1f bf 68 	ldd  [ %fp + -152 ], %f4
    37f0:	21 00 00 00 	sethi  %hi(0), %l0
    37f4:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    37f8:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    37fc:	81 a9 0a c2 	fcmped  %f4, %f2
    3800:	01 00 00 00 	nop 
    3804:	1d 80 00 15 	fbule  3858 <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x350>
    3808:	01 00 00 00 	nop 
    380c:	a0 07 bf d8 	add  %fp, -40, %l0
    3810:	a2 10 20 01 	mov  1, %l1
    3814:	90 14 00 00 	mov  %l0, %o0
    3818:	92 14 40 00 	mov  %l1, %o1
    381c:	40 00 02 43 	call  4128 <__0oIPKVectorvcCiK>
    3820:	01 00 00 00 	nop 
    3824:	87 a0 00 21 	fmovs  %f1, %f3
    3828:	85 a0 00 20 	fmovs  %f0, %f2
    382c:	c5 3f bf 60 	std  %f2, [ %fp + -160 ]
    3830:	a0 07 bf d8 	add  %fp, -40, %l0
    3834:	a2 10 20 01 	mov  1, %l1
    3838:	c5 1f bf 60 	ldd  [ %fp + -160 ], %f2
    383c:	85 a0 00 a2 	fnegs  %f2, %f2
    3840:	90 14 00 00 	mov  %l0, %o0
    3844:	92 14 40 00 	mov  %l1, %o1
    3848:	c5 3b a0 58 	std  %f2, [ %sp + 0x58 ]
    384c:	d4 1b a0 58 	ldd  [ %sp + 0x58 ], %o2
    3850:	40 00 02 20 	call  40d0 <__0fIPKVectorIsetCoordid>
    3854:	01 00 00 00 	nop 
    3858:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    385c:	a2 07 bf d8 	add  %fp, -40, %l1
    3860:	90 14 00 00 	mov  %l0, %o0
    3864:	92 14 40 00 	mov  %l1, %o1
    3868:	40 00 01 f4 	call  4038 <__0fIPKObjectJsetVectorRC6IPKVector>
    386c:	01 00 00 00 	nop 
    3870:	a0 07 bf b8 	add  %fp, -72, %l0
    3874:	a2 10 20 02 	mov  2, %l1
    3878:	90 14 00 00 	mov  %l0, %o0
    387c:	92 14 40 00 	mov  %l1, %o1
    3880:	40 00 02 ee 	call  4438 <__0oHPKPointdtv>
    3884:	01 00 00 00 	nop 
    3888:	a0 07 bf d8 	add  %fp, -40, %l0
    388c:	a2 10 20 02 	mov  2, %l1
    3890:	90 14 00 00 	mov  %l0, %o0
    3894:	92 14 40 00 	mov  %l1, %o1
    3898:	40 00 02 cc 	call  43c8 <__0oIPKVectordtv>
    389c:	01 00 00 00 	nop 
    38a0:	10 80 00 10 	b  38e0 <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x3d8>
    38a4:	01 00 00 00 	nop 
    38a8:	a0 07 bf b8 	add  %fp, -72, %l0
    38ac:	a2 10 20 02 	mov  2, %l1
    38b0:	90 14 00 00 	mov  %l0, %o0
    38b4:	92 14 40 00 	mov  %l1, %o1
    38b8:	40 00 02 e0 	call  4438 <__0oHPKPointdtv>
    38bc:	01 00 00 00 	nop 
    38c0:	a0 07 bf d8 	add  %fp, -40, %l0
    38c4:	a2 10 20 02 	mov  2, %l1
    38c8:	90 14 00 00 	mov  %l0, %o0
    38cc:	92 14 40 00 	mov  %l1, %o1
    38d0:	40 00 02 be 	call  43c8 <__0oIPKVectordtv>
    38d4:	01 00 00 00 	nop 
    38d8:	40 00 00 00 	call  38d8 <__0fSPKPhysicsInterfaceObounceWithWallP6MGEGameObjectTB+0x3d0>
    38dc:	01 00 00 00 	nop 
    38e0:	81 c7 e0 08 	ret 
    38e4:	81 e8 00 00 	restore 
    38e8:	00 01 00 00 	unimp  0x10000
    38ec:	00 01 00 00 	unimp  0x10000
    38f0:	00 01 00 00 	unimp  0x10000
    38f4:	00 01 00 00 	unimp  0x10000

000038f8 <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB>:
    38f8:	9d e3 be 98 	save  %sp, -360, %sp
    38fc:	f4 27 a0 4c 	st  %i2, [ %fp + 0x4c ]
    3900:	f2 27 a0 48 	st  %i1, [ %fp + 0x48 ]
    3904:	f0 27 a0 44 	st  %i0, [ %fp + 0x44 ]
    3908:	a2 07 bf d8 	add  %fp, -40, %l1
    390c:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    3910:	90 14 00 00 	mov  %l0, %o0
    3914:	40 00 03 c3 	call  4820 <__0fIPKObjectLgetPositionvK>
    3918:	01 00 00 00 	nop 
    391c:	a4 12 00 00 	mov  %o0, %l2
    3920:	e0 07 a0 4c 	ld  [ %fp + 0x4c ], %l0
    3924:	90 14 00 00 	mov  %l0, %o0
    3928:	40 00 03 be 	call  4820 <__0fIPKObjectLgetPositionvK>
    392c:	01 00 00 00 	nop 
    3930:	a0 12 00 00 	mov  %o0, %l0
    3934:	90 14 40 00 	mov  %l1, %o0
    3938:	92 14 80 00 	mov  %l2, %o1
    393c:	94 14 00 00 	mov  %l0, %o2
    3940:	40 00 01 8c 	call  3f70 <__0OmiRC6HPKPointTB>
    3944:	01 00 00 00 	nop 
    3948:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    394c:	90 14 00 00 	mov  %l0, %o0
    3950:	40 00 03 66 	call  46e8 <__0fIPKObjectJgetVectorvK>
    3954:	01 00 00 00 	nop 
    3958:	a0 12 00 00 	mov  %o0, %l0
    395c:	e0 27 bf 7c 	st  %l0, [ %fp + -132 ]
    3960:	a0 07 bf b8 	add  %fp, -72, %l0
    3964:	e2 07 bf 7c 	ld  [ %fp + -132 ], %l1
    3968:	90 14 00 00 	mov  %l0, %o0
    396c:	92 14 40 00 	mov  %l1, %o1
    3970:	40 00 02 04 	call  4180 <__0oIPKVectorctRC6IPKVector>
    3974:	01 00 00 00 	nop 
    3978:	21 00 00 00 	sethi  %hi(0), %l0
    397c:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3980:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3984:	c5 3f bf b0 	std  %f2, [ %fp + -80 ]
    3988:	a0 07 bf d8 	add  %fp, -40, %l0
    398c:	a2 10 20 01 	mov  1, %l1
    3990:	90 14 00 00 	mov  %l0, %o0
    3994:	92 14 40 00 	mov  %l1, %o1
    3998:	40 00 01 e4 	call  4128 <__0oIPKVectorvcCiK>
    399c:	01 00 00 00 	nop 
    39a0:	87 a0 00 21 	fmovs  %f1, %f3
    39a4:	85 a0 00 20 	fmovs  %f0, %f2
    39a8:	c5 3f bf 70 	std  %f2, [ %fp + -144 ]
    39ac:	e0 07 a0 4c 	ld  [ %fp + 0x4c ], %l0
    39b0:	90 14 00 00 	mov  %l0, %o0
    39b4:	40 00 02 55 	call  4308 <__0fMGEGameObjectJgetHeightv>
    39b8:	01 00 00 00 	nop 
    39bc:	a0 12 00 00 	mov  %o0, %l0
    39c0:	e0 27 bf 6c 	st  %l0, [ %fp + -148 ]
    39c4:	c9 1f bf 70 	ldd  [ %fp + -144 ], %f4
    39c8:	c5 1f bf b0 	ldd  [ %fp + -80 ], %f2
    39cc:	bd a1 09 42 	fmuld  %f4, %f2, %f30
    39d0:	fd 3f be f8 	std  %f30, [ %fp + -264 ]
    39d4:	e0 07 bf 6c 	ld  [ %fp + -148 ], %l0
    39d8:	a2 10 20 02 	mov  2, %l1
    39dc:	90 14 00 00 	mov  %l0, %o0
    39e0:	92 14 40 00 	mov  %l1, %o1
    39e4:	40 00 00 00 	call  39e4 <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB+0xec>
    39e8:	01 00 00 00 	nop 
    39ec:	a0 12 00 00 	mov  %o0, %l0
    39f0:	e0 27 bf 04 	st  %l0, [ %fp + -252 ]
    39f4:	c5 07 bf 04 	ld  [ %fp + -252 ], %f2
    39f8:	85 a0 19 02 	fitod  %f2, %f2
    39fc:	f9 1f be f8 	ldd  [ %fp + -264 ], %f28
    3a00:	85 a7 09 c2 	fdivd  %f28, %f2, %f2
    3a04:	c5 3f bf a8 	std  %f2, [ %fp + -88 ]
    3a08:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    3a0c:	90 14 00 00 	mov  %l0, %o0
    3a10:	40 00 03 36 	call  46e8 <__0fIPKObjectJgetVectorvK>
    3a14:	01 00 00 00 	nop 
    3a18:	a0 12 00 00 	mov  %o0, %l0
    3a1c:	e0 27 bf 68 	st  %l0, [ %fp + -152 ]
    3a20:	e0 07 bf 68 	ld  [ %fp + -152 ], %l0
    3a24:	90 14 00 00 	mov  %l0, %o0
    3a28:	40 00 01 22 	call  3eb0 <__0FGlengthRC6IPKVector>
    3a2c:	01 00 00 00 	nop 
    3a30:	87 a0 00 21 	fmovs  %f1, %f3
    3a34:	85 a0 00 20 	fmovs  %f0, %f2
    3a38:	c5 3f bf 60 	std  %f2, [ %fp + -160 ]
    3a3c:	c5 1f bf 60 	ldd  [ %fp + -160 ], %f2
    3a40:	c5 3f bf a0 	std  %f2, [ %fp + -96 ]
    3a44:	c5 1f bf a8 	ldd  [ %fp + -88 ], %f2
    3a48:	c5 3b a0 58 	std  %f2, [ %sp + 0x58 ]
    3a4c:	d0 1b a0 58 	ldd  [ %sp + 0x58 ], %o0
    3a50:	40 00 00 00 	call  3a50 <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB+0x158>
    3a54:	01 00 00 00 	nop 
    3a58:	87 a0 00 21 	fmovs  %f1, %f3
    3a5c:	85 a0 00 20 	fmovs  %f0, %f2
    3a60:	c5 3f bf 58 	std  %f2, [ %fp + -168 ]
    3a64:	c5 1f bf a8 	ldd  [ %fp + -88 ], %f2
    3a68:	c5 3b a0 58 	std  %f2, [ %sp + 0x58 ]
    3a6c:	d0 1b a0 58 	ldd  [ %sp + 0x58 ], %o0
    3a70:	40 00 00 00 	call  3a70 <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB+0x178>
    3a74:	01 00 00 00 	nop 
    3a78:	87 a0 00 21 	fmovs  %f1, %f3
    3a7c:	85 a0 00 20 	fmovs  %f0, %f2
    3a80:	c5 3f bf 50 	std  %f2, [ %fp + -176 ]
    3a84:	a2 07 bf 80 	add  %fp, -128, %l1
    3a88:	c9 1f bf a0 	ldd  [ %fp + -96 ], %f4
    3a8c:	c5 1f bf 58 	ldd  [ %fp + -168 ], %f2
    3a90:	8d a1 09 42 	fmuld  %f4, %f2, %f6
    3a94:	c9 1f bf a0 	ldd  [ %fp + -96 ], %f4
    3a98:	c5 1f bf 50 	ldd  [ %fp + -176 ], %f2
    3a9c:	85 a1 09 42 	fmuld  %f4, %f2, %f2
    3aa0:	21 00 00 00 	sethi  %hi(0), %l0
    3aa4:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3aa8:	c9 1c 20 00 	ldd  [ %l0 ], %f4
    3aac:	90 14 40 00 	mov  %l1, %o0
    3ab0:	cd 3b a0 58 	std  %f6, [ %sp + 0x58 ]
    3ab4:	d2 03 a0 58 	ld  [ %sp + 0x58 ], %o1
    3ab8:	d4 03 a0 5c 	ld  [ %sp + 0x5c ], %o2
    3abc:	c5 3b a0 58 	std  %f2, [ %sp + 0x58 ]
    3ac0:	d6 03 a0 58 	ld  [ %sp + 0x58 ], %o3
    3ac4:	d8 03 a0 5c 	ld  [ %sp + 0x5c ], %o4
    3ac8:	c9 3b a0 58 	std  %f4, [ %sp + 0x58 ]
    3acc:	da 03 a0 58 	ld  [ %sp + 0x58 ], %o5
    3ad0:	40 00 00 d6 	call  3e28 <__0oIPKVectorctdNCB>
    3ad4:	01 00 00 00 	nop 
    3ad8:	a0 07 bf b8 	add  %fp, -72, %l0
    3adc:	a2 10 20 00 	clr  %l1
    3ae0:	90 14 00 00 	mov  %l0, %o0
    3ae4:	92 14 40 00 	mov  %l1, %o1
    3ae8:	40 00 01 90 	call  4128 <__0oIPKVectorvcCiK>
    3aec:	01 00 00 00 	nop 
    3af0:	87 a0 00 21 	fmovs  %f1, %f3
    3af4:	85 a0 00 20 	fmovs  %f0, %f2
    3af8:	c5 3f bf 48 	std  %f2, [ %fp + -184 ]
    3afc:	c9 1f bf 48 	ldd  [ %fp + -184 ], %f4
    3b00:	21 00 00 00 	sethi  %hi(0), %l0
    3b04:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3b08:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3b0c:	81 a9 0a c2 	fcmped  %f4, %f2
    3b10:	01 00 00 00 	nop 
    3b14:	1d 80 00 26 	fbule  3bac <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB+0x2b4>
    3b18:	01 00 00 00 	nop 
    3b1c:	a0 07 bf 80 	add  %fp, -128, %l0
    3b20:	a2 10 20 00 	clr  %l1
    3b24:	90 14 00 00 	mov  %l0, %o0
    3b28:	92 14 40 00 	mov  %l1, %o1
    3b2c:	40 00 01 7f 	call  4128 <__0oIPKVectorvcCiK>
    3b30:	01 00 00 00 	nop 
    3b34:	87 a0 00 21 	fmovs  %f1, %f3
    3b38:	85 a0 00 20 	fmovs  %f0, %f2
    3b3c:	c5 3f bf 40 	std  %f2, [ %fp + -192 ]
    3b40:	c9 1f bf 40 	ldd  [ %fp + -192 ], %f4
    3b44:	21 00 00 00 	sethi  %hi(0), %l0
    3b48:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3b4c:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3b50:	81 a9 0a c2 	fcmped  %f4, %f2
    3b54:	01 00 00 00 	nop 
    3b58:	1d 80 00 15 	fbule  3bac <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB+0x2b4>
    3b5c:	01 00 00 00 	nop 
    3b60:	a0 07 bf 80 	add  %fp, -128, %l0
    3b64:	a2 10 20 00 	clr  %l1
    3b68:	90 14 00 00 	mov  %l0, %o0
    3b6c:	92 14 40 00 	mov  %l1, %o1
    3b70:	40 00 01 6e 	call  4128 <__0oIPKVectorvcCiK>
    3b74:	01 00 00 00 	nop 
    3b78:	87 a0 00 21 	fmovs  %f1, %f3
    3b7c:	85 a0 00 20 	fmovs  %f0, %f2
    3b80:	c5 3f bf 38 	std  %f2, [ %fp + -200 ]
    3b84:	a0 07 bf 80 	add  %fp, -128, %l0
    3b88:	a2 10 20 00 	clr  %l1
    3b8c:	c5 1f bf 38 	ldd  [ %fp + -200 ], %f2
    3b90:	85 a0 00 a2 	fnegs  %f2, %f2
    3b94:	90 14 00 00 	mov  %l0, %o0
    3b98:	92 14 40 00 	mov  %l1, %o1
    3b9c:	c5 3b a0 58 	std  %f2, [ %sp + 0x58 ]
    3ba0:	d4 1b a0 58 	ldd  [ %sp + 0x58 ], %o2
    3ba4:	40 00 01 4b 	call  40d0 <__0fIPKVectorIsetCoordid>
    3ba8:	01 00 00 00 	nop 
    3bac:	a0 07 bf d8 	add  %fp, -40, %l0
    3bb0:	a2 10 20 00 	clr  %l1
    3bb4:	90 14 00 00 	mov  %l0, %o0
    3bb8:	92 14 40 00 	mov  %l1, %o1
    3bbc:	40 00 01 5b 	call  4128 <__0oIPKVectorvcCiK>
    3bc0:	01 00 00 00 	nop 
    3bc4:	87 a0 00 21 	fmovs  %f1, %f3
    3bc8:	85 a0 00 20 	fmovs  %f0, %f2
    3bcc:	c5 3f bf 30 	std  %f2, [ %fp + -208 ]
    3bd0:	c9 1f bf 30 	ldd  [ %fp + -208 ], %f4
    3bd4:	21 00 00 00 	sethi  %hi(0), %l0
    3bd8:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3bdc:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3be0:	81 a9 0a c2 	fcmped  %f4, %f2
    3be4:	01 00 00 00 	nop 
    3be8:	1d 80 00 26 	fbule  3c80 <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB+0x388>
    3bec:	01 00 00 00 	nop 
    3bf0:	a0 07 bf 80 	add  %fp, -128, %l0
    3bf4:	a2 10 20 00 	clr  %l1
    3bf8:	90 14 00 00 	mov  %l0, %o0
    3bfc:	92 14 40 00 	mov  %l1, %o1
    3c00:	40 00 01 4a 	call  4128 <__0oIPKVectorvcCiK>
    3c04:	01 00 00 00 	nop 
    3c08:	87 a0 00 21 	fmovs  %f1, %f3
    3c0c:	85 a0 00 20 	fmovs  %f0, %f2
    3c10:	c5 3f bf 28 	std  %f2, [ %fp + -216 ]
    3c14:	c9 1f bf 28 	ldd  [ %fp + -216 ], %f4
    3c18:	21 00 00 00 	sethi  %hi(0), %l0
    3c1c:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3c20:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3c24:	81 a9 0a c2 	fcmped  %f4, %f2
    3c28:	01 00 00 00 	nop 
    3c2c:	19 80 00 15 	fbuge  3c80 <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB+0x388>
    3c30:	01 00 00 00 	nop 
    3c34:	a0 07 bf 80 	add  %fp, -128, %l0
    3c38:	a2 10 20 00 	clr  %l1
    3c3c:	90 14 00 00 	mov  %l0, %o0
    3c40:	92 14 40 00 	mov  %l1, %o1
    3c44:	40 00 01 39 	call  4128 <__0oIPKVectorvcCiK>
    3c48:	01 00 00 00 	nop 
    3c4c:	87 a0 00 21 	fmovs  %f1, %f3
    3c50:	85 a0 00 20 	fmovs  %f0, %f2
    3c54:	c5 3f bf 20 	std  %f2, [ %fp + -224 ]
    3c58:	a0 07 bf 80 	add  %fp, -128, %l0
    3c5c:	a2 10 20 00 	clr  %l1
    3c60:	c5 1f bf 20 	ldd  [ %fp + -224 ], %f2
    3c64:	85 a0 00 a2 	fnegs  %f2, %f2
    3c68:	90 14 00 00 	mov  %l0, %o0
    3c6c:	92 14 40 00 	mov  %l1, %o1
    3c70:	c5 3b a0 58 	std  %f2, [ %sp + 0x58 ]
    3c74:	d4 1b a0 58 	ldd  [ %sp + 0x58 ], %o2
    3c78:	40 00 01 16 	call  40d0 <__0fIPKVectorIsetCoordid>
    3c7c:	01 00 00 00 	nop 
    3c80:	a0 07 bf d8 	add  %fp, -40, %l0
    3c84:	a2 10 20 00 	clr  %l1
    3c88:	90 14 00 00 	mov  %l0, %o0
    3c8c:	92 14 40 00 	mov  %l1, %o1
    3c90:	40 00 01 26 	call  4128 <__0oIPKVectorvcCiK>
    3c94:	01 00 00 00 	nop 
    3c98:	87 a0 00 21 	fmovs  %f1, %f3
    3c9c:	85 a0 00 20 	fmovs  %f0, %f2
    3ca0:	c5 3f bf 18 	std  %f2, [ %fp + -232 ]
    3ca4:	c9 1f bf 18 	ldd  [ %fp + -232 ], %f4
    3ca8:	21 00 00 00 	sethi  %hi(0), %l0
    3cac:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3cb0:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3cb4:	81 a9 0a c2 	fcmped  %f4, %f2
    3cb8:	01 00 00 00 	nop 
    3cbc:	19 80 00 26 	fbuge  3d54 <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB+0x45c>
    3cc0:	01 00 00 00 	nop 
    3cc4:	a0 07 bf 80 	add  %fp, -128, %l0
    3cc8:	a2 10 20 00 	clr  %l1
    3ccc:	90 14 00 00 	mov  %l0, %o0
    3cd0:	92 14 40 00 	mov  %l1, %o1
    3cd4:	40 00 01 15 	call  4128 <__0oIPKVectorvcCiK>
    3cd8:	01 00 00 00 	nop 
    3cdc:	87 a0 00 21 	fmovs  %f1, %f3
    3ce0:	85 a0 00 20 	fmovs  %f0, %f2
    3ce4:	c5 3f bf 10 	std  %f2, [ %fp + -240 ]
    3ce8:	c9 1f bf 10 	ldd  [ %fp + -240 ], %f4
    3cec:	21 00 00 00 	sethi  %hi(0), %l0
    3cf0:	a0 14 20 00 	mov  %l0, %l0	! 0 <_PROCEDURE_LINKAGE_TABLE_>
    3cf4:	c5 1c 20 00 	ldd  [ %l0 ], %f2
    3cf8:	81 a9 0a c2 	fcmped  %f4, %f2
    3cfc:	01 00 00 00 	nop 
    3d00:	1d 80 00 15 	fbule  3d54 <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB+0x45c>
    3d04:	01 00 00 00 	nop 
    3d08:	a0 07 bf 80 	add  %fp, -128, %l0
    3d0c:	a2 10 20 00 	clr  %l1
    3d10:	90 14 00 00 	mov  %l0, %o0
    3d14:	92 14 40 00 	mov  %l1, %o1
    3d18:	40 00 01 04 	call  4128 <__0oIPKVectorvcCiK>
    3d1c:	01 00 00 00 	nop 
    3d20:	87 a0 00 21 	fmovs  %f1, %f3
    3d24:	85 a0 00 20 	fmovs  %f0, %f2
    3d28:	c5 3f bf 08 	std  %f2, [ %fp + -248 ]
    3d2c:	a0 07 bf 80 	add  %fp, -128, %l0
    3d30:	a2 10 20 00 	clr  %l1
    3d34:	c5 1f bf 08 	ldd  [ %fp + -248 ], %f2
    3d38:	85 a0 00 a2 	fnegs  %f2, %f2
    3d3c:	90 14 00 00 	mov  %l0, %o0
    3d40:	92 14 40 00 	mov  %l1, %o1
    3d44:	c5 3b a0 58 	std  %f2, [ %sp + 0x58 ]
    3d48:	d4 1b a0 58 	ldd  [ %sp + 0x58 ], %o2
    3d4c:	40 00 00 e1 	call  40d0 <__0fIPKVectorIsetCoordid>
    3d50:	01 00 00 00 	nop 
    3d54:	e0 07 a0 48 	ld  [ %fp + 0x48 ], %l0
    3d58:	a2 07 bf 80 	add  %fp, -128, %l1
    3d5c:	90 14 00 00 	mov  %l0, %o0
    3d60:	92 14 40 00 	mov  %l1, %o1
    3d64:	40 00 00 b5 	call  4038 <__0fIPKObjectJsetVectorRC6IPKVector>
    3d68:	01 00 00 00 	nop 
    3d6c:	a0 07 bf 80 	add  %fp, -128, %l0
    3d70:	a2 10 20 02 	mov  2, %l1
    3d74:	90 14 00 00 	mov  %l0, %o0
    3d78:	92 14 40 00 	mov  %l1, %o1
    3d7c:	40 00 01 93 	call  43c8 <__0oIPKVectordtv>
    3d80:	01 00 00 00 	nop 
    3d84:	a0 07 bf b8 	add  %fp, -72, %l0
    3d88:	a2 10 20 02 	mov  2, %l1
    3d8c:	90 14 00 00 	mov  %l0, %o0
    3d90:	92 14 40 00 	mov  %l1, %o1
    3d94:	40 00 01 8d 	call  43c8 <__0oIPKVectordtv>
    3d98:	01 00 00 00 	nop 
    3d9c:	a0 07 bf d8 	add  %fp, -40, %l0
    3da0:	a2 10 20 02 	mov  2, %l1
    3da4:	90 14 00 00 	mov  %l0, %o0
    3da8:	92 14 40 00 	mov  %l1, %o1
    3dac:	40 00 01 87 	call  43c8 <__0oIPKVectordtv>
    3db0:	01 00 00 00 	nop 
    3db4:	10 80 00 16 	b  3e0c <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB+0x514>
    3db8:	01 00 00 00 	nop 
    3dbc:	a0 07 bf 80 	add  %fp, -128, %l0
    3dc0:	a2 10 20 02 	mov  2, %l1
    3dc4:	90 14 00 00 	mov  %l0, %o0
    3dc8:	92 14 40 00 	mov  %l1, %o1
    3dcc:	40 00 01 7f 	call  43c8 <__0oIPKVectordtv>
    3dd0:	01 00 00 00 	nop 
    3dd4:	a0 07 bf b8 	add  %fp, -72, %l0
    3dd8:	a2 10 20 02 	mov  2, %l1
    3ddc:	90 14 00 00 	mov  %l0, %o0
    3de0:	92 14 40 00 	mov  %l1, %o1
    3de4:	40 00 01 79 	call  43c8 <__0oIPKVectordtv>
    3de8:	01 00 00 00 	nop 
    3dec:	a0 07 bf d8 	add  %fp, -40, %l0
    3df0:	a2 10 20 02 	mov  2, %l1
    3df4:	90 14 00 00 	mov  %l0, %o0
    3df8:	92 14 40 00 	mov  %l1, %o1
    3dfc:	40 00 01 73 	call  43c8 <__0oIPKVectordtv>
    3e00:	01 00 00 00 	nop 
    3e04:	40 00 00 00 	call  3e04 <__0fSPKPhysicsInterfaceQbounceWithPlayerP6MGEGameObjectTB+0x50c>
    3e08:	01 00 00 00 	nop 
    3e0c:	81 c7 e0 08 	ret 
    3e10:	81 e8 00 00 	restore 
