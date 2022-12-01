project('animation-cw3', 'cpp', default_options : ['cpp_std=c++20', 'warning_level=everything'])

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules : ['Core', 'Gui', 'Widgets'])

qobjects = qt6.compile_moc(
  headers : [
    'src/qobject/MainWindow.h'
  ]
)

sources = [
  'src/main.cpp',
  'src/qobject/MainWindow.cpp'
]

executable('animation-cw3',
  sources : sources + qobjects,
  dependencies : [
    qt6_dep
  ]
)