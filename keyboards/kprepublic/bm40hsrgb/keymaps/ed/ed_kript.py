from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
import base64
import hashlib
from Crypto import Random
from Crypto.Cipher import AES
import pyscrypt
import os, binascii
from backports.pbkdf2 import pbkdf2_hmac

salt = b'aa1f2d3f4d23ac44e9c5a6c3d8f9ee8c'
passwd = b'p@$Sw0rD~7'
key = pyscrypt.hash(passwd, salt, 2 , 8, 1, 32)
print("Derived key:")
print(key.hex())

salt = binascii.unhexlify('aaef2d3f4d77ac66e9c5a6c3d8f921d1')
passwd = "abacate".encode("utf8")
key = pbkdf2_hmac("sha256", passwd, salt, 50000, 32)
print("Derived key:")
print(key.hex())


class AESCipher(object):

    def __init__(self, key):
        self.bs = AES.block_size
        self.key = hashlib.sha256(key.encode()).digest()

        print("Key:")
        print(self.key.hex())

    def encrypt(self, raw):
        raw = self._pad(raw)
        iv = Random.new().read(AES.block_size)
        print("IV:")
        print(iv.hex())

        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        data = cipher.encrypt(raw.encode())
        print("cipher:")
        print(data.hex())
        print((iv + data).hex())
        return base64.b64encode(iv + data)

    def decrypt(self, enc):
        enc = base64.b64decode(enc)
        iv = enc[:AES.block_size]
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        return self._unpad(cipher.decrypt(enc[AES.block_size:])).decode('utf-8')

    def _pad(self, s):
        return s + (self.bs - len(s) % self.bs) * chr(self.bs - len(s) % self.bs)

    @staticmethod
    def _unpad(s):
        return s[:-ord(s[len(s)-1:])]

#password = input("Password:\n")

# void kript_key_init(uint8_t *key) {
#   uint8_t j = 0, r = 1;
#   for (int i = 0; i < KRIPT_KEY_SIZE; ++i){
#     r = (g_kript_password[j] * 2 + 4 * r) & 0xFF;
#     key[i] = r;
#     j = (j + 1) % g_kript_count;}
# }

ed_kript = AESCipher("casa")
print("abacate:")
print("abacate".encode('utf-8').hex())
encripted = ed_kript.encrypt("abacate")
decripted = ed_kript.decrypt(encripted)
print("Decripted:")
print(decripted)

# key = get_random_bytes(32)
# print(key)
# data = "1234567890123456".encode("utf-8")
# cipher = AES.new(key, AES.MODE_EAX)
# ciphertext, tag = cipher.encrypt_and_digest(data)

# file_out = open("encrypted.bin", "wb")
# [ file_out.write(x) for x in (cipher.nonce, tag, ciphertext) ]
# file_out.close()

# file_in = open("encrypted.bin", "rb")
# nonce, tag, ciphertext = [ file_in.read(x) for x in (16, 16, -1) ]

# # let's assume that the key is somehow available again
# cipher = AES.new(key, AES.MODE_EAX, nonce)
# data = cipher.decrypt_and_verify(ciphertext, tag)

# print(data)
