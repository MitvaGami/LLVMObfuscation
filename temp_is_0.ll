; ModuleID = '/home/mohini/LLVMObfuscation/temp_bogus_0.ll'
source_filename = "test/sih_demo.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [6 x i8] c"admin\00", align 1
@.str.1 = private unnamed_addr constant [5 x i8] c"user\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"guest\00", align 1
@__const.authenticate_user.valid_users = private unnamed_addr constant [3 x ptr] [ptr @.str, ptr @.str.1, ptr @.str.2], align 16
@.str.3 = private unnamed_addr constant [9 x i8] c"admin123\00", align 1
@.str.4 = private unnamed_addr constant [9 x i8] c"userpass\00", align 1
@__const.authenticate_user.valid_passwords = private unnamed_addr constant [3 x ptr] [ptr @.str.3, ptr @.str.4, ptr @.str.2], align 16
@.str.5 = private unnamed_addr constant [34 x i8] c"=== SIH LLVM Obfuscator Demo ===\0A\00", align 1
@.str.6 = private unnamed_addr constant [33 x i8] c"Usage: %s <username> <password>\0A\00", align 1
@.str.7 = private unnamed_addr constant [25 x i8] c"Authenticating user: %s\0A\00", align 1
@.str.8 = private unnamed_addr constant [32 x i8] c"\E2\9C\85 Authentication successful!\0A\00", align 1
@.str.9 = private unnamed_addr constant [23 x i8] c"\F0\9F\94\90 Secret value: %d\0A\00", align 1
@.str.10 = private unnamed_addr constant [39 x i8] c"\F0\9F\8E\89 Access granted to secure system!\0A\00", align 1
@.str.11 = private unnamed_addr constant [28 x i8] c"\E2\9D\8C Authentication failed!\0A\00", align 1
@.str.12 = private unnamed_addr constant [21 x i8] c"\F0\9F\9A\AB Access denied!\0A\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @authenticate_user(ptr noundef %0, ptr noundef %1) #0 {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca ptr, align 8
  %4 = alloca ptr, align 8
  %5 = alloca [3 x ptr], align 16
  %6 = alloca [3 x ptr], align 16
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %entry
  br label %continue

continue:                                         ; preds = %fake_branch, %entry
  %7 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  store ptr %1, ptr %4, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr align 16 %5, ptr align 16 @__const.authenticate_user.valid_users, i64 24, i1 false)
  call void @llvm.memcpy.p0.p0.i64(ptr align 16 %6, ptr align 16 @__const.authenticate_user.valid_passwords, i64 24, i1 false)
  store i32 0, ptr %7, align 4
  store i32 2, ptr %switch_var, align 4
  br label %dispatcher

8:                                                ; preds = %dispatcher
  %9 = load i32, ptr %7, align 4
  %10 = icmp slt i32 %9, 3
  br i1 false, label %fake_branch2, label %continue1

fake_branch2:                                     ; preds = %8
  br label %continue1

continue1:                                        ; preds = %fake_branch2, %8
  %11 = select i1 %10, i32 8, i32 6
  store i32 %11, ptr %switch_var, align 4
  br label %dispatcher

12:                                               ; preds = %dispatcher
  %13 = load ptr, ptr %3, align 8
  %14 = load i32, ptr %7, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [3 x ptr], ptr %5, i64 0, i64 %15
  %17 = load ptr, ptr %16, align 8
  br i1 false, label %fake_branch4, label %continue3

fake_branch4:                                     ; preds = %12
  br label %continue3

continue3:                                        ; preds = %fake_branch4, %12
  %18 = call i32 @strcmp(ptr noundef %13, ptr noundef %17) #4
  %19 = icmp eq i32 %18, 0
  %20 = select i1 %19, i32 7, i32 1
  store i32 %20, ptr %switch_var, align 4
  br label %dispatcher

21:                                               ; preds = %dispatcher
  %22 = load ptr, ptr %4, align 8
  %23 = load i32, ptr %7, align 4
  %24 = sext i32 %23 to i64
  %25 = getelementptr inbounds [3 x ptr], ptr %6, i64 0, i64 %24
  %26 = load ptr, ptr %25, align 8
  br i1 false, label %fake_branch6, label %continue5

fake_branch6:                                     ; preds = %21
  br label %continue5

continue5:                                        ; preds = %fake_branch6, %21
  %27 = call i32 @strcmp(ptr noundef %22, ptr noundef %26) #4
  %28 = icmp eq i32 %27, 0
  %29 = select i1 %28, i32 3, i32 1
  store i32 %29, ptr %switch_var, align 4
  br label %dispatcher

30:                                               ; preds = %dispatcher
  store i32 1, ptr %2, align 4
  store i32 4, ptr %switch_var, align 4
  br label %dispatcher

31:                                               ; preds = %dispatcher
  store i32 5, ptr %switch_var, align 4
  br label %dispatcher

32:                                               ; preds = %dispatcher
  %33 = load i32, ptr %7, align 4
  %sub.subst = sub i32 %33, -1
  %fake_mem = alloca i32, align 4
  store i32 411, ptr %fake_mem, align 4
  %34 = load i32, ptr %fake_mem, align 4
  store i32 %sub.subst, ptr %7, align 4
  store i32 2, ptr %switch_var, align 4
  br label %dispatcher

35:                                               ; preds = %dispatcher
  store i32 0, ptr %2, align 4
  store i32 4, ptr %switch_var, align 4
  br label %dispatcher

36:                                               ; preds = %dispatcher
  %37 = load i32, ptr %2, align 4
  store i32 %37, ptr %retval_storage, align 4
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %36, %35, %32, %31, %30, %continue5, %continue3, %continue1, %continue
  %38 = load i32, ptr %switch_var, align 4
  switch i32 %38, label %return_block [
    i32 2, label %8
    i32 8, label %12
    i32 6, label %35
    i32 7, label %21
    i32 1, label %31
    i32 3, label %30
    i32 4, label %36
    i32 5, label %32
  ]

return_block:                                     ; preds = %dispatcher
  %39 = load i32, ptr %retval_storage, align 4
  ret i32 %39
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #1

; Function Attrs: nounwind willreturn memory(read)
declare i32 @strcmp(ptr noundef, ptr noundef) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @calculate_secret_value(i32 noundef %0) #0 {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca i32, align 4
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, ptr %1, align 4
  %4 = load i32, ptr %1, align 4
  store i32 %4, ptr %2, align 4
  store i32 0, ptr %3, align 4
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

5:                                                ; preds = %dispatcher
  %6 = load i32, ptr %3, align 4
  %7 = icmp slt i32 %6, 10
  %fake_mem = alloca i32, align 4
  store i32 478, ptr %fake_mem, align 4
  %8 = load i32, ptr %fake_mem, align 4
  %9 = select i1 %7, i32 5, i32 6
  store i32 %9, ptr %switch_var, align 4
  br label %dispatcher

10:                                               ; preds = %dispatcher
  %11 = load i32, ptr %2, align 4
  %12 = srem i32 %11, 2
  %13 = icmp eq i32 %12, 0
  %14 = select i1 %13, i32 2, i32 7
  store i32 %14, ptr %switch_var, align 4
  br label %dispatcher

15:                                               ; preds = %dispatcher
  %16 = load i32, ptr %2, align 4
  %17 = sdiv i32 %16, 2
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %15
  br label %continue

continue:                                         ; preds = %fake_branch, %15
  store i32 %17, ptr %2, align 4
  store i32 4, ptr %switch_var, align 4
  br label %dispatcher

18:                                               ; preds = %dispatcher
  %19 = load i32, ptr %2, align 4
  %20 = mul nsw i32 %19, 3
  %sub.subst = sub i32 %20, -1
  br i1 false, label %fake_branch2, label %continue1

fake_branch2:                                     ; preds = %18
  br label %continue1

continue1:                                        ; preds = %fake_branch2, %18
  store i32 %sub.subst, ptr %2, align 4
  store i32 4, ptr %switch_var, align 4
  br label %dispatcher

21:                                               ; preds = %dispatcher
  br i1 false, label %fake_branch4, label %continue3

fake_branch4:                                     ; preds = %21
  br label %continue3

continue3:                                        ; preds = %fake_branch4, %21
  store i32 3, ptr %switch_var, align 4
  br label %dispatcher

22:                                               ; preds = %dispatcher
  %23 = load i32, ptr %3, align 4
  %sub.subst1 = sub i32 %23, -1
  store i32 %sub.subst1, ptr %3, align 4
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

24:                                               ; preds = %dispatcher
  %25 = load i32, ptr %2, align 4
  store i32 %25, ptr %retval_storage, align 4
  br i1 false, label %fake_branch6, label %continue5

fake_branch6:                                     ; preds = %24
  br label %continue5

continue5:                                        ; preds = %fake_branch6, %24
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %continue5, %22, %continue3, %continue1, %continue, %10, %5, %entry
  %26 = load i32, ptr %switch_var, align 4
  switch i32 %26, label %return_block [
    i32 1, label %5
    i32 5, label %10
    i32 6, label %24
    i32 2, label %15
    i32 7, label %18
    i32 4, label %21
    i32 3, label %22
  ]

return_block:                                     ; preds = %dispatcher
  %27 = load i32, ptr %retval_storage, align 4
  ret i32 %27
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, ptr noundef %1) #0 {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca ptr, align 8
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %7 = alloca i32, align 4
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %entry
  br label %continue

continue:                                         ; preds = %fake_branch, %entry
  store i32 0, ptr %2, align 4
  store i32 %0, ptr %3, align 4
  store ptr %1, ptr %4, align 8
  %8 = call i32 (ptr, ...) @printf(ptr noundef @.str.5)
  %9 = load i32, ptr %3, align 4
  %10 = icmp slt i32 %9, 3
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

11:                                               ; preds = %continue5
  %12 = load ptr, ptr %4, align 8
  %13 = getelementptr inbounds ptr, ptr %12, i64 0
  %14 = load ptr, ptr %13, align 8
  %fake_mem = alloca i32, align 4
  store i32 30, ptr %fake_mem, align 4
  %15 = load i32, ptr %fake_mem, align 4
  %16 = call i32 (ptr, ...) @printf(ptr noundef @.str.6, ptr noundef %14)
  store i32 1, ptr %2, align 4
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

17:                                               ; preds = %continue5
  %18 = load ptr, ptr %4, align 8
  %19 = getelementptr inbounds ptr, ptr %18, i64 1
  %20 = load ptr, ptr %19, align 8
  store ptr %20, ptr %5, align 8
  %21 = load ptr, ptr %4, align 8
  %22 = getelementptr inbounds ptr, ptr %21, i64 2
  %23 = load ptr, ptr %22, align 8
  store ptr %23, ptr %6, align 8
  %24 = load ptr, ptr %5, align 8
  %25 = call i32 (ptr, ...) @printf(ptr noundef @.str.7, ptr noundef %24)
  %26 = load ptr, ptr %5, align 8
  %27 = load ptr, ptr %6, align 8
  %28 = call i32 @authenticate_user(ptr noundef %26, ptr noundef %27)
  %29 = icmp ne i32 %28, 0
  %30 = select i1 %29, i32 4, i32 6
  store i32 %30, ptr %switch_var, align 4
  br label %dispatcher

31:                                               ; preds = %continue5
  %32 = call i32 (ptr, ...) @printf(ptr noundef @.str.8)
  %33 = call i32 @calculate_secret_value(i32 noundef 42)
  store i32 %33, ptr %7, align 4
  %34 = load i32, ptr %7, align 4
  %35 = call i32 (ptr, ...) @printf(ptr noundef @.str.9, i32 noundef %34)
  %36 = call i32 (ptr, ...) @printf(ptr noundef @.str.10)
  store i32 3, ptr %switch_var, align 4
  br label %dispatcher

37:                                               ; preds = %continue5
  %38 = call i32 (ptr, ...) @printf(ptr noundef @.str.11)
  %39 = call i32 (ptr, ...) @printf(ptr noundef @.str.12)
  store i32 3, ptr %switch_var, align 4
  br label %dispatcher

40:                                               ; preds = %continue5
  store i32 0, ptr %2, align 4
  br i1 false, label %fake_branch2, label %continue1

fake_branch2:                                     ; preds = %40
  br label %continue1

continue1:                                        ; preds = %fake_branch2, %40
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

41:                                               ; preds = %continue5
  %42 = load i32, ptr %2, align 4
  store i32 %42, ptr %retval_storage, align 4
  br i1 false, label %fake_branch4, label %continue3

fake_branch4:                                     ; preds = %41
  br label %continue3

continue3:                                        ; preds = %fake_branch4, %41
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %continue3, %continue1, %37, %31, %17, %11, %continue
  br i1 false, label %fake_branch6, label %continue5

fake_branch6:                                     ; preds = %dispatcher
  br label %continue5

continue5:                                        ; preds = %fake_branch6, %dispatcher
  %43 = load i32, ptr %switch_var, align 4
  switch i32 %43, label %return_block [
    i32 5, label %11
    i32 2, label %17
    i32 1, label %41
    i32 4, label %31
    i32 6, label %37
    i32 3, label %40
  ]

return_block:                                     ; preds = %continue5
  %44 = load i32, ptr %retval_storage, align 4
  ret i32 %44
}

declare i32 @printf(ptr noundef, ...) #3

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { nounwind willreturn memory(read) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nounwind willreturn memory(read) }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
