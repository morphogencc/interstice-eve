#include <string>
#include <memory>
#include "HTTPClient.h"

namespace midnight {
	namespace eve {
		enum EventType {
			HEARTBEAT,
			INFORMATIONAL,
			EVENT
		};

		class Logger {
		public:
			static std::shared_ptr<Logger> make();
			void setEndpoint(std::string endpoint);
			void setAppName(std::string app);
			void setClientName(std::string client);
			void sendHeartbeat();
			void sendInformational(std::string msg);
			void sendInteraction(std::string msg);
			~Logger();
		protected:
			Logger();
			void sendEvent(EventType event, std::string msg);
			std::string mEndpoint;
			std::string mAppName;
			std::string mClientName;
			std::shared_ptr<midnight::http::HttpClient> mHttpClient;
		};
	}
}