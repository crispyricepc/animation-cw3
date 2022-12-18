project('animation-cw3', 'cpp', default_options : ['cpp_std=c++20', 'warning_level=3'])

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules : ['Widgets', '3DCore', '3DRender', '3DExtras'])

qobjects = qt6.compile_moc(
  headers : [
    'src/Animation.h',
    'src/LeftPanelWidget.h',
    'src/MainWindow.h',
    'src/Particle.h',
  ]
)
qrc = qt6.compile_resources(
  sources : 'resources.qrc'
)

sources = [
  'src/main.cpp',
  'src/Animation.cpp',
  'src/Forces.cpp',
  'src/LeftPanelWidget.cpp',
  'src/MainWindow.cpp',
  'src/Particle.cpp',
]

clangtidy = find_program('clang-tidy', required: false)
if clangtidy.found()
    run_target(
        'tidy',
        command: [
            clangtidy,
            '-p', meson.build_root()
        ] + sources)
endif

executable('animation-cw3',
  sources : sources + qobjects + qrc,
  dependencies : [
    qt6_dep
  ]
)