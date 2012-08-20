#include	"xship.h"
#include	"sdldata.h"
#include	"render.h"

void		xship_blit(SDLData* d, XShip* s)
{
  v2f		v = *pos_onscreen(&d->cam, &s->ship.pos);
  unsigned	u;

  SDLazy_SetPos(d->srf_ship[SRF_SHIP_BASE], &v);
  SDLazy_Blit(d->srf_ship[SRF_SHIP_BASE]);
  for (u = 0; u < 4; ++u)
    {
      SDLazy_SetPos(s->bases_sprite[u], &v);
      SDLazy_Blit(s->bases_sprite[u]);
    }
  for (u = 0; u < 8; ++u)
    {
      SDLazy_SetPos(s->turret_anim[u], &v);
      SDLazy_Blit(s->turret_anim[u]);
    }
  SDLazy_SetPos(d->srf_ship[SRF_SHIP_TOP], &v);
  SDLazy_Blit(d->srf_ship[SRF_SHIP_TOP]);
}
