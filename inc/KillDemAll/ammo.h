#ifndef		AMMO_H
#define		AMMO_H

#include	"SDLazy.h"
#include	"data_typedef.h"
#include	"sdldata_typedef.h"
#include	"ship.h"

typedef		enum
{
  AMMO_BULLET,
  AMMO_ROCKET,
  NB_AMMOS
}		eAmmoType;

typedef		struct
{
  eAmmoType	type;
  Ship*		from_who;
  v2f		pos;
  v2f		dir;
  double	rad;
  double	created_time;
  double	duration_time;
}		Ammo;

void		ammo_push(Data*, Ammo*);
void		ammos_blit(SDLData*, CList* ammos);
void		ammos_core(CList* ammos);

#endif
