extern void main() {
    *(char *)0xb8000 = 'H';
    *(char *)0xb8002 = 'e';
    *(char *)0xb8004 = 'l';
    *(char *)0xb8006 = 'l';
    *(char *)0xb8008 = 'o';
    *(char *)0xb800A = ',';
    *(char *)0xb800C = ' ';
    *(char *)0xb800E = 'W';
    *(char *)0xb8010 = 'o';
    *(char *)0xb8012 = 'r';
    *(char *)0xb8014 = 'l';
    *(char *)0xb8016 = 'd';
    *(char *)0xb8018 = '!';

    return;
}