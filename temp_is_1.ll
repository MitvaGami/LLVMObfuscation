; ModuleID = '/home/mohini/LLVMObfuscation/temp_bogus_1.ll'
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
@enc_str_0 = private constant [7 x i8] c"\0E\0B\02\06\01o\00"
@enc_str_1 = private constant [6 x i8] c"\9F\99\8F\98\EA\00"
@enc_str_2 = private constant [7 x i8] c":(8.)]\00"
@enc_str_3 = private constant [10 x i8] c"\96\93\9A\9E\99\C6\C5\C4\F7\00"
@enc_str_4 = private constant [10 x i8] c"SUCTVGUU&\00"
@enc_str_5 = private constant [35 x i8] c"\B1\B1\B1\AC\DF\C5\C4\AC\C0\C0\DA\C1\AC\C3\EE\EA\F9\FF\EF\ED\F8\E3\FE\AC\C8\E9\E1\E3\AC\B1\B1\B1\86\8C\00"
@enc_str_6 = private constant [34 x i8] c"\8C\AA\B8\BE\BC\E3\F9\FC\AA\F9\E5\AC\AA\BC\AB\B7\B8\B4\BC\E7\F9\E5\A9\B8\AA\AA\AE\B6\AB\BD\E7\D3\D9\00"
@enc_str_7 = private constant [26 x i8] c"\1BH\07\FA;W\03\FF1T\0F\F38V_\EB9H\11\B8n\0C\14\8CB\00"
@enc_str_8 = private constant [33 x i8] c"\A9\D7\CEk\0A>?#.%?\22(*?\22$%k8>((.88->'jAK\00"
@enc_str_9 = private constant [24 x i8] c"\AA\A2\E7\02~j\12\F5 P\0F\BA P\13\EB/\17C\A7*#g\00"
@enc_str_10 = private constant [40 x i8] c"\D0\BF\AE\A9\00aCCESS\00GRANTED\00TO\00SECURE\00SYSTEM\01* \00"
@enc_str_11 = private constant [29 x i8] c"\DB\A4\B5\19xLMQ\\WMPZXMPVW\19_XPU\\]\1839\00"
@enc_str_12 = private constant [22 x i8] c"?PUd\EF\8E\AC\AC\AA\BC\BC\EF\AB\AA\A1\A6\AA\AB\EE\C5\CF\00"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @authenticate_user(ptr noundef %0, ptr noundef %1) #0 {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca i32, align 4
  br i1 false, label %fake_branch3, label %continue2

fake_branch3:                                     ; preds = %entry
  br label %continue2

continue2:                                        ; preds = %fake_branch3, %entry
  %2 = alloca i32, align 4
  %3 = alloca ptr, align 8
  br i1 false, label %opaque_fake, label %opaque_continue

opaque_continue:                                  ; preds = %opaque_fake, %continue2
  %4 = alloca ptr, align 8
  %5 = alloca [3 x ptr], align 16
  %6 = alloca [3 x ptr], align 16
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %opaque_continue
  %fake_mem4 = alloca i32, align 4
  store i32 513, ptr %fake_mem4, align 4
  %7 = load i32, ptr %fake_mem4, align 4
  br label %continue

continue:                                         ; preds = %fake_branch, %opaque_continue
  %8 = alloca i32, align 4
  store ptr %0, ptr %3, align 8
  store ptr %1, ptr %4, align 8
  call void @llvm.memcpy.p0.p0.i64(ptr align 16 %5, ptr align 16 @__const.authenticate_user.valid_users, i64 24, i1 false)
  br i1 true, label %opaque_continue1, label %opaque_fake2

opaque_continue1:                                 ; preds = %continue38, %continue
  call void @llvm.memcpy.p0.p0.i64(ptr align 16 %6, ptr align 16 @__const.authenticate_user.valid_passwords, i64 24, i1 false)
  store i32 0, ptr %8, align 4
  %fake_mem5 = alloca i32, align 4
  store i32 550, ptr %fake_mem5, align 4
  %9 = load i32, ptr %fake_mem5, align 4
  store i32 2, ptr %switch_var, align 4
  br label %dispatcher

10:                                               ; preds = %continue35
  br i1 false, label %fake_branch7, label %continue6

fake_branch7:                                     ; preds = %10
  br label %continue6

continue6:                                        ; preds = %fake_branch7, %10
  %11 = load i32, ptr %8, align 4
  br i1 false, label %opaque_fake4, label %opaque_continue3

opaque_continue3:                                 ; preds = %continue40, %continue6
  br i1 false, label %fake_branch9, label %continue8

fake_branch9:                                     ; preds = %opaque_continue3
  br label %continue8

continue8:                                        ; preds = %fake_branch9, %opaque_continue3
  %12 = icmp slt i32 %11, 3
  br i1 false, label %fake_branch2, label %continue1

fake_branch2:                                     ; preds = %continue8
  br i1 false, label %fake_branch11, label %continue10

fake_branch11:                                    ; preds = %fake_branch2
  br label %continue10

continue10:                                       ; preds = %fake_branch11, %fake_branch2
  br label %continue1

continue1:                                        ; preds = %continue10, %continue8
  %13 = select i1 %12, i32 8, i32 6
  br i1 true, label %opaque_continue5, label %opaque_fake6

opaque_continue5:                                 ; preds = %continue42, %continue1
  store i32 %13, ptr %switch_var, align 4
  br label %dispatcher

14:                                               ; preds = %continue35
  %15 = load ptr, ptr %3, align 8
  %16 = load i32, ptr %8, align 4
  br i1 false, label %fake_branch13, label %continue12

fake_branch13:                                    ; preds = %14
  br label %continue12

continue12:                                       ; preds = %fake_branch13, %14
  %17 = sext i32 %16 to i64
  br i1 true, label %opaque_continue7, label %opaque_fake8

opaque_continue7:                                 ; preds = %opaque_fake8, %continue12
  %18 = getelementptr inbounds [3 x ptr], ptr %5, i64 0, i64 %17
  br i1 false, label %fake_branch15, label %continue14

fake_branch15:                                    ; preds = %opaque_continue7
  br label %continue14

continue14:                                       ; preds = %fake_branch15, %opaque_continue7
  %19 = load ptr, ptr %18, align 8
  br i1 false, label %fake_branch4, label %continue3

fake_branch4:                                     ; preds = %continue14
  br label %continue3

continue3:                                        ; preds = %fake_branch4, %continue14
  %20 = call i32 @strcmp(ptr noundef %15, ptr noundef %19) #4
  %fake_mem16 = alloca i32, align 4
  store i32 931, ptr %fake_mem16, align 4
  %21 = load i32, ptr %fake_mem16, align 4
  %22 = icmp eq i32 %20, 0
  br i1 true, label %opaque_continue9, label %opaque_fake10

opaque_continue9:                                 ; preds = %opaque_fake10, %continue3
  %23 = select i1 %22, i32 7, i32 1
  %fake_mem17 = alloca i32, align 4
  store i32 314, ptr %fake_mem17, align 4
  %24 = load i32, ptr %fake_mem17, align 4
  store i32 %23, ptr %switch_var, align 4
  br label %dispatcher

25:                                               ; preds = %continue35
  %26 = load ptr, ptr %4, align 8
  %27 = load i32, ptr %8, align 4
  %28 = sext i32 %27 to i64
  br i1 true, label %opaque_continue11, label %opaque_fake12

opaque_continue11:                                ; preds = %opaque_fake12, %25
  %29 = getelementptr inbounds [3 x ptr], ptr %6, i64 0, i64 %28
  br i1 false, label %fake_branch19, label %continue18

fake_branch19:                                    ; preds = %opaque_continue11
  br label %continue18

continue18:                                       ; preds = %fake_branch19, %opaque_continue11
  %30 = load ptr, ptr %29, align 8
  br i1 false, label %fake_branch6, label %continue5

fake_branch6:                                     ; preds = %continue18
  %fake_mem20 = alloca i32, align 4
  store i32 606, ptr %fake_mem20, align 4
  %31 = load i32, ptr %fake_mem20, align 4
  br label %continue5

continue5:                                        ; preds = %fake_branch6, %continue18
  %32 = call i32 @strcmp(ptr noundef %26, ptr noundef %30) #4
  br i1 false, label %fake_branch22, label %continue21

fake_branch22:                                    ; preds = %continue5
  br label %continue21

continue21:                                       ; preds = %fake_branch22, %continue5
  %33 = icmp eq i32 %32, 0
  br i1 true, label %opaque_continue13, label %opaque_fake14

opaque_continue13:                                ; preds = %continue45, %continue21
  %34 = select i1 %33, i32 3, i32 1
  br i1 false, label %fake_branch24, label %continue23

fake_branch24:                                    ; preds = %opaque_continue13
  br label %continue23

continue23:                                       ; preds = %fake_branch24, %opaque_continue13
  store i32 %34, ptr %switch_var, align 4
  br label %dispatcher

35:                                               ; preds = %continue35
  %fake_mem25 = alloca i32, align 4
  store i32 763, ptr %fake_mem25, align 4
  %36 = load i32, ptr %fake_mem25, align 4
  store i32 1, ptr %2, align 4
  br i1 true, label %opaque_continue15, label %opaque_fake16

opaque_continue15:                                ; preds = %opaque_fake16, %35
  store i32 4, ptr %switch_var, align 4
  br label %dispatcher

37:                                               ; preds = %continue35
  %fake_mem26 = alloca i32, align 4
  store i32 658, ptr %fake_mem26, align 4
  %38 = load i32, ptr %fake_mem26, align 4
  store i32 5, ptr %switch_var, align 4
  br i1 true, label %opaque_continue17, label %opaque_fake18

opaque_continue17:                                ; preds = %opaque_fake18, %37
  %fake_mem27 = alloca i32, align 4
  store i32 659, ptr %fake_mem27, align 4
  %39 = load i32, ptr %fake_mem27, align 4
  br label %dispatcher

40:                                               ; preds = %continue35
  %41 = load i32, ptr %8, align 4
  %sub.subst = sub i32 %41, -1
  %fake_mem = alloca i32, align 4
  store i32 411, ptr %fake_mem, align 4
  br i1 true, label %opaque_continue19, label %opaque_fake20

opaque_continue19:                                ; preds = %opaque_fake20, %40
  %42 = load i32, ptr %fake_mem, align 4
  store i32 %sub.subst, ptr %8, align 4
  br i1 false, label %fake_branch29, label %continue28

fake_branch29:                                    ; preds = %opaque_continue19
  br label %continue28

continue28:                                       ; preds = %fake_branch29, %opaque_continue19
  store i32 2, ptr %switch_var, align 4
  br label %dispatcher

43:                                               ; preds = %continue35
  %fake_mem30 = alloca i32, align 4
  store i32 80, ptr %fake_mem30, align 4
  %44 = load i32, ptr %fake_mem30, align 4
  store i32 0, ptr %2, align 4
  br i1 false, label %opaque_fake22, label %opaque_continue21

opaque_continue21:                                ; preds = %opaque_fake22, %43
  %fake_mem31 = alloca i32, align 4
  store i32 539, ptr %fake_mem31, align 4
  %45 = load i32, ptr %fake_mem31, align 4
  store i32 4, ptr %switch_var, align 4
  br label %dispatcher

46:                                               ; preds = %continue35
  %47 = load i32, ptr %2, align 4
  %fake_mem32 = alloca i32, align 4
  store i32 915, ptr %fake_mem32, align 4
  %48 = load i32, ptr %fake_mem32, align 4
  store i32 %47, ptr %retval_storage, align 4
  br i1 false, label %opaque_fake24, label %opaque_continue23

opaque_continue23:                                ; preds = %opaque_fake24, %46
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %opaque_continue23, %opaque_continue21, %continue28, %opaque_continue17, %opaque_continue15, %continue23, %opaque_continue9, %opaque_continue5, %opaque_continue1
  br i1 false, label %fake_branch34, label %continue33

fake_branch34:                                    ; preds = %dispatcher
  br label %continue33

continue33:                                       ; preds = %fake_branch34, %dispatcher
  %49 = load i32, ptr %switch_var, align 4
  br i1 true, label %opaque_continue25, label %opaque_fake26

opaque_continue25:                                ; preds = %opaque_fake26, %continue33
  br i1 false, label %fake_branch36, label %continue35

fake_branch36:                                    ; preds = %opaque_continue25
  br label %continue35

continue35:                                       ; preds = %fake_branch36, %opaque_continue25
  switch i32 %49, label %return_block [
    i32 2, label %10
    i32 8, label %14
    i32 6, label %43
    i32 7, label %25
    i32 1, label %37
    i32 3, label %35
    i32 4, label %46
    i32 5, label %40
  ]

return_block:                                     ; preds = %continue35
  %50 = load i32, ptr %retval_storage, align 4
  br i1 true, label %opaque_continue27, label %opaque_fake28

opaque_continue27:                                ; preds = %opaque_fake28, %return_block
  ret i32 %50

opaque_fake:                                      ; preds = %continue2
  %fake_mem37 = alloca i32, align 4
  store i32 759, ptr %fake_mem37, align 4
  %51 = load i32, ptr %fake_mem37, align 4
  br label %opaque_continue

opaque_fake2:                                     ; preds = %continue
  br i1 false, label %fake_branch39, label %continue38

fake_branch39:                                    ; preds = %opaque_fake2
  br label %continue38

continue38:                                       ; preds = %fake_branch39, %opaque_fake2
  br label %opaque_continue1

opaque_fake4:                                     ; preds = %continue6
  br i1 false, label %fake_branch41, label %continue40

fake_branch41:                                    ; preds = %opaque_fake4
  br label %continue40

continue40:                                       ; preds = %fake_branch41, %opaque_fake4
  br label %opaque_continue3

opaque_fake6:                                     ; preds = %continue1
  br i1 false, label %fake_branch43, label %continue42

fake_branch43:                                    ; preds = %opaque_fake6
  br label %continue42

continue42:                                       ; preds = %fake_branch43, %opaque_fake6
  br label %opaque_continue5

opaque_fake8:                                     ; preds = %continue12
  br label %opaque_continue7

opaque_fake10:                                    ; preds = %continue3
  %fake_mem44 = alloca i32, align 4
  store i32 27, ptr %fake_mem44, align 4
  %52 = load i32, ptr %fake_mem44, align 4
  br label %opaque_continue9

opaque_fake12:                                    ; preds = %25
  br label %opaque_continue11

opaque_fake14:                                    ; preds = %continue21
  br i1 false, label %fake_branch46, label %continue45

fake_branch46:                                    ; preds = %opaque_fake14
  br label %continue45

continue45:                                       ; preds = %fake_branch46, %opaque_fake14
  br label %opaque_continue13

opaque_fake16:                                    ; preds = %35
  br label %opaque_continue15

opaque_fake18:                                    ; preds = %37
  %fake_mem47 = alloca i32, align 4
  store i32 363, ptr %fake_mem47, align 4
  %53 = load i32, ptr %fake_mem47, align 4
  br label %opaque_continue17

opaque_fake20:                                    ; preds = %40
  br label %opaque_continue19

opaque_fake22:                                    ; preds = %43
  %fake_mem48 = alloca i32, align 4
  store i32 260, ptr %fake_mem48, align 4
  %54 = load i32, ptr %fake_mem48, align 4
  br label %opaque_continue21

opaque_fake24:                                    ; preds = %46
  %fake_mem49 = alloca i32, align 4
  store i32 7, ptr %fake_mem49, align 4
  %55 = load i32, ptr %fake_mem49, align 4
  br label %opaque_continue23

opaque_fake26:                                    ; preds = %continue33
  %fake_mem50 = alloca i32, align 4
  store i32 713, ptr %fake_mem50, align 4
  %56 = load i32, ptr %fake_mem50, align 4
  br label %opaque_continue25

opaque_fake28:                                    ; preds = %return_block
  br label %opaque_continue27
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
  br i1 false, label %opaque_fake, label %opaque_continue

opaque_continue:                                  ; preds = %opaque_fake, %entry
  store i32 %0, ptr %1, align 4
  %4 = load i32, ptr %1, align 4
  store i32 %4, ptr %2, align 4
  br i1 false, label %fake_branch3, label %continue2

fake_branch3:                                     ; preds = %opaque_continue
  br label %continue2

continue2:                                        ; preds = %fake_branch3, %opaque_continue
  store i32 0, ptr %3, align 4
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

5:                                                ; preds = %continue32
  %6 = load i32, ptr %3, align 4
  %7 = icmp slt i32 %6, 10
  %fake_mem4 = alloca i32, align 4
  store i32 389, ptr %fake_mem4, align 4
  %8 = load i32, ptr %fake_mem4, align 4
  %fake_mem = alloca i32, align 4
  store i32 478, ptr %fake_mem, align 4
  br i1 false, label %opaque_fake2, label %opaque_continue1

opaque_continue1:                                 ; preds = %continue34, %5
  %9 = load i32, ptr %fake_mem, align 4
  %10 = select i1 %7, i32 5, i32 6
  br i1 false, label %fake_branch7, label %continue6

fake_branch7:                                     ; preds = %opaque_continue1
  br label %continue6

continue6:                                        ; preds = %fake_branch7, %opaque_continue1
  store i32 %10, ptr %switch_var, align 4
  br label %dispatcher

11:                                               ; preds = %continue32
  %12 = load i32, ptr %2, align 4
  %13 = srem i32 %12, 2
  %14 = icmp eq i32 %13, 0
  br i1 false, label %opaque_fake4, label %opaque_continue3

opaque_continue3:                                 ; preds = %continue36, %11
  %15 = select i1 %14, i32 2, i32 7
  br i1 false, label %fake_branch9, label %continue8

fake_branch9:                                     ; preds = %opaque_continue3
  br label %continue8

continue8:                                        ; preds = %fake_branch9, %opaque_continue3
  store i32 %15, ptr %switch_var, align 4
  br label %dispatcher

16:                                               ; preds = %continue32
  %fake_mem10 = alloca i32, align 4
  store i32 416, ptr %fake_mem10, align 4
  %17 = load i32, ptr %fake_mem10, align 4
  %18 = load i32, ptr %2, align 4
  br i1 false, label %opaque_fake6, label %opaque_continue5

opaque_continue5:                                 ; preds = %opaque_fake6, %16
  %fake_mem11 = alloca i32, align 4
  store i32 812, ptr %fake_mem11, align 4
  %19 = load i32, ptr %fake_mem11, align 4
  %20 = sdiv i32 %18, 2
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %opaque_continue5
  br label %continue

continue:                                         ; preds = %fake_branch, %opaque_continue5
  %fake_mem12 = alloca i32, align 4
  store i32 558, ptr %fake_mem12, align 4
  %21 = load i32, ptr %fake_mem12, align 4
  store i32 %20, ptr %2, align 4
  br i1 true, label %opaque_continue7, label %opaque_fake8

opaque_continue7:                                 ; preds = %continue39, %continue
  br i1 false, label %fake_branch14, label %continue13

fake_branch14:                                    ; preds = %opaque_continue7
  br label %continue13

continue13:                                       ; preds = %fake_branch14, %opaque_continue7
  store i32 4, ptr %switch_var, align 4
  br label %dispatcher

22:                                               ; preds = %continue32
  %23 = load i32, ptr %2, align 4
  %24 = mul nsw i32 %23, 3
  br i1 false, label %opaque_fake10, label %opaque_continue9

opaque_continue9:                                 ; preds = %opaque_fake10, %22
  %fake_mem15 = alloca i32, align 4
  store i32 746, ptr %fake_mem15, align 4
  %25 = load i32, ptr %fake_mem15, align 4
  %sub.subst = sub i32 %24, -1
  br i1 false, label %fake_branch2, label %continue1

fake_branch2:                                     ; preds = %opaque_continue9
  %fake_mem16 = alloca i32, align 4
  store i32 506, ptr %fake_mem16, align 4
  %26 = load i32, ptr %fake_mem16, align 4
  br label %continue1

continue1:                                        ; preds = %fake_branch2, %opaque_continue9
  %fake_mem17 = alloca i32, align 4
  store i32 568, ptr %fake_mem17, align 4
  %27 = load i32, ptr %fake_mem17, align 4
  store i32 %sub.subst, ptr %2, align 4
  br i1 false, label %opaque_fake12, label %opaque_continue11

opaque_continue11:                                ; preds = %opaque_fake12, %continue1
  store i32 4, ptr %switch_var, align 4
  br label %dispatcher

28:                                               ; preds = %continue32
  br i1 false, label %fake_branch4, label %continue3

fake_branch4:                                     ; preds = %28
  %fake_mem18 = alloca i32, align 4
  store i32 460, ptr %fake_mem18, align 4
  %29 = load i32, ptr %fake_mem18, align 4
  br label %continue3

continue3:                                        ; preds = %fake_branch4, %28
  br i1 false, label %fake_branch20, label %continue19

fake_branch20:                                    ; preds = %continue3
  br label %continue19

continue19:                                       ; preds = %fake_branch20, %continue3
  store i32 3, ptr %switch_var, align 4
  br i1 true, label %opaque_continue13, label %opaque_fake14

opaque_continue13:                                ; preds = %opaque_fake14, %continue19
  %fake_mem21 = alloca i32, align 4
  store i32 879, ptr %fake_mem21, align 4
  %30 = load i32, ptr %fake_mem21, align 4
  br label %dispatcher

31:                                               ; preds = %continue32
  %32 = load i32, ptr %3, align 4
  %sub.subst1 = sub i32 %32, -1
  br i1 true, label %opaque_continue15, label %opaque_fake16

opaque_continue15:                                ; preds = %continue42, %31
  store i32 %sub.subst1, ptr %3, align 4
  %fake_mem22 = alloca i32, align 4
  store i32 494, ptr %fake_mem22, align 4
  %33 = load i32, ptr %fake_mem22, align 4
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

34:                                               ; preds = %continue32
  br i1 false, label %fake_branch24, label %continue23

fake_branch24:                                    ; preds = %34
  br label %continue23

continue23:                                       ; preds = %fake_branch24, %34
  %35 = load i32, ptr %2, align 4
  br i1 false, label %opaque_fake18, label %opaque_continue17

opaque_continue17:                                ; preds = %opaque_fake18, %continue23
  %fake_mem25 = alloca i32, align 4
  store i32 217, ptr %fake_mem25, align 4
  %36 = load i32, ptr %fake_mem25, align 4
  store i32 %35, ptr %retval_storage, align 4
  br i1 false, label %fake_branch6, label %continue5

fake_branch6:                                     ; preds = %opaque_continue17
  %fake_mem26 = alloca i32, align 4
  store i32 575, ptr %fake_mem26, align 4
  %37 = load i32, ptr %fake_mem26, align 4
  br label %continue5

continue5:                                        ; preds = %fake_branch6, %opaque_continue17
  br i1 false, label %fake_branch28, label %continue27

fake_branch28:                                    ; preds = %continue5
  br label %continue27

continue27:                                       ; preds = %fake_branch28, %continue5
  store i32 0, ptr %switch_var, align 4
  br i1 true, label %opaque_continue19, label %opaque_fake20

opaque_continue19:                                ; preds = %opaque_fake20, %continue27
  %fake_mem29 = alloca i32, align 4
  store i32 359, ptr %fake_mem29, align 4
  %38 = load i32, ptr %fake_mem29, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %opaque_continue19, %opaque_continue15, %opaque_continue13, %opaque_continue11, %continue13, %continue8, %continue6, %continue2
  br i1 false, label %fake_branch31, label %continue30

fake_branch31:                                    ; preds = %dispatcher
  br label %continue30

continue30:                                       ; preds = %fake_branch31, %dispatcher
  %39 = load i32, ptr %switch_var, align 4
  br i1 false, label %opaque_fake22, label %opaque_continue21

opaque_continue21:                                ; preds = %continue45, %continue30
  br i1 false, label %fake_branch33, label %continue32

fake_branch33:                                    ; preds = %opaque_continue21
  br label %continue32

continue32:                                       ; preds = %fake_branch33, %opaque_continue21
  switch i32 %39, label %return_block [
    i32 1, label %5
    i32 5, label %11
    i32 6, label %34
    i32 2, label %16
    i32 7, label %22
    i32 4, label %28
    i32 3, label %31
  ]

return_block:                                     ; preds = %continue32
  %40 = load i32, ptr %retval_storage, align 4
  br i1 false, label %opaque_fake24, label %opaque_continue23

opaque_continue23:                                ; preds = %opaque_fake24, %return_block
  ret i32 %40

opaque_fake:                                      ; preds = %entry
  br label %opaque_continue

opaque_fake2:                                     ; preds = %5
  br i1 false, label %fake_branch35, label %continue34

fake_branch35:                                    ; preds = %opaque_fake2
  br label %continue34

continue34:                                       ; preds = %fake_branch35, %opaque_fake2
  br label %opaque_continue1

opaque_fake4:                                     ; preds = %11
  br i1 false, label %fake_branch37, label %continue36

fake_branch37:                                    ; preds = %opaque_fake4
  br label %continue36

continue36:                                       ; preds = %fake_branch37, %opaque_fake4
  br label %opaque_continue3

opaque_fake6:                                     ; preds = %16
  %fake_mem38 = alloca i32, align 4
  store i32 486, ptr %fake_mem38, align 4
  %41 = load i32, ptr %fake_mem38, align 4
  br label %opaque_continue5

opaque_fake8:                                     ; preds = %continue
  br i1 false, label %fake_branch40, label %continue39

fake_branch40:                                    ; preds = %opaque_fake8
  br label %continue39

continue39:                                       ; preds = %fake_branch40, %opaque_fake8
  br label %opaque_continue7

opaque_fake10:                                    ; preds = %22
  br label %opaque_continue9

opaque_fake12:                                    ; preds = %continue1
  %fake_mem41 = alloca i32, align 4
  store i32 891, ptr %fake_mem41, align 4
  %42 = load i32, ptr %fake_mem41, align 4
  br label %opaque_continue11

opaque_fake14:                                    ; preds = %continue19
  br label %opaque_continue13

opaque_fake16:                                    ; preds = %31
  br i1 false, label %fake_branch43, label %continue42

fake_branch43:                                    ; preds = %opaque_fake16
  br label %continue42

continue42:                                       ; preds = %fake_branch43, %opaque_fake16
  br label %opaque_continue15

opaque_fake18:                                    ; preds = %continue23
  %fake_mem44 = alloca i32, align 4
  store i32 225, ptr %fake_mem44, align 4
  %43 = load i32, ptr %fake_mem44, align 4
  br label %opaque_continue17

opaque_fake20:                                    ; preds = %continue27
  br label %opaque_continue19

opaque_fake22:                                    ; preds = %continue30
  br i1 false, label %fake_branch46, label %continue45

fake_branch46:                                    ; preds = %opaque_fake22
  br label %continue45

continue45:                                       ; preds = %fake_branch46, %opaque_fake22
  br label %opaque_continue21

opaque_fake24:                                    ; preds = %return_block
  %fake_mem47 = alloca i32, align 4
  store i32 460, ptr %fake_mem47, align 4
  %44 = load i32, ptr %fake_mem47, align 4
  br label %opaque_continue23
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 noundef %0, ptr noundef %1) #0 {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca i32, align 4
  %fake_mem1 = alloca i32, align 4
  store i32 903, ptr %fake_mem1, align 4
  %2 = load i32, ptr %fake_mem1, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  br i1 true, label %opaque_continue, label %opaque_fake

opaque_continue:                                  ; preds = %continue27, %entry
  %5 = alloca ptr, align 8
  %6 = alloca ptr, align 8
  %fake_mem2 = alloca i32, align 4
  store i32 968, ptr %fake_mem2, align 4
  %7 = load i32, ptr %fake_mem2, align 4
  %8 = alloca ptr, align 8
  %9 = alloca i32, align 4
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %opaque_continue
  br label %continue

continue:                                         ; preds = %fake_branch, %opaque_continue
  store i32 0, ptr %3, align 4
  store i32 %0, ptr %4, align 4
  store ptr %1, ptr %5, align 8
  %fake_mem3 = alloca i32, align 4
  store i32 284, ptr %fake_mem3, align 4
  %10 = load i32, ptr %fake_mem3, align 4
  %11 = call ptr @decrypt_1418(ptr @enc_str_5)
  %12 = call i32 (ptr, ...) @printf(ptr noundef %11)
  br i1 false, label %opaque_fake2, label %opaque_continue1

opaque_continue1:                                 ; preds = %opaque_fake2, %continue
  %13 = load i32, ptr %4, align 4
  %14 = icmp slt i32 %13, 3
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

15:                                               ; preds = %opaque_continue19
  %16 = load ptr, ptr %5, align 8
  %17 = getelementptr inbounds ptr, ptr %16, i64 0
  %18 = load ptr, ptr %17, align 8
  %fake_mem4 = alloca i32, align 4
  store i32 294, ptr %fake_mem4, align 4
  %19 = load i32, ptr %fake_mem4, align 4
  %fake_mem = alloca i32, align 4
  store i32 30, ptr %fake_mem, align 4
  br i1 true, label %opaque_continue3, label %opaque_fake4

opaque_continue3:                                 ; preds = %opaque_fake4, %15
  %20 = load i32, ptr %fake_mem, align 4
  %21 = call ptr @decrypt_7265(ptr @enc_str_6)
  %22 = call i32 (ptr, ...) @printf(ptr noundef %21, ptr noundef %18)
  store i32 1, ptr %3, align 4
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

23:                                               ; preds = %opaque_continue19
  %24 = load ptr, ptr %5, align 8
  %25 = getelementptr inbounds ptr, ptr %24, i64 1
  %26 = load ptr, ptr %25, align 8
  store ptr %26, ptr %6, align 8
  %27 = load ptr, ptr %5, align 8
  %28 = getelementptr inbounds ptr, ptr %27, i64 2
  %29 = load ptr, ptr %28, align 8
  store ptr %29, ptr %8, align 8
  br i1 true, label %opaque_continue5, label %opaque_fake6

opaque_continue5:                                 ; preds = %continue29, %23
  %30 = load ptr, ptr %6, align 8
  %31 = call ptr @decrypt_864(ptr @enc_str_7)
  %32 = call i32 (ptr, ...) @printf(ptr noundef %31, ptr noundef %30)
  %33 = load ptr, ptr %6, align 8
  %34 = load ptr, ptr %8, align 8
  %fake_mem5 = alloca i32, align 4
  store i32 244, ptr %fake_mem5, align 4
  %35 = load i32, ptr %fake_mem5, align 4
  %36 = call i32 @authenticate_user(ptr noundef %33, ptr noundef %34)
  %37 = icmp ne i32 %36, 0
  %38 = select i1 %37, i32 4, i32 6
  store i32 %38, ptr %switch_var, align 4
  br label %dispatcher

39:                                               ; preds = %opaque_continue19
  %40 = call ptr @decrypt_151(ptr @enc_str_8)
  %41 = call i32 (ptr, ...) @printf(ptr noundef %40)
  %42 = call i32 @calculate_secret_value(i32 noundef 42)
  br i1 false, label %fake_branch7, label %continue6

fake_branch7:                                     ; preds = %39
  br label %continue6

continue6:                                        ; preds = %fake_branch7, %39
  store i32 %42, ptr %9, align 4
  %43 = load i32, ptr %9, align 4
  br i1 true, label %opaque_continue7, label %opaque_fake8

opaque_continue7:                                 ; preds = %continue31, %continue6
  %44 = call ptr @decrypt_8086(ptr @enc_str_9)
  %45 = call i32 (ptr, ...) @printf(ptr noundef %44, i32 noundef %43)
  %46 = call ptr @decrypt_2946(ptr @enc_str_10)
  %fake_mem8 = alloca i32, align 4
  store i32 62, ptr %fake_mem8, align 4
  %47 = load i32, ptr %fake_mem8, align 4
  %48 = call i32 (ptr, ...) @printf(ptr noundef %46)
  store i32 3, ptr %switch_var, align 4
  br label %dispatcher

49:                                               ; preds = %opaque_continue19
  %50 = call ptr @decrypt_1411(ptr @enc_str_11)
  %51 = call i32 (ptr, ...) @printf(ptr noundef %50)
  %52 = call ptr @decrypt_7427(ptr @enc_str_12)
  %53 = call i32 (ptr, ...) @printf(ptr noundef %52)
  br i1 true, label %opaque_continue9, label %opaque_fake10

opaque_continue9:                                 ; preds = %opaque_fake10, %49
  %fake_mem9 = alloca i32, align 4
  store i32 754, ptr %fake_mem9, align 4
  %54 = load i32, ptr %fake_mem9, align 4
  store i32 3, ptr %switch_var, align 4
  br label %dispatcher

55:                                               ; preds = %opaque_continue19
  br i1 false, label %fake_branch11, label %continue10

fake_branch11:                                    ; preds = %55
  br label %continue10

continue10:                                       ; preds = %fake_branch11, %55
  store i32 0, ptr %3, align 4
  br i1 true, label %opaque_continue11, label %opaque_fake12

opaque_continue11:                                ; preds = %continue34, %continue10
  %fake_mem12 = alloca i32, align 4
  store i32 728, ptr %fake_mem12, align 4
  %56 = load i32, ptr %fake_mem12, align 4
  br i1 false, label %fake_branch2, label %continue1

fake_branch2:                                     ; preds = %opaque_continue11
  br label %continue1

continue1:                                        ; preds = %fake_branch2, %opaque_continue11
  store i32 1, ptr %switch_var, align 4
  br i1 false, label %opaque_fake14, label %opaque_continue13

opaque_continue13:                                ; preds = %continue36, %continue1
  %fake_mem13 = alloca i32, align 4
  store i32 32, ptr %fake_mem13, align 4
  %57 = load i32, ptr %fake_mem13, align 4
  br label %dispatcher

58:                                               ; preds = %opaque_continue19
  %fake_mem14 = alloca i32, align 4
  store i32 131, ptr %fake_mem14, align 4
  %59 = load i32, ptr %fake_mem14, align 4
  %60 = load i32, ptr %3, align 4
  br i1 true, label %opaque_continue15, label %opaque_fake16

opaque_continue15:                                ; preds = %continue38, %58
  br i1 false, label %fake_branch16, label %continue15

fake_branch16:                                    ; preds = %opaque_continue15
  br label %continue15

continue15:                                       ; preds = %fake_branch16, %opaque_continue15
  store i32 %60, ptr %retval_storage, align 4
  br i1 false, label %fake_branch4, label %continue3

fake_branch4:                                     ; preds = %continue15
  br i1 false, label %fake_branch18, label %continue17

fake_branch18:                                    ; preds = %fake_branch4
  br label %continue17

continue17:                                       ; preds = %fake_branch18, %fake_branch4
  br label %continue3

continue3:                                        ; preds = %continue17, %continue15
  br i1 false, label %fake_branch20, label %continue19

fake_branch20:                                    ; preds = %continue3
  br label %continue19

continue19:                                       ; preds = %fake_branch20, %continue3
  store i32 0, ptr %switch_var, align 4
  br i1 false, label %opaque_fake18, label %opaque_continue17

opaque_continue17:                                ; preds = %opaque_fake18, %continue19
  %fake_mem21 = alloca i32, align 4
  store i32 712, ptr %fake_mem21, align 4
  %61 = load i32, ptr %fake_mem21, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %opaque_continue17, %opaque_continue13, %opaque_continue9, %opaque_continue7, %opaque_continue5, %opaque_continue3, %opaque_continue1
  br i1 false, label %fake_branch23, label %continue22

fake_branch23:                                    ; preds = %dispatcher
  br label %continue22

continue22:                                       ; preds = %fake_branch23, %dispatcher
  br i1 false, label %fake_branch6, label %continue5

fake_branch6:                                     ; preds = %continue22
  br i1 false, label %fake_branch25, label %continue24

fake_branch25:                                    ; preds = %fake_branch6
  br label %continue24

continue24:                                       ; preds = %fake_branch25, %fake_branch6
  br label %continue5

continue5:                                        ; preds = %continue24, %continue22
  %62 = load i32, ptr %switch_var, align 4
  br i1 false, label %opaque_fake20, label %opaque_continue19

opaque_continue19:                                ; preds = %opaque_fake20, %continue5
  switch i32 %62, label %return_block [
    i32 5, label %15
    i32 2, label %23
    i32 1, label %58
    i32 4, label %39
    i32 6, label %49
    i32 3, label %55
  ]

return_block:                                     ; preds = %opaque_continue19
  %fake_mem26 = alloca i32, align 4
  store i32 467, ptr %fake_mem26, align 4
  %63 = load i32, ptr %fake_mem26, align 4
  %64 = load i32, ptr %retval_storage, align 4
  br i1 false, label %opaque_fake22, label %opaque_continue21

opaque_continue21:                                ; preds = %opaque_fake22, %return_block
  ret i32 %64

opaque_fake:                                      ; preds = %entry
  br i1 false, label %fake_branch28, label %continue27

fake_branch28:                                    ; preds = %opaque_fake
  br label %continue27

continue27:                                       ; preds = %fake_branch28, %opaque_fake
  br label %opaque_continue

opaque_fake2:                                     ; preds = %continue
  br label %opaque_continue1

opaque_fake4:                                     ; preds = %15
  br label %opaque_continue3

opaque_fake6:                                     ; preds = %23
  br i1 false, label %fake_branch30, label %continue29

fake_branch30:                                    ; preds = %opaque_fake6
  br label %continue29

continue29:                                       ; preds = %fake_branch30, %opaque_fake6
  br label %opaque_continue5

opaque_fake8:                                     ; preds = %continue6
  br i1 false, label %fake_branch32, label %continue31

fake_branch32:                                    ; preds = %opaque_fake8
  br label %continue31

continue31:                                       ; preds = %fake_branch32, %opaque_fake8
  br label %opaque_continue7

opaque_fake10:                                    ; preds = %49
  %fake_mem33 = alloca i32, align 4
  store i32 361, ptr %fake_mem33, align 4
  %65 = load i32, ptr %fake_mem33, align 4
  br label %opaque_continue9

opaque_fake12:                                    ; preds = %continue10
  br i1 false, label %fake_branch35, label %continue34

fake_branch35:                                    ; preds = %opaque_fake12
  br label %continue34

continue34:                                       ; preds = %fake_branch35, %opaque_fake12
  br label %opaque_continue11

opaque_fake14:                                    ; preds = %continue1
  br i1 false, label %fake_branch37, label %continue36

fake_branch37:                                    ; preds = %opaque_fake14
  br label %continue36

continue36:                                       ; preds = %fake_branch37, %opaque_fake14
  br label %opaque_continue13

opaque_fake16:                                    ; preds = %58
  br i1 false, label %fake_branch39, label %continue38

fake_branch39:                                    ; preds = %opaque_fake16
  br label %continue38

continue38:                                       ; preds = %fake_branch39, %opaque_fake16
  br label %opaque_continue15

opaque_fake18:                                    ; preds = %continue19
  %fake_mem40 = alloca i32, align 4
  store i32 986, ptr %fake_mem40, align 4
  %66 = load i32, ptr %fake_mem40, align 4
  br label %opaque_continue17

opaque_fake20:                                    ; preds = %continue5
  %fake_mem41 = alloca i32, align 4
  store i32 659, ptr %fake_mem41, align 4
  %67 = load i32, ptr %fake_mem41, align 4
  br label %opaque_continue19

opaque_fake22:                                    ; preds = %return_block
  br label %opaque_continue21
}

declare i32 @printf(ptr noundef, ...) #3

define internal ptr @decrypt_7379(ptr %0) {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca ptr, align 8
  %decrypt_buffer = alloca i8, i32 256, align 1
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %entry
  br label %continue

continue:                                         ; preds = %fake_branch, %entry
  %counter = alloca i32, align 4
  store i32 0, ptr %counter, align 4
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

loop:                                             ; preds = %dispatcher
  %1 = load i32, ptr %counter, align 4
  %2 = getelementptr i8, ptr %0, i32 %1
  %3 = getelementptr i8, ptr %decrypt_buffer, i32 %1
  %4 = load i8, ptr %2, align 1
  %5 = xor i8 %4, 111
  store i8 %5, ptr %3, align 1
  br i1 false, label %fake_branch2, label %continue1

fake_branch2:                                     ; preds = %loop
  br label %continue1

continue1:                                        ; preds = %fake_branch2, %loop
  %6 = icmp eq i8 %4, 111
  %sub.subst = sub i32 %1, -1
  store i32 %sub.subst, ptr %counter, align 4
  %7 = select i1 %6, i32 2, i32 1
  store i32 %7, ptr %switch_var, align 4
  br label %dispatcher

exit:                                             ; preds = %dispatcher
  store ptr %decrypt_buffer, ptr %retval_storage, align 8
  br i1 false, label %fake_branch4, label %continue3

fake_branch4:                                     ; preds = %exit
  br label %continue3

continue3:                                        ; preds = %fake_branch4, %exit
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %continue3, %continue1, %continue
  %8 = load i32, ptr %switch_var, align 4
  switch i32 %8, label %return_block [
    i32 1, label %loop
    i32 2, label %exit
  ]

return_block:                                     ; preds = %dispatcher
  %9 = load ptr, ptr %retval_storage, align 8
  ret ptr %9
}

define internal ptr @decrypt_6684(ptr %0) {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca ptr, align 8
  %decrypt_buffer = alloca i8, i32 256, align 1
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %entry
  br label %continue

continue:                                         ; preds = %fake_branch, %entry
  %counter = alloca i32, align 4
  store i32 0, ptr %counter, align 4
  store i32 2, ptr %switch_var, align 4
  br label %dispatcher

loop:                                             ; preds = %continue2
  %1 = load i32, ptr %counter, align 4
  %2 = getelementptr i8, ptr %0, i32 %1
  %3 = getelementptr i8, ptr %decrypt_buffer, i32 %1
  %4 = load i8, ptr %2, align 1
  %5 = xor i8 %4, -22
  store i8 %5, ptr %3, align 1
  %fake_mem = alloca i32, align 4
  store i32 571, ptr %fake_mem, align 4
  %6 = load i32, ptr %fake_mem, align 4
  %7 = icmp eq i8 %4, -22
  %sub.subst = sub i32 %1, -1
  store i32 %sub.subst, ptr %counter, align 4
  %8 = select i1 %7, i32 1, i32 2
  store i32 %8, ptr %switch_var, align 4
  br label %dispatcher

exit:                                             ; preds = %continue2
  store ptr %decrypt_buffer, ptr %retval_storage, align 8
  %fake_mem1 = alloca i32, align 4
  store i32 480, ptr %fake_mem1, align 4
  %9 = load i32, ptr %fake_mem1, align 4
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %exit, %loop, %continue
  br i1 false, label %fake_branch3, label %continue2

fake_branch3:                                     ; preds = %dispatcher
  br label %continue2

continue2:                                        ; preds = %fake_branch3, %dispatcher
  %10 = load i32, ptr %switch_var, align 4
  switch i32 %10, label %return_block [
    i32 2, label %loop
    i32 1, label %exit
  ]

return_block:                                     ; preds = %continue2
  %11 = load ptr, ptr %retval_storage, align 8
  ret ptr %11
}

define internal ptr @decrypt_8898(ptr %0) {
entry:
  %decrypt_buffer = alloca i8, i32 256, align 1
  ret ptr %decrypt_buffer
}

define internal ptr @decrypt_83(ptr %0) {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca ptr, align 8
  %decrypt_buffer = alloca i8, i32 256, align 1
  %counter = alloca i32, align 4
  store i32 0, ptr %counter, align 4
  store i32 2, ptr %switch_var, align 4
  br label %dispatcher

loop:                                             ; preds = %dispatcher
  %1 = load i32, ptr %counter, align 4
  %2 = getelementptr i8, ptr %0, i32 %1
  %3 = getelementptr i8, ptr %decrypt_buffer, i32 %1
  %4 = load i8, ptr %2, align 1
  %5 = xor i8 %4, -9
  store i8 %5, ptr %3, align 1
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %loop
  br label %continue

continue:                                         ; preds = %fake_branch, %loop
  %6 = icmp eq i8 %4, -9
  %sub.subst = sub i32 %1, -1
  store i32 %sub.subst, ptr %counter, align 4
  %7 = select i1 %6, i32 1, i32 2
  store i32 %7, ptr %switch_var, align 4
  br label %dispatcher

exit:                                             ; preds = %dispatcher
  store ptr %decrypt_buffer, ptr %retval_storage, align 8
  br i1 false, label %fake_branch2, label %continue1

fake_branch2:                                     ; preds = %exit
  br label %continue1

continue1:                                        ; preds = %fake_branch2, %exit
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %continue1, %continue, %entry
  %8 = load i32, ptr %switch_var, align 4
  switch i32 %8, label %return_block [
    i32 2, label %loop
    i32 1, label %exit
  ]

return_block:                                     ; preds = %dispatcher
  %9 = load ptr, ptr %retval_storage, align 8
  ret ptr %9
}

define internal ptr @decrypt_9156(ptr %0) {
entry:
  %decrypt_buffer = alloca i8, i32 256, align 1
  ret ptr %decrypt_buffer
}

define internal ptr @decrypt_1418(ptr %0) {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca ptr, align 8
  %decrypt_buffer = alloca i8, i32 256, align 1
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %entry
  br label %continue

continue:                                         ; preds = %fake_branch, %entry
  %counter = alloca i32, align 4
  store i32 0, ptr %counter, align 4
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

loop:                                             ; preds = %dispatcher
  %1 = load i32, ptr %counter, align 4
  %2 = getelementptr i8, ptr %0, i32 %1
  %3 = getelementptr i8, ptr %decrypt_buffer, i32 %1
  %4 = load i8, ptr %2, align 1
  %5 = xor i8 %4, -116
  store i8 %5, ptr %3, align 1
  br i1 false, label %fake_branch2, label %continue1

fake_branch2:                                     ; preds = %loop
  br label %continue1

continue1:                                        ; preds = %fake_branch2, %loop
  %6 = icmp eq i8 %4, -116
  %sub.subst = sub i32 %1, -1
  store i32 %sub.subst, ptr %counter, align 4
  %7 = select i1 %6, i32 2, i32 1
  store i32 %7, ptr %switch_var, align 4
  br label %dispatcher

exit:                                             ; preds = %dispatcher
  store ptr %decrypt_buffer, ptr %retval_storage, align 8
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %exit, %continue1, %continue
  %8 = load i32, ptr %switch_var, align 4
  switch i32 %8, label %return_block [
    i32 1, label %loop
    i32 2, label %exit
  ]

return_block:                                     ; preds = %dispatcher
  %9 = load ptr, ptr %retval_storage, align 8
  ret ptr %9
}

define internal ptr @decrypt_7265(ptr %0) {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca ptr, align 8
  %decrypt_buffer = alloca i8, i32 256, align 1
  %fake_mem = alloca i32, align 4
  store i32 700, ptr %fake_mem, align 4
  %1 = load i32, ptr %fake_mem, align 4
  %counter = alloca i32, align 4
  store i32 0, ptr %counter, align 4
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

loop:                                             ; preds = %dispatcher
  %2 = load i32, ptr %counter, align 4
  %3 = getelementptr i8, ptr %0, i32 %2
  %4 = getelementptr i8, ptr %decrypt_buffer, i32 %2
  %5 = load i8, ptr %3, align 1
  %6 = xor i8 %5, -39
  store i8 %6, ptr %4, align 1
  %7 = icmp eq i8 %5, -39
  %sub.subst = sub i32 %2, -1
  store i32 %sub.subst, ptr %counter, align 4
  %8 = select i1 %7, i32 2, i32 1
  store i32 %8, ptr %switch_var, align 4
  br label %dispatcher

exit:                                             ; preds = %dispatcher
  store ptr %decrypt_buffer, ptr %retval_storage, align 8
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %exit
  br label %continue

continue:                                         ; preds = %fake_branch, %exit
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %continue, %loop, %entry
  %fake_mem1 = alloca i32, align 4
  store i32 987, ptr %fake_mem1, align 4
  %9 = load i32, ptr %fake_mem1, align 4
  %10 = load i32, ptr %switch_var, align 4
  switch i32 %10, label %return_block [
    i32 1, label %loop
    i32 2, label %exit
  ]

return_block:                                     ; preds = %dispatcher
  %11 = load ptr, ptr %retval_storage, align 8
  ret ptr %11
}

define internal ptr @decrypt_864(ptr %0) {
entry:
  %decrypt_buffer = alloca i8, i32 256, align 1
  ret ptr %decrypt_buffer
}

define internal ptr @decrypt_151(ptr %0) {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca ptr, align 8
  %decrypt_buffer = alloca i8, i32 256, align 1
  %fake_mem = alloca i32, align 4
  store i32 218, ptr %fake_mem, align 4
  %1 = load i32, ptr %fake_mem, align 4
  %counter = alloca i32, align 4
  store i32 0, ptr %counter, align 4
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

loop:                                             ; preds = %continue
  %2 = load i32, ptr %counter, align 4
  %3 = getelementptr i8, ptr %0, i32 %2
  %4 = getelementptr i8, ptr %decrypt_buffer, i32 %2
  %5 = load i8, ptr %3, align 1
  %6 = xor i8 %5, 75
  store i8 %6, ptr %4, align 1
  %fake_mem1 = alloca i32, align 4
  store i32 90, ptr %fake_mem1, align 4
  %7 = load i32, ptr %fake_mem1, align 4
  %8 = icmp eq i8 %5, 75
  %sub.subst = sub i32 %2, -1
  store i32 %sub.subst, ptr %counter, align 4
  %9 = select i1 %8, i32 2, i32 1
  store i32 %9, ptr %switch_var, align 4
  br label %dispatcher

exit:                                             ; preds = %continue
  store ptr %decrypt_buffer, ptr %retval_storage, align 8
  %fake_mem2 = alloca i32, align 4
  store i32 984, ptr %fake_mem2, align 4
  %10 = load i32, ptr %fake_mem2, align 4
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %exit, %loop, %entry
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %dispatcher
  br label %continue

continue:                                         ; preds = %fake_branch, %dispatcher
  %11 = load i32, ptr %switch_var, align 4
  switch i32 %11, label %return_block [
    i32 2, label %exit
    i32 1, label %loop
  ]

return_block:                                     ; preds = %continue
  %12 = load ptr, ptr %retval_storage, align 8
  ret ptr %12
}

define internal ptr @decrypt_8086(ptr %0) {
entry:
  %decrypt_buffer = alloca i8, i32 256, align 1
  ret ptr %decrypt_buffer
}

define internal ptr @decrypt_2946(ptr %0) {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca ptr, align 8
  %decrypt_buffer = alloca i8, i32 256, align 1
  %counter = alloca i32, align 4
  store i32 0, ptr %counter, align 4
  store i32 1, ptr %switch_var, align 4
  br label %dispatcher

loop:                                             ; preds = %dispatcher
  %1 = load i32, ptr %counter, align 4
  %2 = getelementptr i8, ptr %0, i32 %1
  %3 = getelementptr i8, ptr %decrypt_buffer, i32 %1
  %4 = load i8, ptr %2, align 1
  %5 = xor i8 %4, 32
  store i8 %5, ptr %3, align 1
  %fake_mem = alloca i32, align 4
  store i32 715, ptr %fake_mem, align 4
  %6 = load i32, ptr %fake_mem, align 4
  %7 = icmp eq i8 %4, 32
  %sub.subst = sub i32 %1, -1
  store i32 %sub.subst, ptr %counter, align 4
  %8 = select i1 %7, i32 2, i32 1
  store i32 %8, ptr %switch_var, align 4
  br label %dispatcher

exit:                                             ; preds = %dispatcher
  store ptr %decrypt_buffer, ptr %retval_storage, align 8
  %fake_mem1 = alloca i32, align 4
  store i32 472, ptr %fake_mem1, align 4
  %9 = load i32, ptr %fake_mem1, align 4
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %exit, %loop, %entry
  %10 = load i32, ptr %switch_var, align 4
  switch i32 %10, label %return_block [
    i32 1, label %loop
    i32 2, label %exit
  ]

return_block:                                     ; preds = %dispatcher
  %11 = load ptr, ptr %retval_storage, align 8
  ret ptr %11
}

define internal ptr @decrypt_1411(ptr %0) {
entry:
  %decrypt_buffer = alloca i8, i32 256, align 1
  ret ptr %decrypt_buffer
}

define internal ptr @decrypt_7427(ptr %0) {
entry:
  %switch_var = alloca i32, align 4
  %retval_storage = alloca ptr, align 8
  %decrypt_buffer = alloca i8, i32 256, align 1
  br i1 false, label %fake_branch, label %continue

fake_branch:                                      ; preds = %entry
  br label %continue

continue:                                         ; preds = %fake_branch, %entry
  %counter = alloca i32, align 4
  store i32 0, ptr %counter, align 4
  store i32 2, ptr %switch_var, align 4
  br label %dispatcher

loop:                                             ; preds = %continue3
  %1 = load i32, ptr %counter, align 4
  %2 = getelementptr i8, ptr %0, i32 %1
  %3 = getelementptr i8, ptr %decrypt_buffer, i32 %1
  %4 = load i8, ptr %2, align 1
  %5 = xor i8 %4, -49
  store i8 %5, ptr %3, align 1
  %6 = icmp eq i8 %4, -49
  %sub.subst = sub i32 %1, -1
  store i32 %sub.subst, ptr %counter, align 4
  %7 = select i1 %6, i32 1, i32 2
  store i32 %7, ptr %switch_var, align 4
  br label %dispatcher

exit:                                             ; preds = %continue3
  store ptr %decrypt_buffer, ptr %retval_storage, align 8
  br i1 false, label %fake_branch2, label %continue1

fake_branch2:                                     ; preds = %exit
  br label %continue1

continue1:                                        ; preds = %fake_branch2, %exit
  store i32 0, ptr %switch_var, align 4
  br label %dispatcher

dispatcher:                                       ; preds = %continue1, %loop, %continue
  br i1 false, label %fake_branch4, label %continue3

fake_branch4:                                     ; preds = %dispatcher
  br label %continue3

continue3:                                        ; preds = %fake_branch4, %dispatcher
  %8 = load i32, ptr %switch_var, align 4
  switch i32 %8, label %return_block [
    i32 2, label %loop
    i32 1, label %exit
  ]

return_block:                                     ; preds = %continue3
  %9 = load ptr, ptr %retval_storage, align 8
  ret ptr %9
}

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
