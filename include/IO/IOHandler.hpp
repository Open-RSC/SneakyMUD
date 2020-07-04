#pragma once

namespace sneaky {
namespace IO {
	class IOHandler {
	protected:
		IOHandler() = default;
	public:
		virtual ~IOHandler() = default;
	};
}}