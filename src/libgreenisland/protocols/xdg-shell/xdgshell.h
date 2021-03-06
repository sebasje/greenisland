/****************************************************************************
 * This file is part of Green Island.
 *
 * Copyright (C) 2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#ifndef XDGSHELL_H
#define XDGSHELL_H

#include <QtCore/QHash>
#include <QtCompositor/QWaylandGlobalInterface>

#include "qwayland-server-xdg-shell.h"

namespace QtWayland {
class InputDevice;
}

namespace GreenIsland {

class XdgSurface;
class XdgPopupGrabber;

class XdgShell : public QWaylandGlobalInterface, public QtWaylandServer::xdg_shell
{
public:
    explicit XdgShell();

    const wl_interface *interface() const Q_DECL_OVERRIDE;
    void bind(wl_client *client, uint32_t version, uint32_t id) Q_DECL_OVERRIDE;

    void pingSurface(XdgSurface *surface);

private:
    QMap<uint32_t, XdgSurface *> m_pings;
    QHash<QtWayland::InputDevice *, XdgPopupGrabber *> m_popupGrabbers;

    XdgPopupGrabber *popupGrabberForDevice(QtWayland::InputDevice *device);

    void shell_use_unstable_version(Resource *resource, int32_t version) Q_DECL_OVERRIDE;
    void shell_get_xdg_surface(Resource *resource, uint32_t id,
                               wl_resource *surfaceResource)  Q_DECL_OVERRIDE;
    void shell_get_xdg_popup(Resource *resource, uint32_t id, wl_resource *surfaceResource,
                             wl_resource *parentResource, wl_resource *seatResource,
                             uint32_t serial, int32_t x, int32_t y, uint32_t flags)  Q_DECL_OVERRIDE;
    void shell_pong(Resource *resource, uint32_t serial)  Q_DECL_OVERRIDE;
};

}

#endif // XDGSHELL_H
