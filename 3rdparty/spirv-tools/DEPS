use_relative_paths = True

vars = {
  'github': 'https://github.com',

  'effcee_revision': 'b83b58d177b797edd1f94c5f10837f2cc2863f0a',
  'googletest_revision': '2f42d769ad1b08742f7ccb5ad4dd357fc5ff248c',
  're2_revision': '848dfb7e1d7ba641d598cb66f81590f3999a555a',
  'spirv_headers_revision': 'de99d4d834aeb51dd9f099baa285bd44fd04bb3d',
}

deps = {
  'external/effcee':
      Var('github') + '/google/effcee.git@' + Var('effcee_revision'),

  'external/googletest':
      Var('github') + '/google/googletest.git@' + Var('googletest_revision'),

  'external/re2':
      Var('github') + '/google/re2.git@' + Var('re2_revision'),

  'external/spirv-headers':
      Var('github') +  '/KhronosGroup/SPIRV-Headers.git@' +
          Var('spirv_headers_revision'),
}

