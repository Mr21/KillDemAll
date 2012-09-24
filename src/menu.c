#include	"SDLazy.h"
#include	"menu.h"
#include	"data.h"
#include	"controls.h"

static void	_snd_open_close(int status)
{
  sound_play(SND_MENU_OPEN, .9, .8, status ? 25000 : 22050);
}

static void	_menu_openclose_cb(void)
{
  Menu*		d = &((Data*)SDLazy_GetData())->menu;

  _snd_open_close(d->status = !d->status);
}

void		menu_openclose(Menu* d, int status)
{
  _snd_open_close(d->status = status);
  SDLazy_ButtonSetState(d->btn[BTN_MENU_OPEN], d->status);
}

int		menu_mouseover(Menu* d)
{
  return SDLazy_Hover(d->srf[SRF_MENU_BG]);
}

void		menu_init(Menu* d)
{
  SDLazy_Button*        b;

  d->status = 0;

  d->srf[SRF_MENU_BG]         = SDLazy_SurfaceLoad("img/sprites.png", SDLazy_Rect(370, 150, 150,  8));
  d->srf[SRF_MENU_FULLSCREEN] = SDLazy_SurfaceLoad("img/sprites.png", SDLazy_Rect(370, 185,  30, 27));
  d->srf[SRF_MENU_KEYBOARD]   = SDLazy_SurfaceLoad("img/sprites.png", SDLazy_Rect( 20, 150, 128, 36));
  d->srf[SRF_MENU_COMMANDS]   = SDLazy_SurfaceLoad("img/sprites.png", SDLazy_Rect( 20, 280, 128, 36));
  d->srf[SRF_MENU_OPEN]       = SDLazy_SurfaceLoad("img/sprites.png", SDLazy_Rect(290, 150,  32, 32));

  SDLazy_SetCenterAlign(d->srf[SRF_MENU_BG], ALIGN_TOP | ALIGN_LEFT);
  SDLazy_SetPosAlign(d->srf[SRF_MENU_BG], ALIGN_TOP | ALIGN_RIGHT);
  SDLazy_SetCenterX(d->srf[SRF_MENU_BG], 15);

  b = SDLazy_ButtonCreate(d->srf[SRF_MENU_FULLSCREEN], 2);
  d->btn[BTN_MENU_FULLSCREEN] = b;
  SDLazy_SetPosAlign(b, ALIGN_TOP | ALIGN_RIGHT);
  SDLazy_SetPosY(b, 5);
  SDLazy_SetCenterAlign(b, ALIGN_TOP | ALIGN_LEFT);
  SDLazy_ButtonSetFun(b, BUTTON_CLICUP, SDLazy_Fullscreen);

  b = SDLazy_ButtonCreate(d->srf[SRF_MENU_KEYBOARD], 2);
  d->btn[BTN_MENU_KEYBOARD] = b;
  SDLazy_SetCenterAlign(b, ALIGN_TOP | ALIGN_LEFT);
  SDLazy_SetPosAlign(b, ALIGN_TOP | ALIGN_RIGHT);
  SDLazy_SetPosY(b, 50);
  SDLazy_ButtonSetFun(b, BUTTON_CLICUP, ctrls_qwerty_azerty);

  b = SDLazy_ButtonCreate(d->srf[SRF_MENU_COMMANDS], 2);
  d->btn[BTN_MENU_COMMANDS] = b;
  SDLazy_SetCenterAlign(b, ALIGN_TOP | ALIGN_LEFT);
  SDLazy_SetPosAlign(b, ALIGN_TOP | ALIGN_RIGHT);
  SDLazy_SetPosY(b, 100);
  SDLazy_ButtonSetFun(b, BUTTON_CLICUP, ctrls_switch_cmds);

  b = SDLazy_ButtonCreate(d->srf[SRF_MENU_OPEN], 2);
  d->btn[BTN_MENU_OPEN] = b;
  SDLazy_SetPosAlign(b, ALIGN_TOP | ALIGN_RIGHT);
  SDLazy_SetCenterAlign(b, ALIGN_CENTER | ALIGN_CENTER);
  SDLazy_ButtonSetFun(b, BUTTON_CLICUP, _menu_openclose_cb);
}

void		menu_blit(Menu* d)
{
  double	x = SDLazy_GetPosX(d->srf[SRF_MENU_BG]);
  double	h2 = SDLazy_GetHeight(0) / 2;

  SDLazy_SetScaleY(d->srf[SRF_MENU_BG], h2 / 4);
  SDLazy_Blit(d->srf[SRF_MENU_BG]);

  SDLazy_SetPosX(d->btn[BTN_MENU_FULLSCREEN], x + 95);
  SDLazy_Blit(d->btn[BTN_MENU_FULLSCREEN]);

  SDLazy_SetPosX(d->btn[BTN_MENU_KEYBOARD], x - 2);
  SDLazy_Blit(d->btn[BTN_MENU_KEYBOARD]);

  SDLazy_SetPosX(d->btn[BTN_MENU_COMMANDS], x - 2);
  SDLazy_Blit(d->btn[BTN_MENU_COMMANDS]);

  SDLazy_SetPos(d->btn[BTN_MENU_OPEN], v2f_(x - 6, h2));
  SDLazy_Blit(d->btn[BTN_MENU_OPEN]);
}

void		menu_core(Menu* d)
{
  static int	w;
  double	x = SDLazy_GetPosX(d->srf[SRF_MENU_BG]);

  if (!w)
    w = SDLazy_GetWidth(d->srf[SRF_MENU_BG]) - SDLazy_GetCenterX(d->srf[SRF_MENU_BG]);
  x -= (d->status ? (w + x) : x) * .2;
  SDLazy_SetPosX(d->srf[SRF_MENU_BG], x);
}
