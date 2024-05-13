cd src/son/
nasm -f elf64 s1/shellcode1.asm
nasm -f elf64 s2/shellcode2.asm
nasm -f elf64 s3/shellcode3.asm
ld -o s1/shellcode1 s1/shellcode1.o
ld -o s2/shellcode2 s2/shellcode2.o
ld -o s3/shellcode3 s3/shellcode3.o
objcopy -O binary -j .text s1/shellcode1 s1/shellcode1.bin
objcopy -O binary -j .text s2/shellcode2 s2/shellcode2.bin
objcopy -O binary -j .text s3/shellcode3 s3/shellcode3.bin
xxd -i s1/shellcode1.bin > shellcode1.h
xxd -i s2/shellcode2.bin > shellcode2.h
xxd -i s3/shellcode3.bin > shellcode3.h
echo "[+] xxded the shellcodes"

python3 packman.py
echo "[+] packed everything and aligned the shellcodes"
cd ..

cp son/shellcode_xor.h shellcodexored.h

cd sonpacker/

nasm -f elf64 packer.asm
ld -o packer packer.o
objcopy -O binary -j .text packer packer.bin
xxd -i packer.bin > packer.h

cd ..
mv sonpacker/packer.h packer.h

echo "[+] son packer setup done"

gcc -O -Wall *.c -o nanocombattant

strip -o nanocombattant nanocombattant
echo "[+] stripped and compiled"

mv nanocombattant ../nanocombattant

echo "[+] testing the challenge"

echo "fi3r_n4n0comb4ttant" | ../nanocombattant