#include <string>
#include <memory>
#include <thread>
#include <mutex>
#include "HTTPClient.h"

namespace midnight {
	namespace eve {
		enum EventType {
			HEARTBEAT,
			APP_ERROR,
			INFORMATIONAL,
			EVENT,
		};

		class Logger {
		public:
			static std::shared_ptr<Logger> make();
			void setEndpoint(std::string endpoint);
			void setAppName(std::string app);
			void setClientName(std::string client);
			void setHeartbeat(int delayInMilliseconds);
			void sendInformational(std::string msg);
			void sendInteraction(std::string msg);
			~Logger();
		protected:
			Logger();
			void sendEvent(EventType event, std::string msg);
			void sendHeartbeat();
			void updateHeartbeat();
			std::string mEndpoint;
			std::string mAppName;
			std::string mClientName;
			std::shared_ptr<midnight::http::HttpClient> mHttpClient;
			std::thread mHeartbeatThread;
			bool mRunHeartbeat;
			std::mutex mHttpMutex;
			int mHeartbeatDelay;
		};
	}
}