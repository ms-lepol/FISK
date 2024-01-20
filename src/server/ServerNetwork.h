#ifndef FISK_SERVER_NETWORK_H
#define FISK_SERVER_NETWORK_H

#include <atomic>

#include <gf/Random.h>
#include <gf/Ref.h>
#include <gf/SocketSelector.h>
#include <gf/TcpListener.h>

namespace fisk {

  class ServerNetwork {
  public:
    ServerNetwork();

    void run();

  private:
    static void signalHandler(int sig);

  private:
    gf::TcpListener m_listener;
    gf::SocketSelector m_selector;

    static std::atomic_bool g_running;
  };

}

#endif // FISK_SERVER_NETWORK_H
