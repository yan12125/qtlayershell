#include "qwaylandlayershellintegration_p.h"
#include "qwaylandlayershell_p.h"

#include <qwayland-wlr-layer-shell-unstable-v1.h>
#include <QtWaylandClient/private/qwaylandwindow_p.h>
#include <QtWaylandClient/private/qwaylanddisplay_p.h>

QT_BEGIN_NAMESPACE

namespace QtLayerShell {

QWaylandLayerShellIntegration::QWaylandLayerShellIntegration() :
	m_layerShell(Q_NULLPTR)
{
}

bool QWaylandLayerShellIntegration::initialize(QtWaylandClient::QWaylandDisplay *display)
{
    QWaylandShellIntegration::initialize(display);
    display->addRegistryListener(registryLayer, this);
    return m_layerShell != nullptr;
}

QtWaylandClient::QWaylandShellSurface *QWaylandLayerShellIntegration::
	createShellSurface(QtWaylandClient::QWaylandWindow *window)
{
    return m_layerShell->createLayerSurface(window);
}

void QWaylandLayerShellIntegration::registryLayer(void *data,
	struct wl_registry *registry, uint32_t id,
	const QString &interface, uint32_t version)
{
    QWaylandLayerShellIntegration *shell =
		static_cast<QWaylandLayerShellIntegration *>(data);

    if (interface == QStringLiteral("zwlr_layer_shell_v1"))
        shell->m_layerShell = new QWaylandLayerShell(shell->m_display,
				new QtWayland::zwlr_layer_shell_v1(registry, id, version));
}

}

QT_END_NAMESPACE

//#include "qwaylandlayershellintegration.moc"