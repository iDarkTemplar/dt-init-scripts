#include <fbsplash.h>
#include <stdio.h>
#include <string.h>

typedef enum {
	act_undef,
	act_set_verbose,
	act_set_silent
} enum_act;

void usage(void)
{
	printf(
	"Usage: splash_ctl <action>\n"
	"\n"
	"Actions:\n"
	"\tverbose - set splash mode verbose\n"
	"\tsilent  - set splash mode silent\n"
	);
}

int main(int argc, char **argv)
{
	enum_act action = act_undef;
	fbspl_cfg_t *fbspl_cfg;
	struct fbspl_theme *theme;

	// parse options
	if (argc == 2)
	{
		if (!strcmp(argv[1],"verbose"))
		{
			action = act_set_verbose;
		}
		else if (!strcmp(argv[1],"silent"))
		{
			action = act_set_silent;
		}
	}

	// init splash libs
	fbspl_cfg = fbsplash_lib_init(fbspl_undef);
	fbsplash_parse_kcmdline(false);
	//fbsplash_acc_theme_set("natural_gentoo");
	//fbsplash_set_evdev();
	fbsplashr_init(false);
	theme = fbsplashr_theme_load();

	switch (action)
	{
	case act_undef:
		usage();
		break;

	case act_set_verbose:
		if (fbsplash_is_silent())
		{
			fbsplashr_tty_silent_cleanup();
			fbsplash_set_verbose(0);
		}
		break;

	case act_set_silent:
		if (!fbsplash_is_silent())
		{
			fbsplash_set_silent();
			fbsplashr_tty_silent_init(true);
			fbsplashr_render_screen(theme,true,false,FBSPL_EFF_NONE);
			/*if (fbsplashr_tty_silent_update())
			{
				fbsplashr_tty_silent_cleanup();
				fbsplash_set_verbose(0);
				printf("Need to reload theme\n");
			}*/
		}
		break;
	}

	// deinit splash libs
	fbsplashr_theme_free(theme);
	fbsplashr_cleanup();
	fbsplash_lib_cleanup();

	return 0;
}
