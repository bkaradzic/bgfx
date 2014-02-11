{
  'target_defaults': {
    'configurations': {
      'Debug': {
        'defines': [
          'DEBUG',
          '_DEBUG',
        ],
      },
      'Release': {
        'defines': [
          'NDEBUG',
        ],
      },
    },
    'conditions': [
      ['OS=="win"', {
        'target_defaults': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'ExceptionHandling': '0',
            },
          },
        },
      }],
    ],
  }
}
