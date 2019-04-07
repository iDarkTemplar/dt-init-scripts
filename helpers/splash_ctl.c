/*
 * Copyright (C) 2017 i.Dark_Templar <darktemplar@dark-templar-archives.net>
 *
 * This file is part of DT init scripts.
 *
 * DT init scripts is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DT init scripts is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DT init scripts.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <fbsplash.h>

#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <string.h>

typedef enum {
	act_undef,
	act_set_verbose,
	act_set_silent,
	act_get_mode
} enum_act;

void usage(const char *name)
{
	printf(
	"Usage: %s <action>\n"
	"\n"
	"Actions:\n"
	"\tverbose - set splash mode verbose\n"
	"\tsilent  - set splash mode silent\n"
	"\tgetmode - prints \"silent\" or \"verbose\" depending on current splash mode\n",
	name
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
		if (strcmp(argv[1],"verbose") == 0)
		{
			action = act_set_verbose;
		}
		else if (strcmp(argv[1],"silent") == 0)
		{
			action = act_set_silent;
		}
		else if (strcmp(argv[1], "getmode") == 0)
		{
			action = act_get_mode;
		}
	}

	// init splash libs
	fbspl_cfg = fbsplash_lib_init(fbspl_undef);
	fbsplash_parse_kcmdline(false);
	//fbsplash_set_evdev();
	fbsplashr_init(false);
	theme = fbsplashr_theme_load();

	switch (action)
	{
	case act_undef:
		usage(argv[0]);
		break;

	case act_set_verbose:
		if (fbsplash_is_silent() && theme)
		{
			fbsplashr_tty_silent_cleanup();
			fbsplash_set_verbose(0);
		}
		break;

	case act_set_silent:
		if ((!fbsplash_is_silent()) && theme)
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

	case act_get_mode:
		if (fbsplash_is_silent())
		{
			printf("silent\n");
		}
		else
		{
			printf("verbose\n");
		}
		break;
	}

	// deinit splash libs
	fbsplashr_theme_free(theme);
	fbsplashr_cleanup();
	fbsplash_lib_cleanup();

	return 0;
}
