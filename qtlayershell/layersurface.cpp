#include <QtLayerShell/layershell_p.h>
#include <QtLayerShell/layersurface_p.h>
#include <QtWaylandClient/private/qwaylandwindow_p.h>
#include <QtWaylandClient/private/qwaylanddisplay_p.h>
#include <qwayland-wlr-layer-shell-unstable-v1.h>
#include <QDebug>

namespace QtLayerShell {

QtWayland::zwlr_layer_surface_v1 create_layer_surface(
		LayerShell *shell, QtWaylandClient::QWaylandWindow *window)
{
	// TODO: Let the user select the output
	return shell->get_layer_surface(window->object(),
			nullptr,
			QtWayland::zwlr_layer_shell_v1::layer_bottom,
			QString::fromUtf8("qt"));
}

LayerSurface::LayerSurface(LayerShell *shell,
		QtWaylandClient::QWaylandWindow *window) :
	QtWaylandClient::QWaylandShellSurface(window),
	QtWayland::zwlr_layer_surface_v1(create_layer_surface(shell, window)),
	m_window(window)
{
	set_size(m_window->window()->width(), m_window->window()->height());
	// window->window() -> QWindow
}

void LayerSurface::apply() {
	set_anchor(m_anchor);
	set_exclusive_zone(m_exclusive_zone);
	set_margin(m_margin.top, m_margin.right,
		m_margin.bottom, m_margin.left);
	set_keyboard_interactivity(m_keyboard_interactivity);
	// Commit and roundtrip immediately
	m_window->QtWayland::wl_surface::commit();
	m_window->display()->forceRoundTrip();
}

void LayerSurface::setAnchor(uint32_t anchor)
{
	m_anchor = anchor;
	apply();
}

void LayerSurface::setExclusiveZone(int32_t exclusive_zone)
{
	m_exclusive_zone = exclusive_zone;
	apply();
}

void LayerSurface::setMargin(int32_t top, int32_t right,
		int32_t bottom, int32_t left) {
	m_margin.top = top;
	m_margin.right = right;
	m_margin.bottom = bottom;
	m_margin.left = left;
	apply();
}

void LayerSurface::setKeyboardInteractivity(bool keyboard_interactivity)
{
	m_keyboard_interactivity = keyboard_interactivity;
	apply();
}

LayerSurface::~LayerSurface()
{
    destroy();
}

void LayerSurface::zwlr_layer_surface_v1_closed()
{
	m_window->window()->close();
}

void LayerSurface::applyConfigure() {
	m_window->resizeFromApplyConfigure(m_pendingSize);
}

void LayerSurface::zwlr_layer_surface_v1_configure(uint32_t serial,
			uint32_t width, uint32_t height)
{
	m_pendingSize = {width, height};
	m_window->applyConfigureWhenPossible();
	ack_configure(serial);
}

}
