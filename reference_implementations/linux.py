#!/usr/bin/env python3
from ctypes import cdll, c_char_p, c_int, create_string_buffer, c_long

SO_PATH="/home/***************/libAdAuth/libAdAuth.so"

username = create_string_buffer(b"********")
password = create_string_buffer(b"********")
host = create_string_buffer(b"*********.uk")
domain = create_string_buffer(b"*******.uk")
port = 0

lib = cdll.LoadLibrary(SO_PATH)
lib.auth.argtypes = [c_char_p, c_char_p, c_char_p, c_char_p, c_long]
lib.auth.restype = c_int

auth = lib.auth(username, password, host, domain, port)
