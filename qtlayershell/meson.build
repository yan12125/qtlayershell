# https://github.com/mesonbuild/meson/issues/3471
private_modules = ['QtCore', 'QtGui', 'QtWaylandClient']
private_module_includes = []
foreach module : private_modules
	private_module_includes += '/usr/include/qt/@0@/@1@'.format(
		module, qt5_modules.version())
	private_module_includes += '/usr/include/qt/@0@/@1@/@0@'.format(
		module, qt5_modules.version())
endforeach
qt_private = include_directories(private_module_includes)

qtlayershell_deps = [qt5_modules, wayland_client, lib_protos]

qtlayershell_moc = qt5.preprocess(
	moc_sources: [
		'layershellintegrationplugin.cpp',
	],
	moc_headers: [
		'../include/QtLayerShell/layersurface_p.h',
	],
	dependencies: qtlayershell_deps,
)

libqtlayershell = library(
	'qtlayershell', [
		'layerview.cpp',
		'layershell.cpp',
		'layershellintegration.cpp',
		'layershellintegrationplugin.cpp',
		'layersurface.cpp',
		qtlayershell_moc,
	],
	version: '0.0.0',
	link_whole: [protos],
	dependencies: qtlayershell_deps,
	include_directories: [qtlayershell_inc, qt_private],
	install: true,
)

qtlayershell = declare_dependency(
	link_with: libqtlayershell,
	dependencies: qtlayershell_deps,
	include_directories: [qtlayershell_inc, qt_private],
)
