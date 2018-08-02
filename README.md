# md5_sha256
A reproduction of openssl md5 and sha256 cryptographic hashing algorithms

## Compiling and running
Run `make`. An executable will compile. Currently only tested on OS X.
Run `./ft_ssl`.
usage: ft_ssl command [command opts] [command args]

##Avaliable flags:
* -p, echo STDIN to STDOUT and append the checksum to STDOUT
* -q, quiet mode
* -r, reverse the format of the output
* -s, print the sum of the given string
