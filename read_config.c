#include "read_config.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int read_config (const char *input_file, const char *output_file)
{
  config_t cfg;

  config_init (&cfg);

  /* Read the file. If there is an error, report it and exit. */
  if (!config_read_file (&cfg, input_file))
  {
    fprintf (stderr, "%s:%d - %s\n", input_file,
            config_error_line (&cfg), config_error_text (&cfg));
    config_destroy (&cfg);
    return (EXIT_FAILURE);
  }

  // Settings root
  config_setting_t *root = config_root_setting(&cfg);

  // Description of configuration file
  const char *desc = "Snoopy configuration file.";
  read_string (root, "name", &desc);

  // Create physics group
  config_setting_t *physics = add_group (root, "physics");

  // Boxsize
  /* double boxsize[] = {1.0, 1.0, 1.0}; */
  /* read_float_array (physics, "boxsize", &boxsize, 3); */
  /* printf ("boxsize = [%f,%f,%f]\n", boxsize[0], boxsize[1], boxsize[2]); */
  double Lx = 1.0, Ly = 1.0, Lz = 1.0;
  read_float_list (physics, "boxsize", 3, &Lx, &Ly, &Lz);
  printf ("Lx = %f, Ly = %f, Lz = %f\n", Lx, Ly, Lz);

  // Reynolds number
  double Re = 1.0;
  read_float (physics, "reynolds", &Re);
  printf ("Re = %f\n", Re);

  // Magnetic Reynolds number
  double Rm = 1.0;
  read_float (physics, "reynolds_m", &Rm);
  printf ("Rm = %f\n", Rm);

  // Create code group
  config_setting_t *code = add_group (root, "code");

  // Resolution
  int nx = 32, ny = 32, nz = 32;
  read_int_list (code, "pansen", 3, &nx, &ny, &nz);
  printf ("nx = %d, ny = %d, nz = %d\n", nx, ny, nz);

  int dealias = 0;
  read_bool (code, "dealias", &dealias);
  printf ("dealias = %d\n", dealias);

  /* Write out the updated configuration. */
  if (!config_write_file (&cfg, output_file))
  {
    fprintf(stderr, "Error while writing file.\n");
    config_destroy (&cfg);
    return(EXIT_FAILURE);
  }

  fprintf(stderr, "Updated configuration successfully written to: %s\n",
          output_file);

  config_destroy(&cfg);
  return(EXIT_SUCCESS);
}

/* eof */

config_setting_t *add_group (config_setting_t *parent, const char *name)
{
  config_setting_t *group = config_setting_get_member (parent, name);
  if (!group)
  {
    group = config_setting_add (parent, name, CONFIG_TYPE_GROUP);
  }
  return group;
}

void read_int (config_setting_t *parent, const char *name, long *value)
{
  config_setting_t *setting = config_setting_get_member (parent, name);

  if (setting) {
    *value = config_setting_get_int (setting);
    return;
  }

  setting = config_setting_add (parent, name, CONFIG_TYPE_FLOAT);
  config_setting_set_int (setting, *value);
}

void read_float (config_setting_t *parent, const char *name, double *value)
{
  config_setting_t *setting = config_setting_get_member (parent, name);

  if (setting) {
    *value = config_setting_get_float (setting);
    return;
  }

  setting = config_setting_add (parent, name, CONFIG_TYPE_FLOAT);
  config_setting_set_float (setting, *value);
}

void read_bool (config_setting_t *parent, const char *name, int *value)
{
  config_setting_t *setting = config_setting_get_member (parent, name);

  if (setting) {
    *value = config_setting_get_bool (setting);
    return;
  }

  setting = config_setting_add (parent, name, CONFIG_TYPE_BOOL);
  config_setting_set_bool (setting, *value);
}

void read_string (config_setting_t *parent, const char *name, const char **value)
{
  config_setting_t *setting = config_setting_get_member (parent, name);

  if (setting) {
    *value = config_setting_get_string (setting);
    return;
  }

  setting = config_setting_add (parent, name, CONFIG_TYPE_STRING);
  config_setting_set_string (setting, *value);
}

void read_int_list (config_setting_t *parent, const char *name,
    const unsigned int count, ...) {

  va_list args;
  unsigned int index;

  va_start (args, count);

  config_setting_t *setting = config_setting_get_member (parent, name);

  if (setting) {
    assert (config_setting_length (setting) == count);
    for (index = 0; index < count; index++)
    {
      long value = config_setting_get_int_elem (setting, index);
      *va_arg (args, int*) = (int) value;
    }
    return;
  }

  setting = config_setting_add (parent, name, CONFIG_TYPE_ARRAY);
  for (index = 0; index < count; index++) {
    long value = (long) *va_arg (args, int*);
    config_setting_set_int_elem (setting, -1, value);
  }
}

void read_float_list (config_setting_t *parent, const char *name,
    const unsigned int count, ...) {

  va_list args;

  va_start (args, count);

  config_setting_t *setting = config_setting_get_member (parent, name);

  if (setting) {
    assert (config_setting_length (setting) == count);
    for (unsigned int index = 0; index < count; index++)
    {
      double value = config_setting_get_float_elem (setting, index);
      *va_arg (args, double*) = value;
    }
    return;
  }

  setting = config_setting_add (parent, name, CONFIG_TYPE_ARRAY);
  for (unsigned int index = 0; index < count; index++) {
    double value = *va_arg (args, double*);
    config_setting_set_float_elem (setting, -1, value);
  }
}
