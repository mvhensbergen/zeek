// See the file "COPYING" in the main distribution directory for copyright.
//
// Dummy log writer that just discards everything (but still pretends to rotate).

#pragma once

#include "logging/WriterBackend.h"

namespace zeek::logging::writer::detail {

class None : public zeek::logging::WriterBackend {
public:
	explicit None(zeek::logging::WriterFrontend* frontend) : zeek::logging::WriterBackend(frontend)	{}
	~None() override {};

	static zeek::logging::WriterBackend* Instantiate(zeek::logging::WriterFrontend* frontend)
		{ return new None(frontend); }

protected:
	bool DoInit(const WriterInfo& info, int num_fields,
			    const threading::Field* const * fields) override;
	bool DoWrite(int num_fields, const threading::Field* const* fields,
			     threading::Value** vals) override { return true; }
	bool DoSetBuf(bool enabled) override { return true; }
	bool DoRotate(const char* rotated_path, double open,
			      double close, bool terminating) override;
	bool DoFlush(double network_time) override { return true; }
	bool DoFinish(double network_time) override { return true; }
	bool DoHeartbeat(double network_time, double current_time) override { return true; }
};

} // namespace zeek::logging::writer::detail
