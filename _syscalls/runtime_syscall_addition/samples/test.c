#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <sys/types.h>

void whoami(void);

int main(int argc, char *argv[]) {
	
	whoami();

	whoami();

	return 0;
}

void whoami(void) {
	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);

//	if(pw != NULL) {
		printf("%s\n" , pw->pw_name);
		printf("%s\n" , pw->pw_passwd);
		if (strcmp("." , pw->pw_passwd )==0 ) printf("hello");
//	}
}
