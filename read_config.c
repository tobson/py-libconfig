#include "read_config.h"

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

  // Create physics group
  config_setting_t *physics = add_group (root, "physics");

  // Boxsize
  double boxsize[] = {1.0, 1.0, 1.0};
  read_float_array (physics, "boxsize", &boxsize, 3);
  printf ("boxsize = [%f,%f,%f]\n", boxsize[0], boxsize[1], boxsize[2]);

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
  int resolution[] = {32, 32, 32};
  read_int_array (code, "resolution", &resolution, 3);
  printf ("resolution = [%d,%d,%d]\n", resolution[0], resolution[1], resolution[2]);

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

void read_float_array (config_setting_t *parent, const char *name, double (*array)[], unsigned int length) {

  unsigned int index;

  config_setting_t *setting = config_setting_get_member (parent, name);

  if (setting) {
    assert (config_setting_length (setting) == length);
    for (index = 0; index < length; index++)
    {
      (*array)[index] = config_setting_get_float_elem (setting, index);
    }
    return;
  }

  setting = config_setting_add (parent, name, CONFIG_TYPE_ARRAY);
  for (index = 0; index < length; index++) {
    config_setting_set_float_elem (setting, -1, (*array)[index]);
  }
}

void read_int (config_setting_t *parent, const char *name, int *value)
{
  config_setting_t *setting = config_setting_get_member (parent, name);

  if (setting) {
    *value = config_setting_get_float (setting);
    return;
  }

  setting = config_setting_add (parent, name, CONFIG_TYPE_FLOAT);
  config_setting_set_int (setting, *value);
}

void read_int_array (config_setting_t *parent, const char *name, int (*array)[], unsigned int length) {

  unsigned int index;

  config_setting_t *setting = config_setting_get_member (parent, name);

  if (setting) {
    assert (config_setting_length (setting) == length);
    for (index = 0; index < length; index++)
    {
      (*array)[index] = config_setting_get_float_elem (setting, index);
    }
    return;
  }

  setting = config_setting_add (parent, name, CONFIG_TYPE_ARRAY);
  for (index = 0; index < length; index++) {
    config_setting_set_int_elem (setting, -1, (*array)[index]);
  }
}
