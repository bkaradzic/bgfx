{
  'includes': [
    'target_defaults.gypi',
  ],
  'targets': [
    {
      'target_name': 'glslOptimizer',
      'dependencies': [
        'src/glsl_optimizer_lib.gyp:*',
      ],
      'sources': [
        'src/node/binding.cpp',
        'src/node/compiler.cpp',
        'src/node/compiler.h',
        'src/node/shader.cpp',
        'src/node/shader.h',
      ],
      'conditions': [
        ['OS=="win"', {
          'msvs_disabled_warnings': [4506],
        }],
      ],              
    }
  ]
}
