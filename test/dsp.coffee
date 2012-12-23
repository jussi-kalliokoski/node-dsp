require '../lib/test-tools'

describe "DSP", ->
  describe ".add", ->
    it "should provide correct results", ->
      dst = F(4)

      DSP.add(dst, F([1,2,3,4]), F([4,3,2,1]))
      dst.should.be.identicalTo([5,5,5,5])

      DSP.add(dst, F([1,2,3,4]), F([1,1,1,1]))
      dst.should.be.identicalTo([2,3,4,5])

    it "should be able to deal with negative values", ->
      dst = F(4)

      DSP.add(dst, F([-1,9,4,7]), F([-25,22,19,-15]))
      dst.should.be.identicalTo([-26,31,23,-8])

      DSP.add(dst, F([1,2,3,4]), F([-4,-3,-2,-1]))
      dst.should.be.identicalTo([-3,-1,1,3])

    it "should be able to deal with decimal values", ->
      dst = F(4)

      DSP.add(dst, F([0.25,0.5,0.7,0.92]), F([0.22,0.8,0.12,0.01]))
      dst.should.be.identicalTo([0.47,1.3,0.82,0.93])

      DSP.add(dst, F([0.1,0.2,0.3,0.4]), F([0.4,0.3,0.2,0.1]))
      dst.should.be.identicalTo([0.5,0.5,0.5,0.5])

  describe ".sub", ->
    it "should provide correct results", ->
      dst = F(4)

      DSP.sub(dst, F([1,2,3,4]), F([4,3,2,1]))
      dst.should.be.identicalTo([-3,-1,1,3])

      DSP.sub(dst, F([1,2,3,4]), F([1,1,1,1]))
      dst.should.be.identicalTo([0,1,2,3])

    it "should be able to deal with negative values", ->
      dst = F(4)

      DSP.sub(dst, F([-1,9,4,7]), F([-25,22,19,-15]))
      dst.should.be.identicalTo([24,-13,-15,22])

      DSP.sub(dst, F([1,2,3,4]), F([-4,-3,-2,-1]))
      dst.should.be.identicalTo([5,5,5,5])

    it "should be able to deal with decimal values", ->
      dst = F(4)

      DSP.sub(dst, F([0.25,0.5,0.7,0.92]), F([0.22,0.8,0.12,0.01]))
      dst.should.be.identicalTo([0.03,-0.3,0.58,0.91])

      DSP.sub(dst, F([0.1,0.2,0.3,0.4]), F([0.4,0.3,0.2,0.1]))
      dst.should.be.identicalTo([-0.3,-0.1,0.1,0.3])
