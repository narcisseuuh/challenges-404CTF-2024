cd src/
cd son/
nasm -f elf64 son.asm
ld -o son son.o
objcopy -O binary -j .text son son.bin
xxd -i son.bin > shellcode.h

python3 packer.py
cd ..

cp son/shellcode_xor.h shellcodexored.h

gcc -Wall -o antismash *.c

strip -o antismash antismash

patchelf --set-interpreter ld-linux-x86-64.so.2 antismash
patchelf --set-rpath . antismash

cp antismash ../data/antismash
cp libc.so.6 ../data/libc.so.6
cp ld-linux-x86-64.so.2 ../data/ld-linux-x86-64.so.2

mv antismash ..
