freebsd-ports
=============

## Description

Custom ports collection that contains ports made by teknos.

## Compilation

Compiling and installing a port from this repository is similar to installing one from the official FreeBSD ports collection.  
Here's how you do it:

```sh
$ git clone https://github.com/TeknosQuet/freebsd-ports.git
$ cd freebsd-ports/category/port    # cd freebsd-ports/emulators/wine8
$ make
$ sudo make install
```

About emulators/wine\*: make sure to compile on both amd64 **and** i386 architecture; this is possible via [poudriere(8)](https://man.freebsd.org/cgi/man.cgi?query=poudriere) or an i386 FreeBSD [jail(8)](https://man.freebsd.org/cgi/man.cgi?query=jail).
