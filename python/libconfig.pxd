cdef extern from "../libconfig/libconfig.h":

    ctypedef struct config_t:
        pass

    enum: CONFIG_TRUE
    enum: CONFIG_FALSE

    void config_init (config_t *config)
    void config_destroy (config_t * config)
    int config_read_file (config_t *config, char *filename)

    int config_lookup_int (config_t *config, char *path, long *value)
    int config_lookup_float (config_t *config, char *path, double *value)
    int config_lookup_bool (config_t *config, char *path, int *value)
    int config_lookup_string (config_t *config, char *path, const char **value)
