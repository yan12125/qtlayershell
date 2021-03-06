#include <QApplication>
#include <stdint.h>
#include <QLabel>
#include <QtLayerShell/layersurface_p.h>

using QtLayerShell::LayerSurface;

int main(int argc, char *argv[])
{
	qputenv("QT_QPA_PLATFORM", QByteArray("wayland"));
	qputenv("QT_WAYLAND_SHELL_INTEGRATION", QByteArray("layer-shell"));

    QApplication app(argc, argv);

    QLabel label;
    label.setText("Hello world!");
    label.show();

    LayerSurface* surface = LayerSurface::fromQWindow(label.windowHandle());
    surface->setAnchor(QtLayerShell::LayerSurface::anchor_bottom
                    | QtLayerShell::LayerSurface::anchor_left
                    | QtLayerShell::LayerSurface::anchor_right);
    surface->setExclusiveZone(label.size().height());
    surface->setMargin(0, 100, 0, 100);
    surface->setKeyboardInteractivity(true);

    return app.exec();
}
