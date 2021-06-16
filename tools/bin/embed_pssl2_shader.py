import sys
import os
import subprocess
import argparse
import re

#=============================================================================

PY3 = sys.version_info[0] == 3

#=============================================================================

def bin2c(filename, varname='data', linesize=80, indent=4):
	""" Read binary data from file and return as a C array
	:param filename: a filename of a file to read.
	:param varname: a C array variable name.
	:param linesize: a size of a line (min value is 40).
	:param indent: an indent (number of spaces) that prepend each line.
	"""
	if not os.path.isfile(filename):
		print('File "%s" is not found!' % filename)
		return ''
	if not re.match('[a-zA-Z_][a-zA-Z0-9_]*', varname):
		print('Invalid variable name "%s"' % varname)
		return
	with open(filename, 'rb') as in_file:
		data = in_file.read()
	# limit the line length
	if linesize < 40:
		linesize = 40
	byte_len = 6  # '0x00, '
	out = 'const size_t %s_size = %d;\n' % (varname, len(data))
	out += 'const uint8_t %s_data[%d] = {\n' % (varname, len(data))
	line = ''
	for byte in data:
		line += '0x%02x, ' % (byte if PY3 else ord(byte))
		if len(line) + indent + byte_len >= linesize:
			out += ' ' * indent + line + '\n'
			line = ''
	# add the last line
	if len(line) + indent + byte_len < linesize:
		out += ' ' * indent + line + '\n'
	# strip the last comma
	out = out.rstrip(', \n') + '\n'
	out += '};'
	return out

#=============================================================================

def main():

	argParser = argparse.ArgumentParser()
	argParser.add_argument( '-i', '--inputFile', action='store', dest='inputFile', help='Sets the input pssl2 file.', required=True )
	argParser.add_argument( '-p', '--profile', action='store', dest='profile', help='Set profile: vertex, pixel.', required=True )
	options = argParser.parse_args()

	if not os.path.isfile(options.inputFile):
		print( 'Invalid input file: %s.' % (options.inputFile) )
		sys.exit(1)
	
	if options.profile.lower() not in ['vertex', 'pixel']:
		print( 'Invalid profile: %s.' % (options.profile) )
		sys.exit(1)

	profiles = { 'vertex': 'sce_vs_vs_prospero', 'pixel': 'sce_ps_prospero' }
	profile = profiles.get(options.profile.lower(), None)
	if not profile:
		print( 'Invalid profile: %s.' % (options.profile) )

	outputFile = options.inputFile + '.h'
	agsFile = options.inputFile + '.ags'
	result = subprocess.run(['prospero-wave-psslc', '-fastmath', '-o', agsFile, '-O3', options.inputFile, '-profile', profile],
							stdout=subprocess.PIPE,
							universal_newlines=True)
	if result.returncode != 0 or not os.path.isfile( agsFile ):
		print( 'Compiler failed, output: %s' % (result.stdout) )
		sys.exit(1)

	varName = os.path.splitext( os.path.basename( options.inputFile ) )[0]
	src = bin2c( agsFile, varName )
	with open( outputFile, 'w' ) as fh:
		fh.write( src )
	os.unlink( agsFile )

#=============================================================================

if __name__ == "__main__":
	main()

#=============================================================================
