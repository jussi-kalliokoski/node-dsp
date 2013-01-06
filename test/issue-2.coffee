require '../lib/test-tools'

describe 'FFT', ->
  describe '#forward', ->
    it 'should not segfault on odd N', ->
      fft = new FFT(5)
      fft.forward(F(5), F(5), F(5))

  describe '#inverse', ->
    it 'should not segfault on odd N', ->
      fft = new FFT(5)
      fft.inverse(F(5), F(5), F(5))
