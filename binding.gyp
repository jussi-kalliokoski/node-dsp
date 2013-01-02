{
  'targets': [{
    'target_name': 'node-dsp',
    'sources': [
      'src/module.cpp',
      'src/dsp.cpp',
      'src/filter.cpp',
      'src/fft.cpp',
      'src/kiss_fft/kiss_fft.c',
      'src/kiss_fft/kiss_fftr.c',
      'src/float32array.cpp'
    ]
  }]
}
