; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt -S -mtriple=x86_64-pc-linux-gnu -mcpu=generic -slp-vectorizer -pass-remarks-output=%t < %s | FileCheck %s
; RUN: FileCheck --input-file=%t --check-prefix=YAML %s

define i32 @foo(i32* %diff) #0 {
; CHECK-LABEL: @foo(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[M2:%.*]] = alloca [8 x [8 x i32]], align 16
; CHECK-NEXT:    [[TMP0:%.*]] = bitcast [8 x [8 x i32]]* [[M2]] to i8*
; CHECK-NEXT:    br label [[FOR_BODY:%.*]]
; CHECK:       for.body:
; CHECK-NEXT:    [[INDVARS_IV:%.*]] = phi i64 [ 0, [[ENTRY:%.*]] ], [ [[INDVARS_IV_NEXT:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[A_088:%.*]] = phi i32 [ 0, [[ENTRY]] ], [ [[OP_EXTRA:%.*]], [[FOR_BODY]] ]
; CHECK-NEXT:    [[TMP1:%.*]] = shl i64 [[INDVARS_IV]], 3
; CHECK-NEXT:    [[ARRAYIDX:%.*]] = getelementptr inbounds i32, i32* [[DIFF:%.*]], i64 [[TMP1]]
; CHECK-NEXT:    [[TMP2:%.*]] = or i64 [[TMP1]], 4
; CHECK-NEXT:    [[ARRAYIDX2:%.*]] = getelementptr inbounds i32, i32* [[DIFF]], i64 [[TMP2]]
; CHECK-NEXT:    [[ARRAYIDX6:%.*]] = getelementptr inbounds [8 x [8 x i32]], [8 x [8 x i32]]* [[M2]], i64 0, i64 [[INDVARS_IV]], i64 0
; CHECK-NEXT:    [[TMP3:%.*]] = or i64 [[TMP1]], 1
; CHECK-NEXT:    [[ARRAYIDX13:%.*]] = getelementptr inbounds i32, i32* [[DIFF]], i64 [[TMP3]]
; CHECK-NEXT:    [[TMP4:%.*]] = or i64 [[TMP1]], 5
; CHECK-NEXT:    [[ARRAYIDX16:%.*]] = getelementptr inbounds i32, i32* [[DIFF]], i64 [[TMP4]]
; CHECK-NEXT:    [[TMP5:%.*]] = or i64 [[TMP1]], 2
; CHECK-NEXT:    [[ARRAYIDX27:%.*]] = getelementptr inbounds i32, i32* [[DIFF]], i64 [[TMP5]]
; CHECK-NEXT:    [[TMP6:%.*]] = or i64 [[TMP1]], 6
; CHECK-NEXT:    [[ARRAYIDX30:%.*]] = getelementptr inbounds i32, i32* [[DIFF]], i64 [[TMP6]]
; CHECK-NEXT:    [[TMP7:%.*]] = or i64 [[TMP1]], 3
; CHECK-NEXT:    [[ARRAYIDX41:%.*]] = getelementptr inbounds i32, i32* [[DIFF]], i64 [[TMP7]]
; CHECK-NEXT:    [[TMP8:%.*]] = bitcast i32* [[ARRAYIDX]] to <4 x i32>*
; CHECK-NEXT:    [[TMP9:%.*]] = load <4 x i32>, <4 x i32>* [[TMP8]], align 4
; CHECK-NEXT:    [[TMP10:%.*]] = or i64 [[TMP1]], 7
; CHECK-NEXT:    [[ARRAYIDX44:%.*]] = getelementptr inbounds i32, i32* [[DIFF]], i64 [[TMP10]]
; CHECK-NEXT:    [[TMP11:%.*]] = bitcast i32* [[ARRAYIDX2]] to <4 x i32>*
; CHECK-NEXT:    [[TMP12:%.*]] = load <4 x i32>, <4 x i32>* [[TMP11]], align 4
; CHECK-NEXT:    [[TMP13:%.*]] = add nsw <4 x i32> [[TMP12]], [[TMP9]]
; CHECK-NEXT:    [[ADD10:%.*]] = add nsw i32 undef, [[A_088]]
; CHECK-NEXT:    [[ARRAYIDX20:%.*]] = getelementptr inbounds [8 x [8 x i32]], [8 x [8 x i32]]* [[M2]], i64 0, i64 [[INDVARS_IV]], i64 1
; CHECK-NEXT:    [[ADD24:%.*]] = add nsw i32 [[ADD10]], undef
; CHECK-NEXT:    [[ARRAYIDX34:%.*]] = getelementptr inbounds [8 x [8 x i32]], [8 x [8 x i32]]* [[M2]], i64 0, i64 [[INDVARS_IV]], i64 2
; CHECK-NEXT:    [[ADD38:%.*]] = add nsw i32 [[ADD24]], undef
; CHECK-NEXT:    [[ARRAYIDX48:%.*]] = getelementptr inbounds [8 x [8 x i32]], [8 x [8 x i32]]* [[M2]], i64 0, i64 [[INDVARS_IV]], i64 3
; CHECK-NEXT:    [[TMP14:%.*]] = bitcast i32* [[ARRAYIDX6]] to <4 x i32>*
; CHECK-NEXT:    store <4 x i32> [[TMP13]], <4 x i32>* [[TMP14]], align 16
; CHECK-NEXT:    [[RDX_SHUF:%.*]] = shufflevector <4 x i32> [[TMP13]], <4 x i32> undef, <4 x i32> <i32 2, i32 3, i32 undef, i32 undef>
; CHECK-NEXT:    [[BIN_RDX:%.*]] = add nsw <4 x i32> [[TMP13]], [[RDX_SHUF]]
; CHECK-NEXT:    [[RDX_SHUF1:%.*]] = shufflevector <4 x i32> [[BIN_RDX]], <4 x i32> undef, <4 x i32> <i32 1, i32 undef, i32 undef, i32 undef>
; CHECK-NEXT:    [[BIN_RDX2:%.*]] = add nsw <4 x i32> [[BIN_RDX]], [[RDX_SHUF1]]
; CHECK-NEXT:    [[TMP15:%.*]] = extractelement <4 x i32> [[BIN_RDX2]], i32 0
; CHECK-NEXT:    [[OP_EXTRA]] = add nsw i32 [[TMP15]], [[A_088]]
; CHECK-NEXT:    [[ADD52:%.*]] = add nsw i32 [[ADD38]], undef
; CHECK-NEXT:    [[INDVARS_IV_NEXT]] = add nuw nsw i64 [[INDVARS_IV]], 1
; CHECK-NEXT:    [[EXITCOND:%.*]] = icmp eq i64 [[INDVARS_IV_NEXT]], 8
; CHECK-NEXT:    br i1 [[EXITCOND]], label [[FOR_END:%.*]], label [[FOR_BODY]]
; CHECK:       for.end:
; CHECK-NEXT:    ret i32 [[OP_EXTRA]]
;
entry:
  %m2 = alloca [8 x [8 x i32]], align 16
  %0 = bitcast [8 x [8 x i32]]* %m2 to i8*
  br label %for.body

for.body:                                         ; preds = %for.body, %entry
  %indvars.iv = phi i64 [ 0, %entry ], [ %indvars.iv.next, %for.body ]
  %a.088 = phi i32 [ 0, %entry ], [ %add52, %for.body ]
  %1 = shl i64 %indvars.iv, 3
  %arrayidx = getelementptr inbounds i32, i32* %diff, i64 %1
  %2 = load i32, i32* %arrayidx, align 4
  %3 = or i64 %1, 4
  %arrayidx2 = getelementptr inbounds i32, i32* %diff, i64 %3
  %4 = load i32, i32* %arrayidx2, align 4
  %add3 = add nsw i32 %4, %2
  %arrayidx6 = getelementptr inbounds [8 x [8 x i32]], [8 x [8 x i32]]* %m2, i64 0, i64 %indvars.iv, i64 0
  store i32 %add3, i32* %arrayidx6, align 16

  %add10 = add nsw i32 %add3, %a.088
  %5 = or i64 %1, 1
  %arrayidx13 = getelementptr inbounds i32, i32* %diff, i64 %5
  %6 = load i32, i32* %arrayidx13, align 4
  %7 = or i64 %1, 5
  %arrayidx16 = getelementptr inbounds i32, i32* %diff, i64 %7
  %8 = load i32, i32* %arrayidx16, align 4
  %add17 = add nsw i32 %8, %6
  %arrayidx20 = getelementptr inbounds [8 x [8 x i32]], [8 x [8 x i32]]* %m2, i64 0, i64 %indvars.iv, i64 1
  store i32 %add17, i32* %arrayidx20, align 4

  %add24 = add nsw i32 %add10, %add17
  %9 = or i64 %1, 2
  %arrayidx27 = getelementptr inbounds i32, i32* %diff, i64 %9
  %10 = load i32, i32* %arrayidx27, align 4
  %11 = or i64 %1, 6
  %arrayidx30 = getelementptr inbounds i32, i32* %diff, i64 %11
  %12 = load i32, i32* %arrayidx30, align 4
  %add31 = add nsw i32 %12, %10
  %arrayidx34 = getelementptr inbounds [8 x [8 x i32]], [8 x [8 x i32]]* %m2, i64 0, i64 %indvars.iv, i64 2
  store i32 %add31, i32* %arrayidx34, align 8

  %add38 = add nsw i32 %add24, %add31
  %13 = or i64 %1, 3
  %arrayidx41 = getelementptr inbounds i32, i32* %diff, i64 %13
  %14 = load i32, i32* %arrayidx41, align 4
  %15 = or i64 %1, 7
  %arrayidx44 = getelementptr inbounds i32, i32* %diff, i64 %15
  %16 = load i32, i32* %arrayidx44, align 4

  %add45 = add nsw i32 %16, %14
  %arrayidx48 = getelementptr inbounds [8 x [8 x i32]], [8 x [8 x i32]]* %m2, i64 0, i64 %indvars.iv, i64 3
  store i32 %add45, i32* %arrayidx48, align 4

  %add52 = add nsw i32 %add38, %add45

  ; YAML:      --- !Passed
  ; YAML-NEXT: Pass:            slp-vectorizer
  ; YAML-NEXT: Name:            StoresVectorized
  ; YAML-NEXT: Function:        foo
  ; YAML-NEXT: Args:
  ; YAML-NEXT:   - String:          'Stores SLP vectorized with cost '
  ; YAML-NEXT:   - Cost:            '-8'
  ; YAML-NEXT:   - String:          ' and with tree size '
  ; YAML-NEXT:   - TreeSize:        '4'

  ; YAML:      --- !Passed
  ; YAML-NEXT: Pass:            slp-vectorizer
  ; YAML-NEXT: Name:            VectorizedHorizontalReduction
  ; YAML-NEXT: Function:        foo
  ; YAML-NEXT: Args:
  ; YAML-NEXT:   - String:          'Vectorized horizontal reduction with cost '
  ; YAML-NEXT:   - Cost:            '-2'
  ; YAML-NEXT:   - String:          ' and with tree size '
  ; YAML-NEXT:   - TreeSize:        '1'

  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1
  %exitcond = icmp eq i64 %indvars.iv.next, 8
  br i1 %exitcond, label %for.end, label %for.body

for.end:                                          ; preds = %for.body
  ret i32 %add52
}
