; mark_description "Intel(R) C Intel(R) 64 Compiler XE for applications running on Intel(R) 64, Version 14.0.1.106 Build 2013100";
; mark_description "8";
; mark_description "-S -fsource-asm";
        ;FILE "helloworld.c"
        SECTION .text
..TXTST0: 
; -- Begin  main
; mark_begin;
       ALIGN 16, db 090h
        GLOBAL main
main: 
; parameter 1: %edi
; parameter 2: %rsi
..B1.1:                          ; Preds ..B1.0

;;; {

..___tag_value_main.1:                                           ;3.1
MISMATCH: "        pushq     %rbp                                          "
..___tag_value_main.3:                                           ;
        movq      rbp,rsp                                       ;3.1
..___tag_value_main.4:                                           ;
MISMATCH: "        andq      $-128, %rsp                                   "
MISMATCH: "        subq      $128, %rsp                                    "
        movq      rsi,0000000000h                               ;3.1
        mov       edi,3                                         ;3.1
        call      __intel_new_feature_proc_init                 ;3.1
                                ; LOE rbx r12 r13 r14 r15
..B1.5:                          ; Preds ..B1.1
        stmxcsr   [rsp]                                         ;3.1

;;;     puts("hello, world!");

        mov       edi, .L_2__STRING.0                           ;4.2
        or        dword [rsp],32832                             ;3.1
        ldmxcsr   [rsp]                                         ;3.1
        call      puts                                          ;4.2
                                ; LOE rbx r12 r13 r14 r15
..B1.2:                          ; Preds ..B1.5

;;;     return 0;

        xor       eax,eax                                       ;5.9
        movq      rsp,rbp                                       ;5.9
MISMATCH: "        popq      %rbp                                          "
..___tag_value_main.6:                                           ;
        ret                                                     ;5.9
        ALIGN 16, db 090h
..___tag_value_main.8:                                           ;
                                ; LOE
; mark_end;
        GLOBAL main:function
        GLOBAL  main:function (.-main)
        SECTION .data
; -- End  main
MISMATCH: "        .section .rodata.str1.4, "aMS",@progbits,1"
        ALIGN 4
        ALIGN 4
.L_2__STRING.0: 
        dd      1819043176
        dd      1998597231
        dd      1684828783
        dw      33
        GLOBAL .L_2__STRING.0:object
        ;.size  .L_2__STRING.0, 14
        SECTION .data
MISMATCH: "        .section .note.GNU-stack, """
; -- Begin DWARF2 SEGMENT .eh_frame
MISMATCH: "        .section .eh_frame,"a",@progbits"
.eh_frame_seg: 
        ALIGN 8
MISMATCH: "        .4byte 0x00000014"
MISMATCH: "        .8byte 0x7801000100000000"
MISMATCH: "        .8byte 0x0000019008070c10"
MISMATCH: "        .4byte 0x00000000"
MISMATCH: "        .4byte 0x00000034"
MISMATCH: "        .4byte 0x0000001c"
MISMATCH: "        .8byte ..___tag_value_main.1"
MISMATCH: "        .8byte ..___tag_value_main.8-..___tag_value_main.1"
        db    004h
MISMATCH: "        .4byte ..___tag_value_main.3-..___tag_value_main.1"
MISMATCH: "        .2byte 0x100e"
        db    004h
MISMATCH: "        .4byte ..___tag_value_main.4-..___tag_value_main.3"
MISMATCH: "        .4byte 0x8610060c"
MISMATCH: "        .2byte 0x0402"
MISMATCH: "        .4byte ..___tag_value_main.6-..___tag_value_main.4"
MISMATCH: "        .8byte 0x00000000c608070c"
MISMATCH: "        .2byte 0x0000"
; End

