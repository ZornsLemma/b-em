#ifndef __INC_KEYBOARD_H
#define __INC_KEYBOARD_H

extern int kbdips;

extern int keylookup[ALLEGRO_KEY_MAX];
extern bool keyas;
extern bool keylogical;

extern int key_map(ALLEGRO_EVENT *event);
extern void key_char(ALLEGRO_EVENT *event);
extern void key_down(int code);
extern void key_up(int code);

extern void key_clear(void);
extern void key_check(void);
#if 0 // SFTODO DELETE
extern void key_paste_start(char *str); // SFTODO MAKE STATIC?
#endif
extern void key_paste_addc(int ch, bool hostshift, bool hostctrl); // SFTODO MAKE STATIC?
extern void key_paste_poll(void);
extern void key_scan(int row, int col);
extern bool key_is_down(void);
extern bool key_any_down(void);
extern bool key_code_down(int code);

#endif
