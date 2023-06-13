; ModuleID = 'example.bc'
source_filename = "main"

define internal i64 @temp() {
temp:
  %a = alloca i64
  store i64 2, i64* %a
  %b = alloca i64
  store i64 1, i64* %b
  %c = alloca i64
  %a1 = load i64, i64* %a
  %b2 = load i64, i64* %b
  %mul_0 = mul i64 %a1, %b2
  store i64 %mul_0, i64* %c
  %b3 = load i64, i64* %b
  %c4 = load i64, i64* %c
  %div_1 = sdiv i64 %b3, %c4
  store i64 %div_1, i64* %a
  %a5 = load i64, i64* %a
  %add_2 = add i64 %a5, 1
  store i64 %add_2, i64* %a
  %b6 = load i64, i64* %b
  %sub_3 = sub i64 %b6, 1
  store i64 %sub_3, i64* %b
  %d = alloca i64
  %a7 = load i64, i64* %a
  %shr_4 = ashr i64 %a7, 2
  store i64 %shr_4, i64* %d
  %b8 = load i64, i64* %b
  %shl_5 = shl i64 %b8, 2
  store i64 %shl_5, i64* %d
  %a9 = load i64, i64* %a
  %add_6 = add i64 %a9, 6
  ret i64 %add_6
}

define i64 @main() {
main:
  %i = alloca i64
  %a = alloca i64
  store i64 1, i64* %a
  %b = alloca i64
  store i64 1, i64* %b
  %tmp = alloca i64
  %0 = call i64 @temp()
  store i64 %0, i64* %tmp
  %a1 = load i64, i64* %a
  %b2 = load i64, i64* %b
  %add_7 = add i64 %a1, %b2
  store i64 %add_7, i64* %tmp
  br label %entry_0

entry_0:                                          ; preds = %main
  store i64 0, i64* %i
  br label %step_1

step_1:                                           ; preds = %exit_4, %entry_0
  %i13 = load i64, i64* %i
  %1 = trunc i64 %i13 to i32
  %lt_13 = icmp ult i32 %1, 10
  br i1 %lt_13, label %block_0, label %exit_2

exit_2:                                           ; preds = %step_1
  %i14 = load i64, i64* %i
  %2 = inttoptr i64 %i14 to i8*
  call i32 (i8*, ...) @printf(i8* %2)
  ret i64 0

block_0:                                          ; preds = %step_1
  %a3 = load i64, i64* %a
  %b4 = load i64, i64* %b
  %add_8 = add i64 %a3, %b4
  store i64 %add_8, i64* %a
  %a5 = load i64, i64* %a
  store i64 %a5, i64* %tmp
  br label %entry_3

entry_3:                                          ; preds = %block_0
  %a8 = load i64, i64* %a
  %tmp9 = load i64, i64* %tmp
  %gt_11 = icmp ugt i64 %a8, %tmp9
  br i1 %gt_11, label %block_1, label %block_2

exit_4:                                           ; preds = %block_2, %block_1
  %b10 = load i64, i64* %b
  store i64 %b10, i64* %a
  %tmp11 = load i64, i64* %tmp
  store i64 %tmp11, i64* %b
  %i12 = load i64, i64* %i
  %add_12 = add i64 %i12, 1
  store i64 %add_12, i64* %i
  br label %step_1

block_1:                                          ; preds = %entry_3
  %a6 = load i64, i64* %a
  %sub_9 = sub i64 %a6, 3
  store i64 %sub_9, i64* %b
  br label %exit_4

block_2:                                          ; preds = %entry_3
  %a7 = load i64, i64* %a
  %sub_10 = sub i64 %a7, 1
  store i64 %sub_10, i64* %a
  br label %exit_4
}
declare dso_local i32 @printf(i8*, ...) #1
