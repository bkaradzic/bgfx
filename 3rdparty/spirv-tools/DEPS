use_relative_paths = True

vars = {
  'github': 'https://github.com',

  'effcee_revision': '6fa2a03cebb4fb18fbad086d53d1054928bef54e',
  'googletest_revision': 'f2fb48c3b3d79a75a88a99fba6576b25d42ec528',
  're2_revision': '5bd613749fd530b576b890283bfb6bc6ea6246cb',
  'spirv_headers_revision': '601d738723ac381741311c6c98c36d6170be14a2',
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

