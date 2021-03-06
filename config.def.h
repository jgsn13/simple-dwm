/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono NF:style:medium:size=10" };
static const char dmenufont[]       = "JetBrainsMono NF:style:medium:size=11";

static const char col_gray1[] = "#0d1012";
static const char col_gray2[] = "#171716";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[] = "#61538D";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = {"", "", "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "feh",      NULL,       NULL,       0,            1,           -1 },
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	/* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, */
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define AltMask Mod1Mask
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
static const char *dmenucmd[] = { "dmenu_run", "-p",  "Run",     "-m",  dmenumon, "-fn", dmenufont, "-nb", col_gray1,   "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL};
static const char *termcmd[]  = { "st", NULL };

/* Actions */

/* Custom scripts */
/* look at the scripts folder */
static const char *dmenuemoji[] = {"dmenuunicode", NULL};
static const char *print_select[] = {"print_select", NULL};
static const char *print_fullscreen[] = {"print_fullscreen", NULL};
static const char *print_window[] = {"print_window", NULL};
static const char *copygittoken[] = {"copygittoken", NULL};

/* Move the scripts on scripts folder to /bin */
static const char *volup[] = {"amixer", "sset", "Master", "5%+", NULL};
static const char *voldown[] = {"amixer", "sset", "Master", "5%-", NULL};
static const char *volmute[] = {"amixer", "sset", "Master", "0%", NULL};
static const char *volunmute[] = {"amixer", "sset", "Master", "60%", NULL};

// commands
static const char *rofi[] = {"rofi", "-show", "drun", "-show-icons", NULL};
static const char *mapbr[] = {"setxkbmap", "br", NULL};
static const char *mapus[] = {"setxkbmap", "us", NULL};
static const char *ranger[] = {"st", "-e", "ranger", NULL};
static const char *bottom[] = {"st", "-e", "btm", NULL};
static const char *shutdown[] = {"sudo", "shutdown", "-h", "now", NULL};
static const char *reboot[] = {"sudo", "reboot", NULL};
static const char *slock[] = {"slock", NULL};
static const char *xkill[] = {"xkill", NULL};
static const char *xi[] = {"xbacklight", "-inc", "7", NULL};
static const char *xd[] = {"xbacklight", "-dec", "7", NULL};

static Key keys[] = {
    /* modifier                        key            function           argument */
    {MODKEY,                           XK_space,      spawn,             {.v = dmenucmd}},
    {MODKEY,                           XK_Return,     spawn,             {.v = termcmd}},
    {MODKEY|ControlMask,               XK_space,      spawn,             {.v = rofi}},

    // custom
    
    {MODKEY,                           XK_p,          spawn,             {.v = print_select}},
    {MODKEY|ControlMask,               XK_p,          spawn,             {.v = print_fullscreen}},
    {MODKEY|ControlMask|ShiftMask,     XK_p,          spawn,             {.v = print_window}},
    {MODKEY,                           XK_l,          spawn,             {.v = slock}},
    {MODKEY|AltMask,                   XK_k,          spawn,             {.v = volup}},
    {MODKEY|AltMask,                   XK_j,          spawn,             {.v = voldown}},
    {MODKEY|AltMask,                   XK_m,          spawn,             {.v = volmute}},
    {MODKEY|AltMask,                   XK_u,          spawn,             {.v = volunmute}},
    {MODKEY|AltMask,                   XK_f,          spawn,             {.v = ranger}},
    {MODKEY|ControlMask,               XK_m,          spawn,             {.v = bottom}},
    {MODKEY|ControlMask,               XK_s,          spawn,             {.v = shutdown}},
    {MODKEY|ControlMask,               XK_r,          spawn,             {.v = reboot}},
    {MODKEY|ControlMask,               XK_g,          spawn,             {.v = copygittoken}},
    {MODKEY,                           XK_e,          spawn,             {.v = dmenuemoji}},
    {MODKEY|ControlMask,               XK_x,          spawn,             {.v = xkill}},
    {MODKEY|ControlMask,               XK_b,          spawn,             {.v = mapbr}},
    {MODKEY|ControlMask,               XK_u,          spawn,             {.v = mapus}},
    {MODKEY|ControlMask,               XK_k,          spawn,             {.v = xi}},
    {MODKEY|ControlMask,               XK_j,          spawn,             {.v = xd}},

    // other

    {MODKEY,                           XK_b,          togglebar,         {0}},
	{MODKEY,                           XK_j,          focusstackvis,     {.i = +1 }},
	{MODKEY,                           XK_k,          focusstackvis,     {.i = -1 }},
	{MODKEY|ShiftMask,                 XK_j,          focusstackhid,     {.i = +1 }},
	{MODKEY|ShiftMask,                 XK_k,          focusstackhid,     {.i = -1 }},
    {MODKEY,                           XK_i,          incnmaster,        {.i = +1}},
    {MODKEY,                           XK_o,          incnmaster,        {.i = -1}},
    {MODKEY|ShiftMask,                 XK_h,          setmfact,          {.f = -0.05}},
    {MODKEY|ShiftMask,                 XK_l,          setmfact,          {.f = +0.05}},
    {MODKEY|ShiftMask,                 XK_Return,     zoom,              {0}},
    {MODKEY,                           XK_Tab,        view,              {0}},
    {MODKEY,                           XK_w,          killclient,        {0}},
    {MODKEY,                           XK_t,          setlayout,         {.v = &layouts[0]}},
    {MODKEY,                           XK_f,          setlayout,         {.v = &layouts[1]}},
    {MODKEY,                           XK_m,          setlayout,         {.v = &layouts[2]}},
	{MODKEY,                           XK_u,          setlayout,         {.v = &layouts[3]}},
	{MODKEY,                           XK_o,          setlayout,         {.v = &layouts[4]}},
	{MODKEY,                           XK_d,          setlayout,         {.v = &layouts[5]}},
	{MODKEY,                           XK_g,          setlayout,         {.v = &layouts[6]}},
    {MODKEY,                           XK_q,          setlayout,         {0}},
    {MODKEY|ShiftMask,                 XK_space,      togglefloating,    {0}},
    /* {MODKEY|ShiftMask,                 XK_f,          togglefullscr,     {0}}, */
    {MODKEY,                           XK_0,          view,              {.ui = ~0}},
    {MODKEY|ShiftMask,                 XK_0,          tag,               {.ui = ~0}},
    {MODKEY,                           XK_comma,      focusmon,          {.i = -1}},
    {MODKEY,                           XK_period,     focusmon,          {.i = +1}},
    {MODKEY|ShiftMask,                 XK_comma,      tagmon,            {.i = -1}},
    {MODKEY|ShiftMask,                 XK_period,     tagmon,            {.i = +1}},
    {MODKEY,                           XK_n,          toggletag,         {.ui = 1}},
	{MODKEY,                           XK_s,          show,              {0}},
	{MODKEY,                           XK_h,          hide,              {0}},
    TAGKEYS(XK_1, 0)
    TAGKEYS(XK_2, 1)
    TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4)
    TAGKEYS(XK_6, 5)
    {MODKEY|ShiftMask,                 XK_q,          quit,              {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

