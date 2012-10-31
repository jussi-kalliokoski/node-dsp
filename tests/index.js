var fs = require('fs')
var Path = require('path')
var DSP = require('../build/Release/node-dsp')

const EPSILON = 0.0004

function ls (path, expr) {
	var dir = fs.readdirSync(path)

	if (!expr) return dir

	return dir.filter(function (p) {
		return expr.test(p)
	})
}

function numericalCompare (x, y, e) {
	if (x === y || (isNaN(x) && isNaN(y))) return true

	return Math.abs((x - y) / x) < e
}

var dirname = Path.join(__dirname, 'tests')
var done = 0
var passed = 0
var failed = []

console.error('::: Running tests...')

ls(dirname, /\.json$/).forEach(function (testpath) {
	var tests = require(Path.join(dirname, testpath))

	testing: for (var i=0; i<tests.length; i++, done++) {
		try {
			var args = tests[i].arguments.map(function (a, i) {
				if (!i || Array.isArray(a)) {
					return new Float32Array(a)
				}

				return a
			})

			DSP[tests[i].method].apply(null, args)

			var r = new Float32Array(tests[i].result)

			for (var n=0; n<r.length; n++) {
				if (numericalCompare(r[n], args[i][n])) continue

				failed.push({
					error: Error('result mismatch'),
					test: i,
					filename: testpath
				})

				continue testing
			}

			passed += 1
		} catch (e) {
			failed.push({
				error: e,
				test: i,
				filename: testpath
			})
		}
	}

	
})

failed.forEach(function (e) {
	console.error('Test #' + e.test, 'in', '`' + e.filename + '`',
		'failed (' + e.error + ')')
})

console.error(':::', passed, 'out of', done, 'tests passed.')

process.exit(failed.length ? 1 : 0)
