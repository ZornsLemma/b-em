#ifndef __INC_LED_H
#define __INC_LED_H

extern int led_ticks;
extern ALLEGRO_BITMAP *led_bitmap;

typedef enum
{
    LED_CASSETTE_MOTOR,
    LED_CAPS_LOCK,
    LED_SHIFT_LOCK,
    LED_DRIVE_0,
    LED_DRIVE_1,
    LED_VDFS,
    LED_MAX
} led_name_t;

#define LED_DRIVE_TICKS (10) // SFTODO!??!? DELETE

void led_init(void);
void led_update(led_name_t led_name, bool b, int ticks);
void led_timer_fired(void);

#endif