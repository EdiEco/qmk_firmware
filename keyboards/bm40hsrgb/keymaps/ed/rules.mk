VIA_ENABLE = no
AUTO_SHIFT_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = yes
SWAP_HANDS_ENABLE = no

SRC += ed_tap_dance.c
SRC += ed_kript.c
SRC += ed_tools.c

SRC += aes/aes.c

EXTRAFLAGS += -flto
