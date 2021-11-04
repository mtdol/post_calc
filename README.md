# C Calculator  
A calculator application written in C.

# Files  
## to_post.c  
converts an infix arithmetic expression to a postfix one  
`1+2` to `12+`  
## post_calc.c  
takes a postfix arithmetic expression and computes it  
`12+` to `3`  
## compute.sh  
runs both applications in order to compute an infix expression  

# Compile  
```
gcc to_post.c -o to_post.exe
gcc post_calc.c -o post_calc.exe
```

# Run 
The calculator only supports single digit numbers as input.  
## to_post.exe  
Enter the input as a single string  
`./to_post.exe "1 + 2"`
## post_calc.exe  
Enter the input as a single string  
`./post_calc.exe "1 2 +"`
## compute.sh  
Enter the input as a single string  
`./compute.sh "1 + 2"`
