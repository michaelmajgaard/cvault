# cvault
Command line password manager written i C. Uses xor OTP encryption. Probably shouldn't be used for anything important. Was fun to write though.

```
usage:
        cvault add -e <entry> -v <value> -k <directory> -d <directory>
        cvault get -e <entry> -k <directory> -d <directory>
        cvault delete -e <entry> -k <directory> -d <directory>

commands:
        add     Encrypts and adds the specified entry to the data directory.
        get     Gets the specified entry from the data directory, decrypts it and writes it to stdout.
        delete  Deletes the specified entry from the data and key directory.

options:
        -e --entry <entry>              Identifier of a given entry.
        -v --value <value>              Value to be stored under the given entry.
        -k --key-dir <directory>        Path to key directory.
        -d --data-dir <directory>       Path to data directory.
```

## Usage examples
```
generate_password.sh
====================
#!/bin/bash
cvault add -e $1 -v $(rkg -s 512 -n) -k /mnt/key_ring -d ~/encrypted

get_password.sh
===============
#!/bin/bash
cvault get -e $1 -k /mnt/key_ring -d ~/encrypted | pbcopy

usage
=====
$ ./generate_password.sh netflix # a new 512 bit password has been generated for key netlix
$ ./get_password.sh netflix # password associated with key 'netflix' is now in clipboard
```
