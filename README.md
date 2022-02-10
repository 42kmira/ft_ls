<br>
<img align="left" height="250" src="https://github.com/42kmira/ft_ls/blob/master/resources/README.png" />
<br>

The goal of this project was to recreate partial functionality of the program ```ls```.

Usage: ```./ft_ls [-RSUacflrtu1] [file ...]```

Handles sticky bits, certain errors like permission denied, nonexistent paths, flag errors, and the flags seen above.

Implements a comparison function for the sorting of the files, which include modify time sorting, file creation, no sorting, size sorting, lexical sorting. The `r` flag then is applicable to all and any such function and it reverses the sorting. This is done without the need of making a comparison for the reverse sort.

Sorting is done through the use of a binary tree, meaning that inserts take O(log(N)). Due to the
`R` it is imperative that resources are not wasted and that no memory is lost as some of these
binary trees may be huge.

Output is buffered to minimize calls to write, a costly system call to the kernel. Output is colored by default, but can be toggled off by the `c` flag.

I have aliased ```ls``` to run my program instead, below is a gif showing the program in action.

<br>
<img align="left" height="600" src="https://github.com/42kmira/ft_ls/blob/master/resources/ft_ls.gif" />
<br>
