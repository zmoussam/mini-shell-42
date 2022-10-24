<html>
# Minishell42
This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors.
<h1>GNU Readline library</h1>
This document describes the GNU Readline Library, a utility which aids in the consistency of user interface across discrete programs which provide a command line 
interface. The Readline home page is http://www.gnu.org/software/readline/.
<h2>Custom Functions</h2>

Readline provides many functions for manipulating the text of the line,
but it isn’t possible to anticipate the needs of all programs. This section describes 
the various functions and variables defined within the Readline library
which allow a user program to add customized functionality to Readline.

Before declaring any functions that customize Readline’s behavior, 
or using any functionality Readline provides in other code, 
an application writer should include the file <readline/readline.h> in 
any file that uses Readline’s features. Since some of the definitions in readline.h
use the stdio library, the file <stdio.h> should be included before readline.h.

readline.h defines a C preprocessor variable that should be treated as an integer, 
RL_READLINE_VERSION, which may be used to conditionally compile application code 
depending on the installed Readline version. The value is a hexadecimal encoding 
of the major and minor version numbers of the library, of the form 0xMMmm. 
MM is the two-digit major version number; mm is the two-digit minor version number. 
For Readline 4.2, for example, the value of RL_READLINE_VERSION would be 0x0402.

<h2>Readline functions use on this project</h2>
<h3>readline() :</h3>
Many programs provide a command line interface, such as mail, ftp, and sh. 
For such programs, the default behaviour of Readline is sufficient. 
This section describes how to use Readline in the simplest way possible, 
perhaps to replace calls in your code to gets() or fgets().

The function readline() prints a prompt prompt and then reads and returns a
single line of text from the user. If prompt is NULL or the empty string, no
prompt is displayed. The line readline returns is allocated with malloc(); the caller should free() 
the line when it has finished with it. The declaration for readline in ANSI C is
             char *readline (const char *prompt);
So, one might say:
 </html>             
