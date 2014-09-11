#ifndef READ_CONFIG_H
#define READ_CONFIG_H

#include "libconfig/libconfig.h"

config_setting_t *add_group (config_setting_t *, const char *);

void read_int (config_setting_t *, const char *, long *);
void read_float (config_setting_t *, const char *, double *);
void read_bool (config_setting_t *, const char *, int *);
void read_string (config_setting_t *, const char *, const char **);

void read_int_list (config_setting_t *, const char *, const unsigned int, ...);
void read_float_list (config_setting_t *, const char *, const unsigned int, ...);

int read_config (const char *, const char *);

#endif
