#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/delay.h>

int __init init_module ( void ) 
{
	printk ( "nothing much" ) ;
	return 0 ;
}
void __exit cleanup_module ( void ) 
{
	printk ("well! c u");
}

void print_key ( unsigned char scancode ) 
{

#if 1

printk ("#%x#",scancode);

switch( scancode ) {

                case 0x10 :
                case 0x10 + 0x80:
                        printk (" ****  Q  ****\n");
                        break ;
                case 0x11 :
                case 0x11 + 0x80:
                        printk (" ****  W  ****\n");
                        break ;
                case 0x12 :
                case 0x12 + 0x80:
                        printk (" ****  E  ****\n");
                        break ;
                case 0x13 :
                case 0x13 + 0x80:
                        printk (" ****  R  ****\n");
                        break ;
                case 0x14 :
                case 0x14 + 0x80:
                        printk (" ****  T  ****\n");
                        break ;
                case 0x15 :
                case 0x15 + 0x80:
                        printk (" ****  Y  ****\n");
                        break ;
                case 0x16 :
                case 0x16 + 0x80:
                        printk (" ****  U  ****\n");
                        break ;
                case 0x17 :
                case 0x17 + 0x80:
                        printk (" ****  I  ****\n");
                        break ;
                case 0x18 :
                case 0x18 + 0x80:
                        printk (" ****  O  ****\n");
                        break ;
                /*case 0x20 :
                case 0x20 + 0x80:
                        printk (" ****  { or [  ****\n");
                        break ;*/
                case 0x19 :
                case 0x19 + 0x80:
                        printk (" ****  P  ****\n");
                        break ;
                /*case 0x21 :
                case 0x21 + 0x80:
                        printk (" ****  } or ]  ****\n");
                        break ;
                case 0x22 :
                case 0x22 + 0x80:
                        printk (" ****  | or \\  ****\n");
                        break ;*/
                case 0x1e :
                case 0x1e + 0x80:
                        printk (" ****  A  ****\n");
                        break ;
                case 0x1f :
                case 0x1f + 0x80:
                        printk (" ****  S  ****\n");
                        break ;
                case 0x20 :
                case 0x20 + 0x80:
                        printk (" ****  D  ****\n");
                        break ;
                case 0x21 :
                case 0x21 + 0x80:
                        printk (" ****  F  ****\n");
                        break ;
                case 0x22 :
                case 0x22 + 0x80:
                        printk (" ****  G  ****\n");
                        break ;
                case 0x23 :
                case 0x23 + 0x80:
                        printk (" ****  H  ****\n");
                        break ;
                case 0x24 :
                case 0x24 + 0x80:
                        printk (" ****  J  ****\n");
                        break ;
                case 0x25 :
                case 0x25 + 0x80:
                        printk (" ****  K  ****\n");
                        break ;
                case 0x26 :
                case 0x26 + 0x80:
                        printk (" ****  L  ****\n");
                        break ;
                case 0x27 :
                case 0x27 + 0x80:
                        printk (" ****  : or ;  ****\n");
                        break ;
                case 0x28 :
                case 0x28 + 0x80:
                        printk (" ****  \" or '  ****\n");
                        break ;
                case 0x2d :
                case 0x2d + 0x80:
                        printk (" ****  X  ****\n");
                        break ;
                case 0x2e :
                case 0x2e + 0x80:
                        printk (" ****  C  ****\n");
                        break ;
                case 0x2f :
                case 0x2f + 0x80:
                        printk (" ****  V  ****\n");
                        break ;
                case 0x30 :
                case 0x30 + 0x80:
                        printk (" ****  B  ****\n");
                        break ;
                case 0x31 :
                case 0x31 + 0x80:
                        printk (" ****  N  ****\n");
                        break ;
                case 0x32 :
                case 0x32 + 0x80:
                        printk (" ****  M  ****\n");
                        break ;
                case 0x33 :
                case 0x33 + 0x80:
                        printk (" ****  < or ,  ****\n");
                        break ;
                case 0x34 :
                case 0x34 + 0x80:
                        printk (" ****  > or .  ****\n");
                        break ;
                case 0x35 :
                case 0x35 + 0x80:
                        printk (" ****  ? or /  ****\n");
                        break ;
                case 2 :
                case 2 + 0x80:
                        printk (" ****  1  ****\n");
                        break ;
                case 3 :
                case 3 + 0x80:
                        printk (" ****  2  ****\n");
                        break ;
                case 4 :
                case 4 + 0x80:
                        printk (" ****  3  ****\n");
                        break ;
                case 5 :
                case 5 + 0x80:
                        printk (" ****  4  ****\n");
                        break ;
                case 6 :
                case 6 + 0x80:
                        printk (" ****  5  ****\n");
                        break ;
                case 7 :
                case 7 + 0x80:
                        printk (" ****  6  ****\n");
                        break ;
                case 8 :
                case 8 + 0x80:
                        printk (" ****  7  ****\n");
                        break ;
                case 9 :
                case 9 + 0x80:
                        printk (" ****  8  ****\n");
                        break ;
                case 10 :
                case 10 + 0x80:
                        printk (" ****  9  ****\n");
                        break ;
                case 11 :
                case 11 + 0x80:
                        printk (" ****  0  ****\n");
                        break ;
                case 12 :
                case 12 + 0x80:
                        printk (" ****  - or _  ****\n");
                        break ;
                case 13 :
                case 13 + 0x80:
                        printk (" ****  = or +  ****\n");
                        break ;
                case 14 :
                case 14 + 0x80:
                        printk (" ****  backspace  ****\n");
                        break ;
                case 0x39 :
                case 0x39 + 0x80:
                        printk (" ****  space  ****\n");
                        break ;
                case 0x2a :
		case 0x36:
		case 0x36 + 0x80 :
                case 0x2a + 0x80:
                        printk (" ****  shift  ****\n");
                        break ;
                case 0x1d :
                case 0x1d + 0x80:
                        printk (" ****  ctrl  ****\n");
                        break ;
                case 0xf :
                case 0xf + 0x80:
                        printk (" ****  tab  ****\n");
                        break ;
                case 0x1c :
                case 0x1c + 0x80:
                        printk (" ****  enter  ****\n");
                        break ;
                case 0x1 :
                case 0x1 + 0x80:
                        printk (" ****  ESC  ****\n");
                        break ;
                case 0x38 :
		case 0xe0:
                case 0x38 + 0x80:
                        printk (" ****  alt  ****\n");
                        break ;
		case 0x3b:
                case 0x3b + 0x80:
                        printk (" ****  f1  ****\n");
                        break ;
		case 0x3c:
                case 0x3c + 0x80:
                        printk (" ****  f2  ****\n");
                        break ;
		case 0x3d:
                case 0x3d + 0x80:
                        printk (" ****  f3  ****\n");
                        break ;
		case 0x3e:
                case 0x3e + 0x80:
                        printk (" ****  f4  ****\n");
                        break ;
		case 0x3f:
                case 0x3f + 0x80:
                        printk (" ****  f5  ****\n");
                        break ;
		case 0x40:
                case 0x40 + 0x80:
                        printk (" ****  f6  ****\n");
                        break ;
		case 0x41:
                case 0x41 + 0x80:
                        printk (" ****  f7  ****\n");
                        break ;
		case 0x42:
                case 0x42 + 0x80:
                        printk (" ****  f8  ****\n");
                        break ;
		case 0x43:
                case 0x43 + 0x80:
                        printk (" ****  f9  ****\n");
                        break ;
		case 0x44:
                case 0x44 + 0x80:
                        printk (" ****  f10  ****\n");
                        break ;
		case 0x57:
                case 0x57 + 0x80:
                        printk (" ****  f11  ****\n");
                        break ;
		case 0x58:
                case 0x58 + 0x80:
                        printk (" ****  f12  ****\n");
                        break ;

                default:

                        printk("alien key for now\n");
                        break ;

                }
#endif
}
EXPORT_SYMBOL ( print_key ) ;
MODULE_LICENSE("GPL v2");
