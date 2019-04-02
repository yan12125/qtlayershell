#include <QtLayerShell/layershell_p.h>
#include <QtLayerShell/layersurface_p.h>
#include <QtLayerShell/layerview.h>
#include <QtWaylandClient/private/qwaylandwindow_p.h>
#include <QtWaylandClient/private/qwaylanddisplay_p.h>
#include <qwayland-wlr-layer-shell-unstable-v1.h>

namespace QtLayerShell {

QtWayland::zwlr_layer_surface_v1 create_layer_surface(
		LayerShell *shell, QtWaylandClient::QWaylandWindow *window)
{
	// TODO: Let the user select the output
	auto layerview = dynamic_cast<LayerView*>(window->window());
	if (layerview != nullptr) {
		return shell->get_layer_surface(window->object(),
				nullptr,
				layerview->m_layer,
				layerview->m_layer_namespace);
	}
	return shell->get_layer_surface(window->object(),
			nullptr,
			QtWayland::zwlr_layer_shell_v1::layer_top,
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
	m_layerview = dynamic_cast<LayerView*>(window->window());
	if (m_layerview == nullptr) {
		qWarning("Warning: using LayerView is strongly recommended");
	} else {
		m_layerview->m_layer_surface = this;
		m_layerview->apply();
	}
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
