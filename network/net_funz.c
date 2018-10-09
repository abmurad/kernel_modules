
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/delay.h>

char *int_ascii ( unsigned long int ) ;

char* _tok ( char *str , char* str2 ) ;

unsigned long int ascii_int(char*) ;

unsigned long int htonl_u ( unsigned long int ) ;

long long int _atoi( char *buf ) ;

long long int _atoi( char *buf ) {

#define CH *( buf + var )

                int var = 0;

                long long int data = 0 ;

                int minus_flag = 1;

                while ( *buf == ' '  || *buf == '\t') {

                                buf++;
                }

                if ( *buf == '-' ) {

                                minus_flag = -1;

                                var++;

                }

                if ( *buf == '+' ) {

                                var++;

                }

                while( CH  ) {

                                if ( CH == ' ' || CH == '\t' || CH == '\n' );

                                else if( CH !='.' ) {

                                                CH = CH - '0' ;

                                                data *= 10 ;

                                                data += ( CH ) ;

                                }

                                else {
                                                break;
                                }

                                var++;

                }

                return data * minus_flag ;
}

unsigned long int ascii_int ( char *str ) 
{
		char *temp = str ;

		char *token = NULL ;

		int i = 0 ;

		static unsigned char arr[4] = {} ;

		token = _tok( str , "u") ;

		i = 3 ;

		while ( token != NULL ) {

				arr[ i-- ] = _atoi ( token ) ;

				token = _tok ( NULL , ".") ;

		}
		return *(int*)arr ;

}

unsigned long int htonl_u ( unsigned long int integer )
{

		printk ("receiced is %lu\n" , integer ); 

		int i = 0 ;

		static unsigned char arr[4] = {} ;
		
		memset (arr , 0 , 4) ;

		int some = 24 ;

		int x = integer ;

		unsigned int mask = 0xff000000 ;


		while ( i < 4 ) {

				arr[i] =  (integer & mask) >> some  ;

				printk ("arr[%d] is %d\n" , i , arr[i]) ;

				mask >>= 8 ;

				some= some - 8 ;
			
				i++ ;

		}
		printk ("sending is is %u : %u :%u :%u\n" ,arr[0] , arr[1] , arr[2] , arr[3] ); 

		return *((int*)arr) ;

}

char *int_ascii ( unsigned long integer )
{

		int some = 24 ;

		unsigned int mask = 0xff000000 ;

		static char array [15] = {} ;

		int index = 0 ;

		int temp = 0 ;

		int rem = 0 ;

		int i = 0 ;

		int var = 100 ;

		static unsigned char arr[4] = {} ;

		while ( i < 4 ) {

				arr[i++] =  (integer & mask) >> some  ;

				temp = arr [ i-1 ] ;

				var = 100 ;

				while ( var) {

						rem = temp / var ;

						rem = rem + 48 ;

						if ( rem != 48 || var == 1 )	

								array[index++] = rem ; 

						//				if ( !(temp == (temp % var)) ) temp = 0 ;

						//				else

						temp = temp%var ;

						if ( var == 1 ) var = 0 ; ;

						var= var / 10 ;


				}	

				array[index++] = '.' ;

				mask >>= 8 ;

				some-=8 ;

		}

		array[--index] = '\0' ;

		return array ;

}
char* _tok ( char *str , char* str2 ) {

        static char *ptr ;

        int var = 0 ;

        int var2 = 0 ;

        if ( str == NULL ) {

                str = ptr;

                if ( ptr == NULL )

                        return NULL;

        }

        while( * (str + var) ) {    //first while

                var2 = 0;

                while ( * ( str2 + var2 ) ) {   //second while

                        if ( *( str + var ) == * ( str2 + var2 ) )      {

                                * ( str + var  ) = '\0';

                                var2 = 0 ;

                                while ( *( str2 + var2 ) && * ( str + var + 1 ) && 1 ) {

                                        if ( *( str2 + var2 ) == *( str +var + 1 ) ) {

                                                var ++ ; var2 = 0 ;

                                        }
                                        else {
                                                if ( ! * (str2 + var2 ) ) {

                                                        ptr = ( str + var + 1  );

                                                        if ( ! *str && ptr == NULL  ) return NULL ;

                                                        return str;
                                                }
                                                var2++ ;
                                        }
                                }

                                ptr = ( str + var + 1  );

                                if ( ! *str ) { str = ptr ; var2 = 0 ; var = 0 ; continue ;}

                                return str;
                        }
                        var2 ++;
                }

                var ++ ;

        } // first while ends

        ptr = NULL ;

        return str;

}

/*int __init init_module ( void )
{
        printk ( "nothing much\n" ) ;
        return 0 ;
}
void __exit cleanup_module ( void )
{
        printk ("well! c u\n");
}*/
EXPORT_SYMBOL(int_ascii);
EXPORT_SYMBOL( ascii_int);
EXPORT_SYMBOL(_tok);
EXPORT_SYMBOL(_atoi);
EXPORT_SYMBOL(htonl_u);
