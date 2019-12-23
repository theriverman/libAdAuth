from ctypes import cdll, c_char_p, c_int, create_string_buffer, pointer
from ctypes.wintypes import LPLONG

# C++ Header
# DLLEXPORT int auth(char *username, char *password, char *host, char *domain, int *port);
DLL_PATH_DEBUG = r'C:\Users\*************\libAdAuthCpp\x64\Debug DLL\libAdAuthCpp.dll'
DLL_PATH_RELEASE = r'C:\Users\***********\libAdAuthCpp\x64\Release\libAdAuthCpp.dll'

username = create_string_buffer(b"************")
password = create_string_buffer(b"************")
host = create_string_buffer(b"*****.uk")
domain = create_string_buffer(b"*****.uk")
port = pointer(c_int(389)) # or pass `ctypes.c_long(0)` to the function directly

lib = cdll.LoadLibrary(DLL_PATH_RELEASE)
lib.auth.argtypes = [c_char_p, c_char_p, c_char_p, c_char_p, LPLONG]
lib.auth.restype = c_int

auth = lib.auth(username, password, host, domain, port)
