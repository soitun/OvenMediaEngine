//==============================================================================
//
//  OvenMediaEngine
//
//  Created by Getroot
//  Copyright (c) 2023 AirenSoft. All rights reserved.
//
//==============================================================================
#pragma once

#include <modules/http/http.h>
#include "whip_interceptor.h"
#include "whip_observer.h"

class WhipServer : public ov::EnableSharedFromThis<WhipServer>
{
public:
	WhipServer(const cfg::bind::cmm::Webrtc &webrtc_bind_cfg);

	bool Start(const std::shared_ptr<WhipObserver> &observer, const ov::SocketAddress *address, const ov::SocketAddress *tls_address, int worker_count);
	bool Stop();

	bool AppendCertificate(const std::shared_ptr<const info::Certificate> &certificate);
	bool RemoveCertificate(const std::shared_ptr<const info::Certificate> &certificate);

	void SetCors(const info::VHostAppName &vhost_app_name, const std::vector<ov::String> &url_list);
	void EraseCors(const info::VHostAppName &vhost_app_name);

private:

	std::shared_ptr<WhipInterceptor> CreateInterceptor();
	ov::String GetIceServerLinkValue(const ov::String &URL, const ov::String &username, const ov::String &credential);

	const cfg::bind::cmm::Webrtc _webrtc_bind_cfg;

	std::shared_ptr<WhipObserver> _observer;

	ov::SocketAddress _http_server_address;
	std::shared_ptr<http::svr::HttpServer> _http_server;
	ov::SocketAddress _https_server_address;
	std::shared_ptr<http::svr::HttpsServer> _https_server;

	std::vector<ov::String> _link_headers;
	bool _tcp_force = false;

	http::CorsManager _cors_manager;
};