
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

<h2>Readline functions used on this project</h2>
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
            char *line = readline ("Enter a line: ");in order to read a line of text from the user. The line returned has the final newline removed, so only the text remains.

If readline encounters an EOF while reading the line, and the line is empty at that point, then (char *)NULL is returned. Otherwise, the line is ended just as if a newline had been typed.

<h3>add_history() :</h3>

If you want the user to be able to get at the line later, (with C-p for example), you must call add_history() to save the line away in a history list of such lines.
add_history (line);
For full details on the GNU History Library, see the associated manual.

<h3>rl_on_new_line() : </h3>

Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.

<h3>rl_clear_history()</h3>

Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.

<h3>rl_replace_line(const char*text, int clear_undo)</h3>
   Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
   

<h3>rl_redisplay() : </h3>
Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

<h2>Readline variables used on this project</h2>
These variables are available to function writers.
<h3>int rl_done</h3>

Setting this to a non-zero value causes Readline to return the current line immediately.
Readline will set this variable when it has read a key sequence bound to accept-line and is about to return the line to the caller.

<h3>rl_hook_func_t * rl_event_hook</h3>
If non-zero, this is the address of a function to call periodically when Readline is waiting 
for terminal input. By default, this will be called at most ten times a second if there is no keyboard input.

<h3>int rl_catch_signals</h3>
 If this variable is non-zero, Readline will install signal handlers for SIGINT, SIGQUIT, SIGTERM, SIGHUP, SIGALRM, SIGTSTP, SIGTTIN, and SIGTTOU.

The default value of rl_catch_signals is 1
