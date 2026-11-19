#ifndef __SCR_SYSTEM_H__
#define __SCR_SYSTEM_H__

/* Controlador de la pantalla Sistema (ver convencion en screens.h) */
void scr_system_prepare(void);
void scr_system_init(void);
void scr_system_uninit(void);
void scr_system_step(void);

/** Vuelve a empezar el minimo historico de heap desde el valor actual. */
void scr_system_reset_heap_min(void);

#endif
