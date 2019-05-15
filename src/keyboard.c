#include "b-em.h"
#include "via.h"
#include "sysvia.h"
#include "keyboard.h"
#include "model.h"
#include "6502.h"
#include <ctype.h>

static uint8_t allegro2bbc[ALLEGRO_KEY_MAX] =
{
    0xaa,   // 0
    0x41,   // 1    ALLEGRO_KEY_A
    0x64,   // 2    ALLEGRO_KEY_B
    0x52,   // 3    ALLEGRO_KEY_C
    0x32,   // 4    ALLEGRO_KEY_D
    0x22,   // 5    ALLEGRO_KEY_E
    0x43,   // 6    ALLEGRO_KEY_F
    0x53,   // 7    ALLEGRO_KEY_G
    0x54,   // 8    ALLEGRO_KEY_H
    0x25,   // 9    ALLEGRO_KEY_I
    0x45,   // 10   ALLEGRO_KEY_J
    0x46,   // 11   ALLEGRO_KEY_K
    0x56,   // 12   ALLEGRO_KEY_L
    0x65,   // 13   ALLEGRO_KEY_M
    0x55,   // 14   ALLEGRO_KEY_N
    0x36,   // 15   ALLEGRO_KEY_O
    0x37,   // 16   ALLEGRO_KEY_P
    0x10,   // 17   ALLEGRO_KEY_Q
    0x33,   // 18   ALLEGRO_KEY_R
    0x51,   // 19   ALLEGRO_KEY_S
    0x23,   // 20   ALLEGRO_KEY_T
    0x35,   // 21   ALLEGRO_KEY_U
    0x63,   // 22   ALLEGRO_KEY_V
    0x21,   // 23   ALLEGRO_KEY_W
    0x42,   // 24   ALLEGRO_KEY_X
    0x44,   // 25   ALLEGRO_KEY_Y
    0x61,   // 26   ALLEGRO_KEY_Z
    0x27,   // 27   ALLEGRO_KEY_0
    0x30,   // 28   ALLEGRO_KEY_1
    0x31,   // 29   ALLEGRO_KEY_2
    0x11,   // 30   ALLEGRO_KEY_3
    0x12,   // 31   ALLEGRO_KEY_4
    0x13,   // 32   ALLEGRO_KEY_5
    0x34,   // 33   ALLEGRO_KEY_6
    0x24,   // 34   ALLEGRO_KEY_7
    0x15,   // 35   ALLEGRO_KEY_8
    0x26,   // 36   ALLEGRO_KEY_9
    0x6a,   // 37   ALLEGRO_KEY_PAD_0
    0x6b,   // 38   ALLEGRO_KEY_PAD_1
    0x7c,   // 39   ALLEGRO_KEY_PAD_2
    0x6c,   // 40   ALLEGRO_KEY_PAD_3
    0x7a,   // 41   ALLEGRO_KEY_PAD_4
    0x7b,   // 42   ALLEGRO_KEY_PAD_5
    0x1a,   // 43   ALLEGRO_KEY_PAD_6
    0x1b,   // 44   ALLEGRO_KEY_PAD_7
    0x2a,   // 45   ALLEGRO_KEY_PAD_8
    0x2b,   // 46   ALLEGRO_KEY_PAD_9
    0x20,   // 56   ALLEGRO_KEY_F1
    0x71,   // 47   ALLEGRO_KEY_F2
    0x72,   // 48   ALLEGRO_KEY_F3
    0x73,   // 49   ALLEGRO_KEY_F4
    0x14,   // 50   ALLEGRO_KEY_F5
    0x74,   // 51   ALLEGRO_KEY_F6
    0x75,   // 52   ALLEGRO_KEY_F7
    0x16,   // 53   ALLEGRO_KEY_F8
    0x76,   // 54   ALLEGRO_KEY_F9
    0x77,   // 55   ALLEGRO_KEY_F10
    0x28,   // 57   ALLEGRO_KEY_F11
    0xaa,   // 58   ALLEGRO_KEY_F12
    0x70,   // 59   ALLEGRO_KEY_ESCAPE
    0x28,   // 60   ALLEGRO_KEY_TILDE
    0x17,   // 61   ALLEGRO_KEY_MINUS
    0x18,   // 62   ALLEGRO_KEY_EQUALS
    0x59,   // 63   ALLEGRO_KEY_BACKSPACE
    0x60,   // 64   ALLEGRO_KEY_TAB
    0x47,   // 65   ALLEGRO_KEY_OPENBRACE
    0x38,   // 66   ALLEGRO_KEY_CLOSEBRACE
    0x49,   // 67   ALLEGRO_KEY_ENTER
    0x57,   // 68   ALLEGRO_KEY_SEMICOLON
    0x48,   // 69   ALLEGRO_KEY_QUOTE
    0x58,   // 70   ALLEGRO_KEY_BACKSLASH
    0x78,   // 71   ALLEGRO_KEY_BACKSLASH2
    0x66,   // 72   ALLEGRO_KEY_COMMA
    0x67,   // 73   ALLEGRO_KEY_FULLSTOP
    0x68,   // 74   ALLEGRO_KEY_SLASH
    0x62,   // 75   ALLEGRO_KEY_SPACE
    0xaa,   // 76   ALLEGRO_KEY_INSERT
    0x59,   // 77   ALLEGRO_KEY_DELETE
    0x5c,   // 78   ALLEGRO_KEY_HOME
    0x69,   // 79   ALLEGRO_KEY_END
    0xaa,   // 80   ALLEGRO_KEY_PGUP
    0x4c,   // 81   ALLEGRO_KEY_PGDN
    0x19,   // 82   ALLEGRO_KEY_LEFT
    0x79,   // 83   ALLEGRO_KEY_RIGHT
    0x39,   // 84   ALLEGRO_KEY_UP
    0x29,   // 85   ALLEGRO_KEY_DOWN
    0x4a,   // 86   ALLEGRO_KEY_PAD_SLASH
    0x5b,   // 87   ALLEGRO_KEY_PAD_ASTERISK
    0x3b,   // 88   ALLEGRO_KEY_PAD_MINUS
    0x3a,   // 89   ALLEGRO_KEY_PAD_PLUS
    0x59,   // 90   ALLEGRO_KEY_PAD_DELETE
    0x3c,   // 91   ALLEGRO_KEY_PAD_ENTER
    0x4c,   // 92   ALLEGRO_KEY_PRINTSCREEN
    0xaa,   // 93   ALLEGRO_KEY_PAUSE
    0x4c,   // 94   ALLEGRO_KEY_ABNT_C1
    0xaa,   // 95   ALLEGRO_KEY_YEN
    0xaa,   // 96   ALLEGRO_KEY_KANA
    0xaa,   // 97   ALLEGRO_KEY_CONVERT
    0xaa,   // 98   ALLEGRO_KEY_NOCONVERT
    0x00,   // 99   ALLEGRO_KEY_AT
    0x00,   // 100  ALLEGRO_KEY_CIRCUMFLEX
    0x01,   // 101  ALLEGRO_KEY_COLON2
    0xaa,   // 102  ALLEGRO_KEY_KANJI
    0x50,   // 103  ALLEGRO_KEY_PAD_EQUALS
    0xaa,   // 104  ALLEGRO_KEY_BACKQUOTE
    0x57,   // 105  ALLEGRO_KEY_SEMICOLON2
    0xaa,   // 106  ALLEGRO_KEY_COMMAND
    0x50,   // 107  ALLEGRO_KEY_BACK
    0xaa,   // 108  ALLEGRO_KEY_VOLUME_UP
    0xaa,   // 109  ALLEGRO_KEY_VOLUME_DOWN
    0xaa,   // 110
    0xaa,   // 111
    0xaa,   // 112
    0xaa,   // 113
    0xaa,   // 114
    0xaa,   // 115
    0xaa,   // 116
    0xaa,   // 117
    0xaa,   // 118
    0xaa,   // 119
    0xaa,   // 120
    0xaa,   // 121
    0xaa,   // 122
    0xaa,   // 123
    0xaa,   // 124
    0xaa,   // 125
    0xaa,   // 126
    0xaa,   // 127
    0xaa,   // 128
    0xaa,   // 129
    0xaa,   // 130
    0xaa,   // 131
    0xaa,   // 132
    0xaa,   // 133
    0xaa,   // 134
    0xaa,   // 135
    0xaa,   // 136
    0xaa,   // 137
    0xaa,   // 138
    0xaa,   // 139
    0xaa,   // 140
    0xaa,   // 141
    0xaa,   // 142
    0xaa,   // 143
    0xaa,   // 144
    0xaa,   // 145
    0xaa,   // 146
    0xaa,   // 147
    0xaa,   // 148
    0xaa,   // 149
    0xaa,   // 150
    0xaa,   // 151
    0xaa,   // 152
    0xaa,   // 153
    0xaa,   // 154
    0xaa,   // 155
    0xaa,   // 156
    0xaa,   // 157
    0xaa,   // 158
    0xaa,   // 159
    0xaa,   // 160
    0xaa,   // 161
    0xaa,   // 162
    0xaa,   // 163
    0xaa,   // 164
    0xaa,   // 165
    0xaa,   // 166
    0xaa,   // 167
    0xaa,   // 168
    0xaa,   // 169
    0xaa,   // 170
    0xaa,   // 171
    0xaa,   // 172
    0xaa,   // 173
    0xaa,   // 174
    0xaa,   // 175
    0xaa,   // 176
    0xaa,   // 177
    0xaa,   // 178
    0xaa,   // 179
    0xaa,   // 180
    0xaa,   // 181
    0xaa,   // 182
    0xaa,   // 183
    0xaa,   // 184
    0xaa,   // 185
    0xaa,   // 186
    0xaa,   // 187
    0xaa,   // 188
    0xaa,   // 189
    0xaa,   // 190
    0xaa,   // 191
    0xaa,   // 192
    0xaa,   // 193
    0xaa,   // 194
    0xaa,   // 195
    0xaa,   // 196
    0xaa,   // 197
    0xaa,   // 198
    0xaa,   // 199
    0xaa,   // 200
    0xaa,   // 201
    0xaa,   // 202
    0xaa,   // 203
    0xaa,   // 204
    0xaa,   // 205
    0xaa,   // 206
    0xaa,   // 207
    0xaa,   // 208
    0xaa,   // 209
    0xaa,   // 210
    0xaa,   // 211
    0xaa,   // 212
    0xaa,   // 213
    0xaa,   // 214
    0x00,   // 215  ALLEGRO_KEY_LSHIFT
    0x00,   // 216  ALLEGRO_KEY_RSHIFT
    0x01,   // 217  ALLEGRO_KEY_LCTRL
    0x01,   // 218  ALLEGRO_KEY_RCTRL
    0xaa,   // 219  ALLEGRO_KEY_ALT
    0xaa,   // 220  ALLEGRO_KEY_ALTGR
    0xaa,   // 221  ALLEGRO_KEY_LWIN
    0xaa,   // 222  ALLEGRO_KEY_RWIN
    0xaa,   // 223  ALLEGRO_KEY_MENU
    0xaa,   // 224  ALLEGRO_KEY_SCROLLLOCK
    0x71,   // 225  ALLEGRO_KEY_NUMLOCK
    0x40,   // 226  ALLEGRO_KEY_CAPSLOCK
};

// Mapping from Allegro to BBC keycodes for logical keyboard mode. If this
// mapping generates 0xaa (an invalid keycode), we instead fake the necessary
// keypresses to type the ASCII character we got from the ALLEGRO_EVENT_KEY_CHAR
// event. If it generates 0xbb, we just ignore the key. Note that not all keys
// generate an ALLEGRO_EVENT_KEY_CHAR, so some of the entries in this cable can
// never be accessed.
static uint8_t allegro2bbclogical[ALLEGRO_KEY_MAX] =
{
    0xbb,   // 0
    0x41,   // 1    ALLEGRO_KEY_A
    0x64,   // 2    ALLEGRO_KEY_B
    0x52,   // 3    ALLEGRO_KEY_C
    0x32,   // 4    ALLEGRO_KEY_D
    0x22,   // 5    ALLEGRO_KEY_E
    0x43,   // 6    ALLEGRO_KEY_F
    0x53,   // 7    ALLEGRO_KEY_G
    0x54,   // 8    ALLEGRO_KEY_H
    0x25,   // 9    ALLEGRO_KEY_I
    0x45,   // 10   ALLEGRO_KEY_J
    0x46,   // 11   ALLEGRO_KEY_K
    0x56,   // 12   ALLEGRO_KEY_L
    0x65,   // 13   ALLEGRO_KEY_M
    0x55,   // 14   ALLEGRO_KEY_N
    0x36,   // 15   ALLEGRO_KEY_O
    0x37,   // 16   ALLEGRO_KEY_P
    0x10,   // 17   ALLEGRO_KEY_Q
    0x33,   // 18   ALLEGRO_KEY_R
    0x51,   // 19   ALLEGRO_KEY_S
    0x23,   // 20   ALLEGRO_KEY_T
    0x35,   // 21   ALLEGRO_KEY_U
    0x63,   // 22   ALLEGRO_KEY_V
    0x21,   // 23   ALLEGRO_KEY_W
    0x42,   // 24   ALLEGRO_KEY_X
    0x44,   // 25   ALLEGRO_KEY_Y
    0x61,   // 26   ALLEGRO_KEY_Z
    0xaa,   // 27   ALLEGRO_KEY_0
    0xaa,   // 28   ALLEGRO_KEY_1
    0xaa,   // 29   ALLEGRO_KEY_2
    0xaa,   // 30   ALLEGRO_KEY_3
    0xaa,   // 31   ALLEGRO_KEY_4
    0xaa,   // 32   ALLEGRO_KEY_5
    0xaa,   // 33   ALLEGRO_KEY_6
    0xaa,   // 34   ALLEGRO_KEY_7
    0xaa,   // 35   ALLEGRO_KEY_8
    0xaa,   // 36   ALLEGRO_KEY_9
    0xaa,   // 37   ALLEGRO_KEY_PAD_0
    0xaa,   // 38   ALLEGRO_KEY_PAD_1
    0xaa,   // 39   ALLEGRO_KEY_PAD_2
    0xaa,   // 40   ALLEGRO_KEY_PAD_3
    0xaa,   // 41   ALLEGRO_KEY_PAD_4
    0xaa,   // 42   ALLEGRO_KEY_PAD_5
    0xaa,   // 43   ALLEGRO_KEY_PAD_6
    0xaa,   // 44   ALLEGRO_KEY_PAD_7
    0xaa,   // 45   ALLEGRO_KEY_PAD_8
    0xaa,   // 46   ALLEGRO_KEY_PAD_9
    0x71,   // 56   ALLEGRO_KEY_F1
    0x72,   // 47   ALLEGRO_KEY_F2
    0x73,   // 48   ALLEGRO_KEY_F3
    0x14,   // 49   ALLEGRO_KEY_F4
    0x74,   // 50   ALLEGRO_KEY_F5
    0x75,   // 51   ALLEGRO_KEY_F6
    0x16,   // 52   ALLEGRO_KEY_F7
    0x76,   // 53   ALLEGRO_KEY_F8
    0x77,   // 54   ALLEGRO_KEY_F9
    0x20,   // 55   ALLEGRO_KEY_F10
    0xbb,   // 57   ALLEGRO_KEY_F11
    0xaa,   // 58   ALLEGRO_KEY_F12
    0x70,   // 59   ALLEGRO_KEY_ESCAPE
    0xbb,   // 60   ALLEGRO_KEY_TILDE
    0xaa,   // 61   ALLEGRO_KEY_MINUS
    0xaa,   // 62   ALLEGRO_KEY_EQUALS
    0x59,   // 63   ALLEGRO_KEY_BACKSPACE
    0x60,   // 64   ALLEGRO_KEY_TAB
    0xaa,   // 65   ALLEGRO_KEY_OPENBRACE
    0xaa,   // 66   ALLEGRO_KEY_CLOSEBRACE
    0xaa,   // 67   ALLEGRO_KEY_ENTER
    0xaa,   // 68   ALLEGRO_KEY_SEMICOLON
    0xaa,   // 69   ALLEGRO_KEY_QUOTE
    0xaa,   // 70   ALLEGRO_KEY_BACKSLASH
    0xaa,   // 71   ALLEGRO_KEY_BACKSLASH2
    0xaa,   // 72   ALLEGRO_KEY_COMMA
    0xaa,   // 73   ALLEGRO_KEY_FULLSTOP
    0xaa,   // 74   ALLEGRO_KEY_SLASH
    0xaa,   // 75   ALLEGRO_KEY_SPACE
    0xbb,   // 76   ALLEGRO_KEY_INSERT
    0x59,   // 77   ALLEGRO_KEY_DELETE
    0xbb,   // 78   ALLEGRO_KEY_HOME
    0x69,   // 79   ALLEGRO_KEY_END
    0xbb,   // 80   ALLEGRO_KEY_PGUP
    0xbb,   // 81   ALLEGRO_KEY_PGDN
    0x19,   // 82   ALLEGRO_KEY_LEFT
    0x79,   // 83   ALLEGRO_KEY_RIGHT
    0x39,   // 84   ALLEGRO_KEY_UP
    0x29,   // 85   ALLEGRO_KEY_DOWN
    0xaa,   // 86   ALLEGRO_KEY_PAD_SLASH
    0xaa,   // 87   ALLEGRO_KEY_PAD_ASTERISK
    0xaa,   // 88   ALLEGRO_KEY_PAD_MINUS
    0xaa,   // 89   ALLEGRO_KEY_PAD_PLUS
    0x59,   // 90   ALLEGRO_KEY_PAD_DELETE
    0xaa,   // 91   ALLEGRO_KEY_PAD_ENTER
    0xbb,   // 92   ALLEGRO_KEY_PRINTSCREEN
    0xbb,   // 93   ALLEGRO_KEY_PAUSE
    0xbb,   // 94   ALLEGRO_KEY_ABNT_C1
    0xbb,   // 95   ALLEGRO_KEY_YEN
    0xbb,   // 96   ALLEGRO_KEY_KANA
    0xbb,   // 97   ALLEGRO_KEY_CONVERT
    0xbb,   // 98   ALLEGRO_KEY_NOCONVERT
    0xbb,   // 99   ALLEGRO_KEY_AT
    0xbb,   // 100  ALLEGRO_KEY_CIRCUMFLEX
    0xbb,   // 101  ALLEGRO_KEY_COLON2
    0xbb,   // 102  ALLEGRO_KEY_KANJI
    0xbb,   // 103  ALLEGRO_KEY_PAD_EQUALS
    0xbb,   // 104  ALLEGRO_KEY_BACKQUOTE
    0xbb,   // 105  ALLEGRO_KEY_SEMICOLON2
    0xbb,   // 106  ALLEGRO_KEY_COMMAND
    0xbb,   // 107  ALLEGRO_KEY_BACK
    0xbb,   // 108  ALLEGRO_KEY_VOLUME_UP
    0xbb,   // 109  ALLEGRO_KEY_VOLUME_DOWN
    0xbb,   // 110
    0xbb,   // 111
    0xbb,   // 112
    0xbb,   // 113
    0xbb,   // 114
    0xbb,   // 115
    0xbb,   // 116
    0xbb,   // 117
    0xbb,   // 118
    0xbb,   // 119
    0xbb,   // 120
    0xbb,   // 121
    0xbb,   // 122
    0xbb,   // 123
    0xbb,   // 124
    0xbb,   // 125
    0xbb,   // 126
    0xbb,   // 127
    0xbb,   // 128
    0xbb,   // 129
    0xbb,   // 130
    0xbb,   // 131
    0xbb,   // 132
    0xbb,   // 133
    0xbb,   // 134
    0xbb,   // 135
    0xbb,   // 136
    0xbb,   // 137
    0xbb,   // 138
    0xbb,   // 139
    0xbb,   // 140
    0xbb,   // 141
    0xbb,   // 142
    0xbb,   // 143
    0xbb,   // 144
    0xbb,   // 145
    0xbb,   // 146
    0xbb,   // 147
    0xbb,   // 148
    0xbb,   // 149
    0xbb,   // 150
    0xbb,   // 151
    0xbb,   // 152
    0xbb,   // 153
    0xbb,   // 154
    0xbb,   // 155
    0xbb,   // 156
    0xbb,   // 157
    0xbb,   // 158
    0xbb,   // 159
    0xbb,   // 160
    0xbb,   // 161
    0xbb,   // 162
    0xbb,   // 163
    0xbb,   // 164
    0xbb,   // 165
    0xbb,   // 166
    0xbb,   // 167
    0xbb,   // 168
    0xbb,   // 169
    0xbb,   // 170
    0xbb,   // 171
    0xbb,   // 172
    0xbb,   // 173
    0xbb,   // 174
    0xbb,   // 175
    0xbb,   // 176
    0xbb,   // 177
    0xbb,   // 178
    0xbb,   // 179
    0xbb,   // 180
    0xbb,   // 181
    0xbb,   // 182
    0xbb,   // 183
    0xbb,   // 184
    0xbb,   // 185
    0xbb,   // 186
    0xbb,   // 187
    0xbb,   // 188
    0xbb,   // 189
    0xbb,   // 190
    0xbb,   // 191
    0xbb,   // 192
    0xbb,   // 193
    0xbb,   // 194
    0xbb,   // 195
    0xbb,   // 196
    0xbb,   // 197
    0xbb,   // 198
    0xbb,   // 199
    0xbb,   // 200
    0xbb,   // 201
    0xbb,   // 202
    0xbb,   // 203
    0xbb,   // 204
    0xbb,   // 205
    0xbb,   // 206
    0xbb,   // 207
    0xbb,   // 208
    0xbb,   // 209
    0xbb,   // 210
    0xbb,   // 211
    0xbb,   // 212
    0xbb,   // 213
    0xbb,   // 214
    0xbb,   // 215  ALLEGRO_KEY_LSHIFT
    0xbb,   // 216  ALLEGRO_KEY_RSHIFT
    0xbb,   // 217  ALLEGRO_KEY_LCTRL
    0xbb,   // 218  ALLEGRO_KEY_RCTRL
    0xbb,   // 219  ALLEGRO_KEY_ALT
    0xbb,   // 220  ALLEGRO_KEY_ALTGR
    0xbb,   // 221  ALLEGRO_KEY_LWIN
    0xbb,   // 222  ALLEGRO_KEY_RWIN
    0xbb,   // 223  ALLEGRO_KEY_MENU
    0xbb,   // 224  ALLEGRO_KEY_SCROLLLOCK
    0xbb,   // 225  ALLEGRO_KEY_NUMLOCK
    0xbb,   // 226  ALLEGRO_KEY_CAPSLOCK
};

#define A2B_SHIFT 0x100
#define A2B_CTRL  0x200

static uint16_t ascii2bbc[] =
{
    0x47|A2B_CTRL,  // 0x00 NUL (CTRL-@)
    0x41|A2B_CTRL,  // 0x01 SOH (CTRL-A)
    0x64|A2B_CTRL,  // 0x02 STX (CTRL-B)
    0x52|A2B_CTRL,  // 0x03 ETX (CTRL-C)
    0x32|A2B_CTRL,  // 0x04 EOT (CTRL-D)
    0x22|A2B_CTRL,  // 0x05 ENQ (CTRL-E)
    0x43|A2B_CTRL,  // 0x06 ACK (CTRL-F)
    0x53|A2B_CTRL,  // 0x07 BEL (CTRL-G)
    0x54|A2B_CTRL,  // 0x08 BS  (CTRL-H)
    0x60,           // 0x09 HT  (CTRL-I)
    0x49,           // 0x0a LF  (CTRL-J)
    0x46|A2B_CTRL,  // 0x0b VT  (CTRL-K)
    0x56|A2B_CTRL,  // 0x0c FF  (CTRL-L)
    0x49,           // 0x0d CR  (CTRL-M)
    0x55|A2B_CTRL,  // 0x0e SO  (CTRL-N)
    0x36|A2B_CTRL,  // 0x0f SI  (CTRL-O)
    0x37|A2B_CTRL,  // 0x10 DLE (CTRL-P)
    0x10|A2B_CTRL,  // 0x11 DC1 (CTRL-Q, XON)
    0x33|A2B_CTRL,  // 0x12 DC2 (CTRL-R)
    0x51|A2B_CTRL,  // 0x13 DC3 (CTRL-S, XOFF)
    0x23|A2B_CTRL,  // 0x14 DC4 (CTRL-T)
    0x35|A2B_CTRL,  // 0x15 NAK (CTRL-U)
    0x63|A2B_CTRL,  // 0x16 SYN (CTRL-V)
    0x21|A2B_CTRL,  // 0x17 ETB (CTRL-W)
    0x42|A2B_CTRL,  // 0x18 CAN (CTRL-X)
    0x44|A2B_CTRL,  // 0x19 EM  (CTRL-Y)
    0x61|A2B_CTRL,  // 0x1a SUB (CTRL-Z)
    0x38,           // 0x1b ESC (CTRL-[)
    0x48|A2B_CTRL,  // 0x1c FS  (CTRL-\)
    0x58|A2B_CTRL,  // 0x1d GS  (CTRL-])
    0x18|A2B_CTRL,  // 0x1e RS  (CTRL-^)`
    0x28|A2B_CTRL,  // 0x1f US  (CTRL-_)
    0x62,           // 0x20 SPC
    0x30|A2B_SHIFT, // 0x21 !
    0x31|A2B_SHIFT, // 0x22 "
    0x11|A2B_SHIFT, // 0x23 #
    0x12|A2B_SHIFT, // 0x24 $
    0x13|A2B_SHIFT, // 0x25 %
    0x34|A2B_SHIFT, // 0x26 &
    0x24|A2B_SHIFT, // 0x27 '
    0x15|A2B_SHIFT, // 0x28 (
    0x26|A2B_SHIFT, // 0x29 )
    0x48|A2B_SHIFT, // 0x2a *
    0x57|A2B_SHIFT, // 0x2b +
    0x66,           // 0x2c ,
    0x17,           // 0x2d -
    0x67,           // 0x2e .
    0x68,           // 0x2f /
    0x27,           // 0x30 0
    0x30,           // 0x31 1
    0x31,           // 0x32 2
    0x11,           // 0x33 3
    0x12,           // 0x34 4
    0x13,           // 0x35 5
    0x34,           // 0x36 6
    0x24,           // 0x37 7
    0x15,           // 0x38 8
    0x26,           // 0x39 9
    0x48,           // 0x3a *
    0x57,           // 0x3b ;
    0x66|A2B_SHIFT, // 0x3c <
    0x17|A2B_SHIFT, // 0x3D =
    0x67|A2B_SHIFT, // 0x3E >
    0x68|A2B_SHIFT, // 0x3F ?
    0x47,           // 0x40 @
    0x41|A2B_SHIFT, // 0x41 A
    0x64|A2B_SHIFT, // 0x42 B
    0x52|A2B_SHIFT, // 0x43 C
    0x32|A2B_SHIFT, // 0x44 D
    0x22|A2B_SHIFT, // 0x45 E
    0x43|A2B_SHIFT, // 0x46 F
    0x53|A2B_SHIFT, // 0x47 G
    0x54|A2B_SHIFT, // 0x48 H
    0x25|A2B_SHIFT, // 0x49 I
    0x45|A2B_SHIFT, // 0x4a J
    0x46|A2B_SHIFT, // 0x4b K
    0x56|A2B_SHIFT, // 0x4c L
    0x65|A2B_SHIFT, // 0x4d M
    0x55|A2B_SHIFT, // 0x4e N
    0x36|A2B_SHIFT, // 0x4f O
    0x37|A2B_SHIFT, // 0x50 P
    0x10|A2B_SHIFT, // 0x51 Q
    0x33|A2B_SHIFT, // 0x52 R
    0x51|A2B_SHIFT, // 0x53 S
    0x23|A2B_SHIFT, // 0x54 T
    0x35|A2B_SHIFT, // 0x55 U
    0x63|A2B_SHIFT, // 0x56 V
    0x21|A2B_SHIFT, // 0x57 W
    0x42|A2B_SHIFT, // 0x58 X
    0x44|A2B_SHIFT, // 0x59 Y
    0x61|A2B_SHIFT, // 0x5a Z
    0x38,           // 0x5b [
    0x78,           // 0x5c backslash
    0x58,           // 0x5d ]
    0x18,           // 0x5e ^
    0x28,           // 0x5f _
    0x28|A2B_SHIFT, // 0x60 £
    0x41,           // 0x61 a
    0x64,           // 0x62 b
    0x52,           // 0x63 c
    0x32,           // 0x64 d
    0x22,           // 0x65 e
    0x43,           // 0x66 f
    0x53,           // 0x67 g
    0x54,           // 0x68 h
    0x25,           // 0x69 i
    0x45,           // 0x6a j
    0x46,           // 0x6b k
    0x56,           // 0x6c l
    0x65,           // 0x6d m
    0x55,           // 0x6e n
    0x36,           // 0x6f o
    0x37,           // 0x70 p
    0x10,           // 0x71 q
    0x33,           // 0x72 r
    0x51,           // 0x73 s
    0x23,           // 0x74 t
    0x35,           // 0x75 u
    0x63,           // 0x76 v
    0x21,           // 0x77 w
    0x42,           // 0x78 x
    0x44,           // 0x79 y
    0x61,           // 0x7a z
    0x38|A2B_SHIFT, // 0x7b {
    0x78|A2B_SHIFT, // 0x7c |
    0x58|A2B_SHIFT, // 0x7d }
    0x18|A2B_SHIFT, // 0x7e ~
    0x59            // 0x7f DEL
};

int keylookup[ALLEGRO_KEY_MAX];
bool keyas = 0;
bool keylogical = 0;

static int keycol, keyrow;
static int bbckey[16][16];
static int hostshift, hostctrl;

typedef enum {
    KP_IDLE,
    KP_NEXT,
#if 0 // SFTODO
    KP_SHIFT_DOWN,
    KP_SHIFT_UP,
    KP_DELAY1,
    KP_CTRL_DOWN,
    KP_CTRL_UP,
#endif
    KP_CHAR,
    KP_DELAY2,
    KP_UP
} kp_state_t;

static kp_state_t kp_state = KP_IDLE;
static unsigned char *key_paste_str;
static unsigned char *key_paste_ptr;
static bool key_paste_shift;
static bool key_paste_ctrl;
static uint16_t clip_paste_key;

void key_clear(void)
{
    int c, r;
    for (c = 0; c < 16; c++)
        for (r = 0; r < 16; r++)
            bbckey[c][r] = 0;
    // SFTODO: SET HOSTSHIFT/HOSTCTRL??? PROB NOT BUT CHECK LATER
    sysvia_set_ca2(0);
}

static void key_update()
{
    int c,d;
    if (IC32 & 8) {
        for (d = 0; d < ((MASTER) ? 13 : 10); d++) {
            for (c = 1; c < 8; c++) {
                if (bbckey[d][c]) {
                    sysvia_set_ca2(1);
                    return;
                }
            }
        }
    }
    else {
        if (keycol < ((MASTER) ? 13 : 10)) {
            for (c = 1; c < 8; c++) {
                if (bbckey[keycol][c]) {
                    sysvia_set_ca2(1);
                    return;
                }
            }
        }
    }
    sysvia_set_ca2(0);
}

int key_map(ALLEGRO_EVENT *event)
{
    int code = event->keyboard.keycode;
    if (code < ALLEGRO_KEY_MAX) {
        if (keyas && code == ALLEGRO_KEY_A)
            code = ALLEGRO_KEY_CAPSLOCK;
        code = keylookup[code];
    }
    log_debug("keyboard: mapping %d to %d", event->keyboard.keycode, code);
    return code;
}

void key_char(ALLEGRO_EVENT *event)
{
    if (keylogical) {
        log_debug("keyboard: key_char keycode=%d, unichar=%d", event->keyboard.keycode, event->keyboard.unichar);
        uint8_t vkey = allegro2bbclogical[event->keyboard.keycode];
        if (vkey == 0xaa) {
            int c = event->keyboard.unichar;
            switch (c)
            {
                case 96:  // unicode backtick
                    break;
                case 163: // unicode pound currency symbol
                    c = 96;
                default:
                    if (c <= 127) {
                        uint16_t bbckey = ascii2bbc[c];
                        key_paste_addc(bbckey & 0xff, bbckey & A2B_SHIFT, bbckey & A2B_CTRL);
                    }
            }
        }
        else if (vkey != 0xbb)
            key_paste_addc(vkey, hostshift, hostctrl);
    }
}

static void set_key(int code, int state)
{
    unsigned vkey;

    // SFTODO HACK
    bool shiftctrl = false;
    if ((code == ALLEGRO_KEY_LSHIFT) || (code == ALLEGRO_KEY_RSHIFT)) {
        hostshift = state;
        shiftctrl = true;
    }
    else if ((code == ALLEGRO_KEY_LCTRL) || (code == ALLEGRO_KEY_RCTRL)) {
        hostctrl = state;
        shiftctrl = true;
    }

    if (!keylogical || (code == ALLEGRO_KEY_CAPSLOCK)) {
        vkey = allegro2bbc[code];
        log_debug("keyboard: code=%d, vkey=%02X", code, vkey);
        if (vkey != 0xaa) {
            bbckey[vkey & 15][vkey >> 4] = state;
            key_update();
        }
    }
    else {
        // SFTODO: I THINK SET_KEY WILL HAVE TO PROCESS SHIFT+CTRL
        // AND JUST MAYBE SOME OTHERS (BREAK?) EVEN IN LOGICAL KEYBOARD MODE - BUT
        // VERY FEW, NOT THE ONES MARKED IN THE EXISTING ALLEGRO2BBCLOGICAL TABLE
        if (shiftctrl)
            key_paste_addc(0xaa, hostshift, hostctrl);
    }
}

void key_down(int code)
{
    set_key(code, 1);
}

void key_up(int code)
{
    set_key(code, 0);
}

// SFTODO: Should we change the "paste" part of all the fn/var names here? Maybe
// ask Steve what he thinks before doing that.

#if 0 // SFTODO:DELETE
void key_paste_start(char *str) // SFTODO: May be unused, delete if so
{
    if (str) {
        log_debug("key_paste_start, str=%s", str);
        key_paste_str = key_paste_ptr = (unsigned char *)str;
        kp_state = KP_NEXT;
    }
}
#endif

static void key_paste_addc2(int ch) // SFTODO CRAP NAME
{
    size_t len;
    int pos;

	log_debug("keyboard: paste addc2, ch=%d", ch);

    if (key_paste_str) {
        len = strlen((char *)key_paste_str);
        pos = key_paste_ptr - key_paste_str;
    }
    else {
        len = 0;
        pos = 0;
        kp_state = KP_NEXT;
        key_paste_shift = bbckey[0][0];
        key_paste_ctrl = bbckey[1][0];
    }

    char *new_str = al_realloc(key_paste_str, len+2);
    if (new_str) {
        key_paste_str = (unsigned char *)new_str;
        key_paste_ptr = key_paste_str + pos;
        new_str[len] = ch;
        new_str[len+1] = 0;
    }
    else
        log_warn("keyboard: out of memory adding character to paste, character discarded");
}

// SFTODO MAGIC CONSTANTS EVERYWHERE!
// SFTODO RENAME THIS AND USE addc() NAME FOR WHAT IS CURRENTLY ADDC2()
void key_paste_addc(int ch, bool shift, bool ctrl)
{
	log_debug("keyboard: paste addc, ch=%d, shift=%d, ctrl=%d", ch, shift, ctrl);

    if (key_paste_shift != shift) {
        key_paste_addc2(0xe0 | shift);
        key_paste_shift = shift;
    }
    if (key_paste_ctrl != ctrl) {
        key_paste_addc2(0xf0 | ctrl);
        key_paste_ctrl = ctrl;
    }
    if (ch != 0xaa)
        key_paste_addc2(ch);
}

#if 0 // SFTODO
static void key_paste_ctrl(void)
{
    if ((clip_paste_key & A2B_CTRL) && !bbckey[0][1]) // SFTODO ARGS WRONG WAY ROUND?
        kp_state = KP_CTRL_DOWN;
    else if (!(clip_paste_key & A2B_CTRL) && bbckey[0][1]) // SFTODO ARGS WRONG WAY ROUND?
        kp_state = KP_CTRL_UP;
    else
        kp_state = KP_CHAR;
}
#endif

void key_paste_poll(void)
{
    unsigned ch;
    //log_debug("key_paste_poll: kp_state=%d", kp_state);

    switch(kp_state) {
        case KP_IDLE:
            break;
        case KP_NEXT:
            if ((ch = *key_paste_ptr++)) {
                log_debug("keyboard: clip_paste_poll ch=%02x", ch);
                // SFTODO MAGIC CONSTANTS
                clip_paste_key = ch;
                if ((ch == 0xe0) || (ch == 0xe1)) {
                    bbckey[0][0] = ch & 0x01;
                    kp_state = KP_NEXT;
                    key_update();
                } else if ((ch == 0xf0) || (ch == 0xf1)) {
                    bbckey[1][0] = ch & 0x01;
                    kp_state = KP_NEXT;
                    key_update();
                }
                else {
                    kp_state = KP_CHAR;
                }
            }
            else {
                if (clip_paste_key < 0xe0)
                    bbckey[clip_paste_key & 15][clip_paste_key >> 4] = 0;
                key_update(); // SFTODO: OK? THINK ORIGINAL DIDN'T HAVE IT HERE
                al_free(key_paste_str);
                key_paste_str = key_paste_ptr = NULL;
                kp_state = KP_IDLE;

                key_paste_addc(0xaa, hostshift, hostctrl); // no-op if already correct
            }
            break;
#if 0 // SFTODO
        case KP_SHIFT_DOWN:
            bbckey[0][0] = 1;
            key_update();
            kp_state = KP_DELAY1;
            break;
        case KP_SHIFT_UP:
            bbckey[0][0] = 0;
            key_update();
            kp_state = KP_DELAY1;
            break;
        case KP_DELAY1:
            key_paste_ctrl();
            break;
        case KP_CTRL_DOWN:
            bbckey[0][1] = 1; // SFTODO: ARGS WRONG WAY ROUND!?!?!
            key_update();
            kp_state = KP_CHAR;
            break;
        case KP_CTRL_UP:
            bbckey[0][1] = 1; // SFTODO: ARGS WRONG WAY ROUND!?!?!
            key_update();
            kp_state = KP_CHAR;
            break;
#endif
        case KP_CHAR:
            log_debug("SFTODO KP_CHAR clip_paste_key=%d", clip_paste_key);
            bbckey[clip_paste_key & 0x0f][(clip_paste_key & 0xf0) >> 4] = 1;
            key_update();
            kp_state = KP_DELAY2;
            break;
        case KP_DELAY2:
            kp_state = KP_UP;
            break;
        case KP_UP:
            bbckey[clip_paste_key & 0x0f][(clip_paste_key & 0xf0) >> 4] = 0;
            key_update();
            kp_state = KP_NEXT;
    }
}

void key_scan(int row, int col) {
    keyrow = row;
    keycol = col;
    key_update();
}

bool key_is_down(void) {
    if (keyrow == 0 && keycol >= 2 && keycol <= 9)
        return kbdips & (1 << (9 - keycol));
    else
        return bbckey[keycol][keyrow];
}

bool key_any_down(void)
{
    for (int c = 0; c < 16; c++)
        for (int r = 1; r < 16; r++)
            if (bbckey[c][r])
                return true;
    return false;
}

bool key_code_down(int code)
{
    // SFTODO: THIS IS USED IN ONLY ONE PLACE BUT NEED TO THINK HOW IT SHOULD
    // INTERACT WITH LOGICAL KBD MODE
    if (!keylogical && code < ALLEGRO_KEY_MAX) {
        code = allegro2bbc[code];
        return bbckey[code & 0x0f][code >> 4];
    }
    return false;
}
