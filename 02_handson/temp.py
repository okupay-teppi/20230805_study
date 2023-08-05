from pwn import *

target = remote("", )
# target = process("./chall")

payload = b"A" * 
payload += p64()

target.sendline(payload)
print(target.recvall().decode())