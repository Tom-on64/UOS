struct idtEntry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idtPtr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idtEntry idt[256];
struct idtPtr idtp;

extern void idtLoad();

/* Use this function to set an entry in the IDT. Alot simpler
 *  than twiddling with the GDT ;) */
void idtSetGate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num].base_lo = (unsigned int)base;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].base_hi = (unsigned int)(base >> 16);
}

void idtInstall()
{
    // Setup IDT pointer
    idtp.limit = (sizeof(struct idtEntry) * 256) - 1;
    idtp.base = &idt;

    // Clear IDT
    memset(&idt, 0, sizeof(struct idtEntry) * 256);

    // idtSetGate();

    idtLoad();
}

extern void main()
{
    idtInstall();
    return;
}