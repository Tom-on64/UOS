#include "system.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void isrs_install()
{
    idtSetGate(0, (unsigned)isr0, 0x08, 0x8E);
    idtSetGate(1, (unsigned)isr1, 0x08, 0x8E);
    idtSetGate(2, (unsigned)isr2, 0x08, 0x8E);
    idtSetGate(3, (unsigned)isr3, 0x08, 0x8E);
    idtSetGate(4, (unsigned)isr4, 0x08, 0x8E);
    idtSetGate(5, (unsigned)isr5, 0x08, 0x8E);
    idtSetGate(6, (unsigned)isr6, 0x08, 0x8E);
    idtSetGate(7, (unsigned)isr7, 0x08, 0x8E);
    idtSetGate(8, (unsigned)isr8, 0x08, 0x8E);
    idtSetGate(9, (unsigned)isr9, 0x08, 0x8E);
    idtSetGate(10, (unsigned)isr10, 0x08, 0x8E);
    idtSetGate(11, (unsigned)isr11, 0x08, 0x8E);
    idtSetGate(12, (unsigned)isr12, 0x08, 0x8E);
    idtSetGate(13, (unsigned)isr13, 0x08, 0x8E);
    idtSetGate(14, (unsigned)isr14, 0x08, 0x8E);
    idtSetGate(15, (unsigned)isr15, 0x08, 0x8E);
    idtSetGate(16, (unsigned)isr16, 0x08, 0x8E);
    idtSetGate(17, (unsigned)isr17, 0x08, 0x8E);
    idtSetGate(18, (unsigned)isr18, 0x08, 0x8E);
    idtSetGate(19, (unsigned)isr19, 0x08, 0x8E);
    idtSetGate(20, (unsigned)isr20, 0x08, 0x8E);
    idtSetGate(21, (unsigned)isr21, 0x08, 0x8E);
    idtSetGate(22, (unsigned)isr22, 0x08, 0x8E);
    idtSetGate(23, (unsigned)isr23, 0x08, 0x8E);
    idtSetGate(24, (unsigned)isr24, 0x08, 0x8E);
    idtSetGate(25, (unsigned)isr25, 0x08, 0x8E);
    idtSetGate(26, (unsigned)isr26, 0x08, 0x8E);
    idtSetGate(27, (unsigned)isr27, 0x08, 0x8E);
    idtSetGate(28, (unsigned)isr28, 0x08, 0x8E);
    idtSetGate(29, (unsigned)isr29, 0x08, 0x8E);
    idtSetGate(30, (unsigned)isr30, 0x08, 0x8E);
    idtSetGate(31, (unsigned)isr31, 0x08, 0x8E);
}

unsigned char *exception_messages[] =
    {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Into Detected Overflow",
        "Out of Bounds",
        "Invalid Opcode",
        "No Coprocessor",
        "Double Fault",
        "Coprocessor Segment Overrun",
        "Bad TSS",
        "Segment Not Present",
        "Stack Fault",
        "General Protection Fault",
        "Page Fault",
        "Unknown Interrupt",
        "Coprocessor Fault",
        "Alignment Check",
        "Machine Check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"};

extern void fault_handler(struct regs *r)
{
    /* Is this a fault whose number is from 0 to 31? */
    if (r->int_no < 32)
    {
        /* Display the description for the Exception that occurred.
         *  In this tutorial, we will simply halt the system using an
         *  infinite loop */
        puts(exception_messages[r->int_no]);
        puts(" Exception. System Halted!\n");
        for (;;)
            ;
    }
}