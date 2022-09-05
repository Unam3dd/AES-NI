# AES-NI
use of the AES-NI instruction set read aes_ni.pdf for more information

# Be careful

be careful words is considered as 32 bits chunks by FIPS197

AES Key expansion : https://www.brainkart.com/article/AES-Key-Expansion_8410/

# AES Key Length

| MOD |   Key Bytes |  NR |
|-----|:-----------:|----:|
| 128 |  16 Bytes   | 10  |
| 192 |  24 Bytes   | 12  |
| 256 |  32 Bytes   | 14  |

# AES-NI ?

Intel has implemented AES with a hardware implementation since March 2008
Reference : https://en.wikipedia.org/wiki/AES_instruction_set 
