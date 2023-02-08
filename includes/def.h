//
// Created by eduardo on 1/16/23.
//

#ifndef DEF_H
# define DEF_H

# define NOTEXEC 126
# define CMDNFND 127
# define EXIT_OFFSET 128

# ifndef SIGHUP
#  define SIGHUP 1
# endif
# ifndef SIGQUIT
#  define SIGQUIT 3
# endif
# ifndef SIGILL
#  define SIGILL 4
# endif
# ifndef SIGTRAP
#  define SIGTRAP 5
# endif
# ifndef SIGABRT
#  define SIGABRT 6
# endif
# ifndef SIGFPE
#  define SIGFPE 8
# endif
# ifndef SIGKILL
#  define SIGKILL 9
# endif
# ifndef SIGSEGV
#  define SIGSEGV 11
# endif
# ifndef SIGALRM
#  define SIGALRM 14
# endif
# ifndef SIGTERM
#  define SIGTERM 15
# endif

#endif
