stdloli allows you to compile compact C and C++ programs without using or 
linking libc. I'm also trying to make it as modular as possible in the linking 
process, which means that only parts of the library that are actually used by 
your program will be linked. This results in extremely small binaries, usually 
an order of magnitude smaller.

At the moment, it only supports AMD64 and I only really implemented a few 
syscalls, but it's already usable. Just grab the code and it will compile out 
of the box.

I won't write any documentation anytime soon, but you can check out the examples
folder and learn the api from there.

Oh by the way, this has absolutely no license. You can do whatever you want with
it.

# Why?
I love compact software with little to no dependencies that compiles  and runs 
out of the box. 
This library can be very well used in minimal software that doesn't require a 
fully featured standard library, and it will effectively cut down binary size 
and compile time.

Also, writing libc-free software is fun and I'm also learning a lot more about
what happens behind the scenes in libc and the OS itself.

# Getting started
```bash
git clone https://github.com/Francesco149/stdloli.git
cd stdloli
make
cd /path/to/my/program/

# compile without stdlib, and avoid linking any dead code
gcc -fno-builtin -nostdlib -fno-stack-protector \
	-fdata-sections -ffunction-sections \
	-I /path/to/stdloli/include my_program.c \
	-L /path/to/stdloli/lib -lstdloli -Wl,--gc-sections

# strip off useless elf sections
strip -R .eh_frame -R .eh_frame_hdr -R .comment a.out

# check binary size in bytes
wc -c a.out

./a.out
```

the compiling is obviously easily simplified with a basic Makefile, you can 
find a generic template in examples/io.
