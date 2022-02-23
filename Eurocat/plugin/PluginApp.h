#pragma once

namespace Eurocat
{
	class EurocatPluginApp
	{
	public:
		EuroScopePlugIn::CPlugIn* GetPlugin();
		void Startup();
		void Cleanup();

	private:
		std::shared_ptr<EuroScopePlugIn::CPlugIn> createdPlugin;
	};
}
