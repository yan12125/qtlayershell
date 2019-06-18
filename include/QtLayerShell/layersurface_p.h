#ifndef _LAYERSURFACE_H
#define _LAYERSURFACE_H
#include <wayland-client.h>
#include <qwayland-wlr-layer-shell-unstable-v1.h>
#include <QtWaylandClient/private/qwaylandwindow_p.h>
#include <QtWaylandClient/private/qwaylandshellsurface_p.h>

namespace QtLayerShell {

using layer = QtWayland::zwlr_layer_shell_v1::layer;
using anchor = QtWayland::zwlr_layer_surface_v1::anchor;

class LayerShell;

class LayerSurface : public QtWaylandClient::QWaylandShellSurface,
	public QtWayland::zwlr_layer_surface_v1
{
	Q_OBJECT
public:
    LayerSurface(LayerShell *shell, QtWaylandClient::QWaylandWindow *window);
    virtual ~LayerSurface();

	void setAnchor(uint32_t anchor);

	void setExclusiveZone(int32_t zone);

	void setMargin(int32_t top, int32_t right, int32_t bottom, int32_t left);

	void setKeyboardInteractivity(bool interactive);

    void applyConfigure() override;

    static LayerSurface* fromQWindow(QWindow* window);

private:
	void zwlr_layer_surface_v1_configure(uint32_t serial,
			uint32_t width, uint32_t height) override;
	void zwlr_layer_surface_v1_closed() override;

	QtWaylandClient::QWaylandWindow *m_window;

	QSize m_pendingSize = {0, 0};

	void apply();

	uint32_t m_anchor = 0;
	int32_t m_exclusive_zone = 0;
	bool m_keyboard_interactivity = false;
	struct {
		int32_t top = 0, right = 0, bottom = 0, left = 0;
	} m_margin;
};

}

#endif
