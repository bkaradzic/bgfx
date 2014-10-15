{
  'includes': [
    'target_defaults.gypi',
  ],
  'targets': [
    {
      "include_dirs" : [
          "<!(node -e \"require('nan')\")"
      ],
      'target_name': 'glslOptimizer',
      'dependencies': [
        'src/glsl_optimizer_lib.gyp:*',
      ],
      'sources': [
        'src/node/binding.cpp',
        'src/node/shader.h',
        'src/node/shader.cpp',
        'src/node/compiler.h',
        'src/node/compiler.cpp'
      ],
      'conditions': [
        ['OS=="win"', {
          'msvs_disabled_warnings': [4506],
        }],
      ],              
    }
  ]
}
