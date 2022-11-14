# 理解RV calling Convention

---

assembly is entirely based on convention, so if you do not strictly follow convention you will not have working code. Understanding convention in RISC-V consists of 3 important parts: registers,
function calls, and entering/exiting a function (prologue/epilogue).

## registers

- x0/zero Always holds 0
- x1/ra Holds the return address 代码段的地址，函数调用完成后，pc恢复到这里储存的地址。
- x2/sp Holds the address of the boundary of the stack 即 current base，栈由高地址往地址增长先进后出，栈地址开辟需要对sp做减法，当退出函数时sp需要做加法。
- Global pointer: x3 (gp)
- Thread pointer: x4 (tp)
- x5/t0-x31/t6 Holds temporary values that do not persist after function calls，t寄存器的特点是，经过一次函数调用后，寄存器的值不保证还会存在。所以callee的prologue无需保存t寄存器，反而caller需要保存x5-x7,x28-x31(t0-t6)。
- x8/fp/s0-s11 Holds values that persist after function calls，s寄存器的特点是储存的值在经过函数调用后依旧正确有效。所以callee的prologue需要保存x18/s2-s11寄存器，反之caller无需保存。
- x10/a0-a1 Holds the first two arguments to the function or the return values
- a2-a7 Holds any remaining arguments（remaining arg words passed in parent’s stack frame）

## function calls

函数调用通常是，使用jal指令跳转到label或使用jalr指令跳转到寄存器中保存的地址，

``` jal ra label or jalr ra rd imm ```

- jal指令会将PC+4保存在ra寄存器中，
- jalr会把rd+imm保存在ra寄存器中。

调用函数时会把参数传进a寄存器并且调用结束后return值会放在a0-1寄存器中。
所以这也隐含了a寄存器在函数调用过程中无需进行额外的处理。

## prologue/epilogue

- sp寄存器退出时（做加法释放空间）的值应该和进入函数时（做减法开辟空间）的值相同。
- 所有的s寄存器都需要进行保存与恢复
- 函数推出后pc指向ra中的值

为了实现这些约定：

```
def prologue():
    Decrement sp by num s registers + local var space 为使用到的S寄存器与局部变量开辟栈存储空间
    Store any saved registers used 保存这些被用到的寄存器
    Store ra if a function call is made 如果后面有函数调用需要保存ra

def epilogue ( ) :
    Reload any saved registers used 恢复保存过的寄存器的值
    Reload ra 需要的话恢复保存的ra的值
    Increment sp back to previous value 增加sp的值释放栈空间
    Jump back to return address 跳转到ra

例子
sumsquares:
prologue:
addi sp sp −16
sw s0 0(sp)
sw s1 4(sp)
sw s2 8(sp)
sw ra 12(sp)

li s0 1
mv s1 a0
mv s2 0

loopstart:
bge s0 s1 loopend
mv a0 s0
jal square
add s2 s2 a0
addi s0 s01
j loopstart

loopend:
mv a0 s2

epilogue:
lw s0 0(sp)
lw s1 4(sp)
lw s2 8(sp)
lw ra 12(sp)
addi sp sp 16
jr ra
```

汇编代码的convention检查列表

- Check that you stored ra properly. For recursion make sure you link ra for each ecursive call. You can test this by putting a break point at the end of the epilogue and seeing where you return.
- Check that you don’t use any t registers after a function call.
- Check that sp enters and exits with the same value.
- Check the number of times you enter the prologue equals the number of times you enter the epilogue.
- Make sure you restore every register you modified.

## 介绍下call stack aka stack frame

Each activation record contains
• the return address for that invocation
• the local variables for that procedure
A stack pointer (sp) keeps track of
the top of the stack
• dedicated register (x2) on the RISC-V
Manipulated by push/pop operations
• push: move sp down, store
• pop: load, move sp up

(Call) Stacks start at a high address in memory
Stacks grow down as frames are pushed on
• Note: data region starts at a low address and grows up
• The growth potential of stacks and data region are not
artificially limited
Return Address lives in Stack Frame
Stack contains stack frames (aka “activation records”)
• 1 stack frame per dynamic function
• Exists only for the duration of function
• Grows down, “top” of stack is sp, x2
• Example: lw x5, 0(sp) puts word at top of stack into x5
Each stack frame contains:
• Local variables, return address (later), register
backups (later)

First eight arguments:
passed in registers x10-x17
• aka a0, a1, …, a7
Subsequent arguments:
”spill” onto the stack
Args passed in child’s
stack frame

x8, aka fp (also known as s0)
can be used to restore sp on exit
