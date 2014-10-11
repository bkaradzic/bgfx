var glslOptimizer = require('../');
var assert = require('assert');

var fs = require('fs');
var path = require('path');
var frag = fs.readFileSync( path.join( __dirname, 'fragment', 'glsl140-basic-in.txt' ), 'utf8' );

assert.equal(glslOptimizer.TARGET_OPENGL, 0, 'exports TARGET_OPENGL');
assert.equal(glslOptimizer.TARGET_OPENGLES20, 1, 'exports TARGET_OPENGLES20');
assert.equal(glslOptimizer.TARGET_OPENGLES30, 2, 'exports TARGET_OPENGLES30');
assert.equal(glslOptimizer.VERTEX_SHADER, 0, 'exports VERTEX_SHADER');
assert.equal(glslOptimizer.FRAGMENT_SHADER, 1, 'exports FRAGMENT_SHADER');
assert.equal(typeof glslOptimizer.Compiler, 'function', 'exports Compiler constructor');

var ESSL = false; 

//First we need to create a new compiler
var compiler = new glslOptimizer.Compiler(2);

assert.equal(typeof compiler.dispose, 'function', 'exports Compiler#dispose()');

var shader = new glslOptimizer.Shader(compiler, glslOptimizer.FRAGMENT_SHADER, frag);

var didCompile = shader.compiled();
var raw = shader.rawOutput();
var output = shader.output();
var log = shader.log();

assert.equal(typeof didCompile, 'boolean', 'exports compiled()');
assert.equal(typeof raw, 'string', 'exports rawOutput()');
assert.equal(typeof output, 'string', 'exports output()');
assert.equal(typeof log, 'string', 'exports log()');

console.log(output, didCompile);

//Clean up shader...
shader.dispose();

//Clean up after we've created our compiler
compiler.dispose();