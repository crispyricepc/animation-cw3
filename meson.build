project('animation-cw3', 'cpp', default_options : ['cpp_std=c++20', 'warning_level=3'])

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules : ['Widgets', 'OpenGLWidgets'])

qobjects = qt6.compile_moc(
  headers : [
    'src/qobject/renderer/RendererWidget.h',
    'src/qobject/LeftPanelWidget.h',
    'src/qobject/MainWindow.h',
    'src/qobject/Scene.h',
    'src/qobject/SceneObject.h',
  ]
)

sources = [
  'src/main.cpp',
  'src/qobject/renderer/RendererWidget.cpp',
  'src/qobject/LeftPanelWidget.cpp',
  'src/qobject/MainWindow.cpp',
  'src/qobject/Scene.cpp',
  'src/qobject/SceneObject.cpp',
]

executable('animation-cw3',
  sources : sources + qobjects,
  dependencies : [
    qt6_dep
  ]
)