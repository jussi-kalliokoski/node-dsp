var Should = require('should')
var DSP = require('../build/Release/node-dsp')
var i = require('util').inspect

var epsilon = 0.01

global.numericalCompare = function (x, y, e) {
	if (x === y || (isNaN(x) && isNaN(y))) return true

	return Math.abs((x - y) / x) < (e || epsilon)
}

global.F = function (d) {
	return new Float32Array(d)
}

global.DSP = DSP.DSP
global.Filter = DSP.Filter
global.FFT = DSP.FFT

Should.Assertion.prototype.approximately = function (val, desc) {
	var obj = this.obj

	this.assert(numericalCompare(obj, val), function () {
		return 'expected ' + i(obj) + ' to be approximately ' + i(val) + (desc ? " | " + desc : "")
	}, function () {
		return 'expected ' + i(obj) + ' not to be approximately ' + i(val) + (desc ? " | " + desc : "")
	}, val)

	return this
}

Should.Assertion.prototype.identicalTo = function (val, desc) {
	var obj = this.obj

	function pos () { return 'expected ' + i([].slice.call(obj)) + ' to be identical to ' + i(val) + (desc ? " | " + desc : "") }
	function neg () { return 'expected ' + i([].slice.call(obj)) + ' to not be identical to ' + i(val) + (desc ? " | " + desc : "") }

	this.assert(val.length === obj.length, pos, neg, val)

	for (var n=0; n<val.length; n++) {
		this.assert(numericalCompare(val[n], obj[n]), pos, neg, val)
	}

	return this
}
