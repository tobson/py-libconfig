import sys

sys.path += ['./python']

from py_libconfig import Config

cfg = Config ('output.cfg')

print 'Re = {0}'.format (cfg.read_float ('physics.reynolds'))
print 'Lz = {0}'.format (cfg.read_float ('physics.boxsize.[2]'))
print 'nx = {0}'.format (cfg.read_int ('code.resolution.[0]'))
print 'name = {0}'.format (cfg.read_string ('name'))
