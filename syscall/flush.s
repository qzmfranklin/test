# mark_description "Intel(R) C Intel(R) 64 Compiler XE for applications running on Intel(R) 64, Version 14.0.1.106 Build 2013100";
# mark_description "8";
# mark_description "-S";
	.file "flush.c"
	.text
..TXTST0:
# -- Begin  main
# mark_begin;
       .align    16,0x90
	.globl main
main:
# parameter 1: %edi
# parameter 2: %rsi
..B1.1:                         # Preds ..B1.0
..___tag_value_main.1:                                          #6.1
        pushq     %rbp                                          #6.1
..___tag_value_main.3:                                          #
        movq      %rsp, %rbp                                    #6.1
..___tag_value_main.4:                                          #
        andq      $-128, %rsp                                   #6.1
        subq      $128, %rsp                                    #6.1
        movq      $0x000000000, %rsi                            #6.1
        movl      $3, %edi                                      #6.1
        call      __intel_new_feature_proc_init                 #6.1
                                # LOE rbx r12 r13 r14 r15
..B1.5:                         # Preds ..B1.1
        stmxcsr   (%rsp)                                        #6.1
        movl      $511, %edi                                    #7.2
        xorl      %eax, %eax                                    #7.2
        orl       $32832, (%rsp)                                #6.1
        ldmxcsr   (%rsp)                                        #6.1
..___tag_value_main.6:                                          #7.2
        call      syscall                                       #7.2
..___tag_value_main.7:                                          #
                                # LOE rbx r12 r13 r14 r15
..B1.2:                         # Preds ..B1.5
        xorl      %eax, %eax                                    #8.9
        movq      %rbp, %rsp                                    #8.9
        popq      %rbp                                          #8.9
..___tag_value_main.8:                                          #
        ret                                                     #8.9
        .align    16,0x90
..___tag_value_main.10:                                         #
                                # LOE
# mark_end;
	.type	main,@function
	.size	main,.-main
	.data
# -- End  main
	.data
	.section .note.GNU-stack, ""
// -- Begin DWARF2 SEGMENT .eh_frame
	.section .eh_frame,"a",@progbits
.eh_frame_seg:
	.align 8
	.4byte 0x00000014
	.8byte 0x7801000100000000
	.8byte 0x0000019008070c10
	.4byte 0x00000000
	.4byte 0x00000034
	.4byte 0x0000001c
	.8byte ..___tag_value_main.1
	.8byte ..___tag_value_main.10-..___tag_value_main.1
	.byte 0x04
	.4byte ..___tag_value_main.3-..___tag_value_main.1
	.2byte 0x100e
	.byte 0x04
	.4byte ..___tag_value_main.4-..___tag_value_main.3
	.4byte 0x8610060c
	.2byte 0x0402
	.4byte ..___tag_value_main.8-..___tag_value_main.4
	.8byte 0x00000000c608070c
	.2byte 0x0000
# End
