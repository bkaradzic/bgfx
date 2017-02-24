# Convert Font Awesome, Google Material Design and Kenney Game icon font
# parameters to C++11, C89 and None compatible formats.
#
#------------------------------------------------------------------------------
# 1 - Source material
#
#   1.1 - Font Awesome
#			https://github.com/FortAwesome/Font-Awesome/blob/master/fonts/fontawesome-webfont.ttf
# 			https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/src/icons.yml
#   1.2 - Material Design
#			https://github.com/google/material-design-icons/blob/master/iconfont/MaterialIcons-Regular.ttf
# 			https://raw.githubusercontent.com/google/material-design-icons/master/iconfont/codepoints
#   1.3 - Kenney icons
#			https://github.com/SamBrishes/kenney-icon-font/blob/master/fonts/kenney-icon-font.ttf
# 			https://raw.githubusercontent.com/SamBrishes/kenney-icon-font/master/css/kenney-icons.css
#
#------------------------------------------------------------------------------
# 2 - Data samples
#
#   2.1 - Font Awesome
#           - input:          - name:       Music
#                               id:         music
#                               unicode:    f001
#                               created:    1.0
#                               filter:
#                                 - note
#                                 - sound
#                               categories:
#                                 - Web Application Icons
#           - output C++11:     #define ICON_FA_MUSIC u8"\uf001"
#           - output C89:       #define ICON_FA_MUSIC "\xEF\x80\x81"
#			- output None:		    var icon-fa-music ""
#
#   2.2 - Google Material Design icons
#           - input:            3d_rotation e84d
#           - output C++11:     #define ICON_MD_3D_ROTATION u8"\ue84d"
#           - output C89:       #define ICON_MD_3D_ROTATION "\xEE\xA1\x8D"
#			- output None:		    var icon-md-3d_rotation ""
#
#   2.3 - Kenney Game icons
#           - input:            .ki-home:before{ content: "\e900"; }
#           - output C++11:     #define ICON_KI_HOME u8"\ue900"
#           - output C89:       #define ICON_KI_HOME "\xEE\xA4\x80"
#			- output None:		    var icon-ki-home ""
#
#   2.4 - All fonts
#           - computed min and max unicode fonts ICON_MIN and ICON_MAX
#           - output C89, C++11:	#define ICON_MIN_FA 0xf000
#                               	#define ICON_MAX_FA 0xf295
#			- output None:			    var icon-min-fa 0xf000
#									    var icon-max-fa 0xf2b2
#
#------------------------------------------------------------------------------
# 3 - Script dependencies
#
#   3.1 - Python 2.7 - https://www.python.org/download/releases/2.7/
#   3.2 - Requests - http://docs.python-requests.org/
#   3.3 - PyYAML - http://pyyaml.org/
#
#------------------------------------------------------------------------------
# 4 - References
#
# None language: https://bitbucket.org/duangle/nonelang/src
#
#------------------------------------------------------------------------------


import requests
import yaml


# Fonts

class Font:
	font_tff = '[ ERROR - missing tff file info ]'
	font_url = '[ ERROR - missing font data url ]'
	font_name = '[ ERROR - missing font name ]'
	font_abbr = '[ ERROR - missing font abbreviation ]'

	@classmethod
	def get_icons( cls, input ):
		# intermediate representation of the fonts data, identify the min and max
		print( '[ ERROR - missing implementation of class method get_icons for {!s} ]'.format( cls.font_name ))
		icons_data = {}
		icons_data.update({ 'font_min' : '[ ERROR - missing font min ]',
							'font_max' : '[ ERROR - missing font max ]',
							'icons' : '[ ERROR - missing list of pairs [ font icon name, code ]]' })
		return icons_data

	@classmethod
	def download( cls ):
		input_raw = ''
		try :
			response = requests.get( cls.font_url, timeout = 2 )
			if response.status_code == 200:
				input_raw = response.content
				print( 'Downloaded - ' + cls.font_name )
		except Exception as e :
			print( '[ ERROR - {!s}: {!s} ]'.format( cls.font_name, e ))
		return input_raw

	@classmethod
	def get_intermediate_representation( cls ):
		font_ir = {}
		input_raw = cls.download()
		if input_raw:
			icons_data = cls.get_icons( input_raw )
			font_ir.update( icons_data )
			font_ir.update({ 'font_tff' : cls.font_tff,
							 'font_url' : cls.font_url,
							 'font_name' : cls.font_name,
							 'font_abbr' : cls.font_abbr })
			print( 'Generated intermediate data - ' + cls.font_name )
		return font_ir


class FontFA( Font ):
	font_tff = 'https://github.com/FortAwesome/Font-Awesome/blob/master/fonts/fontawesome-webfont.ttf'
	font_url = 'https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/src/icons.yml'
	font_name = 'font_awesome'
	font_abbr = 'FA'

	@classmethod
	def get_icons( self, input ):
		icons_data = {}
		data = yaml.safe_load( input )
		if data:
			font_min = 'ffff'
			font_max = '0'
			icons = []
			for item in data[ 'icons' ]:
				if item[ 'unicode' ] < font_min:
					font_min = item[ 'unicode' ]
				if item[ 'unicode' ] >= font_max:
					font_max = item[ 'unicode' ]
				icons.append([ item[ 'id' ], item[ 'unicode' ]])
			icons_data.update({ 'font_min' : font_min,
								'font_max' : font_max,
								'icons' : icons })
		return icons_data


class FontMD( Font ):
	font_tff = 'https://github.com/google/material-design-icons/blob/master/iconfont/MaterialIcons-Regular.ttf'
	font_url = 'https://raw.githubusercontent.com/google/material-design-icons/master/iconfont/codepoints'
	font_name = 'material_design'
	font_abbr = 'MD'

	@classmethod
	def get_icons( self, input ):
		icons_data = {}
		lines = str.split( input, '\n' )
		if lines:
			font_min = 'ffff'
			font_max = '0'
			icons = []
			for line in lines :
				words = str.split(line)
				if words and len( words ) >= 2:
					if words[ 1 ] < font_min:
						font_min = words[ 1 ]
					if words[ 1 ] >= font_max:
						font_max = words[ 1 ]
					icons.append( words )
			icons_data.update({ 'font_min' : font_min,
								'font_max' : font_max,
								'icons' : icons  })
		return icons_data


class FontKI( Font ):
	font_tff = 'https://github.com/SamBrishes/kenney-icon-font/blob/master/fonts/kenney-icon-font.ttf'
	font_url = 'https://raw.githubusercontent.com/SamBrishes/kenney-icon-font/master/css/kenney-icons.css'
	font_name = 'kenney'
	font_abbr = 'KI'

	@classmethod
	def get_icons( self, input ):
		icons_data = {}
		lines = str.split( input, '\n' )
		if lines:
			font_min = 'ffff'
			font_max = '0'
			icons = []
			for line in lines :
				if '.ki-' in line:
					words = str.split(line)
					if words and '.ki-' in words[ 0 ]:
						font_id = words[ 0 ].partition( '.ki-' )[2].partition( ':before' )[0]
						font_code = words[ 2 ].partition( '"\\' )[2].partition( '";' )[0]
						if font_code < font_min:
							font_min = font_code
						if font_code >= font_max:
							font_max = font_code
						icons.append([ font_id, font_code ])
			icons_data.update({ 'font_min' : font_min,
								'font_max' : font_max,
								'icons' : icons  })
		return icons_data


# Languages


class Language:
	language_name = '[ ERROR - missing language name ]'
	file_name = '[ ERROR - missing file name ]'
	intermediate = {}

	def __init__( self, intermediate ):
		self.intermediate = intermediate

	@classmethod
	def prelude( cls ):
		print('[ ERROR - missing implementation of class method prelude for {!s} ]'.format(cls.language_name))
		result = '[ ERROR - missing prelude ]'
		return result

	@classmethod
	def lines_minmax( cls ):
		print('[ ERROR - missing implementation of class method lines_minmax for {!s} ]'.format(cls.language_name))
		result = '[ ERROR - missing min and max ]'
		return result

	@classmethod
	def line_icon( cls, icon ):
		print('[ ERROR - missing implementation of class method line_icon for {!s} ]'.format( cls.language_name ))
		result = '[ ERROR - missing icon line ]'
		return result

	@classmethod
	def convert( cls ):
		result = cls.prelude() + cls.lines_minmax()
		for icon in cls.intermediate.get( 'icons' ):
			line_icon = cls.line_icon( icon )
			result += line_icon
		print ( 'Converted - {!s} for {!s}' ).format( cls.intermediate.get( 'font_name' ), cls.language_name)
		return result

	@classmethod
	def save_to_file( cls ):
		filename = cls.file_name.format( name = str(cls.intermediate.get( 'font_name' )).replace( ' ', '' ))
		converted = cls.convert()
		with open( filename, 'w' ) as f:
			f.write( converted )
		print( 'Saved - {!s}' ).format( filename )


class LanguageC89( Language ):
	language_name = 'C89'
	file_name = 'icons_{name}.h'

	@classmethod
	def prelude( cls ):
		tmpl_prelude = '// Generated by GenerateIconFontCppHeaders.py for language {lang}\n' + \
					   '// from {url}\n' + \
					   '// for use with {tff}\n' + \
					   '#pragma once\n\n'
		result = tmpl_prelude.format(lang = cls.language_name,
									 url = cls.intermediate.get('font_url'),
									 tff = cls.intermediate.get('font_tff'))
		return result

	@classmethod
	def lines_minmax( cls ):
		tmpl_line_minmax = '#define ICON_{minmax}_{abbr} 0x{val}\n'
		result = tmpl_line_minmax.format(minmax = 'MIN',
										 abbr = cls.intermediate.get('font_abbr'),
										 val = cls.intermediate.get('font_min')) + \
				 tmpl_line_minmax.format(minmax = 'MAX',
										 abbr = cls.intermediate.get('font_abbr'),
										 val = cls.intermediate.get('font_max'))
		return result

	@classmethod
	def line_icon( cls, icon ):
		tmpl_line_icon = '#define ICON_{abbr}_{icon} "{code}"\n'
		icon_name = str.upper( icon[ 0 ]).replace( '-', '_' )
		code_base = ''.join([ '{0:x}'.format( ord( x )) for x in unichr( int( icon[ 1 ], 16 )).encode( 'utf-8' )]).upper()
		icon_code = '\\x' + code_base[ :2 ] + '\\x' + code_base[ 2:4 ] + '\\x' + code_base[ 4: ]
		result = tmpl_line_icon.format( abbr = cls.intermediate.get( 'font_abbr' ),
										icon = icon_name,
										code = icon_code )
		return result


class LanguageCpp11( LanguageC89 ):
	language_name = 'C++11'
	file_name = 'Icons{name}.h'

	@classmethod
	def line_icon( cls, icon ):
		tmpl_line_icon = '#define ICON_{abbr}_{icon} u8"\u{code}"\n'
		icon_name = str.upper( icon[ 0 ]).replace( '-', '_' )
		icon_code = icon[ 1 ]
		result = tmpl_line_icon.format( abbr = cls.intermediate.get('font_abbr'),
										icon = icon_name,
										code = icon_code)
		return result


class LanguageNone( Language ):
	language_name = 'None'
	file_name = 'Icons{name}.n'

	@classmethod
	def prelude( cls ):
		tmpl_prelude = 'none\n' + \
					   '; Generated by GenerateIconFontCppHeaders.py for language {lang}\n' + \
					   '; from {url}\n' + \
					   '; for use with {tff}\n' + \
					   '\n$\n'
		result = tmpl_prelude.format( lang = cls.language_name,
									  url = cls.intermediate.get( 'font_url' ),
									  tff = cls.intermediate.get( 'font_tff' ))
		return result

	@classmethod
	def lines_minmax( cls ):
		tmpl_line_minmax = '    var icon-{minmax}-{abbr} 0x{val}\n'
		result = tmpl_line_minmax.format( minmax = 'min',
										  abbr = cls.intermediate.get( 'font_abbr' ).lower(),
										  val = cls.intermediate.get( 'font_min' )) + \
				 tmpl_line_minmax.format( minmax = 'max',
										  abbr = cls.intermediate.get( 'font_abbr' ).lower(),
										  val = cls.intermediate.get( 'font_max' ))
		return result

	@classmethod
	def line_icon( cls, icon ):
		tmpl_line_icon = '    var icon-{abbr}-{icon} "{code}"\n'
		icon_name = str.upper( icon[ 0 ]).replace( '-', '_' ).lower()
		icon_code = unichr( int( icon[ 1 ], 16 )).encode( 'utf-8' )
		result = tmpl_line_icon.format( abbr = cls.intermediate.get( 'font_abbr' ).lower(),
									    icon = icon_name,
									    code = icon_code )
		return result


# Main

fonts = [ FontKI , FontMD, FontFA ]
languages = [ LanguageC89 ]

intermediates = []
for font in fonts:
	intermediates.append( font.get_intermediate_representation())
for interm in intermediates:
	Language.intermediate = interm
	for lang in languages:
		lang.save_to_file()
