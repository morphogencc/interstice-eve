#include "Logger.h"

using namespace midnight::eve;

std::shared_ptr<Logger> Logger::make() {
	std::shared_ptr<Logger> logger = std::shared_ptr<Logger>(new Logger());
	return logger;
}

void Logger::setEndpoint(std::string endpoint) {
}

void Logger::setAppName(std::string app) {
	mAppName = app;
}

void Logger::setClientName(std::string client) {
	mClientName = client;
}

void Logger::setHeartbeat(int delayInMilliseconds) {
	mHeartbeatDelay = delayInMilliseconds;
	mRunHeartbeat = false;
	mHeartbeatThread = std::thread(&Logger::updateHeartbeat, this);
}

void Logger::sendInformational(std::string msg) {
	sendEvent(EventType::INFORMATIONAL, msg);
}

void Logger::sendInteraction(std::string msg) {
	sendEvent(EventType::EVENT, msg);
}

Logger::~Logger() {
	if (mHeartbeatThread.joinable()) {
		mHeartbeatThread.join();
	}
}

Logger::Logger() {
	mHttpClient = midnight::http::HttpClient::make();
	mEndpoint = "http://127.0.0.1:3000/collectionapi/logs/"; // standard meteor endpoint
	mClientName = "Midnight Commercial";
	mAppName = "Test Application";
}

void Logger::sendEvent(EventType event, std::string msg) {
	Json::Value logMessage;
	logMessage["time"] = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();;
	logMessage["client"] = mClientName;
	logMessage["application"] = mAppName;
	logMessage["type"] = event;
	logMessage["message"] = msg;

	midnight::http::HttpRequest Post;
	Post.mUrl = mEndpoint;
	Post.mMethod = midnight::http::HTTP_POST;
	Post.mRequestBody = mHttpClient->jsonToString(logMessage);

	mHttpClient->addRequest(Post);
}

void Logger::sendHeartbeat() {
	sendEvent(EventType::HEARTBEAT, "");
}

void Logger::updateHeartbeat() {
	mRunHeartbeat = true;
	while (mRunHeartbeat) {
		mHttpMutex.lock();
		sendHeartbeat();
		mHttpMutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(mHeartbeatDelay));
	}
}
