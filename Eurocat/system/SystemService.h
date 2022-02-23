#pragma once

namespace Eurocat::System
{
	class SystemService
	{
	public:
		virtual ~SystemService() = default;
		virtual void OnStart() { };
		virtual void OnStop() { };
	};
}
