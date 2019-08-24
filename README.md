# What does "primos" do?

It is a simple prime-number prospector for GNU/Linux. It starts looking for prime numbers in an infinite loop starting from the number passed as an argument. For example:
```
$ primos 55555
```

In that case, it will check whether 55555 is a prime number and then 55557, 55559 and so on (even numbers are skipped because they are never prime, except number 2).

There is no size limit. Starting number can have as many ciphers as wanted. Only hardware and time are the limit.


# Execution
```
$ primos -h
Usage: <executable_file> [-b] [-h] [-n <opt_n_output>] [-p] <starting_value>


Argument (mandatory):
<starting_value>: first number to calculate whether it is a prime or not.

Options:
-b: Stop execution when a prime number is found.
-h: show this help text.
-n <opt_n_output>: limit amount of numbers to calculate. With -p only prime numbers will be count.
-p: show only prime numbers.
```


# Compilation

## Requirement
[GMP library]([GitHub Pages](https://pages.github.com/) required. It is installed by default on many GNU/Linux distributions.

## How to compile
```
$ gcc primos.c -o primos -lgmp
```
