#ifndef __SCR_HOME_H__
#define __SCR_HOME_H__

/* Controlador de la pantalla Home (ver convencion en screens.h) */
void scr_home_prepare(void);
void scr_home_init(void);
void scr_home_uninit(void);
void scr_home_step(void);

/** Lee bateria, temperatura y uptime ya mismo (boton Actualizar / boton fisico). */
void scr_home_force_refresh(void);

#endif
