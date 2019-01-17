#pragma once

class NonCopyable
{
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
public:
	NonCopyable(const NonCopyable&) = delete;
	const NonCopyable& operator=(const NonCopyable&) = delete;
};

class Copyable
{
protected:
	Copyable() = default;
	~Copyable() = default;
public:
	Copyable(const Copyable&) = default;
	Copyable& operator=(const Copyable&) = default;
};