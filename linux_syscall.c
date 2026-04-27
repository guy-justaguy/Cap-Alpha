#include <stdint.h>

extern void processfork();
uint64_t syscall(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, ...);
uint64_t LINUZSYS()
{
    if (syscall == 0)
    {

    //filediscriptopen() coming soon!

    if (syscall == 1)
    {
        //filediscriptclose() coming soon!
    }
     if (syscall == 2)
    { 
        //filediscriptread coming soon!
    }
     if (syscall == 3)
    {
        //filediscriptwrite() coming soon!
    }
    if (syscall == 57)
    {
        processfork();



    }   
}
}
