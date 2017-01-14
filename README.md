# midnight-eve

midnight-eve (short for 'eavesdropper') is the cpp implementation of the Midnight Commercial Eavesdropper.

## Requirements
* requires midnight-http

## Usage
The `Logger` class reports back log messages to a central server with the following information:
* message time
* client name (for ease of sorting)
* application name
* event type (see below)
* a log message

Currently, midnight-eve supports three types of messages:

* `HEARTBEAT` -- signals that the application is still alive
* `INFORMATIONAL` -- the application wants to tell the server an informational message (such as it reboot)
* `EVENT` -- events that an application wishes to be reported to the server (such as a user interaction for analytics)

These are sent from within the `Logger` class by their matching functions, respectively:

```
			void sendHeartbeat();
			void sendInformational(std::string msg);
			void sendInteraction(std::string msg);
```

There are also setters for setting the client name, application name, and endpoint:

```
			void setEndpoint(std::string endpoint);
			void setAppName(std::string app);
			void setClientName(std::string client);
```