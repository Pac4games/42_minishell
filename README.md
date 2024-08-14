# Minishell

This is mine and [Uxixa's](https://github.com/Pedrocasss) attempt at creating a [shell program](https://en.wikipedia.org/wiki/Shell_(computing)) that behaves similarly to the [Bash shell](https://en.wikipedia.org/wiki/Bash_(Unix_shell)).
We had to follow very specific requirements set by the project's [subject](https://cdn.intra.42.fr/pdf/pdf/138329/en.subject.pdf).
The most important requirements are:
- The shell must behave as closely to Bash as possible
- It has to be written following the [42 Norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf)
- Any type of memory leaks are unnacceptable, including open file descriptors when exiting the shell. The only leaks allowed are the ones caused by `readline`, since we have no control over the code included in that third-part library
