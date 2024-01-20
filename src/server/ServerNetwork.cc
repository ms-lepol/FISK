#include "ServerNetwork.h"

#include <algorithm>
#include <cstdint>
#include <gf/Serialization.h>
#include <gf/SocketTypes.h>
#include <gf/Streams.h>
#include <gf/TcpSocket.h>
#include <gf/TcpListener.h>
#include <gf/Log.h>
#include <gf/SocketSelector.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <csignal>

#include "../common/NetworkConstants.h"

namespace fisk {

    ServerNetwork::ServerNetwork() :
    m_listener(PORT)
    {
        if(!m_listener){
            throw std::runtime_error("Can not start listener.");
        }

        std::signal(SIGINT, &ServerNetwork::signalHandler);
        m_selector.addSocket(m_listener);

        gf::Log::info("(SERVER) Launching server on port %s\n", fisk::PORT);
    }

    void ServerNetwork::run(){       
        static constexpr gf::Time Timeout = gf::seconds(1); // Wake up the server every seconds to see if something happened

        while (g_running) {
            auto status = m_selector.wait(Timeout);

            if (status == gf::SocketSelectorStatus::Timeout) {
                continue;
            }

            if (status == gf::SocketSelectorStatus::Error) {
                gf::Log::error("(SERVER) An error occurred in the selector. Stopping the server...\n");
                break;
            }

            // TODO
        }
    }

    void ServerNetwork::signalHandler(int sig) {
        assert(sig == SIGINT);
        g_running = false;
    }

    std::atomic_bool ServerNetwork::g_running(true);

        /*for (;;) {

            if(m_selector.wait() == gf::SocketSelectorStatus::Event){
                for(auto& socket : sockets){
                    if(m_selector.isReady(socket)){
                        // Read data from the socket
                    }
                }
            }

            // Accept a new connection ...
            if(m_selector.isReady(listener)){
                gf::TcpSocket client = listener.accept();
                gf::Log::info("(SERVER) Accepting new connections\n");
                sockets.push_back(std::move(client));
                m_selector.addSocket(sockets.back());
                if (client) {
                // and handle the client...
                    gf::Log::info("(SERVER) new connection on %s\n", client.getRemoteAddress().getHostname().c_str());

                }
            }
        }
        gf::Log::info("(SERVER) Server Closed");
        }*/

}