require '../lib/test-tools'

describe 'FFT', ->
  describe '#forward', ->
    it 'should not segfault on uneven N', ->
      fft = new FFT(3)
      fft.forward(F(3), F(3), F(3))

  describe '#inverse', ->
    it 'should not segfault on uneven N', ->
      fft = new FFT(3)
      fft.inverse(F(3), F(3), F(3))
