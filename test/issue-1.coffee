require '../lib/test-tools'

describe 'Float32Array constructor', ->
  it 'should not segfault', ->
    ( -> DSP.add(undefined) ).should.throw()
