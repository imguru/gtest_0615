#ifndef DLOGGER_TARGET_H
#define DLOGGER_TARGET_H

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

#endif

