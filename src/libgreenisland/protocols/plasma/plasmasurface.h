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

#ifndef PLASMASURFACE_H
#define PLASMASURFACE_H

#include <QtCompositor/QWaylandSurfaceInterface>

#include "plasmashell.h"
#include "shellwindowview.h"

namespace GreenIsland {

class QuickSurface;

class PlasmaSurface : public QObject, public QWaylandSurfaceInterface, public QtWaylandServer::org_kde_plasma_surface
{
    Q_PROPERTY(ShellWindowView::Role role READ role NOTIFY roleChanged)
public:
    explicit PlasmaSurface(PlasmaShell *shell, QuickSurface *surface,
                           wl_client *client, uint32_t id);
    ~PlasmaSurface();

    ShellWindowView::Role role() const;

    ShellWindowView *view() const;

protected:
    bool runOperation(QWaylandSurfaceOp *op) Q_DECL_OVERRIDE;

Q_SIGNALS:
    void roleChanged();

private:
    Compositor *m_compositor;
    PlasmaShell *m_shell;
    QuickSurface *m_surface;
    ShellWindowView *m_view;
    ShellWindowView::Role m_role;
    bool m_deleting;

    ShellWindowView::Role wl2Role(uint32_t role);
    QString role2String(const ShellWindowView::Role &role);

    ShellWindowView::Flags wl2Flags(uint32_t wlFlags);

    void surface_destroy_resource(Resource *resource) Q_DECL_OVERRIDE;

    void surface_destroy(Resource *resource) Q_DECL_OVERRIDE;
    void surface_set_output(Resource *resource,
                            wl_resource *outputResource) Q_DECL_OVERRIDE;
    void surface_set_position(Resource *resource,
                              int32_t x, int32_t y) Q_DECL_OVERRIDE;
    void surface_set_role(Resource *resource,
                          uint32_t wlRole) Q_DECL_OVERRIDE;
    void surface_set_flags(Resource *resource,
                           uint32_t wlFlags) Q_DECL_OVERRIDE;
    void surface_set_screen_edge(Resource *resource,
                                 uint32_t screen_edge) Q_DECL_OVERRIDE;
};

}

#endif // PLASMASURFACE_H
