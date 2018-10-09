/*property of umaraZ Inc written for GLOBALEDGESOFT p LTD */

#include    <uma.h>

//#include    <strings.h>

#define _SIGN 2147483647

#define set 1

#define reset 0

#define CHAR ( ( *(buf + var)   >= '0'  && *(buf + var)   <= '9' ) || ( *( buf + var ) =='\0' ) )

#define SIGN ( *(buf + var)   == '+' || *(buf + var)   == '-' )

#define SPACE ( *(buf + var)   == ' ' || *(buf + var)   == '\t' || *(buf + var)   == '\n' )

#define DOT ( *(buf + var)  == '.' )

long long int _atoi ( char *) ;

int _val (char* passed_string) {

		unsigned char variable = 1;

		while ( variable ) {

				char *buf = NULL;

				unsigned short var = 0;

				char char_flag = 0;

				char space_flag = 0;

				char sign_flag = 0;

				char dot_count = 0;

				char dot_flag = 0;

				long long int final_value = 0;

				var = 0 ;

				if ( passed_string == NULL ) puts(B"enter a integer"Z);

				else  printf(B"enter %s\n"Z,passed_string);

				__fpurge(stdin);        

				if ( getchar() == EOF ) continue ;

				buf = --stdin -> _IO_read_ptr ;

				while ( *(buf + var) =='\t' || *(buf + var) ==' ' ) var++;
				
				if ( *( buf+var ) == '\n' ) {

						puts(R"new line will not be enough"Z);

						continue;
				}

				var = 0;
		
				while ( * ( buf + var ) != '\n'  && ( * ( buf + var ) != '\0' || !puts(""))) var++ ;

				* ( buf + var )= '\0' ;

				var = 0 ;

				variable = 0 ;

				while ( *(buf + var) ) {

						if (  CHAR  ) {

								if ( space_flag == reset) {

										char_flag = set ;

										var++ ;

										continue ;
								}

								else {
										puts(R"mis placed white spaces"Z);

										break;
								}
						}

						else if ( SIGN ) {

								if ( char_flag == set || dot_flag  ) {

										puts( R"mis placed sign"Z);

										break;
								}

								sign_flag ++ ;

								if ( sign_flag > 1 ) {

										puts( R"invalid usage of sign"Z );

										break;
								}
						}

						else if ( DOT ) {

								dot_count++ ;

								if ( dot_count > 1 || space_flag ) {

										puts(R"mis use of decimal point"Z);

										break;
								}

								dot_flag = set ;
						}

						else if ( SPACE ) {

								if (   dot_count  && !char_flag) {

										puts ( R"decimal followed by spaces"Z );

										break;
								}

								if ( char_flag == set ) {

										space_flag = set ;
								}
						}

						else  {

								printf( R"alien characters in integer set %s\n"Z , buf );

								break;
						}

						var++;

				} // while loop ends here 

				variable = 1 ;

				if (* (buf + var ) == '\0' ) {

						final_value =  _atoi(buf);

						if ( final_value > _SIGN || ( final_value < - _SIGN - 1) ) {

								puts(R"overflow cant fit interger in"Z);
	
								__fpurge(stdin);        

								continue ;
						}

						else 
								return final_value ;

				}
		}
		return 0;
}

long long int _atoi( char *buf ) {

#define ch *( buf + var )

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

                while( ch  ) {

                                if ( ch == ' ' || ch == '\t' || ch == '\n' );

                                else if( ch !='.' ) {

                                                ch = ch - '0' ;

                                                data *= 10 ;

                                                data += ( ch ) ;

                                }

                                else {
                                                break;
                                }

                                var++;

                }

                return data * minus_flag ;
}
