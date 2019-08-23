; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-- -mattr=+avx     | FileCheck %s --check-prefixes=ANY,AVX1
; RUN: llc < %s -mtriple=x86_64-- -mattr=+avx2    | FileCheck %s --check-prefixes=ANY,INT256,AVX2
; RUN: llc < %s -mtriple=x86_64-- -mattr=+avx512f | FileCheck %s --check-prefixes=ANY,INT256,AVX512

define <4 x double> @andpd256(<4 x double> %y, <4 x double> %x) nounwind uwtable readnone ssp {
; ANY-LABEL: andpd256:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vandpd %ymm0, %ymm1, %ymm0
; ANY-NEXT:    vxorpd %xmm1, %xmm1, %xmm1
; ANY-NEXT:    vaddpd %ymm1, %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <4 x double> %x to <4 x i64>
  %1 = bitcast <4 x double> %y to <4 x i64>
  %and.i = and <4 x i64> %0, %1
  %2 = bitcast <4 x i64> %and.i to <4 x double>
  ; add forces execution domain
  %3 = fadd <4 x double> %2, <double 0x0, double 0x0, double 0x0, double 0x0>
  ret <4 x double> %3
}

define <4 x double> @andpd256fold(<4 x double> %y) nounwind uwtable readnone ssp {
; ANY-LABEL: andpd256fold:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vandpd {{.*}}(%rip), %ymm0, %ymm0
; ANY-NEXT:    vxorpd %xmm1, %xmm1, %xmm1
; ANY-NEXT:    vaddpd %ymm1, %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <4 x double> %y to <4 x i64>
  %and.i = and <4 x i64> %0, <i64 4616752568008179712, i64 4614838538166547251, i64 4612361558371493478, i64 4608083138725491507>
  %1 = bitcast <4 x i64> %and.i to <4 x double>
  ; add forces execution domain
  %2 = fadd <4 x double> %1, <double 0x0, double 0x0, double 0x0, double 0x0>
  ret <4 x double> %2
}

define <8 x float> @andps256(<8 x float> %y, <8 x float> %x) nounwind uwtable readnone ssp {
; ANY-LABEL: andps256:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vandps %ymm0, %ymm1, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <8 x float> %x to <8 x i32>
  %1 = bitcast <8 x float> %y to <8 x i32>
  %and.i = and <8 x i32> %0, %1
  %2 = bitcast <8 x i32> %and.i to <8 x float>
  ret <8 x float> %2
}

define <8 x float> @andps256fold(<8 x float> %y) nounwind uwtable readnone ssp {
; ANY-LABEL: andps256fold:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vandps {{.*}}(%rip), %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <8 x float> %y to <8 x i32>
  %and.i = and <8 x i32> %0, <i32 1083179008, i32 1079613850, i32 1075000115, i32 1067030938, i32 1083179008, i32 1079613850, i32 1075000115, i32 1067030938>
  %1 = bitcast <8 x i32> %and.i to <8 x float>
  ret <8 x float> %1
}

define <4 x double> @xorpd256(<4 x double> %y, <4 x double> %x) nounwind uwtable readnone ssp {
; ANY-LABEL: xorpd256:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vxorpd %ymm0, %ymm1, %ymm0
; ANY-NEXT:    vxorpd %xmm1, %xmm1, %xmm1
; ANY-NEXT:    vaddpd %ymm1, %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <4 x double> %x to <4 x i64>
  %1 = bitcast <4 x double> %y to <4 x i64>
  %xor.i = xor <4 x i64> %0, %1
  %2 = bitcast <4 x i64> %xor.i to <4 x double>
  ; add forces execution domain
  %3 = fadd <4 x double> %2, <double 0x0, double 0x0, double 0x0, double 0x0>
  ret <4 x double> %3
}

define <4 x double> @xorpd256fold(<4 x double> %y) nounwind uwtable readnone ssp {
; ANY-LABEL: xorpd256fold:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vxorpd {{.*}}(%rip), %ymm0, %ymm0
; ANY-NEXT:    vxorpd %xmm1, %xmm1, %xmm1
; ANY-NEXT:    vaddpd %ymm1, %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <4 x double> %y to <4 x i64>
  %xor.i = xor <4 x i64> %0, <i64 4616752568008179712, i64 4614838538166547251, i64 4612361558371493478, i64 4608083138725491507>
  %1 = bitcast <4 x i64> %xor.i to <4 x double>
  ; add forces execution domain
  %2 = fadd <4 x double> %1, <double 0x0, double 0x0, double 0x0, double 0x0>
  ret <4 x double> %2
}

define <8 x float> @xorps256(<8 x float> %y, <8 x float> %x) nounwind uwtable readnone ssp {
; ANY-LABEL: xorps256:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vxorps %ymm0, %ymm1, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <8 x float> %x to <8 x i32>
  %1 = bitcast <8 x float> %y to <8 x i32>
  %xor.i = xor <8 x i32> %0, %1
  %2 = bitcast <8 x i32> %xor.i to <8 x float>
  ret <8 x float> %2
}

define <8 x float> @xorps256fold(<8 x float> %y) nounwind uwtable readnone ssp {
; ANY-LABEL: xorps256fold:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vxorps {{.*}}(%rip), %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <8 x float> %y to <8 x i32>
  %xor.i = xor <8 x i32> %0, <i32 1083179008, i32 1079613850, i32 1075000115, i32 1067030938, i32 1083179008, i32 1079613850, i32 1075000115, i32 1067030938>
  %1 = bitcast <8 x i32> %xor.i to <8 x float>
  ret <8 x float> %1
}

define <4 x double> @orpd256(<4 x double> %y, <4 x double> %x) nounwind uwtable readnone ssp {
; ANY-LABEL: orpd256:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vorpd %ymm0, %ymm1, %ymm0
; ANY-NEXT:    vxorpd %xmm1, %xmm1, %xmm1
; ANY-NEXT:    vaddpd %ymm1, %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <4 x double> %x to <4 x i64>
  %1 = bitcast <4 x double> %y to <4 x i64>
  %or.i = or <4 x i64> %0, %1
  %2 = bitcast <4 x i64> %or.i to <4 x double>
  ; add forces execution domain
  %3 = fadd <4 x double> %2, <double 0x0, double 0x0, double 0x0, double 0x0>
  ret <4 x double> %3
}

define <4 x double> @orpd256fold(<4 x double> %y) nounwind uwtable readnone ssp {
; ANY-LABEL: orpd256fold:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vorpd {{.*}}(%rip), %ymm0, %ymm0
; ANY-NEXT:    vxorpd %xmm1, %xmm1, %xmm1
; ANY-NEXT:    vaddpd %ymm1, %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <4 x double> %y to <4 x i64>
  %or.i = or <4 x i64> %0, <i64 4616752568008179712, i64 4614838538166547251, i64 4612361558371493478, i64 4608083138725491507>
  %1 = bitcast <4 x i64> %or.i to <4 x double>
  ; add forces execution domain
  %2 = fadd <4 x double> %1, <double 0x0, double 0x0, double 0x0, double 0x0>
  ret <4 x double> %2
}

define <8 x float> @orps256(<8 x float> %y, <8 x float> %x) nounwind uwtable readnone ssp {
; ANY-LABEL: orps256:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vorps %ymm0, %ymm1, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <8 x float> %x to <8 x i32>
  %1 = bitcast <8 x float> %y to <8 x i32>
  %or.i = or <8 x i32> %0, %1
  %2 = bitcast <8 x i32> %or.i to <8 x float>
  ret <8 x float> %2
}

define <8 x float> @orps256fold(<8 x float> %y) nounwind uwtable readnone ssp {
; ANY-LABEL: orps256fold:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vorps {{.*}}(%rip), %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <8 x float> %y to <8 x i32>
  %or.i = or <8 x i32> %0, <i32 1083179008, i32 1079613850, i32 1075000115, i32 1067030938, i32 1083179008, i32 1079613850, i32 1075000115, i32 1067030938>
  %1 = bitcast <8 x i32> %or.i to <8 x float>
  ret <8 x float> %1
}

define <4 x double> @andnotpd256(<4 x double> %y, <4 x double> %x) nounwind uwtable readnone ssp {
; ANY-LABEL: andnotpd256:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vandnpd %ymm0, %ymm1, %ymm0
; ANY-NEXT:    vxorpd %xmm1, %xmm1, %xmm1
; ANY-NEXT:    vaddpd %ymm1, %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <4 x double> %x to <4 x i64>
  %neg.i = xor <4 x i64> %0, <i64 -1, i64 -1, i64 -1, i64 -1>
  %1 = bitcast <4 x double> %y to <4 x i64>
  %and.i = and <4 x i64> %1, %neg.i
  %2 = bitcast <4 x i64> %and.i to <4 x double>
  ; add forces execution domain
  %3 = fadd <4 x double> %2, <double 0x0, double 0x0, double 0x0, double 0x0>
  ret <4 x double> %3
}

define <4 x double> @andnotpd256fold(<4 x double> %y, <4 x double>* nocapture %x) nounwind uwtable readonly ssp {
; ANY-LABEL: andnotpd256fold:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vandnpd (%rdi), %ymm0, %ymm0
; ANY-NEXT:    vxorpd %xmm1, %xmm1, %xmm1
; ANY-NEXT:    vaddpd %ymm1, %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %tmp2 = load <4 x double>, <4 x double>* %x, align 32
  %0 = bitcast <4 x double> %y to <4 x i64>
  %neg.i = xor <4 x i64> %0, <i64 -1, i64 -1, i64 -1, i64 -1>
  %1 = bitcast <4 x double> %tmp2 to <4 x i64>
  %and.i = and <4 x i64> %1, %neg.i
  %2 = bitcast <4 x i64> %and.i to <4 x double>
  ; add forces execution domain
  %3 = fadd <4 x double> %2, <double 0x0, double 0x0, double 0x0, double 0x0>
  ret <4 x double> %3
}

define <8 x float> @andnotps256(<8 x float> %y, <8 x float> %x) nounwind uwtable readnone ssp {
; ANY-LABEL: andnotps256:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vandnps %ymm0, %ymm1, %ymm0
; ANY-NEXT:    retq
entry:
  %0 = bitcast <8 x float> %x to <8 x i32>
  %neg.i = xor <8 x i32> %0, <i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1>
  %1 = bitcast <8 x float> %y to <8 x i32>
  %and.i = and <8 x i32> %1, %neg.i
  %2 = bitcast <8 x i32> %and.i to <8 x float>
  ret <8 x float> %2
}

define <8 x float> @andnotps256fold(<8 x float> %y, <8 x float>* nocapture %x) nounwind uwtable readonly ssp {
; ANY-LABEL: andnotps256fold:
; ANY:       # %bb.0: # %entry
; ANY-NEXT:    vandnps (%rdi), %ymm0, %ymm0
; ANY-NEXT:    retq
entry:
  %tmp2 = load <8 x float>, <8 x float>* %x, align 32
  %0 = bitcast <8 x float> %y to <8 x i32>
  %neg.i = xor <8 x i32> %0, <i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1>
  %1 = bitcast <8 x float> %tmp2 to <8 x i32>
  %and.i = and <8 x i32> %1, %neg.i
  %2 = bitcast <8 x i32> %and.i to <8 x float>
  ret <8 x float> %2
}

;;; Test that basic 2 x i64 logic use the integer version on AVX

define <2 x i64> @vpandn(<2 x i64> %a, <2 x i64> %b) nounwind uwtable readnone ssp {
  ; Force the execution domain with an add.
; ANY-LABEL: vpandn:
; ANY:       # %bb.0:
; ANY-NEXT:    vpcmpeqd %xmm1, %xmm1, %xmm1
; ANY-NEXT:    vpsubq %xmm1, %xmm0, %xmm1
; ANY-NEXT:    vpandn %xmm0, %xmm1, %xmm0
; ANY-NEXT:    retq
  %a2 = add <2 x i64> %a, <i64 1, i64 1>
  %y = xor <2 x i64> %a2, <i64 -1, i64 -1>
  %x = and <2 x i64> %a, %y
  ret <2 x i64> %x
}

define <2 x i64> @vpand(<2 x i64> %a, <2 x i64> %b) nounwind uwtable readnone ssp {
  ; Force the execution domain with an add.
; ANY-LABEL: vpand:
; ANY:       # %bb.0:
; ANY-NEXT:    vpcmpeqd %xmm2, %xmm2, %xmm2
; ANY-NEXT:    vpsubq %xmm2, %xmm0, %xmm0
; ANY-NEXT:    vpand %xmm1, %xmm0, %xmm0
; ANY-NEXT:    retq
  %a2 = add <2 x i64> %a, <i64 1, i64 1>
  %x = and <2 x i64> %a2, %b
  ret <2 x i64> %x
}

define <4 x i32> @and_xor_splat1_v4i32(<4 x i32> %x) nounwind {
; AVX1-LABEL: and_xor_splat1_v4i32:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vandnps {{.*}}(%rip), %xmm0, %xmm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: and_xor_splat1_v4i32:
; INT256:       # %bb.0:
; INT256-NEXT:    vbroadcastss {{.*#+}} xmm1 = [1,1,1,1]
; INT256-NEXT:    vandnps %xmm1, %xmm0, %xmm0
; INT256-NEXT:    retq
  %xor = xor <4 x i32> %x, <i32 1, i32 1, i32 1, i32 1>
  %and = and <4 x i32> %xor, <i32 1, i32 1, i32 1, i32 1>
  ret <4 x i32> %and
}

define <4 x i64> @and_xor_splat1_v4i64(<4 x i64> %x) nounwind {
; AVX1-LABEL: and_xor_splat1_v4i64:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vandnps {{.*}}(%rip), %ymm0, %ymm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: and_xor_splat1_v4i64:
; INT256:       # %bb.0:
; INT256-NEXT:    vbroadcastsd {{.*#+}} ymm1 = [1,1,1,1]
; INT256-NEXT:    vandnps %ymm1, %ymm0, %ymm0
; INT256-NEXT:    retq
  %xor = xor <4 x i64> %x, <i64 1, i64 1, i64 1, i64 1>
  %and = and <4 x i64> %xor, <i64 1, i64 1, i64 1, i64 1>
  ret <4 x i64> %and
}

; PR37749 - https://bugs.llvm.org/show_bug.cgi?id=37749
; For AVX1, we don't want a 256-bit logic op with insert/extract to the surrounding 128-bit ops.

define <8 x i32> @and_disguised_i8_elts(<8 x i32> %x, <8 x i32> %y, <8 x i32> %z) {
; AVX1-LABEL: and_disguised_i8_elts:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm3
; AVX1-NEXT:    vextractf128 $1, %ymm1, %xmm1
; AVX1-NEXT:    vextractf128 $1, %ymm0, %xmm0
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vmovdqa {{.*#+}} xmm1 = [255,255,255,255]
; AVX1-NEXT:    vpand %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vextractf128 $1, %ymm2, %xmm4
; AVX1-NEXT:    vpaddd %xmm4, %xmm0, %xmm0
; AVX1-NEXT:    vpand %xmm1, %xmm3, %xmm1
; AVX1-NEXT:    vpaddd %xmm2, %xmm1, %xmm1
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm1, %ymm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: and_disguised_i8_elts:
; INT256:       # %bb.0:
; INT256-NEXT:    vpaddd %ymm1, %ymm0, %ymm0
; INT256-NEXT:    vpand {{.*}}(%rip), %ymm0, %ymm0
; INT256-NEXT:    vpaddd %ymm2, %ymm0, %ymm0
; INT256-NEXT:    retq
  %a = add <8 x i32> %x, %y
  %l = and <8 x i32> %a, <i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255>
  %t = add <8 x i32> %l, %z
  ret <8 x i32> %t
}

define <8 x i32> @andn_disguised_i8_elts(<8 x i32> %x, <8 x i32> %y, <8 x i32> %z) {
; AVX1-LABEL: andn_disguised_i8_elts:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vpaddd %xmm0, %xmm1, %xmm3
; AVX1-NEXT:    vextractf128 $1, %ymm0, %xmm0
; AVX1-NEXT:    vextractf128 $1, %ymm1, %xmm1
; AVX1-NEXT:    vpaddd %xmm0, %xmm1, %xmm0
; AVX1-NEXT:    vmovdqa {{.*#+}} xmm1 = [255,255,255,255]
; AVX1-NEXT:    vpandn %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vextractf128 $1, %ymm2, %xmm4
; AVX1-NEXT:    vpaddd %xmm4, %xmm0, %xmm0
; AVX1-NEXT:    vpandn %xmm1, %xmm3, %xmm1
; AVX1-NEXT:    vpaddd %xmm2, %xmm1, %xmm1
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm1, %ymm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: andn_disguised_i8_elts:
; INT256:       # %bb.0:
; INT256-NEXT:    vpaddd %ymm0, %ymm1, %ymm0
; INT256-NEXT:    vpandn {{.*}}(%rip), %ymm0, %ymm0
; INT256-NEXT:    vpaddd %ymm2, %ymm0, %ymm0
; INT256-NEXT:    retq
  %add = add <8 x i32> %y, %x
  %neg = and <8 x i32> %add, <i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255>
  %and = xor <8 x i32> %neg, <i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255>
  %add1 = add <8 x i32> %and, %z
  ret <8 x i32> %add1
}

; Negative test - if we don't have a leading concat_vectors, the transform won't be profitable.

define <8 x i32> @andn_variable_mask_operand_no_concat(<8 x i32> %x, <8 x i32> %y, <8 x i32> %z) {
; AVX1-LABEL: andn_variable_mask_operand_no_concat:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vandnps %ymm2, %ymm0, %ymm0
; AVX1-NEXT:    vextractf128 $1, %ymm0, %xmm2
; AVX1-NEXT:    vextractf128 $1, %ymm1, %xmm3
; AVX1-NEXT:    vpaddd %xmm3, %xmm2, %xmm2
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vinsertf128 $1, %xmm2, %ymm0, %ymm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: andn_variable_mask_operand_no_concat:
; INT256:       # %bb.0:
; INT256-NEXT:    vpandn %ymm2, %ymm0, %ymm0
; INT256-NEXT:    vpaddd %ymm1, %ymm0, %ymm0
; INT256-NEXT:    retq
  %and = and <8 x i32> %x, %z
  %xor = xor <8 x i32> %and, %z ; demanded bits will make this a 'not'
  %add = add <8 x i32> %xor, %y
  ret <8 x i32> %add
}

; Negative test - if we don't have a leading concat_vectors, the transform won't be profitable (even if the mask is a constant).

define <8 x i32> @andn_constant_mask_operand_no_concat(<8 x i32> %x, <8 x i32> %y) {
; AVX1-LABEL: andn_constant_mask_operand_no_concat:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vandnps {{.*}}(%rip), %ymm0, %ymm0
; AVX1-NEXT:    vextractf128 $1, %ymm1, %xmm2
; AVX1-NEXT:    vextractf128 $1, %ymm0, %xmm3
; AVX1-NEXT:    vpaddd %xmm2, %xmm3, %xmm2
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vinsertf128 $1, %xmm2, %ymm0, %ymm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: andn_constant_mask_operand_no_concat:
; INT256:       # %bb.0:
; INT256-NEXT:    vpandn {{.*}}(%rip), %ymm0, %ymm0
; INT256-NEXT:    vpaddd %ymm1, %ymm0, %ymm0
; INT256-NEXT:    retq
  %xor = xor <8 x i32> %x, <i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1>
  %and = and <8 x i32> %xor, <i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255>
  %r = add <8 x i32> %and, %y
  ret <8 x i32> %r
}

; This is a close call, but we split the 'andn' to reduce the insert/extract.

define <8 x i32> @andn_variable_mask_operand_concat(<8 x i32> %x, <8 x i32> %y, <8 x i32> %z, <8 x i32> %w) {
; AVX1-LABEL: andn_variable_mask_operand_concat:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm4
; AVX1-NEXT:    vextractf128 $1, %ymm1, %xmm1
; AVX1-NEXT:    vextractf128 $1, %ymm0, %xmm0
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vextractf128 $1, %ymm2, %xmm1
; AVX1-NEXT:    vpandn %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vextractf128 $1, %ymm3, %xmm1
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vpandn %xmm2, %xmm4, %xmm1
; AVX1-NEXT:    vpaddd %xmm3, %xmm1, %xmm1
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm1, %ymm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: andn_variable_mask_operand_concat:
; INT256:       # %bb.0:
; INT256-NEXT:    vpaddd %ymm1, %ymm0, %ymm0
; INT256-NEXT:    vpandn %ymm2, %ymm0, %ymm0
; INT256-NEXT:    vpaddd %ymm3, %ymm0, %ymm0
; INT256-NEXT:    retq
  %add = add <8 x i32> %x, %y
  %xor = xor <8 x i32> %add, <i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1, i32 -1>
  %and = and <8 x i32> %xor, %z
  %r = add <8 x i32> %and, %w
  ret <8 x i32> %r
}

define <8 x i32> @or_disguised_i8_elts(<8 x i32> %x, <8 x i32> %y, <8 x i32> %z) {
; AVX1-LABEL: or_disguised_i8_elts:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm3
; AVX1-NEXT:    vextractf128 $1, %ymm1, %xmm1
; AVX1-NEXT:    vextractf128 $1, %ymm0, %xmm0
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vmovdqa {{.*#+}} xmm1 = [255,255,255,255]
; AVX1-NEXT:    vpor %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vextractf128 $1, %ymm2, %xmm4
; AVX1-NEXT:    vpaddd %xmm4, %xmm0, %xmm0
; AVX1-NEXT:    vpor %xmm1, %xmm3, %xmm1
; AVX1-NEXT:    vpaddd %xmm2, %xmm1, %xmm1
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm1, %ymm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: or_disguised_i8_elts:
; INT256:       # %bb.0:
; INT256-NEXT:    vpaddd %ymm1, %ymm0, %ymm0
; INT256-NEXT:    vpbroadcastd {{.*#+}} ymm1 = [255,255,255,255,255,255,255,255]
; INT256-NEXT:    vpor %ymm1, %ymm0, %ymm0
; INT256-NEXT:    vpaddd %ymm2, %ymm0, %ymm0
; INT256-NEXT:    retq
  %a = add <8 x i32> %x, %y
  %l = or <8 x i32> %a, <i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255>
  %t = add <8 x i32> %l, %z
  ret <8 x i32> %t
}

define <8 x i32> @xor_disguised_i8_elts(<8 x i32> %x, <8 x i32> %y, <8 x i32> %z) {
; AVX1-LABEL: xor_disguised_i8_elts:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm3
; AVX1-NEXT:    vextractf128 $1, %ymm1, %xmm1
; AVX1-NEXT:    vextractf128 $1, %ymm0, %xmm0
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vmovdqa {{.*#+}} xmm1 = [255,255,255,255]
; AVX1-NEXT:    vpxor %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vextractf128 $1, %ymm2, %xmm4
; AVX1-NEXT:    vpaddd %xmm4, %xmm0, %xmm0
; AVX1-NEXT:    vpxor %xmm1, %xmm3, %xmm1
; AVX1-NEXT:    vpaddd %xmm2, %xmm1, %xmm1
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm1, %ymm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: xor_disguised_i8_elts:
; INT256:       # %bb.0:
; INT256-NEXT:    vpaddd %ymm1, %ymm0, %ymm0
; INT256-NEXT:    vpbroadcastd {{.*#+}} ymm1 = [255,255,255,255,255,255,255,255]
; INT256-NEXT:    vpxor %ymm1, %ymm0, %ymm0
; INT256-NEXT:    vpaddd %ymm2, %ymm0, %ymm0
; INT256-NEXT:    retq
  %a = add <8 x i32> %x, %y
  %l = xor <8 x i32> %a, <i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255, i32 255>
  %t = add <8 x i32> %l, %z
  ret <8 x i32> %t
}

define <8 x i32> @and_disguised_i16_elts(<8 x i32> %x, <8 x i32> %y, <8 x i32> %z) {
; AVX1-LABEL: and_disguised_i16_elts:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm3
; AVX1-NEXT:    vextractf128 $1, %ymm1, %xmm1
; AVX1-NEXT:    vextractf128 $1, %ymm0, %xmm0
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vpxor %xmm1, %xmm1, %xmm1
; AVX1-NEXT:    vpblendw {{.*#+}} xmm0 = xmm0[0],xmm1[1],xmm0[2],xmm1[3],xmm0[4],xmm1[5],xmm0[6],xmm1[7]
; AVX1-NEXT:    vextractf128 $1, %ymm2, %xmm4
; AVX1-NEXT:    vpaddd %xmm4, %xmm0, %xmm0
; AVX1-NEXT:    vpblendw {{.*#+}} xmm1 = xmm3[0],xmm1[1],xmm3[2],xmm1[3],xmm3[4],xmm1[5],xmm3[6],xmm1[7]
; AVX1-NEXT:    vpaddd %xmm2, %xmm1, %xmm1
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm1, %ymm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: and_disguised_i16_elts:
; INT256:       # %bb.0:
; INT256-NEXT:    vpaddd %ymm1, %ymm0, %ymm0
; INT256-NEXT:    vpxor %xmm1, %xmm1, %xmm1
; INT256-NEXT:    vpblendw {{.*#+}} ymm0 = ymm0[0],ymm1[1],ymm0[2],ymm1[3],ymm0[4],ymm1[5],ymm0[6],ymm1[7],ymm0[8],ymm1[9],ymm0[10],ymm1[11],ymm0[12],ymm1[13],ymm0[14],ymm1[15]
; INT256-NEXT:    vpaddd %ymm2, %ymm0, %ymm0
; INT256-NEXT:    retq
  %a = add <8 x i32> %x, %y
  %l = and <8 x i32> %a, <i32 65535, i32 65535, i32 65535, i32 65535, i32 65535, i32 65535, i32 65535, i32 65535>
  %t = add <8 x i32> %l, %z
  ret <8 x i32> %t
}

define <8 x i32> @or_disguised_i16_elts(<8 x i32> %x, <8 x i32> %y, <8 x i32> %z) {
; AVX1-LABEL: or_disguised_i16_elts:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm3
; AVX1-NEXT:    vextractf128 $1, %ymm1, %xmm1
; AVX1-NEXT:    vextractf128 $1, %ymm0, %xmm0
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vmovdqa {{.*#+}} xmm1 = [65535,65535,65535,65535]
; AVX1-NEXT:    vpor %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vextractf128 $1, %ymm2, %xmm4
; AVX1-NEXT:    vpaddd %xmm4, %xmm0, %xmm0
; AVX1-NEXT:    vpor %xmm1, %xmm3, %xmm1
; AVX1-NEXT:    vpaddd %xmm2, %xmm1, %xmm1
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm1, %ymm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: or_disguised_i16_elts:
; INT256:       # %bb.0:
; INT256-NEXT:    vpaddd %ymm1, %ymm0, %ymm0
; INT256-NEXT:    vpbroadcastd {{.*#+}} ymm1 = [65535,65535,65535,65535,65535,65535,65535,65535]
; INT256-NEXT:    vpor %ymm1, %ymm0, %ymm0
; INT256-NEXT:    vpaddd %ymm2, %ymm0, %ymm0
; INT256-NEXT:    retq
  %a = add <8 x i32> %x, %y
  %l = or <8 x i32> %a, <i32 65535, i32 65535, i32 65535, i32 65535, i32 65535, i32 65535, i32 65535, i32 65535>
  %t = add <8 x i32> %l, %z
  ret <8 x i32> %t
}

define <8 x i32> @xor_disguised_i16_elts(<8 x i32> %x, <8 x i32> %y, <8 x i32> %z) {
; AVX1-LABEL: xor_disguised_i16_elts:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm3
; AVX1-NEXT:    vextractf128 $1, %ymm1, %xmm1
; AVX1-NEXT:    vextractf128 $1, %ymm0, %xmm0
; AVX1-NEXT:    vpaddd %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vmovdqa {{.*#+}} xmm1 = [65535,65535,65535,65535]
; AVX1-NEXT:    vpxor %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vextractf128 $1, %ymm2, %xmm4
; AVX1-NEXT:    vpaddd %xmm4, %xmm0, %xmm0
; AVX1-NEXT:    vpxor %xmm1, %xmm3, %xmm1
; AVX1-NEXT:    vpaddd %xmm2, %xmm1, %xmm1
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm1, %ymm0
; AVX1-NEXT:    retq
;
; INT256-LABEL: xor_disguised_i16_elts:
; INT256:       # %bb.0:
; INT256-NEXT:    vpaddd %ymm1, %ymm0, %ymm0
; INT256-NEXT:    vpbroadcastd {{.*#+}} ymm1 = [65535,65535,65535,65535,65535,65535,65535,65535]
; INT256-NEXT:    vpxor %ymm1, %ymm0, %ymm0
; INT256-NEXT:    vpaddd %ymm2, %ymm0, %ymm0
; INT256-NEXT:    retq
  %a = add <8 x i32> %x, %y
  %l = xor <8 x i32> %a, <i32 65535, i32 65535, i32 65535, i32 65535, i32 65535, i32 65535, i32 65535, i32 65535>
  %t = add <8 x i32> %l, %z
  ret <8 x i32> %t
}
