#=============================================================================
# bin2c.py
#=============================================================================

import sys
import os
import subprocess
import argparse
import re

#=============================================================================

PY3 = sys.version_info[0] == 3

#=============================================================================

def bin2c(outFile, filename, varname='data', linesize=80, indent=4):
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
	with open(outFile, 'w') as out_file:
		# limit the line length
		if linesize < 40:
			linesize = 40
		byte_len = 6  # '0x00, '
		out_file.write('const size_t %s_size = %d;\n' % (varname, len(data)))
		out_file.write('const uint8_t %s[%d] = {\n' % (varname, len(data)))
		line = ''
		for byte in data:
			line += '0x%02x, ' % (byte if PY3 else ord(byte))
			if len(line) + indent + byte_len >= linesize:
				out_file.write(' ' * indent + line + '\n')
				line = ''
		# add the last line
		if len(line) + indent + byte_len < linesize:
			out_file.write(' ' * indent + line + '\n')
		# strip the last comma
		out_file.write('};\n')

#=============================================================================

def main():

	argParser = argparse.ArgumentParser()
	argParser.add_argument( '-i', '--inputFile', action='store', dest='inputFile', help='Sets the input binary file.', required=True )
	argParser.add_argument( '-o', '--outputFile', action='store', dest='outputFile', help='Sets the output header file.', required=True )
	argParser.add_argument( '-v', '--variableName', action='store', dest='varName', help='Sets the global variable name.', required=True )
	options = argParser.parse_args()

	if not os.path.isfile(options.inputFile):
		print( 'Invalid input file: %s.' % (options.inputFile) )
		sys.exit(1)
	
	bin2c( options.outputFile, options.inputFile, options.varName )

#=============================================================================

if __name__ == "__main__":
	main()

#=============================================================================
