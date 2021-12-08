VIA_ENABLE = no
AUTO_SHIFT_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = yes
SWAP_HANDS_ENABLE = no
ED_KRIPT = yes
ED_KRIPT_SHA256 = no

SRC += ed_tap_dance.c
SRC += ed_tools.c

EXTRAFLAGS += -flto

ifeq ($(strip $(ED_KRIPT)), yes)
	SRC += aes/aes.c
	SRC += ed_kript.c
	OPT_DEFS += -DED_KRIPT
endif

ifeq ($(strip $(ED_KRIPT_SHA256)), yes)
	SRC += aes/sha256.c
	OPT_DEFS += -DED_KRIPT_SHA256
endif

