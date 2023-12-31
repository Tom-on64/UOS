#ifndef __SYSTEM_H
#define __SYSTEM_H

extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern unsigned char inportb(unsigned short _port);
extern void outportb(unsigned short _port, unsigned char _data);

void cls();
void putch(unsigned char c);
void puts(unsigned char *str);
void settextcolor(unsigned char forecolor, unsigned char backcolor);
void init_video();

void idtSetGate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

void idtInstall();
void isrs_install();
struct regs
{
    unsigned int gs, fs, es, ds;                         /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by 'pusha' */
    unsigned int int_no, err_code;                       /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;           /* pushed by the processor automatically */
};

#endif
