from libconfig cimport *

cdef class Config:
    cdef config_t cfg
    def __cinit__ (self, char *filename):
        config_init (&self.cfg)
        assert (config_read_file (&self.cfg, filename) == CONFIG_TRUE)
    def read_int (self, char *path):
        cdef long value
        assert (config_lookup_int (&self.cfg, path, &value) == CONFIG_TRUE)
        return value
    def read_float (self, char *path):
        cdef double value
        assert (config_lookup_float (&self.cfg, path, &value) == CONFIG_TRUE)
        return value
    def read_bool (self, char *path):
        cdef int value
        assert (config_lookup_bool (&self.cfg, path, &value) == CONFIG_TRUE)
        return value
    def read_string (self, char *path):
        cdef const char *value
        assert (config_lookup_string (&self.cfg, path, &value) == CONFIG_TRUE)
        return value
    def __dealloc__ (self):
        config_destroy (&self.cfg)
