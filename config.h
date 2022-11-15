/* appearance */
static const unsigned int borderpx  = 0;//1        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const unsigned int gappih    = 0;//10       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;//10       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;//10       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;//10       /* vert outer gap between windows and screen edge */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 30;
static const char *fonts[] = { "JetBrainsMono Nerd Font:size=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=14";
static const char col_gray1[]       = "#2c323b";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#222222";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "nmtui", "-g", "144x41", "-e", "nmtui", NULL };
const char *spcmd3[] = {"st", "-n", "bc", "-g", "50x10", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"nmtui",       spcmd2},
	{"bc",	        spcmd3}
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	*	WM_CLASS(STRING) = instance, class
	*	WM_NAME(STRING) = title
	*/

	/* class		instance	title			tags mask	isfloating	isterminal	noswallow	monitor */
	{ "Gimpy",		NULL,		NULL,			0,			1,			0,			0,			-1 },
	{ "Firefox",	NULL,		NULL,			1 << 8,		0,			0,			-1,			-1 },
	{ "alacritty",	NULL,		NULL,			0,			0,			1,			0,			-1 },
	{ "st",     	NULL,		NULL,			0,			0,			1,			0,			-1 },
	{ NULL,			NULL,		"Event Tester",	0,			0,			0,			1,			-1 }, /* xev */

	{ NULL,			"spterm",	NULL,			SPTAG(0),	1,			1,			0,			-1 },
	{ NULL,			"nmtui",	NULL,			SPTAG(1),	1,			1,			0,			-1 },
	{ NULL,			"bc",		NULL,			SPTAG(2),	1,			1,			0,			-1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol	arrange function */
	{ "",	tile },    /* first entry is default */
	{ "",	NULL },    /* no layout function means floating behavior */
	{ "柳",	monocle },
};

/*
	{ "[]=",	tile },
	{ "><>",	NULL },
	{ "[M]",	monocle },
*/

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key			function		argument */
	/*workspaces*/
	TAGKEYS(                        XK_1,                       0)
		TAGKEYS(                        XK_2,                       1)
		TAGKEYS(                        XK_3,                       2)
		TAGKEYS(                        XK_4,                       3)
		TAGKEYS(                        XK_5,                       4)
		TAGKEYS(                        XK_6,                       5)
		TAGKEYS(                        XK_7,                       6)
		TAGKEYS(                        XK_8,                       7)
		TAGKEYS(                        XK_9,						8)
		{ MODKEY|ShiftMask,             XK_q,		quit,			{0} },
		{ MODKEY,						XK_q,		killclient,		{0} },
		/*media controls*/
		{ 0,				XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
		{ ShiftMask,		XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },
		{ 0,				XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
		{ ShiftMask,		XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },
		{ 0,				XF86XK_AudioPlay,			spawn,		SHCMD("playerctl play-pause") },
		{ 0,				XF86XK_AudioMute,			spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
		{ MODKEY,	        XK_comma,					spawn,	   	SHCMD("playerctl previous; kill -55 $(pidof dwmblocks)")},
		{ MODKEY,	        XK_period,					spawn,	   	SHCMD("playerctl next; kill -55 $(pidof dwmblocks)")},
		{ 0, 				XF86XK_MonBrightnessUp,		spawn,		SHCMD("xbacklight -inc 10; kill -45 $(pidof dwmblocks)") },
		{ 0, 				XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 10; kill -45 $(pidof dwmblocks)") },
		{ ShiftMask, 		XF86XK_MonBrightnessUp,		spawn,		SHCMD("xbacklight -inc 1; kill -45 $(pidof dwmblocks)") },
		{ ShiftMask, 		XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 1; kill -45 $(pidof dwmblocks)") },
		/*shortcuts*/
		{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
		{ MODKEY,	                    XK_Return, spawn,          {.v = termcmd } },
		{ MODKEY|ShiftMask,	            XK_Return, togglescratch,  {.ui = 0}},
		{ MODKEY,	                    XK_i,      togglescratch,  {.ui = 1}},
		{ MODKEY,	                    XK_slash,  togglescratch,  {.ui = 2}},
		{ MODKEY,	               	    XK_c, 	   spawn,          SHCMD("brave")},
		{ MODKEY,	               	    XK_t, 	   spawn,          SHCMD("thunar")},
		{ MODKEY,	               	    XK_w, 	   spawn,          SHCMD("whatsapp-nativefier")},
		{ MODKEY,	               	    XK_s, 	   spawn,          SHCMD("spotify")},
		{ MODKEY,	               	    XK_b, 	   spawn,          SHCMD("rofi-bt")},
		{ MODKEY,	               	    XK_Escape, spawn,		   SHCMD("lock")},
		{ MODKEY|ShiftMask,	     	    XK_Escape, spawn,		   SHCMD("rofi-power")},
		{ MODKEY,	             	    XK_d,      spawn,		   SHCMD("rofi -modi combi -combi-modi window#drun#run -show combi")},
		{ MODKEY,	             	    XK_v,      spawn,		   SHCMD("alacritty -e nvim")},
		{ MODKEY,	             	    XK_r,      spawn,		   SHCMD("pkill dwmblocks; sleep 2; dwmblocks &")},
		{ 0,		             	    XK_Print,  spawn,		   SHCMD("scrot -s -m ~/pics/screenshots/%s_%H%M_%d.%m.%Y.png")},
		/**/
		{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
		{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
		{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
		{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
		{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
		{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
		{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
		{ MODKEY,                       XK_space,  zoom,           {0} },
		{ MODKEY,                       XK_Tab,    view,           {0} },
		{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
		{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
		{ MODKEY,			            XK_f,      togglefullscr,  {0} },
		{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
		{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
		{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
		{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
		/*
			{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
			{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
			{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
			{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
			{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
			{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
			{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
			{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
			{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
			{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
			{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
			{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
			{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
			{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
			{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
			{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
			{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
			{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
			{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
			{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
		*/
		};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click				event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
