#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <termios.h>

//int main()
//{
//	struct termios term;

//	int i = 0;

//	tcgetattr(STDIN_FILENO, &term);
//	printf ("%d, %d, %d, %d, %d, %d\n, %d, %d, %d, %d, %d\n", \
//	term.c_cc[VINTR],\
//	term.c_cc[VQUIT],\
//	term.c_cc[VERASE],\
//	term.c_cc[VKILL],\
//	term.c_cc[VEOF],\
//	term.c_cc[VTIME],\
//	term.c_cc[VMIN],\
//	term.c_cc[VSTART],\
//	term.c_cc[VSTOP],\
//	term.c_cc[VSUSP],\
//	term.c_cc[VEOL]);
//	term.c_cc[VINTR] = '\0';
//}

// #include <termios.h>
// #include <unistd.h>
// #include <stdio.h>

// int main() {
//   struct termios term1, term2;

//   if (tcgetattr(STDIN_FILENO, &term1) != 0)
//     perror("tcgetattr() error");
//   else {
//     printf("the original intr character is x'%02x'\n",
//            term1.c_cc[VINTR]);
//     term1.c_cc[VINTR] = 'z';
//     if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
//       perror("tcsetattr() error");
//     if (tcgetattr(STDIN_FILENO, &term1) != 0)
//       perror("tcgetattr() error");
//     else
//       printf("the new intr character is x'%02x'\n",
//              term1.c_cc[VINTR]);
//   }
// }