#ifndef _LAYERSURFACE_H
#define _LAYERSURFACE_H
#include <wayland-client.h>
#include <qwayland-wlr-layer-shell-unstable-v1.h>
#include <QtWaylandClient/private/qwaylandwindow_p.h>
#include <QtWaylandClient/private/qwaylandshellsurface_p.h>

namespace QtLayerShell {

class LayerShell;
class LayerView;

class LayerSurface : public QtWaylandClient::QWaylandShellSurface,
	public QtWayland::zwlr_layer_surface_v1
{
	Q_OBJECT
public:
    LayerSurface(LayerShell *shell, QtWaylandClient::QWaylandWindow *window);
    virtual ~LayerSurface();

    void applyConfigure() override;

private:
	void zwlr_layer_surface_v1_configure(uint32_t serial,
			uint32_t width, uint32_t height) override;
	void zwlr_layer_surface_v1_closed() override;

	QtWaylandClient::QWaylandWindow *m_window;
	LayerView *m_layerview;

	QSize m_pendingSize = {0, 0};

	friend class LayerView;
};

}

#endif
