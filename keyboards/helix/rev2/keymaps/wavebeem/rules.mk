# QMK Standard Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
#   See TOP/keyboards/helix/rules.mk for a list of options that can be set.
#   See TOP/docs/config_options.md for more information.
#

# If firmware size is over the limit, try this option
LINK_TIME_OPTIMIZATION_ENABLE = no
# Helix Rows: 4 or 5
HELIX_ROWS = 4
# Enable OLED display
OLED_ENABLE = yes
# use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LOCAL_GLCDFONT = yes
# LED backlight (Enable WS2812 RGB underlight.)
LED_BACK_ENABLE = no
# LED underglow (Enable WS2812 RGB underlight.)
LED_UNDERGLOW_ENABLE = yes
# LED animations
LED_ANIMATIONS = yes
# connect to IOS device (iPad,iPhone)
IOS_DEVICE_ENABLE = no
# Turn off that thing where holding keys on boot can mess up your keyboard
BOOTMAGIC_ENABLE = no
# Enable media keys
EXTRAKEY_ENABLE = yes

# convert Helix-specific options (that represent combinations of standard options)
#   into QMK standard options.
include $(strip $(KEYBOARD_LOCAL_FEATURES_MK))
