/*
 * Copyright (C) 2015 Canonical, Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MIRACASTSERVICEADAPTOR_H_
#define MIRACASTSERVICEADAPTOR_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "miracastinterface.h"
#ifdef __cplusplus
}
#endif

#include "miracastservice.h"

namespace mcs {
class MiracastServiceAdapter : public MiracastService::Delegate {
public:
    static constexpr const char* kBusName{"com.canonical.miracast"};
    static constexpr const char* kManagerPath{"/"};
    static constexpr const char* kManagerIface{"com.canonical.miracast.Manager"};

    static std::shared_ptr<MiracastServiceAdapter> create(MiracastService &service);

    ~MiracastServiceAdapter();

    void OnStateChanged(NetworkDeviceState state) override;
    void OnDeviceFound(const NetworkDevice::Ptr &peer) override;
    void OnDeviceLost(const NetworkDevice::Ptr &peer) override;

private:
    static void OnNameAcquired(GDBusConnection *connection, const gchar *name, gpointer user_data);

    static void OnHandleScan(MiracastInterfaceManager *skeleton, GDBusMethodInvocation *invocation,
                              gpointer user_data);
    static void OnHandleConnectSink(MiracastInterfaceManager *skeleton, GDBusMethodInvocation *invocation,
                                      const gchar *address, gpointer user_data);

    MiracastServiceAdapter(MiracastService& service);

private:
    MiracastService &service_;
    MiracastInterfaceManager *manager_obj_;
    guint bus_id_;
    GDBusObjectManagerServer *object_manager_;
};
} // namespace mcs
#endif
