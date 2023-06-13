; ModuleID = 'main'
source_filename = "main"

define internal i64 @mul(i64 %n) {
mul:
  %n1 = alloca i64
  %i = alloca i64
  store i64 %n, i64* %i
  %j = alloca i64
  store i64 1, i64* %j
  %a = alloca i64
  br label %entry_0

entry_0:                                          ; preds = %mul
  %i5 = load i64, i64* %i
  %j6 = load i64, i64* %j
  %gt_2 = icmp ugt i64 %i5, %j6
  br i1 %gt_2, label %block_0, label %block_1

exit_1:                                           ; preds = %block_1, %block_0
  %a7 = load i64, i64* %a
  ret i64 %a7

block_0:                                          ; preds = %entry_0
  %i2 = load i64, i64* %i
  %sub_0 = sub i64 %i2, i64 1
  %0 = call i64 @mul(i64 %sub_0)
  %i3 = load i64, i64* %i
  %mul_1 = mul i64 %0, %i3
  store i64 %mul_1, i64* %a
  br label %exit_1

block_1:                                          ; preds = %entry_0
  %i4 = load i64, i64* %i
  store i64 %i4, i64* %a
  br label %exit_1
}

define i64 @main() {
main:
  %0 = alloca [5 x i64]
  %1 = getelementptr [5 x i64], [5 x i64]* %0, i32 0, i32 0
  store i64 5, i64* %1
  %2 = getelementptr [5 x i64], [5 x i64]* %0, i32 0, i32 1
  store i64 4, i64* %2
  %3 = getelementptr [5 x i64], [5 x i64]* %0, i32 0, i32 2
  store i64 3, i64* %3
  %4 = getelementptr [5 x i64], [5 x i64]* %0, i32 0, i32 3
  store i64 2, i64* %4
  %5 = getelementptr [5 x i64], [5 x i64]* %0, i32 0, i32 4
  store i64 1, i64* %5
  %n = alloca i64
  store i64 5, i64* %n
  %res = alloca i64
  %6 = call i64 @mul(i64 5)
  ret i64 0
}