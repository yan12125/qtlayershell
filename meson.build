project(
	'qtlayershell',
	['c', 'cpp'],
	version: '0.0.1',
	license: 'MIT',
	meson_version: '>=0.48.0',
)

add_project_arguments('-DQT_STATICPLUGIN', '-DQT_PLUGIN', language: 'cpp')

qt5 = import('qt5')
qt5_modules = dependency('qt5', modules: [
	'Core',
	'Gui',
	'Quick',
	'WaylandClient',
        'XkbCommonSupport',
], private_headers: true, version: '>=5.13.0')
wayland_client = dependency('wayland-client')
wayland_protos = dependency('wayland-protocols')

qtlayershell_inc = include_directories('include')

subdir('protos')
subdir('qtlayershell')
subdir('demo')

includedir = get_option('includedir')
install_subdir('include/QtLayerShell', install_dir: includedir)

pkgconfig = import('pkgconfig')
pkgconfig.generate(
	libraries: libqtlayershell,
	version: meson.project_version(),
	filebase: meson.project_name(),
	name: meson.project_name(),
	description: 'Qt support for the Wayland layer-shell extension',
)
