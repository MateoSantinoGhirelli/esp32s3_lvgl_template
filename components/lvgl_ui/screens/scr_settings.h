#ifndef __SCR_SETTINGS_H__
#define __SCR_SETTINGS_H__

/* Controlador de la pantalla Ajustes (ver convencion en screens.h) */
void scr_settings_prepare(void);
void scr_settings_init(void);
void scr_settings_uninit(void);
void scr_settings_step(void);

/** Brillo al 100 % y timeout de pantalla desactivado. */
void scr_settings_restore_defaults(void);

#endif
